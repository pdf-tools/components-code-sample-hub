"""
File: signatures_validate.py
Usage: python ./signatures_validate.py <input_path> [<certificate_directory>]
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Validate the signatures contained in an input document

"""

import os
import hashlib
from pdftools_sdk.pdf import Document, DocumentSignature
from pdftools_sdk.signature_validation import *
from pdftools_sdk.signature_validation.profiles import Default, RevocationCheckPolicy

import argparse, io

def constraint_to_string(indication: Indication, sub_indication: str, message: str, is_full_revision_covered: bool = None):
    # Handle byte range validation if is_full_revision_covered is provided
    if is_full_revision_covered is None or is_full_revision_covered:
        indication_str = (
            "" if indication == Indication.VALID else
            "?" if indication == Indication.INDETERMINATE else
            "!"
        )
        return f"{indication_str}{sub_indication} {message}"
    byte_range_invalid = "!Invalid signature byte range."
    if indication == Indication.VALID:
        return byte_range_invalid
    else:
        return f"{byte_range_invalid} {sub_indication} {message}"


def format_sha1_digest(fingerprint: str, delimiter: str):
    return delimiter.join(fingerprint[i:i+2] for i in range(0, len(fingerprint), 2))


def print_certificate(cert: Certificate):
    if cert is not None:
        print(f"    - Subject    : {cert.subject_name}")
        print(f"    - Issuer     : {cert.issuer_name}")
        print(f"    - Validity   : {cert.not_before} - {cert.not_after}")
        try:
            # Convert the list of integers to bytes
            raw_data_bytes = bytes(cert.raw_data)
            # Fingerprint calculation using hashlib
            fingerprint = hashlib.sha1(raw_data_bytes).hexdigest().upper()
            print(f"    - Fingerprint: {format_sha1_digest(fingerprint, '-')}")
        except Exception as ex:
            print(str(ex))
        # Extract and print the individual DataSource names
        sources = [source.name for source in DataSource if source in cert.source]
        print(f"    - Source     : {', '.join(sources)}")
        print(f"    - Validity   : {constraint_to_string(cert.validity.indication, cert.validity.sub_indication.name, cert.validity.message)}")
    else:
        print("    - null")


def print_signature_content(content: SignatureContent, is_full_revision_covered: bool = None):
    if content is not None:
        print(f"  - Validity  : {constraint_to_string(content.validity.indication, content.validity.sub_indication.name, content.validity.message, is_full_revision_covered)}")
        if isinstance(content, UnsupportedSignatureContent):
            pass  # No action for unsupported content
        elif isinstance(content, CmsSignatureContent):
            print(f"  - Validation: {content.validation_time} from {content.validation_time_source.name}")
            print(f"  - Hash      : {content.hash_algorithm.name}")
            print("  - Signing Cert")
            print_certificate(content.signing_certificate)
            print("  - Chain")
            for index, cert in enumerate(content.certificate_chain, start=1):
                print(f"  - Issuer Cert {index}")
                print_certificate(cert)
            print(f"  - Chain     : {'complete' if content.certificate_chain.is_complete else 'incomplete'} chain")
            print("  Time-Stamp")
            print_signature_content(content.time_stamp)
        elif isinstance(content, TimeStampContent):
            print(f"  - Validation: {content.validation_time} from {content.validation_time_source.name}")
            print(f"  - Hash      : {content.hash_algorithm.name}")
            print(f"  - Time      : {content.date}")
            print("  - Signing Cert")
            print_certificate(content.signing_certificate)
            print("  - Chain")
            for index, cert in enumerate(content.certificate_chain, start=1):
                print(f"  - Issuer Cert {index}")
                print_certificate(cert)
            print(f"  - Chain     : {'complete' if content.certificate_chain.is_complete else 'incomplete'} chain")
        else:
            print(f"Unsupported signature content type {str(type(content))}")
    else:
        print("  - null")


def on_constraint_event(message: str, indication: Indication, sub_indication: SubIndication, signature: DocumentSignature, data_part: str):
    print(f"  - {signature.name}" + (f": {data_part}" if len(data_part) > 0 else "") + ": " +
          constraint_to_string(indication, sub_indication.name, message))


def validate(input_file: str, cert_dir: str):
    # Use the default validation profile as a base for further settings
    profile = Default()
    # For offline operation, build a custom trust list from the file system and disable external revocation checks
    if cert_dir:
        print("Using 'offline' validation mode with custom trust list.")
        print()
        # create a CustomTrustList to hold the certificates
        ctl = CustomTrustList()
        # Iterate through files in the certificate directory and add certificates to the custom trust list
        if os.path.isdir(cert_dir):
            for file_name in os.listdir(cert_dir):
                try:
                    with io.FileIO(os.path.join(cert_dir, file_name), 'rb') as cert_stream:
                        if file_name.endswith(".cer") or file_name.endswith(".pem"):
                            ctl.add_certificates(cert_stream)
                        elif file_name.endswith(".p12") or file_name.endswith(".pfx"):
                            # If a password is required, use add_archive(certStr, password).
                            ctl.add_archive(cert_stream)
                except Exception as e:
                    print(f"Could not add certificate '{file_name}' to custom trust list: {e}")
        else:
            print(f"Directory {cert_dir} is missing. No certificates were added to the custom trust list.")
        print()
        profile.custom_trust_list = ctl
        # Configure validation options
        validation_options = profile.validation_options
        validation_options.time_source = TimeSource.PROOF_OF_EXISTENCE | TimeSource.EXPIRED_TIME_STAMP | TimeSource.SIGNATURE_TIME
        validation_options.certificate_sources = DataSource.EMBED_IN_SIGNATURE | DataSource.EMBED_IN_DOCUMENT | DataSource.CUSTOM_TRUST_LIST
        # Disable revocation checks.
        profile.signing_cert_trust_constraints.revocation_check_policy = RevocationCheckPolicy.NO_CHECK
        profile.time_stamp_trust_constraints.revocation_check_policy = RevocationCheckPolicy.NO_CHECK
    # Validate ALL signatures in the document (not only the latest)
    signatureSelector = SignatureSelector.ALL
    # Create the validator object and event listeners
    validator = Validator()
    validator.add_constraint_handler(on_constraint_event)
    try:
        with io.FileIO(input_file, 'rb') as in_stream:
            # Open input document
            # If a password is required, use Open(inStr, password)
            with Document.open(in_stream) as document:
                print("Validation Constraints")
                results = validator.validate(document, profile, signatureSelector)
                print()
                print(f"Signatures validated: {len(results)}")
                print()
                for result in results:
                    field = result.signature_field
                    print(f"{field.field_name} of {field.name}")
                    try:
                        print(f"  - Revision  : {'latest' if field.revision.is_latest else 'intermediate'}")
                    except Exception as ex:
                        print(f"Unable to validate document Revision: {str(ex)}")
                    print_signature_content(result.signature_content, field.is_full_revision_covered)
                    print()
    except Exception as e:
        print(f"Unable to validate file: {e}")



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description=" Extract and validate signature information for all digital signatures in the input document, then print the results to the console.", usage="python ./signatures_validate.py <input_path> [<certificate_directory>]")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("certificate_directory", type=str, nargs="?", default=None)

    # Parse the arguments
    args = parser.parse_args()

    input_file = args.input_path
    cert_dir = args.certificate_directory

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        # Optional: Set your proxy configuration
        # Sdk.set_proxy("http://myproxy:8080")
        validate(input_file, cert_dir)

        print(f"Signatures validated successfully")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)