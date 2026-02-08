/****************************************************************************
 *
 * File:            toolboxencrypt.java
 *
 * Usage:           java toolboxencrypt <inputPath> <UserPassword> <OwnerPassword> <outputPath>
 *                  
 * Title:           Encrypt PDF
 *                  
 * Description:     Encrypt a PDF document with a user password and an owner
 *                  password. When opening the document, either of the
 *                  passwords must be provided. If providing the user
 *                  password, the document can be viewed and printed only.
 *                  Providing the owner password grants full access to the
 *                  document.
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

package ToolboxEncrypt;

import java.util.stream.Collectors;

import java.util.EnumSet;
import java.io.File;
import java.io.IOException;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.Encryption;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.Permission;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxEncrypt {
    static void usage() {
        System.out.println("Usage: java toolboxencrypt <inputPath> <UserPassword> <OwnerPassword> <outputPath>");
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
            String userPwd = args[1];
            String ownerPwd = args[2];
            String outPath = args[3];

            // Create encryption parameters
            Encryption encryptionParams = new Encryption(userPwd, ownerPwd,
                    EnumSet.of(Permission.PRINT, Permission.DIGITAL_PRINT));

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document and set a user and owner password
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), encryptionParams)) {

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages and append to output document
                    PageList copiedPages = PageList.copy(outDoc, inDoc.getPages(), copyOptions);
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