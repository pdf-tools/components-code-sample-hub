/****************************************************************************
 *
 * File:            toolboxprinttoc.java
 *
 * Usage:           java toolboxprinttoc <inputPath>
 *                  
 * Title:           Print a table of content
 *                  
 * Description:     Print a formatted table of content from the document
 *                  outline.
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

package ToolboxPrintTOC;

import java.util.stream.Collectors;

import java.io.File;
import java.util.Arrays;
import java.lang.Integer;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.navigation.Destination;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.navigation.OutlineItem;
import com.pdftools.toolbox.pdf.navigation.OutlineItemList;

public class ToolboxPrintTOC {
    static void usage() {
        System.out.println("Usage: java toolboxprinttoc <inputPath>");
    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 1 || args.length > 1) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inPath = args[0];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null)) {
                printOutlineItems(inDoc.getOutline(), "", inDoc);
            }

            System.out.println("Execution successful.");

        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    static void printOutlineItem(OutlineItem item, String indentation, Document document) throws ToolboxException {
        String title = item.getTitle();
        System.out.format("%s%s", indentation, title);
        Destination dest = item.getDestination();
        if (dest != null) {
            int pageNumber = document.getPages().indexOf(dest.getTarget().getPage()) + 1;
            char[] dots = new char[78 - indentation.length() - title.length() - Integer.toString(pageNumber).length()];
            Arrays.fill(dots, '.');
            System.out.format(" %s %d", new String(dots), pageNumber);
        }
        System.out.println();
        printOutlineItems(item.getChildren(), indentation + "  ", document);
    }


    static void printOutlineItems(OutlineItemList outlineItems, String indentation, Document document)
            throws ToolboxException {
        for (OutlineItem item : outlineItems)
            printOutlineItem(item, indentation, document);
    }
}