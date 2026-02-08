/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxTagPdf <inPath> <outPath>
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

using System;
using System.IO;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;
using PdfTools.Toolbox.Pdf.Structure;
using PdfTools.Toolbox.Geometry.Real;

namespace ToolboxDocumentStructure
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxTagPdf <inPath> <outPath>");
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

            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.Initialize("LICENSE-KEY", null);

            string inPath = args[0];
            string outPath = args[1];


            // Open input document
            using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
            using (Document inDoc = Document.Open(inStream, null))

            // Create output document
            using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
            using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
            {
                // Copy document-wide data
                CopyDocumentData(inDoc, outDoc);

                outDoc.Language = "en";
                outDoc.SetPdfUaConformant();
                outDoc.Metadata.Title = "TaggedPDF";
                outDoc.ViewerSettings.DisplayDocumentTitle = true;

                // Create empty output page
                Page inPage = inDoc.Pages[0];
                Page outPage = Page.Create(outDoc, inPage.Size);

                // We create an output page and copy the content elements from the input page to the output page.
                // While copying, we also check if the current element is the one we want to tag.
                // If it is, we tag it and update the logical structure accordingly.
                // You can easily adapt this sample to fit similar scenarios.
                CopyAndTagContent(inPage, outPage, outDoc);
                outDoc.Pages.Add(outPage);
            }

            Console.WriteLine("Execution successful.");
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

        private static void CopyAndTagContent(Page inPage, Page outPage, Document outDoc)
        {
            var structTree = new Tree(outDoc);
            var documentNode = structTree.DocumentNode;
            var section = new Node("Sect", outDoc, outPage);
            documentNode.Children.Add(section);

            // Use a content extractor and a content generator to copy content
            ContentExtractor extractor = new ContentExtractor(inPage.Content);
            using ContentGenerator generator = new ContentGenerator(outPage.Content, false);

            Node p = new Node("P", outDoc);

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
                    // Call CopyAndTagContent() recursively for the group element's content
                    CopyAndTagContent(inPage, outPage, outDoc);
                }
                else
                {
                    // Copy the content element to the output document
                    outElement = ContentElement.Copy(outDoc, inElement);
                    if (outElement is TextElement outTextElement)
                    {
                        if (outTextElement.Text[0].Text == "This is a properly tagged heading")
                        {
                            CopyAndTagTextElement(outTextElement, section, generator, outPage, outDoc, "H1");
                        }
                        else if (outTextElement.Text[0].Text == "This is a properly tagged paragraph. Both heading and paragraph belong to a section.")
                        {
                            p = CopyAndTagTextElement(outTextElement, section, generator, outPage, outDoc, "P");
                        }

                    }
                    else if (outElement is ImageElement imageElement)
                    {
                        var bbox = imageElement.Transform.TransformRectangle(outElement.BoundingBox);
                        if (Math.Abs(bbox.BottomLeft.X - 70.86) < 0.5 && Math.Abs(bbox.BottomLeft.Y - 632.65) < 0.5 && Math.Abs(bbox.TopRight.X - 127.559) < 0.5 && Math.Abs(bbox.TopRight.Y - 689.34) < 0.5)
                        {
                            CopyAndTagImageElement(imageElement, generator, outPage, outDoc, "PdfTools AG Logo", p);
                        }
                    }
                    else
                    {
                        throw new InvalidOperationException("Unexpected content element found.");
                    }
                }
            }
        }

        private static void CopyAndTagImageElement(ImageElement imageElement, ContentGenerator generator, Page outPage, Document outDoc, string alternateText, Node p)
        {
            Node imgElement = new Node("Figure", outDoc, outPage);

            imgElement.AlternateText = alternateText;
            imgElement.Language = "en";

            var bbox = imageElement.Transform.TransformRectangle(imageElement.BoundingBox);
            var rectangle = new Rectangle();
            rectangle.Left = bbox.BottomLeft.X;
            rectangle.Bottom = bbox.BottomLeft.Y;
            rectangle.Right = bbox.TopRight.X;
            rectangle.Top = bbox.TopRight.Y;

            imgElement.BoundingBox = rectangle;
            imgElement.SetStringAttribute("O", "Layout");

            p.Children.Add(imgElement);

            generator.TagAs(imgElement);

            generator.AppendContentElement(imageElement);

            generator.StopTagging();
        }

        private static Node CopyAndTagTextElement(TextElement textElement, Node section, ContentGenerator generator, Page outPage, Document outDoc, string tag)
        {
            Node element = new Node(tag, outDoc, outPage);
            element.ActualText = textElement.Text[0].Text;
            element.Language = "en";

            section.Children.Add(element);

            generator.TagAs(element);

            generator.AppendContentElement(textElement);

            generator.StopTagging();

            return element;
        }
    }
}