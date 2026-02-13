# Pdftools Sample Code Repository

This repository contains runnable code samples demonstrating how to use the **Pdftools SDK** for common PDF processing tasks such as conversion, merging, signing, and validation, as well as the **Pdftools Toolbox** for more advanced and detailed PDF manipulation. It offers implementations for various use cases across multiple programming languages and is designed to assist developers in seamlessly integrating PDF functionalities into their applications.

The samples are intended to help you get started quickly and to serve as a practical reference when integrating the Pdftools SDK or Pdftools Toolbox into your own applications.

**Important:** All samples in this repository require a valid **Pdftools license key** in order to run. If you do not yet have a license, please create a user account at [portal.pdf-tools.com](https://portal.pdf-tools.com/) to request a trial key for evaluation purposes.

---

## Organization of samples

At the top level, you can choose between **Pdftools SDK** samples and **Pdftools Toolbox** samples.
Within each of these areas, the samples are organized **by programming language**.

Each sample folder contains:
- A language-specific `README.md` explaining setup and prerequisites
- Multiple **self-contained sample folders**
- Each sample folder includes:
  - Source code
  - PDF test files
  - A sample-specific `README.md` explaining what the sample does and how to run it

## Repository structure

This repository has the following structure:

```
/pdftools_sdk
  ├── <programming-language>
      ├── /<use-case-folder> 
          ├── README.md
              input.pdf
              <sample-code-and-config>

/pdftools_toolbox 
  ├── <programming-language>
      ├── /<use-case-folder> 
          ├── README.md                
              input.pdf                
              <sample-code-and-config>
```

## Getting started

1. Clone this repository to your local machine:
    ```bash
    git clone https://github.com/pdf-tools/components-code-sample-hub.git
    cd components-code-sample-hub.git
    ```
