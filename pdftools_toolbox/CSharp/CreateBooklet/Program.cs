/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxCreateBooklet <inputPath> <outputPath>
 *                  
 * Title:           Create a booklet from PDF
 *                  
 * Description:     Place up to two A4 pages in the right order on an A3
 *                  page, so that duplex printing and folding the A3 pages
 *                  results in a booklet.
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

namespace CreateBooklet
{
    class Program
    {
        // A3 portrait
        private static readonly Size PageSize = new Size() { Width = 1190, Height = 842 };
        private static readonly double Border = 10;
        private static readonly double CellWidth = (PageSize.Width - 3 * Border) / 2;
        private static readonly double CellHeight = PageSize.Height - 2 * Border;
        private static readonly double CellLeft = Border;
        private static readonly double CellRight = 2 * Border + CellWidth;
        private static readonly double CellYPos = Border;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxCreateBooklet <inputPath> <outputPath>");
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

                    // Create a font
                    Font font = Font.CreateFromSystem(outDoc, "Arial", "Italic", true);

                    // Copy pages
                    PageList inPages = inDoc.Pages;
                    PageList outPages = outDoc.Pages;
                    int numberOfSheets = (inPages.Count + 3) / 4;

                    for (int sheetNumber = 0; sheetNumber < numberOfSheets; ++sheetNumber)
                    {

                        // Add on front side
                        CreateBooklet(inPages, outDoc, outPages, 4 * numberOfSheets - 2 * sheetNumber - 1,
                            2 * sheetNumber, font);

                        // Add on back side
                        CreateBooklet(inPages, outDoc, outPages, 2 * sheetNumber + 1,
                            4 * numberOfSheets - 2 * sheetNumber - 2, font);
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

        private static void CreateBooklet(PageList inPages, Document outDoc, PageList outPages, int leftPageIndex,
            int rightPageIndex, Font font)
        {
            // Define page copy options
            PageCopyOptions copyOptions = new PageCopyOptions();

            // Create page object
            Page outpage = Page.Create(outDoc, PageSize);

            // Create content generator
            using (ContentGenerator generator = new ContentGenerator(outpage.Content, false))
            {
                // Left page 
                if (leftPageIndex < inPages.Count)
                {
                    // Copy page from input to output
                    Page leftPage = inPages[leftPageIndex];
                    Group leftGroup = Group.CopyFromPage(outDoc, leftPage, copyOptions);

                    // Paint group on the calculated rectangle
                    generator.PaintGroup(leftGroup, ComputTargetRect(leftGroup.Size, true), null);

                    // Add page number to page
                    StampPageNumber(outDoc, font, generator, leftPageIndex + 1, true);
                }

                // Right page
                if (rightPageIndex < inPages.Count)
                {
                    // Copy page from input to output
                    Page rigthPage = inPages[rightPageIndex];
                    Group rightGroup = Group.CopyFromPage(outDoc, rigthPage, copyOptions);

                    // Paint group on the calculated rectangle
                    generator.PaintGroup(rightGroup, ComputTargetRect(rightGroup.Size, false), null);

                    // Add page number to page
                    StampPageNumber(outDoc, font, generator, rightPageIndex + 1, false);
                }
            }
            // Add page to output document
            outPages.Add(outpage);
        }

        private static Rectangle ComputTargetRect(Size bbox, bool isLeftPage)
        {
            // Calculate factor for fitting page into rectangle
            double scale = Math.Min(CellWidth / bbox.Width, CellHeight / bbox.Height);
            double groupWidth = bbox.Width * scale;
            double groupHeight = bbox.Height * scale;

            // Calculate x-value
            double groupXPos = isLeftPage ? CellLeft + (CellWidth - groupWidth) / 2 :
                                            CellRight + (CellWidth - groupWidth) / 2;

            // Calculate y-value
            double groupYPos = CellYPos + (CellHeight - groupHeight) / 2;

            // Calculate rectangle
            return new Rectangle
            {
                Left = groupXPos,
                Bottom = groupYPos,
                Right = groupXPos + groupWidth,
                Top = groupYPos + groupHeight
            };
        }

        private static void StampPageNumber(Document document, Font font, ContentGenerator generator,
            int PageNo, bool isLeftPage)
        {
            // Create text object
            Text text = Text.Create(document);

            // Create text generator
            using (TextGenerator textgenerator = new TextGenerator(text, font, 8, null))
            {
                string stampText = string.Format("Page {0}", PageNo);

                // Get width of stamp text
                double width = textgenerator.GetWidth(stampText);

                // Calculate position
                double x = isLeftPage ? Border + 0.5 * CellWidth - width / 2 :
                                        2 * Border + 1.5 * CellWidth - width / 2;
                double y = Border;

                // Move to position
                textgenerator.MoveTo(new Point { X = x, Y = y});

                // Add page number
                textgenerator.Show(stampText);
            }
            // Paint the positioned text
            generator.PaintText(text);
        }
    }
}