"""
File: overlay_color.py
Usage: python ./overlay_color.py [<options>] <input_path> <output_path>
                Example: -k 0.5 1.0 in.pdf out.pdf
                Options:
                -k (k) (a)             specifiy grayscale and alpha color
                -c (c) (m) (y) (k) (a)      specifiy CMKY and alpha color
                -r (r) (g) (b) (a)          specifiy RGB and alpha color
                color values between 0 and 1
                default: -k 0.9 1.0

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Overlay color of PDF

"""

from pdftools_toolbox.geometry.real import Rectangle
from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions
from pdftools_toolbox.pdf.content import BlendMode, ColorSpace, ContentGenerator, Transparency, Fill, IccBasedColorSpace, Paint, ProcessColorSpaceType, Path, PathGenerator
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


def parse_options(options: str) -> tuple:
    """
    Parse the options string to extract color, color type, and alpha.
    """
    # Default values
    color_type = ProcessColorSpaceType.GRAY
    color = [0.9]
    alpha = 1.0
    if options is None:
        return color, color_type, alpha
    # Split options into tokens
    tokens = options.split()
    if not tokens:
        return color, color_type, alpha
    # Parse options
    i = 0
    while i < len(tokens):
        arg = tokens[i]
        if arg.startswith("-"):
            if len(arg) != 2:
                raise ValueError(f"Invalid option: {arg}")
            flag = arg[1]
            i += 1  # Move to the next token
            if flag == "k":  # Grayscale
                if len(tokens) - i != 2:
                    raise ValueError("Invalid arguments for -k. Requires (k) (a).")
                color_type = ProcessColorSpaceType.GRAY
                color = [float(tokens[i])]
                alpha = float(tokens[i + 1])
                i += 2
            elif flag == "c":  # CMYK
                if len(tokens) - i != 5:
                    raise ValueError("Invalid arguments for -c. Requires (c) (m) (y) (k) (a).")
                color_type = ProcessColorSpaceType.CMYK
                color = [float(tokens[i]), float(tokens[i + 1]), float(tokens[i + 2]), float(tokens[i + 3])]
                alpha = float(tokens[i + 4])
                i += 5
            elif flag == "r":  # RGB
                if len(tokens) - i != 4:
                    raise ValueError("Invalid arguments for -r. Requires (r) (g) (b) (a).")
                color_type = ProcessColorSpaceType.RGB
                color = [float(tokens[i]), float(tokens[i + 1]), float(tokens[i + 2])]
                alpha = float(tokens[i + 3])
                i += 4
            else:
                raise ValueError(f"Unsupported option: {flag}")
        else:
            raise ValueError(f"Unexpected token: {arg}")
    # Validate color and alpha values
    if not (0 <= alpha <= 1 and all(0 <= c <= 1 for c in color)):
        raise ValueError("Color and alpha values must be between 0 and 1.")
    return color, color_type, alpha


def apply_overlay_to_pages(in_doc: Document, out_doc: Document, color: list, color_type: ProcessColorSpaceType, color_alpha: float):
    """Apply the overlay color to all pages in the document."""
    # Create transparency and set blend mode
    transparency = Transparency(color_alpha)
    transparency.blend_mode = BlendMode.MULTIPLY
    # Create color space
    color_space = ColorSpace.create_process_color_space(out_doc, color_type)
    # Create a transparent paint for the given color
    paint = Paint.create(out_doc, color_space, color, transparency)
    fill = Fill(paint)
    # Get output pages
    out_pages = out_doc.pages
    # Define page copy options
    copy_options = PageCopyOptions()
    # Loop through all pages
    for in_page in in_doc.pages:
        # Create a new page
        out_page = Page.copy(out_doc, in_page, copy_options)
        in_page_size = in_page.size
        # Create a content generator
        with ContentGenerator(out_page.content, False) as generator:
            # Make a rectangular path the same size as the page
            path = Path()
            with PathGenerator(path) as path_generator:
                # Compute Rectangle
                path_rectangle = Rectangle(
                        left=0,
                        bottom=0,
                        right=in_page_size.width,
                        top=in_page_size.height,
                    )
                path_generator.add_rectangle(path_rectangle)
            # Paint the path with the transparent overlay
            generator.paint_path(path, fill, None)
        out_pages.append(out_page)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Overlay all pages of a PDF document with a configurable color.", usage="python ./overlay_color.py [<options>] <input_path> <output_path>")

    # Add arguments
    parser.add_argument("options", type=str, nargs="?", default=None)
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    options = args.options
    input_file_path = args.input_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Parse the color options
        color, color_type, color_alpha = parse_options(options)
        # Open the input and create the output document
        with open(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with open(output_file_path, "wb+") as out_stream:
                    with Document.create(out_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Apply the overlay
                        apply_overlay_to_pages(in_doc, out_doc, color, color_type, color_alpha)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)