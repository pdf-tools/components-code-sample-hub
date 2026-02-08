"""
File: decrypt.py
Usage: python ./decrypt.py <password> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Decrypt an encrypted PDF

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import OutputOptions as SignOutputOptions, SignatureRemoval, Signer

import argparse, io

def decrypt(password, input_path, output_path):
    # Use password to open encrypted input document
    with io.FileIO(input_path, 'rb') as in_stream:
        with Document.open(in_stream, password) as input_document:
            if input_document.permissions == None:
                print(f"Input file is not encrypted.")
                return
            # Create stream for output file
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Set encryption options
                output_options = SignOutputOptions()
                # Set encryption parameters to no encryption
                output_options.encryption = None
                # Allow removal of signatures. Otherwise the Encryption property is ignored for signed input documents
                # (see warning category Sign.WarningCategory.SignedDocEncryptionUnchanged).
                output_options.remove_signatures = SignatureRemoval.SIGNED
                # Decrypt the document
                signer = Signer()
                signer.process(input_document, output_stream, output_options)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Remove encryption from a PDF.", usage="python ./decrypt.py <password> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("password", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    password = args.password
    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Decrypt a PDF document
        decrypt(password, input_path, output_path)

        print(f"Successfully created decrypted {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)