"""
File: pdf2_img_simple.py
Usage: python ./pdf2_img_simple.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Convert PDF to image

"""

from pdftools_sdk.pdf import Document
from pdftools_sdk.pdf2_image import Converter
from pdftools_sdk.pdf2_image.profiles import Archive

import argparse, io

def pdf_to_image(input_pdf_path: str, output_image_path: str):
    # Open input document
    with io.FileIO(input_pdf_path, 'rb') as input_pdf_stream:
        with Document.open(input_pdf_stream) as input_pdf_document:
            # Create the profile that defines the conversion parameters.
            # The Archive profile converts PDF documents to TIFF images for archiving.
            profile = Archive()
            # Optionally the profile's parameters can be changed according to the 
            # requirements of your conversion process.
            # Create output stream
            with io.FileIO(output_image_path, 'wb+') as output_stream:
                # Convert the PDF document to an image document
                converter = Converter()
                converter.convert_document(input_pdf_document, output_stream, profile)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Convert a PDF to a rasterized image. In this example, the conversion profile outputs the PDF as a TIFF image suitable for archiving.", usage="python ./pdf2_img_simple.py <input_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_pdf_path = args.input_path
    output_image_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        pdf_to_image(input_pdf_path, output_image_path)

        print(f"Successfully created file {output_image_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)