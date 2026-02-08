/****************************************************************************
 *
 * File:            pdftoolspdftoolsintro.java
 *
 * Usage:           java pdftoolspdftoolsintro <coverImage> <contentPdfPath> <outputPath>
 *                  
 * Title:           Hello, Pdftools SDK!
 *                  
 * Description:     Add a cover page from an image to a PDF.
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

package PdfToolsPdfToolsIntro;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.documentassembly.DocumentAssembler;
import com.pdftools.image2pdf.Converter;
import com.pdftools.image2pdf.profiles.Default;
import com.pdftools.sys.*;

public class PdfToolsPdfToolsIntro
{
    static void usage() {
        System.out.println("Usage: java pdftoolspdftoolsintro <coverImage> <contentPdfPath> <outputPath>");
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

            String imageCoverPath = args[0];
            String contentPath = args[1];
            String outputPdfPath = args[2];

            try (
            	MemoryStream imageCoverStream = new MemoryStream();
            	FileStream inputPdfStream = new FileStream(contentPath, FileStream.Mode.READ_ONLY)
            ) {
            	// Convert the cover image to a PDF document
            	image2Pdf(imageCoverPath, imageCoverStream);

            	// Merge the cover page with the content document
            	merge(imageCoverStream, inputPdfStream, outputPdfPath);
        	}

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void image2Pdf(String inPath, MemoryStream imageStream) throws Exception {
        // Create the profile that defines the conversion parameters.
        Default profile = new Default();

        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            com.pdftools.image.Document inDoc = com.pdftools.image.Document.open(inStr)
        ) {
            // Convert the image to a PDF document
        	new Converter().convert(inDoc, imageStream, profile);
        } catch (Exception e) {
            System.out.println("Error during image to PDF conversion: " + e.getMessage());
            e.printStackTrace();
            throw e;
        }
    }

    private static void merge(MemoryStream coverStream, FileStream inputContentStream, String outPath) throws Exception {
        try (
            FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);
            DocumentAssembler docAssembler = new DocumentAssembler(outStream)) {

            // Append only the first page of the cover stream
            docAssembler.append(com.pdftools.pdf.Document.open(coverStream), 1, 1);
            // Append the content document
            docAssembler.append(com.pdftools.pdf.Document.open(inputContentStream));

            // Assemble the merged document
            docAssembler.assemble();
        }
    }
}
