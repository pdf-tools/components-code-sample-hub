/****************************************************************************
 *
 * File:            pdftoolsswisscomsigsrvaddtimestamp.java
 *
 * Usage:           java pdftoolsswisscomsigsrvaddtimestamp <identity> <inputPath> <outputPath>
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

package PdfToolsSwisscomSigSrvAddTimestamp;

import java.util.stream.Collectors;

import java.net.URI;
import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.HttpClientHandler;
import com.pdftools.pdf.*;
import com.pdftools.crypto.providers.swisscomsigsrv.*;
import com.pdftools.sign.Signer;

public class PdfToolsSwisscomSigSrvAddTimestamp
{
    static void usage() {
        System.out.println("Usage: java pdftoolsswisscomsigsrvaddtimestamp <identity> <inputPath> <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 3 || args.length > 3) {
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

            String identity = args[0];
            String inPath = args[1];
            String outPath = args[2];

            // Configure the SSL client certificate to connect to the service
            HttpClientHandler httpClientHandler = new HttpClientHandler();
            try (FileStream sslClientCert = new FileStream("C:/path/to/clientcert.p12", FileStream.Mode.READ_ONLY))
            {
                httpClientHandler.setClientCertificate(sslClientCert, "***insert password***");
            }

            // Connect to the Swisscom Signing Service
            try (Session session = new Session(new URI("https://ais.swisscom.com"), httpClientHandler))
            {
                // Add a document time-stamp to a PDF
                addTimestamp(session, identity, inPath, outPath);
            }

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void addTimestamp(Session session, String identity, String inPath, String outPath) throws Exception
    {
        // Create time-stamp configuration
        TimestampConfiguration timestamp = session.createTimestamp(identity);

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
