"""
File: validate_simple.py
Usage: python ./validate_simple.py <input_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Validate PDF conformance

"""

from pdftools_sdk.pdf import Document, Conformance
from pdftools_sdk.pdf_a.validation import Validator, ErrorCategory

import argparse, io

def error_listener(context, data_part: str, message: str, category: ErrorCategory, context_text: str, page_no: int, object_no: int):
    if page_no > 0:
        print(f"- {category.name}: {message.decode()} ({context_text.decode()} on page {page_no})")
    else:
        print(f"- {category.name}: {message.decode()} ({context_text.decode()})")


def validate(input_file_path: str):
    # Open the document
    with io.FileIO(input_file_path, 'rb') as in_stream:
        with Document.open(in_stream) as input_document:
            # Create a validator object that writes all validation error messages to the console
            validator = Validator()
            validator.add_error_handler(error_listener)
            # Validate the standard conformance of the document
            return validator.validate(input_document)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Assess whether a PDF document adheres to specific standards and conformance levels.", usage="python ./validate_simple.py <input_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        validation_result = validate(input_file_path)
        # Report the validation result
        if validation_result.is_conforming:
            print(f"Document conforms to {Conformance(validation_result.conformance).name}.")
        else:
            print(f"Document does not conform to {Conformance(validation_result.conformance).name}.")

        print(f"Validation of {input_file_path} finished.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)