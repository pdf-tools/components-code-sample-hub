/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsImg2PdfDefault <inputPath> <outputPath>
 *                  
 * Title:           Convert image to PDF
 *                  
 * Description:     Convert an image to a PDF. The default settings for this
 *                  conversion profile place each image on a separate A4
 *                  portrait page with a 2 cm margin.
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
using Profiles = PdfTools.Image2Pdf.Profiles;

namespace PdfToolsImg2PdfDefault
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsImg2PdfDefault <inputPath> <outputPath>");
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

                Image2Pdf(args[0], args[1]);

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void Image2Pdf(string inPath, string outPath)
        {
            // Open image document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create the profile that defines the conversion parameters.
            // The Default profile converts images to PDF documents.
            var profile = new Profiles.Default();

            // Optionally, the profile's parameters can be changed according to the 
            // requirements of your conversion process.

            // Create output stream
            using var outStr = File.Create(outPath);

            // Convert the image to a PDF document
            using var outDoc = new Converter().Convert(inDoc, outStr, profile);
        }
    }
}
