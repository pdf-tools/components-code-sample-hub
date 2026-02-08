/****************************************************************************
 *
 * File:            toolboxtextextraction.java
 *
 * Usage:           java toolboxtextextraction <inputPath>
 *                  Example: in.pdf
 *                  
 * Title:           Extract all text from PDF
 *                  
 * Description:     Write text from PDF page by page to console. Determine
 *                  heuristically if two text fragments belong to the same
 *                  word.
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

package ToolboxTextExtraction;

import java.util.stream.Collectors;

import java.io.File;

import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.content.ContentElement;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextElement;
import com.pdftools.toolbox.pdf.content.TextFragment;
import com.pdftools.toolbox.pdf.content.UngroupingSelection;

public class ToolboxTextExtraction {
    static void usage() {
        System.out.println("Usage: java toolboxtextextraction <inputPath>");
        System.out.println("       Example: in.pdf");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 1 || args.length > 1) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inPath = args[0];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null)) {
                int pageNumber = 1;

                // Process each page
                for (Page inPage : inDoc.getPages()) {
                    System.out.println("==========");
                    System.out.println("Page: " + pageNumber++);
                    System.out.println("==========");

                    ContentExtractor extractor = new ContentExtractor(inPage.getContent());
                    extractor.setUngrouping(UngroupingSelection.ALL);

                    // Iterate over all content elements and only process text elements
                    for (ContentElement element : extractor) {
                        if (element instanceof TextElement)
                            writeText(((TextElement) element).getText());
                    }
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
    private static void writeText(Text text) {
        String textPart = "";

        // Write all text fragments
        // Determine heuristically if there is a space between two text fragments
        for (int iFragment = 0; iFragment < text.size(); iFragment++) {
            TextFragment currFragment = text.get(iFragment);
            if (iFragment == 0)
                textPart += currFragment.getText();
            else {
                TextFragment lastFragment = text.get(iFragment - 1);
                if (currFragment.getCharacterSpacing() != lastFragment.getCharacterSpacing() ||
                    currFragment.getFontSize() != lastFragment.getFontSize() ||
                    currFragment.getHorizontalScaling() != lastFragment.getHorizontalScaling() ||
                    currFragment.getRise() != lastFragment.getRise() ||
                    currFragment.getWordSpacing() != lastFragment.getWordSpacing()) {
                    textPart += " ";
                    textPart += currFragment.getText();
                }
                else {
                    Point currentBotLeft = currFragment.getTransform().transformRectangle(currFragment.getBoundingBox()).getBottomLeft();
                    Point beforeBotRight = lastFragment.getTransform().transformRectangle(lastFragment.getBoundingBox()).getBottomRight();

                    if (beforeBotRight.getX() < currentBotLeft.getX() - 0.7 * currFragment.getFontSize() ||
                        beforeBotRight.getY() < currentBotLeft.getY() - 0.1 * currFragment.getFontSize() ||
                        currentBotLeft.getY() < beforeBotRight.getY() - 0.1 * currFragment.getFontSize()) {
                        textPart += " ";
                        textPart += currFragment.getText();
                    }
                    else
                        textPart += currFragment.getText();
                }
            }
        }
        System.out.println(textPart);
    }
}