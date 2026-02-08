/****************************************************************************
 *
 * File:            toolboxlistinfo.java
 *
 * Usage:           java toolboxlistinfo <inputPath> [<pdfPassword>]
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

package ToolboxListInfo;

import java.util.stream.Collectors;

import java.io.File;
import java.time.OffsetDateTime;
import java.util.EnumSet;
import java.util.Map;

import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.Permission;

public class ToolboxListInfo {
    static void usage() {
        System.out.println("Usage: java toolboxlistinfo <inputPath> [<pdfPassword>]");
    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 1 || args.length > 2) {
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
                // Conformance
                System.out.format("Conformance: %s\n", inDoc.getConformance().toString());

                // Encryption information
                EnumSet<Permission> permissions = inDoc.getPermissions();
                if (permissions == null) {
                    System.out.println("Not encrypted");
                } else {
                    System.out.println("Encryption:");
                    System.out.print("  - Permissions: ");
                    for (Permission permission : permissions) {
                        System.out.format("%s, ", permission.toString());
                    }
                    System.out.println();
                }

                // Get metadata of input PDF
                Metadata metadata = inDoc.getMetadata();
                System.out.format("Document information:\n");

                // Get title
                String title = metadata.getTitle();
                if (title != null)
                    System.out.format("  - Title: %s\n", title);

                // Get author
                String author = metadata.getAuthor();
                if (author != null)
                    System.out.format("  - Author: %s\n", author);

                // Get subject
                String subject = metadata.getSubject();
                if (subject != null)
                    System.out.format("  - Subject: %s\n", subject);

                // Get keywords
                String keywords = metadata.getKeywords();
                if (keywords != null)
                    System.out.format("  - Keywords: %s\n", keywords);

                // Get creation date
                OffsetDateTime creationDate = metadata.getCreationDate();
                if (creationDate != null)
                    System.out.format("  - Creation Date: %s\n", creationDate.toString());

                // Get modification date
                OffsetDateTime modificationDate = metadata.getModificationDate();
                if (modificationDate != null)
                    System.out.format("  - Modification Date: %s\n", modificationDate.toString());

                // Get creator
                String creator = metadata.getCreator();
                if (creator != null)
                    System.out.format("  - Creator: %s\n", creator);

                // Get producer
                String producer = metadata.getProducer();
                if (producer != null)
                    System.out.format("  - Producer: %s\n", producer);

                // Custom entries
                System.out.format("Custom entries:\n");
                for (Map.Entry<String, String> entry : metadata.getCustomEntries().entrySet())
                    System.out.format("  - %s: %s\n", entry.getKey(), entry.getValue());
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
}