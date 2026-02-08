/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           PdfToolsSignaturesValidate <inputPath> [<certificateDirectory>]
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

using PdfTools;
using PdfTools.Pdf;
using PdfTools.SignatureValidation;
using PdfTools.SignatureValidation.Profiles;
using System;
using System.IO;
using System.Text;
using System.Security.Cryptography;
using System.Numerics;

namespace PdfToolsSignaturesValidate
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: PdfToolsSignaturesValidate <inputPath> [<certificateDirectory>]");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 1)
            {
                Usage();
                return;
            }

            try
            {
                // By default, a test license key is active. In this case, a watermark is added to the output. 
                // If you have a license key, please uncomment the following call and set the license key.
                // Sdk.Initialize("LICENSE-KEY");   

                var inputFile = args[0];
                var certDir = (args.Length == 2 ? args[1] : null);

                // Run the validate process passing the file and an optional certificate directory
                Console.WriteLine(Validate(inputFile, certDir));
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static int Validate(string inputFile, string certDir)
        {
            // Use the default validation profile as a base for further settings
            var profile = new Default();

            // For offline operation, build a custom trust list from the file system 
            // and disable external revocation checks
            if (certDir != null && certDir.Length != 0)
            {
                Console.WriteLine("Using 'offline' validation mode with custom trust list.");
                Console.WriteLine();

                // create a CustomTrustList to hold the certificates
                var ctl = new CustomTrustList();

                // Iterate through files in the certificate directory and add certificates
                // to the custom trust list
                if (Directory.Exists(certDir))
                {
                    var directoryListing = Directory.EnumerateFiles(certDir);
                    foreach (string fileName in directoryListing)
                    {
                        try
                        {
                            using var certStr = File.OpenRead(fileName);

                            if (fileName.EndsWith(".cer") || fileName.EndsWith(".pem"))
                            {
                                ctl.AddCertificates(certStr);
                            }
                            else if (fileName.EndsWith(".p12") || fileName.EndsWith(".pfx"))
                            {
                                // If a password is required, use addArchive(certStr, password).
                                ctl.AddArchive(certStr);
                            }
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine("Could not add certificate '" + fileName + "' to custom trust list: " + e.Message);
                        }
                    }
                }
                else
                {
                    // Handle the case where dir is not a directory
                    Console.WriteLine("Directory " + certDir + " is missing. No certificates were added to the custom trust list.");
                }
                Console.WriteLine();

                // Assign the custom trust list to the validation profile
                profile.CustomTrustList = ctl;

                // Allow validation from embedded file sources and the custom trust list
                var vo = profile.ValidationOptions;
                vo.TimeSource = TimeSource.ProofOfExistence | TimeSource.ExpiredTimeStamp | TimeSource.SignatureTime;
                vo.CertificateSources = DataSource.EmbedInSignature | DataSource.EmbedInDocument | DataSource.CustomTrustList;

                // Disable revocation checks.
                profile.SigningCertTrustConstraints.RevocationCheckPolicy = RevocationCheckPolicy.NoCheck;
                profile.TimeStampTrustConstraints.RevocationCheckPolicy = RevocationCheckPolicy.NoCheck;
            }

            // Validate ALL signatures in the document (not only the latest)
            var signatureSelector = SignatureSelector.All;

            // Create the validator object and event listeners
            var validator = new Validator();
            validator.Constraint += (s, e) =>
            {
                Console.WriteLine("  - " + e.Signature.Name + (e.DataPart.Length > 0 ? (": " + e.DataPart) : "") + ": " +
                    ConstraintToString(e.Indication, e.SubIndication, e.Message));
            };

            try
            {
                using var inStr = File.OpenRead(inputFile);
                // Open input document
                // If a password is required, use Open(inStr, password)
                using var document = Document.Open(inStr);

                // Run the validate method passing the document, profile and selector
                Console.WriteLine("Validation Constraints");
                var results = validator.Validate(document, profile, signatureSelector);

                Console.WriteLine();
                Console.WriteLine("Signatures validated: " + results.Count);
                Console.WriteLine();

                // Print results
                foreach (var result in results)
                {
                    var field = result.SignatureField;
                    Console.WriteLine(field.FieldName + " of " + field.Name);
                    try
                    {
                        Console.WriteLine("  - Revision  : " + (field.Revision.IsLatest ? "latest" : "intermediate"));
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Unable to validate document Revision: " + ex.Message);
                    }

                    PrintContent(result.SignatureContent, result.SignatureField.IsFullRevisionCovered);
                    Console.WriteLine();
                }

                return 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Unable to validate file: " + ex.Message);
                return 5;
            }
        }

        // Helper functions to print signature validation details

        private static void PrintContent(SignatureContent content, bool? isFullRevisionCovered)
        {
            if (content != null)
            {
                Console.WriteLine("  - Validity  : " + ConstraintToString(content.Validity, isFullRevisionCovered));
                switch (content)
                {
                    case UnsupportedSignatureContent:
                        break;
                    case CmsSignatureContent signature:
                        {
                            Console.WriteLine("  - Validation: " + signature.ValidationTime + " from " + signature.ValidationTimeSource);
                            Console.WriteLine("  - Hash      : " + signature.HashAlgorithm);
                            Console.WriteLine("  - Signing Cert");
                            PrintContent(signature.SigningCertificate);
                            Console.WriteLine("  - Chain");
                            foreach (var cert in signature.CertificateChain)
                            {
                                Console.WriteLine("  - Issuer Cert " + (signature.CertificateChain.IndexOf(cert) + 1));
                                PrintContent(cert);
                            }
                            Console.WriteLine("  - Chain     : " + (signature.CertificateChain.IsComplete ? "complete" : "incomplete") + " chain");
                            Console.WriteLine("  Time-Stamp");
                            PrintContent(signature.TimeStamp, null);
                            break;
                        }
                    case TimeStampContent timeStamp:
                        {
                            Console.WriteLine("  - Validation: " + timeStamp.ValidationTime + " from " + timeStamp.ValidationTimeSource);
                            Console.WriteLine("  - Hash      : " + timeStamp.HashAlgorithm);
                            Console.WriteLine("  - Time      : " + timeStamp.Date);
                            Console.WriteLine("  - Signing Cert");
                            PrintContent(timeStamp.SigningCertificate);
                            Console.WriteLine("  - Chain");
                            foreach (var cert in timeStamp.CertificateChain)
                            {
                                Console.WriteLine("  - Issuer Cert " + (timeStamp.CertificateChain.IndexOf(cert) + 1));
                                PrintContent(cert);
                            }
                            Console.WriteLine("  - Chain      : " + (timeStamp.CertificateChain.IsComplete ? "complete" : "incomplete") + " chain");
                            break;
                        }
                    default:
                        Console.WriteLine("Unsupported signature content type " + content.GetType().Name);
                        break;
                }
            }
            else
            {
                Console.WriteLine("  - null");
            }
        }

        private static void PrintContent(Certificate cert)
        {
            if(cert != null)
            {
                Console.WriteLine("    - Subject    : " + cert.SubjectName);
                Console.WriteLine("    - Issuer     : " + cert.IssuerName);
                Console.WriteLine("    - Validity   : " + cert.NotBefore + " - " + cert.NotAfter);
                try
                {
                    Console.WriteLine("    - Fingerprint: " + FormatSha1Digest(new BigInteger(SHA1.Create().ComputeHash(cert.RawData)).ToByteArray(), "-"));
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
                Console.WriteLine("    - Source     : " + cert.Source);
                Console.WriteLine("    - Validity   : " + ConstraintToString(cert.Validity, null));
            }
            else
            {
                Console.WriteLine("    - null");
            }
        }

        private static String ConstraintToString(ConstraintResult constraint, bool? isFullRevisionCovered)
        {
            return ConstraintToString(constraint.Indication, constraint.SubIndication, constraint.Message, isFullRevisionCovered);
        }

        private static string ConstraintToString(Indication indication, SubIndication subIndication, string message, bool? isFullRevisionCovered = null)
        {
            if (isFullRevisionCovered is null || isFullRevisionCovered.Value)
            {
                return (indication == Indication.Valid ? "" : indication == Indication.Indeterminate ? "?" : "!") + subIndication + " " + message;
            }
            string byteRangeInvalid = "!Invalid signature byte range.";
            return indication == Indication.Valid ? byteRangeInvalid : $"{byteRangeInvalid} {subIndication} {message}";
        }

        // Helper function to generate a delimited SHA-1 digest string
        private static String FormatSha1Digest(byte[] bytes, String delimiter)
        {
            var result = new StringBuilder();
            foreach (byte aByte in bytes)
            {
                int number = (int)aByte & 0xff;
                String hex = number.ToString("X2");
                result.Append(hex.ToUpper() + delimiter);
            }
            return result.ToString().Substring(0, result.Length - delimiter.Length);
        }
    }
}
