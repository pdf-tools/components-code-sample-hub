/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxSplitAtOutlines <inputPath> <outputDir> [<level>]
 *                  Example: in1.pdf . 2
 *                  
 * Title:           Split at outlines
 *                  
 * Description:     
 *                  Split a PDF document into several parts defined by the
 *                  document's outlines at a given level.
 *                  The outlines' titles define the output file names.
 *                  
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
using System.Collections.Generic;
using System.IO;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxSplit
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxSplitAtOutlines <inputPath> <outputDir> [<level>]");
            Console.WriteLine("       Example: in1.pdf . 2");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2 || args.Length > 3)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                // Parse command line arguments
                string inPath = args[0];
                string outDir = args[1];
                int level = 1;
                if (args.Length == 3)
                    level = int.Parse(args[2]);
                if (level < 1)
                {
                    Usage();
                    return;
                }

                // Ensure that the output directory exists
                Directory.CreateDirectory(outDir);

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))
                {
                    // Collect all outline items at the given level
                    List<OutlineItem> outlines = GetOutlines(inDoc.Outline, level);

                    // Collect all page ranges corresponding to the given outline items
                    List<Tuple<PageList, OutlineItem>> parts = GetParts(inDoc.Pages, outlines);

                    // Iterate over all collected parts
                    foreach (var part in parts)
                    {
                        // Turn the outline item's title into a valid file name
                        string fileName = part.Item2.Title;
                        foreach (char c in System.IO.Path.GetInvalidFileNameChars())
                        {
                            fileName = fileName.Replace(c, '_');
                        }
                        fileName += ".pdf";
                        fileName = System.IO.Path.Combine(outDir, fileName);

                        // Create output document
                        using Stream outStream = new FileStream(fileName, FileMode.Create, FileAccess.ReadWrite);
                        using Document outDoc = Document.Create(outStream, inDoc.Conformance, null);

                        // Copy document-wide data
                        CopyDocumentData(inDoc, outDoc);

                        // Define page copy options
                        PageCopyOptions pageCopyOptions = new PageCopyOptions();
                        pageCopyOptions.CopyOutlineItems = false;

                        // Copy the pages and add to the output document's page list
                        PageList outPages = PageList.Copy(outDoc, part.Item1, pageCopyOptions);
                        outDoc.Pages.AddRange(outPages);

                        // Copy child outline items
                        OutlineCopyOptions outlineCopyOptions = new OutlineCopyOptions();
                        foreach (var child in part.Item2.Children)
                        {
                            outDoc.Outline.Add(OutlineItem.Copy(outDoc, child, outlineCopyOptions));
                        }
                    }
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static List<OutlineItem> GetOutlines(OutlineItemList currentOutlines, int level, int currentLevel = 1)
        {
            List<OutlineItem> matchingOutlines = new List<OutlineItem>();
            // If the current level matches the specified level add the given outline items
            if (level == currentLevel)
            {
                matchingOutlines.AddRange(currentOutlines);
            }
            else
            {
                // Otherwise recurse to next level
                foreach (var outline in currentOutlines)
                {
                    matchingOutlines.AddRange(GetOutlines(outline.Children, level, currentLevel + 1));
                }
            }
            return matchingOutlines;
        }

        private static List<Tuple<PageList, OutlineItem>> GetParts(PageList inPages, List<OutlineItem> outlines)
        {
            // Construct parts according to the given outlines
            List<Tuple<PageList, OutlineItem>> parts = new List<Tuple<PageList, OutlineItem>>();

            // No parts to be constructed if no outlines are found
            if (outlines.Count == 0)
                return parts;

            // Keep both the last and the next outline items while iterating
            OutlineItem lastOutline = null;
            var outlineEnumerator = outlines.GetEnumerator();
            outlineEnumerator.MoveNext();
            OutlineItem nextOutline = outlineEnumerator.Current;

            // Keep both, the last and the current page index while iterating
            int lastPageIndex = 0;
            for (int pageIndex = 0; pageIndex < inPages.Count; pageIndex++)
            {
                // Check if this page is the destination's page of the next outline
                if (inPages[pageIndex].Equals(nextOutline.Destination.Target.Page))
                {
                    // Create a new part if the last outline item is defined and if the page index has increased at least by 1
                    if (lastOutline != null && pageIndex - lastPageIndex > 0)
                        parts.Add(new Tuple<PageList, OutlineItem>(inPages.GetRange(lastPageIndex, pageIndex - lastPageIndex), lastOutline));

                    // Keep the current page index as the last page index used
                    lastPageIndex = pageIndex;

                    // Keep the current outline as the last outline used
                    lastOutline = nextOutline;

                    // Iterate to the next outline item and stop if none left
                    if (outlineEnumerator.MoveNext())
                        nextOutline = outlineEnumerator.Current;
                    else
                        break;
                }
            }
            // Add the last part which is assumed to contain all the pages until the end of the document
            parts.Add(new Tuple<PageList, OutlineItem>(inPages.GetRange(lastPageIndex, inPages.Count - lastPageIndex), lastOutline));
            return parts;
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
    }
}