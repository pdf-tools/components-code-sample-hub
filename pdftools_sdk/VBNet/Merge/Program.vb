''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsMerge <inputPath> [<inputPath2> ...] <outputPath>
'                  
' Title:           Merge PDFs
'                  
' Description:     Merge multiple PDF documents into a single file.
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

Namespace PdfToolsMerge
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsMerge <inputPath> [<inputPath2> ...] <outputPath>")
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

                Merge(args.Take(args.Length - 1), args.Last())
                Console.WriteLine("Execution successful.")
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Private Sub Merge(inPaths As IEnumerable(Of String), outPath As String)
            ' Create output stream
            Using outStream = File.Create(outPath)
                Using docAssembler = New PdfTools.DocumentAssembly.DocumentAssembler(outStream)

                    For Each inPath In inPaths
                        Using inStream = File.OpenRead(inPath)
                            Using inDoc = PdfTools.Pdf.Document.Open(inStream)
                                ' Append the content of the input documents to the output document
                                docAssembler.Append(inDoc)
                            End Using
                        End Using
                    Next

                    ' Merge input documents into an output document
                    docAssembler.Assemble()
                End Using
            End Using
        End Sub
    End Module
End Namespace
