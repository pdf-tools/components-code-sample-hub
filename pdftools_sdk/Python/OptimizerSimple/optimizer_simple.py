"""
File: optimizer_simple.py
Usage: python ./optimizer_simple.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Optimize a PDF

"""

from pdftools_sdk.optimization import Optimizer
from pdftools_sdk.optimization.profiles import Web
from pdftools_sdk.pdf import Document

import argparse, io

def optimize_pdf(input_path: str, output_path: str):
    # Open input document
    with io.FileIO(input_path, 'rb') as input_stream:
        with Document.open(input_stream) as input_document:
            # Create the profile that defines the optimization parameters.
            # The Web profile is used to optimize documents for electronic document exchange.
            profile = Web()
            # Optionally the profile's parameters can be changed according to the 
            # requirements of your optimization process.
            # Create output stream
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Optimize the document
                optimizer = Optimizer()
                optimizer.optimize_document(input_document, output_stream, profile)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Optimize a PDF with the \"Web\" optimization profile.", usage="python ./optimizer_simple.py <input_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        optimize_pdf(input_path, output_path)

        print(f"Successfully created file {output_path}.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)