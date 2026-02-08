/****************************************************************************
 *
 * File:            toolboxadddatamatrix.java
 *
 * Usage:           java toolboxadddatamatrix <inputPath> <imagePath> <outputPath>
 *                  Example: in.pdf in.png out.pdf
 *                  
 * Title:           Add data matrix to PDF
 *                  
 * Description:     Add a two-dimensional barcode from an existing image on
 *                  the first page of a PDF document.
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

package ToolboxAddDataMatrix;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Rectangle;
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

public class ToolboxAddDataMatrix {
    // Define border
    private static double Border = 40;

    static void usage() {
        System.out.println("Usage: java toolboxadddatamatrix <inputPath> <imagePath> <outputPath>");
        System.out.println("       Example: in.pdf in.png out.pdf");

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
            String datamatrixPath = args[1];
            String outPath = args[2];

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

                    // Copy first page, add data matrix image, and append to output document
                    Page outPage = Page.copy(outDoc, inDoc.getPages().get(0), copyOptions);
                    addDatamatrix(outDoc, outPage, datamatrixPath);
                    outDoc.getPages().add(outPage);

                    // Copy remaining pages and append to output document
                    PageList inPageRange = inDoc.getPages().subList(1, inDoc.getPages().size());
                    PageList copiedPages = PageList.copy(outDoc, inPageRange, copyOptions);
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

    private static void addDatamatrix(Document document, Page page, String datamatrixPath)
            throws ToolboxException, IOException {
        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(page.getContent(), false);
            // Import data matrix
            FileStream inMatrix = new FileStream(datamatrixPath, FileStream.Mode.READ_ONLY)) {

            // Create image object for data matrix
            Image datamatrix = Image.create(document, inMatrix);

            // Data matrix size
            double datamatrixSize = 85;

            // Calculate Rectangle for data matrix
            Rectangle rect = new Rectangle(Border, page.getSize().height - (datamatrixSize + Border),
                    datamatrixSize + Border, page.getSize().height - Border);

            // Paint image of data matrix into the specified rectangle
            generator.paintImage(datamatrix, rect);
        }
    }
}