/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsImg2PdfAccessibility <inputPath> <alternateText> <outputPath>
 *                  
 * Title:           Convert an image to an accessible PDF/A document
 *                  
 * Description:     Convert an image to an accessible PDF/A-2a document.
 *                  Alternative text is added to the image, as required for
 *                  PDF/A level A, to ensure accessibility for people with
 *                  disabilities who use assistive technologies.
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

using PdfTools;
using PdfTools.Image;
using PdfTools.Image2Pdf;
using System;
using System.IO;
using Conformance = PdfTools.Pdf.Conformance;
using Profiles = PdfTools.Image2Pdf.Profiles;

namespace PdfToolsImg2PdfAccessibility
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsImg2PdfAccessibility <inputPath> <alternateText> <outputPath>");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 3 || args.Length > 3)
            {
                Usage();
                return;
            }

            try
            {
                // By default, a test license key is active. In this case, a watermark is added to the output. 
                // If you have a license key, please uncomment the following call and set the license key.
                // Sdk.Initialize("LICENSE-KEY");

                Image2Pdf(args[0], args[1], args[2]);

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void Image2Pdf(string inPath, string alternateText, string outPath)
        {
            // Open image document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create the profile that defines the conversion parameters.
            // The Archive profile converts images to PDF/A documents for archiving.
            var profile = new Profiles.Archive();

            // Set conformance of output document to PDF/A-2a
            profile.Conformance = new Conformance(2, Conformance.PdfALevel.A);

            // For PDF/A level A, an alternate text is required for each page of the image.
            // This is optional for other PDF/A levels, e.g. PDF/A-2b.
            profile.Language = "en";
            profile.AlternateText.Add(alternateText);

            // Optionally other profile parameters can be changed according to the 
            // requirements of your conversion process.

            // Create output stream
            using var outStr = File.Create(outPath);

            // Convert the image to a tagged PDF/A document
            using var outDoc = new Converter().Convert(inDoc, outStr, profile);
        }
    }
}
