/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxFitPage <inputPath> <outputPath>
 *                  
 * Title:           Fit pages to specific page format
 *                  
 * Description:     Fit each page of a PDF document to a specific page
 *                  format.
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
using PdfTools.Toolbox.Geometry;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxFitPage
{
    class Program
    {
        // A4 portrait
        private static readonly Size TargetSize = new Size() { Width = 595, Height = 842 };
        private static readonly bool AllowRotate = true;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxFitPage <inputPath> <outputPath>");
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

                    // Copy pages
                    foreach (Page inPage in inDoc.Pages)
                    {
                        Page outPage = null;
                        Size pageSize = inPage.Size;

                        bool rotate = AllowRotate &&
                            (pageSize.Height >= pageSize.Width) != (TargetSize.Height >= TargetSize.Width);
                        Size rotatedSize = pageSize;

                        if (rotate)
                            rotatedSize = new Size { Width = pageSize.Height, Height = pageSize.Width };

                        if (rotatedSize.Width == TargetSize.Width && rotatedSize.Height == TargetSize.Width)
                        {
                            // If size is correct, copy page only
                            outPage = Page.Copy(outDoc, inPage, copyOptions);

                            if (rotate)
                                outPage.Rotate(Rotation.Clockwise);
                        }
                        else
                        {
                            // Create new page of correct size and fit existing page onto it
                            outPage = Page.Create(outDoc, TargetSize);

                            // Copy page as group
                            Group group = Group.CopyFromPage(outDoc, inPage, copyOptions);
                            // Calculate scaling and position of group
                            double scale = Math.Min(TargetSize.Width / rotatedSize.Width,
                                TargetSize.Height / rotatedSize.Height);

                            // Calculate position
                            Point position = new Point
                            {
                                X = (TargetSize.Width - pageSize.Width * scale) / 2,
                                Y = (TargetSize.Height - pageSize.Height * scale) / 2
                            };

                            // Create content generator
                            using ContentGenerator generator = new ContentGenerator(outPage.Content, false);

                            // Calculate and apply transformation
                            AffineTransform transform = AffineTransform.Identity;
                            transform.Translate(position.X, position.Y);
                            transform.Scale(scale, scale);

                            Point point = new Point()
                            {
                                X = pageSize.Width / 2.0,
                                Y = pageSize.Height / 2.0
                            };

                            // Rotate input file 
                            if (rotate)
                                transform.Rotate(90, point);
                            generator.Transform(transform);

                            // Paint group
                            generator.PaintGroup(group, null, null);
                        }
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
    }
}