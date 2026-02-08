"""
File: add_vector_graphics.py
Usage: python ./add_vector_graphics.py <input_path> <output_path>
                Example: in.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add vector graphic to PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions
from pdftools_toolbox.geometry.real import Point
from pdftools_toolbox.pdf.content import ColorSpace, ContentGenerator, IccBasedColorSpace, Paint, ProcessColorSpaceType, Stroke, Path, PathGenerator
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


def add_line(out_doc: Document, page: Page):
    # Extract content generator
    with ContentGenerator(page.content, False) as generator:
        # Create a path
        path = Path()
        with PathGenerator(path) as path_generator:
            # Draw a line diagonally across the page
            page_size = page.size
            path_generator.move_to(Point(x = 10.0, y = 10.0))
            path_generator.line_to(Point(x = page_size.width - 10.0, y=page_size.height - 10.0))
        # Create a RGB color space
        device_rgb_color_space = ColorSpace.create_process_color_space(out_doc, ProcessColorSpaceType.RGB)
        # Create a red color
        red = [1.0, 0.0, 0.0]
        #  Create a paint
        paint = Paint.create(out_doc, device_rgb_color_space, red, None)
        # Create stroking parameters with given paint and line width
        stroke = Stroke(paint, 10.0)
        # Draw the path onto the page
        generator.paint_path(path, None, stroke)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Draw a line on an existing PDF page.", usage="python ./add_vector_graphics.py <input_path> <output_path>")

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
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        # Copy all pages from input document
                        for in_page in in_doc.pages:
                            out_page = Page.copy(out_doc, in_page, copy_options)
                            # Add a line
                            add_line(out_doc, out_page)
                            # Add page to output document
                            out_doc.pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)