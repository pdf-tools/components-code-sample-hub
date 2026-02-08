/****************************************************************************
 *
 * File:            pdftoolsobfuscateebill.java
 *
 * Usage:           java pdftoolsobfuscateebill <inputPath> <outputPath>
 *                  
 * Title:           Obfuscate a PDF
 *                  
 * Description:     Obfuscate a PDF document for the eBill use case.
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

package PdfToolsObfuscateEBill;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.obfuscation.Processor;
import com.pdftools.obfuscation.profiles.EBill;

public class PdfToolsObfuscateEBill
{
    static void usage() {
        System.out.println("Usage: java pdftoolsobfuscateebill <inputPath> <outputPath>");
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

            Obfuscate(args[0], args[1]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void Obfuscate(String inPath, String outPath) throws Exception
    {
        // Configure eBill profile
        EBill profile = new EBill();
        profile.setRemoveUriLinks(true);
        profile.setObfuscateText(true);
        profile.setRemoveEmbeddedFiles(true);
        profile.setRemoveSignatureAppearances(true);

        // Open input document
        try (FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
             Document inDoc = Document.open(inStr, null);
             // Create output stream
             FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);
             // Process and create an output document
             Document outDoc = new Processor().processDocument(inDoc, outStr, profile))
        {
        }
    }
}
