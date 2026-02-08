"""
File: print_t_o_c.py
Usage: python ./print_t_o_c.py <input_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Print a table of content

"""

from pdftools_toolbox.pdf import Document
from pdftools_toolbox.pdf.navigation import OutlineItem, OutlineItemList

import argparse, io

def print_outline_item(item: OutlineItem, indentation: str, in_doc: Document):
    title = item.title
    print(f"{indentation}{title}", end="")
    dest = item.destination
    if dest and dest.target:
        page_number = in_doc.pages.index(dest.target.page) + 1
        dots_length = max(0, 78 - len(indentation) - len(title) - len(str(page_number)))
        dots = "." * dots_length
        print(f" {dots} {page_number}", end="")
    print()  # End the current line
    print_outline_items(item.children, indentation + "  ", in_doc)


def print_outline_items(items: OutlineItemList, indentation: str, in_doc: Document):
    for outline_item in items:
        print_outline_item(outline_item, indentation, in_doc)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Print a formatted table of content from the document outline.", usage="python ./print_t_o_c.py <input_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open the input document
        with open(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                print_outline_items(in_doc.outline, "", in_doc)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)