/****************************************************************************
 *
 * File:            toolboxaddimage.java
 *
 * Usage:           java toolboxaddimage <inputPath> <imagePath> <pageNumber> <outputPath>
 *                  Example: in.pdf in.png 1 out.pdf
 *                  
 * Title:           Add image to PDF
 *                  
 * Description:     Place an image with a specified size at a specific
 *                  location of a page.
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

package ToolboxAddImage;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.geometry.integer.Size;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.content.Image;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;

public class ToolboxAddImage {
    static void usage() {
        System.out.println("Usage: java toolboxaddimage <inputPath> <imagePath> <pageNumber> <outputPath>");
        System.out.println("       Example: in.pdf in.png 1 out.pdf");

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
            String imagePath = args[1];
            int pageNumber = Integer.parseInt(args[2]);
            String outPath = args[3];

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

                    // Copy pages preceding selected page and append to output document
                    PageList inPageRange = inDoc.getPages().subList(0, pageNumber - 1);
                    PageList copiedPages = PageList.copy(outDoc, inPageRange, copyOptions);
                    outDoc.getPages().addAll(copiedPages);

                    // Copy selected page, add image, and append to output document
                    Page outPage = Page.copy(outDoc, inDoc.getPages().get(pageNumber - 1), copyOptions);
                    addImage(outDoc, outPage, imagePath, 150, 150);
                    outDoc.getPages().add(outPage);

                    // Copy remaining pages and append to output document
                    inPageRange = inDoc.getPages().subList(pageNumber, inDoc.getPages().size());
                    copiedPages = PageList.copy(outDoc, inPageRange, copyOptions);
                    outDoc.getPages().addAll(copiedPages);
                }
            }

            System.out.println("Execution successful");
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

    private static void addImage(Document document, Page outPage, String imagePath, double x, double y)
            throws ToolboxException, IOException {
        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(outPage.getContent(), false);
            // Load image from input path
            FileStream inImage = new FileStream(imagePath, FileStream.Mode.READ_ONLY)) {
            // Create image object
            Image image = Image.create(document, inImage);

            double resolution = 150;

            // Calculate rectangle for image
            Size size = image.getSize();
            Rectangle rect = new Rectangle(x, y, x + size.getWidth() * 72 / resolution,
                    y + size.getHeight() * 72 / resolution);

            // Paint image into the specified rectangle
            generator.paintImage(image, rect);
        }
    }
}