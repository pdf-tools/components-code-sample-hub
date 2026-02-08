"""
File: tag_pdf.py
Usage: python ./tag_pdf.py <in_path> <out_path>
                Example: in.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Tag existing PDF content

"""

import io
import os
import math
from pdftools_toolbox.geometry.real import Quadrilateral, Size, Rectangle
from pdftools_toolbox.pdf import Document, Page
from pdftools_toolbox.pdf.content import (
    ContentElement,
    ContentExtractor,
    ContentGenerator,
    GroupElement,
    ImageElement,
    TextElement,
)
from pdftools_toolbox.pdf.structure import Node, Tree
from pdftools_toolbox.pdf.navigation import ViewerSettings
from pdftools_toolbox.pdf.content import IccBasedColorSpace
from pdftools_toolbox.pdf import Metadata, FileReference

import argparse, io

def copy_document_data(in_doc: Document, out_doc: Document):
    if in_doc.output_intent is not None:
        out_doc.output_intent = IccBasedColorSpace.copy(out_doc, in_doc.output_intent)
    out_doc.metadata = Metadata.copy(out_doc, in_doc.metadata)
    out_doc.viewer_settings = ViewerSettings.copy(out_doc, in_doc.viewer_settings)
    out_associated_files = out_doc.associated_files
    for in_file_ref in in_doc.associated_files:
        out_associated_files.append(FileReference.copy(out_doc, in_file_ref))
    out_embedded_files = out_doc.plain_embedded_files
    for in_file_ref in in_doc.plain_embedded_files:
        out_embedded_files.append(FileReference.copy(out_doc, in_file_ref))


def copy_and_tag_text_element(text_element: TextElement, section_node: Node, generator: ContentGenerator,
                              out_page: Page, out_doc: Document, tag: str):
    text_node = Node(tag, out_doc, out_page)
    text_node.actual_text = text_element.text[0].text
    text_node.language = "en"
    section_node.children.append(text_node)
    generator.tag_as(text_node)
    generator.append_content_element(text_element)
    generator.stop_tagging()
    return text_node


def copy_and_tag_image_element(image_element: ImageElement, parent: Node, generator: ContentGenerator,
                               out_page: Page, out_doc: Document, alternate_text: str):
    image_node = Node("Figure", out_doc, out_page)
    image_node.alternate_text = alternate_text
    image_node.language = "en"
    image_node.set_string_attribute("O", "Layout")
    bbox = image_element.transform.transform_rectangle(image_element.bounding_box)
    rectangle = Rectangle()
    rectangle.left = bbox.bottom_left.x
    rectangle.bottom = bbox.bottom_left.y
    rectangle.right = bbox.top_right.x
    rectangle.top = bbox.top_right.y
    image_node.bounding_box = rectangle
    parent.children.append(image_node)
    generator.tag_as(image_node)
    generator.append_content_element(image_element)
    generator.stop_tagging()


def copy_and_tag_content(in_page: Page, out_page: Page, out_doc: Document):
    struct_tree = Tree(out_doc)
    document_node = struct_tree.document_node
    section_node = Node("Sect", out_doc, out_page)
    document_node.children.append(section_node)
    extractor = ContentExtractor(in_page.content)
    p = Node("P", out_doc, None)
    with ContentGenerator(out_page.content, False) as generator:
        for in_element in extractor:
            if isinstance(in_element, GroupElement):
                out_group = GroupElement.copy_without_content(out_doc, in_element)
                copy_and_tag_content(in_page, out_page, out_doc)
            else:
                out_element = ContentElement.copy(out_doc, in_element)
                if isinstance(out_element, TextElement):
                    text = out_element.text[0].text
                    if text == "This is a properly tagged heading":
                        copy_and_tag_text_element(out_element, section_node, generator, out_page, out_doc, "H1")
                    elif text == "This is a properly tagged paragraph. Both heading and paragraph belong to a section.":
                        p = copy_and_tag_text_element(out_element, section_node, generator, out_page, out_doc, "P")
                    else:
                        raise RuntimeError("Unexpected content element found.")
                elif isinstance(out_element, ImageElement):
                    bbox: Quadrilateral = out_element.transform.transform_rectangle(out_element.bounding_box)
                    if (
                        abs(bbox.bottom_left.x - 70.86) < 0.5
                        and abs(bbox.bottom_left.y - 632.65) < 0.5
                        and abs(bbox.top_right.x - 127.559) < 0.5
                        and abs(bbox.top_right.y - 689.34) < 0.5
                    ):
                        copy_and_tag_image_element(out_element, p, generator, out_page, out_doc, "PdfTools AG Logo")
                    else:
                        raise RuntimeError("Unexpected content element found.")
                else:
                    raise RuntimeError("Unexpected content element found.")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Copy content from an existing PDF, then apply logical structure (tags) to selected elements.", usage="python ./tag_pdf.py <in_path> <out_path>")

    # Add arguments
    parser.add_argument("in_path", type=str)
    parser.add_argument("out_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.in_path
    output_file_path = args.out_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as in_doc:
                with io.FileIO(output_file_path, 'wb+') as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Create empty output page
                        in_page = in_doc.pages[0]
                        out_page = Page.create(out_doc, in_page.size)
                        out_doc.language = "en"
                        out_doc.set_pdf_ua_conformant()
                        out_doc.metadata.title = "TaggedPDF"
                        out_doc.viewer_settings.display_document_title = True
                        # We create an output page and copy the content elements from the input page to the output page.
                        # While copying, we also check if the current element is the one we want to tag.
                        # If it is, we tag it and update the logical structure accordingly.
                        # You can easily adapt this sample to fit similar scenarios.
                        copy_and_tag_content(in_page, out_page, out_doc)
                        out_doc.pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)