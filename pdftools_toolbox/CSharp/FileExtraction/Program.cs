/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxFileExtraction <inputPath> <outputDir>
 *                  Example: in.pdf dir/subdir/
 *                  
 * Title:           Extract files embedded from a PDF
 *                  
 * Description:     Extract the embedded files contained in the PDF to the
 *                  file system.
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


namespace ToolboxFileExtraction
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxFileExtraction <inputPath> <outputDir>");
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

                string inputFile = args[0];
                string outputDir = args[1];

     
                // Open input document
                using (FileStream inStream = new FileStream(inputFile, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))
                {
                    FileReferenceList frList = inDoc.AllEmbeddedFiles;

                    foreach(FileReference fr in frList)
                    {
                        ExtractFile(fr, outputDir);
                    }
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

    
        private static void ExtractFile(FileReference fr, String outputDir)
        {
            using (FileStream outStream = new FileStream(outputDir + "/" + fr.Name, FileMode.Create, FileAccess.ReadWrite))
            {
                fr.Data.CopyTo(outStream);
            }
        }
    }
}