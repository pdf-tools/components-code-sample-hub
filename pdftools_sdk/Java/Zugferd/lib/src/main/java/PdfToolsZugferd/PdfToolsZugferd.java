/****************************************************************************
 *
 * File:            pdftoolszugferd.java
 *
 * Usage:           java pdftoolszugferd <inputPath> <invoicePath> <outputPath>
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

package PdfToolsZugferd;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.Sdk;
import com.pdftools.pdf.Conformance;
import com.pdftools.pdf.Document;
import com.pdftools.pdfa.conversion.Converter;
import com.pdftools.pdfa.conversion.Converter.ConversionEvent;
import com.pdftools.pdfa.conversion.Converter.ConversionEventListener;
import com.pdftools.pdfa.conversion.EventSeverity;
import com.pdftools.pdfa.conversion.InvoiceType;
import com.pdftools.pdfa.validation.AnalysisOptions;
import com.pdftools.pdfa.validation.AnalysisResult;
import com.pdftools.pdfa.validation.Validator;
import com.pdftools.sys.FileStream;

public class PdfToolsValidateConvert
{
    static void usage() {
        System.out.println("Usage: java pdftoolszugferd <inputPath> <invoicePath> <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 3 || args.length > 3) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            addZugferdInvoice(args[0], args[1], args[2]);
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void addZugferdInvoice(String inPath, String invoicePath, String outPath) throws Exception
    {
        // Open input document
        try (FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
             Document inDoc = Document.open(inStr))
        {
            // Create the Validator object, and use the Conformance object to create
            // an AnalysisOptions object that controls the behavior of the Validator.
            Validator validator = new Validator();
            AnalysisOptions analysisOptions = new AnalysisOptions();
            // The conformance has to be set to PDF/A-3 when adding the XML invoice file
            analysisOptions.setConformance(new Conformance(new Conformance.PdfAVersion(3, Conformance.PdfAVersion.Level.U)));

            // Run the analysis
            AnalysisResult analysisResult = validator.analyze(inDoc, analysisOptions);

            // Create output stream
            try (FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW))
            {
                // Create a converter object
                Converter converter = new Converter();

                // Add invoice XML file
                try (FileStream invoiceStr = new FileStream(invoicePath, FileStream.Mode.READ_ONLY))
                {
	                converter.addInvoiceXml(InvoiceType.ZUGFERD, invoiceStr);

	                // Add handler for conversion events
	                class EventListener implements ConversionEventListener
	                {
	                    private EventSeverity eventsSeverity = EventSeverity.INFORMATION;

	                    public EventSeverity getEventsSeverity() {
	                        return eventsSeverity;
	                    }

	                    @Override
	                    public void conversionEvent(ConversionEvent event) {
	                        // Get the event's suggested severity
	                        EventSeverity severity = event.getSeverity();

	                        // Optionally the suggested severity can be changed according to
	                        // the requirements of your conversion process and, for example,
	                        // the event's category (e.Category).

	                        if (severity.ordinal() > eventsSeverity.ordinal())
	                            eventsSeverity = severity;

	                        // Report conversion event
	                        System.out.format("- %c %s: %s (%s%s)%n", severity.toString().charAt(0), event.getCategory(), event.getMessage(), event.getContext(), event.getPageNo() > 0 ? " on page " + event.getPageNo() : "");
	                    }
	                }
	                EventListener el = new EventListener();

	                converter.addConversionEventListener(el);

	                // Convert the input document to PDF/A using the converter object
	                // and its conversion event handler
	                try (Document outDoc = converter.convert(analysisResult, inDoc, outStr))
	                {
	                    // Check if critical conversion events occurred
	                    switch (el.getEventsSeverity())
	                    {
	                        case INFORMATION:
	                            System.out.println("Successfully converted document to " + outDoc.getConformance() + ".");
	                            break;

	                        case WARNING:
	                            System.out.println("Warnings occurred during the conversion of document to " + outDoc.getConformance() + ".");
	                            System.out.println("Check the output file to decide if the result is acceptable.");
	                            break;

	                        case ERROR:
	                            throw new Exception("Unable to convert document to PDF/A-3U because of critical conversion events.");
	                    }
	                }
                }
            }
        }
    }
}
