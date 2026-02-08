/****************************************************************************
 *
 * File:            toolboxlayouttext.java
 *
 * Usage:           java toolboxlayouttext <textPath> <outputPath>
 *                  
 * Title:           Layout text on PDF page
 *                  
 * Description:     Create a new PDF document with one page. On this page,
 *                  within a given rectangular area, add a text block with a
 *                  full justification layout.
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

package ToolboxLayoutText;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.charset.Charset;
import java.util.List;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.geometry.real.Size;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextGenerator;

public class ToolboxLayoutText {
    private static double Border = 50;

    static void usage() {
        System.out.println("Usage: java toolboxlayouttext <textPath> <outputPath>");
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

            String textPath = args[0];
            String outPath = args[1];

            try (
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, null, null)) {
                    // Create embedded font in output document
                    Font font = Font.createFromSystem(outDoc, "Arial", "Italic", true);

                    // Create page
                    Page outPage = Page.create(outDoc, new Size(595, 842));

                    // Add text to document
                    layoutText(outDoc, outPage, textPath, font, 20);

                    // Add page to output document
                    outDoc.getPages().add(outPage);
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    private static void layoutText(Document outputDoc, Page outPage, String textPath, Font font, double fontSize)
            throws ToolboxException, IOException {
        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {
            // Create text object
            Text text = Text.create(outputDoc);

            try (// Create a text generator
                TextGenerator textGenerator = new TextGenerator(text, font, fontSize, null)) {

                // Calculate position
                Point position = new Point(Border, outPage.getSize().height - Border);

                // Move to position
                textGenerator.moveTo(position);

                // Loop throw all lines of the textinput
                List<String> lines = Files.readAllLines(Paths.get(textPath), Charset.defaultCharset());
                for (String line : lines) {
                    // Split string in substrings
                    String[] substrings = line.split(" ");
                    String currentLine = null;
                    double maxWidth = outPage.getSize().width - (Border * 2);

                    int wordCount = 0;

                    // Loop throw all words of input strings
                    for (String word : substrings) {
                        String tempLine;

                        // Concatenate substrings to line
                        if (currentLine != null) {
                            tempLine = currentLine + " " + word;
                        } else {
                            tempLine = word;
                        }

                        // Calculate the current width of line
                        double width = textGenerator.getWidth(currentLine);

                        if ((textGenerator.getWidth(tempLine) > maxWidth)) {
                            // Calculate the word spacing
                            textGenerator.setWordSpacing((maxWidth - width) / (double) (wordCount - 1));

                            // Paint on new line
                            textGenerator.showLine(currentLine);
                            textGenerator.setWordSpacing(0);
                            currentLine = word;
                            wordCount = 1;
                        } else {
                            currentLine = tempLine;
                            wordCount++;
                        }
                    }
                    textGenerator.setWordSpacing(0);
                    // Add given stamp string
                    textGenerator.showLine(currentLine);
                }
            }
            // Paint the positioned text
            generator.paintText(text);
        }
    }
}