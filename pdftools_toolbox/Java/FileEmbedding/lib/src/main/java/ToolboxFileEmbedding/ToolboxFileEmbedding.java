/****************************************************************************
 *
 * File:            toolboxfileembedding.java
 *
 * Usage:           java toolboxfileembedding <inputPath> <fileToEmbed> <outputPath> [<page>]
 *                  Example: in.pdf fileToEmbed.xyz out.pdf [page]
 *                  
 * Title:           Embed files into a PDF
 *                  
 * Description:     Embed files into a PDF and attach them to the document or
 *                  attach a page.
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

package ToolboxFileEmbedding;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import java.time.Instant;
import java.time.OffsetDateTime;
import java.time.ZoneId;
import java.time.ZonedDateTime;

import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.annotations.FileAttachment;
import com.pdftools.toolbox.pdf.content.ColorSpace;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.content.Paint;
import com.pdftools.toolbox.pdf.content.ProcessColorSpaceType;
import com.pdftools.toolbox.pdf.content.Transparency;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.sys.FileStream.Mode;

public class ToolboxFileEmbedding {
    static void usage() {
        System.out.println("Usage: java toolboxfileembedding <inputPath> <fileToEmbed> <outputPath> [<page>]");
        System.out.println("       Example: in.pdf fileToEmbed.xyz out.pdf [page]");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 3) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String input = args[0];
            String fileToEmbed = args[1];
            String output = args[2];
            int page = (args.length == 4 ? Integer.parseInt(args[3]) : -1);

            try (// Open input document
                FileStream inStream = new FileStream(input, Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);

                // Create output document
                FileStream outStream = new FileStream(output, Mode.READ_WRITE_NEW);
                Document outDoc = Document.create(outStream, inDoc.getConformance(), null);
                )
            {
                // Copy document-wide data
                copyDocumentData(inDoc, outDoc);

                // Define page copy options
                PageCopyOptions copyOptions = new PageCopyOptions();

                // Copy all pages
                PageList inPageRange = inDoc.getPages().subList(0, inDoc.getPages().size());
                PageList copiedPages = PageList.copy(outDoc, inPageRange, copyOptions);
                outDoc.getPages().addAll(copiedPages);

                embedFile(outDoc, new File(fileToEmbed), page);
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

    
    private static void embedFile(Document outputDoc, File fileToEmbed, int pageNumber) throws Exception
    {
        try(
            // create file stream to read the file to embed
            FileStream fileStream = new FileStream(fileToEmbed, Mode.READ_ONLY);
            )
        {
            // create a file type depending on the file ending (e.g. "application/pdf")
            String fileEnding = fileToEmbed.getName().substring(fileToEmbed.getName().lastIndexOf(".") + 1);
            String type = "application/" + fileEnding;

            // get the modified date from the file
            Instant instant = Instant.ofEpochMilli(fileToEmbed.lastModified());
            ZonedDateTime zonedDateTime = ZonedDateTime.ofInstant(instant, ZoneId.systemDefault());
            OffsetDateTime dateTime = OffsetDateTime.from(zonedDateTime);

            // create a new FileReference
            FileReference fr = FileReference.create(outputDoc, fileStream, fileToEmbed.getName(), type, "", dateTime);

            // if a page is set, add a FileAttachment annotation to that page
            // otherwise, attach the file to the document
            if(pageNumber > 0 && pageNumber <= outputDoc.getPages().size())
            {        
                // get the page to create the annotation on
                Page page = outputDoc.getPages().get(pageNumber - 1);

                // Get the color space
                ColorSpace colorSpace = ColorSpace.createProcessColorSpace(outputDoc, ProcessColorSpaceType.RGB);

                // Choose the RGB color value
                double[] color = { 1.0, 0.0, 0.0 };
                Transparency transparency = new Transparency(1);

                // Create paint object
                Paint paint = Paint.create(outputDoc, colorSpace, color, transparency);

                // put the annotation in the center of the page
                Point point = new Point(page.getSize().getWidth() / 2, page.getSize().getHeight() / 2);

                // create a FileReference annotation and attach it to a page so the FireReference is visible on that page
                FileAttachment fa = FileAttachment.create(outputDoc, point, fr, paint);

                // add FileAttachment annotation to the page
                page.getAnnotations().add(fa);
            }
            else
            {
                // attach it to the document
                outputDoc.getPlainEmbeddedFiles().add(fr);
            }
        }
    }
}