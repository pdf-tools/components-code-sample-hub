''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsValidateSimple <inputPath>
'                  
' Title:           Validate PDF conformance
'                  
' Description:     Assess whether a PDF document adheres to specific
'                  standards and conformance levels.
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
Imports PdfTools.PdfA.Validation

Namespace PdfToolsValidateSimple
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsValidateSimple <inputPath>")
        End Sub

        Sub Main(args As String())
            ' Check command line parameters
            If args.Length < 1 OrElse args.Length > 1 Then
                Usage()
                Return
            End If

            Try
                ' By default, a test license key is active. In this case, a watermark is added to the output. 
                ' If you have a license key, please uncomment the following call and set the license key.
                ' PdfTools.Sdk.Initialize("LICENSE-KEY")

                Dim result = Validate(args(0))

                ' Report the validation result
                If result.IsConforming Then
                    Console.WriteLine($"Document conforms to {result.Conformance}.")
                Else
                    Console.WriteLine($"Document does not conform to {result.Conformance}.")
                End If
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Private Function Validate(inPath As String) As ValidationResult
            ' Open the document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)

                    ' Create a validator object that writes all validation error messages to the console
                    Dim validator = New Validator()
                    AddHandler validator.Error, Sub(s, e)
                                                    Console.WriteLine("- {0}: {1} ({2}{3})", e.Category, e.Message, e.Context, If(e.PageNo > 0, " on page" & e.PageNo, ""))
                                                End Sub

                    ' Validate the standard conformance of the document
                    Return validator.Validate(inDoc)
                End Using
            End Using
        End Function
    End Module
End Namespace
