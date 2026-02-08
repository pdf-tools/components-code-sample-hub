"""
File: fill_form_fields.py
Usage: python ./fill_form_fields.py <field_i_d> <value> <input_path> <output_path>
                Example: TextField1 \"New Text\" Form2None.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Fill form fields

"""

from pdftools_toolbox.pdf import CopyStrategy, Document, FileReference, Metadata, PageList, PageCopyOptions
from pdftools_toolbox.pdf.forms import TextField, CheckBox, ComboBox, Field, FieldNode, FormFieldCopyStrategy, ListBox, RadioButtonGroup
from pdftools_toolbox.pdf.content import IccBasedColorSpace
from pdftools_toolbox.pdf.navigation import ViewerSettings

import argparse, io

def copy_document_data(in_doc: Document, out_doc: Document):
    # Copy document-wide data
    # Output intent
    if in_doc.output_intent is not None:
        in_doc.output_intent = IccBasedColorSpace.copy(out_doc, in_doc.output_intent)
    # Metadata
    out_doc.metadata = Metadata.copy(out_doc, in_doc.metadata)
    # Viewer settings
    out_doc.viewer_settings = ViewerSettings.copy(out_doc, in_doc.viewer_settings)
    # Associated files (for PDF/A-3 and PDF 2.0 only)
    outAssociatedFiles = out_doc.associated_files
    for in_file_ref in in_doc.associated_files:
        outAssociatedFiles.append(FileReference.copy(out_doc, in_file_ref))
    # Plain embedded files
    out_embedded_files = out_doc.plain_embedded_files
    for in_file_ref in in_doc.plain_embedded_files:
        out_embedded_files.append(FileReference.copy(out_doc, in_file_ref))


def fill_form_field(form_field: Field, value: str):
    """Set the value of a form field based on its type."""
    if isinstance(form_field, TextField):
        form_field.text = value
    elif isinstance(form_field, CheckBox):
        form_field.checked = value.lower() == "on"
    elif isinstance(form_field, RadioButtonGroup):
        for button in form_field.buttons:
            if button.export_name == value:
                form_field.chosen_button = button
                break
    elif isinstance(form_field, ComboBox):
        for item in form_field.items:
            if item.display_name == value:
                form_field.chosen_item = item
                break
    elif isinstance(form_field, ListBox):
        for item in form_field.items:
            if item.display_name == value:
                form_field.chosen_items.clear()
                form_field.chosen_items.append(item)
                break



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Change values of AcroForm form fields.", usage="python ./fill_form_fields.py <field_i_d> <value> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("field_i_d", type=str)
    parser.add_argument("value", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    field_identifier = args.field_i_d
    field_value = args.value
    input_file_path = args.input_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Copy form fields
                        in_fields = in_doc.form_fields
                        out_fields = out_doc.form_fields
                        for key, in_field_node in in_fields.items():
                            out_fields[key] = FieldNode.copy(out_doc, in_field_node)
                        # Find the form field and update its value
                        selected_field = out_fields.lookup(field_identifier)
                        if selected_field:
                            fill_form_field(selected_field, field_value)
                        # Configure page copy options
                        copy_options = PageCopyOptions()
                        copy_options.form_fields = FormFieldCopyStrategy.COPY_AND_UPDATE_WIDGETS
                        copy_options.unsigned_signatures = CopyStrategy.REMOVE
                        # Copy all pages
                        copied_pages = PageList.copy(out_doc, in_doc.pages, copy_options)
                        out_doc.pages.extend(copied_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)