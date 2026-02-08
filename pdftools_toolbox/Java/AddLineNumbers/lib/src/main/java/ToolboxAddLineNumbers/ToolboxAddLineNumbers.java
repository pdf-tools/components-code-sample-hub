/****************************************************************************
 *
 * File:            toolboxaddlinenumbers.java
 *
 * Usage:           java toolboxaddlinenumbers <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Add line numbers to PDF
 *                  
 * Description:     Add a line number in front of each line that contains
 *                  text.
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

package ToolboxAddLineNumbers;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import java.util.AbstractMap.SimpleEntry;
import java.util.Comparator;
import java.util.Map.Entry;
import java.util.SortedSet;
import java.util.TreeSet;

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
import com.pdftools.toolbox.pdf.content.ContentElement;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextElement;
import com.pdftools.toolbox.pdf.content.TextFragment;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.content.UngroupingSelection;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.sys.FileStream;

public class ToolboxAddLineNumbers {
    private static double fontSize = 8;
    private static double distance = 10;
    private static long lineNumber = 0;

    static void usage() {
        System.out.println("Usage: java toolboxaddlinenumbers <inputPath> <outputPath>");
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
                try (Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {
                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Create embedded font in output document
                    Font font = Font.createFromSystem(outDoc, "Arial", null, true);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages from input to output document
                    PageList inPages = inDoc.getPages();
                    PageList outPages = PageList.copy(outDoc, inPages, copyOptions);

                    // Iterate over all input-output page pairs and add line numbers
                    for (int i = 0; i < inPages.size(); ++i) {
                        addLineNumbers(outDoc, font, new SimpleEntry<>(inPages.get(i), outPages.get(i)));
                    }

                    // Add the finished pages to the output document's page list
                    outDoc.getPages().addAll(outPages);
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    private static void addLineNumbers(Document outDoc, Font lineNumberFont, Entry<Page, Page> pair) throws IOException, ToolboxException {
        // Add line numbers to all text found in the input page to the output page

        // The input and output page
        Page inPage = pair.getKey();
        Page outPage = pair.getValue();

        // Extract all text fragments
        ContentExtractor extractor = new ContentExtractor(inPage.getContent());
        extractor.setUngrouping(UngroupingSelection.ALL);
        // The left-most horizontal position of all text fragments
        double leftX = inPage.getSize().getWidth();

        Comparator<Double> comparator = new Comparator<Double>() {
            @Override
            public int compare(Double d1, Double d2) {
                Double diff = d2 - d1;
                if (Math.abs(diff) < fontSize)
                    return 0;
                return (int) Math.signum(diff);
            }
        };

        SortedSet<Double> lineYPositions = new TreeSet<>(comparator);

        for (ContentElement element : extractor) {

            // Process only text elements
            if (element instanceof TextElement) {
                TextElement textElement = (TextElement) element;
                // Iterate over all text fragments
                for (TextFragment fragment : textElement.getText()) {

                    // Get the fragments base line starting point
                    Point point = fragment.getTransform().transformPoint(new Point(fragment.getBoundingBox().left, 0));

                    // Update the left-most position
                    leftX = Math.min(leftX, point.x);

                    // Add the vertical position
                    lineYPositions.add(point.y);
                }
            }
        }

        // If at least one text fragment was found: add line numbers
        if (lineYPositions.size() > 0) {

            // Create a text object and use a text generator
            Text text = Text.create(outDoc);
            try (TextGenerator textGenerator = new TextGenerator(text, lineNumberFont, fontSize, null)) {
                // Iterate over all vertical positions found in the input
                for(double y : lineYPositions) {
                    // The line number string
                    String lineNumberString = String.valueOf(++lineNumber);

                    // The width of the line number string when shown on the page
                    double width = textGenerator.getWidth(lineNumberString);

                    // Position line numbers right aligned
                    // with a given distance to the right-most horizontal position
                    // and at the vertical position of the current text fragment
                    textGenerator.moveTo(new Point (leftX - width - distance, y));

                    // Show the line number string
                    textGenerator.show(lineNumberString);
                }
            }
            try (ContentGenerator contentGenerator = new ContentGenerator(outPage.getContent(), false)) {
                // Use a content generator to paint the text onto the page
                contentGenerator.paintText(text);
            }
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