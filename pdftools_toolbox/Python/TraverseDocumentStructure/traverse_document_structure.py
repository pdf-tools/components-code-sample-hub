"""
File: traverse_document_structure.py
Usage: python ./traverse_document_structure.py <input_path>
                Example: in.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Traverse the document structure

"""

from pdftools_toolbox.pdf import Document
from pdftools_toolbox.pdf.structure import Tree, Node

import argparse, io

def print_node_recursive(node: Node, level: int):
    print(" " * level, "Tag: ", node.tag)
    print(" " * level, "Alternative text: ", node.alternate_text)
    print(" " * level, "Actual text: ", node.actual_text)
    print(" " * level, "Abbreviation: ", node.abbreviation)
    print(" " * level, "Language: ", node.language)
    for child in node.children:
        print_node_recursive(child, level + 1)    


def print_document_structure(in_doc: Document):
    tree = Tree(in_doc)
    for node in tree.children:
        print_node_recursive(node, 0)    



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Traverse the logical structure of a\n        tagged PDF file.", usage="python ./traverse_document_structure.py <input_path>")

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
                print_document_structure(in_doc)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)