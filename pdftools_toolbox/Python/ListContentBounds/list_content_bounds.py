"""
File: list_content_bounds.py
Usage: python ./list_content_bounds.py <input_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

List bounds of page content

"""

from pdftools_toolbox.geometry.real import Point, Rectangle
from pdftools_toolbox.pdf import Document
from pdftools_toolbox.pdf.content import ContentExtractor

import argparse, io

def enlarge(content_box: Rectangle, point: Point):
    """
    Enlarge the bounding box to include the given point.
    """
    content_box.left = min(content_box.left, point.x)
    content_box.right = max(content_box.right, point.x)
    content_box.bottom = min(content_box.bottom, point.y)
    content_box.top = max(content_box.top, point.y)


def list_content_bounds(input_doc: Document):
    """
    Process the input PDF file to list page size and bounding boxes.
    """
    # Iterate over all pages
    for page_number, page in enumerate(input_doc.pages, start=1):
        print(f"Page {page_number}")
        # Print page size
        size = page.size
        print("  Size:")
        print(f"    Width: {size.width}")
        print(f"    Height: {size.height}")
        # Compute rectangular bounding box of all content on page
        content_box = Rectangle(
            left=float("inf"),
            bottom=float("inf"),
            right=float("-inf"),
            top=float("-inf"),
        )
        # Extract content and compute bounding box
        extractor = ContentExtractor(page.content)
        for element in extractor:
            # Enlarge the content box for each content element
            tr = element.transform
            box = element.bounding_box
            # The location on the page is given by the transformed points
            enlarge(content_box, tr.transform_point(Point(x=box.left, y=box.bottom)))
            enlarge(content_box, tr.transform_point(Point(x=box.right, y=box.bottom)))
            enlarge(content_box, tr.transform_point(Point(x=box.right, y=box.top)))
            enlarge(content_box, tr.transform_point(Point(x=box.left, y=box.top)))
        print("  Content bounding box:")
        print(f"    Left: {content_box.left}")
        print(f"    Bottom: {content_box.bottom}")
        print(f"    Right: {content_box.right}")
        print(f"    Top: {content_box.top}")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="For each page, list the page size and the rectangular bounding box of all content on the page in PDF points (1/72 inch).", usage="python ./list_content_bounds.py <input_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Process the PDF
                list_content_bounds(in_doc)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)