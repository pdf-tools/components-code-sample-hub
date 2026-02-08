"""
File: add_data_matrix.py
Usage: python ./add_data_matrix.py <input_path> <image_path> <output_path>
                Example: in.pdf in.png out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add data matrix to PDF

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


def add_data_matrix(document: Document, page: Page, data_matrix_path: str):
    # Create content generator
    with ContentGenerator(page.content, False) as generator:
        #  Import data matrix
        with io.FileIO(data_matrix_path, 'rb') as in_matrix_stream:
            # Create image object for data matrix
            data_matrix = Image.create(document, in_matrix_stream)
            # Data matrix size
            data_matrix_size = 85
            # Calculate Rectangle for data matrix
            rect = Rectangle(left=border, bottom=page.size.height - (data_matrix_size + border), right=data_matrix_size + border, top=page.size.height - border)
        # Paint the positioned barcode text
        generator.paint_image(data_matrix, rect)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a two-dimensional barcode from an existing image on the first page of a PDF document.", usage="python ./add_data_matrix.py <input_path> <image_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("image_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    data_matrix_path = args.image_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Define border
        border = 40
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
                        # Copy first page, add datamatrix image, and append to output document
                        out_page = Page.copy(out_doc, in_doc.pages[0], copy_options)
                        add_data_matrix(out_doc, out_page, data_matrix_path)
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