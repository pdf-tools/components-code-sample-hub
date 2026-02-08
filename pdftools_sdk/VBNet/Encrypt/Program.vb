''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsEncrypt <password> <inputPath> <outputPath>
'                  
' Title:           Encrypt a PDF
'                  
' Description:     Encrypt a PDF with a user password.
'                  To open the document, the user password is required.
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
Imports System.IO
Imports Sign = PdfTools.Sign

Namespace PdfToolsEncrypt
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsEncrypt <password> <inputPath> <outputPath>")
        End Sub

        Sub Main(args As String())
            ' Check command line parameters
            If args.Length < 3 OrElse args.Length > 3 Then
                Usage()
                Return
            End If

            Try
                ' By default, a test license key is active. In this case, a watermark is added to the output. 
                ' If you have a license key, please uncomment the following call and set the license key.
                ' PdfTools.Sdk.Initialize("LICENSE-KEY")

                ' Encrypt a PDF document
                Encrypt(args(0), args(1), args(2))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub Encrypt(password As String, inPath As String, outPath As String)
            ' Open input document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)

                    ' Create stream for output file
                    Using outStr = File.Create(outPath)

                        ' Set encryption options
                        Dim outputOptions = New Sign.OutputOptions() With {
                            .Encryption = New Encryption(password, Nothing, Permission.All),
                            .RemoveSignatures = Sign.SignatureRemoval.Signed
                        }

                        ' Encrypt the document
                        Using outDoc = New Sign.Signer().Process(inDoc, outStr, outputOptions)
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
