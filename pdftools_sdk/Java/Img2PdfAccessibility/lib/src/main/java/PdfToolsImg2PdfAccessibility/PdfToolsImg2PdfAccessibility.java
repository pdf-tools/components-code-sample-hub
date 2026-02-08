/****************************************************************************
 *
 * File:            pdftoolsimg2pdfaccessibility.java
 *
 * Usage:           java pdftoolsimg2pdfaccessibility <inputPath> <alternateText> <outputPath>
 *                  
 * Title:           Convert an image to an accessible PDF/A document
 *                  
 * Description:     Convert an image to an accessible PDF/A-2a document.
 *                  Alternative text is added to the image, as required for
 *                  PDF/A level A, to ensure accessibility for people with
 *                  disabilities who use assistive technologies.
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

package PdfToolsImg2PdfAccessibility;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.image2pdf.Converter;
import com.pdftools.image2pdf.profiles.*;
import com.pdftools.pdf.Conformance;
import com.pdftools.pdf.Conformance.PdfAVersion.Level;
import com.pdftools.image.Document;

public class PdfToolsImg2PdfAccessibility
{
    static void usage() {
        System.out.println("Usage: java pdftoolsimg2pdfaccessibility <inputPath> <alternateText> <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 3 || args.length > 3) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            image2Pdf(args[0], args[1], args[2]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void image2Pdf(String inPath, String alternateText, String outPath) throws Exception
    {
        // Create the profile that defines the conversion parameters.
        // The Archive profile converts images to PDF/A documents for archiving.
        Archive profile = new Archive();

        // Set conformance of output document to PDF/A-2a
        profile.setConformance(new Conformance(new Conformance.PdfAVersion(2, Level.A)));

        // For PDF/A level A, an alternate text is required for each page of the image.
        // This is optional for other PDF/A levels, e.g. PDF/A-2b.
        profile.setLanguage("en");
        profile.getAlternateText().add(alternateText);

        // Optionally other profile parameters can be changed according to the 
        // requirements of your conversion process.

        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr);

            // Create output stream
            FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

            // Convert the image to a tagged PDF/A document
            com.pdftools.pdf.Document outDoc = new Converter().convert(inDoc, outStream, profile))
        {
        }
    }
}
