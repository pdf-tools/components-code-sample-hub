/****************************************************************************
 *
 * File:            toolboxfitpage.java
 *
 * Usage:           java toolboxfitpage <inputPath> <outputPath>
 *                  
 * Title:           Fit pages to specific page format
 *                  
 * Description:     Fit each page of a PDF document to a specific page
 *                  format.
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

package ToolboxFitPage;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
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
import com.pdftools.toolbox.geometry.Rotation;
import com.pdftools.toolbox.geometry.real.AffineTransform;

public class ToolboxFitPage {
    // A4 portrait
    private static final double TargetWidth = 595;
    private static final double TargetHeight = 842;
    private static final boolean AllowRotate = true;

    static void usage() {
        System.out.println("Usage: java toolboxfitpage <inputPath> <outputPath>");
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

                    // Copy pages
                    for (Page inPage : inDoc.getPages()) {
                        Page outPage = null;
                        Size pageSize = inPage.getSize();

                        boolean rotate = AllowRotate &&
                            (pageSize.height >= pageSize.width) != (TargetHeight >= TargetWidth);
                        Size rotatedSize = pageSize;

                        if (rotate)
                            rotatedSize = new Size(pageSize.height, pageSize.width);

                        if (rotatedSize.width == TargetWidth && rotatedSize.height == TargetWidth) {
                            // If size is correct, copy page only
                            outPage = Page.copy(outDoc, inPage, copyOptions);

                            if (rotate)
                                outPage.rotate(Rotation.CLOCKWISE);
                        } else {
                            // Create new page of correct size and fit existing page onto it
                            outPage = Page.create(outDoc, new Size(TargetWidth, TargetHeight));

                            // Copy page as group
                            Group group = Group.copyFromPage(outDoc, inPage, copyOptions);
                            // Calculate scaling and position of group
                            double scale = Math.min(TargetWidth / rotatedSize.width,
                                TargetHeight / rotatedSize.height);

                            // Calculate position
                            Point position = new Point(
                                    (TargetWidth - pageSize.width * scale) / 2,
                                    (TargetHeight - pageSize.height * scale) / 2);

                            try(// Create content generator
                                ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {
                                // Calculate and apply transformation
                                AffineTransform transform = AffineTransform.getIdentity();
                                transform.translate(position.x, position.y);
                                transform.scale(scale, scale);

                                Point point = new Point(pageSize.width / 2.0, pageSize.height / 2.0);

                                // Rotate input file 
                                if (rotate)
                                    transform.rotate(90, point);
                                generator.transform(transform);

                                // Paint group
                                generator.paintGroup(group, null, null);
                            }
                        }
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
}