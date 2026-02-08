/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxStampPageNumber <inputPath> <outputPath>
 *                  
 * Title:           Stamp page number to PDF
 *                  
 * Description:     Stamp the page number to the footer of each page of a PDF
 *                  document.
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

namespace ToolboxStampPageNumber
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxStampPageNumber <inputPath> <outputPath>");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2 || args.Length > 2)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];
                string outPath = args[1];

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Create embedded font in output document 
                    Font font = Font.CreateFromSystem(outDoc, "Arial", string.Empty, true);

                    // Copy all pages from input document
                    int currentPageNumber = 1;
                    foreach (Page inPage in inDoc.Pages)
                    {
                        // Copy page from input to output
                        Page outPage = Page.Copy(outDoc, inPage, copyOptions);

                        // Stamp page number on current page of output document
                        AddPageNumber(outDoc, outPage, font, currentPageNumber++);

                        // Add page to output document
                        outDoc.Pages.Add(outPage);
                    }
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

        private static void AddPageNumber(Document outDoc, Page outPage, Font font, int pageNumber)
        {
            // Create content generator
            using ContentGenerator generator = new ContentGenerator(outPage.Content, false);

            // Create text object
            Text text = Text.Create(outDoc);

            // Create a text generator with the given font, size and position
            using (TextGenerator textgenerator = new TextGenerator(text, font, 8, null))
            {
                // Generate string to be stamped as page number
                string stampText = string.Format("Page {0}", pageNumber);

                // Calculate position for centering text at bottom of page
                Point position = new Point
                {
                    X = (outPage.Size.Width / 2) - (textgenerator.GetWidth(stampText) / 2),
                    Y = 10
                };

                // Position the text
                textgenerator.MoveTo(position);
                // Add page number
                textgenerator.Show(stampText);
            }
            // Paint the positioned text
            generator.PaintText(text);
        }
    }
}