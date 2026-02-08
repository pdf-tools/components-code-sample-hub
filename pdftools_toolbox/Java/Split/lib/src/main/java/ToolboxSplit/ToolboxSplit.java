/****************************************************************************
 *
 * File:            toolboxsplit.java
 *
 * Usage:           java toolboxsplit <inputPath> <firstPage> <lastPage> <outputPath>
 *                  
 * Title:           Remove pages from PDF
 *                  
 * Description:     Selectively remove pages from a PDF document.
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

package ToolboxSplit;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.sys.FileStream;

public class ToolboxSplit {
    static void usage() {
        System.out.println("Usage: java toolboxsplit <inputPath> <firstPage> <lastPage> <outputPath>");
    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 4 || args.length > 4) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inPath = args[0];
            int startIndex = Integer.parseInt(args[1]) - 1;
            int endIndex = Integer.parseInt(args[2]);
            String outPath = args[3];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null)) {
                // Get pages from input document
                PageList inPages = inDoc.getPages();

                // Correct and check page indices
                startIndex = Math.max(Math.min(inPages.size() - 1, startIndex), 0);
                endIndex = Math.max(Math.min(inPages.size(), endIndex), 0);
                if (startIndex >= endIndex) {
                    System.out.println("lastPage must be greater or equal to firstPage");
                    return;
                }
                try (
                    FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                    try (// Create output document
                        Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                        // Copy document-wide data
                        copyDocumentData(inDoc, outDoc);

                        // Define page copy options
                        PageCopyOptions copyOptions = new PageCopyOptions();

                        // Get page range from input pages
                        PageList inPageRange = inPages.subList(startIndex, endIndex);

                        // Copy page range and append to output document
                        PageList outPageRange = PageList.copy(outDoc, inPageRange, copyOptions);
                        outDoc.getPages().addAll(outPageRange);
                    }
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    private static void copyDocumentData(Document inDoc, Document outDoc) throws ToolboxException, IOException {
        // Copy document-wide data

        // Output intent
        if (inDoc.getOutputIntent() != null)
            outDoc.setOutputIntent(IccBasedColorSpace.copy(outDoc, inDoc.getOutputIntent()));

        // Metadata
        outDoc.setMetadata(Metadata.copy(outDoc, inDoc.getMetadata()));

        // Viewer settings
        outDoc.setViewerSettings(ViewerSettings.copy(outDoc, inDoc.getViewerSettings()));

        // Associated files (for PDF/A-3 and PDF 2.0 only)
        FileReferenceList outAssociatedFiles = outDoc.getAssociatedFiles();
        for (FileReference inFileRef : inDoc.getAssociatedFiles())
            outAssociatedFiles.add(FileReference.copy(outDoc, inFileRef));

        // Plain mbedded files
        FileReferenceList outEmbeddedFiles = outDoc.getPlainEmbeddedFiles();
        for (FileReference inFileRef : inDoc.getPlainEmbeddedFiles())
            outEmbeddedFiles.add(FileReference.copy(outDoc, inFileRef));
    }
}