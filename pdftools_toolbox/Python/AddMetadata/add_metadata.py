"""
File: add_metadata.py
Usage: python ./add_metadata.py <input_path> <output_path> [<mdatafile>]
                Example: in.pdf out.pdf MetadataTest.xmp

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add metadata to PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, PageCopyOptions, PageList
from pdftools_toolbox.pdf.content import IccBasedColorSpace
from pdftools_toolbox.pdf.navigation import ViewerSettings

import argparse, io

def copy_document_data(in_doc: Document, out_doc: Document):
    # Copy document-wide data (excluding metadata)
    # Output intent
    if in_doc.output_intent is not None:
        in_doc.output_intent = IccBasedColorSpace.copy(out_doc, in_doc.output_intent)
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



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Set metadata such as author, title, and creator of a PDF document. Optionally use the metadata of another PDF document or the content of an XMP file.", usage="python ./add_metadata.py <input_path> <output_path> [<mdatafile>]")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)
    parser.add_argument("mdatafile", type=str, nargs="?", default=None)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_file_path = args.output_path
    metadata_file_path = args.mdatafile if args.mdatafile else None

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, 'rb') as content_pdf_stream:
            with Document.open(content_pdf_stream, None) as content_pdf_document:
                # Create output document
                with io.FileIO(output_file_path, 'wb+') as output_stream:
                    with Document.create(output_stream, content_pdf_document.conformance, None) as output_document:
                        # Copy document-wide data
                        copy_document_data(content_pdf_document, output_document)
                        # Set Metadata
                        if metadata_file_path is not None:
                            with io.FileIO(metadata_file_path, 'rb') as metadata_stream:
                                if metadata_file_path.endswith(".pdf"):
                                    # Use the metadata of another PDF file
                                    with Document.open(metadata_stream, "") as meta_doc:
                                        mdata = Metadata.copy(output_document, meta_doc.metadata)
                                else:
                                    # Use the content of an XMP metadata file
                                    mdata = Metadata.create(output_document, metadata_stream)
                        else:
                            mdata = output_document.metadata
                            mdata.author = "Your Author"
                            mdata.title = "Your Title"
                            mdata.subject = "Your Subject"
                            mdata.creator = "Your Creator"
                        output_document.metadata = mdata
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        # Copy all pages and append to output document
                        copied_pages = PageList.copy(output_document, content_pdf_document.pages, copy_options)
                        output_document.pages.extend(copied_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)