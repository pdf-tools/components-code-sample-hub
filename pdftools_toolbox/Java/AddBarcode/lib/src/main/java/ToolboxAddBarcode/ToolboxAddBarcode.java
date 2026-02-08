/****************************************************************************
 *
 * File:            toolboxaddbarcode.java
 *
 * Usage:           java toolboxaddbarcode <inputPath> <barcode> <fontfile> <outputPath>
 *                  Example: in.pdf \"PDF123\" free3of9.ttf out.pdf
 *                  
 * Title:           Add barcode to PDF
 *                  
 * Description:     Generate and add a barcode at a specified position on the
 *                  first page of a PDF document.
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

package ToolboxAddBarcode;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.sys.FileStream;

public class ToolboxAddBarcode {
    private static double Border = 20;

    static void usage() {
        System.out.println("Usage: java toolboxaddbarcode <inputPath> <barcode> <fontfile> <outputPath>");
        System.out.println("       Example: in.pdf \"PDF123\" free3of9.ttf out.pdf");

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
            String barcode = args[1];
            String fontPath = args[2];
            String outPath = args[3];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                // Create file stream
                FileStream fontStream = new FileStream(fontPath, FileStream.Mode.READ_ONLY);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Create embedded font in output document
                    Font font = Font.create(outDoc, fontStream, true);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy first page, add barcode, and append to output document
                    Page outPage = Page.copy(outDoc, inDoc.getPages().get(0), copyOptions);
                    addBarcode(outDoc, outPage, barcode, font, 50);
                    outDoc.getPages().add(outPage);

                    // Copy remaining pages and append to output document
                    PageList inPageRange = inDoc.getPages().subList(1, inDoc.getPages().size());
                    PageList copiedPages = PageList.copy(outDoc, inPageRange, copyOptions);
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

    private static void addBarcode(Document outputDoc, Page outPage, String barcode, Font font, double fontSize) throws ToolboxException, IOException {
        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {
            // Create text object
            Text barcodeText = Text.create(outputDoc);

            // Create a text generator
            TextGenerator textgenerator = new TextGenerator(barcodeText, font, fontSize, null);

            // Calculate position
            Point position = new Point(outPage.getSize().width - (textgenerator.getWidth(barcode) + Border),
                    outPage.getSize().height - (fontSize * (font.getAscent() + font.getDescent()) + Border));

            // Move to position
            textgenerator.moveTo(position);
            // Add given barcode string
            textgenerator.showLine(barcode);
            // Close text generator
            textgenerator.close();

            // Paint the positioned barcode text
            generator.paintText(barcodeText);
        }
    }
}
