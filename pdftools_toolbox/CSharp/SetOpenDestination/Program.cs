/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxSetOpenDestination <inputPath> <pageNumber> <outputPath>
 *                  Example: in.pdf 2 out.pdf
 *                  
 * Title:           Set the open-destination of a PDF
 *                  
 * Description:     Set the page that is displayed when opening the document.
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

namespace ToolboxSetOpenDestination
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxSetOpenDestination <inputPath> <pageNumber> <outputPath>");
            Console.WriteLine("       Example: in.pdf 2 out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 3 || args.Length > 3)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];
                string outPath = args[2];
                int destinationPageNumber = int.Parse(args[1]);

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))
                {
                    if (destinationPageNumber < 1 || destinationPageNumber > inDoc.Pages.Count)
                        throw new ArgumentOutOfRangeException("Given page number is invalid");

                    // Create output document
                    using Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite);
                    using Document outDoc = Document.Create(outStream, inDoc.Conformance, null);

                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages and append to output document
                    PageList copiedPages = PageList.Copy(outDoc, inDoc.Pages, copyOptions);
                    outDoc.Pages.AddRange(copiedPages);

                    // Add open destination
                    Page outPage = copiedPages[destinationPageNumber - 1];
                    outDoc.OpenDestination = LocationZoomDestination.Create(outDoc, outPage, 0, outPage.Size.Height, null);
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
    }
}