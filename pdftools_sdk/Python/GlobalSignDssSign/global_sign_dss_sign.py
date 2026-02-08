"""
File: global_sign_dss_sign.py
Usage: python ./global_sign_dss_sign.py <common_name> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Sign a PDF using the GlobalSign Digital Signing Service

"""

import json
from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer
from pdftools_sdk.crypto.providers.global_sign_dss import Session
from pdftools_sdk.crypto import ValidationInformation
from pdftools_sdk.http_client_handler import HttpClientHandler

import argparse, io

def sign(session: Session, common_name: str, input_path: str, output_path: str):
    # Create a signing certificate for an account with a dynamic identity
    identity = json.dumps({"subject_dn": {"common_name": common_name}})
    signature = session.create_signature_for_dynamic_identity(identity)
    # Embed validation information to enable the long term validation (LTV) of the signature (default)
    signature.validation_information = ValidationInformation.EMBED_IN_DOCUMENT
    # Open input document
    with io.FileIO(input_path, 'rb') as in_stream:
        with Document.open(in_stream) as input_document:
            # Create stream for output file
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Sign the document
                signer = Signer()
                signer.sign(input_document, signature, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a document signature, sometimes called an approval signature.\n    This type of signature verifies that the signed document has not been altered and authenticates the signer's identity.\n\n    Validation information is embedded to enable the long-term validation (LTV) of the signature.", usage="python ./global_sign_dss_sign.py <common_name> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("common_name", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    common_name = args.common_name
    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Optional: Set your proxy configuration
        # Sdk.set_proxy("http://myproxy:8080")
        # Configure the SSL client certificate to connect to the service
        http_client_handler = HttpClientHandler()
        with io.FileIO("***insert .cer path***", 'rb') as cert_stream:
            with io.FileIO("***insert .key path***", 'rb') as key_stream:
                http_client_handler.set_client_certificate_and_key(cert_stream, key_stream, "***insert password***")
                # Connect to the GlobalSign DSS service
                with Session("https://emea.api.dss.globalsign.com:8443", "***insert api_key***", "***insert api_secret***", http_client_handler) as session:
                    # Sign a PDF document
                    sign(session, common_name, input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)