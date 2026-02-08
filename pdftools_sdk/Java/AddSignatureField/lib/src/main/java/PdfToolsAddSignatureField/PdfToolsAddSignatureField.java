/****************************************************************************
 *
 * File:            pdftoolsaddsignaturefield.java
 *
 * Usage:           java pdftoolsaddsignaturefield <inputPath> <outputPath>
 *                  
 * Title:           Add a signature field to a PDF
 *                  
 * Description:     Add an unsigned signature field that can be signed in
 *                  another application.
 *                  The signature field indicates that the document requires
 *                  a signature and defines the page and position
 *                  where the signature's visual appearance will be placed.
 *                  This is especially useful for forms and contracts
 *                  with designated signature spaces. The signature visual
 *                  appearance is irrelevant to the signature validation
 *                  process and only serves as a visual cue for the user.
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

package PdfToolsAddSignatureField;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.geometry.units.*;
import com.pdftools.geometry.units.Length.Units;
import com.pdftools.pdf.*;
import com.pdftools.sign.*;

public class PdfToolsAddSignatureField
{
    static void usage() {
        System.out.println("Usage: java pdftoolsaddsignaturefield <inputPath> <outputPath>");
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

            // Add a signature field to a PDF document
            addSignatureField(args[0], args[1]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void addSignatureField(String inPath, String outPath) throws Exception
    {
        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr))
        {
            // Create empty field appearance that is 6cm by 3cm in size
            var appearance = Appearance.createFieldBoundingBox(new Size(6, 3, Units.CENTIMETRE));

            // Add field to last page of document
            appearance.setPageNumber(inDoc.getPageCount());

            // Position field
            appearance.setBottom(new Length(3, Units.CENTIMETRE));
            appearance.setLeft(new Length(6.5, Units.CENTIMETRE));

            // Create a signature field configuration
            var field = new SignatureFieldOptions(appearance);

            try (
                // Create output stream
                FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

                // Sign the input document
                Document outDoc = new Signer().addSignatureField(inDoc, field, outStr))
            {
            }
        }
    }
}
