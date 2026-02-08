/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsDecrypt <password> <inputPath> <outputPath>
 *                  
 * Title:           Decrypt an encrypted PDF
 *                  
 * Description:     Remove encryption from a PDF.
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
using PdfTools.Pdf;
using System;
using System.IO;
using Sign = PdfTools.Sign;

namespace PdfToolsDecrypt
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsDecrypt <password> <inputPath> <outputPath>");
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

                // Decrypt a PDF document
                Decrypt(args[0], args[1], args[2]);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void Decrypt(string password, string inPath, string outPath)
        {
            // Use password to open encrypted input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr, password);

            if (inDoc.Permissions == null)
                throw new Exception("Input file is not encrypted.");

            // Create stream for output file
            using var outStr = File.Create(outPath);

            // Set encryption options
            var outputOptions = new Sign.OutputOptions()
            {
                // Set encryption parameters to no encryption
                Encryption = null,
                // Allow removal of signatures. Otherwise the Encryption property is ignored for signed input documents
                // (see warning category Sign.WarningCategory.SignedDocEncryptionUnchanged).
                RemoveSignatures = Sign.SignatureRemoval.Signed,
            };

            // Decrypt the document
            using var outDoc = new Sign.Signer().Process(inDoc, outStr, outputOptions);
        }
    }
}
