''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsZugferd <inputPath> <invoicePath> <outputPath>
'                  
' Title:           Create a ZUGFeRD invoice
'                  
' Description:     Convert a PDF to PDF/A-3 and embed XML data to create a
'                  ZUGFeRD-compliant invoice.
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
            Console.WriteLine("Usage: PdfToolsZugferd <inputPath> <invoicePath> <outputPath>")
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

                AddZugferdInvoice(args(0), args(1), args(2))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub AddZugferdInvoice(inPath As String, invoicePath As String, outPath As String)
            ' Open input document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)

                    ' Create the Validator object, and use the Conformance object to create
                    ' an AnalysisOptions object that controls the behavior of the Validator.
                    Dim validator = New Validator()
                    ' The conformance has to be set to PDF/A-3 when adding the XML invoice file
                    Dim analysisOptions = New AnalysisOptions() With {.Conformance = New Conformance(3, Conformance.PdfALevel.U)}

                    ' Run the analysis
                    Dim analysisResult = validator.Analyze(inDoc, analysisOptions)

                    ' Create a converter object
                    Dim converter = New Converter()

                    ' Add invoice XML file
                    Using invoiceStr = File.OpenRead(invoicePath)
                        converter.AddInvoiceXml(InvoiceType.Zugferd, invoiceStr)

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
                                                                  Console.WriteLine("- {0} {1}: {2} ({3}{4})", severity.ToString()(0), e.Category, e.Message, e.Context, If(e.PageNo > 0, " page " & e.PageNo, ""))
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
                                        Throw New Exception($"Unable to convert document to PDF/A-3U because of critical conversion events.")
                                End Select
                            End Using
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
