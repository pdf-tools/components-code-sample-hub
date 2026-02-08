''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsPkcs11Sign <pkcs11Library> <password> <certificate> <inputPath> <outputPath>
'                  
' Title:           Sign a PDF using a PKCS#11 device
'                  
' Description:     Add a document signature, sometimes called an approval
'                  signature.
'                  This type of signature verifies the integrity of the
'                  signed part of the document and authenticates the
'                  signer's identity.
'                  
'                  Validation information is embedded to enable the
'                  long-term validation (LTV) of the signature.
'                  
'                  The signing certificate is stored on a cryptographic
'                  device with PKCS#11 middleware (driver).
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
Imports Pkcs11 = PdfTools.Crypto.Providers.Pkcs11

Namespace PdfToolsPkcs11Sign
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsPkcs11Sign <pkcs11Library> <password> <certificate> <inputPath> <outputPath>")
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

                Dim pkcs11Library As String = args(0)
                Dim password As String = args(1)
                Dim certificate As String = args(2)
                Dim inPath As String = args(3)
                Dim outPath As String = args(4)

                ' Load the PKCS#11 driver module (middleware)
                ' The module can only be loaded once in the application.
                Using [module] = Pkcs11.Module.Load(pkcs11Library)

                    ' Create a session to the cryptographic device and log in
                    ' with the password (pin)
                    Using session = [module].Devices.GetSingle().CreateSession(password)

                        ' Sign a PDF document
                        Sign(session, certificate, inPath, outPath)
                    End Using
                End Using
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub Sign(session As Pkcs11.Session, certificate As String, inPath As String, outPath As String)
            ' Create the signature configuration
            ' This can be re-used to sign multiple documents
            Dim signature = session.CreateSignatureFromName(certificate)

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
        End Sub
    End Module
End Namespace
