"""
File: add_appearance_signature_field.py
Usage: python ./add_appearance_signature_field.py <certificate_file> <password> <app_config_file> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Sign a PDF and apply a visual signature appearance

"""

import os
from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer
from pdftools_sdk.crypto.providers.built_in import Provider
from pdftools_sdk.sign.appearance import Appearance

import argparse, io

def add_appearance_signature_field(certificate_file: str, password: str, appearance_config_file: str, input_path: str, output_path: str):
    # Create a session to the built-in cryptographic provider
    with Provider() as session:
        # Create signature configuration from PFX (or P12) file
        with io.FileIO(certificate_file, 'rb') as pfx_str:
            signature = session.create_signature_from_certificate(pfx_str, password)
            # Open input document
            with io.FileIO(input_path, 'rb') as input_pdf_stream:
                with Document.open(input_pdf_stream) as input_pdf_document:
                    # Choose first signature field
                    for field in input_pdf_document.signature_fields:
                        if field:
                            signature.field_name = field.field_name
                            break
                    # Create stream for output file
                    with io.FileIO(output_path, 'wb+') as output_stream:
                        # Create appearance configuration from either XML or JSON file
                        with io.FileIO(appearance_config_file, 'rb') as appearance_config_stream:
                            if os.path.splitext(appearance_config_file)[1].lower() == ".xml":
                                signature.appearance = Appearance.create_from_xml(appearance_config_stream)
                            else:
                                signature.appearance = Appearance.create_from_json(appearance_config_stream)
                            signature.appearance.custom_text_variables["company"] = "Daily Planet"
                            # Sign the input document
                            signer = Signer()
                            signer.sign(input_pdf_document, signature, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Sign a PDF document using a provided certificate and apply a visual signature appearance. This process requires an input PDF that already contains a signature field. The provided certificate is used to sign the document and attach the signature to the existing field. The visual appearance of the signature is updated using an XML or JSON file, allowing the addition of text, images, or PDFs. This signature consists of both a visible and a non-visible part. Only the non-visible part is used by other applications to verify the integrity of the signed part of the document and validate the signing certificate. The signing certificate is retrieved from a password-protected PKCS#12 file (.pfx or .p12). ", usage="python ./add_appearance_signature_field.py <certificate_file> <password> <app_config_file> <input_path> <output_path>")

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

        # Sign the input document
        add_appearance_signature_field(certificate_file, password, appearance_config_file, input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)