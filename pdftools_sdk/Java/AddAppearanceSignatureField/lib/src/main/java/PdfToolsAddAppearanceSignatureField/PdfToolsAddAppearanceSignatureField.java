/****************************************************************************
 *
 * File:            pdftoolsaddappearancesignaturefield.java
 *
 * Usage:           java pdftoolsaddappearancesignaturefield <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>
 *                  
 * Title:           Sign a PDF and apply a visual signature appearance
 *                  
 * Description:     Sign a PDF document using a provided certificate and
 *                  apply a visual signature appearance. This process
 *                  requires an input PDF that already contains a signature
 *                  field. The provided certificate is used to sign the
 *                  document and attach the signature to the existing field.
 *                  The visual appearance of the signature is updated using
 *                  an XML or JSON file, allowing the addition of text,
 *                  images, or PDFs. This signature consists of both a
 *                  visible and a non-visible part. Only the non-visible part
 *                  is used by other applications to verify the integrity of
 *                  the signed part of the document and validate the signing
 *                  certificate. The signing certificate is retrieved from a
 *                  password-protected PKCS#12 file (.pfx or .p12).
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

package PdfToolsAddAppearanceSignatureField;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.crypto.providers.builtin.*;
import com.pdftools.sign.Signer;
import com.pdftools.sign.Appearance;

public class PdfToolsAddAppearanceSignatureField
{
    static void usage() {
        System.out.println("Usage: java pdftoolsaddappearancesignaturefield <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>");
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
            FileStream pfxStr = new FileStream(certificateFile, FileStream.Mode.READ_ONLY);

            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr);)
        {
            // Create signature configuration from PFX (or P12) file
            SignatureConfiguration signature = session.createSignatureFromCertificate(pfxStr, password);

            // Choose first signature field
            for (int i = 0; i < inDoc.getSignatureFields().size(); i++) {
                if (inDoc.getSignatureFields().get(i) != null) {
                    signature.setFieldName(inDoc.getSignatureFields().get(i).getFieldName());
                    break;
                }
            }

            try (
               // Create appearance from either an XML or a json file
                FileStream appConfigStr = new FileStream(appConfigFile, FileStream.Mode.READ_ONLY))
            {
                if (appConfigFile.toLowerCase().endsWith(".xml"))
                    signature.setAppearance(Appearance.createFromXml(appConfigStr));
                else
                    signature.setAppearance(Appearance.createFromJson(appConfigStr));

                signature.getAppearance().getCustomTextVariables().put("company", "Daily Planet");

                try(
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
