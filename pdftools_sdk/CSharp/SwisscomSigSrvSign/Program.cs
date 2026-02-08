/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsSwisscomSigSrvSign <identity> <commonName> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF using the Swisscom Signing Service
 *                  
 * Description:     Add a document signature, also called an approval
 *                  signature. This signature verifies the integrity of the
 *                  signed part of the document and confirms the certificate
 *                  used for singing.
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
using SwisscomSigSrv = PdfTools.Crypto.Providers.SwisscomSigSrv;

namespace PdfToolsSwisscomSigSrvSign
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsSwisscomSigSrvSign <identity> <commonName> <inputPath> <outputPath>");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 4 || args.Length > 4)
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

                string identity = args[0];
                string commonName = args[1];
                string inPath = args[2];
                string outPath = args[3];

                // Configure the SSL client certificate to connect to the service
                var httpClientHandler = new HttpClientHandler();
                using (var sslClientCert = File.OpenRead(@"C:\path\to\clientcert.p12"))
                    httpClientHandler.SetClientCertificate(sslClientCert, "***insert password***");

                // Connect to the Swisscom Signing Service
                using var session = new SwisscomSigSrv.Session(new Uri("https://ais.swisscom.com"), httpClientHandler);

                // Sign a PDF document
                Sign(session, identity, commonName, inPath, outPath);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void Sign(SwisscomSigSrv.Session session, string identity, string commonName, string inPath, string outPath)
        {
            // Create a signing certificate for a static identity
            var signature = session.CreateSignatureForStaticIdentity(identity, commonName);

            // Embed validation information to enable the long term validation (LTV) of the signature (default)
            signature.EmbedValidationInformation = true;

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
