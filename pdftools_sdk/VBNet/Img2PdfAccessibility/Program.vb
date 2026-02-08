''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsImg2PdfAccessibility <inputPath> <alternateText> <outputPath>
'                  
' Title:           Convert an image to an accessible PDF/A document
'                  
' Description:     Convert an image to an accessible PDF/A-2a document.
'                  Alternative text is added to the image, as required for
'                  PDF/A level A, to ensure accessibility for people with
'                  disabilities who use assistive technologies.
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
Imports Conformance = PdfTools.Pdf.Conformance
Imports Profiles = PdfTools.Image2Pdf.Profiles

Namespace PdfToolsImg2PdfAccessibility
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsImg2PdfAccessibility <inputPath> <alternateText> <outputPath>")
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

                Image2Pdf(args(0), args(1), args(2))

                Console.WriteLine("Execution successful.")
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Private Sub Image2Pdf(inPath As String, alternateText As String, outPath As String)
            ' Open image document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)

                    ' Create the profile that defines the conversion parameters.
                    ' The Archive profile converts images to PDF/A documents for archiving.
                    Dim profile = New Profiles.Archive()

                    ' Set conformance of output document to PDF/A-2a
                    profile.Conformance = New Conformance(2, Conformance.PdfALevel.A)

                    ' For PDF/A level A, an alternate text is required for each page of the image.
                    ' This is optional for other PDF/A levels, e.g. PDF/A-2b.
                    profile.Language = "en"
                    profile.AlternateText.Add(alternateText)

                    ' Optionally other profile parameters can be changed according to the 
                    ' requirements of your conversion process.

                    ' Create output stream
                    Using outStr = File.Create(outPath)

                        ' Convert the image to a tagged PDF/A document
                        Using outDoc = New Converter().Convert(inDoc, outStr, profile)
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
