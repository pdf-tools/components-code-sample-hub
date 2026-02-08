/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsGlobalSignDssSign <commonName> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF using the GlobalSign Digital Signing Service
 *                  
 * Description:     Add a document signature, sometimes called an approval
 *                  signature.
 *                  This type of signature verifies that the signed document
 *                  has not been altered and authenticates the signer's
 *                  identity.
 *                  
 *                  Validation information is embedded to enable the
 *                  long-term validation (LTV) of the signature.
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
using System.Text.Json;
using GlobalSignDss = PdfTools.Crypto.Providers.GlobalSignDss;

namespace PdfToolsGlobalSignDssSign
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsGlobalSignDssSign <commonName> <inputPath> <outputPath>");
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

                // Optional: Set your proxy configuration
                // Sdk.Proxy = new Uri("http://myproxy:8080");

                string commonName = args[0];
                string inPath = args[1];
                string outPath = args[2];

                // Configure the SSL client certificate to connect to the service
                var httpClientHandler = new HttpClientHandler();
                using (var sslClientCert = File.OpenRead(@"C:\path\to\clientcert.cer"))
                    using (var sslClientKey = File.OpenRead(@"C:\path\to\privateKey.key"))
                    httpClientHandler.SetClientCertificateAndKey(sslClientCert, sslClientKey, "***insert password***");

                // Connect to the GlobalSign Digital Signing Service
                using var session = new GlobalSignDss.Session(new Uri("https://emea.api.dss.globalsign.com:8443"), "***insert api_key***", "***insert api_secret***", httpClientHandler);

                // Sign a PDF document
                Sign(session, commonName, inPath, outPath);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void Sign(GlobalSignDss.Session session, string commonName, string inPath, string outPath)
        {
            // Create a signing certificate for an account with a dynamic identity
            var identity = JsonSerializer.Serialize(new { subject_dn = new { common_name = commonName } });
            var signature = session.CreateSignatureForDynamicIdentity(identity);

            // Embed validation information to enable the long term validation (LTV) of the signature (default)
            signature.ValidationInformation = PdfTools.Crypto.ValidationInformation.EmbedInDocument;

            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create stream for output file
            using var outStr = File.Create(outPath);

            // Sign the document
            using var outDoc = new Signer().Sign(inDoc, signature, outStr);
        }
    }
}
