"""
File: add_signature_field.py
Usage: python ./add_signature_field.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add a signature field to a PDF

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer, SignatureFieldOptions, Appearance
from pdftools_sdk.geometry.units import Size

import argparse, io

def add_signature_field(input_path: str, output_path: str):
    # Open input document
    with io.FileIO(input_path, 'rb') as in_stream:
        with Document.open(in_stream) as input_document:
            # Create empty field appearance that is 6cm by 3cm in size
            appearance = Appearance.create_field_bounding_box(Size(170.08, 85.04))
            # Add field to last page of document
            appearance.page_number = input_document.page_count
            # Position field
            appearance.bottom = 85.04
            appearance.left = 184.25
            # Create a signature field configuration
            field = SignatureFieldOptions(appearance)
            # Create stream for output file
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Sign the input document
                signer = Signer()
                signer.add_signature_field(input_document, field, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add an unsigned signature field that can be signed in another application.\n    The signature field indicates that the document requires a signature and defines the page and position\n    where the signature's visual appearance will be placed. This is especially useful for forms and contracts\n    with designated signature spaces. The signature visual appearance is irrelevant to the signature validation process and only serves as a visual cue for the user.", usage="python ./add_signature_field.py <input_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Sign the input document
        add_signature_field(input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)