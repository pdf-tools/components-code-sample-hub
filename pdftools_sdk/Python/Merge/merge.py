"""
File: merge.py
Usage: python ./merge.py <input_path> [<input_path2> ...] <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Merge PDFs

"""

from pdftools_sdk.document_assembly import DocumentAssembler
from pdftools_sdk.pdf import Document

import argparse, io

def merge(input_paths: str, output_path: str):
    # Create output stream
    with io.FileIO(output_path, 'wb+') as output_stream:
        with DocumentAssembler(output_stream, None, None) as assembler:
            for input_path in input_paths:
                with open(input_path, 'rb') as input_stream:
                    with Document.open(input_stream) as input_document:
                        # Append the content of the input documents to the output document
                        assembler.append(input_document)
            # Merge input documents into an output document
            assembler.assemble()



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Merge multiple PDF documents into a single file.", usage="python ./merge.py <input_path> [<input_path2> ...] <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str, nargs="*")
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_paths = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        merge(input_paths, output_path)

        print(f"Successfully created file {output_path}.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)