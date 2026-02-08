''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsAddAppearanceSignatureField <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>
'                  
' Title:           Sign a PDF and apply a visual signature appearance
'                  
' Description:     Sign a PDF document using a provided certificate and
'                  apply a visual signature appearance. This process
'                  requires an input PDF that already contains a signature
'                  field. The provided certificate is used to sign the
'                  document and attach the signature to the existing field.
'                  The visual appearance of the signature is updated using
'                  an XML or JSON file, allowing the addition of text,
'                  images, or PDFs. This signature consists of both a
'                  visible and a non-visible part. Only the non-visible part
'                  is used by other applications to verify the integrity of
'                  the signed part of the document and validate the signing
'                  certificate. The signing certificate is retrieved from a
'                  password-protected PKCS#12 file (.pfx or .p12).
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

Imports PdfTools.Pdf
Imports PdfTools.Sign
Imports System.IO

Namespace PdfToolsAddAppearanceSignatureField
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsAddAppearanceSignatureField <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>")
        End Sub

        Sub Main(args As String())
            ' Check command line parameters
            If args.Length < 5 OrElse args.Length > 5 Then
                Usage()
                Return
            End If

            Try
                ' By default, a test license key is active. In this case, a watermark is added to the output. 
                ' If you have a license key, please uncomment the following call and set the license key.
                ' PdfTools.Sdk.Initialize("LICENSE-KEY")

                ' Sign a PDF document
                AddAppearanceSignatureField(args(0), args(1), args(2), args(3), args(4))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub AddAppearanceSignatureField(certificateFile As String, password As String, appConfigFile As String, inPath As String, outPath As String)
            ' Create a session to the built-in cryptographic provider
            Using session As New PdfTools.Crypto.Providers.BuiltIn.Provider()

                ' Create signature configuration from PFX (or P12) file
                Using pfxStr = File.OpenRead(certificateFile)
                    Dim signature = session.CreateSignatureFromCertificate(pfxStr, password)

                    ' Open input document
                    Using inStr = File.OpenRead(inPath)
                        Using inDoc = Document.Open(inStr)

                            ' Choose first signature field
                            For Each field In inDoc.SignatureFields
                                If field IsNot Nothing Then
                                    signature.FieldName = field.FieldName
                                    Exit For
                                End If
                            Next

                            ' Create stream for output file
                            Using outStr = File.Create(outPath)

                                ' Create appearance from either an XML or a JSON file
                                Using appStream = File.OpenRead(appConfigFile)
                                    If Path.GetExtension(appConfigFile).ToLower() = ".xml" Then
                                        signature.Appearance = Appearance.CreateFromXml(appStream)
                                    Else
                                        signature.Appearance = Appearance.CreateFromJson(appStream)
                                    End If

                                    signature.Appearance.CustomTextVariables.Add("company", "Daily Planet")

                                    ' Sign the input document
                                    Using outDoc = New Signer().Sign(inDoc, signature, outStr)
                                    End Using
                                End Using
                            End Using
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
