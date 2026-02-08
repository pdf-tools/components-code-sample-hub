/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsValidateSimple <inputPath>
 *                  
 * Title:           Validate PDF conformance
 *                  
 * Description:     Assess whether a PDF document adheres to specific
 *                  standards and conformance levels.
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
using PdfTools.PdfA.Validation;

namespace PdfToolsValidateSimple
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsValidateSimple <inputPath>");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 1 || args.Length > 1)
            {
                Usage();
                return;
            }

            try
            {
                // By default, a test license key is active. In this case, a watermark is added to the output. 
                // If you have a license key, please uncomment the following call and set the license key.
                // Sdk.Initialize("LICENSE-KEY");

                var result = Validate(args[0]);

                // Report the validation result
                if (result.IsConforming)
                    Console.WriteLine($"Document conforms to {result.Conformance}.");
                else
                    Console.WriteLine($"Document does not conform to {result.Conformance}.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static ValidationResult Validate(string inPath)
        {
            // Open the document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create a validator object that writes all validation error messages to the console
            var validator = new Validator();
            validator.Error += (s, e) => Console.WriteLine("- {0}: {1} ({2}{3})", e.Category, e.Message, e.Context, e.PageNo > 0 ? " on page" + e.PageNo : "");

            // Validate the standard conformance of the document
            return validator.Validate(inDoc);
        }
    }
}
