/****************************************************************************
 *
 * File:            pdftoolsmultipleimg2pdf.java
 *
 * Usage:           java pdftoolsmultipleimg2pdf <inputPath> [<inputPath2> ...] <outputPath>
 *                  
 * Title:           Convert multiple images to a PDF
 *                  
 * Description:     Convert a list of images into a single PDF. Supported
 *                  image types are TIFF, JPEG, BMP, GIF, PNG, JBIG2, and
 *                  JPEG2000.
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

package PdfToolsMultipleImg2Pdf;

import java.util.stream.Collectors;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.image2pdf.Converter;
import com.pdftools.image2pdf.profiles.*;
import com.pdftools.image.Document;
import com.pdftools.image.DocumentList;

public class PdfToolsMultipleImg2Pdf
{
    static void usage() {
        System.out.println("Usage: java pdftoolsmultipleimg2pdf <inputPath> [<inputPath2> ...] <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 2) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            Images2Pdf(Arrays.copyOfRange(args, 0, args.length - 1), args[args.length - 1]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void Images2Pdf(String[] inPaths, String outPath) throws Exception
    {
        // Create the profile that defines the conversion parameters.
        Default profile = new Default();

        List<FileStream> streams = new ArrayList<>();
        DocumentList images = new DocumentList();

        // Optionally the profile's parameters can be changed according to the 
        // requirements of your conversion process.
        try {
            // Open input documents
            for (String inPath : inPaths) {
                FileStream stream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                streams.add(stream);
                images.add(Document.open(stream));
            }

            try (
                // Create output stream
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);
                // Convert the image to a PDF document
                com.pdftools.pdf.Document outDoc = new Converter().convertMultiple(images, outStream, profile)) {
                }
        }
        finally {
            for (Document image : images) 
                image.close();
            for (FileStream stream : streams)
                stream.close();
        }
    }
}
