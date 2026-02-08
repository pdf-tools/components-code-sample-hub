/****************************************************************************
 *
 * File:            toolboxstamppagenumber.java
 *
 * Usage:           java toolboxstamppagenumber <inputPath> <outputPath>
 *                  
 * Title:           Stamp page number to PDF
 *                  
 * Description:     Stamp the page number to the footer of each page of a PDF
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

package ToolboxStampPageNumber;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxStampPageNumber {
    static void usage() {
        System.out.println("Usage: java toolboxstamppagenumber <inputPath> <outputPath>");
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

            String inPath = args[0];
            String outPath = args[1];

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

                    // Copy pages from input to output
                    int pageNo = 1;

                    // Create embedded font in output document
                    Font font = Font.createFromSystem(outDoc, "Arial", "", true);

                    // Loop through all pages of input
                    for (Page inPage : inDoc.getPages()) {
                        // Copy page from input to output
                        Page outPage = Page.copy(outDoc, inPage, copyOptions);

                        // Stamp page number on current page of output document
                        applyStamps(outDoc, outPage, font, pageNo++);

                        // Add page to output document
                        outDoc.getPages().add(outPage);
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

        // Plain embedded files
        FileReferenceList outEmbeddedFiles = outDoc.getPlainEmbeddedFiles();
        for (FileReference inFileRef : inDoc.getPlainEmbeddedFiles())
            outEmbeddedFiles.add(FileReference.copy(outDoc, inFileRef));
    }

    private static void applyStamps(Document doc, Page page, Font font, int pageNo) throws ToolboxException, IOException {

        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(page.getContent(), false)) {
            // Create text object
            Text text = Text.create(doc);

            try (// Create a text generator with the given font, size and position
                TextGenerator textgenerator = new TextGenerator(text, font, 8, null)) {

                // Generate string to be stamped as page number
                String stampText = String.format("Page %d", pageNo);

                // Calculate position for centering text at bottom of page
                Point position = new Point((page.getSize().width / 2) - (textgenerator.getWidth(stampText) / 2), 10);

                // Position the text
                textgenerator.moveTo(position);
                // Add page number
                textgenerator.show(stampText);
            }

            // Paint the positioned text
            generator.paintText(text);
        }
    }
}