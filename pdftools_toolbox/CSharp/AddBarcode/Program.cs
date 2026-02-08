/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddBarcode <inputPath> <barcode> <fontfile> <outputPath>
 *                  Example: in.pdf \"PDF123\" free3of9.ttf out.pdf
 *                  
 * Title:           Add barcode to PDF
 *                  
 * Description:     Generate and add a barcode at a specified position on the
 *                  first page of a PDF document.
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
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;
using PdfTools.Toolbox.Geometry.Real;

namespace ToolboxAddBarcode
{
    class Program
    {
        private static readonly double Border = 20;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddBarcode <inputPath> <barcode> <fontfile> <outputPath>");
            Console.WriteLine("       Example: in.pdf \"PDF123\" free3of9.ttf out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 4 || args.Length > 4)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];
                string barcode = args[1];
                string fontPath = args[2];
                string outPath = args[3];

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create file stream
                using (Stream fontStream = new FileStream(fontPath, FileMode.Open, FileAccess.Read))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Create embedded font in output document
                    Font font = Font.Create(outDoc, fontStream, true);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy first page, add barcode, and append to output document
                    Page outPage = Page.Copy(outDoc, inDoc.Pages[0], copyOptions);
                    AddBarcode(outDoc, outPage, barcode, font, 50);
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

        private static void AddBarcode(Document outputDoc, Page outPage, string barcode,
            Font font, double fontSize)
        {
            // Create content generator 
            using ContentGenerator gen = new ContentGenerator(outPage.Content, false);

            // Create text object
            Text barcodeText = Text.Create(outputDoc);

            // Create text generator
            using (TextGenerator textGenerator = new TextGenerator(barcodeText, font, fontSize, null))
            {
                // Calculate position
                Point position = new Point
                {
                    X = outPage.Size.Width - (textGenerator.GetWidth(barcode) + Border),
                    Y = outPage.Size.Height - (fontSize * (font.Ascent + font.Descent) + Border)
                };

                // Move to position
                textGenerator.MoveTo(position);
                // Add given barcode string
                textGenerator.ShowLine(barcode);
            }
            // Paint the positioned barcode text
            gen.PaintText(barcodeText);
        }
    }
}
