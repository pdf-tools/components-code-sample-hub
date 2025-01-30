/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsEncrypt <password> <inputPath> <outputPath>
 *                  
 * Title:           Encrypt a PDF
 *                  
 * Description:     Encrypt a PDF document with a user password.
 *                  To open the document, the user password is required.
 *                  
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2025 PDF Tools AG, Switzerland
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

namespace PdfToolsEncrypt
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsEncrypt <password> <inputPath> <outputPath>");
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
                // Sdk.Initialize("<PDFSDK,V1,MGAASQD6L2JMQHL54PK08RQX8GG4SS0M8DAHVPH0VMP3NB8R9DUK>");

                // Encrypt a PDF document
                Encrypt(args[0], args[1], args[2]);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void Encrypt(string password, string inPath, string outPath)
        {
            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create stream for output file
            using var outStr = File.Create(outPath);

            // Set encryption options
            var outputOptions = new Sign.OutputOptions()
            {
                // Set a user password that will be required to open the document.
                // Note that this will remove PDF/A conformance of input files (see warning category Sign.WarningCategory.PdfARemoved)
                Encryption = new Encryption(password, null, Permission.All),
                // Allow removal of signatures. Otherwise the Encryption property is ignored for signed input documents
                // (see warning category Sign.WarningCategory.SignedDocEncryptionUnchanged).
                RemoveSignatures = Sign.SignatureRemoval.Signed,
            };

            // Encrypt the document
            using var outDoc = new Sign.Signer().Process(inDoc, outStr, outputOptions);
        }
    }
}
