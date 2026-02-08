''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsPdf2ImgSimple <inputPath> <outputPath>
'                  
' Title:           Convert PDF to image
'                  
' Description:     Convert a PDF to a rasterized image. In this example, the
'                  conversion profile outputs the PDF as a TIFF image
'                  suitable for archiving.
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

Imports System.IO
Imports PdfTools.Pdf
Imports PdfTools.Pdf2Image
Imports Profiles = PdfTools.Pdf2Image.Profiles

Namespace PdfToolsPdf2ImgSimple
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsPdf2ImgSimple <inputPath> <outputPath>")
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

                Pdf2Image(args(0), args(1))
                Console.WriteLine("Execution successful.")
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Private Sub Pdf2Image(inPath As String, outPath As String)
            ' Open input document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)

                    ' Create the profile that defines the conversion parameters.
                    ' The Archive profile converts PDF documents to TIFF images for archiving.
                    Dim profile = New Profiles.Archive()

                    ' Optionally the profile's parameters can be changed according to the 
                    ' requirements of your conversion process.

                    ' Create output stream
                    Using outStr = File.Create(outPath)

                        ' Convert the PDF document to an image document
                        Using outDoc = New Converter().ConvertDocument(inDoc, outStr, profile)
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
