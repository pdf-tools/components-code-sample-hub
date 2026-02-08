/****************************************************************************
 *
 * File:            toolboxaddformfields.java
 *
 * Usage:           java toolboxaddformfields <inputPath> <outputPath>
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

package ToolboxAddFormFields;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.Map.Entry;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.geometry.real.Rectangle;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.forms.CheckBox;
import com.pdftools.toolbox.pdf.forms.ChoiceItem;
import com.pdftools.toolbox.pdf.forms.ChoiceItemList;
import com.pdftools.toolbox.pdf.forms.ComboBox;
import com.pdftools.toolbox.pdf.CopyStrategy;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.forms.FieldNode;
import com.pdftools.toolbox.pdf.forms.FieldNodeMap;
import com.pdftools.toolbox.pdf.forms.FormFieldCopyStrategy;
import com.pdftools.toolbox.pdf.forms.GeneralTextField;
import com.pdftools.toolbox.pdf.forms.ListBox;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.forms.RadioButton;
import com.pdftools.toolbox.pdf.forms.RadioButtonGroup;
import com.pdftools.toolbox.pdf.forms.Widget;
import com.pdftools.toolbox.pdf.forms.WidgetList;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxAddFormFields {
    static void usage() {
        System.out.println("Usage: java toolboxaddformfields <inputPath> <outputPath>");
        System.out.println("       Example: Form2NoneNoTP.pdf out.pdf");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            // Get the command line arguments
            String inPath = args[0];
            String outPath = args[1];

            try (// Open input document
                FileStream inStream = new FileStream(inPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, null);
                FileStream outStream = new FileStream(outPath, FileStream.Mode.READ_WRITE_NEW)) {
                try (// Create output document
                    Document outDoc = Document.create(outStream, inDoc.getConformance(), null)) {

                    // Copy document-wide data
                    copyDocumentData(inDoc, outDoc);

                    // Copy all form fields
                    FieldNodeMap inFormFields = inDoc.getFormFields();
                    FieldNodeMap outFormFields = outDoc.getFormFields();
                    for (Entry<String, FieldNode> entry : inFormFields.entrySet())
                        outFormFields.put(entry.getKey(), FieldNode.copy(outDoc, entry.getValue()));

                    // Define page copy options
                    PageCopyOptions copyOptions = new PageCopyOptions();
                    copyOptions.setFormFields(FormFieldCopyStrategy.COPY_AND_UPDATE_WIDGETS);
                    copyOptions.setUnsignedSignatures(CopyStrategy.REMOVE);

                    // Copy first page
                    Page inPage = inDoc.getPages().get(0);
                    Page outPage = Page.copy(outDoc, inPage, copyOptions);

                    // Add different types of form fields to the output page
                    addCheckBox(outDoc, "Check Box ID", true, outPage, new Rectangle(50, 300, 70, 320));
                    addComboBox(outDoc, "Combo Box ID", new String[] { "item 1", "item 2" }, "item 1", outPage,
                            new Rectangle(50, 260, 210, 280));
                    addListBox(outDoc, "List Box ID", new String[] { "item 1", "item 2", "item 3" },
                            new String[] { "item 1", "item 3" }, outPage, new Rectangle(50, 160, 210, 240));
                    addRadioButtonGroup(outDoc, "Radio Button ID", new String[] { "A", "B", "C" }, 0, outPage,
                            new Rectangle(50, 120, 210, 140));
                    addGeneralTextField(outDoc, "Text ID", "Text", outPage, new Rectangle(50, 80, 210, 100));

                    // Add page to output document
                    outDoc.getPages().add(outPage);

                    // Copy remaining pages and append to output document
                    PageList inPageRange = inDoc.getPages().subList(1, inDoc.getPages().size());
                    PageList copiedPages = PageList.copy(outDoc, inPageRange, copyOptions);
                    outDoc.getPages().addAll(copiedPages);
                }
            }

            System.out.println("Execution successful");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    private static void copyDocumentData(Document inDoc, Document outDoc) throws ToolboxException, IOException {
        // Copy document-wide data

        // Output intent
        if (inDoc.getOutputIntent() != null)
            outDoc.setOutputIntent(IccBasedColorSpace.copy(outDoc, inDoc.getOutputIntent()));

        // Metadata
        outDoc.setMetadata(Metadata.copy(outDoc, inDoc.getMetadata()));

        // Viewer settings
        outDoc.setViewerSettings(ViewerSettings.copy(outDoc, inDoc.getViewerSettings()));

        // Associated files (for PDF/A-3 and PDF 2.0 only)
        FileReferenceList outAssociatedFiles = outDoc.getAssociatedFiles();
        for (FileReference inFileRef : inDoc.getAssociatedFiles())
            outAssociatedFiles.add(FileReference.copy(outDoc, inFileRef));

        // Plain embedded files
        FileReferenceList outEmbeddedFiles = outDoc.getPlainEmbeddedFiles();
        for (FileReference inFileRef : inDoc.getPlainEmbeddedFiles())
            outEmbeddedFiles.add(FileReference.copy(outDoc, inFileRef));
    }

    private static void addCheckBox(Document doc, String id, boolean isChecked, Page page, Rectangle rectangle)
            throws ToolboxException {
        // Create a check box
        CheckBox checkBox = CheckBox.create(doc);

        // Add the check box to the document
        doc.getFormFields().put(id, checkBox);

        // Set the check box's state
        checkBox.setChecked(isChecked);

        // Create a widget and add it to the page's widgets
        page.getWidgets().add(checkBox.addNewWidget(rectangle));
    }


    private static void addListBox(Document doc, String id, String[] itemNames, String[] chosenNames, Page page,
            Rectangle rectangle) throws ToolboxException {
        List<String> chosenNamesList = Arrays.asList(chosenNames);

        // Create a list box
        ListBox listBox = ListBox.create(doc);

        // Add the list box to the document
        doc.getFormFields().put(id, listBox);

        // Allow multiple selections
        listBox.setAllowMultiSelect(true);

        // Get the list of chosen items
        ChoiceItemList chosenItems = listBox.getChosenItems();

        // Loop over all given item names
        for (String itemName : itemNames) {
            ChoiceItem item = listBox.addNewItem(itemName);
            // Check whether to add to the chosen items
            if (chosenNamesList.contains(itemName))
                chosenItems.add(item);
        }

        // Create a widget and add it to the page's widgets
        page.getWidgets().add(listBox.addNewWidget(rectangle));
    }


    private static void addComboBox(Document doc, String id, String[] itemNames, String value, Page page,
            Rectangle rectangle) throws ToolboxException {
        // Create a combo box
        ComboBox comboBox = ComboBox.create(doc);

        // Add the combo box to the document
        doc.getFormFields().put(id, comboBox);

        // Loop over all given item names
        for (String itemName : itemNames) {
            ChoiceItem item = comboBox.addNewItem(itemName);
            // Check whether to add to the chosen items
            if (value.equals(itemName))
                comboBox.setChosenItem(item);
        }
        if (comboBox.getChosenItem() == null && !(value == null || value.isEmpty())) {
            // If no item has been chosen then assume we want to set the editable item
            comboBox.setCanEdit(true);
            comboBox.setEditableItemName(value);
        }

        // Create a widget and add it to the page's widgets
        page.getWidgets().add(comboBox.addNewWidget(rectangle));
    }


    private static void addRadioButtonGroup(Document doc, String id, String[] buttonNames, int chosen, Page page,
            Rectangle rectangle) throws ToolboxException {
        // Create a radio button group
        RadioButtonGroup group = RadioButtonGroup.create(doc);

        // Add the radio button group to the document
        doc.getFormFields().put(id, group);

        // We partition the given rectangle horizontally into sub-rectangles, one for
        // each button
        // Compute the width of the sub-rectangles
        double buttonWidth = (rectangle.right - rectangle.left) / buttonNames.length;

        // Get the page's widgets
        WidgetList widgets = page.getWidgets();

        // Loop over all button names
        for (int i = 0; i < buttonNames.length; i++) {
            // Compute the sub-rectangle for this button
            Rectangle buttonRectangle = new Rectangle(rectangle.left + i * buttonWidth, rectangle.bottom,
                    rectangle.left + (i + 1) * buttonWidth, rectangle.top);

            // Create the button and an associated widget
            RadioButton button = group.addNewButton(buttonNames[i]);
            Widget widget = button.addNewWidget(buttonRectangle);

            // Check if this is the chosen button
            if (i == chosen)
                group.setChosenButton(button);

            // Add the widget to the page's widgets
            widgets.add(widget);
        }
    }


    private static void addGeneralTextField(Document doc, String id, String value, Page page, Rectangle rectangle)
            throws ToolboxException {
        // Create a general text field
        GeneralTextField field = GeneralTextField.create(doc);

        // Add the field to the document
        doc.getFormFields().put(id, field);

        // Set the check box's state
        field.setText(value);

        // Create a widget and add it to the page's widgets
        page.getWidgets().add(field.addNewWidget(rectangle));
    }
}