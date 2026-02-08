/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxListSignatures <inputPath>
 *                  
 * Title:           List Signatures in PDF
 *                  
 * Description:     List all signature fields in a PDF document and their
 *                  properties.
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
using PdfTools.Toolbox.Pdf.Forms;

namespace ToolboxListSignatures
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxListSignatures <inputPath>");
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
                    SignatureFieldList signatureFields = inDoc.SignatureFields;
                    Console.WriteLine("Number of signature fields: {0}", signatureFields.Count);
                    foreach (SignatureField field in signatureFields)
                    {
                        if (field is Signature sig)
                        {
                            // List name
                            string name = sig.Name;
                            Console.WriteLine("- {0} fields, signed by: {1}",
                                sig.IsVisible ? "Visible" : "Invisible", name ?? "(Unknown name)");

                            // List location
                            string location = sig.Location;
                            if (location != null)
                                Console.WriteLine("  - Location: {0}", location);

                            // List reason 
                            string reason = sig.Reason;
                            if (reason != null)
                                Console.WriteLine("  - Reason: {0}", reason);

                            // List contact info
                            string contactInfo = sig.ContactInfo;
                            if (contactInfo != null)
                                Console.WriteLine("  - Contact info: {0}", contactInfo);

                            // List date
                            DateTimeOffset? date = sig.Date;
                            if (date != null)
                                Console.WriteLine("  - Date: {0}", date.Value);
                        }
                        else
                            Console.WriteLine("- {0} field, not signed", field.IsVisible ? "Visible" : "Invisible");
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