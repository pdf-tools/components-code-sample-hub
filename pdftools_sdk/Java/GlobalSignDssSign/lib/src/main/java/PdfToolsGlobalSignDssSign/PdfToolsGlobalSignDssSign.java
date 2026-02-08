/****************************************************************************
 *
 * File:            pdftoolsglobalsigndsssign.java
 *
 * Usage:           java pdftoolsglobalsigndsssign <commonName> <inputPath> <outputPath>
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

package PdfToolsGlobalSignDssSign;

import java.util.stream.Collectors;

import java.io.File;
import java.net.URI;

import com.pdftools.sys.FileStream;
import com.pdftools.HttpClientHandler;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.crypto.ValidationInformation;
import com.pdftools.crypto.providers.globalsigndss.Session;
import com.pdftools.crypto.providers.globalsigndss.SignatureConfiguration;
import com.pdftools.sign.Signer;

public class PdfToolsGlobalSignDssSign
{
    static void usage() {
        System.out.println("Usage: java pdftoolsglobalsigndsssign <commonName> <inputPath> <outputPath>");
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

            String commonName = args[0];
            String inPath = args[1];
            String outPath = args[2];

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
                // Sign a PDF document
                sign(session, commonName, inPath, outPath);
            }

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void sign(Session session, String commonName, String inPath, String outPath) throws Exception
    {
        // Create a signing certificate for an account with a dynamic identity
        // This can be re-used to sign multiple documents
        SignatureConfiguration signature = session.createSignatureForDynamicIdentity(String.format("{ \"subject_dn\" : { \"common_name\" : \"%s\" } }", commonName));

        // Embed validation information to enable the long term validation (LTV) of the signature (default)
        signature.setValidationInformation(ValidationInformation.EMBED_IN_DOCUMENT);

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
