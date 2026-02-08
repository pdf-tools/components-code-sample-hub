/****************************************************************************
 *
 * File:            toolboxmergepdf.java
 *
 * Usage:           java toolboxmergepdf <inputPath> [<inputPath2> ...] <outputPath>
 *                  Example: in1.pdf in2.pdf out.pdf
 *                  
 * Title:           Merge multiple PDFs
 *                  
 * Description:     Merge several PDF documents to one.
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

package ToolboxMergePdf;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;

public class ToolboxMergePdf {
    static void usage() {
        System.out.println("Usage: java toolboxmergepdf <inputPath> [<inputPath2> ...] <outputPath>");
        System.out.println("       Example: in1.pdf in2.pdf out.pdf");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 2) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String outPath = args[args.length - 1];

            String[] inPath = new String[args.length - 1];
            for (int i = 0; i < args.length - 1; i++) {
                inPath[i] = args[i];
            }

            try (
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, null, null)) {

                    // Configure page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Get output pages
                    PageList outPages = outDoc.getPages();

                    // Merge input document
                    for (int i = 0; i < args.length - 1; i++) {
                        try (// Open input document
                            FileStream inStream = new FileStream(inPath[i], FileStream.Mode.READ_ONLY);
                            Document inDoc = Document.open(inStream, null)) {

                            // Copy all pages and append to output document
                            PageList copiedPages = PageList.copy(outDoc, inDoc.getPages(), copyOptions);
                            outPages.addAll(copiedPages);
                        }
                    }
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
}