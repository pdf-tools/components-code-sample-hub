"""
File: encrypt.py
Usage: python ./encrypt.py <password> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Encrypt a PDF

"""

import io
from ctypes import *
from pdftools_sdk.pdf import Document, Encryption, Permission
from pdftools_sdk.sign import OutputOptions as SignOutputOptions, SignatureRemoval, Signer
import argparse


def encrypt(password: str, input_path: str, output_path: str):
    # Open input document
    with io.FileIO(input_path, 'rb') as in_stream:
        with Document.open(in_stream) as input_document:
            # Create stream for output file
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Set encryption options
                output_options = SignOutputOptions()
                # Set a user password that will be required to open the document.
                # Note that this will remove PDF/A conformance of input files (see warning category Sign.WarningCategory.PdfARemoved)
                output_options.encryption = Encryption(password, None, Permission.ALL)
                # Allow removal of signatures. Otherwise the Encryption property is ignored for signed input documents
                # (see warning category Sign.WarningCategory.SignedDocEncryptionUnchanged).
                output_options.remove_signatures = SignatureRemoval.SIGNED

                # Encrypt the document
                signer = Signer()
                signer.process(input_document, output_stream, output_options)


if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Encrypt a PDF document with a user password.\n    To open the document, the user password is required.", usage="python ./encrypt.py <password> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("password", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # Sdk.initialize("<PDFSDK,V1,MGAASQD6L2JMQHL54PK08RQX8GG4SS0M8DAHVPH0VMP3NB8R9DUK>")

        # Encrypt a PDF document
        encrypt(args.password, args.input_path, args.output_path)

        print(f"Successfully created encrypted {args.output_path}")
        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)
