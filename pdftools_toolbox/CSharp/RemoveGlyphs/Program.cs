/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxRemoveGlyphs <inputPath> <outputPath>
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

using System;
using System.IO;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxRemoveGlyphs
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxRemoveGlyphs <inputPath> <outputPath>");
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
                        // Copy page content from input to output and remove glyphs
                        CopyContentAndRemoveGlyphs(inPage.Content, outPage.Content, outDoc);
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

        private static void CopyContentAndRemoveGlyphs(Content inContent, Content outContent, Document outDoc)
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
                    // Call CopyContentAndRemoveGlyphs() recursively for the group element's content
                    CopyContentAndRemoveGlyphs(inGroupElement.Group.Content, outGroupElement.Group.Content, outDoc);
                }
                else
                {
                    // Copy the content element to the output document
                    outElement = ContentElement.Copy(outDoc, inElement);
                    if (outElement is TextElement outTextElement)
                    {
                        // Special treatment for text element
                        Text text = outTextElement.Text;
                        // Remove the first two glyphs from each text fragment
                        foreach (var fragment in text)
                        {
                            // Ensure that the fragment has more than two glyphs
                            if (fragment.Count > 2)
                            {
                                // Call RemoveAt twice
                                fragment.RemoveAt(0);
                                fragment.RemoveAt(0);
                            }
                        }
                    }
                }
                // Append the finished output element to the content generator
                generator.AppendContentElement(outElement);
            }
        }

    }
}