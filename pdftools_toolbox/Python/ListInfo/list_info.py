"""
File: list_info.py
Usage: python ./list_info.py <input_path> [<pdf_password>]
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

List document information of PDF

"""

from pdftools_toolbox.pdf import Document, Permission

import argparse, io

def display_permissions(permissions: int):
    """Display encryption permissions in a readable format."""
    # Display active permission names
    active_permissions = [perm.name for perm in Permission if permissions & perm]
    for perm in active_permissions:
        print(f"  - {perm}")


def list_pdf_info(input_doc: Document):
    """
    List document information and metadata of the given PDF.
    """
    # Conformance
    print(f"Conformance: {input_doc.conformance.name}")
    # Encryption information
    permissions = input_doc.permissions
    if permissions is None:
        print("Not encrypted")
    else:
        display_permissions(permissions)
    # Get metadata
    metadata = input_doc.metadata
    print("Document information:")
    # Display standard metadata
    if metadata.title:
        print(f"  - Title: {metadata.title}")
    if metadata.author:
        print(f"  - Author: {metadata.author}")
    if metadata.subject:
        print(f"  - Subject: {metadata.subject}")
    if metadata.keywords:
        print(f"  - Keywords: {metadata.keywords}")
    if metadata.creation_date:
        print(f"  - Creation Date: {metadata.creation_date}")
    if metadata.modification_date:
        print(f"  - Modification Date: {metadata.modification_date}")
    if metadata.creator:
        print(f"  - Creator: {metadata.creator}")
    if metadata.producer:
        print(f"  - Producer: {metadata.producer}")
    # Display custom entries
    print("Custom entries:")
    for key, value in metadata.custom_entries.items():
        print(f"  - {key}: {value}")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="List attributes of a PDF document (i.e. conformance and encryption information) and metadata (i.e. author, title, creation date etc.).", usage="python ./list_info.py <input_path> [<pdf_password>]")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("pdf_password", type=str, nargs="?", default=None)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    pdf_password = args.pdf_password

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, pdf_password) as in_doc:
                # Process the PDF
                list_pdf_info(in_doc)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)