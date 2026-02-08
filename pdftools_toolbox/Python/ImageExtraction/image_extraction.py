"""
File: image_extraction.py
Usage: python ./image_extraction.py <input_path> <output_dir>
                Example: in.pdf dir/subdir/

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Extract all images and image masks from a PDF

"""

import io
import os
from pdftools_toolbox.pdf import Document, Page
from pdftools_toolbox.pdf.content import ContentExtractor, ImageElement, ImageMaskElement, ImageType

import argparse, io

def extract_image(image_element: ImageElement, output_path: str):
    with open(output_path, "wb+") as out_stream:
        image_element.image.extract(out_stream)


def extract_image_mask(image_mask_element: ImageMaskElement, output_path: str):
    with open(output_path, "wb+") as out_stream:
        image_mask_element.image_mask.extract(out_stream)


def process_page_content(page: Page, page_number: int, output_dir: str):
    extractor = ContentExtractor(page.content)
    img_count = 0
    mask_count = 0
    for content_element in extractor:
        # Extract image elements
        if isinstance(content_element, ImageElement):
            img_count += 1
            image_type = content_element.image.default_image_type
            extension = ".jpg" if image_type == ImageType.JPEG else ".tiff"
            output_path = os.path.join(output_dir, f"image_page{page_number}_{img_count}{extension}")
            extract_image(content_element, output_path)
            print(f"Extracted image: {output_path}")
        # Extract image masks
        elif isinstance(content_element, ImageMaskElement):
            mask_count += 1
            output_path = os.path.join(output_dir, f"image_mask_page{page_number}_{mask_count}.tiff")
            extract_image_mask(content_element, output_path)
            print(f"Extracted image mask: {output_path}")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Extract the embedded image data as JPEG or TIFF, depending on the compression format used.", usage="python ./image_extraction.py <input_path> <output_dir>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_dir", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_dir = args.output_dir

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Ensure the output directory exists
        os.makedirs(output_dir, exist_ok=True)
        # Open input document
        with io.FileIO(input_file_path, "rb") as in_stream:
            with Document.open(in_stream, None) as in_doc:
                for page_number, page in enumerate(in_doc.pages, start=1):
                    process_page_content(page, page_number, output_dir)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)