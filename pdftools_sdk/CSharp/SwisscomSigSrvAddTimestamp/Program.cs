/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsSwisscomSigSrvAddTimestamp <identity> <inputPath> <outputPath>
 *                  
 * Title:           Add a document time-stamp to a PDF using the Swisscom
 *                  Signing Service
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
using SwisscomSigSrv = PdfTools.Crypto.Providers.SwisscomSigSrv;

namespace PdfToolsSwisscomSigSrvAddTimestamp
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsSwisscomSigSrvAddTimestamp <identity> <inputPath> <outputPath>");
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

                string identity = args[0];
                string inPath = args[1];
                string outPath = args[2];

                // Configure the SSL client certificate to connect to the service
                var httpClientHandler = new HttpClientHandler();
                using (var sslClientCert = File.OpenRead(@"C:\path\to\clientcert.p12"))
                    httpClientHandler.SetClientCertificate(sslClientCert, "***insert password***");

                // Connect to the Swisscom Signing Service
                using var session = new SwisscomSigSrv.Session(new Uri("https://ais.swisscom.com"), httpClientHandler);

                // Add a document time-stamp to a PDF
                AddTimestamp(session, identity, inPath, outPath);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void AddTimestamp(SwisscomSigSrv.Session session, string identity, string inPath, string outPath)
        {
            // Create time-stamp configuration
            var timestamp = session.CreateTimestamp(identity);

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
