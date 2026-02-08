/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddLineNumbers <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Add line numbers to PDF
 *                  
 * Description:     Add a line number in front of each line that contains
 *                  text.
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
using System.Linq;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxAddLineNumbers
{
    class Program
    {
        private static readonly double distance = 10;
        private static readonly double fontSize = 8;
        private static uint lineNumber = 0;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddLineNumbers <inputPath> <outputPath>");
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
                Sdk.Initialize("LICENSE-KEY", null);
                string inPath = args[0];
                string outPath = args[1];

                // Open input document
                using Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read);
                using Document inDoc = Document.Open(inStream, null);

                // Create output document
                using Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite);
                using Document outDoc = Document.Create(outStream, inDoc.Conformance, null);
                // Copy document-wide data
                CopyDocumentData(inDoc, outDoc);

                // Create a font for the line numbers
                var lineNumberFont = Font.CreateFromSystem(outDoc, "Arial", null, true);

                // Define page copy options
                PageCopyOptions pageCopyOptions = new();

                // Copy all pages from input to output document
                var inPages = inDoc.Pages;
                var outPages = PageList.Copy(outDoc, inPages, pageCopyOptions);

                // Iterate over all input-output page pairs
                var pages = inPages.Zip(outPages);
                foreach (var pair in pages)
                    AddLineNumbers(outDoc, lineNumberFont, pair);

                // Add the finished pages to the output document's page list
                outDoc.Pages.AddRange(outPages);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void AddLineNumbers(Document outDoc, Font lineNumberFont, (Page first, Page second) pair)
        {
            // Add line numbers to all text found in the input page to the output page

            // The input and output page
            var inPage = pair.first;
            var outPage = pair.second;

            // Extract all text fragments
            var extractor = new ContentExtractor(inPage.Content)
            {
                Ungrouping = UngroupingSelection.All
            };

            // The left-most horizontal position of all text fragments
            double leftX = inPage.Size.Width;

            // A comparison for doubles that considers distances smaller than the font size as equal
            var comparison = new Comparison<double>(
                (a, b) =>
                {
                    var d = b - a;
                    if (Math.Abs(d) < fontSize)
                        return 0;
                    return Math.Sign(d);
                });

            // A container to hold the vertical positions of all text fragments, sorted and without duplicates
            SortedSet<double> lineYPositions = new(Comparer<double>.Create(comparison));

            // Iterate over all content elements of the input page
            foreach (var element in extractor)
            {
                // Process only text elements
                if (element is TextElement textElement)
                {
                    // Iterate over all text fragments
                    foreach (var fragment in textElement.Text)
                    {
                        // Get the fragments base line starting point
                        var point = fragment.Transform.TransformPoint(new Point { X = fragment.BoundingBox.Left, Y = 0 });

                        // Update the left-most position
                        leftX = Math.Min(leftX, point.X);

                        // Add the vertical position
                        lineYPositions.Add(point.Y);
                    }
                }
            }

            // If at least text fragment was found: add line numbers
            if (lineYPositions.Count > 0)
            {
                // Create a text object and use a text generator
                var text = Text.Create(outDoc);
                using (var textGenerator = new TextGenerator(text, lineNumberFont, fontSize, null))
                {
                    // Iterate over all vertical positions found in the input
                    foreach (var y in lineYPositions)
                    {
                        // The line number string
                        var lineNumberString = string.Format("{0}", ++lineNumber);

                        // The width of the line number string when shown on the page
                        var width = textGenerator.GetWidth(lineNumberString);

                        // Position line numbers right aligned
                        // with a given distance to the right-most horizontal position
                        // and at the vertical position of the current text fragment
                        textGenerator.MoveTo(new Point { X = leftX - width - distance, Y = y });

                        // Show the line number string
                        textGenerator.Show(lineNumberString);
                    }
                }

                // Use a content generator to paint the text onto the page
                using var contentGenerator = new ContentGenerator(outPage.Content, false);
                contentGenerator.PaintText(text);
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
