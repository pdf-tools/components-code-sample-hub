/****************************************************************************
 *
 * File:            pdftoolsvalidatesimple.java
 *
 * Usage:           java pdftoolsvalidatesimple <inputPath>
 *                  
 * Title:           Validate PDF conformance
 *                  
 * Description:     Assess whether a PDF document adheres to specific
 *                  standards and conformance levels.
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

package PdfToolsValidateSimple;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.pdfa.validation.*;

public class PdfToolsValidateSimple
{
    static void usage() {
        System.out.println("Usage: java pdftoolsvalidatesimple <inputPath>");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 1 || args.length > 1) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");

            ValidationResult result = validate(args[0]);

            // Report the validation result
            if (result.getIsConforming())
                System.out.println("Document conforms to " + result.getConformance() + ".");
            else
                System.out.println("Document does not conform to "+ result.getConformance() + ".");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static ValidationResult validate(String inPath) throws Exception
    {
        // Open input document
        try (FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
             Document inDoc = Document.open(inStr))
        {
            // Create a validator object that writes all validation error messages to the console
            Validator validator = new Validator();
            validator.addErrorListener(
                (Validator.Error error) ->
                System.out.format("- %s: %s (%s%s)%n", error.getCategory(), error.getMessage(), error.getContext(), error.getPageNo() > 0 ? String.format(" on page %d", error.getPageNo()) : "")
            );

            // Validate the standard conformance of the document
            return validator.validate(inDoc);
        }
    }
}
