/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsAddAppearanceSignatureField <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF and apply a visual signature appearance
 *                  
 * Description:     Sign a PDF document using a provided certificate and
 *                  apply a visual signature appearance. This process
 *                  requires an input PDF that already contains a signature
 *                  field. The provided certificate is used to sign the
 *                  document and attach the signature to the existing field.
 *                  The visual appearance of the signature is updated using
 *                  an XML or JSON file, allowing the addition of text,
 *                  images, or PDFs. This signature consists of both a
 *                  visible and a non-visible part. Only the non-visible part
 *                  is used by other applications to verify the integrity of
 *                  the signed part of the document and validate the signing
 *                  certificate. The signing certificate is retrieved from a
 *                  password-protected PKCS#12 file (.pfx or .p12).
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

namespace PdfToolsAddAppearanceSignatureField
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsAddAppearanceSignatureField <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>");
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
                AddAppearanceSignatureField(args[0], args[1], args[2], args[3], args[4]);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void AddAppearanceSignatureField(string certificateFile, string password, string appConfigFile, string inPath, string outPath)
        {
            // Create a session to the built-in cryptographic provider
            using var session = new PdfTools.Crypto.Providers.BuiltIn.Provider();

            // Create signature configuration from PFX (or P12) file
            using var pfxStr = File.OpenRead(certificateFile);
            var signature = session.CreateSignatureFromCertificate(pfxStr, password);

            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Choose first signature field
            foreach (var field in inDoc.SignatureFields)
            {
                if (field != null)
                {
                    signature.FieldName = field.FieldName;
                    break;
                }
            }

            // Create stream for output file
            using var outStr = File.Create(outPath);

            // Create appearance from either an XML or a json file
            using var appStream = File.OpenRead(appConfigFile);
            if (Path.GetExtension(appConfigFile) == ".xml")
                signature.Appearance = Appearance.CreateFromXml(appStream);
            else
                signature.Appearance = Appearance.CreateFromJson(appStream);

            signature.Appearance.CustomTextVariables.Add("company", "Daily Planet");

            // Sign the input document
            using var outDoc = new Signer().Sign(inDoc, signature, outStr);
        }
    }
}
