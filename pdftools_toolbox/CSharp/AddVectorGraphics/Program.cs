/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddVectorGraphics <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Add vector graphic to PDF
 *                  
 * Description:     Draw a line on an existing PDF page.
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

using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxAddVectorGraphics
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddVectorGraphics <inputPath> <outputPath>");
            Console.WriteLine("       Example: in.pdf out.pdf");

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
                using (System.IO.Stream inStream = new System.IO.FileStream(inPath, System.IO.FileMode.Open, System.IO.FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (System.IO.Stream outStream = new System.IO.FileStream(outPath, System.IO.FileMode.Create, System.IO.FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages from input document
                    foreach (Page inPage in inDoc.Pages)
                    {
                        Page outPage = Page.Copy(outDoc, inPage, copyOptions);

                        // Add a line
                        AddLine(outDoc, outPage);

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

        private static void AddLine(Document document, Page page)
        {
            // Create content generator 
            using ContentGenerator generator = new ContentGenerator(page.Content, false);

            // Create a path
            Path path = new Path();
            using (PathGenerator pathGenerator = new PathGenerator(path))
            {
                // Draw a line diagonally across the page
                Size pageSize = page.Size;
                pathGenerator.MoveTo(new Point() { X = 10.0, Y = 10.0 });
                pathGenerator.LineTo(new Point() { X = pageSize.Width - 10.0, Y = pageSize.Height - 10.0 });
            }

            // Create a RGB color space
            ColorSpace deviceRgbColorSpace = ColorSpace.CreateProcessColorSpace(document, ProcessColorSpaceType.Rgb);

            // Create a red color
            double[] color = new double[] { 1.0, 0.0, 0.0 };

            // Create a paint
            Paint paint = Paint.Create(document, deviceRgbColorSpace, color, null);

            // Create stroking parameters with given paint and line width
            Stroke stroke = new Stroke(paint, 10.0);

            // Draw the path onto the page
            generator.PaintPath(path, null, stroke);
        }
    }
}