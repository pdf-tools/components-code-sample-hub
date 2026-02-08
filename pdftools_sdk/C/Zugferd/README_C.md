About this kit
==============

This kit contains the Zugferd sample for the Pdftools SDK for C. The Pdftools SDK is a comprehensive development library that lets developers integrate advanced PDF functionalities into in-house applications. Find more information about this kit in Pdftools [documentation portal](https://www.pdf-tools.com/docs/).

By downloading and using this kit, you accept PDF Tools AG's [license agreement](https://www.pdf-tools.com/license-agreement/), [privacy policy](https://www.pdf-tools.com/privacy-policy/), and allow PDF Tools AG to track your usage data.

## Quick start

How to execute this sample:

**Prerequisite:**

- CMake version at least VERSION 3.16

Use CMake to generate a make file which in turn can be used to compile the sample `pdftoolszugferd`.
The input configuration file for CMake is `CMakeLists.txt`.
Native libraries are linked and header files are included automatically. Supported platforms are Windows, Linux and MacOS.

**How it works:**

1. navigate to where `CMakeLists.txt` resides
2. execute: `cmake .`
3. execute: `cmake --build .`
4. execute sample: `./pdftoolszugferd <inputPath> <invoicePath> <outputPath>`

## Licensing

- **Pdftools SDK** doesn't require a license key for evaluation. Without a license key, the SDK adds a watermark to output files.
- **Toolbox add-on** requires a trial or full license key to run. Without a valid license key, processing fails.

**Important:** Toolbox add-on processing fails without a valid license key.

To get a trial license key, create a user account at the [Pdftools portal](https://portal.pdf-tools.com/). For more information, refer to [Trial license overview](https://www.pdf-tools.com/docs/licenses/products/pdf-tools-sdk-license/#trial-license-overview).

## Technical Support

Do you need technical support or want to report an issue?
Open a ticket through the [support form](https://www.pdf-tools.com/docs/support/).