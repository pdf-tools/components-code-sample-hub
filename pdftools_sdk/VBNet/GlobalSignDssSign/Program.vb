''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsGlobalSignDssSign <commonName> <inputPath> <outputPath>
'                  
' Title:           Sign a PDF using the GlobalSign Digital Signing Service
'                  
' Description:     Add a document signature, sometimes called an approval
'                  signature.
'                  This type of signature verifies that the signed document
'                  has not been altered and authenticates the signer's
'                  identity.
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
Imports System
Imports System.IO
Imports System.Text.Json
Imports GlobalSignDss = PdfTools.Crypto.Providers.GlobalSignDss

Namespace PdfToolsGlobalSignDssSign
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsGlobalSignDssSign <commonName> <inputPath> <outputPath>")
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
                ' Sdk.Proxy = new Uri("http://myproxy:8080")

                Dim commonName As String = args(0)
                Dim inPath As String = args(1)
                Dim outPath As String = args(2)

                ' Configure the SSL client certificate to connect to the service
                Dim httpClientHandler = New HttpClientHandler()
                Using sslClientCert = File.OpenRead("C:\path\to\clientcert.cer")
                    Using sslClientKey = File.OpenRead("C:\path\to\privateKey.key")
                        httpClientHandler.SetClientCertificateAndKey(sslClientCert, sslClientKey, "***insert password***")
                    End Using
                End Using

                ' Connect to the GlobalSign Digital Signing Service
                Using session = New GlobalSignDss.Session(New Uri("https://emea.api.dss.globalsign.com:8443"), "***insert api_key***", "***insert api_secret***", httpClientHandler)

                    ' Sign a PDF document
                    Sign(session, commonName, inPath, outPath)
                End Using
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub Sign(session As GlobalSignDss.Session, commonName As String, inPath As String, outPath As String)
            ' Create a signing certificate for an account with a dynamic identity
            Dim identity = JsonSerializer.Serialize(New With {.subject_dn = New With {.common_name = commonName}})
            Dim signature = session.CreateSignatureForDynamicIdentity(identity)

            ' Embed validation information to enable the long term validation (LTV) of the signature (default)
            signature.ValidationInformation = PdfTools.Crypto.ValidationInformation.EmbedInDocument

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
