"""
File: img2_pdf_accessibility.py
Usage: python ./img2_pdf_accessibility.py <input_path> <alternate_text> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Convert an image to an accessible PDF/A document

"""

from pdftools_sdk.image import Document
from pdftools_sdk.pdf import Conformance
from pdftools_sdk.image2_pdf import Converter
from pdftools_sdk.image2_pdf.profiles import Archive

import argparse, io

def image_to_pdf(input_path: str, alternate_text: str, output_path: str):
    # Open image document
    with io.FileIO(input_path, 'rb') as image_stream:
        with Document.open(image_stream) as image_document:
            # Create the profile that defines the conversion parameters.
            # The Archive profile converts images to PDF/A documents for archiving.
            profile = Archive()
            # Set conformance of output document to PDF/A-2a
            profile.conformance = Conformance.PDF_A2_A
            # For PDF/A level A, an alternate text is required for each page of the image.
            # This is optional for other PDF/A levels, e.g. PDF/A-2b.
            profile.language = "en"
            profile.alternate_text.append(alternate_text)
            # Optionally other profile parameters can be changed according to the 
            # requirements of your conversion process.
            # Create output stream
            with io.FileIO(output_path, 'wb+') as output_stream:
                # Convert the image to a tagged PDF/A document
                converter = Converter()
                converter.convert(image_document, output_stream, profile)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Convert an image to an accessible PDF/A-2a document. Alternative text is added to the image, as required for PDF/A level A, to ensure accessibility for people with disabilities who use assistive technologies.", usage="python ./img2_pdf_accessibility.py <input_path> <alternate_text> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("alternate_text", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_path = args.input_path
    alternate_text = args.alternate_text
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        image_to_pdf(input_path, alternate_text, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)