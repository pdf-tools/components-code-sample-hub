"""
File: add_line_numbers.py
Usage: python ./add_line_numbers.py <input_path> <output_path>
                Example: in.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add line numbers to PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, PageCopyOptions, PageList
from pdftools_toolbox.geometry.real import Point
from pdftools_toolbox.pdf.content import ContentExtractor, ContentGenerator, Font, IccBasedColorSpace, Text, TextElement, TextGenerator, UngroupingSelection
from pdftools_toolbox.pdf.navigation import ViewerSettings

import argparse, io

def copy_document_data(in_doc: Document, out_doc: Document):
    # Copy document-wide data
    # Output intent
    if in_doc.output_intent is not None:
        in_doc.output_intent = IccBasedColorSpace.copy(out_doc, in_doc.output_intent)
    # Metadata
    out_doc.metadata = Metadata.copy(out_doc, in_doc.metadata)
    # Viewer settings
    out_doc.viewer_settings = ViewerSettings.copy(out_doc, in_doc.viewer_settings)
    # Associated files (for PDF/A-3 and PDF 2.0 only)
    outAssociatedFiles = out_doc.associated_files
    for in_file_ref in in_doc.associated_files:
        outAssociatedFiles.append(FileReference.copy(out_doc, in_file_ref))
    # Plain embedded files
    out_embedded_files = out_doc.plain_embedded_files
    for in_file_ref in in_doc.plain_embedded_files:
        out_embedded_files.append(FileReference.copy(out_doc, in_file_ref))


class TolerantSortedSet:
    def add(self, value: float):
        for existing in self.data:
            if abs(existing - value) < self.tolerance:
                return  # Do not add duplicate-like value
        self.data.append(value)
        self.data.sort(reverse=self.sort_reverse)
    def iterator(self):
        return iter(self.data)
    def display(self):
        return str(self.data)


def create_tolerant_sorted_set(tolerance: float, sort_reverse: bool):
    tolerant_sorted_set = TolerantSortedSet()
    tolerant_sorted_set.tolerance = tolerance
    tolerant_sorted_set.sort_reverse = sort_reverse
    tolerant_sorted_set.data = []
    return tolerant_sorted_set


def add_line_numbers(out_doc: Document, line_number_font: Font, pair: tuple):
    global line_number
    # Add line numbers to all text found in the input page to the output page
    # The input and output page
    in_page, out_page = pair
    # Extract all text fragments
    extractor = ContentExtractor(in_page.content)
    extractor.ungrouping = UngroupingSelection.ALL
    # The left-most horizontal position of all text fragments
    left_x = in_page.size.width
    # A comparison for doubles that considers distances smaller than the font size as equal
    def comparison(a, b):
        d = b - a
        if abs(d) < font_size:
            return 0
        return (d > 0) - (d < 0)    # return 1 if d > 0, -1 if d < 0, 0 otherwise
    # A sorted set to hold the vertical positions of all text fragments
    # Keep the data sorted in reverse order as the coordinates are reverse in a PDF
    line_y_positions = create_tolerant_sorted_set(tolerance=font_size, sort_reverse=True)
    # Iterate over all content elements of the input page
    for element in extractor:
        # Process only text elements
        if isinstance(element, TextElement):
            # Iterate over all text fragments
            for fragment in element.text:
                # Get the fragment's baseline starting point
                point = fragment.transform.transform_point(
                    Point(fragment.bounding_box.left, 0)
                )
                # Update the left-most position
                left_x = min(left_x, point.x)
                # Add the vertical position
                line_y_positions.add(point.y)
    # If at least one text fragment was found, add line numbers
    if line_y_positions:
        # Create a text object and use a text generator
        text = Text.create(out_doc)
        with TextGenerator(text, line_number_font, font_size, None) as text_generator:
            # Iterate over all vertical positions found in the input
            for y in line_y_positions.iterator():
                # The line number string
                line_number += 1
                line_number_string = str(line_number)
                # The width of the line number string when shown on the page
                width = text_generator.get_width(line_number_string)
                # Position line numbers right-aligned
                # with a given distance to the right-most horizontal position
                # and at the vertical position of the current text fragment
                text_generator.move_to(Point(left_x - width - distance, y))
                # Show the line number string
                text_generator.show(line_number_string)
        # Use a content generator to paint the text onto the page
        with ContentGenerator(out_page.content, False) as content_generator:
            content_generator.paint_text(text)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a line number in front of each line that contains text.", usage="python ./add_line_numbers.py <input_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Define global variables
        distance = 10
        font_size = 8.0
        line_number = 0
        # Open input document
        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, 'wb+') as output_stream:
                    with Document.create(output_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Create a font for the line numbers
                        lineNumberFont = Font.create_from_system(out_doc, "Arial", None, True)
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        # Copy all pages from input to output document
                        in_pages = in_doc.pages
                        out_pages = PageList.copy(out_doc, in_pages, copy_options)
                        # Iterate over all input-output page pairs
                        pages = zip(in_pages, out_pages)
                        for pair in pages:
                            add_line_numbers(out_doc, lineNumberFont, pair)
                        out_doc.pages.extend(out_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)