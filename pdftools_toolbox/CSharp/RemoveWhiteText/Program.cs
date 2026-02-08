/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxRemoveWhiteText <inputPath> <outputPath>
 *                  Example: in.pdf out.pdf
 *                  
 * Title:           Remove white text from PDF
 *                  
 * Description:     Remove white text from all pages of a PDF. Links,
 *                  annotations, form fields, outlines, logical structure,
 *                  and embedded files are discarded.
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
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxRemoveWhiteText
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxRemoveWhiteText <inputPath> <outputPath>");
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
                        // Copy page content from input to output
                        CopyContent(inPage.Content, outPage.Content, outDoc);
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

        private static void CopyContent(Content inContent, Content outContent, Document outDoc)
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
                    // Call CopyContent() recursively for the group element's content
                    CopyContent(inGroupElement.Group.Content, outGroupElement.Group.Content, outDoc);
                }
                else
                {
                    // Copy the content element to the output document
                    outElement = ContentElement.Copy(outDoc, inElement);
                    if (outElement is TextElement outTextElement)
                    {
                        // Special treatment for text element
                        Text text = outTextElement.Text;
                        // Remove all those text fragments whose fill and stroke paint is white
                        for (int iFragment = text.Count - 1; iFragment >= 0; iFragment--)
                        {
                            TextFragment fragment = text[iFragment];
                            if ((fragment.Fill == null || IsWhite(fragment.Fill.Paint)) &&
                                (fragment.Stroke == null || IsWhite(fragment.Stroke.Paint)))
                                text.RemoveAt(iFragment);
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

        private static bool IsWhite(Paint paint)
        {
            ColorSpace colorSpace = paint.ColorSpace;
            if (colorSpace is DeviceGrayColorSpace || colorSpace is CalibratedGrayColorSpace ||
                colorSpace is DeviceRgbColorSpace || colorSpace is CalibratedRgbColorSpace)
            {
                // These color spaces are additive: white is 1.0
                return paint.Color.Min() == 1.0;
            }
            if (colorSpace is DeviceCmykColorSpace)
            {
                // This color space is subtractive: white is 0.0
                return paint.Color.Max() == 0.0;
            }
            return false;
        }
    }
}