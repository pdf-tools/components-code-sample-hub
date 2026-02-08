/****************************************************************************
 *
 * File:            toolboxtraversedocumentstructure.java
 *
 * Usage:           java toolboxtraversedocumentstructure <inputPath>
 *                  Example: in.pdf
 *                  
 * Title:           Traverse the document structure
 *                  
 * Description:     Traverse the logical structure of a
 *                  tagged PDF file.
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

package ToolboxTraverseDocumentStructure;

import java.util.stream.Collectors;

import java.io.File;

import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.NotFoundException;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.structure.Node;
import com.pdftools.toolbox.pdf.structure.Tree;

public class ToolboxTraverseDocumentStructure {
    static void usage() {
        System.out.println("Usage: java toolboxtraversedocumentstructure <inputPath>");
        System.out.println("       Example: in.pdf");

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
                    Tree tree = new Tree(inDoc);
                    for (Node node : tree.getChildren()) {
                        printNodeRecursively(node, 0);
                    }                   
            }

            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }    


    static void printProperty(int level, String name, String value) {
        for (int i = 0; i< level; ++i) {
            System.out.print(" ");
        }
        System.out.println(name + ": " + value);
    }


   static void printNodeRecursively(Node node, int level) throws NotFoundException {
        printProperty(level, "Tag", node.getTag());
        printProperty(level, "Alternative text", node.getAlternateText());
        printProperty(level, "Actual text", node.getActualText());
        printProperty(level, "Abbreviation", node.getAbbreviation());
        printProperty(level, "Language", node.getLanguage());
        for  (Node child : node.getChildren()) {
            printNodeRecursively(child, level + 1);
        }
    }
}
