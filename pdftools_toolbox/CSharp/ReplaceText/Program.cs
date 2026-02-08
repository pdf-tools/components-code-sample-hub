/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxReplaceText <inputPath> <outputPath>
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

using System;
using System.IO;
using System.Linq;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxReplaceText
{
    class Program
    {
        // Information about the found text fragment
        static AffineTransform overallTransform = AffineTransform.Identity;
        static TextFragment fragment;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxReplaceText <inputPath> <outputPath>");
            Console.WriteLine("       Example: in.pdf out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2 || args.Length > 2)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];
                string outPath = args[1];
                string searchString = "Muster Company AG";
                string replString = "Replacement String";

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Process each page
                    foreach (var inPage in inDoc.Pages)
                    {
                        // Create empty output page
                        Page outPage = Page.Create(outDoc, inPage.Size);
                        // Copy page content from input to output and search for string
                        CopyContent(inPage.Content, outPage.Content, outDoc, searchString);
                        // If the text was found and deleted, add the replacement text
                        if (fragment != null)
                            AddText(outDoc, outPage, replString);
                        // Add the new page to the output document's page list
                        outDoc.Pages.Add(outPage);
                    }
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        private static void CopyDocumentData(Document inDoc, Document outDoc)
        {
            // Copy document-wide data

            // Output intent
            if (inDoc.OutputIntent != null)
                outDoc.OutputIntent = IccBasedColorSpace.Copy(outDoc, inDoc.OutputIntent);

            // Metadata
            outDoc.Metadata = Metadata.Copy(outDoc, inDoc.Metadata);

            // Viewer settings
            outDoc.ViewerSettings = ViewerSettings.Copy(outDoc, inDoc.ViewerSettings);

            // Associated files (for PDF/A-3 and PDF 2.0 only)
            FileReferenceList outAssociatedFiles = outDoc.AssociatedFiles;
            foreach (FileReference inFileRef in inDoc.AssociatedFiles)
                outAssociatedFiles.Add(FileReference.Copy(outDoc, inFileRef));

            // Plain embedded files
            FileReferenceList outEmbeddedFiles = outDoc.PlainEmbeddedFiles;
            foreach (FileReference inFileRef in inDoc.PlainEmbeddedFiles)
                outEmbeddedFiles.Add(FileReference.Copy(outDoc, inFileRef));
        }

        private static void CopyContent(Content inContent, Content outContent, Document outDoc, string searchString)
        {
            // Use a content extractor and a content generator to copy content
            ContentExtractor extractor = new ContentExtractor(inContent);
            using ContentGenerator generator = new ContentGenerator(outContent, false);

            // Iterate over all content elements
            foreach (ContentElement inElement in extractor)
            {
                ContentElement outElement;
                // Special treatment for group elements
                if (inElement is GroupElement inGroupElement)
                {
                    // Create empty output group element
                    GroupElement outGroupElement = GroupElement.CopyWithoutContent(outDoc, inGroupElement);
                    outElement = outGroupElement;
                    // Save transform for later restore
                    AffineTransform currentTransform = overallTransform;
                    // Update the transform
                    overallTransform.Concatenate(inGroupElement.Transform);
                    // Call CopyContent() recursively for the group element's content
                    CopyContent(inGroupElement.Group.Content, outGroupElement.Group.Content, outDoc, searchString);
                    // Restore the transform
                    overallTransform = currentTransform;
                }
                else
                {
                    // Copy the content element to the output document
                    outElement = ContentElement.Copy(outDoc, inElement);
                    if (fragment == null && outElement is TextElement outTextElement)
                    {
                        // Special treatment for text element
                        Text text = outTextElement.Text;
                        // Find text fragment with string to replace
                        for (int iFragment = text.Count - 1; iFragment >= 0; iFragment--)
                        {
                            // In this sample, the fragment text must match in its entirety
                            if (text[iFragment].Text == searchString)
                            {
                                // Keep the found fragment for later use
                                fragment = text[iFragment];
                                // Update the transform
                                overallTransform.Concatenate(fragment.Transform);
                                // Remove the found text fragment from the output
                                text.RemoveAt(iFragment);
                                break;
                            }
                        }
                        // Prevent appending an empty text element
                        if (text.Count == 0)
                            outElement = null;
                    }
                }
                // Append the finished output element to the content generator
                if (outElement != null)
                    generator.AppendContentElement(outElement);
            }
        }

        private static void AddText(Document doc, Page page, string replString)
        {
            // Create a new text object
            Text text = Text.Create(doc);
            // Heuristic to map the extracted font base name to a font name and font family
            string[] parts = fragment.Font.BaseFont.Split('-');
            string family = parts[0];
            string style = parts.Length > 1 ? parts[1] : null;
            // Create a new font object
            Font font = Font.CreateFromSystem(doc, family, style, true);
            // Create a text generator and set the original fragment's properties
            using (TextGenerator textGenerator = new TextGenerator(text, font, fragment.FontSize, null))
            {
                textGenerator.CharacterSpacing = fragment.CharacterSpacing;
                textGenerator.WordSpacing = fragment.WordSpacing;
                textGenerator.HorizontalScaling = fragment.HorizontalScaling;
                textGenerator.Rise = fragment.Rise;
                textGenerator.Show(replString);
            }
            // Create a content generator
            using ContentGenerator contentGenerator = new ContentGenerator(page.Content, false);
            // Apply the computed transform
            contentGenerator.Transform(overallTransform);
            // Paint the new text
            contentGenerator.PaintText(text);
        }
    }
}