/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxFlattenFormFields <inputPath> <outputPath>
 *                  
 * Title:           Flatten form fields in PDF
 *                  
 * Description:     Flatten the visual appearance of form fields and discard
 *                  all interactive elements.
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
using PdfTools.Toolbox.Pdf.Forms;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxFlattenFormFields
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxFlattenFormFields <inputPath> <outputPath>");
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

                    // Define copy options including form field flattening
                    PageCopyOptions copyOptions = new PageCopyOptions();
                    copyOptions.FormFields = FormFieldCopyStrategy.Flatten;

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