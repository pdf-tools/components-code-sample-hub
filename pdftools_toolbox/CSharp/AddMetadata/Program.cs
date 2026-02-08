/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddMetadata <inputPath> <outputPath> [<mdatafile>]
 *                  Example: in.pdf out.pdf MetadataTest.xmp
 *                  
 * Title:           Add metadata to PDF
 *                  
 * Description:     Set metadata such as author, title, and creator of a PDF
 *                  document. Optionally use the metadata of another PDF
 *                  document or the content of an XMP file.
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

namespace ToolboxAddMetadata
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddMetadata <inputPath> <outputPath> [<mdatafile>]");
            Console.WriteLine("       Example: in.pdf out.pdf MetadataTest.xmp");

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

                string inPath = args[0];
                string outPath = args[1];

                string mdatafile = null;
                if (args.Length == 3)
                {
                    mdatafile = args[2];
                }

                // Open input document 
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Set Metadata
                    if (args.Length == 3)
                    {
                        Metadata mdata;

                        // Add metadata from a input file 
                        using FileStream metaStream = File.OpenRead(mdatafile);
                        if (mdatafile.EndsWith(".pdf"))
                        {
                            // Use the metadata of another PDF file
                            using Document metaDoc = Document.Open(metaStream, "");
                            mdata = Metadata.Copy(outDoc, metaDoc.Metadata);
                        }
                        else
                        {
                            // Use the content of an XMP metadata file 
                            mdata = Metadata.Create(outDoc, metaStream);
                        }
                        outDoc.Metadata = mdata;
                    }
                    else
                    {
                        // Set some metadata properties 
                        Metadata metadata = outDoc.Metadata;
                        metadata.Author = "Your Author";
                        metadata.Title = "Your Title";
                        metadata.Subject = "Your Subject";
                        metadata.Creator = "Your Creator";
                    }

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages and append to output document
                    PageList copiedPages = PageList.Copy(outDoc, inDoc.Pages, copyOptions);
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
            // Copy document-wide data (except metadata)

            // Output intent
            if (inDoc.OutputIntent != null)
                outDoc.OutputIntent = IccBasedColorSpace.Copy(outDoc, inDoc.OutputIntent);

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