/****************************************************************************
 *
 * File:            pdftoolsencrypt.java
 *
 * Usage:           java pdftoolsencrypt <password> <inputPath> <outputPath>
 *                  
 * Title:           Encrypt a PDF
 *                  
 * Description:     Encrypt a PDF document with a user password.
 *                  To open the document, the user password is required.
 *                  
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2025 PDF Tools AG, Switzerland
 *                  Permission to use, copy, modify, and distribute this
 *                  software and its documentation for any purpose and without
 *                  fee is hereby granted, provided that the above copyright
 *                  notice appear in all copies and that both that copyright
 *                  notice and this permission notice appear in supporting
 *                  documentation. This software is provided "as is" without
 *                  express or implied warranty.
 *
 ***************************************************************************/

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.Document;
import com.pdftools.pdf.Encryption;
import com.pdftools.pdf.Permission;
import com.pdftools.sign.*;

public class PdfToolsEncrypt
{
    private static void loadLibrary() {
        // Try to find and load the native library from classpath
        // NOTE: This is not necessary if the native library is either in one of the paths in java.library.path
        //       or in a system library directory.
        tryLoadLibrary("lib/win-x64", "", "dll");
        tryLoadLibrary("lib/win-x86", "", "dll");
        tryLoadLibrary("lib/win-arm64", "", "dll");
        tryLoadLibrary("lib/linux-x64", "lib", "so");
        tryLoadLibrary("lib/osx-arm64", "lib", "dylib");
        tryLoadLibrary("lib/osx-x64", "lib", "dylib");
    }

    private static void tryLoadLibrary(String platform, String prefix, String extension) {
        try {
            java.net.URL urlPdfToolsSdk = ClassLoader.getSystemResource(platform + File.separator + prefix + "PdfToolsSdk." + extension);
            if (urlPdfToolsSdk != null && urlPdfToolsSdk.getProtocol().toLowerCase().equals("file"))
                System.load(new File(urlPdfToolsSdk.toURI()).getAbsolutePath());
        } catch (java.net.URISyntaxException ex) {
        } catch (UnsatisfiedLinkError ex) {
        }
    }

    static void usage() {
        System.out.println("Usage: java pdftoolsencrypt <password> <inputPath> <outputPath>");
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
            // Load the native library
            loadLibrary();

            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("<PDFSDK,V1,MGAASQD6L2JMQHL54PK08RQX8GG4SS0M8DAHVPH0VMP3NB8R9DUK>");

            // Encrypt a PDF document
            encrypt(args[0], args[1], args[2]);

            System.out.println("Execution successful.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static void encrypt(String password, String inPath, String outPath) throws Exception
    {
        try (
            // Open input document
            FileStream inStr = new FileStream(inPath, FileStream.Mode.READ_ONLY);
            Document inDoc = Document.open(inStr))
        {
            // Set encryption options
            OutputOptions outputOptions = new OutputOptions();

            // Set a user password that will be required to open the document.
            // Note that this will remove PDF/A conformance of input files (see warning category WarningCategory.PDF_A_REMOVED)
            outputOptions.setEncryption(new Encryption(password, null, Permission.ALL));

            // Allow removal of signatures. Otherwise the Encryption property is ignored for signed input documents
            // (see warning category WarningCategory.SIGNED_DOC_ENCRYPTION_UNCHANGED).
            outputOptions.setRemoveSignatures(SignatureRemoval.SIGNED);

            try(
                // Create output stream
                FileStream outStr = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW);

                // Encrypt the document
                Document outDoc = new Signer().process(inDoc, outStr, outputOptions))
            {
            }
        }
    }
}
