/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxFillFormFields <fieldID> <value> <inputPath> <outputPath>
 *                  Example: TextField1 \"New Text\" Form2None.pdf out.pdf
 *                  
 * Title:           Fill form fields
 *                  
 * Description:     Change values of AcroForm form fields.
 *                  
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2026 PDF Tools AG, Switzerland
 *                  Permission to use, copy, modify, and distribute this
 *                  software and its documentation for any purpose and without
 *                  fee is hereby granted, provided that the above copyright
 *                  notice appear in all copies and that both that copyright
 *                  notice and this permission notice appear in supporting
 *                  documentation. This software is provided "as is" without
 *                  express or implied warranty.
 *
 ***************************************************************************/

using System;
using System.IO;
using PdfTools.Toolbox;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Forms;
using PdfTools.Toolbox.Pdf.Navigation;


namespace ToolboxFillFormFields
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxFillFormFields <fieldID> <value> <inputPath> <outputPath>");
            Console.WriteLine("       Example: TextField1 \"New Text\" Form2None.pdf out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 4 || args.Length > 4)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                string fieldIdentifier = args[0];
                string fieldValue = args[1];
                string inPath = args[2];
                string outPath = args[3];

                // Open input document
                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    FieldNodeMap outFields = outDoc.FormFields;

                    // Copy all form fields
                    FieldNodeMap inFields = inDoc.FormFields;
                    foreach (var inPair in inFields)
                    {
                        FieldNode inFieldNode = inPair.Value;
                        FieldNode outFormFieldNode = FieldNode.Copy(outDoc, inFieldNode);
                        outFields.Add(inPair.Key, outFormFieldNode);
                    }

                    // Find the given field, exception thrown if not found
                    var selectedNode = outFields.Lookup(fieldIdentifier);
                    if (selectedNode is Field selectedField)
                        FillFormField(selectedField, fieldValue);

                    // Configure copying options for updating existing widgets and removing signature fields
                    PageCopyOptions copyOptions = new PageCopyOptions
                    {
                        FormFields = FormFieldCopyStrategy.CopyAndUpdateWidgets,
                        UnsignedSignatures = CopyStrategy.Remove,
                    };

                    // Copy all pages and append to output document
                    PageList copiedPages = PageList.Copy(outDoc, inDoc.Pages, copyOptions);
                    outDoc.Pages.AddRange(copiedPages);
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private static void CopyDocumentData(Document inDoc, Document outDoc)
        {
            // Copy document-wide data

            // Output intent
            if (inDoc.OutputIntent != null)
                outDoc.OutputIntent = IccBasedColorSpace.Copy(outDoc, inDoc.OutputIntent);

            // Metadata
            outDoc.Metadata = Metadata.Copy(outDoc, inDoc.Metadata);

            // Viewer settings
            outDoc.ViewerSettings = ViewerSettings.Copy(outDoc, inDoc.ViewerSettings);

            // Associated files (for PDF/A-3 and PDF 2.0 only)
            FileReferenceList outAssociatedFiles = outDoc.AssociatedFiles;
            foreach (FileReference inFileRef in inDoc.AssociatedFiles)
                outAssociatedFiles.Add(FileReference.Copy(outDoc, inFileRef));

            // Plain embedded files
            FileReferenceList outEmbeddedFiles = outDoc.PlainEmbeddedFiles;
            foreach (FileReference inFileRef in inDoc.PlainEmbeddedFiles)
                outEmbeddedFiles.Add(FileReference.Copy(outDoc, inFileRef));
        }

        static void FillFormField(Field formField, string value)
        {
            // Apply the value, depending on the field type
            if (formField is TextField textField)
            {
                // Set the text
                textField.Text = value;
            }
            else if (formField is CheckBox checkBox)
            {
                // Check or un-check
                checkBox.Checked = "on".Equals(value, StringComparison.CurrentCultureIgnoreCase);
            }
            else if (formField is RadioButtonGroup group)
            {
                // Search the buttons for given name
                foreach (var button in group.Buttons)
                {
                    if (value.Equals(button.ExportName))
                    {
                        // Found: Select this button
                        group.ChosenButton = button;
                        break;
                    }
                }
            }
            else if (formField is ComboBox comboBox)
            {
                // Search for the given item
                foreach (var item in comboBox.Items)
                {
                    if (value.Equals(item.DisplayName))
                    {
                        // Found: Select this item.
                        comboBox.ChosenItem = item;
                        break;
                    }
                }
            }
            else if (formField is ListBox listBox)
            {
                // Search for the given item
                foreach (var item in listBox.Items)
                {
                    if (value.Equals(item.DisplayName))
                    {
                        // Found: Set this item as the only selected item
                        var itemList = listBox.ChosenItems;
                        itemList.Clear();
                        itemList.Add(item);
                        break;
                    }
                }
            }
        }
    }
}