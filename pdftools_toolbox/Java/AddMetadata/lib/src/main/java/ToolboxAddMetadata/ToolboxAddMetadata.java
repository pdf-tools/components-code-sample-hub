/****************************************************************************
 *
 * File:            toolboxaddmetadata.java
 *
 * Usage:           java toolboxaddmetadata <inputPath> <outputPath> [<mdatafile>]
 *                  Example: in.pdf out.pdf MetadataTest.xmp
 *                  
 * Title:           Add metadata to PDF
 *                  
 * Description:     Set metadata such as author, title, and creator of a PDF
 *                  document. Optionally use the metadata of another PDF
 *                  document or the content of an XMP file.
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

package ToolboxAddMetadata;

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

public class ToolboxAddMetadata {
    static void usage() {
        System.out.println("Usage: java toolboxaddmetadata <inputPath> <outputPath> [<mdatafile>]");
        System.out.println("       Example: in.pdf out.pdf MetadataTest.xmp");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 2 || args.length > 3) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inPath = args[0];
            String outPath = args[1];

            String mdatafile = null;
            if (args.length == 3) {
                mdatafile = args[2];
            }

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages and append to output document
                    PageList copiedPages = PageList.copy(outDoc, inDoc.getPages(), copyOptions);
                    outDoc.getPages().addAll(copiedPages);

                    if (args.length == 3) {
                        Metadata mdata;

                        // Add metadata from a input file
                        try (
                        	FileStream metaStream = new FileStream(mdatafile, FileStream.Mode.READ_ONLY)) {

	                        if (mdatafile.toLowerCase().endsWith(".pdf")) {
	                            // Use the metadata of another PDF file
	                            try (
	                            	Document metaDoc = Document.open(metaStream, null)) {

	                            	mdata = Metadata.copy(outDoc, metaDoc.getMetadata());
	                            }
	                        } else {
	                            // Use the content of an XMP metadata file
	                            mdata = Metadata.create(outDoc, metaStream);
	                        }
                        }
                        outDoc.setMetadata(mdata);
                    } else {
                        // Set some metadata properties
                        Metadata metadata = outDoc.getMetadata();
                        metadata.setAuthor("Your Author");
                        metadata.setTitle("Your Title");
                        metadata.setSubject("Your Subject");
                        metadata.setCreator("Your Creator");
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
        // Copy document-wide data (excluding metadata)

        // Output intent
        if (inDoc.getOutputIntent() != null)
            outDoc.setOutputIntent(IccBasedColorSpace.copy(outDoc, inDoc.getOutputIntent()));

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