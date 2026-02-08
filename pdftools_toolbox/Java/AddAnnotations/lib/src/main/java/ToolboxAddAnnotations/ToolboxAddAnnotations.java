/****************************************************************************
 *
 * File:            toolboxaddannotations.java
 *
 * Usage:           java toolboxaddannotations <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Add annotations to PDF
 *                  
 * Description:     Generate and add various types of annotations at
 *                  specified positions on the first page of a PDF document.
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

package ToolboxAddAnnotations;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;

import com.pdftools.toolbox.ConformanceException;
import com.pdftools.toolbox.CorruptException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.UnsupportedFeatureException;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.geometry.real.QuadrilateralList;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.geometry.real.Size;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.annotations.AnnotationList;
import com.pdftools.toolbox.pdf.annotations.EllipseAnnotation;
import com.pdftools.toolbox.pdf.annotations.FreeText;
import com.pdftools.toolbox.pdf.annotations.Highlight;
import com.pdftools.toolbox.pdf.annotations.StickyNote;
import com.pdftools.toolbox.pdf.content.ColorSpace;
import com.pdftools.toolbox.pdf.content.ContentElement;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.content.ImageElement;
import com.pdftools.toolbox.pdf.content.Paint;
import com.pdftools.toolbox.pdf.content.ProcessColorSpaceType;
import com.pdftools.toolbox.pdf.content.Stroke;
import com.pdftools.toolbox.pdf.content.TextElement;
import com.pdftools.toolbox.pdf.content.TextFragment;
import com.pdftools.toolbox.pdf.content.Transparency;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.pdf.navigation.WebLink;
import com.pdftools.toolbox.sys.FileStream;

public class ToolboxAddAnnotations {

    static void usage() {
        System.out.println("Usage: java toolboxaddannotations <inputPath> <outputPath>");
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
                // Create file stream
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy first page and add annotations
                    Page outPage = copyAndAddAnnotations(outDoc, inDoc.getPages().get(0), copyOptions);

                    // Add the page to the output document's page list
                    outDoc.getPages().add(outPage);

                    // Copy the remaining pages and add to the output document's page list
                    PageList inPages = inDoc.getPages().subList(1, inDoc.getPages().size());
                    PageList outPages = PageList.copy(outDoc, inPages, copyOptions);
                    outDoc.getPages().addAll(outPages);
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

    private static Page copyAndAddAnnotations(Document outDoc, Page inPage, PageCopyOptions copyOptions) throws ConformanceException, CorruptException, IOException, UnsupportedFeatureException {
        // Copy page to output document
        Page outPage = Page.copy(outDoc, inPage, copyOptions);

        // Make a RGB color space
        ColorSpace rgb = ColorSpace.createProcessColorSpace(outDoc, ProcessColorSpaceType.RGB);

        // Get the page size for positioning annotations
        Size pageSize = outPage.getSize();

        // Get the output page's list of annotations for adding annotations
        AnnotationList annotations = outPage.getAnnotations();

        // Create a sticky note and add to output page's annotations
        Paint green = Paint.create(outDoc, rgb, new double[] { 0, 1, 0 }, null);
        Point stickyNoteTopLeft = new Point(10, pageSize.height - 10 );
        StickyNote stickyNote = StickyNote.create(outDoc, stickyNoteTopLeft, "Hello world!", green);
        annotations.add(stickyNote);

        // Create an ellipse and add to output page's annotations
        Paint blue = Paint.create(outDoc, rgb, new double[] { 0, 0, 1 }, null);
        Paint yellow = Paint.create(outDoc, rgb, new double[] { 1, 1, 0 }, null);
        Rectangle ellipseBox = new Rectangle(10, pageSize.height - 60, 70, pageSize.height - 20);
        EllipseAnnotation ellipse = EllipseAnnotation.create(outDoc, ellipseBox, new Stroke(blue, 1.5), yellow);
        annotations.add(ellipse);

        // Create a free text and add to output page's annotations
        Paint yellowTransp = Paint.create(outDoc, rgb, new double[] { 1, 1, 0 }, new Transparency(0.5));
        Rectangle freeTextBox = new Rectangle(10, pageSize.height - 170, 120, pageSize.height - 70);
        FreeText freeText = FreeText.create(outDoc, freeTextBox, "Lorem ipsum dolor sit amet, consectetur adipiscing elit.", yellowTransp);
        annotations.add(freeText);

        // A highlight and a web-link to be fitted on existing page content elements
        Highlight highlight = null;
        WebLink webLink = null;
        // Extract content elements from the input page
        ContentExtractor extractor = new ContentExtractor(inPage.getContent());
        for (ContentElement element : extractor) {
            // Take the first text element
            if (highlight == null && element instanceof TextElement) {
                TextElement textElement = (TextElement)element;
                // Get the quadrilaterals of this text element
                QuadrilateralList quadrilaterals = new QuadrilateralList();
                for (TextFragment fragment : textElement.getText())
                    quadrilaterals.add(fragment.getTransform().transformRectangle(fragment.getBoundingBox()));

                    // Create a highlight and add to output page's annotations
                    highlight = Highlight.createFromQuadrilaterals(outDoc, quadrilaterals, yellow);
                    annotations.add(highlight);
                }

            // Take the first image element
            if (webLink == null && element instanceof ImageElement) {
                // Get the quadrilateral of this image
                QuadrilateralList quadrilaterals = new QuadrilateralList();
                quadrilaterals.add(element.getTransform().transformRectangle(element.getBoundingBox()));

                // Create a web-link and add to the output page's links
                webLink = WebLink.createFromQuadrilaterals(outDoc, quadrilaterals, "https://www.pdf-tools.com");
                Paint red = Paint.create(outDoc, rgb, new double[] { 1, 0, 0 }, null);
                webLink.setBorderStyle(new Stroke(red, 1.5));
                outPage.getLinks().add(webLink);
            }

            // Exit loop if highlight and webLink have been created
            if (highlight != null && webLink != null)
                break;
        }

        // return the finished page
        return outPage;
    }
}
