"""
File: img_accessibility_a_i.py
Usage: python ./img_accessibility_a_i.py <input_path> [<input_path2> ...] <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Convert images to an accessible PDF/A document

"""

from openai import OpenAI
import base64
from pdftools_sdk.image import Document as ImageDocument, DocumentList as ImageDocumentList
from pdftools_sdk.pdf import Conformance
from pdftools_sdk.image2_pdf import Converter
from pdftools_sdk.image2_pdf.profiles import Archive

import argparse, io

def get_alternate_text(image_path: str):
    # Getting base64 representation of input image
    with io.FileIO(image_path, 'rb') as image_stream:
        base64_image = base64.b64encode(image_stream.read()).decode('utf-8')
    # Instantiate OpenAI client and let AI create the alternate text
    client = OpenAI(api_key="***insert-open-ai-api-key***")
    response = client.chat.completions.create(
        model="gpt-4-turbo",
        messages=[
            {
            "role": "user",
            "content": [
                {"type": "text", "text": "Write a short sentence what can be seen on the image. It shall explain to a person with impaired vision what is on the image. Write the answer in a poetic way in english."},
                {
                    "type": "image_url",
                    "image_url":
                        {
                            "url": f"data:image/jpeg;base64,{base64_image}",
                        },
                },
            ],
            }
        ],
        max_tokens=300,
    )
    return response.choices[0].message.content.strip()


def images_to_accessible_pdf(image_paths: list[str], output_file_path: str):
    # Store stream descriptors and images in lists
    stream_list = []
    images = ImageDocumentList()
    # Loop over all the image paths and store opened images into list
    for input_image_path in image_paths:
        image_stream = io.FileIO(input_image_path, 'rb')
        stream_list.append(image_stream)
        images.append(ImageDocument.open(image_stream))
    # Create output stream for writing
    with io.FileIO(output_file_path, 'wb+') as output_stream:
        # Create the profile that defines the conversion parameters.
        # The Archive profile converts images to PDF/A documents for archiving.
        profile = Archive()
        # Set conformance of output document to PDF/A-2a
        profile.conformance = Conformance.PDF_A2_A
        # For PDF/A level A, an alternate text is required for each page of the image.
        # This is optional for other PDF/A levels, e.g. PDF/A-2b.
        profile.language = "en"
        # Set alternate texts created by AI
        alternate_text_list = profile.alternate_text
        for image_path in image_paths:                
            alternate_text = get_alternate_text(image_path)
            alternate_text_list.append(alternate_text)
        converter = Converter()
        out_document = converter.convert_multiple(images, output_stream, profile)
        if not out_document:
            print(f"Error while converting images to Pdf.")
            return
    # Cleanup in finally block
    for image in images:
        image.__exit__(None, None, None)
    for stream in stream_list:
        stream.__exit__(None, None, None)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Convert images to an accessible PDF/A-2a document. Alternative texts are generated using the OpenAI API with a dedicated prompt.", usage="python ./img_accessibility_a_i.py <input_path> [<input_path2> ...] <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str, nargs="*")
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    image_paths = args.input_path
    output_file_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        images_to_accessible_pdf(image_paths, output_file_path)

        print(f"Successfully created file {output_file_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)