"""
File: visual_signature.py
Usage: python ./visual_signature.py <certificate_file> <password> <app_config_file> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Sign a PDF and add a visual appearance

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer
from pdftools_sdk.crypto.providers.built_in import Provider
from pdftools_sdk.sign import Appearance

import argparse, io

def sign(certificate_file: str, password: str, appearance_config_file: str, input_path: str, output_path: str):
    # Create a session with the built-in cryptographic provider
    with Provider() as session:
        # Open certificate file
        with io.FileIO(certificate_file, 'rb') as pfx_stream:
            # Create signature configuration from PFX (or P12) file
            signature = session.create_signature_from_certificate(pfx_stream, password)
            # Create appearance from either an XML or JSON file
            with io.FileIO(appearance_config_file, 'rb') as appearance_stream:
                if appearance_config_file.endswith(".xml"):
                    signature.appearance = Appearance.create_from_xml(appearance_stream)
                else:
                    signature.appearance = Appearance.create_from_json(appearance_stream)
            signature.appearance.page_number = 1
            signature.appearance.custom_text_variables["company"] = "Daily Planet"
            # Open input document
            with io.FileIO(input_path, 'rb') as input_stream:
                with Document.open(input_stream) as input_document:
                    # Create stream for output file
                    with io.FileIO(output_path, 'wb+') as output_stream:
                        # Sign the input document
                        signer = Signer()
                        signer.sign(input_document, signature, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a document signature with a visual appearance.\n    The visual appearance is configured using an XML or JSON file, allowing the addition of text, images, or PDFs.\n    \n    This signature consists of both a visible and a non-visible part. \n    Only the non-visible part verifies the integrity of the signed part of the document and authenticates the signer's identity.\n    The signing certificate is read from a password-protected PKCS#12 file (.pfx or .p12).", usage="python ./visual_signature.py <certificate_file> <password> <app_config_file> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("certificate_file", type=str)
    parser.add_argument("password", type=str)
    parser.add_argument("app_config_file", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    certificate_file = args.certificate_file
    password = args.password
    appearance_config_file = args.app_config_file
    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Optional: Set your proxy configuration
        # Sdk.set_proxy("http://myproxy:8080")
        # Sign a PDF document
        sign(certificate_file, password, appearance_config_file, input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)