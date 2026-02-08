''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsBuiltInAddTimestamp <timeStampUrl> <inputPath> <outputPath>
'                  
' Title:           Add a document time-stamp to a PDF
'                  
' Description:     Add a trusted document time-stamp to a PDF
'                  and confirm that the signed document has not been
'                  altered. This type of signature proves that
'                  the document existed at a specific time and ensures its
'                  integrity.
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

Namespace PdfToolsBuiltInAddTimestamp
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsBuiltInAddTimestamp <timeStampUrl> <inputPath> <outputPath>")
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

                ' Optional: Set your proxy configuration
                ' Sdk.Proxy = New Uri("http://myproxy:8080")

                ' Add a document time-stamp to a PDF
                AddTimestamp(New Uri(args(0)), args(1), args(2))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub AddTimestamp(timeStampUrl As Uri, inPath As String, outPath As String)
            ' Create a session to the built-in cryptographic provider
            Using session As New BuiltIn.Provider()
                session.TimestampUrl = timeStampUrl

                ' Create time-stamp configuration
                Dim timestamp = session.CreateTimestamp()

                ' Open input document
                Using inStr = File.OpenRead(inPath)
                    Using inDoc = Document.Open(inStr)

                        ' Create stream for output file
                        Using outStr = File.Create(outPath)

                            ' Add the document time-stamp
                            Using outDoc = New Signer().AddTimestamp(inDoc, timestamp, outStr)
                            End Using
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
