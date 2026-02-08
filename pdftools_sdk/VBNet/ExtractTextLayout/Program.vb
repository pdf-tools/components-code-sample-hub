''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsExtractTextLayout <inputPath> <outputDir>
'                  
' Title:           Extract text mimicking layout
'                  
' Description:     Extracting text from a PDF page by page into text files,
'                  preserving the original layout by adding whitespaces to
'                  the monospace text.
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

Imports System
Imports System.IO
Imports PdfTools.Pdf
Imports PdfTools.Extraction
Imports PdfTools.Geometry.Units

Namespace PdfToolsExtractTextLayout
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsExtractTextLayout <inputPath> <outputDir>")
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

                ExtractText(args(0), args(1))
                Console.WriteLine("Execution successful.")
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub ExtractText(inPath As String, outDir As String)
            ' Open input document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)
                    ' Create directory if not exists
                    If Not Directory.Exists(outDir) Then
                        Directory.CreateDirectory(outDir)
                    End If

                    Dim options As New TextOptions()
                    options.ExtractionFormat = TextExtractionFormat.Monospace
                    options.AdvanceWidth = Length.Parse("9.2pt")

                    ' Extract text page per page from the document
                    Dim extractor As New Extractor()
                    For i As Integer = 0 To inDoc.PageCount - 1
                        Using outStr = File.Create(Path.Combine(outDir, $"page{i + 1}.txt"))
                            extractor.ExtractText(inDoc, outStr, options, i + 1, i + 1)
                        End Using
                    Next
                End Using
            End Using
        End Sub
    End Module
End Namespace
