# Pdftools Sample Code Repository

This repository contains runnable code samples demonstrating how to use the **Pdftools SDK** for common PDF processing tasks such as conversion, merging, signing, and validation, as well as the **Pdftools Toolbox** for more advanced and detailed PDF manipulation. It offers implementations for various use cases across multiple programming languages and is designed to assist developers in seamlessly integrating PDF functionalities into their applications.

PDF processing code samples for PDF conversion, archiving, merging, digital signatures, validation, text extraction, and advanced PDF manipulation. Run code samples in C, .NET, Java, Python, and Visual Basic.

This repository covers two PDF libraries:
- **Pdftools SDK**: high-level PDF processing such as conversion, optimization, merging, signing, and validation.
- **Toolbox add-on**: low-level PDF manipulation such as creating documents from scratch, editing content, extracting information, and managing metadata.

## Licensing

- **Pdftools SDK** doesn't require a license key for evaluation. Without a license key, the SDK adds a watermark to output files.
- **Toolbox add-on** requires a trial or full license key to run. Without a valid license key, processing fails.

**Important:** Toolbox add-on processing fails without a valid license key.

To get a trial license key, create a user account at the [Pdftools portal](https://portal.pdf-tools.com/). For more information, refer to [Trial license overview](https://www.pdf-tools.com/docs/licenses/products/pdf-tools-sdk-license/#trial-license-overview).


## Organization of samples

At the top level, you can choose between **Pdftools SDK** samples and **Toolbox add-on**  samples.
Within each of these product areas, you can find the samples grouped **by programming language**.

Each language folder contains:
- A `README.md` explaining setup and prerequisites
- Self-contained sample folders, each with:
    - Source code
    - PDF test files
    - A `README.md` explaining what the sample does and how to run it

## Repository structure

This repository has the following structure:

```
/pdftools_sdk
  ├── PROGRAMMING_LANGUAGE
      ├── /USE_CASE_FOLDER 
          ├── README.md
              input.pdf
              SAMPLE_CODE_AND_CONFIG

/pdftools_toolbox 
  ├── PROGRAMMING_LANGUAGE
      ├── /USE_CASE_FOLDER
          ├── README.md                
              input.pdf                
              SAMPLE_CODE_AND_CONFIG
```

## Getting started

1. Clone this repository to your local machine:
    ```bash
    git clone https://github.com/pdf-tools/components-code-sample-hub.git
    cd components-code-sample-hub.git
    ```
1. Navigate to the sample you want to run (for example, `components-code-sample-hub/pdftools_sdk/java/`).
1. Follow the instructions in the `README.md` of that folder.
