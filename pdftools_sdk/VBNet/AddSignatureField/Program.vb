''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' File:            Program.vb
'
' Usage:           PdfToolsAddSignatureField <inputPath> <outputPath>
'                  
' Title:           Add a signature field to a PDF
'                  
' Description:     Add an unsigned signature field that can be signed in
'                  another application.
'                  The signature field indicates that the document requires
'                  a signature and defines the page and position
'                  where the signature's visual appearance will be placed.
'                  This is especially useful for forms and contracts
'                  with designated signature spaces. The signature visual
'                  appearance is irrelevant to the signature validation
'                  process and only serves as a visual cue for the user.
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

Imports PdfTools
Imports PdfTools.Geometry.Units
Imports PdfTools.Pdf
Imports PdfTools.Sign
Imports System.IO

Namespace PdfToolsAddSignatureField
    Module Program
        Sub Usage()
            Console.WriteLine("Usage: PdfToolsAddSignatureField <inputPath> <outputPath>")
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

                ' Add a signature field to a PDF document
                AddSignatureField(args(0), args(1))
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Sub

        Sub AddSignatureField(inPath As String, outPath As String)
            ' Open input document
            Using inStr = File.OpenRead(inPath)
                Using inDoc = Document.Open(inStr)

                    ' Create empty field appearance that is 6cm by 3cm in size
                    Dim appearance = Sign.Appearance.CreateFieldBoundingBox(Size.cm(6, 3))

                    ' Add field to last page of document
                    appearance.PageNumber = inDoc.PageCount

                    ' Position field
                    appearance.Bottom = Length.cm(3)
                    appearance.Left = Length.cm(6.5)

                    ' Create a signature field configuration
                    Dim field = New SignatureFieldOptions(appearance)

                    ' Create stream for output file
                    Using outStr = File.Create(outPath)

                        ' Sign the input document
                        Using outDoc = New Signer().AddSignatureField(inDoc, field, outStr)
                        End Using
                    End Using
                End Using
            End Using
        End Sub
    End Module
End Namespace
