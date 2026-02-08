"""
File: built_in_certify.py
Usage: python ./built_in_certify.py <certificate_file> <password> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Certify a PDF

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer
from pdftools_sdk.crypto.providers.built_in import Provider
from pdftools_sdk.crypto import ValidationInformation

import argparse, io

def certify_document(certificate_file: str, password: str, input_path: str, output_path: str):
    # Create a session to the built-in cryptographic provider
    with Provider() as session:
        with io.FileIO(certificate_file, 'rb') as pfx_stream:
            # Create signature configuration from PFX (or P12) file
            signature = session.create_signature_from_certificate(pfx_stream, password)
            # Embed validation information to enable the long-term validation (LTV) of the signature
            signature.validation_information = ValidationInformation.EMBED_IN_DOCUMENT
            # Open input document
            with io.FileIO(input_path, 'rb') as in_stream:
                with Document.open(in_stream) as input_document:
                    # Create stream for output file
                    with io.FileIO(output_path, 'wb+') as output_stream:
                        # Certify the document with the MDP signature
                        signer = Signer()
                        signer.certify(input_document, signature, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="This type of signature allows the PDF author to specify which types of modifications are permissible after signing.\n    These signatures are also known as Modification Detection and Prevention (MDP) signatures.\n\n    The signing certificate is read from a password-protected PKCS#12 file (.pfx or .p12).\n    ", usage="python ./built_in_certify.py <certificate_file> <password> <input_path> <output_path>")

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

        # Certify a PDF document
        certify_document(certificate_file, password, input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)