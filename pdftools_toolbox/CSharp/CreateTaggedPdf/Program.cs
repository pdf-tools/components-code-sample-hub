/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxCreateTaggedPdf <imagePath> <outPath>
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

using System;
using System.IO;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Structure;


namespace ToolboxDocumentStructure
{
    class Program
    {

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxCreateTaggedPdf <imagePath> <outPath>");
            Console.WriteLine("       Example: PdfToolsLogo.png out.pdf");

        }

        // Look & Feel
        private static readonly double MARGIN = ToPoints(2.5, "cm");
        private static readonly double PADDING = ToPoints(1, "cm"); // Padding between elements

        private static readonly string[] ARIAL_AND_FALLBACKS =
        {
            "Arial", // Common on Windows, available on most systems
            "Liberation Sans", // Common on Linux
            "DejaVu Sans", // Common on Linux
            "Helvetica", // Common on macOS
            "sans-serif" // Generic fallback
        };

        struct NodeAndPosition
        {
            public double position { get; set; }
            public Node node { get; set; }

            public NodeAndPosition(double position, Node node)
            {
                this.position = position;
                this.node = node;
            }
        };

        public static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2 || args.Length > 2)
            {
                Usage();
                return;
            }

            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.Initialize("LICENSE-KEY", null);

            string imagePath = args[0];
            string outPath = args[1];

            // Check if image file exists
            if (!File.Exists(imagePath))
            {
                throw new FileNotFoundException(
                    "Image file not found: " + imagePath + "." +
                    "Please ensure the image file exists and the path is correct.");
            }


            // Create output document
            using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
            using (Document outDoc = Document.Create(outStream, Conformance.Pdf17, null))
            {
                // Create a font
                Font font = CreateFontWithFallbacks(outDoc, ARIAL_AND_FALLBACKS);

                outDoc.Language = "en";
                outDoc.SetPdfUaConformant();
                outDoc.Metadata.Title = "TaggedPDF";
                outDoc.ViewerSettings.DisplayDocumentTitle = true;

                // Create a page
                Size pageSize = new Size { Width = ToPoints(21, "cm"), Height = ToPoints(29.7, "cm") }; // DIN A4
                Page outPage = Page.Create(outDoc, pageSize);
                CreateAndTagContent(outDoc, outPage, imagePath, font);
                outDoc.Pages.Add(outPage);
            }

            Console.WriteLine("Execution successful.");

        }


        private static void CreateAndTagContent(Document outputDoc, Page outPage, string imagePath, Font font)
        {
            using (ContentGenerator gen = new ContentGenerator(outPage.Content, false))
            {
                Tree structTree = new Tree(outputDoc);
                Node docNode = structTree.DocumentNode;
                Node sectionNode = new Node("Sect", outputDoc, outPage);
                docNode.Children.Add(sectionNode);

                // Start from the top of the page with margin
                double currentY = outPage.Size.Height - MARGIN;

                // Create header
                NodeAndPosition np = CreateAndTagText(
                    outputDoc,
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
                np = CreateAndTagText(
                    outputDoc,
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
                CreateAndTagImage(outputDoc, outPage, gen, imagePath, currentY, np.node);
            }
        }

        /// <summary>
        /// Create and tag a text element (header, paragraph, etc.).
        /// </summary>
        /// <param name="outputDoc">The output document</param>
        /// <param name="outPage">The output page</param>
        /// <param name="gen">The content generator</param>
        /// <param name="sectionNode">The section node to add the text element to</param>
        /// <param name="font">The font to use</param>
        /// <param name="topY">Y coordinate for the top of this element</param>
        /// <param name="tagName">PDF structure tag name (e.g., "H1", "P")</param>
        /// <param name="textContent">The text content to display</param>
        /// <param name="fontSize">Font size in points</param>
        /// <returns>Bottom Y coordinate of this element and created node</returns>
        private static NodeAndPosition CreateAndTagText(
            Document outputDoc,
            Page outPage,
            ContentGenerator gen,
            Node sectionNode,
            Font font,
            double topY,
            string tagName,
            string textContent,
            double fontSize)
        {
            Node textNode = new Node(tagName, outputDoc, outPage);
            textNode.ActualText = textContent;
            textNode.Language = "en";
            gen.TagAs(textNode);
            Text text = Text.Create(outputDoc);
            sectionNode.Children.Add(textNode);

            // Calculate text baseline position
            double baselineY = topY - fontSize * font.Ascent;

            using (TextGenerator textGen = new TextGenerator(text, font, fontSize, null))
            {
                Point position = new Point { X = MARGIN, Y = baselineY };
                textGen.MoveTo(position);
                textGen.ShowLine(textNode.ActualText);
            }

            gen.PaintText(text);
            gen.StopTagging();

            // Return bottom coordinate (baseline - descent)
            return new NodeAndPosition(baselineY - fontSize * font.Descent, textNode);
        }

        /// <summary>
        /// Create and tag an image element.
        /// </summary>
        /// <param name="outputDoc">The output document</param>
        /// <param name="outPage">The output page</param>
        /// <param name="gen">The content generator</param>
        /// <param name="imagePath">Path to the image file</param>
        /// <param name="topY">Y coordinate for the top of this element</param>
        /// <param name="parent">Parent node</param>
        /// <returns>Bottom Y coordinate of this element</returns>
        private static double CreateAndTagImage(Document outputDoc, Page outPage, ContentGenerator gen,
            string imagePath, double topY, Node parent)
        { 
            Node figureNode = new Node("Figure", outputDoc, outPage);
            figureNode.AlternateText = "PdfTools AG Logo";
            parent.Children.Add(figureNode);

            figureNode.Language = "en";

            figureNode.SetStringAttribute("O", "Layout");

            gen.TagAs(figureNode);

            Image image;
            try
            {
                using (Stream inImage = new FileStream(imagePath, FileMode.Open, FileAccess.Read))
                {
                    image = Image.Create(outputDoc, inImage);
                }
            }
            catch (Exception e)
            {
                throw new InvalidOperationException(
                    "Failed to create image from file " + imagePath + ": " + e.Message + ". " +
                    "Please ensure the file is a valid image format (PNG, JPEG, etc.).");
            }

            double x = MARGIN;
            double width = ToPoints(2.0, "cm");
            double height = width * image.Size.Height / image.Size.Width; // preserve aspect ratio

            Rectangle rect = new Rectangle
            {
                Left = x, // left
                Bottom = topY - height, // bottom (Rectangle coordinates: bottom is lower than top)
                Right = x + width, // right
                Top = topY // top
            };

            figureNode.BoundingBox = rect;

            gen.PaintImage(image, rect);
            gen.StopTagging();

            // Return bottom coordinate
            return topY - height;
        }

        /// <summary>
        /// Try to create a font using common font names that are likely to be available
        /// on Windows, Linux, and Mac systems. Throws an exception if no font can be created.
        /// </summary>
        private static Font CreateFontWithFallbacks(Document document, string[] fontAndFallbacks)
        {
            foreach (string fontName in fontAndFallbacks)
            {
                try
                {
                    Font font = Font.CreateFromSystem(document, fontName, "", true);
                    if (font != null)
                    {
                        return font;
                    }
                }
                catch (Exception)
                {
                    // Try next font
                }
            }

            // If we get here, no font worked
            throw new InvalidOperationException(
                "Unable to create font. Tried the following fonts: " + string.Join(", ", fontAndFallbacks) + ". " +
                "Please ensure you have at least one of these fonts installed on your system.");
        }

        /// <summary>
        /// Convert measurement from inches or centimeters to points.
        /// </summary>
        /// <param name="value">The measurement value</param>
        /// <param name="unit">Unit of measurement ("in" for inches, "cm" for centimeters)</param>
        /// <returns>Value converted to points (1 inch = 72 points, 1 cm ≈ 28.35 points)</returns>
        private static double ToPoints(double value, string unit)
        {
            if (unit == "in")
            {
                return value * 72.0; // 1 inch = 72 points
            }
            else if (unit == "cm")
            {
                return value * 28.346456693; // 1 cm = 28.346456693 points (72/2.54)
            }
            else
            {
                throw new ArgumentException(
                    "Unsupported unit " + unit + ". Use 'in' for inches or 'cm' for centimeters.", nameof(unit));
            }
        }

    }
}