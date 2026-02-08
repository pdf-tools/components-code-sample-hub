/****************************************************************************
 *
 * File:            pdftoolspkcs11sign.java
 *
 * Usage:           java pdftoolspkcs11sign <pkcs11Library> <password> <certificate> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF using a PKCS#11 device
 *                  
 * Description:     Add a document signature, sometimes called an approval
 *                  signature.
 *                  This type of signature verifies the integrity of the
 *                  signed part of the document and authenticates the
 *                  signer's identity.
 *                  
 *                  Validation information is embedded to enable the
 *                  long-term validation (LTV) of the signature.
 *                  
 *                  The signing certificate is stored on a cryptographic
 *                  device with PKCS#11 middleware (driver).
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

package PdfToolsPkcs11Sign;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.crypto.providers.pkcs11.Module;
import com.pdftools.crypto.providers.pkcs11.Session;
import com.pdftools.crypto.providers.pkcs11.SignatureConfiguration;
import com.pdftools.sign.Signer;

public class PdfToolsPkcs11Sign
{
    static void usage() {
        System.out.println("Usage: java pdftoolspkcs11sign <pkcs11Library> <password> <certificate> <inputPath> <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 5 || args.length > 5) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            String pkcs11Library = args[0];
            String password = args[1];
            String certificate = args[2];
            String inPath = args[3];
            String outPath = args[4];

            try (
                // Load the PKCS#11 driver module (middleware)
                // The module can only be loaded once in the application.
                Module module = Module.load(pkcs11Library);

                // Create a session to the cryptographic device and log in
                // with the password (pin)
                Session session = module.getDevices().getSingle().createSession(password))
            {
                // Sign a PDF document
                sign(session, certificate, inPath, outPath);
            }

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void sign(Session session, String certificate, String inPath, String outPath) throws Exception
    {
        // Create the signature configuration
        // This can be re-used to sign multiple documents
        SignatureConfiguration signature = session.createSignatureFromName(certificate);

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
