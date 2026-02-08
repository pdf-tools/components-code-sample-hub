/****************************************************************************
 *
 * File:            toolboxcreatetaggedpdf.java
 *
 * Usage:           java toolboxcreatetaggedpdf <imagePath> <outPath>
 *                  Example: PdfToolsLogo.png out.pdf
 *                  
 * Title:           Create tagged PDF
 *                  
 * Description:     Create a new PDF document, add content and apply logical
 *                  structure (tags) during content creation.
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

package ToolboxCreateTaggedPdf;

import java.util.stream.Collectors;

import java.io.File;

import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.pdf.Conformance;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.content.ContentGenerator;
import com.pdftools.toolbox.pdf.content.Font;
import com.pdftools.toolbox.pdf.content.Image;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextGenerator;
import com.pdftools.toolbox.pdf.structure.Node;
import com.pdftools.toolbox.pdf.structure.Tree;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Point;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.geometry.real.Size;

public class ToolboxCreateTaggedPdf {
    static void usage() {
        System.out.println("Usage: java toolboxcreatetaggedpdf <imagePath> <outPath>");
        System.out.println("       Example: PdfToolsLogo.png out.pdf");

    }

    // Look & Feel
    private static final double MARGIN = toPoints(2.5, "cm");
    private static final double PADDING = toPoints(1, "cm");
    private static final String[] ARIAL_AND_FALLBACKS = {
            "Arial",          // Common on Windows, available on most systems
            "Liberation Sans", // Common on Linux
            "DejaVu Sans",    // Common on Linux
            "Helvetica",      // Common on macOS
            "sans-serif"      // Generic fallback
    };

	static class NodeAndPosition{
		public Node node;
		public double position;

		public NodeAndPosition(Node node, double position) {
			this.node = node;
			this.position = position;
		}
	}

    public static void main(String[] args) throws Exception {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        Sdk.initialize("LICENSE-KEY", null);

        String imagePath = args[0];
        String outPath = args[1];

        // Check if image file exists
        File imageFile = new File(imagePath);
        if (!imageFile.isFile()) {
            throw new RuntimeException(
                    String.format("Image file not found: '%s'. " +
                            "Please ensure the image file exists and the path is correct.", imagePath)
            );
        }

        // Create a PDF document
        try (FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);
                 Document outDoc = Document.create(outStream, Conformance.PDF17, null)) {

            // Create a font
            Font font = createFontWithFallbacks(outDoc, ARIAL_AND_FALLBACKS);

            outDoc.setLanguage("en");
            outDoc.setPdfUaConformant();
            outDoc.getMetadata().setTitle("TaggedPDF");
            outDoc.getViewerSettings().setDisplayDocumentTitle(true);

            // Create a page
            Size pageSize = new Size(toPoints(21, "cm"), toPoints(29.7, "cm")); // DIN A4
            Page outPage = Page.create(outDoc, pageSize);
            createAndTagContent(outDoc, outPage, imagePath, font);
            outDoc.getPages().add(outPage);
        }

        System.out.println("Execution successful.");

    }


    private static void createAndTagContent(Document outDoc, Page outPage, String imagePath, Font font) throws Exception {
        try (ContentGenerator gen = new ContentGenerator(outPage.getContent(), false)) {
            Tree structTree = new Tree(outDoc);
            Node docNode = structTree.getDocumentNode();
            Node sectionNode = new Node("Sect", outDoc, outPage);
            docNode.getChildren().add(sectionNode);

            // Start from the top of the page with margin
            double currentY = outPage.getSize().getHeight() - MARGIN;

            // Create header
            NodeAndPosition np = createAndTagText(
                    outDoc,
                    outPage,
                    gen,
                    sectionNode,
                    font,
                    currentY,
                    "H1",
                    "This is a properly tagged heading",
                    24.0
            );

            // Add padding and create paragraph
            currentY = np.position;
            currentY -= PADDING;
            np = createAndTagText(
                    outDoc,
                    outPage,
                    gen,
                    sectionNode,
                    font,
                    currentY,
                    "P",
                    "This is a properly tagged paragraph. Both heading and paragraph belong to a section.",
                    12.0
            );

            // Add padding and create image
            currentY = np.position;
            currentY -= PADDING;
            createAndTagImage(outDoc, outPage, gen, imagePath, currentY, np.node);
        }
    }

    /**
     * Create and tag a text element (header, paragraph, etc.).
     *
     * @param outDoc      The output document
     * @param outPage     The output page
     * @param gen         The content generator
     * @param sectionNode The section node to add the text element to
     * @param font        The font to use
     * @param topY        Y coordinate for the top of this element
     * @param tagName     PDF structure tag name (e.g., "H1", "P")
     * @param textContent The text content to display
     * @param fontSize    Font size in points
     * @return Bottom Y coordinate of this element and created node
     */
    private static NodeAndPosition createAndTagText(
            Document outDoc,
            Page outPage,
            ContentGenerator gen,
            Node sectionNode,
            Font font,
            double topY,
            String tagName,
            String textContent,
            double fontSize) throws Exception {

        Node textNode = new Node(tagName, outDoc, outPage);
        textNode.setActualText(textContent);
        textNode.setLanguage("en");
        gen.tagAs(textNode);
        Text text = Text.create(outDoc);
        sectionNode.getChildren().add(textNode);

        // Calculate text baseline position
        double baselineY = topY - fontSize * font.getAscent();

        try (TextGenerator textGen = new TextGenerator(text, font, fontSize, null)) {
            Point position = new Point(MARGIN, baselineY);
            textGen.moveTo(position);
            textGen.showLine(textNode.getActualText());
        }
        gen.paintText(text);
        gen.stopTagging();

        // Return bottom coordinate (baseline - descent)
        return new NodeAndPosition(textNode, baselineY - fontSize * font.getDescent());
    }

    /**
     * Create and tag an image element.
     *
     * @param outDoc    The output document
     * @param outPage   The output page
     * @param gen       The content generator
     * @param imagePath Path to the image file
     * @param topY      Y coordinate for the top of this element
     * @param parent    Parent node
     * @return Bottom   Y coordinate of this element
     */
    private static double createAndTagImage(
            Document outDoc,
            Page outPage,
            ContentGenerator gen,
            String imagePath,
            double topY, Node parent) throws Exception {

        Node figureNode = new Node("Figure", outDoc, outPage);
        figureNode.setAlternateText("PdfTools AG Logo");
        gen.tagAs(figureNode);

        figureNode.setLanguage("en");
        figureNode.setStringAttribute("O", "Layout");

        Image image;
        try (FileStream inImage = new FileStream(imagePath, FileStream.Mode.READ_ONLY)) {
            image = Image.create(outDoc, inImage);
        } catch (Exception e) {
            throw new RuntimeException(
                    String.format("Failed to create image from file '%s': %s. " +
                                    "Please ensure the file is a valid image format (PNG, JPEG, etc.).",
                            imagePath, e.getMessage())
            );
        }

        double x = MARGIN;
        double width = toPoints(2.0, "cm");
        double height = width * image.getSize().getHeight() / image.getSize().getWidth(); // preserve aspect ratio

        Rectangle rect = new Rectangle(
                x,                    // left
                topY - height,        // bottom (Rectangle coordinates: bottom is lower than top)
                x + width,            // right
                topY                  // top
        );

        figureNode.setBoundingBox(rect);

        parent.getChildren().add(figureNode);

        gen.paintImage(image, rect);
        gen.stopTagging();

        // Return bottom coordinate
        return topY - height;
    }

    /**
     * Try to create a font using common font names that are likely to be available
     * on Windows, Linux, and Mac systems. Throws an exception if no font can be created.
     */
    private static Font createFontWithFallbacks(Document document, String[] fontAndFallbacks) {
        for (String fontName : fontAndFallbacks) {
            try {
                Font font = Font.createFromSystem(document, fontName, "", true);
                if (font != null) {
                    return font;
                }
            } catch (Exception e) {
                // Try next font
            }
        }

        // If we get here, no font worked
        throw new RuntimeException(
                String.format("Unable to create font. Tried the following fonts: %s. " +
                                "Please ensure you have at least one of these fonts installed on your system.",
                        String.join(", ", ARIAL_AND_FALLBACKS))
        );
    }

    /**
     * Convert measurement from inches or centimeters to points.
     *
     * @param value The measurement value
     * @param unit  Unit of measurement ("in" for inches, "cm" for centimeters)
     * @return Value converted to points (1 inch = 72 points, 1 cm ≈ 28.35 points)
     */
    private static double toPoints(double value, String unit) {
        if ("in".equals(unit)) {
            return value * 72.0; // 1 inch = 72 points
        } else if ("cm".equals(unit)) {
            return value * 28.346456693; // 1 cm = 28.346456693 points (72/2.54)
        } else {
            throw new IllegalArgumentException(
                    String.format("Unsupported unit '%s'. Use 'in' for inches or 'cm' for centimeters.", unit)
            );
        }
    }
}
