"""
File: multiple_img2_pdf.py
Usage: python ./multiple_img2_pdf.py <input_path> [<input_path2> ...] <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Convert multiple images to a PDF

"""

from pdftools_sdk.image import Document as ImageDocument, DocumentList as ImageDocumentList
from pdftools_sdk.image2_pdf import Converter
from pdftools_sdk.image2_pdf.profiles import Default

import argparse, io

def images_to_pdf(input_image_paths: list[str], output_file_path: str):
    try:
        stream_list = []
        images = ImageDocumentList()
        # Open input images and store in list
        for input_image_path in input_image_paths:
            image_stream = io.FileIO(input_image_path, 'rb')
            stream_list.append(image_stream)
            images.append(ImageDocument.open(image_stream))
        # Create the profile that defines the conversion parameters.
        profile = Default()
        # Optionally the profile's parameters can be changed according to the 
        # requirements of your conversion process.
        # Create output stream
        with io.FileIO(output_file_path, 'wb+') as output_stream:
            converter = Converter()
            converter.convert_multiple(images, output_stream, profile)
    finally:
        if 'images' in locals():
            for image in images:
                image.__exit__(None, None, None)
        if 'stream_list' in locals(): 
            for stream in stream_list:
                stream.__exit__(None, None, None)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Convert a list of images into a single PDF. Supported image types are TIFF, JPEG, BMP, GIF, PNG, JBIG2, and JPEG2000.", usage="python ./multiple_img2_pdf.py <input_path> [<input_path2> ...] <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str, nargs="*")
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_image_paths = args.input_path
    output_file_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        images_to_pdf(input_image_paths, output_file_path)

        print(f"Successfully created file {output_file_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)