"""
File: add_form_fields.py
Usage: python ./add_form_fields.py <input_path> <output_path>
                Example: Form2NoneNoTP.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add form field

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList, CopyStrategy
from pdftools_toolbox.geometry.real import Rectangle
from pdftools_toolbox.pdf.content import IccBasedColorSpace
from pdftools_toolbox.pdf.forms import CheckBox, ComboBox, FieldNode, FormFieldCopyStrategy, GeneralTextField, ListBox, RadioButtonGroup
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


def add_check_box(doc: Document, field_id: str, is_checked: bool, page: Page, rectangle: Rectangle):
    # Create a check box
    check_box = CheckBox.create(doc)
    # Add the check box to the document
    doc.form_fields[field_id] = check_box
    # Set the check box's state
    check_box.checked = is_checked
    # Create a widget and add it to the page's widgets
    page.widgets.append(check_box.add_new_widget(rectangle))


def add_combo_box(doc: Document, field_id: str, item_names: list[str], value: str, page: Page, rectangle: Rectangle):
    # Create a combo box
    combo_box = ComboBox.create(doc)
    # Add the combo box to the document
    doc.form_fields[field_id] = combo_box
    # Loop over all given item names
    for item_name in item_names:
        # Create a new choice item
        item = combo_box.add_new_item(item_name)
        # Check whether this is the chosen item name
        if value == item_name:
            combo_box.chosen_item = item
    if combo_box.chosen_item is None and value:
        # If no item has been chosen then assume we want to set the editable item
        combo_box.can_edit = True
        combo_box.editable_item_name = value
    # Create a widget and add it to the page's widgets
    page.widgets.append(combo_box.add_new_widget(rectangle))


def add_list_box(doc: Document, field_id: str, item_names: list[str], chosen_names: list[str], page: Page, rectangle: Rectangle):
    # Create a list box
    list_box = ListBox.create(doc)
    # Add the list box to the document
    doc.form_fields[field_id] = list_box
    # Allow multiple selections
    list_box.allow_multi_select = True
    chosen_items = list_box.chosen_items
    # Loop over all given item names
    for item_name in item_names:
        # Create a new choice item
        item = list_box.add_new_item(item_name)
        # Check whether to add to the chosen items
        if item_name in chosen_names:
            chosen_items.append(item)
    # Create a widget and add it to the page's widgets
    page.widgets.append(list_box.add_new_widget(rectangle))


def add_radio_button_group(doc: Document, field_id: str, button_names: list[str], chosen: int, page: Page, rectangle: Rectangle):
    # Create a radio button group
    group = RadioButtonGroup.create(doc)
    # Get the page's widgets
    widgets = page.widgets
    # Add the radio button group to the document
    doc.form_fields[field_id] = group
    # We partition the given rectangle horizontally into sub-rectangles, one for each button
    #  Compute the width of the sub-rectangles
    button_width = (rectangle.right - rectangle.left) / len(button_names)
    # Loop over all button names
    for i, button_name in enumerate(button_names):
        # Compute the sub-rectangle for this button
        button_rectangle = Rectangle(
            left = rectangle.left + i * button_width,
            bottom = rectangle.bottom,
            right = rectangle.left + (i + 1) * button_width,
            top = rectangle.top
        )
        # Create the button and associated widget
        button = group.add_new_button(button_name)
        widget = button.add_new_widget(button_rectangle)
        # Check if this is the chosen button
        if i == chosen:
            group.chosen_button = button
        # Add the widget to the page's widgets
        widgets.append(widget)


def add_general_text_field(doc: Document, field_id: str, value: str, page: Page, rectangle: Rectangle):
    # Create a general text field
    text_field = GeneralTextField.create(doc)
    # Add the field to the document
    doc.form_fields[field_id] = text_field
    # Set the text value
    text_field.text = value
    # Create a widget and add it to the page's widgets
    page.widgets.append(text_field.add_new_widget(rectangle))



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add form fields to a PDF.", usage="python ./add_form_fields.py <input_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, 'wb+') as output_stream:
                    with Document.create(output_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Copy all form fields
                        in_form_fields = in_doc.form_fields
                        out_form_fields = out_doc.form_fields
                        for in_pair_key, in_pair_node in in_form_fields.items():
                            out_form_field_node = FieldNode.copy(out_doc, in_pair_node)
                            out_form_fields[in_pair_key] = out_form_field_node
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        copy_options.form_fields = FormFieldCopyStrategy.COPY_AND_UPDATE_WIDGETS
                        copy_options.unsigned_signatures = CopyStrategy.REMOVE
                        # Copy first page
                        out_page = Page.copy(out_doc, in_doc.pages[0], copy_options)
                        # Add different types of form fields to the output page
                        add_check_box(out_doc, "Check Box ID", True, out_page, Rectangle(left=50.0, bottom=300.0, right=70.0, top=320.0))
                        add_combo_box(out_doc, "Combo Box ID", ["item 1", "item 2"], "item 1", out_page, Rectangle(left=50.0, bottom=260.0, right=210.0, top=280.0))
                        add_list_box(out_doc, "List Box ID", ["item 1", "item 2", "item 3"], ["item 1", "item 3"], out_page, Rectangle(left=50.0, bottom=160.0, right=210.0, top=240.0))
                        add_radio_button_group(out_doc, "Radio Button ID", ["A", "B", "C"], 0, out_page, Rectangle(left=50.0, bottom=120.0, right=210.0, top=140.0))
                        add_general_text_field(out_doc, "Text ID", "Text", out_page, Rectangle(left=50.0, bottom=80.0, right=210.0, top=100.0))
                        # Add page to output document
                        out_doc.pages.append(out_page)
                        # Copy remaining pages and append to output document
                        in_page_range = in_doc.pages[1:]
                        copied_pages = PageList.copy(out_doc, in_page_range, copy_options)
                        out_doc.pages.extend(copied_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)