"""
File: remove_glyphs.py
Usage: python ./remove_glyphs.py <input_path> <output_path>
                Example: in.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Remove glyphs

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page
from pdftools_toolbox.pdf.content import Content, ContentElement, ContentExtractor, ContentGenerator, GroupElement, IccBasedColorSpace, TextElement
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


def copy_content_and_remove_glyphs(in_content: Content, out_content: Content, out_doc: Document):
    """Process content to remove the first two glyphs from text fragments."""
    # Use a content extractor and a content generator to copy content
    extractor = ContentExtractor(in_content)
    with ContentGenerator(out_content, False) as generator:
        # Iterate over all content elements
        for in_element in extractor:
            # Special treatment for group elements
            if isinstance(in_element, GroupElement):
                # Create empty output group element
                out_group_element = GroupElement.copy_without_content(out_doc, in_element)
                out_element = out_group_element
                copy_content_and_remove_glyphs(in_element.group.content, out_group_element.group.content, out_doc)
            else:
                # Copy the content element to the output document
                out_element = ContentElement.copy(out_doc, in_element)
                if isinstance(out_element, TextElement):
                    # Special treatment for text element
                    text = out_element.text
                    # Remove the first two glyphs from each text fragment
                    for fragment in text:
                        # Ensure that the fragment has more than two glyphs
                        if len(fragment) > 2:
                            # Call RemoveAt twice
                            fragment.remove(0)
                            fragment.remove(0)
            # Append the finished output element to the content generator
            generator.append_content_element(out_element)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Remove the first two glyphs from every text fragment.", usage="python ./remove_glyphs.py <input_path> <output_path>")

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

        # Open input and create output documents
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
                            # Copy page content from input to output and remove glyphs
                            copy_content_and_remove_glyphs(in_page.content, out_page.content, out_doc)
                            # Add the new page to the output document's page list
                            out_doc.pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)