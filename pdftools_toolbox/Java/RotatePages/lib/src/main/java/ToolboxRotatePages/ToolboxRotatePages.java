/****************************************************************************
 *
 * File:            toolboxrotatepages.java
 *
 * Usage:           java toolboxrotatepages <pageNumber> [<pageNumber2> ...] <inputPath> <outputPath>
 *                  Example: 2 4  in.pdf out.pdf
 *                  
 * Title:           Set page orientation
 *                  
 * Description:     Rotate a specified page of a PDF document by 90 degrees.
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

package ToolboxRotatePages;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.geometry.Rotation;

public class ToolboxRotatePages {
    static void usage() {
        System.out.println("Usage: java toolboxrotatepages <pageNumber> [<pageNumber2> ...] <inputPath> <outputPath>");
        System.out.println("       Example: 2 4  in.pdf out.pdf");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 3) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            int[] pageNumbers = new int[args.length - 2];
            for (int i = 0; i < args.length - 2; i++) {
                pageNumbers[i] = Integer.parseInt(args[i]);
            }

            String inPath = args[args.length - 2];
            String outPath = args[args.length - 1];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Set copy options and flatten annotations, form fields and signatures
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages
                    PageList copiedPages = PageList.copy(outDoc, inDoc.getPages(), copyOptions);

                    // Rotate selected pages by 90 degrees
                    for (int pageNumber : pageNumbers) {
                        copiedPages.get(pageNumber - 1).rotate(Rotation.CLOCKWISE); 
                    }

                    // Add pages to output document
                    outDoc.getPages().addAll(copiedPages);
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

        // Plain embedded files
        FileReferenceList outEmbeddedFiles = outDoc.getPlainEmbeddedFiles();
        for (FileReference inFileRef : inDoc.getPlainEmbeddedFiles())
            outEmbeddedFiles.add(FileReference.copy(outDoc, inFileRef));
    }
}