/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxImageExtraction <inputPath> <outputDir>
 *                  Example: in.pdf dir/subdir/
 *                  
 * Title:           Extract all images and image masks from a PDF
 *                  
 * Description:     Extract the embedded image data as JPEG or TIFF,
 *                  depending on the compression format used.
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

using PdfTools.Toolbox;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using System;
using System.IO;
using System.Linq;

namespace ToolboxImageExtraction
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxImageExtraction <inputPath> <outputDir>");
            Console.WriteLine("       Example: in.pdf dir/subdir/");

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
                string outputDir = args[1];

                if (!Directory.Exists(outputDir))
                    Directory.CreateDirectory(outputDir);

                // Open input document
                using (Stream stream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document doc = Document.Open(stream, null))
                {
                    // Loop over all pages and extract images
                    for (int i = 0; i < doc.Pages.Count; i++)
                    {
                        ContentExtractor extractor = new ContentExtractor(doc.Pages[i].Content);
                        ExtractImages(extractor, i + 1, outputDir);
                    }
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void ExtractImages(ContentExtractor extractor, int pageNo, string outputDir)
        {
            int imgCount = 0;
            int imgMaskCount = 0;
            foreach (ContentElement contentElement in extractor)
            {
                if (contentElement is ImageElement element)
                {
                    imgCount++;
                    string extension = ".tiff";
                    switch (element.Image.DefaultImageType)
                    {
                        case ImageType.Jpeg:
                            extension = ".jpg";
                            break;
                        case ImageType.Tiff:
                            extension = ".tiff";
                            break;
                        default:
                            break;
                    }
                    string outputPath = System.IO.Path.Combine(outputDir, $"image_page{pageNo}_{imgCount}{extension}");

                    try
                    {
                        using (Stream imageStream = new FileStream(outputPath, FileMode.Create, FileAccess.ReadWrite))
                        {
                            element.Image.Extract(imageStream);
                        }
                    }
                    catch (GenericException ex)
                    {
                        Console.WriteLine(ex.ToString());
                    }
                }
                else if (contentElement is ImageMaskElement maskElement)
                {
                    imgMaskCount++;
                    string extension = ".tiff";
                    string outputPath = System.IO.Path.Combine(outputDir, $"image_mask_page{pageNo}_{imgMaskCount}{extension}");
                    try
                    {
                        using (Stream imageStream = new FileStream(outputPath, FileMode.Create, FileAccess.ReadWrite))
                        {
                            maskElement.ImageMask.Extract(imageStream);
                        }
                    }
                    catch (GenericException ex)
                    {
                        Console.WriteLine(ex.ToString());
                    }
                }
            }
        }
    }
}