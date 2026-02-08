"""
File: set_info.py
Usage: python ./set_info.py <input_path> <key> <value> <output_path>
                Example: in.pdf key value out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add info entries to PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList
from pdftools_toolbox.pdf.content import IccBasedColorSpace
from pdftools_toolbox.pdf.navigation import ViewerSettings
from datetime import datetime

import argparse, io

def copy_document_data(in_doc: Document, out_doc: Document):
    # Copy document-wide data (excluding metadata)
    # Output intent
    if in_doc.output_intent is not None:
        in_doc.output_intent = IccBasedColorSpace.copy(out_doc, in_doc.output_intent)
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
    parser = argparse.ArgumentParser(description="Set metadata such as author, title, and creator of a PDF document or add a custom entry.", usage="python ./set_info.py <input_path> <key> <value> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("key", type=str)
    parser.add_argument("value", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    key = args.key
    value = args.value
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
                        # Copy all pages and append to output document
                        copied_pages = PageList.copy(out_doc, in_doc.pages, page_copy_options)
                        out_doc.pages.extend(copied_pages)
                        # Set info entry
                        metadata = Metadata.copy(out_doc, in_doc.metadata)
                        if key == "Title":
                            metadata.title = value
                        elif key == "Author":
                            metadata.author = value
                        elif key == "Subject":
                            metadata.subject = value
                        elif key == "Keywords":
                            metadata.keywords = value
                        elif key == "CreationDate":
                            # Use of the ISO 8601 format for the date
                            date_format = "%Y-%m-%dT%H:%M:%S"
                            parsed_date = datetime.strptime(value, date_format)
                            metadata.creation_date = parsed_date
                        elif key == "ModDate":
                            raise Exception("ModDate cannot be set.")
                        elif key == "Creator":
                            metadata.creator = value
                        elif key == "Producer":
                            raise Exception("Producer is set by means of the license key.")
                        else:
                            metadata.custom_entries[key] = value
                        # Assign modified metadata to the output document
                        out_doc.metadata = metadata

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)