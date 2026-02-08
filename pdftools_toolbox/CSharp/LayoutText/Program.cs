/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxLayoutText <textPath> <outputPath>
 *                  
 * Title:           Layout text on PDF page
 *                  
 * Description:     Create a new PDF document with one page. On this page,
 *                  within a given rectangular area, add a text block with a
 *                  full justification layout.
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
using System.Text;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;


namespace ToolboxLayoutText
{
    class Program
    {
        private static readonly double Border = 50;
        private static readonly Size PageSize = new Size() { Width = 595, Height = 842 };

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxLayoutText <textPath> <outputPath>");
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

                string textPath = args[0];
                string outPath = args[1];

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.CreateNew, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, null, null))
                {
                    Font font = Font.CreateFromSystem(outDoc, "Arial", "Italic", true);

                    // Create page
                    Page outPage = Page.Create(outDoc, PageSize);

                    // Add text as justified text
                    LayoutText(outDoc, outPage, textPath, font, 20);

                    // Add page to document
                    outDoc.Pages.Add(outPage);
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void LayoutText(Document outputDoc, Page outPage, string textPath, Font font,
            double fontSize)
        {
            // Create content generator 
            using ContentGenerator gen = new ContentGenerator(outPage.Content, false);

            // Create text object
            Text text = Text.Create(outputDoc);

            // Create text generator
            using TextGenerator textGenerator = new TextGenerator(text, font, fontSize, null);

            // Calculate position
            Point position = new Point
            {
                X = Border,
                Y = outPage.Size.Height - Border
            };

            // Move to position
            textGenerator.MoveTo(position);

            // Loop through all lines of the textinput
            string[] lines = File.ReadAllLines(textPath, Encoding.Default);
            foreach (string line in lines)
            {
                // Split string in substrings
                string[] substrings = line.Split(new char[] { ' ' }, StringSplitOptions.None);
                string currentLine = null;
                double maxWidth = outPage.Size.Width - Border * 2;
                int wordcount = 0;

                // Loop through all words of input strings
                foreach (string word in substrings)
                {
                    string tempLine;

                    // Concatenate substrings to line
                    if (currentLine != null)
                        tempLine = currentLine + " " + word;
                    else
                        tempLine = word;

                    // Calculate the current width of line
                    double width = textGenerator.GetWidth(currentLine);
                    if (textGenerator.GetWidth(tempLine) > maxWidth)
                    {
                        // Calculate the word spacing
                        textGenerator.WordSpacing = (maxWidth - width) / (wordcount - 1);
                        // Paint on new line
                        textGenerator.ShowLine(currentLine);
                        textGenerator.WordSpacing = 0;
                        currentLine = word;
                        wordcount = 1;
                    }
                    else
                    {
                        currentLine = tempLine;
                        wordcount++;
                    }
                }
                textGenerator.WordSpacing = 0;
                // Add given stamp string
                textGenerator.ShowLine(currentLine);
            }
            // Paint the positioned text
            gen.PaintText(text);
        }
    }
}