"""
File: text_extraction.py
Usage: python ./text_extraction.py <input_path>
                Example: in.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Extract all text from PDF

"""

from pdftools_toolbox.pdf import Document
from pdftools_toolbox.pdf.content import ContentExtractor, Text, UngroupingSelection, TextElement

import argparse, io

def write_text(text: Text):
    """Reconstruct text heuristically from text fragments."""
    text_part = []
    # Write all text fragments
    # Determine heuristically if there is a space between two text fragments
    for i_fragment, curr_fragment in enumerate(text):
        if i_fragment == 0:
            text_part.append(curr_fragment.text)
        else:
            last_fragment = text[i_fragment - 1]
            # Determine if there's a space between fragments
            if (curr_fragment.character_spacing != last_fragment.character_spacing or
                curr_fragment.font_size != last_fragment.font_size or
                curr_fragment.horizontal_scaling != last_fragment.horizontal_scaling or
                curr_fragment.rise != last_fragment.rise or
                curr_fragment.word_spacing != last_fragment.word_spacing):
                text_part.append(f" {curr_fragment.text}")
            else:
                current_bot_left = curr_fragment.transform.transform_rectangle(curr_fragment.bounding_box).bottom_left
                before_bot_right = last_fragment.transform.transform_rectangle(last_fragment.bounding_box).bottom_right
                if (before_bot_right.x < current_bot_left.x - 0.7 * curr_fragment.font_size or
                    before_bot_right.y < current_bot_left.y - 0.1 * curr_fragment.font_size or
                    current_bot_left.y < before_bot_right.y - 0.1 * curr_fragment.font_size):
                    text_part.append(f" {curr_fragment.text}")
                else:
                    text_part.append(curr_fragment.text)
    print("".join(text_part))



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Write text from PDF page by page to console. Determine heuristically if two text fragments belong to the same word.", usage="python ./text_extraction.py <input_path>")

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
        with open(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                page_number = 1
                # Process each page
                for in_page in in_doc.pages:
                    print(f"==========\nPage: {page_number}\n==========")
                    extractor = ContentExtractor(in_page.content)
                    extractor.ungrouping = UngroupingSelection.ALL
                    # Iterate over all content elements and only process text elements
                    for element in extractor:
                        if isinstance(element, TextElement):
                            write_text(element.text)
                    page_number += 1

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)