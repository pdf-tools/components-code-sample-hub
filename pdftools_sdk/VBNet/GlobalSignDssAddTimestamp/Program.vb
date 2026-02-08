''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsGlobalSignDssAddTimestamp <inputPath> <outputPath>
'                  
' Title:           Add a document time-stamp to a PDF using the GlobalSign
'                  Digital Signing Service
'                  
' Description:     Add a trusted document time-stamp to a PDF and confirm
'                  that the signed document has not been altered. This type
'                  of signature proves that the document existed at a
'                  specific time and ensures its integrity.
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
Imports PdfTools.Pdf
Imports PdfTools.Sign
Imports System.IO
Imports GlobalSignDss = PdfTools.Crypto.Providers.GlobalSignDss

Namespace PdfToolsGlobalSignDssAddTimestamp
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsGlobalSignDssAddTimestamp <inputPath> <outputPath>")
        End Sub

        Sub Main(args As String())
            ' Check command line parameters
            If args.Length < 2 OrElse args.Length > 2 Then
                Usage()
                Return
            End If

            Try
                ' By default, a test license key is active. In this case, a watermark is added to the output. 
                ' If you have a license key, please uncomment the following call and set the license key.
                ' PdfTools.Sdk.Initialize("LICENSE-KEY")

                ' Optional: Set your proxy configuration
                ' Sdk.Proxy = new Uri("http://myproxy:8080")

                Dim inPath As String = args(0)
                Dim outPath As String = args(1)

                ' Configure the SSL client certificate to connect to the service
                Dim httpClientHandler = New HttpClientHandler()
                Using sslClientCert = File.OpenRead("C:\path\to\clientcert.cer")
                    Using sslClientKey = File.OpenRead("C:\path\to\privateKey.key")
                        httpClientHandler.SetClientCertificateAndKey(sslClientCert, sslClientKey, "***insert password***")
                    End Using
                End Using

                ' Connect to the GlobalSign Digital Signing Service
                Using session = New GlobalSignDss.Session(New Uri("https://emea.api.dss.globalsign.com:8443"), "***insert api_key***", "***insert api_secret***", httpClientHandler)

                    ' Add a document time-stamp to a PDF
                    AddTimestamp(session, inPath, outPath)
                End Using
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub AddTimestamp(session As GlobalSignDss.Session, inPath As String, outPath As String)
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
        End Sub
    End Module
End Namespace
