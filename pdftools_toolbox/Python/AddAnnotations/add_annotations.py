"""
File: add_annotations.py
Usage: python ./add_annotations.py <input_path> <output_path>
                Example: in.pdf out.pdf

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Add annotations to PDF

"""

from pdftools_toolbox.pdf import Document, FileReference, Metadata, Page, PageCopyOptions, PageList
from pdftools_toolbox.geometry.real import Point, QuadrilateralList, Rectangle
from pdftools_toolbox.pdf.annotations import EllipseAnnotation, FreeText, Highlight, StickyNote
from pdftools_toolbox.pdf.content import ColorSpace, ContentExtractor, IccBasedColorSpace, ImageElement, Paint, ProcessColorSpaceType, Stroke, TextElement, Transparency
from pdftools_toolbox.pdf.navigation import ViewerSettings, WebLink

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


def copy_and_add_annotations(out_doc: Document, in_page: Page, copy_options: PageCopyOptions):
    # Copy page to output document
    out_page = Page.copy(out_doc, in_page, copy_options)
    # Make a RGB color space
    rgb = ColorSpace.create_process_color_space(out_doc, ProcessColorSpaceType.RGB)
    # Get the page size for positioning annotations
    page_size = out_page.size
    # Get the output page's list of annotations for adding annotations
    annotations = out_page.annotations
    # Create a sticky note and add to output page's annotations
    green = Paint.create(out_doc, rgb, [0.0, 1.0, 0.0], None)
    sticky_note_top_left = Point(x=10.0, y=page_size.height - 10.0)
    sticky_note = StickyNote.create(out_doc, sticky_note_top_left, "Hello world!", green)
    annotations.append(sticky_note)
    # Create an ellipse and add to output page's annotations
    blue = Paint.create(out_doc, rgb, [0.0, 0.0, 1.0], None)
    yellow = Paint.create(out_doc, rgb, [1.0, 1.0, 0.0], None)
    ellipse_box = Rectangle(left=10.0, bottom=page_size.height - 60.0, right=70.0, top=page_size.height - 20.0)
    ellipse = EllipseAnnotation.create(out_doc, ellipse_box, Stroke(blue, 1.5), yellow)
    annotations.append(ellipse)
    # Create a free text and add to output page's annotations
    yellow_transp = Paint.create(out_doc, rgb, [1.0, 1.0, 0.0], Transparency(0.5))
    free_text_box = Rectangle(left=10.0, bottom=page_size.height - 170.0, right=120.0, top=page_size.height - 70.0)
    free_text = FreeText.create(out_doc, free_text_box, "Lorem ipsum dolor sit amet, consectetur adipiscing elit.", yellow_transp)
    annotations.append(free_text)
    # A highlight and a web-link to be fitted on existing page content elements
    highlight = None
    web_link = None
    # Extract content elements from the input page
    extractor = ContentExtractor(in_page.content)
    for element in extractor:
        # Take the first text element
        if highlight is None and isinstance(element, TextElement):
            # Get the quadrilaterals of this text element
            quadrilaterals = QuadrilateralList()
            for fragment in element.text:
                quadrilaterals.append(fragment.transform.transform_rectangle(fragment.bounding_box))
            # Create a highlight and add to output page's annotations
            highlight = Highlight.create_from_quadrilaterals(out_doc, quadrilaterals, yellow)
            annotations.append(highlight)
        # Take the first image element
        if web_link is None and isinstance(element, ImageElement):
            # Get the quadrilateral of this image
            quadrilaterals = QuadrilateralList()
            quadrilaterals.append(element.transform.transform_rectangle(element.bounding_box))
            # Create a web-link and add to the output page's links
            web_link = WebLink.create_from_quadrilaterals(out_doc, quadrilaterals, "https://www.pdf-tools.com")
            red = Paint.create(out_doc, rgb, [1.0, 0.0, 0.0], None)
            web_link.border_style = Stroke(red, 1.5)
            out_page.links.append(web_link)
        # Exit loop if highlight and web-link have been created
        if highlight is not None and web_link is not None:
            break
    return out_page



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Generate and add various types of annotations at specified positions on the first page of a PDF document.", usage="python ./add_annotations.py <input_path> <output_path>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("output_path", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    output_file_path = args.output_path

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        # Open input document
        with io.FileIO(input_file_path, 'rb') as in_stream:
            with Document.open(in_stream, None) as in_doc:
                # Create output document
                with io.FileIO(output_file_path, 'wb+') as output_stream:
                    with Document.create(output_stream, in_doc.conformance, None) as out_doc:
                        # Copy document-wide data
                        copy_document_data(in_doc, out_doc)
                        # Define page copy options
                        copy_options = PageCopyOptions()
                        # Copy first page and add annotations
                        out_page = copy_and_add_annotations(out_doc, in_doc.pages[0], copy_options)
                        # Add the page to the output document's page list
                        out_doc.pages.append(out_page)
                        # Copy the remaining pages and add to the output document's page list
                        in_pages = in_doc.pages[1:]
                        out_pages = PageList.copy(out_doc, in_pages, copy_options)
                        out_doc.pages.extend(out_pages)

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)