/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsAddSignatureField <inputPath> <outputPath>
 *                  
 * Title:           Add a signature field to a PDF
 *                  
 * Description:     Add an unsigned signature field that can be signed in
 *                  another application.
 *                  The signature field indicates that the document requires
 *                  a signature and defines the page and position
 *                  where the signature's visual appearance will be placed.
 *                  This is especially useful for forms and contracts
 *                  with designated signature spaces. The signature visual
 *                  appearance is irrelevant to the signature validation
 *                  process and only serves as a visual cue for the user.
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
using PdfTools.Geometry.Units;
using PdfTools.Pdf;
using PdfTools.Sign;
using System;
using System.IO;

namespace PdfToolsAddSignatureField
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsAddSignatureField <inputPath> <outputPath>");
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

                // Add a signature field to a PDF document
                AddSignatureField(args[0], args[1]);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void AddSignatureField(string inPath, string outPath)
        {
            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create empty field appearance that is 6cm by 3cm in size
            var appearance = Appearance.CreateFieldBoundingBox(Size.cm(6, 3));

            // Add field to last page of document
            appearance.PageNumber = inDoc.PageCount;

            // Position field
            appearance.Bottom = Length.cm(3);
            appearance.Left = Length.cm(6.5);

            // Create a signature field configuration
            var field = new SignatureFieldOptions(appearance);

            // Create stream for output file
            using var outStr = File.Create(outPath);

            // Sign the input document
            using var outDoc = new Signer().AddSignatureField(inDoc, field, outStr);
        }
    }
}
