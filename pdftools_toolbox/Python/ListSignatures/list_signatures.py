"""
File: list_signatures.py
Usage: python ./list_signatures.py <input_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

List Signatures in PDF

"""

from pdftools_toolbox.pdf import Document
from pdftools_toolbox.pdf.forms import Signature

import argparse, io

def list_signatures(in_doc: Document):
    # Retrieve the list of signature fields
    signature_fields = in_doc.signature_fields
    print(f"Number of signature fields: {len(signature_fields)}")
    for field in signature_fields:
        if isinstance(field, Signature):
            # List name
            name = field.name or "(Unknown name)"
            print(f"- {'Visible' if field.is_visible else 'Invisible'} field, signed by: {name}")
            # List location
            if field.location:
                print(f"  - Location: {field.location}")
            # List reason
            if field.reason:
                print(f"  - Reason: {field.reason}")
            # List contact info
            if field.contact_info:
                print(f"  - Contact info: {field.contact_info}")
            # List date
            if field.date:
                print(f"  - Date: {field.date}")
        else:
            print(f"- {'Visible' if field.is_visible else 'Invisible'} field, not signed")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="List all signature fields in a PDF document and their properties.", usage="python ./list_signatures.py <input_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # List all signatures of the PDF document
                list_signatures(in_doc)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)