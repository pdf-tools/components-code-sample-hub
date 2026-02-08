/****************************************************************************
 *
 * File:            pdftoolssignaturesvalidate.java
 *
 * Usage:           java pdftoolssignaturesvalidate <inputPath> [<certificateDirectory>]
 *                  
 * Title:           Validate the signatures contained in an input document
 *                  
 * Description:     Extract and validate signature information for all
 *                  digital signatures in the input document, then print the
 *                  results to the console.
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

package PdfToolsSignaturesValidate;

import java.util.stream.Collectors;

import java.security.MessageDigest;
import java.util.EnumSet;
import java.io.File;
import com.pdftools.sys.FileStream;
import com.pdftools.Sdk;
import com.pdftools.pdf.*;
import com.pdftools.signaturevalidation.*;
import com.pdftools.signaturevalidation.profiles.*;


public class PdfToolsSignaturesValidate
{
    static void usage() {
        System.out.println("Usage: java pdftoolssignaturesvalidate <inputPath> [<certificateDirectory>]");
    }

    public static void main(String[] args)
    {
        // Check command line parameters
        if (args.length < 1) {
            usage();
            return;
        }

        try
        {
            // By default, a test license key is active. In this case, a watermark is added to the output. 
            // If you have a license key, please uncomment the following call and set the license key.
            // Sdk.initialize("LICENSE-KEY");    

            String inputFile = args[0];
            String certDir = (args.length == 2 ? args[1] : null);

            // Run the validate process passing the file and an optional certificate directory
            int status = validate(inputFile, certDir);

            System.out.println("Execution successful.");
            System.exit(status);
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
    }    

    private static int validate(String inputFile, String certDir)
    {
        // Use the default validation profile as a base for further settings
        Profile profile = new Default();

        // For offline operation, build a custom trust list from the file system
        // and disable external revocation checks
        if (certDir != null && !certDir.isEmpty())
        {
            System.out.println("Using 'offline' validation mode with custom trust list.");
            System.out.println();

            // create a CustomTrustList to hold the certificates
            CustomTrustList ctl = new CustomTrustList();

            // Iterate through files in the certificate directory and add certificates
            // to the custom trust list
            File dir = new File(certDir);
            File[] directoryListing = dir.listFiles();
            if (directoryListing != null)
            {
                for (File child : directoryListing)
                {
                    String fileName = child.getName();
                    try (
                        FileStream certStr = new FileStream(child.getPath(), FileStream.Mode.READ_ONLY))
                    {
                        if (fileName.endsWith(".cer") || fileName.endsWith(".pem"))
                        {
                            ctl.addCertificates(certStr);
                        }
                        else if (fileName.endsWith(".p12") || fileName.endsWith(".pfx"))
                        {
                            // If a password is required, use addArchive(certStr, password).
                            ctl.addArchive(certStr);
                        }
                    }
                    catch (Exception e)
                    {
                        System.out.println("Could not add certificate '" + child.getName() + "' to custom trust list: " + e.getMessage());
                    }
                }
            }
            else
            {
                // Handle the case where dir is not a directory
                System.out.println("Directory " + certDir + " is missing. No certificates were added to the custom trust list.");
            }
            System.out.println();

            // Assign the custom trust list to the validation profile
            profile.setCustomTrustList(ctl);

            // Allow validation from embedded file sources and the custom trust list
            ValidationOptions vo = profile.getValidationOptions();
            vo.setTimeSource(EnumSet.of(TimeSource.PROOF_OF_EXISTENCE, TimeSource.EXPIRED_TIME_STAMP, TimeSource.SIGNATURE_TIME));
            vo.setCertificateSources(EnumSet.of(DataSource.EMBED_IN_SIGNATURE, DataSource.EMBED_IN_DOCUMENT, DataSource.CUSTOM_TRUST_LIST));

            // Disable revocation checks.
            profile.getSigningCertTrustConstraints().setRevocationCheckPolicy(RevocationCheckPolicy.NO_CHECK);
            profile.getTimeStampTrustConstraints().setRevocationCheckPolicy(RevocationCheckPolicy.NO_CHECK);
        }

        // Validate ALL signatures in the document (not only the latest)
        SignatureSelector signatureSelector = SignatureSelector.ALL;

        // Create the validator object and event listeners
        Validator validator = new Validator();
        validator.addConstraintListener(e -> {
            System.out.println("  - " + e.getSignature().getName() + (e.getDataPart().length() > 0 ? (": " + e.getDataPart()) : "") + ": " +
                constraintToString(e.getIndication(), e.getSubIndication(), e.getMessage(), true));
        });

        try (
            FileStream inStr = new FileStream(inputFile, FileStream.Mode.READ_ONLY);
            // Open input document
            // If a password is required, use open(inStr, password)
            Document document = Document.open(inStr);
        )
        {
            // Run the validate method passing the document, profile and selector
            System.out.println("Validation Constraints");
            ValidationResults results = validator.validate(document, profile, signatureSelector);

            System.out.println();
            System.out.println("Signatures validated: " + results.size());
            System.out.println();

            // Print results
            results.forEach(result -> {
                SignedSignatureField field = result.getSignatureField();
                System.out.println(field.getFieldName() + " of " + field.getName());
                try
                {
                    System.out.println("  - Revision  : " + (field.getRevision().getIsLatest() ? "latest" : "intermediate"));
                }
                catch (Exception ex)
                {
                    System.out.println("Unable to validate document Revision: " + ex.getMessage());
                }

                printContent(result.getSignatureContent(), result.getSignatureField().getFullRevisionCovered());
                System.out.println();
            });

            return 0;
        }
        catch (Exception ex)
        {
            System.out.println("Unable to validate file: " + ex.getMessage());
            return 5;
        }
    }

    // Helper functions to print signature validation details

 
    private static void printContent(SignatureContent content, Boolean isFullRevisionCovered)
    {
        if (content != null)
        {
            System.out.println("  - Validity  : " + constraintToString(content.getValidity(), isFullRevisionCovered));
            switch (content.getClass().getSimpleName())
            {
                case "UnsupportedSignatureContent":
                    break;
                case "CmsSignatureContent":
                    {
                        CmsSignatureContent signature = (CmsSignatureContent)content;
                        System.out.println("  - Validation: " + signature.getValidationTime() + " from " + signature.getValidationTimeSource());
                        System.out.println("  - Hash      : " + signature.getHashAlgorithm());
                        System.out.println("  - Signing Cert");
                        printContent(signature.getSigningCertificate());
                        System.out.println("  - Chain");
                        signature.getCertificateChain().forEach(cert -> {
                            System.out.println("  - Issuer Cert " + (signature.getCertificateChain().indexOf(cert) + 1));
                            printContent(cert);
                        });
                        System.out.println("  - Chain     : " + (signature.getCertificateChain().getIsComplete() ? "complete" : "incomplete") + " chain");
                        System.out.println("  Time-Stamp");
                        printContent(signature.getTimeStamp(), true);
                        break;
                    }
                case "TimeStampContent":
                    {
                        TimeStampContent timeStamp = (TimeStampContent)content;
                        System.out.println("  - Validation: " + timeStamp.getValidationTime() + " from " + timeStamp.getValidationTimeSource());
                        System.out.println("  - Hash      : " + timeStamp.getHashAlgorithm());
                        System.out.println("  - Time      : " + timeStamp.getDate());
                        System.out.println("  - Signing Cert");
                        printContent(timeStamp.getSigningCertificate());
                        System.out.println("  - Chain");
                        timeStamp.getCertificateChain().forEach(cert -> {
                            System.out.println("  - Issuer Cert " + (timeStamp.getCertificateChain().indexOf(cert) + 1));
                            printContent(cert);
                        });
                        System.out.println("  - Chain      : " + (timeStamp.getCertificateChain().getIsComplete() ? "complete" : "incomplete") + " chain");
                        break;
                    }
                default:
                    System.out.println("Unsupported signature content type " + content.getClass().getName());
                    break;
            }
        }
        else
        {
            System.out.println("  - null");
        }
    }

         
    private static void printContent(Certificate cert)
    { 
        if(cert != null)
        {
            System.out.println("    - Subject    : " + cert.getSubjectName());
            System.out.println("    - Issuer     : " + cert.getIssuerName());
            System.out.println("    - Validity   : " + cert.getNotBefore() + " - " + cert.getNotAfter());
            try {
                System.out.println("    - Fingerprint: " + formatSha1Digest(new java.math.BigInteger(1, (MessageDigest.getInstance("SHA-1").digest(cert.getRawData()))).toByteArray(), "-"));
            } catch (Exception ex) {
                System.out.println(ex.getMessage());
            }
            System.out.println("    - Source     : " + cert.getSource());
            System.out.println("    - Validity   : " + constraintToString(cert.getValidity(), true));
        }
        else
        {
            System.out.println("    - null");
        }
    }

 
    private static String constraintToString(ConstraintResult constraint, Boolean isFullRevisionCovered)
    {
        return constraintToString(constraint.getIndication(), constraint.getSubIndication(), constraint.getMessage(), isFullRevisionCovered);
    }

 
    private static String constraintToString(Indication indication, SubIndication subIndication, String message, Boolean isFullRevisionCovered)
    {
        if (isFullRevisionCovered == null || isFullRevisionCovered)
        {
            return (indication == Indication.VALID ? "" : (indication == Indication.INDETERMINATE ? "?" : "!")) + "" +
                subIndication + " " +
                message;
        }

        String byteRangeInvalid = "!Invalid signature byte range.";
        if (indication == Indication.VALID)
            return byteRangeInvalid;
        else
            return byteRangeInvalid + " " + subIndication + " " + message;
    }

    // Helper function to generate a delimited SHA-1 digest string
    private static String formatSha1Digest(byte[] bytes, String delimiter) {
        StringBuilder result = new StringBuilder();
        for (byte aByte : bytes) {
            int decimal = (int) aByte & 0xff;               
            String hex = Integer.toHexString(decimal);
            if (hex.length() % 2 == 1)                   
                hex = "0" + hex;
            result.append(hex.toUpperCase() + delimiter);
        }
        return result.substring(0, result.length() - delimiter.length());
    }

}
