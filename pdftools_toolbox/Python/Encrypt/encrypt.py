"""
File: encrypt.py
Usage: python ./encrypt.py <input_path> <user_password> <owner_password> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Encrypt PDF

"""

from pdftools_toolbox.pdf import Document, Encryption, FileReference, Metadata, PageCopyOptions, PageList, Permission
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
    parser = argparse.ArgumentParser(description="Encrypt a PDF document with a user password and an owner password. When opening the document, either of the passwords must be provided. If providing the user password, the document can be viewed and printed only. Providing the owner password grants full access to the document.", usage="python ./encrypt.py <input_path> <user_password> <owner_password> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("user_password", type=str)
    parser.add_argument("owner_password", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    user_pwd = args.user_password
    owner_pwd = args.owner_password
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create encryption parameters
                encryption_params = Encryption(
                    user_pwd,
                    owner_pwd,
                    Permission.PRINT | Permission.DIGITAL_PRINT,
                )
                # Create output document and set a user and owner password
                with io.FileIO(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, encryption_params) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        # Copy all pages and append to output document
                        copied_pages = PageList.copy(out_doc, in_doc.pages, copy_options)
                        out_doc.pages.extend(copied_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)