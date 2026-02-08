/****************************************************************************
 *
 * File:            toolboxmergewithoutlines.java
 *
 * Usage:           java toolboxmergewithoutlines <inputPath> [<inputPath2> ...] <outputPath>
 *                  Example: in1.pdf in2.pdf out.pdf
 *                  
 * Title:           Merge multiple PDFs with outlines
 *                  
 * Description:     Merge several PDF documents to one, while creating an
 *                  outline item for each input document.
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

package ToolboxMergeWithOutlines;

import java.util.stream.Collectors;

import java.io.File;
import java.nio.file.Paths;
import java.util.Arrays;

import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.pdf.navigation.Destination;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.navigation.LocationZoomDestination;
import com.pdftools.toolbox.pdf.navigation.OutlineCopyOptions;
import com.pdftools.toolbox.pdf.navigation.OutlineItem;
import com.pdftools.toolbox.pdf.navigation.OutlineItemList;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;

public class ToolboxMergeWithOutlines {
    static void usage() {
        System.out.println("Usage: java toolboxmergewithoutlines <inputPath> [<inputPath2> ...] <outputPath>");
        System.out.println("       Example: in1.pdf in2.pdf out.pdf");

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

            String outPath = args[args.length - 1];
            String[] inPaths = Arrays.copyOfRange(args, 0, args.length - 1);

            try (
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, null, null)) {
                    // Define page copy options, skip outline
                    PageCopyOptions pageCopyOptions = new PageCopyOptions();
                    pageCopyOptions.setCopyOutlineItems(false);

                    // Define outline copy options
                    OutlineCopyOptions outlineCopyOptions = new OutlineCopyOptions();

                    // Get output pages
                    PageList outPages = outDoc.getPages();

                    // Merge input document
                    for (String inPath : inPaths) {
                        try (// Open input document
                            FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                            Document inDoc = Document.open(inStream, null)) {

                            // Copy all pages and append to output document
                            PageList copiedPages = PageList.copy(outDoc, inDoc.getPages(), pageCopyOptions);
                            outPages.addAll(copiedPages);

                            // Create outline item
                            String title = inDoc.getMetadata().getTitle();
                            if (title == null)
                                title = Paths.get(inPath).getFileName().toString();
                            Page firstCopiedPage = copiedPages.get(0);
                            Destination destination = LocationZoomDestination.create(outDoc, firstCopiedPage, 0.0,
                                    firstCopiedPage.getSize().getHeight(), null);
                            OutlineItem outlineItem = OutlineItem.create(outDoc, title, destination);
                            outDoc.getOutline().add(outlineItem);

                            // Add outline items from input document as children
                            OutlineItemList children = outlineItem.getChildren();
                            for (OutlineItem inputOutline : inDoc.getOutline())
                                children.add(OutlineItem.copy(outDoc, inputOutline, outlineCopyOptions));
                        }
                    }
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
}