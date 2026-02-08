/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxSetInfo <inputPath> <key> <value> <outputPath>
 *                  Example: in.pdf key value out.pdf
 *                  
 * Title:           Add info entries to PDF
 *                  
 * Description:     Set metadata such as author, title, and creator of a PDF
 *                  document or add a custom entry.
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
            Console.WriteLine("Usage: ToolboxSetInfo <inputPath> <key> <value> <outputPath>");
            Console.WriteLine("       Example: in.pdf key value out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 4 || args.Length > 4)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];
                string outPath = args[3];
                string key = args[1];
                string value = args[2];

                // Open input document 
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages and append to output document
                    PageList copiedPages = PageList.Copy(outDoc, inDoc.Pages, copyOptions);
                    outDoc.Pages.AddRange(copiedPages);

                    // Set info entry
                    Metadata metadata = Metadata.Copy(outDoc, inDoc.Metadata);
                    if (key == "Title")
                        metadata.Title = value;
                    else if (key == "Author")
                        metadata.Author = value;
                    else if (key == "Subject")
                        metadata.Subject = value;
                    else if (key == "Keywords")
                        metadata.Keywords = value;
                    else if (key == "CreationDate")
                        metadata.CreationDate = DateTimeOffset.Parse(value);
                    else if (key == "ModDate")
                        throw new Exception("ModDate cannot be set.");
                    else if (key == "Creator")
                        metadata.Creator = value;
                    else if (key == "Producer")
                        throw new Exception("Producer is set by means of the license key.");
                    else
                        metadata.CustomEntries[key] = value;
                    outDoc.Metadata = metadata;
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