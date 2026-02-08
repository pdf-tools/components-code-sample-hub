/****************************************************************************
 *
 * File:            pdftoolsglobalsigndssaddtimestamp.java
 *
 * Usage:           java pdftoolsglobalsigndssaddtimestamp <inputPath> <outputPath>
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

package PdfToolsGlobalSignDssAddTimestamp;

import java.util.stream.Collectors;

import java.net.URI;
import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.HttpClientHandler;
import com.pdftools.pdf.*;
import com.pdftools.crypto.providers.globalsigndss.*;
import com.pdftools.sign.Signer;

public class PdfToolsGlobalSignDssAddTimestamp
{
    static void usage() {
        System.out.println("Usage: java pdftoolsglobalsigndssaddtimestamp <inputPath> <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            // Optional: Set your proxy configuration
            // Sdk.setProxy(new URI("http://myproxy:8080"));

            String inPath = args[0];
            String outPath = args[1];

            // Configure the SSL client certificate to connect to the service
            HttpClientHandler httpClientHandler = new HttpClientHandler();
            try (
                 FileStream sslClientCert = new FileStream("C:/path/to/clientcert.cer", FileStream.Mode.READ_ONLY);
                 FileStream sslClientKey = new FileStream("C:/path/to/privateKey.key", FileStream.Mode.READ_ONLY))
            {
                httpClientHandler.setClientCertificateAndKey(sslClientCert, sslClientKey, "***insert password***");
            }

            // Connect to the GlobalSign Digital Signing Service
            try (Session session = new Session(new URI("https://emea.api.dss.globalsign.com:8443"),
                                               "***insert api_key***", "***insert api_secret***",
                                               httpClientHandler))
            {
                // Add a document time-stamp to a PDF
                addTimestamp(session, inPath, outPath);
            }

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void addTimestamp(Session session, String inPath, String outPath) throws Exception
    {
        // Create time-stamp configuration
        TimestampConfiguration timestamp = session.createTimestamp();

        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr);

            // Create output stream
            FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

            // Add the document time-stamp
            Document outDoc = new Signer().addTimestamp(inDoc, timestamp, outStr))
        {
        }
    }
}
