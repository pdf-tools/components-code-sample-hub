/****************************************************************************
 *
 * File:            toolboxsetinfo.java
 *
 * Usage:           java toolboxsetinfo <inputPath> <key> <value> <outputPath>
 *                  Example: in.pdf key value out.pdf
 *                  
 * Title:           Add info entries to PDF
 *                  
 * Description:     Set metadata such as author, title, and creator of a PDF
 *                  document or add a custom entry.
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

package ToolboxSetInfo;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import java.time.OffsetDateTime;
import java.time.format.DateTimeFormatter;
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

public class ToolboxSetInfo {
    static void usage() {
        System.out.println("Usage: java toolboxsetinfo <inputPath> <key> <value> <outputPath>");
        System.out.println("       Example: in.pdf key value out.pdf");

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
            String outPath = args[3];
            String key = args[1];
            String value = args[2];

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

                    // Set info entry
                    Metadata metadata = Metadata.copy(outDoc, inDoc.getMetadata());
                    if (key.equals("Title"))
                        metadata.setTitle(value);
                    else if (key.equals("Author"))
                        metadata.setAuthor(value);
                    else if (key.equals("Subject"))
                        metadata.setSubject(value);
                    else if (key.equals("Keywords"))
                        metadata.setKeywords(value);
                    else if (key.equals("CreationDate")) {
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd' 'HH:mm:ssZ");
                        OffsetDateTime creationDate = OffsetDateTime.parse(value, formatter);
                        metadata.setCreationDate(creationDate);
                    } else if (key.equals("ModDate"))
                        throw new Exception("ModDate cannot be set.");
                    else if (key.equals("Creator"))
                        metadata.setCreator(value);
                    else if (key.equals("Producer"))
                        throw new Exception("Producer is set by means of the license key.");
                    else
                        metadata.getCustomEntries().put(key, value);
                    outDoc.setMetadata(metadata);
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