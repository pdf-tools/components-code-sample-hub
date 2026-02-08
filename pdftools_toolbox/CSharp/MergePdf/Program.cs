/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxMergePdf <inputPath> [<inputPath2> ...] <outputPath>
 *                  Example: in1.pdf in2.pdf out.pdf
 *                  
 * Title:           Merge multiple PDFs
 *                  
 * Description:     Merge several PDF documents to one.
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

namespace ToolboxMergePdf
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxMergePdf <inputPath> [<inputPath2> ...] <outputPath>");
            Console.WriteLine("       Example: in1.pdf in2.pdf out.pdf");

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

                string outPath = args[^1];

                string[] inPath = new string[args.Length - 1];
                for (int i = 0; i < args.Length - 1; i++)
                {
                    inPath[i] = args[i];
                }

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, null, null))
                {
                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();

                    // Get output pages
                    PageList outPages = outDoc.Pages;

                    // Merge input documents 
                    for (int i = 0; i < args.Length - 1; i++)
                    {
                        // Open input document
                        using Stream inFs = new FileStream(inPath[i], FileMode.Open, FileAccess.Read);
                        using Document inDoc = Document.Open(inFs, null);

                        // Copy all pages and append to output document
                        PageList copiedPages = PageList.Copy(outDoc, inDoc.Pages, copyOptions);
                        outPages.AddRange(copiedPages);
                    }
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}