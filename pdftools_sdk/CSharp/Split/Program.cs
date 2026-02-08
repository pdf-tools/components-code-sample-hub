/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsSplit <inputPath> <outputPath>
 *                  
 * Title:           Split a PDF
 *                  
 * Description:     Divide a PDF document into multiple PDF files.
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
using PdfTools;

namespace PdfToolsSplit
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsSplit <inputPath> <outputPath>");
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

                Split(args[0], args[1]);
                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void Split(string inPath, string outPathPrefix)
        {
            // Open input document
            using var inStream = File.OpenRead(inPath);
            using var inDoc = PdfTools.Pdf.Document.Open(inStream);

            // Split the input document page by page
            for (int i = 1; i <= inDoc.PageCount; ++i)
            {
                using var outStream = File.Create(outPathPrefix + "_page_" + i + ".pdf");
                using var docAssembler = new PdfTools.DocumentAssembly.DocumentAssembler(outStream);
                docAssembler.Append(inDoc, i, i);
                docAssembler.Assemble();
            }
        }
    }
}
