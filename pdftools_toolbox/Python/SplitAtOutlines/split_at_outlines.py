"""
File: split_at_outlines.py
Usage: python ./split_at_outlines.py <input_path> <output_dir> [<level>]
                Example: in1.pdf . 2

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Split at outlines

"""

import os
from pdftools_toolbox.pdf import Document, FileReference, Metadata, PageCopyOptions, PageList
from pdftools_toolbox.pdf.content import IccBasedColorSpace
from pdftools_toolbox.pdf.navigation import OutlineCopyOptions, OutlineItem, OutlineItemList, ViewerSettings

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


def get_outlines(current_outlines: OutlineItemList, level: int, current_level: int = 1) -> list:
    """Recursively collect outline items at the specified level."""
    matching_outlines = []
    # If the current level matches the specified level add the given outline items
    if level == current_level:
        matching_outlines.extend(current_outlines)
    else:
        # Otherwise recurse to next level
        for outline in current_outlines:
            matching_outlines.extend(get_outlines(outline.children, level, current_level + 1))
    return matching_outlines


def get_parts(in_pages: PageList, outlines: list) -> list:
    """Collect page ranges corresponding to the outlines."""
    # Construct parts according to the given outlines
    parts = []
    # No parts to be constructed if no outlines are found
    if not outlines or len(outlines) == 0:
        return parts
    # Keep both the last and the next outline items while iterating
    last_outline = None
    last_page_index = 0
    for page_index, page in enumerate(in_pages):
        # Check if this page is the destination's page of the next outline
        if outlines and page == outlines[0].destination.target.page:
            # Create a new part if the last outline item is defined and if the page index has increased at least by 1
            if last_outline and page_index - last_page_index > 0:
                parts.append((in_pages[last_page_index:page_index], last_outline))
            last_outline = outlines.pop(0)
            # Keep the current page index as the last page index used
            last_page_index = page_index
    # Add the last part which is assumed to contain all the pages until the end of the document
    if last_outline:
        parts.append((in_pages[last_page_index:], last_outline))
    return parts



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="\n    Split a PDF document into several parts defined by the document's outlines at a given level.\n    The outlines' titles define the output file names.\n  ", usage="python ./split_at_outlines.py <input_path> <output_dir> [<level>]")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_dir", type=str)
    parser.add_argument("level", type=str, nargs="?", default=None)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_dir = args.output_dir
    level = args.level if args.level is not None else '1'

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Get the level from the arguments, default to 1 if not provided
        level = int(level)
        if level < 1:
            raise ValueError("The level must be greater than zero.")
        # Ensure the output directory exists
        os.makedirs(output_dir, exist_ok=True)
        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Collect all outline items at the given level
                outlines = get_outlines(in_doc.outline, level)
                # Collect all page ranges corresponding to the given outline items
                parts = get_parts(in_doc.pages, outlines)
                # Iterate over all collected parts
                for page_list, outline_item in parts:
                    # Turn the outline item's title into a valid file name
                    file_name = "".join([c if c.isalnum() or c in "._-" else "_" for c in outline_item.title.replace("\x00", "")]) + ".pdf"
                    file_path = os.path.join(output_dir, file_name)
                    # Create output document
                    with io.FileIO(file_path, "wb+") as out_stream:
                        with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                            # Copy document-wide data
                            copy_document_data(in_doc, out_doc)
                            # Define page copy options
                            page_copy_options = PageCopyOptions()
                            page_copy_options.copy_outline_items = False
                            # Copy the pages and add to the output document's page list
                            out_pages = PageList.copy(out_doc, page_list, page_copy_options)
                            out_doc.pages.extend(out_pages)
                            # Copy child outline items
                            outline_copy_options = OutlineCopyOptions()
                            for child in outline_item.children:
                                out_doc.outline.append(OutlineItem.copy(out_doc, child, outline_copy_options))

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)