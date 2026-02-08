''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsImg2PdfDefault <inputPath> <outputPath>
'                  
' Title:           Convert image to PDF
'                  
' Description:     Convert an image to a PDF. The default settings for this
'                  conversion profile place each image on a separate A4
'                  portrait page with a 2 cm margin.
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

Imports PdfTools.Image
Imports PdfTools.Image2Pdf
Imports System.IO
Imports Profiles = PdfTools.Image2Pdf.Profiles

Namespace PdfToolsImg2PdfDefault
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsImg2PdfDefault <inputPath> <outputPath>")
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

                Image2Pdf(args(0), args(1))

                Console.WriteLine("Execution successful.")
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Private Sub Image2Pdf(inPath As String, outPath As String)
            ' Open image document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)

                    ' Create the profile that defines the conversion parameters.
                    ' The Default profile converts images to PDF documents.
                    Dim profile = New Profiles.Default()

                    ' Optionally, the profile's parameters can be changed according to the 
                    ' requirements of your conversion process.

                    ' Create output stream
                    Using outStr = File.Create(outPath)

                        ' Convert the image to a PDF document
                        Using outDoc = New Converter().Convert(inDoc, outStr, profile)
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
