"""
File: chat_with_pdf.py
Usage: python ./chat_with_pdf.py <input_path> <question>
Author: PDF Tools AG
Copyright: Copyright (C) 2024 PDF Tools AG, Switzerland

Chat with a PDF

"""

from openai import OpenAI
from pdftools_sdk.pdf import Document
from pdftools_sdk.extraction import Extractor, TextOptions, TextExtractionFormat

import argparse, io

def extract_text(input_file_path: str) -> str:
    # Open input document
    with open(input_file_path, 'rb') as in_stream:
        with Document.open(in_stream) as in_doc:
            # Set extraction options
            options = TextOptions()
            options.extraction_format = TextExtractionFormat.DOCUMENT_ORDER
            # Extract text from PDF
            extractor = Extractor()
            with io.BytesIO() as output_stream:
                extractor.extract_text(in_doc, output_stream, options)
                return output_stream.getvalue().decode('utf-8')


def answer_question(text: str, question: str) -> str:
    client = OpenAI(api_key="***insert-open-ai-api-key***")
    prompt = (
        "You are a helpful assistant. Use the provided text to answer the "
        "question. If the answer is not in the text, say 'Not found'.\n\n"
        f"Text: {text}\nQuestion: {question}\nAnswer:"
    )
    response = client.chat.completions.create(
        model="gpt-4",
        messages=[
            {"role": "system", "content": "You answer questions based on text."},
            {"role": "user", "content": prompt}
        ],
    )
    return response.choices[0].message.content.strip()



if __name__ == "__main__":
    # Create the parser
    parser = argparse.ArgumentParser(description="Ask a question about a PDF and get an answer on the console.", usage="python ./chat_with_pdf.py <input_path> <question>")

    # Add arguments
    parser.add_argument("input_path", type=str)
    parser.add_argument("question", type=str)

    # Parse the arguments
    args = parser.parse_args()

    input_path = args.input_path
    question = args.question

    try:
        # By default, a test license key is active. In this case, a watermark is added to the output. 
        # If you have a license key, please uncomment the following call and set the license key.
        # from pdftools_sdk.sdk import Sdk
        # Sdk.initialize("LICENSE-KEY")

        extracted_text = extract_text(input_path)
        answer = answer_question(extracted_text, question)
        print(f"Question: {question}")
        print(f"Answer: {answer}")

        print(f"Finished chatting with PDF.")

        exit(0)
    except Exception as e:
        print(f"An error occurred: {e}")
        exit(1)