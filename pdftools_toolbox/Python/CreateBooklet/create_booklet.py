"""
File: create_booklet.py
Usage: python ./create_booklet.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Create a booklet from PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList
from pdftools_toolbox.geometry.real import Point, Rectangle, Size
from pdftools_toolbox.pdf.content import Font, ContentGenerator, Group, IccBasedColorSpace, Text, TextGenerator
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


def compute_target_rect(bbox: Size, is_left_page: bool) -> Rectangle:
    # Calculate factor for fitting page into rectangle
    scale = min(cell_width / bbox.width, cell_height / bbox.height)
    group_width = bbox.width * scale
    group_height = bbox.height * scale
    # Calculate x-value
    group_x_pos = cell_left + (cell_width - group_width) / 2 if is_left_page else cell_right + (cell_width - group_width) / 2
    # Calculate y-value
    group_y_pos = cell_y_pos + (cell_height - group_height) / 2
    # Calculate rectangle
    return Rectangle(
        left=group_x_pos,
        bottom=group_y_pos,
        right=group_x_pos + group_width,
        top=group_y_pos + group_height,
    )


def stamp_page_number(document: Document, font: Font, generator: ContentGenerator, page_no: int, is_left_page: bool):
    # Create text object
    text = Text.create(document)
    # Create text generator
    with TextGenerator(text, font, 8.0, None) as text_generator:
        stamp_text = f"Page {page_no}"
        # Get width of stamp text
        width = text_generator.get_width(stamp_text)
        # Calculate position
        x = border + 0.5 * cell_width - width / 2 if is_left_page else 2 * border + 1.5 * cell_width - width / 2
        y = border
        # Move to position
        text_generator.move_to(Point(x=x, y=y))
        # Add page number
        text_generator.show(stamp_text)
    # Paint the positioned text
    generator.paint_text(text)


def create_booklet(in_pages: PageList, out_doc: Document, out_pages: PageList, left_page_index: int, right_page_index: int, font: Font):
    # Define page copy options
    copy_options = PageCopyOptions()
    # Create page object
    out_page = Page.create(out_doc, page_size)
    # Create content generator
    with ContentGenerator(out_page.content, False) as generator:
        # Left page
        if left_page_index < len(in_pages):
            # Copy page from input to output
            left_page = in_pages[left_page_index]
            left_group = Group.copy_from_page(out_doc, left_page, copy_options)
            # Paint group into target rectangle
            generator.paint_group(left_group, compute_target_rect(left_group.size, True), None)
            # Add page number to page
            stamp_page_number(out_doc, font, generator, left_page_index + 1, True)
        # Right page
        if right_page_index < len(in_pages):
            # Copy page from input to output
            right_page = in_pages[right_page_index]
            right_group = Group.copy_from_page(out_doc, right_page, copy_options)
            # Paint group on the calculated rectangle
            generator.paint_group(right_group, compute_target_rect(right_group.size, False), None)
            # Add page number to page
            stamp_page_number(out_doc, font, generator, right_page_index + 1, False)
    # Add page to output document
    out_pages.append(out_page)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Place up to two A4 pages in the right order on an A3 page, so that duplex printing and folding the A3 pages results in a booklet.", usage="python ./create_booklet.py <input_path> <output_path>")

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

        # Define global variables
        page_size = Size(1190.0, 842.0)  # A3 portrait
        border = 10.0
        cell_width = (page_size.width - 3 * border) / 2
        cell_height = page_size.height - 2 * border
        cell_left = border
        cell_right = 2 * border + cell_width
        cell_y_pos = border
        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, "wb+") as output_stream:
                    with Document.create(output_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Create a font
                        font = Font.create_from_system(out_doc, "Arial", "Italic", True)
                        # Copy pages
                        in_pages = in_doc.pages
                        out_pages = out_doc.pages
                        number_of_sheets = (len(in_pages) + 3) // 4
                        for sheet_number in range(number_of_sheets):
                            # Add front side
                            create_booklet(in_pages, out_doc, out_pages, 4 * number_of_sheets - 2 * sheet_number - 1, 2 * sheet_number, font)
                            # Add back side
                            create_booklet(in_pages, out_doc, out_pages, 2 * sheet_number + 1, 4 * number_of_sheets - 2 * sheet_number - 2, font)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)