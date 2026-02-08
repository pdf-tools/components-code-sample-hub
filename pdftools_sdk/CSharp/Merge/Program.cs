/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsMerge <inputPath> [<inputPath2> ...] <outputPath>
 *                  
 * Title:           Merge PDFs
 *                  
 * Description:     Merge multiple PDF documents into a single file.
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
using PdfTools;

namespace PdfToolsMerge
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsMerge <inputPath> [<inputPath2> ...] <outputPath>");
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
                // By default, a test license key is active. In this case, a watermark is added to the output. 
                // If you have a license key, please uncomment the following call and set the license key.
                // Sdk.Initialize("LICENSE-KEY");

                Merge(args.Take(args.Length - 1), args.Last());
                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void Merge(IEnumerable<string> inPaths, string outPath)
        {
            // Create output stream
            using var outStream = File.Create(outPath);
            using var docAssembler = new PdfTools.DocumentAssembly.DocumentAssembler(outStream);

            foreach (var inPath in inPaths)
            {
                using var inStream = File.OpenRead(inPath);
                using var inDoc = PdfTools.Pdf.Document.Open(inStream);
                // Append the content of the input documents to the output document
                docAssembler.Append(inDoc);
            }

            // Merge input documents into an output document
            docAssembler.Assemble();
        }
    }
}
