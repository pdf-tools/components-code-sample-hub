/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsVisualSignature <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF and add a visual appearance
 *                  
 * Description:     Add a document signature with a visual appearance.
 *                  The visual appearance is configured using an XML or JSON
 *                  file, allowing the addition of text, images, or PDFs.
 *                  
 *                  This signature consists of both a visible and a
 *                  non-visible part.
 *                  Only the non-visible part verifies the integrity of the
 *                  signed part of the document and authenticates the
 *                  signer's identity.
 *                  The signing certificate is read from a password-protected
 *                  PKCS#12 file (.pfx or .p12).
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
using BuiltIn = PdfTools.Crypto.Providers.BuiltIn;

namespace PdfToolsVisualSignature
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsVisualSignature <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>");
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

                // Sign a PDF document
                Sign(args[0], args[1], args[2], args[3], args[4]);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void Sign(string certificateFile, string password, string appConfigFile, string inPath, string outPath)
        {
            // Create a session to the built-in cryptographic provider
            using var session = new BuiltIn.Provider();

            // Open certificate file
            using var pfxStr = File.OpenRead(certificateFile);

            // Create signature configuration from PFX (or P12) file
            BuiltIn.SignatureConfiguration signature = session.CreateSignatureFromCertificate(pfxStr, password);

            // Create appearance from either an XML or a json file
            using var appStream = File.OpenRead(appConfigFile);
            if (Path.GetExtension(appConfigFile) == ".xml")
                signature.Appearance = Appearance.CreateFromXml(appStream);
            else
                signature.Appearance = Appearance.CreateFromJson(appStream);

            signature.Appearance.PageNumber = 1;
            signature.Appearance.CustomTextVariables.Add("company", "Daily Planet");

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
