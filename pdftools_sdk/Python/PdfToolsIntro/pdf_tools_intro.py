"""
File: pdf_tools_intro.py
Usage: python ./pdf_tools_intro.py <cover_image> <content_pdf_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Hello, Pdftools SDK!

"""

from pdftools_sdk.image import Document as ImageDocument
from pdftools_sdk.pdf import Document as PdfDocument
from pdftools_sdk.image2_pdf import Converter
from pdftools_sdk.image2_pdf.profiles import Default
from pdftools_sdk.document_assembly import DocumentAssembler

import argparse, io

def add_cover_to_pdf(cover_image: str, content_pdf_path: str, output_path: str):
    # Convert the image cover to a PDF (stored in memory)
    with io.BytesIO() as cover_stream:
        with io.FileIO(cover_image, 'rb') as image_stream:
            with ImageDocument.open(image_stream) as image_document:
                # Create the profile for converting the image to PDF
                profile = Default()
                # Convert image to PDF
                converter = Converter()
                converter.convert(image_document, cover_stream, profile)
        # Prepare the content PDF and merge with the cover
        with io.FileIO(content_pdf_path, 'rb') as content_pdf_stream:
            with PdfDocument.open(content_pdf_stream) as content_pdf_document:
                # Open output stream and append cover and content
                with io.FileIO(output_path, 'wb+') as output_stream:
                    with DocumentAssembler(output_stream, None, None) as assembler:
                        # Append cover page (convert from memory stream to PDF)
                        assembler.append(PdfDocument.open(io.BytesIO(cover_stream.getvalue())), 1, 1)
                        # Append the content PDF
                        assembler.append(content_pdf_document)
                        # Finalize the merged document
                        assembler.assemble()



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Add a cover page from an image to a PDF.", usage="python ./pdf_tools_intro.py <cover_image> <content_pdf_path> <output_path>")

    # Add arguments
    parser.add_argument("cover_image", type=str)
    parser.add_argument("content_pdf_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    cover_image = args.cover_image
    content_pdf_path = args.content_pdf_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Optional: Set your proxy configuration
        # Sdk.set_proxy("http://myproxy:8080")
        add_cover_to_pdf(cover_image, content_pdf_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)