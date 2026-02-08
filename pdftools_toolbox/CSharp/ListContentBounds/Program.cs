/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxListContentBounds <inputPath>
 *                  
 * Title:           List bounds of page content
 *                  
 * Description:     For each page, list the page size and the rectangular
 *                  bounding box of all content on the page in PDF points
 *                  (1/72 inch).
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

namespace ToolboxListContentBounds
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxListContentBounds <inputPath>");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 1 || args.Length > 1)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string path = args[0];

                // Open input document
                using (Stream stream = new FileStream(path, FileMode.Open, FileAccess.Read))
                using (Document doc = Document.Open(stream, null))
                {
                    // Iterate over all pages
                    int pageNumber = 1;
                    foreach (Page page in doc.Pages)
                    {
                        // Print page size
                        Console.WriteLine("Page {0}", pageNumber++);
                        Size size = page.Size;
                        Console.WriteLine("  Size:");
                        Console.WriteLine("    Width: {0}", size.Width);
                        Console.WriteLine("    Height: {0}", size.Height);

                        // Compute rectangular bounding box of all content on page
                        Rectangle contentBox = new Rectangle()
                        {
                            Left = double.MaxValue,
                            Bottom = double.MaxValue,
                            Right = double.MinValue,
                            Top = double.MinValue,
                        };
                        ContentExtractor extractor = new ContentExtractor(page.Content);
                        foreach (ContentElement element in extractor)
                        {
                            // Enlarge the content box for each content element
                            AffineTransform tr = element.Transform;
                            Rectangle box = element.BoundingBox;

                            // The location on the page is given by the transformed points
                            Enlarge(ref contentBox, tr.TransformPoint(new Point { X = box.Left, Y = box.Bottom, }));
                            Enlarge(ref contentBox, tr.TransformPoint(new Point { X = box.Right, Y = box.Bottom, }));
                            Enlarge(ref contentBox, tr.TransformPoint(new Point { X = box.Right, Y = box.Top, }));
                            Enlarge(ref contentBox, tr.TransformPoint(new Point { X = box.Left, Y = box.Top, }));
                        }
                        Console.WriteLine("  Content bounding box:");
                        Console.WriteLine("    Left: {0}", contentBox.Left);
                        Console.WriteLine("    Bottom: {0}", contentBox.Bottom);
                        Console.WriteLine("    Right: {0}", contentBox.Right);
                        Console.WriteLine("    Top: {0}", contentBox.Top);
                    }
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void Enlarge(ref Rectangle box, Point point)
        {
            // Enlarge box if point lies outside of box
            if (point.X < box.Left)
                box.Left = point.X;
            else if (point.X > box.Right)
                box.Right = point.X;
            if (point.Y < box.Bottom)
                box.Bottom = point.Y;
            else if (point.Y > box.Top)
                box.Top = point.Y;
        }
    }
}