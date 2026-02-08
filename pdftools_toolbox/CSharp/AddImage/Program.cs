/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddImage <inputPath> <imagePath> <pageNumber> <outputPath>
 *                  Example: in.pdf in.png 1 out.pdf
 *                  
 * Title:           Add image to PDF
 *                  
 * Description:     Place an image with a specified size at a specific
 *                  location of a page.
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

namespace ToolboxAddImage
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddImage <inputPath> <imagePath> <pageNumber> <outputPath>");
            Console.WriteLine("       Example: in.pdf in.png 1 out.pdf");

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
                string imagePath = args[1];
                int pageNumber = int.Parse(args[2]);
                string outPath = args[3];

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

                    // Copy pages preceding selected page and append to output document
                    PageList inPageRange = inDoc.Pages.GetRange(0, pageNumber - 1);
                    PageList copiedPages = PageList.Copy(outDoc, inPageRange, copyOptions);
                    outDoc.Pages.AddRange(copiedPages);

                    // Copy selected page, add image, and append to output document
                    Page outPage = Page.Copy(outDoc, inDoc.Pages[pageNumber - 1], copyOptions);
                    AddImage(outDoc, outPage, imagePath, 150, 150);
                    outDoc.Pages.Add(outPage);

                    // Copy remaining pages and append to output document
                    inPageRange = inDoc.Pages.GetRange(pageNumber, inDoc.Pages.Count - pageNumber);
                    copiedPages = PageList.Copy(outDoc, inPageRange, copyOptions);
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

        private static void AddImage(Document document, Page page, string imagePath, double x, double y)
        {
            // Create content generator 
            using ContentGenerator generator = new ContentGenerator(page.Content, false);

            // Load image from input path
            using Stream inImage = new FileStream(imagePath, FileMode.Open, FileAccess.Read);

            // Create image object
            Image image = Image.Create(document, inImage);
            double resolution = 150;

            // Calculate rectangle for image 
            PdfTools.Toolbox.Geometry.Integer.Size size = image.Size;
            Rectangle rect = new Rectangle
            {
                Left = x,
                Bottom = y,
                Right = x + size.Width * 72 / resolution,
                Top = y + size.Height * 72 / resolution
            };

            // Paint image into the specified rectangle 
            generator.PaintImage(image, rect);
        }
    }
}