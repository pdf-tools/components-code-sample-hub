/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddStamp <inputPath> <stampString> <outputPath> [<alpha>]
 *                  Example: in.pdf APPROVED out.pdf 0.5
 *                  
 * Title:           Add stamp to PDF
 *                  
 * Description:     Add a semi-transparent stamp text onto each page of a PDF
 *                  document. Optionally specify the color and the opacity of
 *                  the stamp.
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


namespace ToolboxAddStamp
{
    class Program
    {
        private static Paint paint;
        private static Font font;
        private static readonly double fontSize = 50.0;

        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddStamp <inputPath> <stampString> <outputPath> [<alpha>]");
            Console.WriteLine("       Example: in.pdf APPROVED out.pdf 0.5");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 3 || args.Length > 4)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];
                string stampString = args[1];
                string outPath = args[2];

                // Get opacity of stamp
                double alpha = 0.5; // default of opacity
                if (args.Length == 4)
                {
                    alpha = double.Parse(args[3]);
                    if (alpha < 0.0 || alpha > 1.0)
                        throw new Exception("The value must be between 0.0 and 1.0. Current value: " + args[3]);
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

                    font = Font.CreateFromSystem(outDoc, "Arial", "Italic", true);

                    // Get the color space
                    ColorSpace colorSpace = ColorSpace.CreateProcessColorSpace(outDoc, ProcessColorSpaceType.Rgb);

                    // Choose the RGB color value
                    double[] color = { 1.0, 0.0, 0.0 };
                    Transparency transparency = new Transparency(alpha);

                    // Create paint object with the choosen RGB color
                    paint = Paint.Create(outDoc, colorSpace, color, transparency);

                    // Define copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Copy all pages from input document
                    foreach (Page inPage in inDoc.Pages)
                    {
                        // Copy page from input to output
                        Page outPage = Page.Copy(outDoc, inPage, copyOptions);

                        // Add text to page
                        AddStamp(outDoc, outPage, stampString);

                        // Add page to document
                        outDoc.Pages.Add(outPage);
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

        private static void AddStamp(Document outputDoc, Page outPage, string stampString)
        {
            // Create content generator and text object
            using ContentGenerator gen = new ContentGenerator(outPage.Content, false);
            Text text = Text.Create(outputDoc);

            // Create text generator
            using (TextGenerator textgenerator = new TextGenerator(text, font, fontSize, null))
            {
                // Calculate point and angle of rotation
                Point rotationCenter = new Point
                {
                    X = outPage.Size.Width / 2.0,
                    Y = outPage.Size.Height / 2.0
                };
                double rotationAngle = Math.Atan2(outPage.Size.Height,
                    outPage.Size.Width) / Math.PI * 180.0;

                // Rotate text input around the calculated position
                AffineTransform trans = AffineTransform.Identity;
                trans.Rotate(rotationAngle, rotationCenter);
                gen.Transform(trans);

                // Calculate position
                Point position = new Point
                {
                    X = (outPage.Size.Width - textgenerator.GetWidth(stampString)) / 2.0,
                    Y = (outPage.Size.Height - font.Ascent * fontSize) / 2.0
                };

                // Move to position
                textgenerator.MoveTo(position);

                // Set text paint
                textgenerator.Fill = paint;

                // Add given stamp string
                textgenerator.ShowLine(stampString);
            }
            // Paint the positioned text
            gen.PaintText(text);
        }
    }
}