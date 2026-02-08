/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsMultipleImg2Pdf <inputPath> [<inputPath2> ...] <outputPath>
 *                  
 * Title:           Convert multiple images to a PDF
 *                  
 * Description:     Convert a list of images into a single PDF. Supported
 *                  image types are TIFF, JPEG, BMP, GIF, PNG, JBIG2, and
 *                  JPEG2000.
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
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Profiles = PdfTools.Image2Pdf.Profiles;

namespace PdfToolsMultipleImg2Pdf
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsMultipleImg2Pdf <inputPath> [<inputPath2> ...] <outputPath>");
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

                Images2Pdf(args.Take(args.Length - 1), args.Last());

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void Images2Pdf(IEnumerable<string> inPaths, string outPath)
        {
            var streams = new List<FileStream>();
            var images = new DocumentList();
            try
            {
                // Open input images and store in list
                foreach (var inPath in inPaths)
                {
                    var stream = File.OpenRead(inPath);
                    streams.Add(stream);
                    images.Add(Document.Open(stream));
                }

                // Create the profile that defines the conversion parameters.
                var profile = new Profiles.Default();

                // Optionally the profile's parameters can be changed according to the 
                // requirements of your conversion process.

                // Create output stream
                using var outStream = File.Create(outPath);
                using var outPdf = new Converter().ConvertMultiple(images, outStream, profile);
            }
            finally
            {
                foreach (var image in images)
                    image.Dispose();
                foreach (var stream in streams)
                    stream.Dispose();
            }
        }
    }
}
