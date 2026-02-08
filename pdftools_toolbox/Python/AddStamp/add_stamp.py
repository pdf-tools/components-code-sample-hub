"""
File: add_stamp.py
Usage: python ./add_stamp.py <input_path> <stamp_string> <output_path> [<alpha>]
                Example: in.pdf APPROVED out.pdf 0.5

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add stamp to PDF

"""

import math
from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions
from pdftools_toolbox.geometry.real import AffineTransform, Point
from pdftools_toolbox.pdf.content import ColorSpace, ContentGenerator, Font, IccBasedColorSpace, Paint, ProcessColorSpaceType, Text, TextGenerator, Transparency
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


def add_stamp(output_doc: Document, out_page: Page, stamp_string: str):
    # Create content generator and text object
    with ContentGenerator(out_page.content, False) as gen:
        text = Text.create(output_doc)
        # Create text generator
        with TextGenerator(text, font, font_size, None) as text_generator:
            # Calculate point and angle of rotation
            rotation_center = Point(
                x=out_page.size.width / 2.0,
                y=out_page.size.height / 2.0
            )
            rotation_angle = math.atan2(out_page.size.height, out_page.size.width) / math.pi * 180.0
            # Rotate text input around the calculated position
            trans = AffineTransform.get_identity()
            trans.rotate(rotation_angle, rotation_center)
            gen.transform(trans)
            # Calculate position
            position = Point(
                x=(out_page.size.width - text_generator.get_width(stamp_string)) / 2.0,
                y=(out_page.size.height - font.ascent * font_size) / 2.0
            )
            # Move to position
            text_generator.move_to(position)
            # Set text paint
            text_generator.fill = paint
            # Add given stamp string
            text_generator.show_line(stamp_string)
        # Paint the positioned text
        gen.paint_text(text)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a semi-transparent stamp text onto each page of a PDF document. Optionally specify the color and the opacity of the stamp.", usage="python ./add_stamp.py <input_path> <stamp_string> <output_path> [<alpha>]")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("stamp_string", type=str)
    parser.add_argument("output_path", type=str)
    parser.add_argument("alpha", type=str, nargs="?", default=None)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    stamp_string = args.stamp_string
    output_file_path = args.output_path
    if args.alpha is not None:
        alpha = float(args.alpha)
        if alpha < 0.0 or alpha > 1.0:
            raise ValueError(f"The value must be between 0.0 and 1.0. Current value: {alpha}")
    else:
        alpha = 0.5

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Define global variables
        font_size = 50.0
        # Open input document
        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, 'wb+') as output_stream:
                    with Document.create(output_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Create font
                        font = Font.create_from_system(out_doc, "Arial", "Italic", True)
                        # Get the color space
                        color_space = ColorSpace.create_process_color_space(out_doc, ProcessColorSpaceType.RGB)
                        # Choose the RGB color value and transparency
                        color = [1.0, 0.0, 0.0]
                        transparency = Transparency(alpha)
                        # Create paint object with the chosen RGB color
                        paint = Paint.create(out_doc, color_space, color, transparency)
                        # Define copy options
                        copy_options = PageCopyOptions()
                        # Copy all pages from input document
                        for in_page in in_doc.pages:
                            # Copy page from input to output
                            out_page = Page.copy(out_doc, in_page, copy_options)
                            # Add text to page
                            add_stamp(out_doc, out_page, stamp_string)
                            # Add page to document
                            out_doc.pages.append(out_page)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)