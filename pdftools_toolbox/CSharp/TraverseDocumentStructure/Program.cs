/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxTraverseDocumentStructure <inputPath>
 *                  Example: in.pdf
 *                  
 * Title:           Traverse the document structure
 *                  
 * Description:     Traverse the logical structure of a
 *                  tagged PDF file.
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
using PdfTools.Toolbox.Pdf.Structure;

using System;
using System.IO;

namespace ToolboxDocumentStructure
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxTraverseDocumentStructure <inputPath>");
            Console.WriteLine("       Example: in.pdf");

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

                string inPath = args[0];


                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))
                {
                    var tree = new Tree(inDoc);
                    foreach (var child in tree.Children)
                    {
                        PrintNodeRecursively(child);
                    }
                }
                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void PrintProperty(int level, String name, String value)
        {
            Console.Write($"{new string(' ', level * 2)}");
            Console.WriteLine($"{name}: '{value}'");
        }


        static void PrintNodeRecursively(Node node, int level = 0)
        {
            PrintProperty(level, "Tag", node.Tag);
            PrintProperty(level, "Alternative text", node.AlternateText);
            PrintProperty(level, "Actual text", node.ActualText);
            PrintProperty(level, "Abbreviation", node.Abbreviation);
            PrintProperty(level, "Language", node.Language);

            foreach (var child in node.Children)
            {
                PrintNodeRecursively(child, level + 1);
            }
        }
    }
}