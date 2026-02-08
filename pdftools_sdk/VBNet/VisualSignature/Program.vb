''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsVisualSignature <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>
'                  
' Title:           Sign a PDF and add a visual appearance
'                  
' Description:     Add a document signature with a visual appearance.
'                  The visual appearance is configured using an XML or JSON
'                  file, allowing the addition of text, images, or PDFs.
'                  
'                  This signature consists of both a visible and a
'                  non-visible part.
'                  Only the non-visible part verifies the integrity of the
'                  signed part of the document and authenticates the
'                  signer's identity.
'                  The signing certificate is read from a password-protected
'                  PKCS#12 file (.pfx or .p12).
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
Imports BuiltIn = PdfTools.Crypto.Providers.BuiltIn

Namespace PdfToolsVisualSignature
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsVisualSignature <certificateFile> <password> <appConfigFile> <inputPath> <outputPath>")
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
                Sign(args(0), args(1), args(2), args(3), args(4))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub Sign(certificateFile As String, password As String, appConfigFile As String, inPath As String, outPath As String)
            ' Create a session to the built-in cryptographic provider
            Using session As New BuiltIn.Provider()

                ' Open certificate file
                Using pfxStr = File.OpenRead(certificateFile)

                    ' Create signature configuration from PFX (or P12) file
                    Dim signature As BuiltIn.SignatureConfiguration = session.CreateSignatureFromCertificate(pfxStr, password)

                    ' Create appearance from either an XML or a JSON file
                    Using appStream = File.OpenRead(appConfigFile)
                        If Path.GetExtension(appConfigFile) = ".xml" Then
                            signature.Appearance = Appearance.CreateFromXml(appStream)
                        Else
                            signature.Appearance = Appearance.CreateFromJson(appStream)
                        End If
                    End Using

                    signature.Appearance.PageNumber = 1
                    signature.Appearance.CustomTextVariables.Add("company", "Daily Planet")

                    ' Open input document
                    Using inStr = File.OpenRead(inPath)
                        Using inDoc = Document.Open(inStr)

                            ' Create stream for output file
                            Using outStr = File.Create(outPath)

                                ' Sign the input document
                                Using outDoc = New Signer().Sign(inDoc, signature, outStr)
                                End Using
                            End Using
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
