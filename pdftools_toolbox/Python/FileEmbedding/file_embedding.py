"""
File: file_embedding.py
Usage: python ./file_embedding.py <input_path> <file_to_embed> <output_path> [<page>]
                Example: in.pdf fileToEmbed.xyz out.pdf [page]

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Embed files into a PDF

"""

import os
from datetime import datetime
from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList
from pdftools_toolbox.geometry.real import Point
from pdftools_toolbox.pdf.annotations import FileAttachment
from pdftools_toolbox.pdf.content import ColorSpace, IccBasedColorSpace, Paint, ProcessColorSpaceType, Transparency
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


def embed_file(output_doc: Document, file_to_embed: str, page_number: int | None):
    # Create file stream to read the file to embed
    with open(file_to_embed, "rb") as file_stream:
        # Create a file type depending on the file ending (e.g. "application/pdf")
        file_to_embed_name = os.path.basename(file_to_embed)
        file_type = "application/" + file_to_embed_name.split(".")[-1]
        # Get the modified date from the file
        last_modified = datetime.fromtimestamp(os.path.getmtime(file_to_embed))
        # Create a new FileReference
        file_ref = FileReference.create(output_doc, file_stream, file_to_embed_name, file_type, "", last_modified)
        # If a page is set, add a FileAttachment annotation to that page
        # otherwise, attach the file to the document
        if page_number is not None and page_number > 0 and page_number <= len(output_doc.pages):
            # Get the page to create the annotation on
            page = output_doc.pages[page_number - 1]
            # Get the color space
            color_space = ColorSpace.create_process_color_space(output_doc, ProcessColorSpaceType.RGB)
            # Choose the RGB color value
            color = [1.0, 0.0, 0.0]  # Red color
            transparency = Transparency(1)
            # Create paint object
            paint = Paint.create(output_doc, color_space, color, transparency)
            # Put the annotation in the center of the page
            point = Point(x = page.size.width/2, y = page.size.height/2)
            # Create a FileReference annotation and attach it to a page so the FireReference is visible on that page
            annotation = FileAttachment.create(output_doc, point, file_ref, paint)
            # Add the annotation to the page
            page.annotations.append(annotation)
        else:
            # Attach the file to the document
            output_doc.plain_embedded_files.append(file_ref)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Embed files into a PDF and attach them to the document or attach a page.", usage="python ./file_embedding.py <input_path> <file_to_embed> <output_path> [<page>]")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("file_to_embed", type=str)
    parser.add_argument("output_path", type=str)
    parser.add_argument("page", type=str, nargs="?", default=None)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    file_to_embed = args.file_to_embed
    output_file_path = args.output_path
    page_number = int(args.page) if args.page and args.page.isdigit() else None

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        # Copy all pages and append to output document
                        copied_pages = PageList.copy(out_doc, in_doc.pages, copy_options)
                        out_doc.pages.extend(copied_pages)
                        embed_file(out_doc, file_to_embed, page_number)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)