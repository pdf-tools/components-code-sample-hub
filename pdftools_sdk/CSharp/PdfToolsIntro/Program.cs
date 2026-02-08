/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsPdfToolsIntro <coverImage> <contentPdfPath> <outputPath>
 *                  
 * Title:           Hello, Pdftools SDK!
 *                  
 * Description:     Add a cover page from an image to a PDF.
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

using PdfTools.Image2Pdf;
using System;
using System.IO;
using Profiles = PdfTools.Image2Pdf.Profiles;

namespace PdfToolsPdfToolsIntro
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsPdfToolsIntro <coverImage> <contentPdfPath> <outputPath>");
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

                var imageCoverPath = args[0];
                var contentPath = args[1];
                var outputPdfPath = args[2];

                using var imageCoverStream = new MemoryStream();
                Image2Pdf(imageCoverPath, imageCoverStream);

                using var inputPdfStream = File.OpenRead(contentPath);

                // Merge the cover page with the content document
                Merge(imageCoverStream, inputPdfStream, outputPdfPath);

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void Image2Pdf(string inPath, MemoryStream imageStream)
        {
            // Open image document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = PdfTools.Image.Document.Open(inStr);

            // Create the profile that defines the conversion parameters.
            // The Default profile converts images to PDF documents.
            var profile = new Profiles.Default();

            // Optionally, the profile's parameters can be changed according to the 
            // requirements of your conversion process.

            // Convert the image to a PDF document
            var outDoc = new Converter().Convert(inDoc, imageStream, profile);
        }

        private static void Merge(MemoryStream coverStream, FileStream inputContentStream, string outPath)
        {
            // Create output stream
            using var outStream = File.Create(outPath);
            using var docAssembler = new PdfTools.DocumentAssembly.DocumentAssembler(outStream);

            docAssembler.Append(PdfTools.Pdf.Document.Open(coverStream), 1, 1);
            docAssembler.Append(PdfTools.Pdf.Document.Open(inputContentStream));

            // Merge input documents into an output document
            docAssembler.Assemble();
        }
    }
}
