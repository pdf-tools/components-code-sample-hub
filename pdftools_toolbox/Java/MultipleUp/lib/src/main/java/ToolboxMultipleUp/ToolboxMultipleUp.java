/****************************************************************************
 *
 * File:            toolboxmultipleup.java
 *
 * Usage:           java toolboxmultipleup <inputPath> <outputPath>
 *                  
 * Title:           Place multiple pages on one page
 *                  
 * Description:     Place four pages of a PDF document on a single page.
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

package ToolboxMultipleUp;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.geometry.real.Size;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.content.Group;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;

public class ToolboxMultipleUp {
    // Put 4 pages on 1
    private static final int Nx = 2;
    private static final int Ny = 2;

    private static final double Border = 10;

    static void usage() {
        System.out.println("Usage: java toolboxmultipleup <inputPath> <outputPath>");
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
                Document inDoc = Document.open(inStream, null)) {
                try (
                    FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                    try (// Create output document
                        Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {
                        PageList outPages = outDoc.getPages();
                        int pageCount = 0;
                        ContentGenerator generator = null;
                        Page outPage = null;

                        // A4 portrait
                        Size pageSize = new Size(595, 842);

                        // Copy document-wide data
                        copyDocumentData(inDoc, outDoc);

                        // Copy pages
                        for (Page inPage : inDoc.getPages()) {

                            if (pageCount == Nx * Ny) {
                                // Add to output document
                                generator.close();
                                outPages.add(outPage);
                                outPage = null;
                                pageCount = 0;
                            }
                            if (outPage == null) {
                                // Create a new output page
                                outPage = Page.create(outDoc, pageSize);
                                generator = new ContentGenerator(outPage.getContent(), false);
                            }

                            // Get area where group has to be
                            int x = pageCount % Nx;
                            int y = Ny - (pageCount / Nx) - 1;

                            // Calculate cell size
                            Size cellSize = new Size((pageSize.width - ((Nx + 1) * Border)) / Nx,
                                    (pageSize.height - ((Ny + 1) * Border)) / Ny);

                            // Calculate cell position
                            Point cellPosition = new Point(Border + x * (cellSize.width + Border),
                                    Border + y * (cellSize.height + Border));

                            // Set copy option
                            PageCopyOptions copyOptions = new PageCopyOptions();

                            // Copy page group from input to output
                            Group group = Group.copyFromPage(outDoc, inPage, copyOptions);

                            // Calculate group position
                            Size groupSize = group.getSize();
                            double scale = Math.min(cellSize.width / groupSize.width,
                                    cellSize.height / groupSize.height);

                            // Calculate target size
                            Size targetSize = new Size(groupSize.width * scale, groupSize.height * scale);

                            // Calculate position
                            Point targetPos = new Point(cellPosition.x + ((cellSize.width - targetSize.width) / 2),
                                    cellPosition.y + ((cellSize.height - targetSize.height) / 2));

                            // Calculate rectangle
                            Rectangle targetRect = new Rectangle(targetPos.x, targetPos.y,
                                    targetPos.x + targetSize.width, targetPos.y + targetSize.height);

                            // Add group to page
                            generator.paintGroup(group, targetRect, null);

                            pageCount++;
                        }
                        // Add page
                        if (outPage != null) {
                            generator.close();
                            outPages.add(outPage);
                        }
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
}