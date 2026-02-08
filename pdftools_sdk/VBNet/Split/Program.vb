''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsSplit <inputPath> <outputPath>
'                  
' Title:           Split a PDF
'                  
' Description:     Divide a PDF document into multiple PDF files.
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

Namespace PdfToolsSplit
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsSplit <inputPath> <outputPath>")
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

                Split(args(0), args(1))
                Console.WriteLine("Execution successful.")
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Private Sub Split(inPath As String, outPathPrefix As String)
            ' Open input document
            Using inStream = File.OpenRead(inPath)
                Using inDoc = PdfTools.Pdf.Document.Open(inStream)

                    ' Split the input document page by page
                    For i As Integer = 1 To inDoc.PageCount
                        Using outStream = File.Create(outPathPrefix & "_page_" & i & ".pdf")
                            Using docAssembler = New PdfTools.DocumentAssembly.DocumentAssembler(outStream)
                                docAssembler.Append(inDoc, i, i)
                                docAssembler.Assemble()
                            End Using
                        End Using
                    Next
                End Using
            End Using
        End Sub
    End Module
End Namespace
