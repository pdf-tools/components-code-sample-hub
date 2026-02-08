/****************************************************************************
 *
 * File:            pdftoolsdecrypt.java
 *
 * Usage:           java pdftoolsdecrypt <password> <inputPath> <outputPath>
 *                  
 * Title:           Decrypt an encrypted PDF
 *                  
 * Description:     Remove encryption from a PDF.
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

package PdfToolsDecrypt;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.Document;
import com.pdftools.sign.*;

public class PdfToolsDecrypt
{
    static void usage() {
        System.out.println("Usage: java pdftoolsdecrypt <password> <inputPath> <outputPath>");
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

            // Decrypt a PDF document
            decrypt(args[0], args[1], args[2]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void decrypt(String password, String inPath, String outPath) throws Exception
    {
        try (
            // Use password to open encrypted input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr, password))
        {
            if (inDoc.getPermissions() == null)
                throw new Exception("Input file is not encrypted.");

            // Set encryption options
            OutputOptions outputOptions = new OutputOptions();

            // Set encryption parameters to no encryption
            outputOptions.setEncryption(null);

            // Allow removal of signatures. Otherwise the Encryption property is ignored for signed input documents
            // (see warning category WarningCategory.SIGNED_DOC_ENCRYPTION_UNCHANGED).
            outputOptions.setRemoveSignatures(SignatureRemoval.SIGNED);

            try(
                // Create output stream
                FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

                // Decrypt the document
                Document outDoc = new Signer().process(inDoc, outStr, outputOptions))
            {
            }
        }
    }
}
