/****************************************************************************
 *
 * File:            toolboxlistcontentbounds.java
 *
 * Usage:           java toolboxlistcontentbounds <inputPath>
 *                  
 * Title:           List bounds of page content
 *                  
 * Description:     For each page, list the page size and the rectangular
 *                  bounding box of all content on the page in PDF points
 *                  (1/72 inch).
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

package ToolboxListContentBounds;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.geometry.real.Size;
import com.pdftools.toolbox.pdf.content.ContentElement;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.geometry.real.AffineTransform;

public class ToolboxListContentBounds {
    static void usage() {
        System.out.println("Usage: java toolboxlistcontentbounds <inputPath>");
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

            String path = args[0];

            try (// Open input document
                FileStream stream = new FileStream(path, FileStream.Mode.READ_ONLY);
                Document doc = Document.open(stream, null)) {
                // Iterate over all pages
                int pageNumber = 1;
                for (Page page : doc.getPages()) {
                    // Print page size
                    System.out.format("Page %d\n", pageNumber++);
                    Size size = page.getSize();
                    System.out.println("  Size:");
                    System.out.format("    Width: %f\n", size.getWidth());
                    System.out.format("    Height: %f\n", size.getHeight());

                    // Compute rectangular bounding box of all content on page
                    Rectangle contentBox = new Rectangle(Double.MAX_VALUE, Double.MAX_VALUE, Double.MIN_VALUE, Double.MIN_VALUE);
                    ContentExtractor extractor = new ContentExtractor(page.getContent());
                    for (ContentElement element : extractor) {
                        // Enlarge the content box for each content element
                        AffineTransform tr = element.getTransform();
                        Rectangle box = element.getBoundingBox();

                        // The location on the page is given by the transformed points
                        contentBox = enlarge(contentBox, tr.transformPoint(new Point(box.getLeft(), box.getBottom())));
                        contentBox = enlarge(contentBox, tr.transformPoint(new Point(box.getRight(), box.getBottom())));
                        contentBox = enlarge(contentBox, tr.transformPoint(new Point(box.getRight(), box.getTop())));
                        contentBox = enlarge(contentBox, tr.transformPoint(new Point(box.getLeft(), box.getTop())));
                    }
                    System.out.println("  Content bounding box:");
                    System.out.format("    Left: %f\n", contentBox.getLeft());
                    System.out.format("    Bottom: %f\n", contentBox.getBottom());
                    System.out.format("    Right: %f\n", contentBox.getRight());
                    System.out.format("    Top: %f\n", contentBox.getTop());
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    static Rectangle enlarge(Rectangle box, Point point) {
        // Enlarge box if point lies outside of box
        if (point.getX() < box.getLeft())
            box.setLeft(point.getX());
        else if (point.getX() > box.getRight())
            box.setRight(point.getX());
        if (point.getY() < box.getBottom())
            box.setBottom(point.getY());
        else if (point.getY() > box.getTop())
            box.setTop(point.getY());
        return box;
    }
}