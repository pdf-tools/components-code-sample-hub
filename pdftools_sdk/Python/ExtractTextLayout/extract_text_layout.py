"""
File: extract_text_layout.py
Usage: python ./extract_text_layout.py <input_path> <output_dir>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Extract text mimicking layout

"""

import os
from pdftools_sdk.pdf import Document
from pdftools_sdk.extraction import Extractor, TextOptions, TextExtractionFormat

import argparse, io

def extract_text(input_file_path: str, output_directory: str):
    # Open input document
    with open(input_file_path, 'rb') as in_stream:
        with Document.open(in_stream) as in_doc:
            # Create directory if it doesn't exist
            if not os.path.exists(output_directory):
                os.makedirs(output_directory)
            # Set extraction options
            options = TextOptions()
            options.extraction_format = TextExtractionFormat.MONOSPACE
            options.advance_width = 9.2
            # Extract text page by page
            extractor = Extractor()
            for i in range(in_doc.page_count):
                output_file = os.path.join(output_directory, f"page{i + 1}.txt")
                with open(output_file, 'wb') as out_stream:
                    extractor.extract_text(in_doc, out_stream, options, i + 1, i + 1)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Extracting text from a PDF page by page into text files, preserving the original layout by adding whitespaces to the monospace text.", usage="python ./extract_text_layout.py <input_path> <output_dir>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_dir", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_path = args.input_path
    output_dir = args.output_dir

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        extract_text(input_path, output_dir)

        print(f"Successfully extracted page-wise text from PDF to {output_dir}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)