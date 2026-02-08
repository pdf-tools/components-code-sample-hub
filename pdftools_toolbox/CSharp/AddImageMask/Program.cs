/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddImageMask <inputPath> <imageMaskPath> <outputPath>
 *                  Example: in.pdf in.tif out.pdf
 *                  
 * Title:           Add image mask to PDF
 *                  
 * Description:     Place a rectangular image mask at a specified location of
 *                  a page. The image mask is a stencil mask to fill or mask
 *                  out the image per pixel.
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


namespace AddImageMask
{
    class Program
    {
        private static Paint paint;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddImageMask <inputPath> <imageMaskPath> <outputPath>");
            Console.WriteLine("       Example: in.pdf in.tif out.pdf");

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
                string imageMaskPath = args[1];
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

                    // Get the device color space
                    ColorSpace colorSpace = ColorSpace.CreateProcessColorSpace(outDoc, ProcessColorSpaceType.Rgb);

                    // Create paint object
                    paint = Paint.Create(outDoc, colorSpace, new double[] { 1.0, 0.0, 0.0 }, null);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy first page, add image mask, and append to output document
                    Page outPage = Page.Copy(outDoc, inDoc.Pages[0], copyOptions);
                    AddImageMask(outDoc, outPage, imageMaskPath, 250, 150);
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

        private static void AddImageMask(Document document, Page outPage, string imagePath, 
            double x, double y)
        {
            // Create content generator 
            using ContentGenerator generator = new ContentGenerator(outPage.Content, false);

            // Load image from input path
            using Stream inImage = new FileStream(imagePath, FileMode.Open, FileAccess.Read);

            // Create image mask object
            ImageMask imageMask = ImageMask.Create(document, inImage);
            double resolution = 150;

            // Calculate rectangle for image 
            PdfTools.Toolbox.Geometry.Integer.Size size = imageMask.Size;
            Rectangle rect = new Rectangle
            {
                Left = x,
                Bottom = y,
                Right = x + size.Width * 72 / resolution,
                Top = y + size.Height * 72 / resolution
            };

            // Paint image mask into the specified rectangle
            generator.PaintImageMask(imageMask, rect, paint);
        }
    }
}