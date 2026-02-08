/****************************************************************************
 *
 * File:            toolboxmergeandcreatetableofcontents.java
 *
 * Usage:           java toolboxmergeandcreatetableofcontents <inputPath> [<inputPath2> ...] <outputPath>
 *                  Example: in1.pdf in2.pdf out.pdf
 *                  
 * Title:           Merge multiple PDFs and create a table of contents page
 *                  
 * Description:     Merge several PDF documents to one and create a table of
 *                  contents page.
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

package ToolboxMergeAndCreateTableOfContents;

import java.util.stream.Collectors;
import java.io.File;
import java.io.IOException;
import java.util.AbstractMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.navigation.InternalLink;
import com.pdftools.toolbox.pdf.navigation.LocationZoomDestination;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.sys.Stream;

public class ToolboxMergeAndCreateTableOfContents {
    static void usage() {
        System.out.println("Usage: java toolboxmergeandcreatetableofcontents <inputPath> [<inputPath2> ...] <outputPath>");
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

            String[] inPaths = new String[args.length - 1];
            for (int i = 0; i < args.length - 1; i++) {
                inPaths[i] = args[i];
            }

            try (
                // Open input document
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, null, null)) {

                    // Create embedded font in output document 
                    Font font = Font.createFromSystem(outDoc, "Arial", "", true);

                    // Configure page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    Set<Map.Entry<String, PageList>> copiedPageLists = new HashSet<>(inPaths.length);

                    // A page number counter
                    int pageNumber = 2;


                    // Copy all input documents pages
                    for (String inPath : inPaths) {
                        try (// Open input document
                            Stream inFs = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                            Document inDoc = Document.open(inFs, null)) {

                            // Copy all pages and append to output document
                            PageList copiedPages = PageList.copy(outDoc, inDoc.getPages(), copyOptions);

                            // Add page numbers to copied pages
                            for ( Page copiedPage : copiedPages)
                            {
                                addPageNumber(outDoc, copiedPage, font, pageNumber++);
                            }

                            // Hold the file name without extension
                            if (inPath == null)
                                continue;
                            // Get position of last '.'.
                            int pos = inPath.lastIndexOf(".");
                            // If there was a '.', hold the file name only
                            if (pos != -1) 
                                inPath = inPath.substring(0, pos);

                            // Create outline item
                            String title = (inDoc.getMetadata().getTitle() == null ? inPath : inDoc.getMetadata().getTitle());
                            copiedPageLists.add(new AbstractMap.SimpleEntry<String, PageList>(title, copiedPages));
                        }
                    }

                    // Create table of contents page
                    Page contentsPage = createTableOfContents(outDoc, copiedPageLists);
                    addPageNumber(outDoc, contentsPage, font, 1);

                    // Add pages to the output document
                    PageList outPages = outDoc.getPages();
                    outPages.add(contentsPage);
                    for (Map.Entry<String, PageList> entry : copiedPageLists)
                    {
                        outPages.addAll(entry.getValue());
                    }

                    System.out.println("Execution successful.");
                }
            }
        } 
        catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    private static void addPageNumber(Document outDoc, Page copiedPage, Font font, int pageNumber) throws ToolboxException, IOException
    {
        // Create content generator
        try (ContentGenerator generator = new ContentGenerator(copiedPage.getContent(), false)) {
            // Create text object
            Text text = Text.create(outDoc);

            // Create a text generator with the given font, size and position
            try (TextGenerator textgenerator = new TextGenerator(text, font, 8, null)) {
                // Generate string to be stamped as page number
                String stampText = String.format("Page %d", pageNumber);

                // Calculate position for centering text at bottom of page
                Point position = new Point();
                position.x = (copiedPage.getSize().getWidth() / 2) - (textgenerator.getWidth(stampText) / 2);
                position.y = 10;

                // Position the text
                textgenerator.moveTo(position);
                // Add page number
                textgenerator.show(stampText);
            }

            // Paint the positioned text
            generator.paintText(text);
        }
    }

    private static Page createTableOfContents(Document outDoc, Set<Map.Entry<String, PageList>> copiedPageLists) throws IOException, ToolboxException
    {
        // Create a new page with size equal to the first page copied
        Page page = Page.create(outDoc, copiedPageLists.iterator().next().getValue().get(0).getSize());

        // Create a font
        Font font = Font.createFromSystem(outDoc, "Arial", null, true);

        // Parameters for layout computation
        double border = 30;
        double textWidth = page.getSize().getWidth() - 2 * border;
        double chapterTitleSize = 24;
        double titleSize = 12;

        // The current text location
        Point location = new Point();
        location.x = border;
        location.y = page.getSize().getHeight() - border - chapterTitleSize;

        // The page number of the current item in the table of content
        int pageNumber = 2;

        // Creat a content generator for the table of contents page
        try (ContentGenerator contentGenerator = new ContentGenerator(page.getContent(), false)) {
            // Create a text object
            Text text = Text.create(outDoc);

            // Create a text generator to generate the table of contents. Initially, use the chapter title font size
            try (TextGenerator textGenerator = new TextGenerator(text, font, chapterTitleSize, location)) {
                // Show a chapter title
                textGenerator.showLine("Table of Contents");

                // Advance the vertical position
                location.y -= 1.7 * chapterTitleSize;

                // Select the font size for an entry in the table of contents
                textGenerator.setFontSize(titleSize);

                // Iterate over all copied page ranges
                for (Map.Entry<String, PageList> entry : copiedPageLists)
                {
                    // The title string for the current entry
                    String title = entry.getKey();

                    // The page number string of the target page for this entry
                    String pageNumberString = String.format("%d", pageNumber);

                    // The width of the page number string
                    double pageNumberWidth = textGenerator.getWidth(pageNumberString);

                    // Compute the number of filler dots to be displayed between the entry title and the page number
                    int numberOfDots = (int)Math.floor((textWidth - textGenerator.getWidth(title) - pageNumberWidth) / textGenerator.getWidth("."));

                    // Move to the current location and show the entry's title and the filler dots
                    textGenerator.moveTo(location);
                    String dots = new String();
                    for (int i = 0; i < numberOfDots; i++)
                    {
                        dots += '.';
                    }
                    textGenerator.show(title + dots);

                    // Show the page number
                    Point point = new Point();
                    point.x = page.getSize().getWidth() - border - pageNumberWidth;
                    point.y = location.y;
                    textGenerator.moveTo(point);
                    textGenerator.show(pageNumberString);

                    // Compute the rectangle for the link
                    Rectangle linkRectangle = new Rectangle();
                    linkRectangle.setLeft(border);
                    linkRectangle.setBottom(location.y + font.getDescent() * titleSize);
                    linkRectangle.setRight(border + textWidth);
                    linkRectangle.setTop(location.y + font.getAscent() * titleSize);

                    // Create a destination to the first page of the current page range and create a link for this destination
                    PageList pageList = entry.getValue();
                    Page targetPage = pageList.get(0);
                    LocationZoomDestination destination = LocationZoomDestination.create(outDoc, targetPage, (double) 0, targetPage.getSize().getHeight(), null);
                    InternalLink link = InternalLink.create(outDoc, linkRectangle, destination);

                    // Add the link to the table of contents page
                    page.getLinks().add(link);

                    // Advance the location for the next entry
                    location.y -= 1.8 * titleSize;
                    pageNumber += pageList.size();
                }
            }

            // Paint the generated text
            contentGenerator.paintText(text);
        }

        // Return the finished table-of-contents page
        return page;
    }
}
