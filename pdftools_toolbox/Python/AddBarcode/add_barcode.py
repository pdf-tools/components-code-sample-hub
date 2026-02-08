"""
File: add_barcode.py
Usage: python ./add_barcode.py <input_path> <barcode> <fontfile> <output_path>
                Example: in.pdf \"PDF123\" free3of9.ttf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add barcode to PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList
from pdftools_toolbox.geometry.real import Point
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


def add_barcode(out_doc: Document, out_page: Page, barcode: str, font: Font, font_size: float):
    # Create content generator
    with ContentGenerator(out_page.content, False) as gen:
        # Create text object
        barcode_text = Text.create(out_doc)
        #  Create text generator
        with TextGenerator(barcode_text, font, font_size, None) as text_generator:
            # Calculate position
            position = Point(x=out_page.size.width - (text_generator.get_width(barcode) + border), 
                             y=out_page.size.height - (font_size * (font.ascent + font.descent) + border))
            # Move to position
            text_generator.move_to(position)
            # Add given barcode string
            text_generator.show_line(barcode)
        # Paint the positioned barcode text
        gen.paint_text(barcode_text)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Generate and add a barcode at a specified position on the first page of a PDF document.", usage="python ./add_barcode.py <input_path> <barcode> <fontfile> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("barcode", type=str)
    parser.add_argument("fontfile", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    barcode = args.barcode
    font_path = args.fontfile
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Define border
        border = 20
        # Open input document
        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create font stream
                with io.FileIO(font_path, 'rb') as font_stream:
                    # Create output document
                    with io.FileIO(output_file_path, 'wb+') as output_stream:
                        with Document.create(output_stream, in_doc.conformance, None) as out_doc:
                            # Copy document-wide data
                            copy_document_data(in_doc, out_doc)
                            # Create embedded font in output document
                            font = Font.create(out_doc, font_stream, True)
                            # Define page copy options
                            copy_options = PageCopyOptions()
                            # Copy first page, add barcode, and append to output document
                            out_page = Page.copy(out_doc, in_doc.pages[0], copy_options)
                            add_barcode(out_doc, out_page, barcode, font, 50.0)
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