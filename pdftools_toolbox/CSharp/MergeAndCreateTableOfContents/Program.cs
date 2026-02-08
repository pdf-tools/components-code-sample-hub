/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxMergeAndCreateTableOfContents <inputPath> [<inputPath2> ...] <outputPath>
 *                  Example: in1.pdf in2.pdf out.pdf
 *                  
 * Title:           Merge multiple PDFs and create a table of contents page
 *                  
 * Description:     Merge several PDF documents to one and create a table of
 *                  contents page.
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
using System.Collections.Generic;
using System.IO;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxMergeAndCreateTableOfContents
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxMergeAndCreateTableOfContents <inputPath> [<inputPath2> ...] <outputPath>");
            Console.WriteLine("       Example: in1.pdf in2.pdf out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                // The last argument is the output file
                string outPath = args[^1];

                string[] inPaths = new string[args.Length - 1];
                Array.Copy(args, inPaths, args.Length - 1);

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, null, null))
                {
                    // Create embedded font in output document 
                    Font font = Font.CreateFromSystem(outDoc, "Arial", string.Empty, true);

                    // Define page copy options
                    PageCopyOptions pageCopyOptions = new PageCopyOptions();

                    var copiedPageLists = new List<Tuple<string, PageList>>(inPaths.Length);

                    // A page number counter
                    int pageNumber = 2;

                    // Copy all input documents pages
                    foreach (string inPath in inPaths)
                    {
                        // Open input document
                        using Stream inFs = new FileStream(inPath, FileMode.Open, FileAccess.Read);
                        using Document inDoc = Document.Open(inFs, null);

                        // Copy all pages and append to output document
                        PageList copiedPages = PageList.Copy(outDoc, inDoc.Pages, pageCopyOptions);

                        // Add page numbers to copied pages
                        foreach (var copiedPage in copiedPages)
                        {
                            AddPageNumber(outDoc, copiedPage, font, pageNumber++);
                        }

                        // Create outline item
                        string title = inDoc.Metadata.Title ?? System.IO.Path.GetFileNameWithoutExtension(inPath);
                        copiedPageLists.Add(new Tuple<string, PageList>(title, copiedPages));
                    }

                    // Create table of contents page
                    var contentsPage = CreateTableOfContents(outDoc, copiedPageLists);
                    AddPageNumber(outDoc, contentsPage, font, 1);

                    // Add pages to the output document
                    PageList outPages = outDoc.Pages;
                    outPages.Add(contentsPage);
                    foreach (var tuple in copiedPageLists)
                    {
                        outPages.AddRange(tuple.Item2);
                    }

                    Console.WriteLine("Execution successful.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void AddPageNumber(Document outDoc, Page copiedPage, Font font, int pageNumber)
        {
            // Create content generator
            using ContentGenerator generator = new ContentGenerator(copiedPage.Content, false);

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
                    X = (copiedPage.Size.Width / 2) - (textgenerator.GetWidth(stampText) / 2),
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

        private static Page CreateTableOfContents(Document outDoc, List<Tuple<string, PageList>> copiedPageLists)
        {
            // Create a new page with size equal to the first page copied
            var page = Page.Create(outDoc, copiedPageLists[0].Item2[0].Size);

            // Create a font
            var font = Font.CreateFromSystem(outDoc, "Arial", null, true);

            // Parameters for layout computation
            double border = 30;
            double textWidth = page.Size.Width - 2 * border;
            double chapterTitleSize = 24;
            double titleSize = 12;

            // The current text location
            var location = new Point() { X = border, Y = page.Size.Height - border - chapterTitleSize };

            // The page number of the current item in the table of content
            int pageNumber = 2;

            // Create a content generator for the table of contents page
            using (var contentGenerator = new ContentGenerator(page.Content, false))
            {
                // Create a text object
                var text = Text.Create(outDoc);

                // Create a text generator to generate the table of contents. Initially, use the chapter title font size
                using (var textGenerator = new TextGenerator(text, font, chapterTitleSize, location))
                {
                    // Show a chapter title
                    textGenerator.ShowLine("Table of Contents");

                    // Advance the vertical position
                    location.Y -= 1.7 * chapterTitleSize;

                    // Select the font size for an entry in the table of contents
                    textGenerator.FontSize = titleSize;

                    // Iterate over all copied page ranges
                    foreach (var tuple in copiedPageLists)
                    {
                        // The title string for the current entry
                        string title = tuple.Item1;

                        // The page number string of the target page for this entry
                        string pageNumberString = string.Format("{0}", pageNumber);

                        // The width of the page number string
                        double pageNumberWidth = textGenerator.GetWidth(pageNumberString);

                        // Compute the number of filler dots to be displayed between the entry title and the page number
                        int numberOfDots = (int)Math.Floor((textWidth - textGenerator.GetWidth(title) - pageNumberWidth) / textGenerator.GetWidth("."));

                        // Move to the current location and show the entry's title and the filler dots
                        textGenerator.MoveTo(location);
                        textGenerator.Show(title + new string('.', numberOfDots));

                        // Show the page number
                        textGenerator.MoveTo(new Point() { X = page.Size.Width - border - pageNumberWidth, Y = location.Y });
                        textGenerator.Show(pageNumberString);

                        // Compute the rectangle for the link
                        var linkRectangle = new Rectangle()
                        {
                            Left = border,
                            Bottom = location.Y + font.Descent * titleSize,
                            Right = border + textWidth,
                            Top = location.Y + font.Ascent * titleSize
                        };

                        // Create a destination to the first page of the current page range and create a link for this destination
                        var pageList = tuple.Item2;
                        var targetPage = pageList[0];
                        var destination = LocationZoomDestination.Create(outDoc, targetPage, 0, targetPage.Size.Height, null);
                        var link = InternalLink.Create(outDoc, linkRectangle, destination);

                        // Add the link to the table of contents page
                        page.Links.Add(link);

                        // Advance the location for the next entry
                        location.Y -= 1.8 * titleSize;
                        pageNumber += pageList.Count;
                    }
                }

                // Paint the generated text
                contentGenerator.PaintText(text);
            }

            // Return the finished table-of-contents page
            return page;
        }
    }
}