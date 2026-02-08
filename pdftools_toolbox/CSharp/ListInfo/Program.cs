/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxListInfo <inputPath> [<pdfPassword>]
 *                  
 * Title:           List document information of PDF
 *                  
 * Description:     List attributes of a PDF document (i.e. conformance and
 *                  encryption information) and metadata (i.e. author, title,
 *                  creation date etc.).
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

namespace ToolboxListInfo
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxListInfo <inputPath> [<pdfPassword>]");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 1 || args.Length > 2)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string inPath = args[0];
                var password = args.Length == 2 ? args[1] : null;

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, password))
                {
                    // Conformance
                    Console.WriteLine("Conformance: {0}", inDoc.Conformance.ToString());

                    // Encryption information
                    Permission? permissions = inDoc.Permissions;
                    if (!permissions.HasValue)
                    {
                        Console.WriteLine("Not encrypted");
                    }
                    else
                    {
                        Console.WriteLine("Encryption:");
                        Console.Write("  - Permissions: ");
                        foreach (Enum flag in Enum.GetValues(typeof(Permission)))
                            if (permissions.Value.HasFlag(flag))
                                Console.Write("{0}, ", flag.ToString());
                        Console.WriteLine();
                    }

                    // Get metadata
                    Metadata metadata = inDoc.Metadata;
                    Console.WriteLine("Document information:");

                    // Get title
                    string title = metadata.Title;
                    if (title != null)
                        Console.WriteLine("  - Title: {0}", title);

                    // Get author
                    string author = metadata.Author;
                    if (author != null)
                        Console.WriteLine("  - Author: {0}", author);

                    // Get subject
                    string subject = metadata.Subject;
                    if (subject != null)
                        Console.WriteLine("  - Subject: {0}", subject);

                    // Get keywords
                    string keywords = metadata.Keywords;
                    if (keywords != null)
                        Console.WriteLine("  - Keywords: {0}", keywords);

                    // Get creation date
                    DateTimeOffset? creationDate = metadata.CreationDate;
                    if (creationDate != null)
                        Console.WriteLine("  - Creation Date: {0}", creationDate);

                    // Get modification date
                    DateTimeOffset? modificationDate = metadata.ModificationDate;
                    if (modificationDate != null)
                        Console.WriteLine("  - Modification Date: {0}", modificationDate);

                    // Get creator
                    string creator = metadata.Creator;
                    if (creator != null)
                        Console.WriteLine("  - Creator: {0}", creator);

                    // Get producer
                    string producer = metadata.Producer;
                    if (producer != null)
                        Console.WriteLine("  - Producer: {0}", producer);

                    // Custom entries
                    Console.WriteLine("Custom entries:");
                    foreach (var entry in metadata.CustomEntries)
                        Console.WriteLine("  - {0}: {1}", entry.Key, entry.Value);
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