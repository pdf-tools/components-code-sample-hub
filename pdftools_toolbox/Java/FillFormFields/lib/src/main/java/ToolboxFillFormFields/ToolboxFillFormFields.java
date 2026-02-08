/****************************************************************************
 *
 * File:            toolboxfillformfields.java
 *
 * Usage:           java toolboxfillformfields <fieldID> <value> <inputPath> <outputPath>
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

package ToolboxFillFormFields;

import java.util.stream.Collectors;

import java.io.File;
import java.io.IOException;
import java.util.Map.Entry;

import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.pdf.forms.CheckBox;
import com.pdftools.toolbox.pdf.forms.ChoiceItem;
import com.pdftools.toolbox.pdf.forms.ChoiceItemList;
import com.pdftools.toolbox.pdf.forms.ComboBox;
import com.pdftools.toolbox.pdf.CopyStrategy;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.FileReference;
import com.pdftools.toolbox.pdf.FileReferenceList;
import com.pdftools.toolbox.pdf.Metadata;
import com.pdftools.toolbox.pdf.forms.Field;
import com.pdftools.toolbox.pdf.forms.FieldNode;
import com.pdftools.toolbox.pdf.forms.FieldNodeMap;
import com.pdftools.toolbox.pdf.forms.FormFieldCopyStrategy;
import com.pdftools.toolbox.pdf.forms.ListBox;
import com.pdftools.toolbox.pdf.PageCopyOptions;
import com.pdftools.toolbox.pdf.PageList;
import com.pdftools.toolbox.pdf.content.IccBasedColorSpace;
import com.pdftools.toolbox.pdf.forms.RadioButton;
import com.pdftools.toolbox.pdf.forms.RadioButtonGroup;
import com.pdftools.toolbox.pdf.forms.TextField;
import com.pdftools.toolbox.pdf.navigation.ViewerSettings;

public class ToolboxFillFormFields {
    static void usage() {
        System.out.println("Usage: java toolboxfillformfields <fieldID> <value> <inputPath> <outputPath>");
        System.out.println("       Example: TextField1 \"New Text\" Form2None.pdf out.pdf");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 4 || args.length > 4) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String fieldIdentifier = args[0];
            String fieldValue = args[1];
            String inPath = args[2];
            String outPath = args[3];

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

                    // Find the given field, exception thrown if not found
                    Field selectedField = (Field) outFormFields.lookup(fieldIdentifier);
                    fillFormField(selectedField, fieldValue);

                    // Configure copying options for updating existing widgets and removing signature fields
                    PageCopyOptions copyOptions = new PageCopyOptions();
                    copyOptions.setFormFields(FormFieldCopyStrategy.COPY_AND_UPDATE_WIDGETS);
                    copyOptions.setUnsignedSignatures(CopyStrategy.REMOVE);

                    // Copy all pages and append to output document
                    PageList copiedPages = PageList.copy(outDoc, inDoc.getPages(), copyOptions);
                    outDoc.getPages().addAll(copiedPages);
                }
            }

            System.out.println("Execution successful.");
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

    private static void fillFormField(Field formField, String value) throws ToolboxException {
        // Apply the value, depending on the field type
        if (formField instanceof TextField) {
            // Set the text
            TextField textField = (TextField) formField;
            textField.setText(value);
        } else if (formField instanceof CheckBox) {
            // Check or un-check
            CheckBox checkBox = (CheckBox) formField;
            checkBox.setChecked(value.equalsIgnoreCase("on"));
        } else if (formField instanceof RadioButtonGroup) {
            // Search the buttons for given name
            RadioButtonGroup group = (RadioButtonGroup) formField;
            for (RadioButton button : group.getButtons()) {
                if (value.equals(button.getExportName())) {
                    // Found: Select this button
                    group.setChosenButton(button);
                    break;
                }
            }
        } else if (formField instanceof ComboBox) {
            // Search for the given item
            ComboBox comboBox = (ComboBox) formField;
            for (ChoiceItem item : comboBox.getItems()) {
                if (value.equals(item.getDisplayName())) {
                    // Found: Select this item
                    comboBox.setChosenItem(item);
                    break;
                }
            }
        } else if (formField instanceof ListBox) {
            // Search for the given item
            ListBox listBox = (ListBox) formField;
            for (ChoiceItem item : listBox.getItems()) {
                if (value.equals(item.getDisplayName())) {
                    // Found: Set this item as the only selected item
                    ChoiceItemList itemList = listBox.getChosenItems();
                    itemList.clear();
                    itemList.add(item);
                    break;
                }
            }
        }
    }
}