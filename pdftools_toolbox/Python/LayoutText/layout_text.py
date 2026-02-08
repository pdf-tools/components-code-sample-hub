"""
File: layout_text.py
Usage: python ./layout_text.py <text_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Layout text on PDF page

"""

from pdftools_toolbox.geometry.real import Size, Point
from pdftools_toolbox.pdf import Document, Page
from pdftools_toolbox.pdf.content import ContentGenerator, Font, Text, TextGenerator

import argparse, io

def layout_text(output_doc: Document, out_page: Page, text_path: str, font: Font, font_size: float):
    """
    Layout and justify text on the PDF page.
    """
    # Create content generator
    with ContentGenerator(out_page.content, False) as generator:
        # Create text object
        text = Text.create(output_doc)
        # Create text generator
        with TextGenerator(text, font, font_size, None) as text_generator:
            # Calculate starting position
            position = Point(x=BORDER, y=out_page.size.height - BORDER)
            # Move to position
            text_generator.move_to(position)
            with open(text_path, "r", encoding="utf-8") as file:
                lines = file.readlines()
            # Loop through all lines of the textinput
            for line in lines:
                # Split string in substrings
                substrings = line.split(" ")
                current_line = ""
                max_width = out_page.size.width - BORDER * 2
                word_count = 0
                # Loop through all words of input strings
                for word in substrings:
                    # Concatenate substrings to line
                    temp_line = f"{current_line} {word}".strip()
                    # Calculate the current width of line
                    current_width = text_generator.get_width(current_line)
                    if text_generator.get_width(temp_line) > max_width:
                        # Calculate the word spacing
                        text_generator.word_spacing = (max_width - current_width) / (word_count - 1) if word_count > 1 else 0
                        text_generator.show_line(current_line)
                        text_generator.word_spacing = 0
                        current_line = word
                        word_count = 1
                    else:
                        current_line = temp_line
                        word_count += 1
                text_generator.word_spacing = 0
                # Add given stamp string
                text_generator.show_line(current_line)
        # Paint the positioned text
        generator.paint_text(text)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Create a new PDF document with one page. On this page, within a given rectangular area, add a text block with a full justification layout.", usage="python ./layout_text.py <text_path> <output_path>")

    # Add arguments
    parser.add_argument("text_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_text_path = args.text_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Define global variables
        BORDER = 50
        PAGE_SIZE = Size(width=595, height=842)  # A4 page size in points
        # Create output document
        with io.FileIO(output_file_path, "wb+") as out_stream:
            with Document.create(out_stream, None, None) as out_doc:
                font = Font.create_from_system(out_doc, "Arial", "Italic", True)
                # Create page
                out_page = Page.create(out_doc, PAGE_SIZE)
                # Add text as justified text
                layout_text(out_doc, out_page, input_text_path, font, font_size=20)
                # Add page to document
                out_doc.pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)