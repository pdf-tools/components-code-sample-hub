"""
File: split.py
Usage: python ./split.py <input_path> <first_page> <last_page> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Remove pages from PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, PageCopyOptions, PageList
from pdftools_toolbox.pdf.content import IccBasedColorSpace
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
    parser = argparse.ArgumentParser(description="Selectively remove pages from a PDF document.", usage="python ./split.py <input_path> <first_page> <last_page> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("first_page", type=str)
    parser.add_argument("last_page", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_file_path = args.output_path
    first_page = args.first_page
    last_page = args.last_page

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        start_index = int(first_page) - 1
        last_page = int(last_page)
        count = last_page - start_index
        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Validate page range
                start_index = max(min(len(in_doc.pages) - 1, start_index), 0)
                count = min(len(in_doc.pages) - start_index, count)
                if count <= 0:
                    raise ValueError("lastPage must be greater or equal to firstPage")
                # Create output document
                with io.FileIO(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Define page copy options
                        page_copy_options = PageCopyOptions()
                        # Get page range from input pages
                        in_page_range = in_doc.pages[start_index:last_page]
                        # Copy page range and append to output document
                        out_page_range = PageList.copy(out_doc, in_page_range, page_copy_options)
                        out_doc.pages.extend(out_page_range)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)