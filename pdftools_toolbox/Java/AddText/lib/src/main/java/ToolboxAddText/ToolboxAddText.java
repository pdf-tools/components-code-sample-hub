/****************************************************************************
 *
 * File:            toolboxaddtext.java
 *
 * Usage:           java toolboxaddtext <inputPath> <textString> <outputPath>
 *                  Example: in.pdf \"Test String\" out.pdf
 *                  
 * Title:           Add text to PDF
 *                  
 * Description:     Add text at a specified position on the first page of a
 *                  PDF document.
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

package ToolboxAddText;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxAddText {
    private static double border = 40;
    private static double fontSize = 15;
    private static Font font;

    static void usage() {
        System.out.println("Usage: java toolboxaddtext <inputPath> <textString> <outputPath>");
        System.out.println("       Example: in.pdf \"Test String\" out.pdf");

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
            String textString = args[1];
            String outPath = args[2];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {
                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Create embedded font in output document
                    font = Font.createFromSystem(outDoc, "Arial", "Italic", true);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy first page, add text, and append to output document
                    Page outPage = Page.copy(outDoc, inDoc.getPages().get(0), copyOptions);
                    addText(outDoc, outPage, textString);
                    outDoc.getPages().add(outPage);

                    // Copy remaining pages and append to output document
                    PageList inPageRange = inDoc.getPages().subList(1, inDoc.getPages().size());
                    PageList copiedPages = PageList.copy(outDoc, inPageRange, copyOptions);
                    outDoc.getPages().addAll(copiedPages);
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    private static void copyDocumentData(Document inDoc, Document outDoc) throws ToolboxException, IOException {
        // Copy document-wide data (excluding metadata)

        // Output intent
        if (inDoc.getOutputIntent() != null)
            outDoc.setOutputIntent(IccBasedColorSpace.copy(outDoc, inDoc.getOutputIntent()));

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

    private static void addText(Document outputDoc, Page outPage, String textString)
            throws ToolboxException, IOException {
        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {
            // Create text object
            Text text = Text.create(outputDoc);

            try (// Create a text generator
                TextGenerator textgenerator = new TextGenerator(text, font, fontSize, null)) {
                // Calculate position
                Point position = new Point(border, outPage.getSize().height - border - fontSize * font.getAscent());

                // Move to position
                textgenerator.moveTo(position);
                // Add given text string
                textgenerator.showLine(textString);
            }

            // Paint the positioned text
            generator.paintText(text);
        }
    }
}