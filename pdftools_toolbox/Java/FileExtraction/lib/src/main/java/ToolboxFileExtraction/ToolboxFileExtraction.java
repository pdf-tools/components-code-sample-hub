/****************************************************************************
 *
 * File:            toolboxfileextraction.java
 *
 * Usage:           java toolboxfileextraction <inputPath> <outputDir>
 *                  Example: in.pdf dir/subdir/
 *                  
 * Title:           Extract files embedded from a PDF
 *                  
 * Description:     Extract the embedded files contained in the PDF to the
 *                  file system.
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

package ToolboxFileExtraction;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.sys.FileStream.Mode;

public class ToolboxFileExtraction {
    static void usage() {
        System.out.println("Usage: java toolboxfileextraction <inputPath> <outputDir>");
        System.out.println("       Example: in.pdf dir/subdir/");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inputFile = args[0];
            String outputDir = args[1];

            try (// Open input document
                FileStream inStream = new FileStream(inputFile, Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                )
            {
                FileReferenceList frList = inDoc.getAllEmbeddedFiles();

                for(FileReference fr: frList)
                {
                    extractFile(fr, outputDir);
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    
    private static void extractFile(FileReference fr, String outputDir) throws Exception
    {
        try(
            FileStream outStream = new FileStream(outputDir + "/" + fr.getName(), Mode.READ_WRITE_NEW);
            )
        {
            outStream.copy(fr.getData());
        }
    }
}