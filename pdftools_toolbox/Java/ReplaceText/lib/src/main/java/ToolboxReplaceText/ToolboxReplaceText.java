/****************************************************************************
 *
 * File:            toolboxreplacetext.java
 *
 * Usage:           java toolboxreplacetext <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Replace text fragment in PDF
 *                  
 * Description:     For a given text, search through all text fragments on
 *                  all pages and replace the first matching fragment found.
 *                  Links, annotations, form fields, outlines, and logical
 *                  structure are discarded.
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

package ToolboxReplaceText;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;

import com.pdftools.toolbox.CorruptException;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.geometry.real.AffineTransform;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.content.Content;
import com.pdftools.toolbox.pdf.content.ContentElement;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.content.GroupElement;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextElement;
import com.pdftools.toolbox.pdf.content.TextFragment;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxReplaceText {

    // Information about the found text fragment
    static AffineTransform overallTransform;
    static TextFragment fragment = null;

    static void usage() {
        System.out.println("Usage: java toolboxreplacetext <inputPath> <outputPath>");
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
            String searchString = "Muster Company AG";
            String replString = "Replacement String";
            overallTransform = AffineTransform.getIdentity();

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
                        // Copy page content from input to output and search for string
                        copyContent(inPage.getContent(), outPage.getContent(), outDoc, searchString);
                        // If the text was found and deleted, add the replacement text
                        if (fragment != null)
                            addText(outDoc, outPage, replString);
                        // Add page to output document
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

    private static void copyContent(Content inContent, Content outContent, Document outDoc, String searchString) throws ToolboxException, IOException {
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
                    // Save transform for later restor
                    AffineTransform currentTransform = overallTransform;
                    // Update the transform
                    overallTransform.concatenate(inGroupElement.getTransform());
                    // Call copyContent() recursively for the group element's content
                    copyContent(inGroupElement.getGroup().getContent(), outGroupElement.getGroup().getContent(), outDoc, searchString);
                    // Restor the transform
                    overallTransform = currentTransform;
                } else {
                    // Copy the content element to the output document
                    outElement = ContentElement.copy(outDoc, inElement);
                    if (fragment == null && outElement instanceof TextElement) {
                        // Special treatment for text element
                        TextElement outTextElement = (TextElement)outElement;
                        Text text = outTextElement.getText();
                        // Find text fragment with string to replace
                        for (int iFragment = text.size() - 1; iFragment >= 0; iFragment--) {
                            // In this sample, the fragment text must match in its entirety
                            if (text.get(iFragment).getText().equals(searchString)) {
                                // Keep the found fragment for later use
                                fragment = text.get(iFragment);
                                // Update the transform
                                overallTransform.concatenate(fragment.getTransform());
                                // Remove the found text fragment from the output
                                text.remove(iFragment);
                                break;
                            }
                        }
                        // Prevent appending an empty text element
                        if (text.size() == 0)
                            outElement = null;
                    }
                }
                // Append the finished output element to the content generator
                if (outElement != null)
                    generator.appendContentElement(outElement);
            }
        }
    }

    private static void addText(Document doc, Page page, String replString) throws CorruptException, ToolboxException, IOException {
        // Create a new text object
        Text text = Text.create(doc);
        // Heuristic to map the extracted fon base name to a font family and font style
        String[] parts = fragment.getFont().getBaseFont().split("-");
        String family = parts[0];
        String style = parts.length > 1 ? parts[1] : null;
        // Create a new font object
        Font font = Font.createFromSystem(doc, family, style, true);
        // Create a text generator and set the original fragment's properties
        try (TextGenerator textGenerator = new TextGenerator(text, font, fragment.getFontSize(), null)) {
            textGenerator.setCharacterSpacing(fragment.getCharacterSpacing());
            textGenerator.setWordSpacing(fragment.getWordSpacing());
            textGenerator.setHorizontalScaling(fragment.getHorizontalScaling());
            textGenerator.setRise(fragment.getRise());
            textGenerator.show(replString);
        }
        // Create a content generator
        try (ContentGenerator contentGenerator = new ContentGenerator(page.getContent(), false)) {
            // Apply the computed transform
            contentGenerator.transform(overallTransform);
            // Paint the new text
            contentGenerator.paintText(text);
        }
    }
}