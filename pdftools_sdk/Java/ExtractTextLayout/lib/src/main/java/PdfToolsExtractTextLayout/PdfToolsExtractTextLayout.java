/****************************************************************************
 *
 * File:            pdftoolsextracttextlayout.java
 *
 * Usage:           java pdftoolsextracttextlayout <inputPath> <outputDir>
 *                  
 * Title:           Extract text mimicking layout
 *                  
 * Description:     Extracting text from a PDF page by page into text files,
 *                  preserving the original layout by adding whitespaces to
 *                  the monospace text.
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

package PdfToolsExtractTextLayout;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.pdf.Document;
import com.pdftools.extraction.Extractor;
import com.pdftools.extraction.TextOptions;
import com.pdftools.extraction.TextExtractionFormat;
import com.pdftools.geometry.units.Length;

public class PdfToolsExtractTextLayout
{
    static void usage() {
        System.out.println("Usage: java pdftoolsextracttextlayout <inputPath> <outputDir>");
    }

    public static void main(String[] args) 
    {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        try {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            extractText(args[0], args[1]);
            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void extractText(String inPath, String outDir) throws Exception {
        // Open input document
        try (
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr)
        ) {
            // Create directory if it does not exist
            File dir = new File(outDir);
            if (!dir.exists()) {
                dir.mkdirs();
            }

            // Set text extraction options
            TextOptions options = new TextOptions();
            options.setExtractionFormat(TextExtractionFormat.MONOSPACE);
            options.setAdvanceWidth(Length.parse("9.2pt"));

            // Extract text page by page from the document
            Extractor extractor = new Extractor();
            for (int i = 0; i < inDoc.getPageCount(); i++) {
                try (
                    FileStream outStr = new FileStream(outDir + File.separator + "page" + (i + 1) + ".txt", FileStream.Mode.READ_WRITE_NEW)
                ) {
                    extractor.extractText(inDoc, outStr, options, i + 1, i + 1);
                }
            }
        }
    }
}
