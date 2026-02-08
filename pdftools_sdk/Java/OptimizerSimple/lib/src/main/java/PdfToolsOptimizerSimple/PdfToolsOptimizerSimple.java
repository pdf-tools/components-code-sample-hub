/****************************************************************************
 *
 * File:            pdftoolsoptimizersimple.java
 *
 * Usage:           java pdftoolsoptimizersimple <inputPath> <outputPath>
 *                  
 * Title:           Optimize a PDF
 *                  
 * Description:     Optimize a PDF with the "Web" optimization profile.
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

package PdfToolsOptimizerSimple;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.optimization.Optimizer;
import com.pdftools.optimization.profiles.*;

public class PdfToolsOptimizerSimple
{
    static void usage() {
        System.out.println("Usage: java pdftoolsoptimizersimple <inputPath> <outputPath>");
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

            optimize(args[0], args[1]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void optimize(String inPath, String outPath) throws Exception
    {
        // Create the profile that defines the optimization parameters.
        // The Web profile is used to optimize documents for electronic document exchange.
        Web profile = new Web();

        // Optionally the profile's parameters can be changed according to the 
        // requirements of your optimization process.

        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr);

            // Create output stream
            FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

            // Optimize the document
            Document outDoc = new Optimizer().optimizeDocument(inDoc, outStr, profile))
        {
        }
    }
}
