"""
File: fit_page.py
Usage: python ./fit_page.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Fit pages to specific page format

"""

from pdftools_toolbox.geometry.real import Size, Point, AffineTransform
from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions
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


def scale_pages_to_fit(in_doc: Document, out_doc: Document):
    copy_options = PageCopyOptions()
    # Copy pages
    for in_page in in_doc.pages:
        page_size = in_page.size
        rotate = (
            ALLOW_ROTATE
            and (page_size.height >= page_size.width) != (TARGET_SIZE.height >= TARGET_SIZE.width)
        )
        rotated_size = Size(
            width=page_size.height, height=page_size.width
        ) if rotate else page_size
        if rotated_size.width == TARGET_SIZE.width and rotated_size.height == TARGET_SIZE.height:
            # If size is correct, copy page only
            out_page = Page.copy(out_doc, in_page, copy_options)
            if rotate:
                out_page.rotate(90)  # Clockwise rotation
        else:
            # Create new page of correct size and fit existing page onto it
            out_page = Page.create(out_doc, TARGET_SIZE)
            # Copy page as group
            group = Group.copy_from_page(out_doc, in_page, copy_options)
            # Calculate scaling and position of group
            scale = min(TARGET_SIZE.width / rotated_size.width, TARGET_SIZE.height / rotated_size.height)
            # Calculate position
            position = Point(
                x=(TARGET_SIZE.width - page_size.width * scale) / 2,
                y=(TARGET_SIZE.height - page_size.height * scale) / 2,
            )
            # Create content generator
            with ContentGenerator(out_page.content, False) as generator:
                # Calculate and apply transformation
                transform = AffineTransform.get_identity()
                transform.translate(position.x, position.y)
                transform.scale(scale, scale)
                # Rotate input file 
                if rotate:
                    center_point = Point(x=page_size.width / 2, y=page_size.height / 2)
                    transform.rotate(90, center_point)
                # Paint group
                generator.transform(transform)
                generator.paint_group(group, None, None)
        # Add the page to the output document
        out_doc.pages.append(out_page)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Fit each page of a PDF document to a specific page format.", usage="python ./fit_page.py <input_path> <output_path>")

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
        TARGET_SIZE = Size(width=595, height=842)  # A4 portrait
        ALLOW_ROTATE = True
        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Process and resize pages
                        scale_pages_to_fit(in_doc, out_doc)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)