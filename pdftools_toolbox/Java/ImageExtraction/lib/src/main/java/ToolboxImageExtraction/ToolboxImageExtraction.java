/****************************************************************************
 *
 * File:            toolboximageextraction.java
 *
 * Usage:           java toolboximageextraction <inputPath> <outputDir>
 *                  Example: in.pdf dir/subdir/
 *                  
 * Title:           Extract all images and image masks from a PDF
 *                  
 * Description:     Extract the embedded image data as JPEG or TIFF,
 *                  depending on the compression format used.
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

package ToolboxImageExtraction;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;

import com.pdftools.toolbox.*;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.content.ImageElement;
import com.pdftools.toolbox.pdf.content.ImageMaskElement;
import com.pdftools.toolbox.pdf.Document;

public class ToolboxImageExtraction {
    static void usage() {
        System.out.println("Usage: java toolboximageextraction <inputPath> <outputDir>");
        System.out.println("       Example: in.pdf dir/subdir/");

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
            String outputDir = args[1];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null)) {

                // Loop over all pages and extract images
                for (int i = 0; i < inDoc.getPages().size(); i++) {
                    ContentExtractor extractor = new ContentExtractor(inDoc.getPages().get(i).getContent());
                    extractImages(extractor, i + 1, outputDir);
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    private static void extractImages(ContentExtractor extractor, int pageNo, String outputDir) throws IOException {
        int imgCount = 0;
        int imgMaskCount = 0;
        for (Object elementObj : extractor) {
            if (elementObj instanceof ImageElement) {
                ImageElement element = (ImageElement) elementObj;
                imgCount++;
                String extension = ".tiff";
                switch (element.getImage().getDefaultImageType()) {
                    case JPEG:
                        extension = ".jpg";
                        break;
                    case TIFF:
                        extension = ".tiff";
                        break;
                    default:
                        break;
                }
                String outputPath = Paths.get(outputDir, "image_page" + pageNo + "_" + imgCount + extension).toString();
                try (FileStream imageStream = new FileStream(outputPath, FileStream.Mode.READ_WRITE_NEW)) {
                    element.getImage().extract(imageStream);
                } catch (GenericException ex) {
                    System.out.println(ex.toString());
                }
            }
            else if (elementObj instanceof ImageMaskElement) {
                ImageMaskElement element = (ImageMaskElement) elementObj;
                imgMaskCount++;
                String extension = ".tiff";
                String outputPath = Paths.get(outputDir, "image_mask_page" + pageNo + "_" + imgMaskCount + extension).toString();
                try (FileStream imageStream = new FileStream(outputPath, FileStream.Mode.READ_WRITE_NEW)) {
                    element.getImageMask().extract(imageStream);
                } catch (GenericException ex) {
                    System.out.println(ex.toString());
                }
            }
        }
    }
}