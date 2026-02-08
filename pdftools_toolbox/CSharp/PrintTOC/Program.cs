/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxPrintTOC <inputPath>
 *                  
 * Title:           Print a table of content
 *                  
 * Description:     Print a formatted table of content from the document
 *                  outline.
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
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxListInfo
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxPrintTOC <inputPath>");
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
                    PrintOutlineItems(inDoc.Outline, "", inDoc);
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void PrintOutlineItem(OutlineItem item, string indentation, Document document)
        {
            string title = item.Title;
            Console.Out.Write("{0}{1}", indentation, title);
            Destination dest = item.Destination;
            if (dest != null)
            {
                int pageNumber = document.Pages.IndexOf(dest.Target.Page) + 1;
                string dots = new string('.', 78 - indentation.Length - title.Length - pageNumber.ToString().Length);
                Console.Out.Write(" {0} {1}", dots, pageNumber);
            }
            Console.Out.WriteLine();
            PrintOutlineItems(item.Children, indentation + "  ", document);
        }

        static void PrintOutlineItems(OutlineItemList outlineItems, string indentation, Document document)
        {
            foreach (var item in outlineItems)
                PrintOutlineItem(item, indentation, document);
        }
    }
}