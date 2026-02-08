"""
File: validate_convert.py
Usage: python ./validate_convert.py <input_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Convert a PDF to PDF/A-2b if necessary

"""

from pdftools_sdk.pdf import Document, Conformance
from pdftools_sdk.pdf_a.conversion import Converter, EventSeverity, EventCategory, EventCode
from pdftools_sdk.pdf_a.validation import AnalysisOptions, Validator

import argparse, io

def convert_if_not_conforming(input_file_path: str, output_file_path: str, conformance: Conformance):
    with io.FileIO(input_file_path, 'rb') as in_stream:
        with Document.open(in_stream) as input_document:
            # Create the Validator object, and use the Conformance object to create
            # an AnalysisOptions object that controls the behavior of the Validator.
            validator = Validator()
            analysis_options = AnalysisOptions()
            analysis_options.conformance = conformance
            # Run the analysis, and check the results.
            # Only proceed if document is not conforming.
            analysis_result = validator.analyze(input_document, analysis_options)
            if analysis_result.is_conforming:
                print(f"Document conforms to {input_document.conformance.name} already.")
                return
            # Create a converter object
            converter = Converter()
            # Add handler for conversion events
            converter.add_conversion_event_handler(event_handler)
            with io.FileIO(output_file_path, 'wb+') as output_stream:
                # Convert the input document to PDF/A using the converter object
                # and its conversion event handler
                output_document = converter.convert(analysis_result, input_document, output_stream, None)
                # Check if critical conversion events occurred
                match events_severity:
                    case EventSeverity.INFORMATION:
                        print(f"Successfully converted document to {output_document.conformance.name}.")
                    case EventSeverity.WARNING:
                        print(f"Warnings occurred during the conversion of document to {output_document.conformance.name}.")
                        print("Check the output file to decide if the result is acceptable.")
                    case EventSeverity.ERROR:
                        raise Exception(f"Unable to convert document to {conformance.name} because of critical conversion events.")


def event_handler(data_part: str, message: str, severity: EventSeverity, category: EventCategory, code: EventCode, context_info: str, page_no: int):
    # Get the event's suggested severity
    suggested_severity = severity
    # Optionally, the suggested severity can be changed according to
    # the requirements of your conversion process and, for example,
    # the event's category.
    global events_severity
    if suggested_severity > events_severity:
        events_severity = suggested_severity
    # Report conversion event
    if suggested_severity == EventSeverity.INFORMATION:
        severity_char = 'I'
    elif suggested_severity == EventSeverity.WARNING:
        severity_char = 'W'
    else:
        severity_char = 'E'
    if page_no > 0:
        print(f"- {severity_char} {category.name}: {message} ({context_info} on page {page_no})")
    else:
        print(f"- {severity_char} {category.name}: {message} ({context_info})")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Analyze the input PDF document. If it does not yet conform to PDF/A-2b, convert it to PDF/A-2b.", usage="python ./validate_convert.py <input_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_file_path = args.output_path
    conformance = Conformance.PDF_A2_B

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Define global events_severity
        events_severity = EventSeverity.INFORMATION
        convert_if_not_conforming(input_file_path, output_file_path, conformance)

        print(f"Successfully created file {output_file_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)