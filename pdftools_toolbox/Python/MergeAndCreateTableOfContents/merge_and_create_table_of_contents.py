"""
File: merge_and_create_table_of_contents.py
Usage: python ./merge_and_create_table_of_contents.py <input_path> [<input_path2> ...] <output_path>
                Example: in1.pdf in2.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Merge multiple PDFs and create a table of contents page

"""

import os
from pdftools_toolbox.geometry.real import Point, Rectangle
from pdftools_toolbox.pdf import Document, Page, PageCopyOptions, PageList
from pdftools_toolbox.pdf.content import ContentGenerator, Font, Text, TextGenerator
from pdftools_toolbox.pdf.navigation import InternalLink, LocationZoomDestination

import argparse, io

def add_page_number(out_doc: Document, page: Page, font: Font, page_number: int):
    """Add a page number to the bottom center of a page."""
    # Create content generator
    with ContentGenerator(page.content, False) as generator:
        # Create text object
        text = Text.create(out_doc)
        # Create a text generator with the given font, size and position
        with TextGenerator(text, font, 8, None) as text_generator:
            # Generate string to be stamped as page number
            stamp_text = f"Page {page_number}"
            # Calculate position for centering text at bottom of page
            position = Point(
                x=(page.size.width / 2) - (text_generator.get_width(stamp_text) / 2),
                y=10,
            )
            # Position the text
            text_generator.move_to(position)
            # Add page number
            text_generator.show(stamp_text)
        # Paint the positioned text
        generator.paint_text(text)


def create_table_of_contents(out_doc: Document, toc_entries: tuple, font: Font):
    """Create a table of contents (TOC) page."""
    # Create a new page with size equal to the first page copied
    page = Page.create(out_doc, toc_entries[0][1][0].size)
    # Parameters for layout computation
    border = 30
    text_width = page.size.width - 2 * border
    chapter_title_size = 24
    title_size = 12
    # The current text location
    location = Point(x=border, y=page.size.height - border - chapter_title_size)
    # The page number of the current item in the table of content
    page_number = 2
    # Create a content generator for the table of contents page
    with ContentGenerator(page.content, False) as content_generator:
        # Create a text object
        text = Text.create(out_doc)
        # Create a text generator to generate the table of contents. Initially, use the chapter title font size
        with TextGenerator(text, font, chapter_title_size, location) as text_gen:
            # Show a chapter title
            text_gen.show_line("Table of Contents")
            # Advance the vertical position
            location.y -= 1.7 * chapter_title_size
            # Select the font size for an entry in the table of contents
            text_gen.font_size = title_size
            # Iterate over all copied page ranges
            for title, page_list in toc_entries:
                # The title string for the current entry
                title_text = title
                # The page number string of the target page for this entry
                page_number_text = f"{page_number}"
                # The width of the page number string
                page_number_width = text_gen.get_width(page_number_text)
                # Compute the number of filler dots to be displayed between the entry title and the page number
                filler_dots_count = int(
                    (text_width - text_gen.get_width(title_text) - page_number_width)
                    / text_gen.get_width(".")
                )
                # Move to the current location and show the entry's title and the filler dots
                text_gen.move_to(location)
                text_gen.show(title_text + "." * filler_dots_count)
                # Show the page number
                text_gen.move_to(Point(x=page.size.width - border - page_number_width, y=location.y))
                text_gen.show(page_number_text)
                # Compute the rectangle for the link
                link_rectangle = Rectangle(
                    left=border,
                    bottom=location.y + font.descent * title_size,
                    right=border + text_width,
                    top=location.y + font.ascent * title_size,
                )
                # Create a destination to the first page of the current page range and create a link for this destination
                target_page = page_list[0]
                destination = LocationZoomDestination.create(out_doc, target_page, 0, target_page.size.height, None)
                link = InternalLink.create(out_doc, link_rectangle, destination)
                # Add the link to the table of contents page
                page.links.append(link)
                # Advance the location for the next entry
                location.y -= 1.8 * title_size
                page_number += len(page_list)
        # Paint the generated text
        content_generator.paint_text(text)
    return page



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Merge several PDF documents to one and create a table of contents page.", usage="python ./merge_and_create_table_of_contents.py <input_path> [<input_path2> ...] <output_path>")

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
                # Create embedded font in output document
                font = Font.create_from_system(out_doc, "Arial", None, True)
                # Define page copy options
                page_copy_options = PageCopyOptions()
                # List of copied pages that will be added to the table of contents
                toc_entries = []
                # A page number counter
                page_number = 2
                # Copy all input documents pages
                for input_path in input_paths:
                    # Open input document
                    with open(input_path, "rb") as in_stream:
                        with Document.open(in_stream, None) as in_doc:
                            # Copy all pages and append to output document
                            copied_pages = PageList.copy(out_doc, in_doc.pages, page_copy_options)
                            for copied_page in copied_pages:
                                add_page_number(out_doc, copied_page, font, page_number)
                                page_number += 1
                            # Create outline item
                            title = in_doc.metadata.title or os.path.splitext(os.path.basename(input_path))[0]
                            toc_entries.append((title, copied_pages))
                # Create table of contents page
                contents_page = create_table_of_contents(out_doc, toc_entries, font)
                add_page_number(out_doc, contents_page, font, 1)
                # Add pages to the output document
                out_doc.pages.append(contents_page)
                for _, pages in toc_entries:
                    out_doc.pages.extend(pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)