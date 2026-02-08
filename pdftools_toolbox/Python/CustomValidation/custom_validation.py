"""
File: custom_validation.py
Usage: python ./custom_validation.py <input_path> <ini_path> [<pdf_password>]
                Example: in.pdf properties.ini \"my_password\"

Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Validate custom properties of a PDF file

"""

import os
import re
import configparser
from pdftools_toolbox.geometry.integer import Size
from pdftools_toolbox.pdf import Conformance, Document, Permission
from pdftools_toolbox.pdf.content import ContentExtractor, TextElement, UngroupingSelection

import argparse, io

class IniFile:
    def get_value(self, section: str, key: str, default_value: str = None) -> str:
        return self.config.get(section, key, fallback=default_value)
    def get_keys_matching_pattern(self, section: str, pattern: str) -> list:
        matching_keys = []
        if section in self.config:
            for key in self.config[section]:
                if re.match(pattern, key, re.IGNORECASE):
                    matching_keys.append(self.config[section][key])
        return matching_keys


def open_ini_file(path: str) -> IniFile:
    ini_file = IniFile()
    ini_file.config = configparser.ConfigParser()
    ini_file.config.read(path)
    return ini_file


class DocumentValidator:
    def validate_document(self) -> bool:
        is_valid = self.validate_file_size()
        with open(self.input_path, "rb") as in_stream:
            with Document.open(in_stream, self.pdf_password) as in_doc:
                is_valid &= self.validate_conformance(in_doc.conformance)
                is_valid &= self.validate_encryption(in_doc.permissions)
                is_valid &= self.validate_pages_size(in_doc)
                is_valid &= self.validate_fonts(in_doc)
        return is_valid
    def validate_file_size(self) -> bool:
        file_size_in_mb = os.path.getsize(self.input_path) / (1024 * 1024)
        if self.ini_file_size:
            ini_file_size_in_mb = float(self.ini_file_size)
            if file_size_in_mb > ini_file_size_in_mb:
                print("The PDF file size exceeds the specified custom limit.")
                return False
            else:
                print("The PDF file size does not exceed the specified custom limit.")
                return True
        return True
    def validate_conformance(self, current_conformance: Conformance) -> bool:
        if self.ini_max_pdf_version_str:
            if ConformanceValidator.validate_conformance(self.ini_max_pdf_version_str, current_conformance):
                print("The PDF version does not exceed the specified custom maximum version.")
                return True
            else:
                print("The PDF version exceeds the specified custom maximum version.")
                return False
        return True
    def validate_encryption(self, permissions: Permission) -> bool:
        if self.ini_encryption:
            encryption_required = self.ini_encryption.lower() == "true"
            if encryption_required and not permissions:
                print("Encryption not conform: the PDF file is not encrypted. The custom encryption value specifies that the PDF file should be encrypted.")
                return False
            elif not encryption_required and permissions:
                print("Encryption not conform: the PDF file is encrypted. The custom encryption value specifies that the PDF file should not be encrypted.")
                return False
            else:
                print("The PDF encryption is conform to the specified custom value.")
                return True
        return True
    def validate_pages_size(self, in_doc: Document) -> bool:
        is_valid = True
        if self.ini_max_page_size is not None:
            page_number = 0
            for page in in_doc.pages:
                page_number += 1
                size_with_int = Size(
                    width=int(page.size.width), height=int(page.size.height)
                )
                is_valid &= self.validate_page_size(page_number, size_with_int)
        return is_valid
    def validate_page_size(self, page_number: int, page_size: Size) -> bool:
        if self.ini_max_page_size is not None:
            validator = create_page_size_validator(self.ini_max_page_size, self.size_tolerance)
            if validator.validate_page_size(page_size):
                print(
                    f"The size of page {page_number} is within the specified custom maximum page size value."
                )
                return True
            else:
                print(
                    f"The size of page {page_number} exceeds the specified custom maximum page size value."
                )
                return False
        return True
    def validate_fonts(self, in_doc: Document) -> bool:
        is_valid = True
        if self.ini_embedding:
            embedding_required = self.ini_embedding.lower() == "true"
            for page_number in range(len(in_doc.pages)):
                page_number += 1
                page = in_doc.pages[page_number-1]
                extractor = ContentExtractor(page.content)
                extractor.ungrouping = UngroupingSelection.ALL
                for element in extractor:
                    if isinstance(element, TextElement):
                        for fragment in element.text:
                            font_name = fragment.font.base_font
                            is_embedded = fragment.font.is_embedded
                            # Check if the font is in the exception list
                            is_current_font_an_exception = any(
                                re.match(exc.replace("*", ".*"), font_name, re.IGNORECASE)
                                for exc in self.embedding_exception_fonts
                            )
                            # Validate based on the embedding setting
                            if (embedding_required and not is_embedded and not is_current_font_an_exception) or (
                                not embedding_required and is_embedded and not is_current_font_an_exception
                            ):
                                is_valid = False
                                status_text = "be embedded" if embedding_required else "not be embedded"
                                print(
                                    f"The font '{font_name}' on page {page_number} should {status_text} as specified by the property 'Embedding' or it should be added to the list of exceptions."
                                )
                            else:
                                status_text = (
                                    "in the exception list" if embedding_required != is_embedded 
                                    else "embedded" if is_embedded 
                                    else "not be embedded"
                                )
                                print(
                                    f"The font '{font_name}' on page {page_number} is conform to the 'Embedding' property as it is {status_text}."
                                )
        return is_valid


def create_document_validator(ini_file: IniFile, input_path: str, pdf_password: str = None) -> DocumentValidator:
    document_validator = DocumentValidator()
    document_validator.ini_file = ini_file
    document_validator.input_path = input_path
    document_validator.pdf_password = pdf_password
    # Extract values from INI file
    document_validator.size_tolerance = ini_file.get_value("Pages", "SizeTolerance", "3.0")
    document_validator.ini_max_page_size = ini_file.get_value("Pages", "MaxPageSize")
    document_validator.ini_max_pdf_version_str = ini_file.get_value("File", "MaxPdfVersion")
    document_validator.ini_encryption = ini_file.get_value("File", "Encryption")
    document_validator.ini_file_size = ini_file.get_value("File", "FileSize")
    document_validator.ini_embedding = ini_file.get_value("Fonts", "Embedding")
    document_validator.embedding_exception_fonts = ini_file.get_keys_matching_pattern("Fonts", r"EmbeddingExcFont\d+")
    return document_validator


class PageSizeValidator:
    named_page_sizes = {
        "Letter": Size(width=612, height=792),
        "A0": Size(width=2384, height=3370),
        "A1": Size(width=1684, height=2384),
        "A2": Size(width=1191, height=1684),
        "A3": Size(width=842, height=1191),
        "A4": Size(width=595, height=842),
        "A5": Size(width=420, height=595),
        "A6": Size(width=298, height=420),
        "A7": Size(width=210, height=298),
        "A8": Size(width=147, height=210),
        "A9": Size(width=105, height=147),
        "A10": Size(width=74, height=105),
        "DL": Size(width=283, height=595),
    }
    def parse_page_size(self, max_page_size: str) -> Size:
        named_size = self.named_page_sizes.get(max_page_size)
        if named_size:
            return named_size
        match = re.match(
            r"(\d+(\.\d+)?)\s*x\s*(\d+(\.\d+)?)(\s*(pt|in|cm|mm))?", max_page_size, re.IGNORECASE
        )
        if not match:
            raise ValueError(f"Invalid MaxPageSize format: {max_page_size}")
        width = float(match.group(1))
        height = float(match.group(3))
        unit = match.group(6).lower() if match.group(6) else "pt"
        if unit == "in":
            return Size(width=int(width * 72), height=int(height * 72))
        elif unit == "cm":
            return Size(width=int(width * 28.3465), height=int(height * 28.3465))
        elif unit == "mm":
            return Size(width=int(width * 2.83465), height=int(height * 2.83465))
        elif unit in ["pt", ""]:
            return Size(width=int(width), height=int(height))
        else:
            raise ValueError(f"Unsupported unit: {unit}")
    def parse_size_tolerance(self, size_tolerance_str: str) -> float:
        if not size_tolerance_str:
            return 3.0
        match = re.match(r"(\d+(\.\d+)?)\s*(%)?", size_tolerance_str, re.IGNORECASE)
        if not match:
            raise ValueError(f"Invalid SizeTolerance format: {size_tolerance_str}")
        value = float(match.group(1))
        return value / 100.0 if match.group(3) else value
    def validate_page_size(self, page_size: Size) -> bool:
        is_valid = (
            (page_size.width <= self.max_size.width + self.size_tolerance
            and page_size.height <= self.max_size.height + self.size_tolerance
            ) or 
            (page_size.height <= self.max_size.width + self.size_tolerance
            and page_size.width <= self.max_size.height + self.size_tolerance)
        )
        return is_valid


def create_page_size_validator(max_page_size_str: str, size_tolerance_str: str) -> PageSizeValidator:
    page_size_validator = PageSizeValidator()
    page_size_validator.max_size = page_size_validator.parse_page_size(max_page_size_str)
    page_size_validator.size_tolerance = page_size_validator.parse_size_tolerance(size_tolerance_str)
    return page_size_validator


class ConformanceValidator:
    version_map = {
        "1.0": Conformance.PDF10,
        "1.1": Conformance.PDF11,
        "1.2": Conformance.PDF12,
        "1.3": Conformance.PDF13,
        "1.4": Conformance.PDF14,
        "1.5": Conformance.PDF15,
        "1.6": Conformance.PDF16,
        "1.7": Conformance.PDF17,
        "2.0": Conformance.PDF20,
    }
    @staticmethod
    def parse_version_string(version: str) -> Conformance:
        version_parts = version.split(".")
        if len(version_parts) == 2:
            major_minor_version = f"{version_parts[0]}.{version_parts[1]}"
            conformance = ConformanceValidator.version_map.get(major_minor_version)
            if conformance:
                return conformance
        raise ValueError(f"Unsupported version or conformance level: {version}")
    @staticmethod
    def validate_conformance(max_pdf_version_str: str, current_conformance: Conformance) -> bool:
        max_pdf_conformance = ConformanceValidator.parse_version_string(max_pdf_version_str)
        current_conformance_version = ConformanceValidator.get_version_from_conformance(current_conformance)
        return current_conformance_version.value <= max_pdf_conformance.value
    @staticmethod
    def get_version_from_conformance(conformance: Conformance) -> Conformance:
        if conformance in ConformanceValidator.version_map.values():
            return conformance
        if conformance in {Conformance.PDF_A1_A, Conformance.PDF_A1_B}:
            return Conformance.PDF14
        if conformance in {
            Conformance.PDF_A2_A,
            Conformance.PDF_A2_B,
            Conformance.PDF_A2_U,
            Conformance.PDF_A3_A,
            Conformance.PDF_A3_B,
            Conformance.PDF_A3_U,
        }:
            return Conformance.PDF17
        raise ValueError(f"Unsupported conformance level: {conformance}")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Validates the properties defined in a custom properties file. The validation results are written to the console.", usage="python ./custom_validation.py <input_path> <ini_path> [<pdf_password>]")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("ini_path", type=str)
    parser.add_argument("pdf_password", type=str, nargs="?", default=None)

    # Parse the arguments
    args = parser.parse_args()

    input_file_path = args.input_path
    ini_path = args.ini_path
    pdf_password = args.pdf_password if args.pdf_password else None

    try:
        # Set and check license key. If the license key is not valid, an exception is thrown.
        from pdftools_toolbox.sdk import Sdk
        Sdk.initialize("LICENSE-KEY", None)

        ini_file = open_ini_file(ini_path)
        document_validator = create_document_validator(ini_file, input_file_path, pdf_password)
        if document_validator.validate_document():
            print("\nThe document does conform the specified properties.")
        else:
            print("\nThe document does not conform the specified properties.")

        print("Execution successful.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)