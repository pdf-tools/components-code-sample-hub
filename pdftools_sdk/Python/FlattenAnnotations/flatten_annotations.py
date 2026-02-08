"""
File: flatten_annotations.py
Usage: python ./flatten_annotations.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Flatten annotations

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.optimization import Optimizer
from pdftools_sdk.optimization.profiles import MinimalFileSize
from pdftools_sdk.optimization.conversion_strategy import ConversionStrategy

import argparse, io

def flatten_annotations(input_path: str, output_path: str):
    # Open input document
    with io.FileIO(input_path, 'rb') as in_stream:
        with Document.open(in_stream) as input_document:
            # Create the optimization profile for minimal file size
            profile = MinimalFileSize()
            # Flatten annotations, form fields, and links
            profile.removal_options.annotations = ConversionStrategy.FLATTEN
            profile.removal_options.form_fields = ConversionStrategy.FLATTEN
            profile.removal_options.links = ConversionStrategy.FLATTEN
            # Create output stream
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Optimize the document
                optimizer = Optimizer()
                optimizer.optimize_document(input_document, output_stream, profile)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Optimize a PDF document by flattening the annotations of the PDF. As a result, the annotations are converted to static content.", usage="python ./flatten_annotations.py <input_path> <output_path>")

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

        flatten_annotations(input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)