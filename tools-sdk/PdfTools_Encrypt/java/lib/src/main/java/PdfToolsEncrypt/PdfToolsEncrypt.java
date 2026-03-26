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

package PdfToolsEncrypt;

import java.util.stream.Collectors;

import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.Document;
import com.pdftools.pdf.Encryption;
import com.pdftools.pdf.Permission;
import com.pdftools.sign.*;

public class PdfToolsEncrypt
{
    private static void loadNativeLibrary(String directoryPath) throws Exception {
        File dir = new File(directoryPath);

        if (!dir.exists() || !dir.isDirectory()) {
            System.err.println("Error: Directory does not exist or is not a directory: " + directoryPath);
            return;
        }

        // Determine platform-specific library extensions
        String osName = System.getProperty("os.name").toLowerCase();
        String osArch = System.getProperty("os.arch").toLowerCase();

        String extension;
        if (osName.contains("win")) {
            extension = ".dll";
        } else if (osName.contains("mac")) {
            extension = ".dylib";
        } else if (osName.contains("nix") || osName.contains("nux") || osName.contains("aix")) {
            extension = ".so";
        } else {
            throw new UnsupportedOperationException("Unsupported operating system: " + osName);
        }

        // Search for files with the correct extension
        File[] matchingFiles = dir.listFiles((dir1, name) -> name.endsWith(extension));

        if (matchingFiles == null || matchingFiles.length == 0) {
            throw new Exception("Error: No native library file found for platform " + osName + " (" + osArch + ") in directory: " + directoryPath);
        } else if (matchingFiles.length > 1) {
                String filePaths = java.util.Arrays.stream(matchingFiles)
                        .map(File::getAbsolutePath)
                        .collect(Collectors.joining(", "));
                throw new Exception("Error: Multiple native library files found for platform " + osName + " (" + osArch + ") in directory: " + directoryPath + ". Files: " + filePaths);
        } else {
            // Load the single matching library
            try {
                System.load(matchingFiles[0].getAbsolutePath());
            } catch (UnsatisfiedLinkError e) {
                System.err.println("Error: Failed to load native library: " + matchingFiles[0].getAbsolutePath());
                e.printStackTrace();
            }
        }
    }

    private static void loadLibrary(){
        String userHome = System.getProperty("user.home");
        String libDir = userHome + "/.m2/repository/com/pdftools/pdftools-sdk/1.5.0";
        try {
    	    loadNativeLibrary(libDir);
    	} catch (Exception e) {
    		System.out.println(e.getMessage());
    		e.printStackTrace();
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
