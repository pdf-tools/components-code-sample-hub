/****************************************************************************
 *
 * File:            toolboxaddvectorgraphics.java
 *
 * Usage:           java toolboxaddvectorgraphics <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Add vector graphic to PDF
 *                  
 * Description:     Draw a line on an existing PDF page.
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

package ToolboxAddVectorGraphics;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.geometry.real.Size;
import com.pdftools.toolbox.pdf.content.ColorSpace;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.content.ProcessColorSpaceType;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.content.Paint;
import com.pdftools.toolbox.pdf.content.Path;
import com.pdftools.toolbox.pdf.content.PathGenerator;
import com.pdftools.toolbox.pdf.content.Stroke;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxAddVectorGraphics {
    static void usage() {
        System.out.println("Usage: java toolboxaddvectorgraphics <inputPath> <outputPath>");
        System.out.println("       Example: in.pdf out.pdf");

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

                    // Copy all pages
                    for (Page inPage : inDoc.getPages()) {
                        // Copy page from input to output
                        Page outPage = Page.copy(outDoc, inPage, copyOptions);

                        // Add a line
                        addLine(outDoc, outPage);

                        // Add page to output document
                        outDoc.getPages().add(outPage);
                    }
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

    private static void addLine(Document document, Page outPage)
            throws ToolboxException, IOException {
        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {

            // Create a path
            Path path = new Path();
            try (// Create a path generator
                PathGenerator pathGenerator = new PathGenerator(path)) {
                // Draw a line diagonally across the page
                Size pageSize = outPage.getSize();
                pathGenerator.moveTo(new Point(10.0, 10.0));
                pathGenerator.lineTo(new Point(pageSize.width - 10.0, pageSize.height - 10.0));
            }

            // Create a RGB color space
            ColorSpace deviceRgbColorSpace = ColorSpace.createProcessColorSpace(document, ProcessColorSpaceType.RGB);

            // Create a red color
            double[] color = new double[] { 1.0, 0.0, 0.0 };

            // Create a paint
            Paint paint = Paint.create(document, deviceRgbColorSpace, color, null);

            // Create stroking parameters with given paint and line width
            Stroke stroke = new Stroke(paint, 10.0);

            // Draw the path onto the page
            generator.paintPath(path, null, stroke);
        }
    }
}