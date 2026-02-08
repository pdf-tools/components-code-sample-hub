/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxTextExtraction <inputPath>
 *                  Example: in.pdf
 *                  
 * Title:           Extract all text from PDF
 *                  
 * Description:     Write text from PDF page by page to console. Determine
 *                  heuristically if two text fragments belong to the same
 *                  word.
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

using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using System;
using System.IO;

namespace ToolboxTextExtraction
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxTextExtraction <inputPath>");
            Console.WriteLine("       Example: in.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 1 || args.Length > 1)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))
                {
                    int pageNumber = 1;

                    // Process each page
                    foreach (var inPage in inDoc.Pages)
                    {
                        Console.WriteLine("==========");
                        Console.WriteLine($"Page: {pageNumber++}");
                        Console.WriteLine("==========");

                        ContentExtractor extractor = new ContentExtractor(inPage.Content);
                        extractor.Ungrouping = UngroupingSelection.All;

                        // Iterate over all content elements and only process text elements
                        foreach (ContentElement element in extractor)
                            if (element is TextElement textElement)
                                WriteText(textElement.Text);
                    }
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        private static void WriteText(Text text)
        {
            string textPart = "";

            // Write all text fragments
            // Determine heuristically if there is a space between two text fragments
            for (int iFragment = 0; iFragment < text.Count; iFragment++)
            {

                TextFragment currFragment = text[iFragment];
                if (iFragment == 0)
                    textPart += currFragment.Text;
                else
                {
                    TextFragment lastFragment = text[iFragment - 1];
                    if (currFragment.CharacterSpacing != lastFragment.CharacterSpacing ||
                        currFragment.FontSize != lastFragment.FontSize ||
                        currFragment.HorizontalScaling != lastFragment.HorizontalScaling ||
                        currFragment.Rise != lastFragment.Rise ||
                        currFragment.WordSpacing != lastFragment.WordSpacing)
                        textPart += $" {currFragment.Text}";
                    else
                    {
                        Point currentBotLeft = currFragment.Transform.TransformRectangle(currFragment.BoundingBox).BottomLeft;
                        Point beforeBotRight = lastFragment.Transform.TransformRectangle(lastFragment.BoundingBox).BottomRight;

                        if (beforeBotRight.X < currentBotLeft.X - 0.7 * currFragment.FontSize ||
                            beforeBotRight.Y < currentBotLeft.Y - 0.1 * currFragment.FontSize ||
                            currentBotLeft.Y < beforeBotRight.Y - 0.1 * currFragment.FontSize)
                            textPart += $" {currFragment.Text}";
                        else
                            textPart += currFragment.Text;
                    }
                }
            }
            Console.WriteLine(textPart);
        }
    }
}