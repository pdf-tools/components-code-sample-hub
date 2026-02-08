"""
File: img2_pdf_default.py
Usage: python ./img2_pdf_default.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Convert image to PDF

"""

from pdftools_sdk.image import Document
from pdftools_sdk.image2_pdf import Converter
from pdftools_sdk.image2_pdf.profiles import Default

import argparse, io

def convert_image_to_pdf(input_path: str, output_path: str):
    # Open image document
    with io.FileIO(input_path, 'rb') as in_stream:
        with Document.open(in_stream) as input_document:
            # Create the profile that defines the conversion parameters (Default profile)
            profile = Default()
            # Optionally, you can adjust the profile's parameters if needed
            # Create output stream
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Convert the image to a PDF document
                converter = Converter()
                converter.convert(input_document, output_stream, profile)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Convert an image to a PDF. The default settings for this conversion profile place each image on a separate A4 portrait page with a 2 cm margin.", usage="python ./img2_pdf_default.py <input_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_path = args.input_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Optional: Set your proxy configuration
        # Sdk.set_proxy("http://myproxy:8080")
        convert_image_to_pdf(input_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)