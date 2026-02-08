/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsGlobalSignDssAddTimestamp <inputPath> <outputPath>
 *                  
 * Title:           Add a document time-stamp to a PDF using the GlobalSign
 *                  Digital Signing Service
 *                  
 * Description:     Add a trusted document time-stamp to a PDF and confirm
 *                  that the signed document has not been altered. This type
 *                  of signature proves that the document existed at a
 *                  specific time and ensures its integrity.
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
using GlobalSignDss = PdfTools.Crypto.Providers.GlobalSignDss;

namespace PdfToolsGlobalSignDssAddTimestamp
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsGlobalSignDssAddTimestamp <inputPath> <outputPath>");
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

                // Optional: Set your proxy configuration
                // Sdk.Proxy = new Uri("http://myproxy:8080");

                string inPath = args[0];
                string outPath = args[1];

                // Configure the SSL client certificate to connect to the service
                var httpClientHandler = new HttpClientHandler();
                using (var sslClientCert = File.OpenRead(@"C:\path\to\clientcert.cer"))
                    using (var sslClientKey = File.OpenRead(@"C:\path\to\privateKey.key"))
                    httpClientHandler.SetClientCertificateAndKey(sslClientCert, sslClientKey, "***insert password***");

                // Connect to the GlobalSign Digital Signing Service
                using var session = new GlobalSignDss.Session(new Uri("https://emea.api.dss.globalsign.com:8443"), "***insert api_key***", "***insert api_secret***", httpClientHandler);

                // Add a document time-stamp to a PDF
                AddTimestamp(session, inPath, outPath);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void AddTimestamp(GlobalSignDss.Session session, string inPath, string outPath)
        {
            // Create time-stamp configuration
            var timestamp = session.CreateTimestamp();

            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create stream for output file
            using var outStr = File.Create(outPath);

            // Add the document time-stamp
            using var outDoc = new Signer().AddTimestamp(inDoc, timestamp, outStr);
        }
    }
}
