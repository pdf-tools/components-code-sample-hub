''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsMultipleImg2Pdf <inputPath> [<inputPath2> ...] <outputPath>
'                  
' Title:           Convert multiple images to a PDF
'                  
' Description:     Convert a list of images into a single PDF. Supported
'                  image types are TIFF, JPEG, BMP, GIF, PNG, JBIG2, and
'                  JPEG2000.
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

Namespace PdfToolsMultipleImg2Pdf
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsMultipleImg2Pdf <inputPath> [<inputPath2> ...] <outputPath>")
        End Sub

        Sub Main(args As String())
            ' Check command line parameters
            If args.Length < 2 Then
                Usage()
                Return
            End If

            Try
                ' By default, a test license key is active. In this case, a watermark is added to the output. 
                ' If you have a license key, please uncomment the following call and set the license key.
                ' PdfTools.Sdk.Initialize("LICENSE-KEY")

                Images2Pdf(args.Take(args.Length - 1), args.Last())
                Console.WriteLine("Execution successful.")
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Private Sub Images2Pdf(inPaths As IEnumerable(Of String), outPath As String)
            Dim streams = New List(Of FileStream)()
            Dim images = New DocumentList()
            Try
                ' Open input images and store in list
                For Each inPath In inPaths
                    Dim stream = File.OpenRead(inPath)
                    streams.Add(stream)
                    images.Add(Document.Open(stream))
                Next

                ' Create the profile that defines the conversion parameters.
                Dim profile = New Profiles.Default()

                ' Optionally the profile's parameters can be changed according to the 
                ' requirements of your conversion process.
                ' Create output stream
                Using outStream = File.Create(outPath)
                    Using outPdf = New Converter().ConvertMultiple(images, outStream, profile)
                    End Using
                End Using
            Finally
                For Each item In images
                    item.Dispose()
                Next
                For Each stream In streams
                    stream.Dispose()
                Next
            End Try
        End Sub
    End Module
End Namespace
