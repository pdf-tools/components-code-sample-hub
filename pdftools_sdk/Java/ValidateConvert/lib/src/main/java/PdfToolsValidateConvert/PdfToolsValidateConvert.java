/****************************************************************************
 *
 * File:            pdftoolsvalidateconvert.java
 *
 * Usage:           java pdftoolsvalidateconvert <inputPath> <outputPath>
 *                  
 * Title:           Convert a PDF to PDF/A-2b if necessary
 *                  
 * Description:     Analyze the input PDF document. If it does not yet
 *                  conform to PDF/A-2b, convert it to PDF/A-2b.
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

package PdfToolsValidateConvert;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.pdfa.validation.*;
import com.pdftools.pdfa.conversion.*;
import com.pdftools.pdfa.conversion.Converter.*;

public class PdfToolsValidateConvert
{
    static void usage() {
        System.out.println("Usage: java pdftoolsvalidateconvert <inputPath> <outputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            // Convert the document to PDF/A-2b
            convertIfNotConforming(args[0], args[1], new Conformance(new Conformance.PdfAVersion(2, Conformance.PdfAVersion.Level.B)));
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void convertIfNotConforming(String inPath, String outPath, Conformance conformance) throws Exception
    {
        // Open input document
        try (FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
             Document inDoc = Document.open(inStr))
        {
            // Create the Validator object, and use the Conformance object to create
            // an AnalysisOptions object that controls the behavior of the Validator.
            Validator validator = new Validator();
            AnalysisOptions analysisOptions = new AnalysisOptions();
            analysisOptions.setConformance(conformance);

            // Run the analysis, and check the results.
            // Only proceed if document is not conforming.
            AnalysisResult analysisResult = validator.analyze(inDoc, analysisOptions);
            if (analysisResult.getIsConforming())
            {
                System.out.println("Document conforms to " + inDoc.getConformance() + " already.");
                return;
            }

            // Create output stream
            try (FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW))
            {
                // Create a converter object
                Converter converter = new Converter();

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
                            throw new Exception("Unable to convert document to " + conformance + " because of critical conversion events.");
                    }
                }
            }

        }
    }
}
