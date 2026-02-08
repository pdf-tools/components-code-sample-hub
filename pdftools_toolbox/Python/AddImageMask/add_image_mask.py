"""
File: add_image_mask.py
Usage: python ./add_image_mask.py <input_path> <image_mask_path> <output_path>
                Example: in.pdf in.tif out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add image mask to PDF

"""

import io
from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList
from pdftools_toolbox.geometry.real import Rectangle
from pdftools_toolbox.pdf.content import ColorSpace, ContentGenerator, IccBasedColorSpace, ImageMask, Paint, ProcessColorSpaceType
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


def add_image_mask(document: Document, page: Page, image_path: str, x: float, y: float):
    # Create content generator
    with ContentGenerator(page.content, False) as generator:
        # Load image from input path
        with io.FileIO(image_path, 'rb') as in_image_stream:
            # Create image mask object
            image_mask = ImageMask.create(document, in_image_stream)
            resolution = 150
            # Calculate rectangle for image
            size = image_mask.size
            rect = Rectangle(
                left=x,
                bottom=y,
                right=x + size.width * 72 / resolution,
                top=y + size.height * 72 / resolution
            )
            # Paint image mask into the specified rectangle
            generator.paint_image_mask(image_mask, rect, paint)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Place a rectangular image mask at a specified location of a page. The image mask is a stencil mask to fill or mask out the image per pixel.", usage="python ./add_image_mask.py <input_path> <image_mask_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("image_mask_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    image_mask_path = args.image_mask_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, 'wb+') as output_stream:
                    with Document.create(output_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Get the device color space
                        color_space = ColorSpace.create_process_color_space(out_doc, ProcessColorSpaceType.RGB)
                        # Create paint object
                        paint = Paint.create(out_doc, color_space, [1.0, 0.0, 0.0], None)
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        # Copy first page, add image mask, and append to output document
                        out_page = Page.copy(out_doc, in_doc.pages[0], copy_options)
                        add_image_mask(out_doc, out_page, image_mask_path, 250, 150)
                        out_doc.pages.append(out_page)
                        # Copy remaining pages and append to output document
                        in_page_range = in_doc.pages[1:]
                        copied_pages = PageList.copy(out_doc, in_page_range, copy_options)
                        out_doc.pages.extend(copied_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)