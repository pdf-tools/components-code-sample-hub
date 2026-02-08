"""
File: add_image.py
Usage: python ./add_image.py <input_path> <image_path> <page_number> <output_path>
                Example: in.pdf in.png 1 out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add image to PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList
from pdftools_toolbox.geometry.real import Rectangle
from pdftools_toolbox.pdf.content import ContentGenerator, IccBasedColorSpace, Image
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


def add_image(document: Document, page: Page, image_path: str, x: float, y: float):
    # Create content generator
    with ContentGenerator(page.content, False) as generator:
        # Load image from input path
        with io.FileIO(image_path, 'rb') as in_image_stream:
            # Create image object
            image = Image.create(document, in_image_stream)
            resolution = 150
            # Calculate rectangle for image
            size = image.size
            rect = Rectangle(
                left=x,
                bottom=y,
                right=x + size.width * 72 / resolution,
                top=y + size.height * 72 / resolution
            )
            # Paint image into the specified rectangle
            generator.paint_image(image, rect)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Place an image with a specified size at a specific location of a page.", usage="python ./add_image.py <input_path> <image_path> <page_number> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("image_path", type=str)
    parser.add_argument("page_number", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    image_path = args.image_path
    try:
        page_number = int(args.page_number)
    except ValueError:
        print("Error: page_number must be an integer.")
        exit(1)
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
                        # Copy pages preceding selected page and append to output document
                        if page_number > 1:
                            in_page_range = in_doc.pages[:page_number - 1]
                            copied_pages = PageList.copy(out_doc, in_page_range, copy_options)
                            out_doc.pages.extend(copied_pages)
                        # Copy selected page, add image, and append to output document
                        out_page = Page.copy(out_doc, in_doc.pages[page_number - 1], copy_options)
                        add_image(out_doc, out_page, image_path, 150, 150)
                        out_doc.pages.append(out_page)
                        # Copy remaining pages and append to output document
                        in_page_range = in_doc.pages[page_number:]
                        copied_pages = PageList.copy(out_doc, in_page_range, copy_options)
                        out_doc.pages.extend(copied_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)