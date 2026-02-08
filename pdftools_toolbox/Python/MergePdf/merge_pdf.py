"""
File: merge_pdf.py
Usage: python ./merge_pdf.py <input_path> [<input_path2> ...] <output_path>
                Example: in1.pdf in2.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Merge multiple PDFs

"""

from pdftools_toolbox.pdf import Document, PageCopyOptions, PageList

import argparse, io

if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Merge several PDF documents to one.", usage="python ./merge_pdf.py <input_path> [<input_path2> ...] <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str, nargs="*")
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_paths = args.input_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Create output document
        with open(output_file_path, "wb+") as out_stream:
            with Document.create(out_stream, None, None) as out_doc:
                # Define page copy options
                page_copy_options = PageCopyOptions()
                # Get output pages
                out_pages = out_doc.pages
                # Merge input documents
                for input_path in input_paths:
                    # Open input document
                    with open(input_path, "rb") as in_stream:
                        with Document.open(in_stream, None) as in_doc:
                            # Copy all pages and append to output document
                            copied_pages = PageList.copy(out_doc, in_doc.pages, page_copy_options)
                            out_pages.extend(copied_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)