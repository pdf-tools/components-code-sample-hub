"""
File: zugferd.py
Usage: python ./zugferd.py <input_path> <invoice_path> <output_path>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Create a ZUGFeRD invoice

"""

from pdftools_sdk.pdf import Document, Conformance
from pdftools_sdk.pdf_a.validation import Validator, AnalysisOptions
from pdftools_sdk.pdf_a.conversion import Converter, InvoiceType, EventSeverity, EventCategory, EventCode

import argparse, io

def add_zugferd_invoice(input_path: str, zugferd_xml_path: str, output_path: str):
    # Open input document
    with io.FileIO(input_path, 'rb') as input_stream:
        with Document.open(input_stream) as input_document:
            # Create the Validator object, and use the Conformance object to create
            # an AnalysisOptions object that controls the behavior of the Validator.
            validator = Validator()
            # The conformance has to be set to PDF/A-3 when adding the XML invoice file
            analysis_options = AnalysisOptions()
            analysis_options.conformance = Conformance.PDF_A3_U
            # Run the analysis
            analysis_result = validator.analyze(input_document, analysis_options)
            # Create a converter object
            converter = Converter()
            # Add the invoice XML file
            with io.FileIO(zugferd_xml_path, 'rb') as invoice_stream:
                converter.add_invoice_xml(InvoiceType.ZUGFERD, invoice_stream)
                # Add handler for conversion events
                event_severity_holder = [EventSeverity.INFORMATION]
                converter.add_conversion_event_handler(lambda *args: handle_conversion_event(*args, event_severity_holder))
                # Create output file
                with io.FileIO(output_path, 'wb+') as output_stream:
                    # Convert the input document to PDF/A
                    with converter.convert(analysis_result, input_document, output_stream) as output_document:
                        if event_severity_holder[0] == EventSeverity.INFORMATION:
                            print(f"Successfully converted document to {output_document.conformance.name}.")
                        elif event_severity_holder[0] == EventSeverity.WARNING:
                            print(f"Warnings occurred during the conversion to {output_document.conformance}.")
                            print("Check the output file to decide if the result is acceptable.")
                        elif event_severity_holder[0] == EventSeverity.ERROR:
                            raise Exception(f"Unable to convert document to PDF/A-3U because of critical conversion events.")


def handle_conversion_event(data_part: str, message: str, severity: EventSeverity, category: EventCategory, code: EventCode, context: str, page_no: int, event_severity_holder: list[EventSeverity]):
    # Optionally the suggested severity can be changed according to
    # the requirements of your conversion process and, for example,
    # the event's category (e.Category).
    if severity > event_severity_holder[0]:
        event_severity_holder[0] = severity
    print(f"- {severity.name} {category.name}: {message} ({context}{f' on page {page_no}' if page_no > 0 else ''})")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Convert a PDF to PDF/A-3 and embed XML data to create a ZUGFeRD-compliant invoice.", usage="python ./zugferd.py <input_path> <invoice_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("invoice_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_path = args.input_path
    zugferd_xml_path = args.invoice_path
    output_path = args.output_path

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Optional: Set your proxy configuration
        # Sdk.set_proxy("http://myproxy:8080")
        add_zugferd_invoice(input_path, zugferd_xml_path, output_path)

        print(f"Successfully created file {output_path}")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)