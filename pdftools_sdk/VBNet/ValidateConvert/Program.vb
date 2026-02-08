''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsValidateConvert <inputPath> <outputPath>
'                  
' Title:           Convert a PDF to PDF/A-2b if necessary
'                  
' Description:     Analyze the input PDF document. If it does not yet
'                  conform to PDF/A-2b, convert it to PDF/A-2b.
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
Imports PdfTools.PdfA.Conversion

Namespace PdfToolsValidateConvert
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsValidateConvert <inputPath> <outputPath>")
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

                ' Convert the document to PDF/A-2b
                ConvertIfNotConforming(args(0), args(1), New Conformance(2, Conformance.PdfALevel.B))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub ConvertIfNotConforming(inPath As String, outPath As String, conformance As Conformance)
            ' Open input document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)
                    ' Create the Validator object, and use the Conformance object to create
                    ' an AnalysisOptions object that controls the behavior of the Validator.
                    Dim validator = New Validator()
                    Dim analysisOptions = New AnalysisOptions() With {.conformance = conformance}

                    ' Run the analysis, and check the results.
                    ' Only proceed if document is not conforming.
                    Dim analysisResult = validator.Analyze(inDoc, analysisOptions)
                    If analysisResult.IsConforming Then
                        Console.WriteLine($"Document conforms to {inDoc.Conformance} already.")
                        Return
                    End If

                    ' Create a converter object
                    Dim converter = New Converter()

                    ' Add handler for conversion events
                    Dim eventsSeverity = EventSeverity.Information
                    AddHandler converter.ConversionEvent, Sub(s, e)
                                                              ' Get the event's suggested severity
                                                              Dim severity = e.Severity

                                                              ' Optionally the suggested severity can be changed according to
                                                              ' the requirements of your conversion process and, for example,
                                                              ' the event's category (e.Category).

                                                              If severity > eventsSeverity Then
                                                                  eventsSeverity = severity
                                                              End If

                                                              ' Report conversion event
                                                              Console.WriteLine("- {0} {1}: {2} ({3}{4})",
                                                                severity.ToString()(0), e.Category, e.Message, e.Context, If(e.PageNo > 0, " page " & e.PageNo, "")
                                                              )
                                                          End Sub

                    ' Create stream for output file
                    Using outStr = File.Create(outPath)
                        ' Convert the input document to PDF/A using the converter object
                        ' and its conversion event handler
                        Using outDoc = converter.Convert(analysisResult, inDoc, outStr)
                            ' Check if critical conversion events occurred
                            Select Case eventsSeverity
                                Case EventSeverity.Information
                                    Console.WriteLine($"Successfully converted document to {outDoc.Conformance}.")
                                Case EventSeverity.Warning
                                    Console.WriteLine($"Warnings occurred during the conversion of document to {outDoc.Conformance}.")
                                    Console.WriteLine($"Check the output file to decide if the result is acceptable.")
                                Case EventSeverity.Error
                                    Throw New Exception($"Unable to convert document to {conformance} because of critical conversion events.")
                            End Select
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
