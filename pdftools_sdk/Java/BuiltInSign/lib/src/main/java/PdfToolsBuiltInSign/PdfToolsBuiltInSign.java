/****************************************************************************
 *
 * File:            pdftoolsbuiltinsign.java
 *
 * Usage:           java pdftoolsbuiltinsign <certificateFile> <password> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF using a software-based certificate file
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
 *                  The signing certificate is read from a password-protected
 *                  PKCS#12 file (.pfx or .p12).
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

package PdfToolsBuiltInSign;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.crypto.providers.builtin.*;
import com.pdftools.sign.Signer;

public class PdfToolsBuiltInSign
{
    static void usage() {
        System.out.println("Usage: java pdftoolsbuiltinsign <certificateFile> <password> <inputPath> <outputPath>");
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

            // Sign a PDF document
            sign(args[0], args[1], args[2], args[3]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void sign(String certificateFile, String password, String inPath, String outPath) throws Exception
    {
        try (
            // Create a session to the built-in cryptographic provider
            Provider session = new Provider();

            // Open certificate file
            FileStream pfxStr = new FileStream(certificateFile, FileStream.Mode.READ_ONLY))
        {
            // Create signature configuration from PFX (or P12) file
            SignatureConfiguration signature = session.createSignatureFromCertificate(pfxStr, password);

            // Embed validation information to enable the long term validation (LTV) of the signature (default)
            signature.setValidationInformation(com.pdftools.crypto.ValidationInformation.EMBED_IN_DOCUMENT);

            try (
                // Open input document
                FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStr);

                // Create a stream for the output file
                FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

                // Sign the input document
                Document outDoc = new Signer().sign(inDoc, signature, outStr))
            {
            }
        }
    }
}
