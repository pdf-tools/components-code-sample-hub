/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsFlattenAnnotations <inputPath> <outputPath>
 *                  
 * Title:           Flatten annotations
 *                  
 * Description:     Optimize a PDF document by flattening the annotations of
 *                  the PDF. As a result, the annotations are converted to
 *                  static content.
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

namespace PdfToolsFlattenAnnotations
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsFlattenAnnotations <inputPath> <outputPath>");
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

                FlattenAnnotations(args[0], args[1]);

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void FlattenAnnotations(string inPath, string outPath)
        {
            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create the profile that defines the optimization parameters.
            // The MinimalFileSize profile is used to to produce a minimal file size
            var profile = new Profiles.MinimalFileSize();

            // Optionally the profile's parameters can be changed according to the 
            // requirements of your optimization process.
            profile.RemovalOptions.Annotations = ConversionStrategy.Flatten;
            profile.RemovalOptions.FormFields = ConversionStrategy.Flatten;
            profile.RemovalOptions.Links = ConversionStrategy.Flatten;

            // Create output stream
            using var outStr = File.Create(outPath);

            // Optimize the document
            using var outDoc = new Optimizer().OptimizeDocument(inDoc, outStr, profile);
        }
    }
}
