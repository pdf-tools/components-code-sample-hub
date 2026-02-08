"""
File: pkcs11_sign.py
Usage: python ./pkcs11_sign.py <pkcs11_library> <password> <certificate> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Sign a PDF using a PKCS#11 device

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer
from pdftools_sdk.crypto.providers.pkcs11 import Module, Session

import argparse, io

def sign(session: Session, certificate: str, input_path: str, output_path: str):
    # Create the signature configuration for the certificate
    signature = session.create_signature_from_name(certificate)
    # Open input document
    with io.FileIO(input_path, 'rb') as in_stream:
        with Document.open(in_stream) as input_document:
            # Create stream for output file
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Sign the input document
                signer = Signer()
                signer.sign(input_document, signature, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a document signature, sometimes called an approval signature.\n    This type of signature verifies the integrity of the signed part of the document and authenticates the signer's identity.\n\n    Validation information is embedded to enable the long-term validation (LTV) of the signature.\n\n    The signing certificate is stored on a cryptographic device with PKCS#11 middleware (driver).", usage="python ./pkcs11_sign.py <pkcs11_library> <password> <certificate> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("pkcs11_library", type=str)
    parser.add_argument("password", type=str)
    parser.add_argument("certificate", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    pkcs11_library = args.pkcs11_library
    password = args.password
    certificate = args.certificate
    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Optional: Set your proxy configuration
        # Sdk.set_proxy("http://myproxy:8080")
        # Load the PKCS#11 driver module (middleware)
        # The module can only be loaded once in the application.
        with Module.load(pkcs11_library) as module:
            # Create a session to the cryptographic device and log in with the password (pin)
            # Use devices[i] if you have more than one device installed instead of devices.get_single()
            with module.devices.get_single().create_session(password) as session:
                # Sign a PDF document
                sign(session, certificate, input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)