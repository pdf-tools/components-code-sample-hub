/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsZugferd <inputPath> <invoicePath> <outputPath>
 *                  
 * Title:           Create a ZUGFeRD invoice
 *                  
 * Description:     Convert a PDF to PDF/A-3 and embed XML data to create a
 *                  ZUGFeRD-compliant invoice.
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
using PdfTools;
using PdfTools.Pdf;
using PdfTools.PdfA.Validation;
using PdfTools.PdfA.Conversion;

namespace PdfToolsValidateConvert
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsZugferd <inputPath> <invoicePath> <outputPath>");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 3 || args.Length > 3)
            {
                Usage();
                return;
            }

            try
            {
                // By default, a test license key is active. In this case, a watermark is added to the output. 
                // If you have a license key, please uncomment the following call and set the license key.
                // Sdk.Initialize("LICENSE-KEY");

                AddZugferdInvoice(args[0], args[1], args[2]);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void AddZugferdInvoice(string inPath, string invoicePath, string outPath)
        {
            // Open input document
            using var inStr = File.OpenRead(inPath);
            using var inDoc = Document.Open(inStr);

            // Create the Validator object, and use the Conformance object to create
            // an AnalysisOptions object that controls the behavior of the Validator.
            var validator = new Validator();
            // The conformance has to be set to PDF/A-3 when adding the XML invoice file
            var analysisOptions = new AnalysisOptions() { Conformance = new Conformance(3, Conformance.PdfALevel.U) };

            // Run the analysis
            var analysisResult = validator.Analyze(inDoc, analysisOptions);

            // Create a converter object
            var converter = new Converter();

            // Add invoice XML file
            using var invoiceStr = File.OpenRead(invoicePath);
            converter.AddInvoiceXml(InvoiceType.Zugferd, invoiceStr);

            // Add handler for conversion events
            var eventsSeverity = EventSeverity.Information;
            converter.ConversionEvent += (s, e) =>
            {
                // Get the event's suggested severity
                var severity = e.Severity;

                // Optionally the suggested severity can be changed according to
                // the requirements of your conversion process and, for example,
                // the event's category (e.Category).

                if (severity > eventsSeverity)
                    eventsSeverity = severity;

                // Report conversion event
                Console.WriteLine("- {0} {1}: {2} ({3}{4})",
                    severity.ToString()[0], e.Category, e.Message, e.Context, e.PageNo > 0 ? " page " + e.PageNo : ""
                );
            };

            // Create stream for output file
            using var outStr = File.Create(outPath);

            // Convert the input document to PDF/A using the converter object
            // and its conversion event handler
            using var outDoc = converter.Convert(analysisResult, inDoc, outStr);

            // Check if critical conversion events occurred
            switch (eventsSeverity)
            {
                case EventSeverity.Information:
                    Console.WriteLine($"Successfully converted document to {outDoc.Conformance}.");
                    break;

                case EventSeverity.Warning:
                    Console.WriteLine($"Warnings occurred during the conversion of document to {outDoc.Conformance}.");
                    Console.WriteLine($"Check the output file to decide if the result is acceptable.");
                    break;

                case EventSeverity.Error:
                    throw new Exception($"Unable to convert document to PDF/A-3U because of critical conversion events.");
            }
        }
    }
}
