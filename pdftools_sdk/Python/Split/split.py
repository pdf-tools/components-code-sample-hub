"""
File: split.py
Usage: python ./split.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Split a PDF

"""

import os
from pdftools_sdk.document_assembly import DocumentAssembler
from pdftools_sdk.pdf import Document

import argparse, io

def split_pdf(input_file_path: str, output_file_path: str):
    # Open input document
    with open(input_file_path, 'rb') as input_stream:
        with Document.open(input_stream) as input_document:
            # Split the input document page by page
            for i in range(1, input_document.page_count + 1):
                current_out_file = construct_file_name(output_file_path, i)
                with open(current_out_file, 'wb+') as output_stream:
                    with DocumentAssembler(output_stream, None, None) as assembler:
                        assembler.append(input_document, i, i)
                        assembler.assemble()


# Construct file name from input path and page number of input document
def construct_file_name(input_file: str, page_number: int):
    # Split the directory and file name from the input path
    directory, basename = os.path.split(input_file)
    # Split the file base name and extension
    base, extension = os.path.splitext(basename)
    return os.path.join(directory, f"{base}_page_{page_number}{extension}")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Divide a PDF document into multiple PDF files.", usage="python ./split.py <input_path> <output_path>")

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

        split_pdf(input_path, output_path)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)