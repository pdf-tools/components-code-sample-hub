/****************************************************************************
 *
 * File:            pdftoolsswisscomsigsrvsign.java
 *
 * Usage:           java pdftoolsswisscomsigsrvsign <identity> <commonName> <inputPath> <outputPath>
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

package PdfToolsSwisscomSigSrvSign;

import java.util.stream.Collectors;

import java.io.File;
import java.net.URI;

import com.pdftools.sys.FileStream;
import com.pdftools.HttpClientHandler;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.crypto.providers.swisscomsigsrv.Session;
import com.pdftools.crypto.providers.swisscomsigsrv.SignatureConfiguration;
import com.pdftools.sign.Signer;

public class PdfToolsSwisscomSigSrvSign
{
    static void usage() {
        System.out.println("Usage: java pdftoolsswisscomsigsrvsign <identity> <commonName> <inputPath> <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 4 || args.length > 4) {
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
            String commonName = args[1];
            String inPath = args[2];
            String outPath = args[3];

            // Configure the SSL client certificate to connect to the service
            HttpClientHandler httpClientHandler = new HttpClientHandler();
            try (FileStream sslClientCert = new FileStream("C:/path/to/clientcert.p12", FileStream.Mode.READ_ONLY))
            {
                httpClientHandler.setClientCertificate(sslClientCert, "***insert password***");
            }

            // Connect to the Swisscom Signing Service
            try (Session session = new Session(new URI("https://ais.swisscom.com"), httpClientHandler))
            {
                // Sign a PDF document
                sign(session, identity, commonName, inPath, outPath);
            }

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void sign(Session session, String identity, String commonName, String inPath, String outPath) throws Exception
    {
        // Create a signing certificate for a static identity
        // This can be re-used to sign multiple documents
        SignatureConfiguration signature = session.createSignatureForStaticIdentity(identity, commonName);

        // Embed validation information to enable the long term validation (LTV) of the signature (default)
        signature.setEmbedValidationInformation(true);

        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr);

            // Create output stream
            FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

            // Sign the input document
            Document outDoc = new Signer().sign(inDoc, signature, outStr))
        {
        }
    }
}
