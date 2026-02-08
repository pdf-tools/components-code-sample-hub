''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsSwisscomSigSrvSign <identity> <commonName> <inputPath> <outputPath>
'                  
' Title:           Sign a PDF using the Swisscom Signing Service
'                  
' Description:     Add a document signature, also called an approval
'                  signature. This signature verifies the integrity of the
'                  signed part of the document and confirms the certificate
'                  used for singing.
'                  
'                  Validation information is embedded to enable the
'                  long-term validation (LTV) of the signature.
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
Imports SwisscomSigSrv = PdfTools.Crypto.Providers.SwisscomSigSrv

Namespace PdfToolsSwisscomSigSrvSign
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsSwisscomSigSrvSign <identity> <commonName> <inputPath> <outputPath>")
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

                ' Optional: Set your proxy configuration
                ' Sdk.Proxy = New Uri("http://myproxy:8080")

                Dim identity As String = args(0)
                Dim commonName As String = args(1)
                Dim inPath As String = args(2)
                Dim outPath As String = args(3)

                ' Configure the SSL client certificate to connect to the service
                Dim httpClientHandler = New HttpClientHandler()
                Using sslClientCert = File.OpenRead("C:\path\to\clientcert.p12")
                    httpClientHandler.SetClientCertificate(sslClientCert, "***insert password***")
                End Using

                ' Connect to the Swisscom Signing Service
                Using session = New SwisscomSigSrv.Session(New Uri("https://ais.swisscom.com"), httpClientHandler)

                    ' Sign a PDF document
                    Sign(session, identity, commonName, inPath, outPath)
                End Using
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub Sign(session As SwisscomSigSrv.Session, identity As String, commonName As String, inPath As String, outPath As String)
            ' Create a signing certificate for a static identity
            Dim signature = session.CreateSignatureForStaticIdentity(identity, commonName)

            ' Embed validation information to enable the long term validation (LTV) of the signature (default)
            signature.EmbedValidationInformation = True

            ' Open input document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)

                    ' Create stream for output file
                    Using outStr = File.Create(outPath)

                        ' Sign the document
                        Using outDoc = New Signer().Sign(inDoc, signature, outStr)
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
