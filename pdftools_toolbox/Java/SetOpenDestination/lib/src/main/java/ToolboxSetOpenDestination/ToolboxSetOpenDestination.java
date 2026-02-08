/****************************************************************************
 *
 * File:            toolboxsetopendestination.java
 *
 * Usage:           java toolboxsetopendestination <inputPath> <pageNumber> <outputPath>
 *                  Example: in.pdf 2 out.pdf
 *                  
 * Title:           Set the open-destination of a PDF
 *                  
 * Description:     Set the page that is displayed when opening the document.
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

package ToolboxSetOpenDestination;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.navigation.LocationZoomDestination;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxSetOpenDestination {
    static void usage() {
        System.out.println("Usage: java toolboxsetopendestination <inputPath> <pageNumber> <outputPath>");
        System.out.println("       Example: in.pdf 2 out.pdf");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 3 || args.length > 3) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inPath = args[0];
            String outPath = args[2];
            int destinationPageNumber = Integer.parseInt(args[1]);

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                    // Check given page number
                    if (destinationPageNumber < 1 || destinationPageNumber > inDoc.getPages().size()) {
                        System.out.println("Given pageNumber is invalid.");
                        return;
                    }

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages and append to output document
                    PageList copiedPages = PageList.copy(outDoc, inDoc.getPages(), copyOptions);
                    outDoc.getPages().addAll(copiedPages);

                    // Add open destination
                    Page outPage = outDoc.getPages().get(destinationPageNumber - 1);
                    LocationZoomDestination destination = LocationZoomDestination.create(outDoc, outPage, 0.0, outPage.getSize().getHeight(), null); 
                    outDoc.setOpenDestination(destination);
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