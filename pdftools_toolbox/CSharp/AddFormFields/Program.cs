/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxAddFormFields <inputPath> <outputPath>
 *                  Example: Form2NoneNoTP.pdf out.pdf
 *                  
 * Title:           Add form field
 *                  
 * Description:     Add form fields to a PDF.
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
using System.Collections.Generic;
using System.IO;
using System.Linq;

using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Real;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using PdfTools.Toolbox.Pdf.Forms;
using PdfTools.Toolbox.Pdf.Navigation;

namespace ToolboxAddFormFields
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxAddFormFields <inputPath> <outputPath>");
            Console.WriteLine("       Example: Form2NoneNoTP.pdf out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2 || args.Length > 2)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                // Get all the command line arguments
                string inPath = args[0];
                string outPath = args[1];

                using (Stream inStream = new FileStream(inPath, FileMode.Open, FileAccess.Read))
                using (Document inDoc = Document.Open(inStream, null))

                // Create output document
                using (Stream outStream = new FileStream(outPath, FileMode.Create, FileAccess.ReadWrite))
                using (Document outDoc = Document.Create(outStream, inDoc.Conformance, null))
                {
                    // Copy document-wide data
                    CopyDocumentData(inDoc, outDoc);

                    // Copy all form fields
                    FieldNodeMap inFormFields = inDoc.FormFields;
                    FieldNodeMap outFormFields = outDoc.FormFields;
                    foreach (KeyValuePair<string, FieldNode> inPair in inFormFields)
                    {
                        FieldNode outFormFieldNode = FieldNode.Copy(outDoc, inPair.Value);
                        outFormFields.Add(inPair.Key, outFormFieldNode);
                    }

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions
                    {
                        FormFields = FormFieldCopyStrategy.CopyAndUpdateWidgets,
                        UnsignedSignatures = CopyStrategy.Remove,
                    };

                    // Copy first page
                    Page inPage = inDoc.Pages[0];
                    Page outPage = Page.Copy(outDoc, inPage, copyOptions);

                    // Add different types of form fields to the output page
                    AddCheckBox(outDoc, "Check Box ID", true, outPage, new Rectangle { Left = 50, Bottom = 300, Right = 70, Top = 320 });
                    AddComboBox(outDoc, "Combo Box ID", new string[] { "item 1", "item 2" }, "item 1", outPage, new Rectangle { Left = 50, Bottom = 260, Right = 210, Top = 280 });
                    AddListBox(outDoc, "List Box ID", new string[] { "item 1", "item 2", "item 3" }, new string[] { "item 1", "item 3" }, outPage, new Rectangle { Left = 50, Bottom = 160, Right = 210, Top = 240 });
                    AddRadioButtonGroup(outDoc, "Radio Button ID", new string[] { "A", "B", "C" }, 0, outPage, new Rectangle { Left = 50, Bottom = 120, Right = 210, Top = 140 });
                    AddGeneralTextField(outDoc, "Text ID", "Text", outPage, new Rectangle { Left = 50, Bottom = 80, Right = 210, Top = 100 });

                    // Add page to output document
                    outDoc.Pages.Add(outPage);

                    // Copy remaining pages and append to output document
                    PageList inPageRange = inDoc.Pages.GetRange(1, inDoc.Pages.Count - 1);
                    PageList copiedPages = PageList.Copy(outDoc, inPageRange, copyOptions);
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

        private static void AddCheckBox(Document doc, string id, bool isChecked, Page page, Rectangle rectangle)
        {
            // Create a check box
            CheckBox checkBox = CheckBox.Create(doc);

            // Add the check box to the document
            doc.FormFields.Add(id, checkBox);

            // Set the check box's state
            checkBox.Checked = isChecked;

            // Create a widget and add it to the page's widgets
            page.Widgets.Add(checkBox.AddNewWidget(rectangle));
        }

        private static void AddComboBox(Document doc, string id, string[] itemNames, string value, Page page, Rectangle rectangle)
        {
            // Create a combo box
            ComboBox comboBox = ComboBox.Create(doc);

            // Add the combo box to the document
            doc.FormFields.Add(id, comboBox);

            // Loop over all given item names
            foreach (string itemName in itemNames)
            {
                // Create a new choice item
                ChoiceItem item = comboBox.AddNewItem(itemName);

                // Check whether this is the chosen item name
                if (value.Equals(itemName))
                    comboBox.ChosenItem = item;
            }
            if (comboBox.ChosenItem == null && !string.IsNullOrEmpty(value))
            {
                // If no item has been chosen then assume we want to set the editable item
                comboBox.CanEdit = true;
                comboBox.EditableItemName = value;
            }

            // Create a widget and add it to the page's widgets
            page.Widgets.Add(comboBox.AddNewWidget(rectangle));
        }

        private static void AddListBox(Document doc, string id, string[] itemNames, string[] chosenNames, Page page, Rectangle rectangle)
        {
            // Create a list box
            ListBox listBox = ListBox.Create(doc);

            // Add the list box to the document
            doc.FormFields.Add(id, listBox);

            // Allow multiple selections
            listBox.AllowMultiSelect = true;
            ChoiceItemList chosenItems = listBox.ChosenItems;

            // Loop over all given item names
            foreach (string itemName in itemNames)
            {
                // Create a new choice item
                ChoiceItem item = listBox.AddNewItem(itemName);

                // Check whether to add to the chosen items
                if (chosenNames.Contains(itemName))
                    chosenItems.Add(item);
            }

            // Create a widget and add it to the page's widgets
            page.Widgets.Add(listBox.AddNewWidget(rectangle));
        }

        private static void AddRadioButtonGroup(Document doc, string id, string[] buttonNames, int chosen, Page page, Rectangle rectangle)
        {
            // Create a radio button group
            RadioButtonGroup group = RadioButtonGroup.Create(doc);

            // Get the page's widgets
            WidgetList widgets = page.Widgets;

            // Add the radio button group to the document
            doc.FormFields.Add(id, group);

            // We partition the given rectangle horizontally into sub-rectangles, one for each button
            // Compute the width of the sub-rectangles
            double buttonWidth = (rectangle.Right - rectangle.Left) / buttonNames.Length;

            // Loop over all button names
            for (int i = 0; i < buttonNames.Length; i++)
            {
                // Compute the sub-rectangle for this button
                Rectangle buttonRectangle = new Rectangle()
                {
                    Left = rectangle.Left + i * buttonWidth,
                    Bottom = rectangle.Bottom,
                    Right = rectangle.Left + (i + 1) * buttonWidth,
                    Top = rectangle.Top
                };

                // Create the button and an associated widget
                RadioButton button = group.AddNewButton(buttonNames[i]);
                Widget widget = button.AddNewWidget(buttonRectangle);

                // Check if this is the chosen button
                if (i == chosen)
                    group.ChosenButton = button;

                // Add the widget to the page's widgets
                widgets.Add(widget);
            }
        }

        private static void AddGeneralTextField(Document doc, string id, string value, Page page, Rectangle rectangle)
        {
            // Create a general text field
            GeneralTextField field = GeneralTextField.Create(doc);

            // Add the field to the document
            doc.FormFields.Add(id, field);

            // Set the text value
            field.Text = value;

            // Create a widget and add it to the page's widgets
            page.Widgets.Add(field.AddNewWidget(rectangle));
        }
    }
}