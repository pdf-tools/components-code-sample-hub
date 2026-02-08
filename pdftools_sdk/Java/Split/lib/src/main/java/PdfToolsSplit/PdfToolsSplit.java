/****************************************************************************
 *
 * File:            pdftoolssplit.java
 *
 * Usage:           java pdftoolssplit <inputPath> <outputPath>
 *                  
 * Title:           Split a PDF
 *                  
 * Description:     Divide a PDF document into multiple PDF files.
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

package PdfToolsSplit;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.documentassembly.DocumentAssembler;
import com.pdftools.pdf.Document;

public class PdfToolsSplit
{
    static void usage() {
        System.out.println("Usage: java pdftoolssplit <inputPath> <outputPath>");
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

            split(args[0], args[1]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void split(String inPath, String outPathPrefix) throws Exception
    {
        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr)) {
            for (int i = 1; i <= inDoc.getPageCount(); ++i) {
                try (
                    // Create output stream for each page of the input document
                    FileStream outStream = new FileStream(outPathPrefix + "_page_" + i + ".pdf", FileStream.Mode.READ_WRITE_NEW);
                    DocumentAssembler docAssembler = new DocumentAssembler(outStream)) {
                    docAssembler.append(inDoc, i, i);
                    docAssembler.assemble();
                }
            }
        }
    }
}
