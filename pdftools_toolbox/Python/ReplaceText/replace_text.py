"""
File: replace_text.py
Usage: python ./replace_text.py <input_path> <output_path>
                Example: in.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Replace text fragment in PDF

"""

from pdftools_toolbox.geometry.real import AffineTransform
from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page
from pdftools_toolbox.pdf.content import Content, ContentElement, ContentExtractor, ContentGenerator, GroupElement, IccBasedColorSpace, Text, TextElement, TextFragment, TextGenerator
from pdftools_toolbox.pdf.navigation import ViewerSettings
from pdftools_toolbox.pdf.content.font import Font

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


def copy_content_and_remove_text(in_content: Content, out_content: Content, out_doc: Document, search_text: str):
    """Process content to find and remove a specific text fragment."""
    global overall_transform, fragment
    # Use a content extractor and a content generator to copy content
    extractor = ContentExtractor(in_content)
    with ContentGenerator(out_content, False) as generator:
        # Iterate over all content elements
        for in_element in extractor:
            # Special treatment for group elements
            if isinstance(in_element, GroupElement):
                out_group_element = GroupElement.copy_without_content(out_doc, in_element)
                out_element = out_group_element
                # Save transform for later restore
                current_transform = overall_transform
                # Update the transform
                copy_content_and_remove_text(in_element.group.content, out_group_element.group.content, out_doc, search_text)
                # Restore the transform
                overall_transform = current_transform
            else:
                # Copy the content element to the output document
                out_element = ContentElement.copy(out_doc, in_element)
                if isinstance(out_element, TextElement) and fragment is None:
                    # Special treatment for text element
                    text = out_element.text
                    # Find text fragment with string to replace
                    for index_fragment in range(len(text) - 1, -1, -1):
                        # In this sample, the fragment text must match in its entirety (Text might contain null characters)
                        if text[index_fragment].text.replace("\x00", "") == search_text:
                            # Keep the found fragment for later use
                            fragment = text[index_fragment]
                            # Update the transform
                            overall_transform.concatenate(fragment.transform)
                            # Remove the fragment from the text element
                            text.remove(index_fragment)
                    # Prevent appending an empty text element
                    if len(text) == 0:
                        out_element = None
            # Append the finished output element to the content generator
            if out_element:
                generator.append_content_element(out_element)


def add_text(out_doc: Document, page, replacement_text):
    """Add the replacement text at the location of the removed fragment."""
    # Create a new text object
    text = Text.create(out_doc)
    # Heuristic to map the extracted font base name to a font name and font family
    font_parts = fragment.font.base_font.split("-")
    font_family = font_parts[0]
    font_style = font_parts[1] if len(font_parts) > 1 else None
    # Create a new font object
    font = Font.create_from_system(out_doc, font_family, font_style, True)
    # Create a text generator and set the original fragment's properties
    with TextGenerator(text, font, fragment.font_size, None) as text_gen:
        text_gen.character_spacing = fragment.character_spacing
        text_gen.word_spacing = fragment.word_spacing
        text_gen.horizontal_scaling = fragment.horizontal_scaling
        text_gen.rise = fragment.rise
        text_gen.show(replacement_text)
    # Create a content generator
    with ContentGenerator(page.content, False) as content_gen:
        # Apply the computed transform
        content_gen.transform(overall_transform)
        # Paint the new text
        content_gen.paint_text(text)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="For a given text, search through all text fragments on all pages and replace the first matching fragment found. Links, annotations, form fields, outlines, and logical structure are discarded.", usage="python ./replace_text.py <input_path> <output_path>")

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
        overall_transform = AffineTransform.get_identity()
        fragment = None
        search_string = "Muster Company AG"
        replacement_string = "Replacement String"
        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Process each page
                        for in_page in in_doc.pages:
                            # Create empty output page
                            out_page = Page.create(out_doc, in_page.size)
                            # Copy page content from input to output and search for string
                            copy_content_and_remove_text(in_page.content, out_page.content, out_doc, search_string)
                            # If the text was found and deleted, add the replacement text
                            if fragment:
                                add_text(out_doc, out_page, replacement_string)
                            # Add the new page to the output document's page list
                            out_doc.pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)