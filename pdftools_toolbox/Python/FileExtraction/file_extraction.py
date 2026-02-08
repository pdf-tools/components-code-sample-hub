"""
File: file_extraction.py
Usage: python ./file_extraction.py <input_path> <output_dir>
                Example: in.pdf dir/subdir/

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Extract files embedded from a PDF

"""

import os
from pdftools_toolbox.pdf import Document, FileReference

import argparse, io

def copy_to_stream(data: io.IOBase, out_stream: io.IOBase, chunk_size: int = 4096):
    """Copy data from an IO stream to another."""
    while chunk := data.read(chunk_size):
        out_stream.write(chunk)


def extract_file(file_reference: FileReference, output_dir: str):
    # Remove null characters
    clean_file_name = file_reference.name.replace(chr(0), "")
    output_path = os.path.join(output_dir, clean_file_name)
    if file_reference.data is None:
        raise ValueError("The file_reference.data stream is None.")
    if not file_reference.data.readable():
        raise ValueError("The file_reference.data stream is not readable.")
    # Ensure the output directory exists
    os.makedirs(output_dir, exist_ok=True)
    with io.FileIO(output_path, "wb") as out_file:
        copy_to_stream(file_reference.data, out_file)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Extract the embedded files contained in the PDF to the file system.", usage="python ./file_extraction.py <input_path> <output_dir>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_dir", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_dir = args.output_dir

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                file_ref_list = in_doc.all_embedded_files
                for file_ref in file_ref_list:
                    extract_file(file_ref, output_dir)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)