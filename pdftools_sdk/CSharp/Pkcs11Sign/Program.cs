/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsPkcs11Sign <pkcs11Library> <password> <certificate> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF using a PKCS#11 device
 *                  
 * Description:     Add a document signature, sometimes called an approval
 *                  signature.
 *                  This type of signature verifies the integrity of the
 *                  signed part of the document and authenticates the
 *                  signer's identity.
 *                  
 *                  Validation information is embedded to enable the
 *                  long-term validation (LTV) of the signature.
 *                  
 *                  The signing certificate is stored on a cryptographic
 *                  device with PKCS#11 middleware (driver).
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
using PdfTools.Sign;
using System;
using System.IO;
using Pkcs11 = PdfTools.Crypto.Providers.Pkcs11;

namespace PdfToolsPkcs11Sign
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsPkcs11Sign <pkcs11Library> <password> <certificate> <inputPath> <outputPath>");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 5 || args.Length > 5)
            {
                Usage();
                return;
            }

            try
            {
                // By default, a test license key is active. In this case, a watermark is added to the output. 
                // If you have a license key, please uncomment the following call and set the license key.
                // Sdk.Initialize("LICENSE-KEY");

                string pkcs11Library = args[0];
                string password = args[1];
                string certificate = args[2];
                string inPath = args[3];
                string outPath = args[4];

                // Load the PKCS#11 driver module (middleware)
                // The module can only be loaded once in the application.
                using var module = Pkcs11.Module.Load(pkcs11Library);

                // Create a session to the cryptographic device and log in
                // with the password (pin)
                // Use Devices[i] if you have more than one device installed instead of Devices.GetSingle()
                using var session = module.Devices.GetSingle().CreateSession(password);

                // Sign a PDF document
                Sign(session, certificate, inPath, outPath);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void Sign(Pkcs11.Session session, string certificate, string inPath, string outPath)
        {
            // Create the signature configuration
            // This can be re-used to sign multiple documents
            var signature = session.CreateSignatureFromName(certificate);

            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create stream for output file
            using var outStr = File.Create(outPath);

            // Sign the input document
            using var outDoc = new Signer().Sign(inDoc, signature, outStr);
        }
    }
}
