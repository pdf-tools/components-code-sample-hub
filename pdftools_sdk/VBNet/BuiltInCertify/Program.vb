''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsBuiltInCertify <certificateFile> <password> <inputPath> <outputPath>
'                  
' Title:           Certify a PDF
'                  
' Description:     This type of signature allows the PDF author to specify
'                  which types of modifications are permissible after
'                  signing.
'                  These signatures are also known as Modification Detection
'                  and Prevention (MDP) signatures.
'                  
'                  The signing certificate is read from a password-protected
'                  PKCS#12 file (.pfx or .p12).
'                  
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

Namespace PdfToolsBuiltInCertify
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsBuiltInCertify <certificateFile> <password> <inputPath> <outputPath>")
        End Sub

        Sub Main(args As String())
            ' Check command line parameters
            If args.Length < 4 OrElse args.Length > 4 Then
                Usage()
                Return
            End If

            Try
                ' By default, a test license key is active. In this case, a watermark is added to the output. 
                ' If you have a license key, please uncomment the following call and set the license key.
                ' PdfTools.Sdk.Initialize("LICENSE-KEY")

                ' Certify a PDF document
                Certify(args(0), args(1), args(2), args(3))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub Certify(certificateFile As String, password As String, inPath As String, outPath As String)
            ' Create a session to the built-in cryptographic provider
            Using session As New BuiltIn.Provider()

                ' Create signature configuration from PFX (or P12) file
                Using pfxStr = File.OpenRead(certificateFile)
                    Dim signature = session.CreateSignatureFromCertificate(pfxStr, password)

                    ' Embed validation information to enable the long term validation (LTV) of the signature (default)
                    signature.ValidationInformation = PdfTools.Crypto.ValidationInformation.EmbedInDocument

                    ' Open input document
                    Using inStr = File.OpenRead(inPath)
                        Using inDoc = Document.Open(inStr)

                            ' Create stream for output file
                            Using outStr = File.Create(outPath)

                                ' Add a document certification (MDP) signature
                                ' Optionally, the access permissions can be set.
                                Using outDoc = New Signer().Certify(inDoc, signature, outStr)
                                End Using
                            End Using
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
