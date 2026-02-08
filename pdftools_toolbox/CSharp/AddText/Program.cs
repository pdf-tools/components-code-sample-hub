/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddText <inputPath> <textString> <outputPath>
 *                  Example: in.pdf \"Test String\" out.pdf
 *                  
 * Title:           Add text to PDF
 *                  
 * Description:     Add text at a specified position on the first page of a
 *                  PDF document.
 *                  
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2026 PDF Tools AG, Switzerland
 *                  Permission to use, copy, modify, and distribute this
 *                  software and its documentation for any purpose and without
 *                  fee is hereby granted, provided that the above copyright
 *                  notice appear in all copies and that both that copyright
 *                  notice and this permission notice appear in supporting
 *                  documentation. This software is provided "as is" without
 *                  express or implied warranty.
 *
 ***************************************************************************/

using System;
using System.IO;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;


namespace ToolboxAddText
{
    class Program
    {
        private static Font font;
        private static readonly double border = 40;
        private static readonly double fontSize = 15;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddText <inputPath> <textString> <outputPath>");
            Console.WriteLine("       Example: in.pdf \"Test String\" out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 3 || args.Length > 3)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];
                string textString = args[1];
                string outPath = args[2];

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Create a font
                    font = Font.CreateFromSystem(outDoc, "Arial", "Italic", true);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy first page, add text, and append to output document
                    Page outPage = Page.Copy(outDoc, inDoc.Pages[0], copyOptions);
                    AddText(outDoc, outPage, textString);
                    outDoc.Pages.Add(outPage);

                    // Copy remaining pages and append to output document
                    PageList inPageRange = inDoc.Pages.GetRange(1, inDoc.Pages.Count - 1);
                    PageList copiedPages = PageList.Copy(outDoc, inPageRange, copyOptions);
                    outDoc.Pages.AddRange(copiedPages);
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void CopyDocumentData(Document inDoc, Document outDoc)
        {
            // Copy document-wide data

            // Output intent
            if (inDoc.OutputIntent != null)
                outDoc.OutputIntent = IccBasedColorSpace.Copy(outDoc, inDoc.OutputIntent);

            // Metadata
            outDoc.Metadata = Metadata.Copy(outDoc, inDoc.Metadata);

            // Viewer settings
            outDoc.ViewerSettings = ViewerSettings.Copy(outDoc, inDoc.ViewerSettings);

            // Associated files (for PDF/A-3 and PDF 2.0 only)
            FileReferenceList outAssociatedFiles = outDoc.AssociatedFiles;
            foreach (FileReference inFileRef in inDoc.AssociatedFiles)
                outAssociatedFiles.Add(FileReference.Copy(outDoc, inFileRef));

            // Plain embedded files
            FileReferenceList outEmbeddedFiles = outDoc.PlainEmbeddedFiles;
            foreach (FileReference inFileRef in inDoc.PlainEmbeddedFiles)
                outEmbeddedFiles.Add(FileReference.Copy(outDoc, inFileRef));
        }

        private static void AddText(Document outputDoc, Page outPage, string textString)
        {
            // Create content generator and text object
            using ContentGenerator gen = new ContentGenerator(outPage.Content, false);
            Text text = Text.Create(outputDoc);

            // Create text generator
            using (TextGenerator textGenerator = new TextGenerator(text, font, fontSize, null))
            {
                // Calculate position
                Point position = new Point
                {
                    X = border,
                    Y = outPage.Size.Height - border - fontSize * font.Ascent
                };

                // Move to position
                textGenerator.MoveTo(position);
                // Add given text string
                textGenerator.ShowLine(textString);
            }
            // Paint the positioned text
            gen.PaintText(text);
        }
    }
}