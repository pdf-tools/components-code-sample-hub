"""
File: create_tagged_pdf.py
Usage: python ./create_tagged_pdf.py <image_path> <out_path>
                Example: PdfToolsLogo.png out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Create tagged PDF

"""

import argparse
import io
import os
from pdftools_toolbox.geometry.real import Point, Rectangle, Size
from pdftools_toolbox.pdf import Document, Page
from pdftools_toolbox.pdf.conformance import Conformance
from pdftools_toolbox.pdf.content import (
    ContentGenerator,
    Font,
    Image,
    Text,
    TextGenerator,
)
from pdftools_toolbox.pdf.structure import Node, Tree

import argparse, io

def to_points(value: float, unit: str = "cm") -> float:
    """
    Convert measurement from inches or centimeters to points.
    Args:
        value: The measurement value
        unit: Unit of measurement ("in" for inches, "cm" for centimeters)
    Returns:
        Value converted to points (1 inch = 72 points, 1 cm ≈ 28.35 points)
    """
    if unit == "in":
        return value * 72.0  # 1 inch = 72 points
    elif unit == "cm":
        return value * 28.346456693  # 1 cm = 28.346456693 points (72/2.54)
    else:
        raise ValueError(
            f"Unsupported unit '{unit}'. Use 'in' for inches or 'cm' for centimeters."
        )


# Look & Feel
MARGIN = to_points(2.5, "cm")
PADDING = to_points(1, "cm")
ARIAL_AND_FALLBACKS = [
    "Arial",  # Common on Windows, available on most systems
    "Liberation Sans",  # Common on Linux
    "DejaVu Sans",  # Common on Linux
    "Helvetica",  # Common on macOS
    "sans-serif",  # Generic fallback
]


def create_font_with_fallbacks(
    document: Document, font_and_fallbacks: list[str]
) -> Font:
    """
    Try to create a font using common font names that are likely to be available
    on Windows, Linux, and Mac systems. Raises an exception if no font can be created.
    """
    for font_name in font_and_fallbacks:
        try:
            font = Font.create_from_system(document, font_name, "", True)
            if font is not None:
                return font
        except Exception:
            # Try next font
            continue
    # If we get here, no font worked
    raise RuntimeError(
        f"Unable to create font. Tried the following fonts: {', '.join(font_and_fallbacks)}. "
        "Please ensure you have at least one of these fonts installed on your system."
    )


def create_and_tag_text(
    out_doc: Document,
    out_page: Page,
    gen: ContentGenerator,
    section_node: Node,
    font: Font,
    top_y: float,
    tag_name: str,
    text_content: str,
    font_size: float,
) -> float:
    """
    Create and tag a text element (header, paragraph, etc.).
    Args:
        top_y: Y coordinate for the top of this element
        tag_name: PDF structure tag name (e.g., "H1", "P")
        text_content: The text content to display
        font_size: Font size in points
    Returns:
        Bottom Y coordinate of this element
    """
    text_node = Node(tag_name, out_doc, out_page)
    text_node.actual_text = text_content
    gen.tag_as(text_node)
    text = Text.create(out_doc)
    section_node.children.append(text_node)
    text_node.language = "en"
    # Calculate text baseline position
    baseline_y = top_y - font_size * font.ascent
    with TextGenerator(text, font, font_size, None) as text_gen:
        position = Point(MARGIN, baseline_y)
        text_gen.move_to(position)
        text_gen.show_line(text_node.actual_text)
    gen.paint_text(text)
    gen.stop_tagging()
    # Return bottom coordinate (baseline - descent)
    return text_node, baseline_y - font_size * font.descent


def create_and_tag_image(
    out_doc: Document,
    out_page: Page,
    gen: ContentGenerator,
    input_image_path: str,
    top_y: float,
    parent: Node
) -> float:
    """
    Create and tag an image element.
    Args:
        top_y: Y coordinate for the top of this element
    Returns:
        Bottom Y coordinate of this element
    """
    figure_node = Node("Figure", out_doc, out_page)
    figure_node.alternate_text = "PdfTools AG Logo"
    figure_node.language = "en"
    figure_node.set_string_attribute("O", "Layout")
    gen.tag_as(figure_node)
    try:
        with io.FileIO(input_image_path, "rb") as in_image:
            image = Image.create(out_doc, in_image)
    except Exception as e:
        raise RuntimeError(
            f"Failed to create image from file '{input_image_path}': {str(e)}. "
            "Please ensure the file is a valid image format (PNG, JPEG, etc.)."
        )
    x = MARGIN
    width = to_points(2.0, "cm")
    height = width * image.size.height / image.size.width  # preserve aspect ratio
    rect = Rectangle(
        left=x,
        bottom=top_y - height,  # Rectangle coordinates: bottom is lower than top
        right=x + width,
        top=top_y,
    )
    gen.paint_image(image, rect)
    gen.stop_tagging()
    figure_node.bounding_box = rect
    parent.children.append(figure_node)
    # Return bottom coordinate
    return top_y - height


def create_and_tag_content(
    out_doc: Document,
    out_page: Page,
    input_image_path: str,
    font: Font,
):
    with ContentGenerator(out_page.content, False) as gen:
        struct_tree = Tree(out_doc)
        doc_node = struct_tree.document_node
        section_node = Node("Sect", out_doc, out_page)
        doc_node.children.append(section_node)
        # Start from the top of the page with margin
        current_y = out_page.size.height - MARGIN
        # Create header
        node, current_y = create_and_tag_text(
            out_doc,
            out_page,
            gen,
            section_node,
            font,
            current_y,
            "H1",
            "This is a properly tagged heading",
            24.0,
        )
        # Add padding and create paragraph
        current_y -= PADDING
        node, current_y = create_and_tag_text(
            out_doc,
            out_page,
            gen,
            section_node,
            font,
            current_y,
            "P",
            "This is a properly tagged paragraph. Both heading and paragraph belong to a section.",
            12.0,
        )
        # Add padding and create image
        current_y -= PADDING
        create_and_tag_image(out_doc, out_page, gen, input_image_path, current_y, node)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Create a new PDF document, add content and apply logical structure (tags) during content creation.", usage="python ./create_tagged_pdf.py <image_path> <out_path>")

    # Add arguments
    parser.add_argument("image_path", type=str)
    parser.add_argument("out_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_image_path = args.image_path
    output_file_path = args.out_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Check if image file exists
        if not os.path.isfile(input_image_path):
            raise FileNotFoundError(
                f"Image file not found: '{input_image_path}'. "
                "Please ensure the image file exists and the path is correct."
            )
        # Create a PDF document
        with io.FileIO(output_file_path, "wb+") as out_stream:
            with Document.create(out_stream, Conformance.PDF17, None) as out_doc:
                # Create a font
                font = create_font_with_fallbacks(out_doc, ARIAL_AND_FALLBACKS)
                out_doc.language = "en"
                out_doc.set_pdf_ua_conformant()
                out_doc.metadata.title = "TaggedPDF"
                out_doc.viewer_settings.display_document_title = True
                # Create a page
                page_size = Size(to_points(21, "cm"), to_points(29.7, "cm"))  # DIN A4
                out_page = Page.create(out_doc, page_size)
                create_and_tag_content(out_doc, out_page, input_image_path, font)
                out_doc.pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)