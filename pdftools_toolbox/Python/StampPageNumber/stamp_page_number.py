"""
File: stamp_page_number.py
Usage: python ./stamp_page_number.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Stamp page number to PDF

"""

from pdftools_toolbox.geometry.real import Point
from pdftools_toolbox.pdf import Document, FileReference, Metadata, PageCopyOptions, Page
from pdftools_toolbox.pdf.content import ContentGenerator, Font, IccBasedColorSpace, Text, TextGenerator
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


def add_page_number(out_doc, out_page, font, page_number):
    """Stamp the page number on the specified page."""
    # Create content generator
    with ContentGenerator(out_page.content, False) as generator:
        # Create text object
        text = Text.create(out_doc)
        # Create a text generator with the given font, size, and position
        with TextGenerator(text, font, 8, None) as text_generator:
            # Generate string to be stamped as the page number
            stamp_text = f"Page {page_number}"
            # Calculate position for centering text at the bottom of the page
            position = Point(
                x=(out_page.size.width / 2) - (text_generator.get_width(stamp_text) / 2),
                y=10
            )
            # Position the text
            text_generator.move_to(position)
            # Add page number
            text_generator.show(stamp_text)
        # Paint the positioned text
        generator.paint_text(text)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Stamp the page number to the footer of each page of a PDF document.", usage="python ./stamp_page_number.py <input_path> <output_path>")

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
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Define page copy options
                        page_copy_options = PageCopyOptions()
                        # Create embedded font in the output document
                        font = Font.create_from_system(out_doc, "Arial", None, True)
                        # Copy all pages from input document
                        for page_number, in_page in enumerate(in_doc.pages, start=1):
                            # Copy page from input to output
                            out_page = Page.copy(out_doc, in_page, page_copy_options)
                            # Stamp page number on current page of output document
                            add_page_number(out_doc, out_page, font, page_number)
                            # Add page to output document
                            out_doc.pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)