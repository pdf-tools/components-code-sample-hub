/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddDataMatrix <inputPath> <imagePath> <outputPath>
 *                  Example: in.pdf in.png out.pdf
 *                  
 * Title:           Add data matrix to PDF
 *                  
 * Description:     Add a two-dimensional barcode from an existing image on
 *                  the first page of a PDF document.
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
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Navigation;


namespace ToolboxAddDataMatrix
{
    class Program
    {
        // Define border
        private static readonly double Border = 40;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddDataMatrix <inputPath> <imagePath> <outputPath>");
            Console.WriteLine("       Example: in.pdf in.png out.pdf");

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
                string datamatrixPath = args[1];
                string outPath = args[2];

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

                    // Copy first page, add datamatrix image, and append to output document
                    Page outPage = Page.Copy(outDoc, inDoc.Pages[0], copyOptions);
                    AddDataMatrix(outDoc, outPage, datamatrixPath);
                    outDoc.Pages.Add(outPage);

                    // Copy remaining pages and append to output document
                    PageList inPageRange = inDoc.Pages.GetRange(1, inDoc.Pages.Count - 1);
                    PageList copiedPages = PageList.Copy(outDoc, inPageRange, copyOptions);
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

        private static void AddDataMatrix(Document document, Page page, string datamatrixPath)
        {
            // Create content generator
            using ContentGenerator generator = new ContentGenerator(page.Content, false);

            // Import data matrix
            using Stream inMatrix = new FileStream(datamatrixPath, FileMode.Open, FileAccess.Read);

            // Create image object for data matrix
            Image datamatrix = Image.Create(document, inMatrix);

            // Data matrix size
            double datamatrixSize = 85;

            // Calculate Rectangle for data matrix
            Rectangle rect = new Rectangle
            {
                Left = Border,
                Bottom = page.Size.Height - (datamatrixSize + Border),
                Right = datamatrixSize + Border,
                Top = page.Size.Height - Border
            };

            // Paint image of data matrix into the specified rectangle 
            generator.PaintImage(datamatrix, rect);
        }
    }
}