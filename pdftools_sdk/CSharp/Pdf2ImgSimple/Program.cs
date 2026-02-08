/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsPdf2ImgSimple <inputPath> <outputPath>
 *                  
 * Title:           Convert PDF to image
 *                  
 * Description:     Convert a PDF to a rasterized image. In this example, the
 *                  conversion profile outputs the PDF as a TIFF image
 *                  suitable for archiving.
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
using PdfTools.Pdf2Image;
using Profiles = PdfTools.Pdf2Image.Profiles;

namespace PdfToolsPdf2ImgSimple
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsPdf2ImgSimple <inputPath> <outputPath>");
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

                Pdf2Image(args[0], args[1]);

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void Pdf2Image(string inPath, string outPath)
        {
            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create the profile that defines the conversion parameters.
            // The Archive profile converts PDF documents to TIFF images for archiving.
            var profile = new Profiles.Archive();

            // Optionally the profile's parameters can be changed according to the 
            // requirements of your conversion process.

            // Create output stream
            using var outStr = File.Create(outPath);

            // Convert the PDF document to an image document
            using var outDoc = new Converter().ConvertDocument(inDoc, outStr, profile);
        }
    }
}
