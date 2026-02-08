"""
File: built_in_add_timestamp.py
Usage: python ./built_in_add_timestamp.py <time_stamp_url> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add a document time-stamp to a PDF

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer
from pdftools_sdk.crypto.providers.built_in import Provider

import argparse, io

def add_timestamp(time_stamp_url: str, input_path: str, output_path: str):
    # Create a session to the built-in cryptographic provider
    with Provider() as session:
        session.timestamp_url = time_stamp_url
        # Create time-stamp configuration
        timestamp = session.create_timestamp()
        # Open input document
        with io.FileIO(input_path, 'rb') as in_stream:
            with Document.open(in_stream) as input_document:
                # Create stream for output file
                with io.FileIO(output_path, 'wb+') as output_stream:
                    # Add the document time-stamp
                    signer = Signer()
                    signer.add_timestamp(input_document, timestamp, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a trusted document time-stamp to a PDF \n    and confirm that the signed document has not been altered. This type of signature proves that\n    the document existed at a specific time and ensures its integrity.", usage="python ./built_in_add_timestamp.py <time_stamp_url> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("time_stamp_url", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    time_stamp_url = args.time_stamp_url
    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Optional: Set your proxy configuration
        # Sdk.Proxy = new Uri("http://myproxy:8080");
        # Add a document time-stamp to a PDF
        add_timestamp(time_stamp_url, input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)