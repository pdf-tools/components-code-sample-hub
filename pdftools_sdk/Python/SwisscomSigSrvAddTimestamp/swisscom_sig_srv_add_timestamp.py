"""
File: swisscom_sig_srv_add_timestamp.py
Usage: python ./swisscom_sig_srv_add_timestamp.py <identity> <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add a document time-stamp to a PDF using the Swisscom
Signing Service

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.sign import Signer
from pdftools_sdk.crypto.providers.swisscom_sig_srv import Session
from pdftools_sdk.http_client_handler import HttpClientHandler

import argparse, io

def add_timestamp(session: Session, identity: str, input_path: str, output_path: str):
    # Create timestamp configuration
    timestamp = session.create_timestamp(identity)
    # Open input document
    with io.FileIO(input_path, 'rb') as input_stream:
        with Document.open(input_stream) as input_document:
            # Create stream for output file
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Add the document timestamp
                signer = Signer()
                signer.add_timestamp(input_document, timestamp, output_stream)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a trusted document time-stamp to a PDF and confirm that the signed document has not been altered. This type of signature proves that the document existed at a specific time and ensures its integrity.", usage="python ./swisscom_sig_srv_add_timestamp.py <identity> <input_path> <output_path>")

    # Add arguments
    parser.add_argument("identity", type=str)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    identity = args.identity
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
        with io.FileIO("C:/path/to/clientcert.p12", 'rb') as cert_stream:
            http_client_handler.set_client_certificate(cert_stream, "***insert password***")
            # Connect to the Swisscom Signing Service
            with Session("https://ais.swisscom.com", http_client_handler) as session:
                # Add a document timestamp to a PDF
                add_timestamp(session, identity, input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)