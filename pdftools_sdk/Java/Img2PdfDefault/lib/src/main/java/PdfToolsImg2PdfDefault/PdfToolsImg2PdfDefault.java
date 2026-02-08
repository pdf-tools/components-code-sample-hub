/****************************************************************************
 *
 * File:            pdftoolsimg2pdfdefault.java
 *
 * Usage:           java pdftoolsimg2pdfdefault <inputPath> <outputPath>
 *                  
 * Title:           Convert image to PDF
 *                  
 * Description:     Convert an image to a PDF. The default settings for this
 *                  conversion profile place each image on a separate A4
 *                  portrait page with a 2 cm margin.
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

package PdfToolsImg2PdfDefault;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.image2pdf.Converter;
import com.pdftools.image2pdf.profiles.*;
import com.pdftools.image.Document;

public class PdfToolsImg2PdfDefault
{
    static void usage() {
        System.out.println("Usage: java pdftoolsimg2pdfdefault <inputPath> <outputPath>");
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

            image2Pdf(args[0], args[1]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void image2Pdf(String inPath, String outPath) throws Exception
    {
        // Create the profile that defines the conversion parameters.
        // The Default profile converts images to PDF documents.
        Default profile = new Default();

        // Optionally, the profile's parameters can be changed according to the 
        // requirements of your conversion process.

        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr);

            // Create output stream
            FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

            // Convert the image to a PDF document
            com.pdftools.pdf.Document outDoc = new Converter().convert(inDoc, outStream, profile))
        {
        }
    }
}
