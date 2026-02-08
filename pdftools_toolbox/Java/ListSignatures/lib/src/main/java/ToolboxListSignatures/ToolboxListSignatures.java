/****************************************************************************
 *
 * File:            toolboxlistsignatures.java
 *
 * Usage:           java toolboxlistsignatures <inputPath>
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

package ToolboxListSignatures;

import java.util.stream.Collectors;

import java.time.OffsetDateTime;
import java.io.File;

import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.forms.Signature;
import com.pdftools.toolbox.pdf.forms.SignatureField;
import com.pdftools.toolbox.pdf.forms.SignatureFieldList;

public class ToolboxListSignatures {
    static void usage() {
        System.out.println("Usage: java toolboxlistsignatures <inputPath>");
    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 1 || args.length > 1) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String inPath = args[0];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null)) {
                SignatureFieldList signatureFields = inDoc.getSignatureFields();
                System.out.format("Number of signature fields: %d\n", signatureFields.size());

                for (SignatureField field : signatureFields) {
                    if (field instanceof Signature) {
                        Signature sig = (Signature)field;
                        // List name
                        String name = sig.getName();
                        System.out.format("- %s field, signed by: %s\n", sig.getIsVisible() ? "Visible" : "Invisible",
                                name != null ? name : "(Unknown name)");

                        // List location
                        String location = sig.getLocation();
                        if (location != null)
                            System.out.format("  - Location: %s\n", location);

                        // List reason
                        String reason = sig.getReason();
                        if (reason != null)
                            System.out.format("  - Reason: %s\n", reason);

                        // List contact info
                        String contactInfo = sig.getContactInfo();
                        if (contactInfo != null)
                            System.out.format("  - Contact info: %s\n", contactInfo);

                        // List date
                        OffsetDateTime date = sig.getDate();
                        if (date != null)
                            System.out.format("  - Date: %s\n", date.toString());
                    } else {
                        System.out.format("- %s field, not signed\n", field.getIsVisible() ? "Visible" : "Invisible");
                    }
                }
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
}