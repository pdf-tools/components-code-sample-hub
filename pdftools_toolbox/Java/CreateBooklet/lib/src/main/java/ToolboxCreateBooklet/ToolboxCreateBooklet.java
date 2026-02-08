/****************************************************************************
 *
 * File:            toolboxcreatebooklet.java
 *
 * Usage:           java toolboxcreatebooklet <inputPath> <outputPath>
 *                  
 * Title:           Create a booklet from PDF
 *                  
 * Description:     Place up to two A4 pages in the right order on an A3
 *                  page, so that duplex printing and folding the A3 pages
 *                  results in a booklet.
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

package ToolboxCreateBooklet;

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
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.pdf.content.Group;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextGenerator;

public class ToolboxCreateBooklet {
    // A3 landscape
    private static final double PageWidth = 1190;
    private static final double PageHeight = 842;
    private static final double Border = 10;
    private static final double CellWidth = (PageWidth - 3 * Border) / 2;
    private static final double CellHeight = PageHeight - 2 * Border;
    private static final double CellLeft = Border;
    private static final double CellRight = 2 * Border + CellWidth;
    private static final double CellYPos = Border;

    static void usage() {
        System.out.println("Usage: java toolboxcreatebooklet <inputPath> <outputPath>");
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
                    Font font = Font.createFromSystem(outDoc, "Arial", "Italic", true);

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Copy pages
                    PageList inPages = inDoc.getPages();
                    PageList outPages = outDoc.getPages();
                    int numberOfSheets = (inPages.size() + 3) / 4;

                    for (int sheetNumber = 0; sheetNumber < numberOfSheets; ++sheetNumber) {
                        // Add on front side
                        createBooklet(inPages, outDoc, outPages, 4 * numberOfSheets - 2 * sheetNumber - 1,
                                2 * sheetNumber, font);

                        // Add on back side
                        createBooklet(inPages, outDoc, outPages, 2 * sheetNumber + 1,
                                4 * numberOfSheets - 2 * sheetNumber - 2, font);
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

    private static void createBooklet(PageList inPages, Document outDoc, PageList outPages, int leftPageIndex,
            int rightPageIndex, Font font) throws ToolboxException, IOException {
        // Define page copy options
        PageCopyOptions copyOptions = new PageCopyOptions();

        // Create page object
        Page outPage = Page.create(outDoc,  new Size(PageWidth, PageHeight));

        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {

            // Left page
            if (leftPageIndex < inPages.size()) {
                Page leftPage = inPages.get(leftPageIndex);

                // Copy page from input to output
                Group leftGroup = Group.copyFromPage(outDoc, leftPage, copyOptions);

                // Paint group on the calculated rectangle
                generator.paintGroup(leftGroup, computeTargetRect(leftGroup.getSize(), true), null);

                // Add page number to page
                StampPageNumber(outDoc, font, generator, leftPageIndex + 1, true);
            }

            // Right page
            if (rightPageIndex < inPages.size()) {
                Page rightPage = inPages.get(rightPageIndex);

                // Copy page from input to output
                Group rightGroup = Group.copyFromPage(outDoc, rightPage, copyOptions);

                // Paint group on the calculated rectangle
                generator.paintGroup(rightGroup, computeTargetRect(rightGroup.getSize(), false), null);

                // Add page number to page
                StampPageNumber(outDoc, font, generator, rightPageIndex + 1, false);
            }
        }
        // Add page to output document
        outPages.add(outPage);
    }

    private static Rectangle computeTargetRect(Size bbox, Boolean isLeftPage) {
        // Calculate factor for fitting page into rectangle
        double scale = Math.min(CellWidth / bbox.width, CellHeight / bbox.height);
        double groupWidth = bbox.width * scale;
        double groupHeight = bbox.height * scale;

        // Calculate x-value
        double groupXPos = isLeftPage ? CellLeft + (CellWidth - groupWidth) / 2 :
                                        CellRight + (CellWidth - groupWidth) / 2;

        // Calculate y-value
        double groupYPos = CellYPos + (CellHeight - groupHeight) / 2;

        // Calculate rectangle
        return new Rectangle(groupXPos, groupYPos, groupXPos + groupWidth, groupYPos + groupHeight);
    }

    private static void StampPageNumber(Document document, Font font, ContentGenerator generator, int pageNo,
            boolean isLeftPage) throws ToolboxException, IOException {
        // Create text object
        Text text = Text.create(document);

        try (// Create text generator
            TextGenerator textgenerator = new TextGenerator(text, font, 8, null)) {
            String stampText = String.format("Page %d", pageNo);

            // Get width of stamp text
            double width = textgenerator.getWidth(stampText);

            // Calculate position
            double x = isLeftPage ? Border + 0.5 * CellWidth - width / 2 :
                                    2 * Border + 1.5 * CellWidth - width / 2;
            double y = Border;

            // Move to position
            textgenerator.moveTo(new Point(x, y));

            // Add page number
            textgenerator.show(stampText);
        }

        // Paint the positioned text
        generator.paintText(text);
    }
}