/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsOptimizerSimple <inputPath> <outputPath>
 *                  
 * Title:           Optimize a PDF
 *                  
 * Description:     Optimize a PDF with the "Web" optimization profile.
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
using PdfTools.Pdf;
using PdfTools.Optimization;
using Profiles = PdfTools.Optimization.Profiles;

namespace PdfToolsOptimizeSimple
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsOptimizerSimple <inputPath> <outputPath>");
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

                Optimize(args[0], args[1]);

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void Optimize(string inPath, string outPath)
        {
            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create the profile that defines the optimization parameters.
            // The Web profile is used to optimize documents for electronic document exchange.
            var profile = new Profiles.Web();

            // Optionally the profile's parameters can be changed according to the 
            // requirements of your optimization process.

            // Create output stream
            using var outStr = File.Create(outPath);

            // Optimize the document
            using var outDoc = new Optimizer().OptimizeDocument(inDoc, outStr, profile);
        }
    }
}
