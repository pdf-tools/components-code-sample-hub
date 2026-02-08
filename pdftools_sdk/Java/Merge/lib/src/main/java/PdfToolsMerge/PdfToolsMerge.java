/****************************************************************************
 *
 * File:            pdftoolsmerge.java
 *
 * Usage:           java pdftoolsmerge <inputPath> [<inputPath2> ...] <outputPath>
 *                  
 * Title:           Merge PDFs
 *                  
 * Description:     Merge multiple PDF documents into a single file.
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

package PdfToolsMerge;

import java.util.stream.Collectors;

import java.io.File;
import java.util.Arrays;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.documentassembly.DocumentAssembler;
import com.pdftools.pdf.Document;

public class PdfToolsMerge
{
    static void usage() {
        System.out.println("Usage: java pdftoolsmerge <inputPath> [<inputPath2> ...] <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 2) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            merge(Arrays.copyOfRange(args, 0, args.length - 1), args[args.length - 1]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void merge(String[] inPaths, String outPath) throws Exception
    {
    	try (
            // Create output stream
            FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);
            DocumentAssembler docAssembler = new DocumentAssembler(outStream)) {
            for (String inPath : inPaths) {
	            try (
	                // Open input document
	                FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
	                Document inDoc = Document.open(inStr)) {
	                // Append the content of each input document to the output document
	                docAssembler.append(inDoc);
	            }
            }
            // Merge input documents into an output document
            docAssembler.assemble();
    	}
    }
}
