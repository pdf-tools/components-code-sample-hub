/****************************************************************************
 *
 * File:            toolboxoverlaycolor.java
 *
 * Usage:           java toolboxoverlaycolor [<options>] <inputPath> <outputPath>
 *                  Example: -k 0.5 1.0 in.pdf out.pdf
 *                  Options:
 *                  -k (k) (a)             specifiy grayscale and alpha color
 *                  -c (c) (m) (y) (k) (a)      specifiy CMKY and alpha color
 *                  -r (r) (g) (b) (a)          specifiy RGB and alpha color
 *                  color values between 0 and 1
 *                  default: -k 0.9 1.0
 *                  
 * Title:           Overlay color of PDF
 *                  
 * Description:     Overlay all pages of a PDF document with a configurable
 *                  color.
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

package ToolboxOverlayColor;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.geometry.real.Size;
import com.pdftools.toolbox.pdf.content.ColorSpace;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.Fill;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.content.ProcessColorSpaceType;
import com.pdftools.toolbox.pdf.content.Transparency;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.content.Paint;
import com.pdftools.toolbox.pdf.content.BlendMode;
import com.pdftools.toolbox.pdf.content.Path;
import com.pdftools.toolbox.pdf.content.PathGenerator;

public class ToolboxOverlayColor {
    // Defines
    private static ProcessColorSpaceType colorType = ProcessColorSpaceType.GRAY;
    private static double colorAlpha = 1.0;

    static void usage() {
        System.out.println("Usage: java toolboxoverlaycolor [<options>] <inputPath> <outputPath>");
        System.out.println("       Example: -k 0.5 1.0 in.pdf out.pdf");
        System.out.println("       Options:");
        System.out.println("       -k (k) (a)             specifiy grayscale and alpha color");
        System.out.println("       -c (c) (m) (y) (k) (a)      specifiy CMKY and alpha color");
        System.out.println("       -r (r) (g) (b) (a)          specifiy RGB and alpha color");
        System.out.println("       color values between 0 and 1");
        System.out.println("       default: -k 0.9 1.0");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 2) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            double[] color = new double[] { 0.9 };

            int i = 0;
            for (; i < args.length; i++) {
                if (args[i].charAt(0) == '-') {
                    switch (args[i].charAt(1)) {
                    case 'c':
                        colorType = ProcessColorSpaceType.CMYK;
                        if (args.length - i++ < 8) {
                            usage();
                        }
                        color = new double[] {
                                Double.parseDouble(args[i++]),
                                Double.parseDouble(args[i++]),
                                Double.parseDouble(args[i++]),
                                Double.parseDouble(args[i++]) };
                        colorAlpha = Double.parseDouble(args[i]);
                        break;
                    case 'k':
                        colorType = ProcessColorSpaceType.GRAY;
                        if (args.length - i++ < 5) {
                            usage();
                        }
                        color = new double[] { Double.parseDouble(args[i++]) };
                        colorAlpha = Double.parseDouble(args[i]);
                        break;
                    case 'r':
                        colorType = ProcessColorSpaceType.RGB;
                        if (args.length - i++ < 7) {
                            usage();
                        }
                        color = new double[] {
                                Double.parseDouble(args[i++]),
                                Double.parseDouble(args[i++]),
                                Double.parseDouble(args[i++]) };
                        colorAlpha = Double.parseDouble(args[i]);
                        break;
                    }
                } else
                    break;
            }

            if (args.length - i < 2) {
                 usage(); 
            }

            String inPath = args[i];
            String outPath = args[i + 1];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Create transparency and set blend mode
                    Transparency transparency = new Transparency(colorAlpha);
                    transparency.setBlendMode(BlendMode.MULTIPLY);

                    // Create colorspace
                    ColorSpace colorSpace = ColorSpace.createProcessColorSpace(outDoc, colorType);

                    // Create a transparent paint for the given color
                    Paint paint = Paint.create(outDoc, colorSpace, color, transparency);
                    Fill fill = new Fill(paint);

                    // Set copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Loop through all pages
                    for (Page inPage : inDoc.getPages()) {
                        // Create a new page
                        Size size = inPage.getSize();
                        Page outPage = Page.copy(outDoc, inPage, copyOptions);

                        try (// Create a content generator
                            ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {
                            // Calculate rectangle
                            Rectangle rect = new Rectangle(0, 0, size.width, size.height);

                            // Make a rectangular path the same size as the page
                            Path path = new Path();
                            try (
                                PathGenerator pathGenerator = new PathGenerator(path)) {
                                pathGenerator.addRectangle(rect);
                            }

                            // Paint the path with the transparent paint
                            generator.paintPath(path, fill, null);
                        }

                        // Add pages to output document
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