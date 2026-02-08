/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxUpdateAnnotations <inputPath> <inputFdfPath> <outputPath> <outputFdfPath>
 *                  Example: in.pdf inFdf.fdf out.pdf outFdf.fdf
 *                  
 * Title:           Update annotations to PDF
 *                  
 * Description:     Remove the 'Ellipse' annotations from the PDF and export
 *                  the new list of annotations to a new FDF-File.
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
            Console.WriteLine("Usage: ToolboxUpdateAnnotations <inputPath> <inputFdfPath> <outputPath> <outputFdfPath>");
            Console.WriteLine("       Example: in.pdf inFdf.fdf out.pdf outFdf.fdf");

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
                string inFdfPath = args[1];
                string outPath = args[2];
                string outFdfPath = args[3];

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Stream inFdfStream = new FileStream(inFdfPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.OpenWithFdf(inStream, inFdfStream, null))
                {
                    // Create output document
                    using var outStream = new FileStream(outPath, FileMode.Create, FileAccess.Write);
                    using var outFdfStream = new FileStream(outFdfPath, FileMode.Create, FileAccess.Write);
                    using var outDoc = Document.CreateWithFdf(outStream, outFdfStream, inDoc.Conformance, null);

                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    FilterAnnotations(inDoc, outDoc);
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

        private static void FilterAnnotations(Document inDoc, Document outDoc)
        {
            // Define page copy options
            var copyOptions = new PageCopyOptions
            {
                // Remove all annotations: we will add the filtered ones later
                Annotations = CopyStrategy.Remove
            };

            foreach (var inPage in inDoc.Pages)
            {
                // Copy page to output document
                var outPage = Page.Copy(outDoc, inPage, copyOptions);

                // Hold the annotations from the input document
                var inAnnotations = inPage.Annotations;

                // Selectively copy annotations (excluding EllipseAnnotations - like Circle)
                foreach (var inAnnotation in inAnnotations)
                {
                    // Skip if the annotation is an EllipseAnnotation
                    if (inAnnotation is EllipseAnnotation)
                    {
                        continue;
                    }

                    outPage.Annotations.Add(Annotation.Copy(outDoc, inAnnotation));
                }

                // Add the page to the output document
                outDoc.Pages.Add(outPage);
            }
        }
    }
}
