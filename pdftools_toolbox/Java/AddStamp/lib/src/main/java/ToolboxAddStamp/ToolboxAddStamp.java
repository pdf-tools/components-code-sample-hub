/****************************************************************************
 *
 * File:            toolboxaddstamp.java
 *
 * Usage:           java toolboxaddstamp <inputPath> <stampString> <outputPath> [<alpha>]
 *                  Example: in.pdf APPROVED out.pdf 0.5
 *                  
 * Title:           Add stamp to PDF
 *                  
 * Description:     Add a semi-transparent stamp text onto each page of a PDF
 *                  document. Optionally specify the color and the opacity of
 *                  the stamp.
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

package ToolboxAddStamp;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.pdf.content.ColorSpace;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.ProcessColorSpaceType;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.content.Paint;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.content.Transparency;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.geometry.real.AffineTransform;

public class ToolboxAddStamp {
    private static Paint paint;
    private static Font font;
    private static double fontSize = 50.0;

    static void usage() {
        System.out.println("Usage: java toolboxaddstamp <inputPath> <stampString> <outputPath> [<alpha>]");
        System.out.println("       Example: in.pdf APPROVED out.pdf 0.5");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 3 || args.length > 4) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inPath = args[0];
            String stampString = args[1];
            String outPath = args[2];

            // Get opacity of stamp
            double alpha = 0.5; // default of opacity
            if (args.length == 4) {
                alpha = Double.parseDouble(args[3]);
                if (alpha < 0.0 || alpha > 1.0)
                    throw new IOException("The value must be between 0.0 and 1.0. Current value: " + args[3]);
            }

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

                    // Get the color space
                    ColorSpace colorSpace = ColorSpace.createProcessColorSpace(outDoc, ProcessColorSpaceType.RGB);

                    // Choose the RGB color value
                    double[] color = { 1.0, 0.0, 0.0 };
                    Transparency transparency = new Transparency(alpha);

                    // Create paint object
                    paint = Paint.create(outDoc, colorSpace, color, transparency);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Loop throw all pages of input
                    for (Page inPage : inDoc.getPages()) {
                        // Copy page from input to output
                        Page outPage = Page.copy(outDoc, inPage, copyOptions);

                        // Add text to page
                        addStamp(outDoc, outPage, stampString);

                        // Add page to document
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

    private static void addStamp(Document outputDoc, Page outPage, String stampString)
            throws ToolboxException, IOException {
        try (// Create content generator
            ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {
            // Create text object
            Text text = Text.create(outputDoc);
            try (// Create text generator
                TextGenerator textgenerator = new TextGenerator(text, font, fontSize, null)) {
                // Calculate point and angle of rotation
                Point rotationCenter = new Point(outPage.getSize().width / 2.0, outPage.getSize().height / 2.0);

                // Calculate rotation angle
                double rotationAngle = Math.atan2(outPage.getSize().height, outPage.getSize().width) / Math.PI * 180.0;

                // Rotate text input around the calculated position
                AffineTransform trans = AffineTransform.getIdentity();
                trans.rotate(rotationAngle, rotationCenter);
                generator.transform(trans);

                // Calculate position
                Point position = new Point((outPage.getSize().width - textgenerator.getWidth(stampString)) / 2.0,
                        (outPage.getSize().height - font.getAscent() * fontSize) / 2.0);

                // Move to position
                textgenerator.moveTo(position);

                // Set text paint
                textgenerator.setFill(paint);

                // Add given stamp string
                textgenerator.showLine(stampString);
            }

            // Paint the positioned text
            generator.paintText(text);
        }
    }
}