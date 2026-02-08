/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxOverlayColor [<options>] <inputPath> <outputPath>
 *                  Example: -k 0.5 1.0 in.pdf out.pdf
 *                  Options:
 *                  -k (k) (a)             specifiy grayscale and alpha color
 *                  -c (c) (m) (y) (k) (a)      specifiy CMKY and alpha color
 *                  -r (r) (g) (b) (a)          specifiy RGB and alpha color
 *                  color values between 0 and 1
 *                  default: -k 0.9 1.0
 *                  
 * Title:           Overlay color of PDF
 *                  
 * Description:     Overlay all pages of a PDF document with a configurable
 *                  color.
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


namespace ToolboxOverlayColor
{
    class Program
    {
        // Defines
        private static ProcessColorSpaceType colorType = ProcessColorSpaceType.Gray;
        private static double colorAlpha = 1.0;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxOverlayColor [<options>] <inputPath> <outputPath>");
            Console.WriteLine("       Example: -k 0.5 1.0 in.pdf out.pdf");
            Console.WriteLine("       Options:");
            Console.WriteLine("       -k (k) (a)             specifiy grayscale and alpha color");
            Console.WriteLine("       -c (c) (m) (y) (k) (a)      specifiy CMKY and alpha color");
            Console.WriteLine("       -r (r) (g) (b) (a)          specifiy RGB and alpha color");
            Console.WriteLine("       color values between 0 and 1");
            Console.WriteLine("       default: -k 0.9 1.0");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                double[] color = new double[] { 0.9 };
                int i = 0;
                for (; i < args.Length; i++)
                {
                    string arg = args[i];


                    if (arg[0] == '-')
                    {
                        // Set optionally the overlay color
                        switch (arg[1])
                        {
                            case 'c':
                                colorType = ProcessColorSpaceType.Cmyk;
                                if (args.Length - i++ < 8)
                                {
                                    Usage();
                                }
                                color = new double[]
                                {
                                    double.Parse(args[i++]),
                                    double.Parse(args[i++]),
                                    double.Parse(args[i++]),
                                    double.Parse(args[i++])
                                };
                                colorAlpha = double.Parse(args[i]);
                                break;
                            case 'k':
                                colorType = ProcessColorSpaceType.Gray;
                                if (args.Length - i++ < 5)
                                {
                                    Usage();
                                }
                                color = new double[] { double.Parse(args[i++]) };
                                colorAlpha = double.Parse(args[i]);
                                break;
                            case 'r':
                                colorType = ProcessColorSpaceType.Rgb;
                                if (args.Length - i++ < 7)
                                {
                                    Usage();
                                }
                                color = new double[]
                                {
                                    double.Parse(args[i++]),
                                    double.Parse(args[i++]),
                                    double.Parse(args[i++])
                                };
                                colorAlpha = double.Parse(args[i]);
                                break;
                        }
                    }
                    else
                        break;
                }

                if (args.Length - i < 2)
                {
                    Usage();
                }

                string inPath = args[i];
                string outPath = args[i + 1];

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Create transparency and set blend mode
                    Transparency transparency = new Transparency(colorAlpha)
                    {
                        BlendMode = BlendMode.Multiply
                    };

                    // Create colorspace
                    ColorSpace colorSpace = ColorSpace.CreateProcessColorSpace(outDoc, colorType);

                    // Create a transparent paint for the given color
                    Paint paint = Paint.Create(outDoc, colorSpace, color, transparency);
                    Fill fill = new Fill(paint);

                    // Get output pages
                    PageList outPages = outDoc.Pages;

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Loop through all pages
                    foreach (Page inPage in inDoc.Pages)
                    {
                        // Create a new page
                        Page outPage = Page.Copy(outDoc, inPage, copyOptions);
                        Size size = inPage.Size;

                        // Create a content generator
                        using (ContentGenerator generator = new ContentGenerator(outPage.Content, false))
                        {
                            // Make a rectangular path the same size as the page
                            PdfTools.Toolbox.Pdf.Content.Path path = new PdfTools.Toolbox.Pdf.Content.Path();
                            using (PathGenerator pathGenerator = new PathGenerator(path))
                            {
                                // Compute Rectangle
                                Rectangle pathRect = new Rectangle
                                {
                                    Left = 0,
                                    Bottom = 0,
                                    Right = size.Width,
                                    Top = size.Height
                                };
                                pathGenerator.AddRectangle(pathRect);
                            }
                            // Paint the path with the transparent paint
                            generator.PaintPath(path, fill, null);
                        }
                        // Add pages to output document
                        outPages.Add(outPage);
                    }
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