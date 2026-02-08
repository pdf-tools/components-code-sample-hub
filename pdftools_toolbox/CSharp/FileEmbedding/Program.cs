/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxFileEmbedding <inputPath> <fileToEmbed> <outputPath> [<page>]
 *                  Example: in.pdf fileToEmbed.xyz out.pdf [page]
 *                  
 * Title:           Embed files into a PDF
 *                  
 * Description:     Embed files into a PDF and attach them to the document or
 *                  attach a page.
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


namespace ToolboxFileEmbedding
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxFileEmbedding <inputPath> <fileToEmbed> <outputPath> [<page>]");
            Console.WriteLine("       Example: in.pdf fileToEmbed.xyz out.pdf [page]");

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

                string input = args[0];
                string fileToEmbed = args[1];
                string output = args[2];
                int page = (args.Length == 4 ? Int32.Parse(args[3]) : -1);

            
                // Open input document
                using (FileStream inStream = new FileStream(input, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (FileStream outStream = new FileStream(output, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages
                    PageList inPageRange = inDoc.Pages.GetRange(0, inDoc.Pages.Count);
                    PageList copiedPages = PageList.Copy(outDoc, inPageRange, copyOptions);
                    outDoc.Pages.AddRange(copiedPages);

                    EmbedFile(outDoc, new FileInfo(fileToEmbed), page);
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

        private static void EmbedFile(Document outputDoc, FileSystemInfo fileToEmbed, int pageNumber)
        {
            // create file stream to read the file to embed
            using (FileStream fileStream = new FileStream(fileToEmbed.FullName, FileMode.Open, FileAccess.Read))
            {
                // create a file type depending on the file ending (e.g. "application/pdf")
                string fileEnding = fileToEmbed.Name.Substring(fileToEmbed.Name.LastIndexOf(".") + 1);
                string type = "application/" + fileEnding;

                // get the modified date from the file
                DateTime dateTime = fileToEmbed.LastWriteTime;

                // create a new FileReference
                FileReference fr = FileReference.Create(outputDoc, fileStream, fileToEmbed.Name, type, "", dateTime);

                // if a page is set, add a FileAttachment annotation to that page
                // otherwise, attach the file to the document
                if (pageNumber > 0 && pageNumber <= outputDoc.Pages.Count)
                {
                    // get the page to create the annotation on
                    Page page = outputDoc.Pages[pageNumber - 1];

                    // Get the color space
                    ColorSpace colorSpace = ColorSpace.CreateProcessColorSpace(outputDoc, ProcessColorSpaceType.Rgb);

                    // Choose the RGB color value
                    double[] color = { 1.0, 0.0, 0.0 };
                    Transparency transparency = new Transparency(1);

                    // Create paint object
                    Paint paint = Paint.Create(outputDoc, colorSpace, color, transparency);

                    // put the annotation in the center of the page
                    Point point = new Point
                    { 
                        X= page.Size.Width / 2,
                        Y= page.Size.Height / 2
                    };

                    // create a FileReference annotation and attach it to a page so the FireReference is visible on that page
                    FileAttachment fa = FileAttachment.Create(outputDoc, point, fr, paint);

                    // add FileAttachment annotation to page
                    page.Annotations.Add(fa);
                }
                else
                {
                    // attach it to the document
                    outputDoc.PlainEmbeddedFiles.Add(fr);
                }
            }
        }
    }
}