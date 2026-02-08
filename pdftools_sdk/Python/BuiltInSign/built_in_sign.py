"""
File: built_in_sign.py
Usage: python ./built_in_sign.py <certificate_file> <password> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Sign a PDF using a software-based certificate file

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer, Appearance
from pdftools_sdk.crypto.providers.built_in import Provider
from pdftools_sdk.crypto import ValidationInformation
from pdftools_sdk.geometry.units.size import Size

import argparse, io

def sign(certificate_file: str, password: str, input_path: str, output_path: str):
    # Create a session to the built-in cryptographic provider
    with Provider() as session:
        with io.FileIO(certificate_file, 'rb') as pfx_str:
            # Create signature configuration from PFX (or P12) file
            signature = session.create_signature_from_certificate(pfx_str, password)
            # Embed validation information to enable long-term validation (LTV) of the signature
            signature.validation_information = ValidationInformation.EMBED_IN_DOCUMENT
            signature.appearance = Appearance.create_field_bounding_box(Size(width=200, height=300))
            signature.appearance.page_number = 1
            # Open input document
            with io.FileIO(input_path, 'rb') as input_pdf_stream:
                with Document.open(input_pdf_stream) as input_pdf_document:
                    # Create stream for output file
                    with io.FileIO(output_path, 'wb+') as output_stream:
                        # Sign the input document
                        signer = Signer()
                        signer.sign(input_pdf_document, signature, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a document signature, sometimes called an approval signature.\n    This type of signature verifies the integrity of the signed part of the document and authenticates the signer's identity.\n\n    Validation information is embedded to enable the long-term validation (LTV) of the signature.\n\n    The signing certificate is read from a password-protected PKCS#12 file (.pfx or .p12).", usage="python ./built_in_sign.py <certificate_file> <password> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("certificate_file", type=str)
    parser.add_argument("password", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    certificate_file = args.certificate_file
    password = args.password
    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Sign a PDF document
        sign(certificate_file, password, input_path, output_path)

        print(f"Successfully created signed document {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)