"""
File: set_open_destination.py
Usage: python ./set_open_destination.py <input_path> <page_number> <output_path>
                Example: in.pdf 2 out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Set the open-destination of a PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, PageCopyOptions, PageList
from pdftools_toolbox.pdf.content import IccBasedColorSpace
from pdftools_toolbox.pdf.navigation import ViewerSettings, LocationZoomDestination

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
    parser = argparse.ArgumentParser(description="Set the page that is displayed when opening the document.", usage="python ./set_open_destination.py <input_path> <page_number> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("page_number", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    page_number = args.page_number
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        destination_page_number = int(page_number)
        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                if destination_page_number < 1 or destination_page_number > len(in_doc.pages):
                    raise ValueError("Given page number is invalid")
                # Create output document
                with io.FileIO(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Define page copy options
                        page_copy_options = PageCopyOptions()
                        # Copy all pages and append to output document
                        copied_pages = PageList.copy(out_doc, in_doc.pages, page_copy_options)
                        out_doc.pages.extend(copied_pages)
                        # Add open destination
                        out_page = copied_pages[destination_page_number - 1]
                        out_doc.open_destination = LocationZoomDestination.create(out_doc, out_page, 0, out_page.size.height, None)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)