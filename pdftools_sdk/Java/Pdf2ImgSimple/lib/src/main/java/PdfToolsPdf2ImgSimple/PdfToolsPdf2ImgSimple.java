/****************************************************************************
 *
 * File:            pdftoolspdf2imgsimple.java
 *
 * Usage:           java pdftoolspdf2imgsimple <inputPath> <outputPath>
 *                  
 * Title:           Convert PDF to image
 *                  
 * Description:     Convert a PDF to a rasterized image. In this example, the
 *                  conversion profile outputs the PDF as a TIFF image
 *                  suitable for archiving.
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

package PdfToolsPdf2ImgSimple;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf2image.Converter;
import com.pdftools.pdf2image.profiles.*;
import com.pdftools.pdf.Document;

public class PdfToolsPdf2ImgSimple
{
    static void usage() {
        System.out.println("Usage: java pdftoolspdf2imgsimple <inputPath> <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            pdf2Image(args[0], args[1]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void pdf2Image(String inPath, String outPath) throws Exception
    {
        // Create the profile that defines the conversion parameters.
        // The Archive profile converts PDF documents to TIFF images for archiving.
        Archive profile = new Archive();

        // Optionally the profile's parameters can be changed according to the 
        // requirements of your conversion process.

        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr);

            // Create output stream
            FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

            // Convert the PDF document to an image document
            com.pdftools.image.Document outDoc = new Converter().convertDocument(inDoc, outStream, profile))
        {
        }
    }
}
