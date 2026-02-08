"""
File: multiple_up.py
Usage: python ./multiple_up.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Place multiple pages on one page

"""

from pdftools_toolbox.geometry.real import Rectangle, Size
from pdftools_toolbox.pdf import Document, FileReference, Metadata, PageCopyOptions, Page
from pdftools_toolbox.pdf.content import ContentGenerator, Group, IccBasedColorSpace
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



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Place four pages of a PDF document on a single page.", usage="python ./multiple_up.py <input_path> <output_path>")

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
        nx = 2
        ny = 2
        page_size = Size(595.0, 842.0)  # A4 portrait
        border = 10.0
        # Open input document
        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as input_document:
                # Create output document
                with io.FileIO(output_file_path, 'wb+') as output_stream:
                    with Document.create(output_stream, input_document.conformance, None) as output_document:
                        out_pages = output_document.pages
                        page_count = 0
                        generator = None
                        out_page = None
                        # Copy document-wide data
                        copy_document_data(input_document, output_document)
                        # Copy all pages from input document
                        for in_page in input_document.pages:
                            if page_count == nx * ny:
                                # Add to output document
                                generator.__exit__(None, None, None)
                                out_pages.append(out_page)
                                out_page = None
                                page_count = 0
                            if out_page is None:
                                # Create a new output page
                                out_page = Page.create(output_document, page_size)
                                generator = ContentGenerator(out_page.content, False)
                            # Get area where group has to be (// calculates the floor of the division)
                            x = int(page_count % nx)
                            y = int(ny - (page_count // nx) - 1)
                            # Compute cell size
                            cell_width = (page_size.width - ((nx + 1) * border)) / nx
                            cell_height = (page_size.height - ((ny + 1) * border)) / ny
                            # Compute cell position
                            cell_x = border + x * (cell_width + border)
                            cell_y = border + y * (cell_height + border)
                            # Define page copy options
                            copy_options = PageCopyOptions()
                            # Copy page as group from input to output
                            group = Group.copy_from_page(output_document, in_page, copy_options)
                            # Compute group position
                            group_size = group.size
                            scale = min(cell_width / group_size.width, cell_height / group_size.height)
                            # Compute target size
                            target_width = group_size.width * scale
                            target_height = group_size.height * scale
                            # Compute position
                            target_x = cell_x + ((cell_width - target_width) / 2)
                            target_y = cell_y + ((cell_height - target_height) / 2)
                            # Compute rectangle
                            target_rect = Rectangle()
                            target_rect.left = target_x
                            target_rect.bottom = target_y
                            target_rect.right = target_x + target_width
                            target_rect.top = target_y + target_height
                            # Add group to page
                            generator.paint_group(group, target_rect, None)
                            page_count += 1
                        # Add page
                        if out_page:
                            generator.__exit__(None, None, None)
                            out_pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)