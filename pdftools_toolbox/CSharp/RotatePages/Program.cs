/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxRotatePages <pageNumber> [<pageNumber2> ...] <inputPath> <outputPath>
 *                  Example: 2 4  in.pdf out.pdf
 *                  
 * Title:           Set page orientation
 *                  
 * Description:     Rotate a specified page of a PDF document by 90 degrees.
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
using PdfTools.Toolbox.Geometry;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxRotatePages
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxRotatePages <pageNumber> [<pageNumber2> ...] <inputPath> <outputPath>");
            Console.WriteLine("       Example: 2 4  in.pdf out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 3)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                int[] pageNumbers = new int[args.Length - 2];
                for (int i = 0; i < args.Length - 2; i++)
                {
                    pageNumbers[i] = int.Parse(args[i]);
                }

                string inPath = args[^2];
                string outPath = args[^1];

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outFs = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outFs, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages
                    PageList copiedPages = PageList.Copy(outDoc, inDoc.Pages, copyOptions);

                    // Rotate selected pages by 90 degrees
                    foreach (var pageNumber in pageNumbers)
                    {
                        copiedPages[pageNumber - 1].Rotate(Rotation.Clockwise);
                    }

                    // Add pages to output document
                    outDoc.Pages.AddRange(copiedPages);
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