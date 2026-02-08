''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsSignaturesValidate <inputPath> [<certificateDirectory>]
'                  
' Title:           Validate the signatures contained in an input document
'                  
' Description:     Extract and validate signature information for all
'                  digital signatures in the input document, then print the
'                  results to the console.
'                  
' Author:          PDF Tools AG
'
' Copyright:       Copyright(C) 2026 PDF Tools AG, Switzerland
'                  Permission to use, copy, modify, And distribute this
'                  software And its documentation for any purpose And without
'                  fee Is hereby granted, provided that the above copyright
'                  notice appear in all copies And that both that copyright
'                  notice And this permission notice appear in supporting
'                  documentation. This software Is provided "as is" without
'                  express Or implied warranty.
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Imports PdfTools
Imports PdfTools.SignatureValidation
Imports PdfTools.SignatureValidation.Profiles
Imports System.IO
Imports System.Text
Imports System.Security.Cryptography
Imports System.Numerics

Namespace PdfToolsSignaturesValidate
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsSignaturesValidate <inputPath> [<certificateDirectory>]")
        End Sub

        Sub Main(args As String())
            ' Check command line parameters
            If args.Length < 1 Then
                Usage()
                Return
            End If

            Try
                ' By default, a test license key is active. In this case, a watermark is added to the output. 
                ' If you have a license key, please uncomment the following call and set the license key.
                ' PdfTools.Sdk.Initialize("LICENSE-KEY")

                Dim inputFile = args(0)
                Dim certDir = If(args.Length = 2, args(1), Nothing)

                ' Run the validate process passing the file and an optional certificate directory
                Console.WriteLine(Validate(inputFile, certDir))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Function Validate(inputFile As String, certDir As String) As Integer
            ' Use the default validation profile as a base for further settings
            Dim profile = New PdfTools.SignatureValidation.Profiles.Default()

            ' For offline operation, build a custom trust list from the file system 
            ' and disable external revocation checks
            If Not String.IsNullOrEmpty(certDir) Then
                Console.WriteLine("Using 'offline' validation mode with custom trust list.")
                Console.WriteLine()

                ' create a CustomTrustList to hold the certificates
                Dim ctl = New CustomTrustList()

                ' Iterate through files in the certificate directory and add certificates
                ' to the custom trust list
                If Directory.Exists(certDir) Then
                    Dim directoryListing = Directory.EnumerateFiles(certDir)
                    For Each fileName In directoryListing
                        Try
                            Using certStr = File.OpenRead(fileName)
                                If fileName.EndsWith(".cer") OrElse fileName.EndsWith(".pem") Then
                                    ctl.AddCertificates(certStr)
                                ElseIf fileName.EndsWith(".p12") OrElse fileName.EndsWith(".pfx") Then
                                    ' If a password is required, use addArchive(certStr, password).
                                    ctl.AddArchive(certStr)
                                End If
                            End Using
                        Catch e As Exception
                            Console.WriteLine("Could not add certificate '" & fileName & "' to custom trust list: " & e.Message)
                        End Try
                    Next
                Else
                    ' Handle the case where dir is not a directory
                    Console.WriteLine("Directory " & certDir & " is missing. No certificates were added to the custom trust list.")
                End If
                Console.WriteLine()

                ' Assign the custom trust list to the validation profile
                profile.CustomTrustList = ctl

                ' Allow validation from embedded file sources and the custom trust list
                Dim vo = profile.ValidationOptions
                vo.TimeSource = TimeSource.ProofOfExistence Or TimeSource.ExpiredTimeStamp Or TimeSource.SignatureTime
                vo.CertificateSources = DataSource.EmbedInSignature Or DataSource.EmbedInDocument Or DataSource.CustomTrustList

                ' Disable revocation checks.
                profile.SigningCertTrustConstraints.RevocationCheckPolicy = RevocationCheckPolicy.NoCheck
                profile.TimeStampTrustConstraints.RevocationCheckPolicy = RevocationCheckPolicy.NoCheck
            End If

            ' Validate ALL signatures in the document (not only the latest)
            Dim signatureSelector = SignatureValidation.SignatureSelector.All

            ' Create the validator object and event listeners
            Dim validator = New Validator()
            AddHandler validator.Constraint, Sub(s, e)
                                                 Console.WriteLine("  - " & e.Signature.Name & If(e.DataPart.Length > 0, ": " & e.DataPart, "") & ": " &
                                                   ConstraintToString(e.Indication, e.SubIndication, e.Message))
                                             End Sub

            Try
                Using inStr = File.OpenRead(inputFile)
                    ' Open input document
                    ' If a password is required, use Open(inStr, password)
                    Using document = Pdf.Document.Open(inStr)

                        ' Run the validate method passing the document, profile and selector
                        Console.WriteLine("Validation Constraints")
                        Dim results = validator.Validate(document, profile, signatureSelector)

                        Console.WriteLine()
                        Console.WriteLine("Signatures validated: " & results.Count)
                        Console.WriteLine()

                        ' Print results
                        For Each result In results
                            Dim field = result.SignatureField
                            Console.WriteLine(field.FieldName & " of " & field.Name)
                            Try
                                Console.WriteLine("  - Revision  : " & If(field.Revision.IsLatest, "latest", "intermediate"))
                            Catch ex As Exception
                                Console.WriteLine("Unable to validate document Revision: " & ex.Message)
                            End Try

                            PrintContent(result.SignatureContent, field.IsFullRevisionCovered)
                            Console.WriteLine()
                        Next

                        Return 0
                    End Using
                End Using
            Catch ex As Exception
                Console.WriteLine("Unable to validate file: " & ex.Message)
                Return 5
            End Try
        End Function

        ' Helper functions to print signature validation details
        Private Sub PrintContent(content As SignatureContent, isFullRevisionCovered As Boolean?)
            If content IsNot Nothing Then
                Console.WriteLine("  - Validity  : " & ConstraintToString(content.Validity, isFullRevisionCovered))
                If TypeOf content Is UnsupportedSignatureContent Then
                    ' Do nothing
                ElseIf TypeOf content Is CmsSignatureContent Then
                    Dim signature As CmsSignatureContent = CType(content, CmsSignatureContent)
                    Console.WriteLine("  - Validation: " & signature.ValidationTime.ToString() & " from " & signature.ValidationTimeSource.ToString())
                    Console.WriteLine("  - Hash      : " & signature.HashAlgorithm.ToString())
                    Console.WriteLine("  - Signing Cert")
                    PrintContent(signature.SigningCertificate)
                    Console.WriteLine("  - Chain")
                    For Each cert In signature.CertificateChain
                        Console.WriteLine("  - Issuer Cert " & (signature.CertificateChain.IndexOf(cert) + 1))
                        PrintContent(cert)
                    Next
                    Console.WriteLine("  - Chain     : " & If(signature.CertificateChain.IsComplete, "complete", "incomplete") & " chain")
                    Console.WriteLine("  Time-Stamp")
                    PrintContent(signature.TimeStamp, Nothing)
                ElseIf TypeOf content Is TimeStampContent Then
                    Dim timeStamp As TimeStampContent = CType(content, TimeStampContent)
                    Console.WriteLine("  - Validation: " & timeStamp.ValidationTime.ToString() & " from " & timeStamp.ValidationTimeSource.ToString())
                    Console.WriteLine("  - Hash      : " & timeStamp.HashAlgorithm.ToString())
                    Console.WriteLine("  - Time      : " & timeStamp.Date.ToString())
                    Console.WriteLine("  - Signing Cert")
                    PrintContent(timeStamp.SigningCertificate)
                    Console.WriteLine("  - Chain")
                    For Each cert In timeStamp.CertificateChain
                        Console.WriteLine("  - Issuer Cert " & (timeStamp.CertificateChain.IndexOf(cert) + 1))
                        PrintContent(cert)
                    Next
                    Console.WriteLine("  - Chain      : " & If(timeStamp.CertificateChain.IsComplete, "complete", "incomplete") & " chain")
                Else
                    Console.WriteLine("Unsupported signature content type " & content.GetType().Name)
                End If
            Else
                Console.WriteLine("  - null")
            End If
        End Sub

        Private Sub PrintContent(cert As Certificate)
            If cert IsNot Nothing Then
                Console.WriteLine("    - Subject    : " & cert.SubjectName)
                Console.WriteLine("    - Issuer     : " & cert.IssuerName)
                Console.WriteLine("    - Validity   : " & cert.NotBefore.ToString() & " - " & cert.NotAfter.ToString())
                Try
                    Console.WriteLine("    - Fingerprint: " & FormatSha1Digest(New BigInteger(SHA1.Create().ComputeHash(cert.RawData)).ToByteArray(), "-"))
                Catch ex As Exception
                    Console.WriteLine(ex.Message)
                End Try
                Console.WriteLine("    - Source     : " & cert.Source.ToString())
                Console.WriteLine("    - Validity   : " & ConstraintToString(cert.Validity))
            Else
                Console.WriteLine("    - null")
            End If
        End Sub

        Private Function ConstraintToString(constraint As ConstraintResult) As String
            Return ConstraintToString(constraint.Indication, constraint.SubIndication, constraint.Message)
        End Function

        Private Function ConstraintToString(constraint As ConstraintResult, isFullRevisionCovered As Boolean?) As String
            Return ConstraintToString(constraint.Indication, constraint.SubIndication, constraint.Message, isFullRevisionCovered)
        End Function

        Private Function ConstraintToString(indication As Indication, subIndication As SubIndication, message As String) As String
            Return If(indication = indication.Valid, "", If(indication = indication.Indeterminate, "?", "!")) & "" &
                subIndication.ToString() & " " &
                message
        End Function

        Private Function ConstraintToString(indication As Indication, subIndication As SubIndication, message As String, isFullRevisionCovered As Boolean?) As String
            If isFullRevisionCovered Is Nothing OrElse isFullRevisionCovered.Value Then
                Return If(indication = indication.Valid, "", If(indication = indication.Indeterminate, "?", "!")) & "" &
                    subIndication.ToString() & " " &
                    message
            Else
                Dim byteRangeInvalid = "!Invalid signature byte range."
                If indication = indication.Valid Then
                    Return byteRangeInvalid
                Else
                    Return byteRangeInvalid & " " & subIndication.ToString() & " " & message
                End If
            End If
        End Function

        ' Helper function to generate a delimited SHA-1 digest string
        Private Function FormatSha1Digest(bytes As Byte(), delimiter As String) As String
            Dim result = New StringBuilder()
            For Each aByte In bytes
                Dim number = CInt(aByte) And &HFF
                Dim hex = number.ToString("X2")
                result.Append(hex.ToUpper() & delimiter)
            Next
            Return result.ToString().Substring(0, result.Length - delimiter.Length)
        End Function
    End Module
End Namespace
