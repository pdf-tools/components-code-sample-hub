/****************************************************************************
 *
 * File:            pdftoolsvisualsignature.java
 *
 * Usage:           java pdftoolsvisualsignature <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF and add a visual appearance
 *                  
 * Description:     Add a document signature with a visual appearance.
 *                  The visual appearance is configured using an XML or JSON
 *                  file, allowing the addition of text, images, or PDFs.
 *                  
 *                  This signature consists of both a visible and a
 *                  non-visible part.
 *                  Only the non-visible part verifies the integrity of the
 *                  signed part of the document and authenticates the
 *                  signer's identity.
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

package PdfToolsVisualSignature;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.crypto.providers.builtin.*;
import com.pdftools.sign.Signer;
import com.pdftools.sign.Appearance;

public class PdfToolsVisualSignature
{
    static void usage() {
        System.out.println("Usage: java pdftoolsvisualsignature <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>");
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

            // Sign a PDF document
            sign(args[0], args[1], args[2], args[3], args[4]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void sign(String certificateFile, String password, String appConfigFile, String inPath, String outPath) throws Exception
    {
        try (
            // Create a session to the built-in cryptographic provider
            Provider session = new Provider();

            // Open certificate file
            FileStream pfxStr = new FileStream(certificateFile, FileStream.Mode.READ_ONLY))
        {
            // Create signature configuration from PFX (or P12) file
            SignatureConfiguration signature = session.createSignatureFromCertificate(pfxStr, password);

            try (
               // Create appearance from either an XML or a json file
                FileStream appConfigStr = new FileStream(appConfigFile, FileStream.Mode.READ_ONLY))
            {
                if (appConfigFile.toLowerCase().endsWith(".xml"))
                    signature.setAppearance(Appearance.createFromXml(appConfigStr));
                else
                    signature.setAppearance(Appearance.createFromJson(appConfigStr));

                signature.getAppearance().setPageNumber(1);
                signature.getAppearance().getCustomTextVariables().put("company", "Daily Planet");

                try(
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
}
