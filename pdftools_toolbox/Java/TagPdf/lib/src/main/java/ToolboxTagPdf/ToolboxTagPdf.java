/****************************************************************************
 *
 * File:            toolboxtagpdf.java
 *
 * Usage:           java toolboxtagpdf <inPath> <outPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Tag existing PDF content
 *                  
 * Description:     Copy content from an existing PDF, then apply logical
 *                  structure (tags) to selected elements.
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

package ToolboxTagPdf;

import java.util.stream.Collectors;

import java.util.stream.Collectors;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.File;

import com.pdftools.toolbox.NotFoundException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.UnsupportedFeatureException;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.Content;
import com.pdftools.toolbox.pdf.content.ContentElement;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.GroupElement;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.content.Image;
import com.pdftools.toolbox.pdf.content.ImageElement;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextElement;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.structure.Node;
import com.pdftools.toolbox.pdf.structure.Tree;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.geometry.real.Quadrilateral;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.geometry.integer.Size;

public class ToolboxTagPdf {
    static void usage() {
        System.out.println("Usage: java toolboxtagpdf <inPath> <outPath>");
        System.out.println("       Example: in.pdf out.pdf");

    }

    public static void main(String[] args) throws Exception {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        Sdk.initialize("LICENSE-KEY", null);

        String inPath = args[0];
        String outPath = args[1];

        try (FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStream, null);
            FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);
            Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

            // Copy document-wide data
            copyDocumentData(inDoc, outDoc);

            outDoc.setLanguage("en");
            outDoc.setPdfUaConformant();
            outDoc.getMetadata().setTitle("TaggedPDF");
            outDoc.getViewerSettings().setDisplayDocumentTitle(true);

            // Create empty output page
            Page inPage = inDoc.getPages().get(0);
            Page outPage = Page.create(outDoc, inPage.getSize());

            // We create an output page and copy the content elements from the input page to the output page.
            // While copying, we also check if the current element is the one we want to tag.
            // If it is, we tag it and update the logical structure accordingly.
            // You can easily adapt this sample to fit similar scenarios.
            copyAndTagContent(inPage, outPage, outDoc);
            outDoc.getPages().add(outPage);
        }

        System.out.println("Execution successful.");
    }

    private static void copyDocumentData(Document inDoc, Document outDoc) throws Exception {
        // Copy output intent
        if (inDoc.getOutputIntent() != null)
            outDoc.setOutputIntent(IccBasedColorSpace.copy(outDoc, inDoc.getOutputIntent()));

        // Copy metadata
        outDoc.setMetadata(Metadata.copy(outDoc, inDoc.getMetadata()));

        // Copy viewer settings
        outDoc.setViewerSettings(ViewerSettings.copy(outDoc, inDoc.getViewerSettings()));

        // Copy associated files
        FileReferenceList outAssociatedFiles = outDoc.getAssociatedFiles();
        for (FileReference inFileRef : inDoc.getAssociatedFiles()) {
            outAssociatedFiles.add(FileReference.copy(outDoc, inFileRef));
        }

        // Copy plain embedded files
        FileReferenceList outEmbeddedFiles = outDoc.getPlainEmbeddedFiles();
        for (FileReference inFileRef : inDoc.getPlainEmbeddedFiles()) {
            outEmbeddedFiles.add(FileReference.copy(outDoc, inFileRef));
        }
    }

    private static void copyAndTagContent(Page inPage, Page outPage, Document outDoc) throws ToolboxException, IOException {
        Tree structTree = new Tree(outDoc);
        Node documentNode = structTree.getDocumentNode();
        Node section = new Node("Sect", outDoc, outPage);
        documentNode.getChildren().add(section);

        Node p = new Node("P", outDoc, null);

        ContentExtractor extractor = new ContentExtractor(inPage.getContent());
        try (ContentGenerator generator = new ContentGenerator(outPage.getContent(), false)) {
            for (ContentElement inElement : extractor) {
                ContentElement outElement;

                if (inElement instanceof GroupElement) {
                    GroupElement inGroup = (GroupElement) inElement;
                    GroupElement outGroup = GroupElement.copyWithoutContent(outDoc, inGroup);
                    outElement = outGroup;
                    // Call CopyAndTagContent() recursively for the group element's content
                    copyAndTagContent(inPage, outPage, outDoc);
                } else {
                    outElement = ContentElement.copy(outDoc, inElement);

                    if (outElement instanceof TextElement) {
                        TextElement text = (TextElement) outElement;
                        String str = text.getText().get(0).getText();

                        if ("This is a properly tagged heading".equals(str)) {
                            copyAndTagTextElement(text, section, generator, outPage, outDoc, "H1");
                        } else if ("This is a properly tagged paragraph. Both heading and paragraph belong to a section.".equals(str)) {
                            p = copyAndTagTextElement(text, section, generator, outPage, outDoc, "P");
                        }else{
                            throw new RuntimeException("Unexpected content element found.");
                        }
                    } else if (outElement instanceof ImageElement) {
                        ImageElement image = (ImageElement) outElement;
                        Quadrilateral bbox = image.getTransform().transformRectangle(image.getBoundingBox());

                        if (Math.abs(bbox.getBottomLeft().getX() - 70.86) < 0.5 &&
                            Math.abs(bbox.getBottomLeft().getY() - 632.65) < 0.5 &&
                            Math.abs(bbox.getTopRight().getX() - 127.559) < 0.5 &&
                            Math.abs(bbox.getTopRight().getY() - 689.34) < 0.5) {

                            copyAndTagImageElement(image, p, generator, outPage, outDoc, "PdfTools AG Logo");
                        }else{
                            throw new RuntimeException("Unexpected content element found.");
                        }
                    } else {
                        throw new RuntimeException("Unexpected content element found.");
                    }
                }
            }
        }
    }

    private static void copyAndTagImageElement(ImageElement imageElement, Node parentNode, ContentGenerator generator,
                                        Page outPage, Document outDoc, String altText) throws NotFoundException, UnsupportedFeatureException {
        Node figure = new Node("Figure", outDoc, outPage);
        figure.setAlternateText(altText);

        figure.setLanguage("en");

        Quadrilateral bbox = imageElement.getTransform().transformRectangle(imageElement.getBoundingBox());
        Rectangle rectangle = new Rectangle();
        rectangle.setLeft(bbox.getBottomLeft().getX());
        rectangle.setBottom(bbox.getBottomLeft().getY());
        rectangle.setRight(bbox.getTopRight().getX());
        rectangle.setTop(bbox.getTopRight().getY());

        figure.setBoundingBox(rectangle);
        figure.setStringAttribute("O", "Layout");

        parentNode.getChildren().add(figure);

        generator.tagAs(figure);
        generator.appendContentElement(imageElement);
        generator.stopTagging();
    }

    private static Node copyAndTagTextElement(TextElement textElement, Node section, ContentGenerator generator,
                                       Page outPage, Document outDoc, String tag) throws NotFoundException, UnsupportedFeatureException {
        Node tagNode = new Node(tag, outDoc, outPage);
        tagNode.setActualText(textElement.getText().get(0).getText());
        section.getChildren().add(tagNode);

        tagNode.setLanguage("en");

        generator.tagAs(tagNode);
        generator.appendContentElement(textElement);
        generator.stopTagging();

        return tagNode;
    }

}
