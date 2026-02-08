"""
File: update_annotations.py
Usage: python ./update_annotations.py <input_path> <input_fdf_path> <output_path> <output_fdf_path>
                Example: in.pdf inFdf.fdf out.pdf outFdf.fdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Update annotations to PDF

"""

from pdftools_toolbox.pdf import CopyStrategy, Document, FileReference, Metadata, PageCopyOptions, Page
from pdftools_toolbox.pdf.content import IccBasedColorSpace
from pdftools_toolbox.pdf.annotations import Annotation, EllipseAnnotation
from pdftools_toolbox.pdf.navigation import ViewerSettings

import argparse, io

def copy_document_data(in_doc: Document, out_doc: Document):
    # Copy document-wide data
    # Output intent
    if in_doc.output_intent is not None:
        in_doc.output_intent = IccBasedColorSpace.copy(out_doc, in_doc.output_intent)
    # Metadata
    out_doc.metadata = Metadata.copy(out_doc, in_doc.metadata)
    # Viewer settings
    out_doc.viewer_settings = ViewerSettings.copy(out_doc, in_doc.viewer_settings)
    # Associated files (for PDF/A-3 and PDF 2.0 only)
    outAssociatedFiles = out_doc.associated_files
    for in_file_ref in in_doc.associated_files:
        outAssociatedFiles.append(FileReference.copy(out_doc, in_file_ref))
    # Plain embedded files
    out_embedded_files = out_doc.plain_embedded_files
    for in_file_ref in in_doc.plain_embedded_files:
        out_embedded_files.append(FileReference.copy(out_doc, in_file_ref))


def filter_annotations(in_doc: Document, out_doc: Document):
    """Filter annotations and remove 'Ellipse' annotations."""
    # Define page copy options
    copy_options = PageCopyOptions()
    # Remove all annotations: we will add the filtered ones later
    copy_options.annotations = CopyStrategy.REMOVE
    for in_page in in_doc.pages:
        # Copy page to the output document
        out_page = Page.copy(out_doc, in_page, copy_options)
        # Hold the annotations from the input document
        in_annotations = in_page.annotations
        # Selectively copy annotations (excluding EllipseAnnotations - like Circle)
        for in_annotation in in_annotations:
            if not isinstance(in_annotation, EllipseAnnotation):
                out_page.annotations.append(Annotation.copy(out_doc, in_annotation))
        # Add the page to the output document
        out_doc.pages.append(out_page)



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Remove the 'Ellipse' annotations from the PDF and export the new list of annotations to a new FDF-File.", usage="python ./update_annotations.py <input_path> <input_fdf_path> <output_path> <output_fdf_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("input_fdf_path", type=str)
    parser.add_argument("output_path", type=str)
    parser.add_argument("output_fdf_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    input_fdf_path = args.input_fdf_path
    output_file_path = args.output_path
    output_fdf_path = args.output_fdf_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input PDF and FDF files
        with io.FileIO(input_file_path, "rb") as in_stream:
            with io.FileIO(input_fdf_path, "rb") as in_fdf_stream:
                with Document.open_with_fdf(in_stream, in_fdf_stream, None) as in_doc:
                    # Create output PDF and FDF files
                    with io.FileIO(output_file_path, "wb+") as out_stream:
                        with io.FileIO(output_fdf_path, "wb+") as out_fdf_stream:
                            with Document.create_with_fdf(out_stream, out_fdf_stream, in_doc.conformance, None) as out_doc:
                                # Copy document-wide data
                                copy_document_data(in_doc, out_doc)
                                # Filter and process annotations
                                filter_annotations(in_doc, out_doc)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)