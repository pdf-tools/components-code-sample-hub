"""
File: add_text.py
Usage: python ./add_text.py <input_path> <text_string> <output_path>
                Example: in.pdf \"Test String\" out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add text to PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList
from pdftools_toolbox.geometry.real import Point
from pdftools_toolbox.pdf.content import Font, ContentGenerator, IccBasedColorSpace, Text, TextGenerator
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


def add_text(output_doc: Document, output_page: Page, text_string: str):
    # Create content generator and text object
    with ContentGenerator(output_page.content, False) as gen:
        text = Text.create(output_doc)
        # Create text generator
        with TextGenerator(text, font, font_size, None) as textGenerator:
            # Calculate position
            position = Point(border, output_page.size.height - border - font_size * font.ascent)
            # Move to position
            textGenerator.move_to(position)
            # Add given text string
            textGenerator.show_line(text_string)
        # Paint the positioned text
        gen.paint_text(text)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add text at a specified position on the first page of a PDF document.", usage="python ./add_text.py <input_path> <text_string> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("text_string", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    text_string = args.text_string
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Define global variables
        border = 40.0
        font_size = 15.0
        # Open input document
        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as input_document:
                # Create output document
                with io.FileIO(output_file_path, 'wb+') as output_stream:
                    with Document.create(output_stream, input_document.conformance, None) as output_document:
                        # Copy document-wide data
                        copy_document_data(input_document, output_document)
                        # Create a font
                        font = Font.create_from_system(output_document, "Arial", "Italic", True)
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        # Copy first page, add text, and append to output document
                        out_page = Page.copy(output_document, input_document.pages[0], copy_options)
                        add_text(output_document, out_page, text_string)
                        output_document.pages.append(out_page)
                        # Copy remaining pages and append to output document
                        inPageRange = input_document.pages[1:]
                        copied_pages = PageList.copy(output_document, inPageRange, copy_options)
                        output_document.pages.extend(copied_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)