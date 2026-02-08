/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsExtractTextLayout <inputPath> <outputDir>
 *                  
 * Title:           Extract text mimicking layout
 *                  
 * Description:     Extracting text from a PDF page by page into text files,
 *                  preserving the original layout by adding whitespaces to
 *                  the monospace text.
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
using PdfTools.Pdf;
using PdfTools.Extraction;
using PdfTools.Geometry.Units;

namespace PdfToolsExtractTextLayout
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsExtractTextLayout <inputPath> <outputDir>");
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
                // By default, a test license key is active. In this case, a watermark is added to the output. 
                // If you have a license key, please uncomment the following call and set the license key.
                // Sdk.Initialize("LICENSE-KEY");

                ExtractText(args[0], args[1]);
                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void ExtractText(string inPath, string outDir)
        {
            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create directory if not exists
            if (!Directory.Exists(outDir))
            {
                Directory.CreateDirectory(outDir);
            }

            var options = new TextOptions();
            options.ExtractionFormat = TextExtractionFormat.Monospace;
            options.AdvanceWidth = Length.Parse("9.2pt");

            // Extract text page per page from the document
            Extractor extractor = new Extractor();
            for (int i = 0; i < inDoc.PageCount; i++)
            {
                using var outStr = File.Create(Path.Combine(outDir, $"page{i + 1}.txt"));
                extractor.ExtractText(inDoc, outStr, options, i + 1, i + 1);
            }
        }
    }
}
