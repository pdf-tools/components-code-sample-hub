/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddAnnotations <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Add annotations to PDF
 *                  
 * Description:     Generate and add various types of annotations at
 *                  specified positions on the first page of a PDF document.
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
using PdfTools.Toolbox.Pdf.Annotations;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxAddAnnotations
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddAnnotations <inputPath> <outputPath>");
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

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))
                {
                    // Create output document
                    using Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite);
                    using Document outDoc = Document.Create(outStream, inDoc.Conformance, null);

                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy first page and add annotations
                    Page outPage = CopyAndAddAnnotations(outDoc, inDoc.Pages[0], copyOptions);

                    // Add the page to the output document's page list
                    outDoc.Pages.Add(outPage);

                    // Copy the remaining pages and add to the output document's page list
                    PageList inPages = inDoc.Pages.GetRange(1, inDoc.Pages.Count - 1);
                    PageList outPages = PageList.Copy(outDoc, inPages, copyOptions);
                    outDoc.Pages.AddRange(outPages);
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

        private static Page CopyAndAddAnnotations(Document outDoc, Page inPage, PageCopyOptions copyOptions)
        {
            // Copy page to output document
            Page outPage = Page.Copy(outDoc, inPage, copyOptions);

            // Make a RGB color space
            ColorSpace rgb = ColorSpace.CreateProcessColorSpace(outDoc, ProcessColorSpaceType.Rgb);

            // Get the page size for positioning annotations
            Size pageSize = outPage.Size;

            // Get the output page's list of annotations for adding annotations
            AnnotationList annotations = outPage.Annotations;

            // Create a sticky note and add to output page's annotations
            Paint green = Paint.Create(outDoc, rgb, new double[] { 0, 1, 0 }, null);
            Point stickyNoteTopLeft = new Point() { X = 10, Y = pageSize.Height - 10 };
            StickyNote stickyNote = StickyNote.Create(outDoc, stickyNoteTopLeft, "Hello world!", green);
            annotations.Add(stickyNote);

            // Create an ellipse and add to output page's annotations
            Paint blue = Paint.Create(outDoc, rgb, new double[] { 0, 0, 1 }, null);
            Paint yellow = Paint.Create(outDoc, rgb, new double[] { 1, 1, 0 }, null);
            Rectangle ellipseBox = new Rectangle() { Left = 10, Bottom = pageSize.Height - 60, Right = 70, Top = pageSize.Height - 20 };
            EllipseAnnotation ellipse = EllipseAnnotation.Create(outDoc, ellipseBox, new Stroke(blue, 1.5), yellow);
            annotations.Add(ellipse);

            // Create a free text and add to output page's annotations
            Paint yellowTransp = Paint.Create(outDoc, rgb, new double[] { 1, 1, 0 }, new Transparency(0.5));
            Rectangle freeTextBox = new Rectangle() { Left = 10, Bottom = pageSize.Height - 170, Right = 120, Top = pageSize.Height - 70 };
            FreeText freeText = FreeText.Create(outDoc, freeTextBox, "Lorem ipsum dolor sit amet, consectetur adipiscing elit.", yellowTransp);
            annotations.Add(freeText);

            // A highlight and a web-link to be fitted on existing page content elements
            Highlight highlight = null;
            WebLink webLink = null;
            // Extract content elements from the input page
            ContentExtractor extractor = new ContentExtractor(inPage.Content);
            foreach (ContentElement element in extractor)
            {
                // Take the first text element
                if (highlight == null && element is TextElement textElement)
                {
                    // Get the quadrilaterals of this text element
                    QuadrilateralList quadrilaterals = new QuadrilateralList();
                    foreach (TextFragment fragment in textElement.Text)
                        quadrilaterals.Add(fragment.Transform.TransformRectangle(fragment.BoundingBox));

                    // Create a highlight and add to output page's annotations
                    highlight = Highlight.CreateFromQuadrilaterals(outDoc, quadrilaterals, yellow);
                    annotations.Add(highlight);
                }

                // Take the first image element
                if (webLink == null && element is ImageElement)
                {
                    // Get the quadrilateral of this image
                    QuadrilateralList quadrilaterals = new QuadrilateralList();
                    quadrilaterals.Add(element.Transform.TransformRectangle(element.BoundingBox));

                    // Create a web-link and add to the output page's links
                    webLink = WebLink.CreateFromQuadrilaterals(outDoc, quadrilaterals, "https://www.pdf-tools.com");
                    Paint red = Paint.Create(outDoc, rgb, new double[] { 1, 0, 0 }, null);
                    webLink.BorderStyle = new Stroke(red, 1.5);
                    outPage.Links.Add(webLink);
                }

                // Exit loop if highlight and webLink have been created
                if (highlight != null && webLink != null)
                    break;
            }

            // return the finished page
            return outPage;
        }
    }
}
