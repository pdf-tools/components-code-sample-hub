/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxMultipleUp <inputPath> <outputPath>
 *                  
 * Title:           Place multiple pages on one page
 *                  
 * Description:     Place four pages of a PDF document on a single page.
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

namespace ToolboxMultipleUp
{
    class Program
    {
        // Put 4 pages on 1
        private const int Nx = 2;
        private const int Ny = 2;

        // A4 portrait
        private static readonly Size PageSize = new Size() { Width = 595, Height = 842 };
        private const double Border = 10;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxMultipleUp <inputPath> <outputPath>");
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
                {
                    // Create output document 
                    using Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite);
                    using Document outDoc = Document.Create(outStream, inDoc.Conformance, null);
                    PageList outPages = outDoc.Pages;
                    int pageCount = 0;
                    ContentGenerator generator = null;
                    Page outPage = null;

                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Copy all pages from input document
                    foreach (Page inPage in inDoc.Pages)
                    {
                        if (pageCount == Nx * Ny)
                        {
                            // Add to output document
                            generator.Dispose();
                            outPages.Add(outPage);
                            outPage = null;
                            pageCount = 0;
                        }
                        if (outPage == null)
                        {
                            // Create a new output page
                            outPage = Page.Create(outDoc, PageSize);
                            generator = new ContentGenerator(outPage.Content, false);
                        }

                        // Get area where group has to be
                        int x = pageCount % Nx;
                        int y = Ny - (pageCount / Nx) - 1;

                        // Compute cell size
                        Size cellSize = new Size
                        {
                            Width = (PageSize.Width - ((Nx + 1) * Border)) / Nx,
                            Height = (PageSize.Height - ((Ny + 1) * Border)) / Ny
                        };

                        // Compute cell position
                        Point cellPosition = new Point
                        {
                            X = Border + x * (cellSize.Width + Border),
                            Y = Border + y * (cellSize.Height + Border)
                        };

                        // Define page copy options
                        PageCopyOptions copyOptions = new PageCopyOptions();

                        // Copy page as group from input to output
                        Group group = Group.CopyFromPage(outDoc, inPage, copyOptions);

                        // Compute group position 
                        Size groupSize = group.Size;
                        double scale = Math.Min(cellSize.Width / groupSize.Width,
                            cellSize.Height / groupSize.Height);

                        // Compute target size
                        Size targetSize = new Size
                        {
                            Width = groupSize.Width * scale,
                            Height = groupSize.Height * scale
                        };

                        // Compute position
                        Point targetPos = new Point
                        {
                            X = cellPosition.X + ((cellSize.Width - targetSize.Width) / 2),
                            Y = cellPosition.Y + ((cellSize.Height - targetSize.Height) / 2)
                        };

                        // Compute rectangle
                        Rectangle targetRect = new Rectangle
                        {
                            Left = targetPos.X,
                            Bottom = targetPos.Y,
                            Right = targetPos.X + targetSize.Width,
                            Top = targetPos.Y + targetSize.Height
                        };

                        // Add group to page
                        generator.PaintGroup(group, targetRect, null);
                        pageCount++;
                    }
                    // Add page
                    if (outPage != null)
                    {
                        generator.Dispose();
                        outPages.Add(outPage);
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