/****************************************************************************
 *
 * File:            toolboxremoveglyphs.java
 *
 * Usage:           java toolboxremoveglyphs <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Remove glyphs
 *                  
 * Description:     Remove the first two glyphs from every text fragment.
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

package ToolboxRemoveGlyphs;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.content.Content;
import com.pdftools.toolbox.pdf.content.ContentElement;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.content.GroupElement;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextElement;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxRemoveGlyphs {

    static void usage() {
        System.out.println("Usage: java toolboxremoveglyphs <inputPath> <outputPath>");
        System.out.println("       Example: in.pdf out.pdf");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inPath = args[0];
            String outPath = args[1];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Process each page
                    for (Page inPage : inDoc.getPages()) {
                        // Create empty output page
                        Page outPage = Page.create(outDoc, inPage.getSize());
                        // Copy page content from input to output and remove glyphs
                        copyContentAndRemoveGlyphs(inPage.getContent(), outPage.getContent(), outDoc);
                        // Add the new page to the output document's page list
                        outDoc.getPages().add(outPage);
                    }
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
    private static void copyDocumentData(Document inDoc, Document outDoc) throws ToolboxException, IOException {
        // Copy document-wide data

        // Output intent
        if (inDoc.getOutputIntent() != null)
            outDoc.setOutputIntent(IccBasedColorSpace.copy(outDoc, inDoc.getOutputIntent()));

        // Metadata
        outDoc.setMetadata(Metadata.copy(outDoc, inDoc.getMetadata()));

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

    private static void copyContentAndRemoveGlyphs(Content inContent, Content outContent, Document outDoc) throws ToolboxException, IOException {
        // Use a content extractor and a content generator to copy content
        ContentExtractor extractor = new ContentExtractor(inContent);
        try (ContentGenerator generator = new ContentGenerator(outContent, false)) {
            // Iterate over all content elements
            for (ContentElement inElement : extractor) {
                ContentElement outElement = null;
                // Special treatment for group elements
                if (inElement instanceof GroupElement) {
                    GroupElement inGroupElement = (GroupElement)inElement;
                    // Create empty output group element
                    GroupElement outGroupElement = GroupElement.copyWithoutContent(outDoc, inGroupElement);
                    outElement = outGroupElement;
                    // Call copyContentAndRemoveGlyphs() recursively for the group element's content
                    copyContentAndRemoveGlyphs(inGroupElement.getGroup().getContent(), outGroupElement.getGroup().getContent(), outDoc);
                } else {
                    // Copy the content element to the output document
                    outElement = ContentElement.copy(outDoc, inElement);
                    if (outElement instanceof TextElement) {
                        // Special treatment for text element
                        TextElement outTextElement = (TextElement)outElement;
                        Text text = outTextElement.getText();
                        // Remove the first two glyphs from each text fragment
                        for (int iFragment = 0; iFragment < text.size(); ++iFragment) {
                            // Ensure that the fragment has more than two glyphs
                            if (text.get(iFragment).size() > 2) {
                                // Call remove twice
                                text.get(iFragment).remove(0);
                                text.get(iFragment).remove(0);
                            }
                        }
                    }
                }
                // Append the finished output element to the content generator
                generator.appendContentElement(outElement);
            }
        }
    }
}