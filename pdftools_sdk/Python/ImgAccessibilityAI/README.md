About this kit
==============

This kit contains the ImgAccessibilityAI sample for the Pdftools SDK for Python. The Pdftools SDK is a comprehensive development library that lets developers integrate advanced PDF functionalities into in-house applications. Find more information about this kit in Pdftools [documentation portal](https://www.pdf-tools.com/docs/).

By downloading and using this kit, you accept PDF Tools AG's [license agreement](https://www.pdf-tools.com/license-agreement/), [privacy policy](https://www.pdf-tools.com/privacy-policy/), and allow PDF Tools AG to track your usage data.

## Preparing steps for usage with OpenAI API
**Create an OpenAI Account**

Sign up for an account at the [OpenAI website](https://openai.com/).

**Generate API Key**

After gaining access, generate an API key from the API dashboard. This key is essential for authenticating the API requests.

**Setting the OpenAI API key**

In order to set the OpenAI API key you generated, replace `***insert-open-ai-api-key***` in the code or alternatively set up a new environment variable with the name `OPENAI_API_KEY`. 

## Quick start

**Prerequisite:**

- Python 3.7 or higher
- On some systems, mostly Linux based ones, only Python 3 is installed and `python` is not aliased, so on these systems you need to run `python3` instead.

**Installation**

Install the package for the Pdftools SDK by executing:

```bash
pip install pdftools_sdk
```

To install the OpenAI package for Python, execute the following command in your terminal:
```
pip install openai
``` 

**Usage:**

To run the sample, use the following command:

```bash
python ./img_accessibility_a_i.py <input_path> [<input_path2> ...] <output_path>
```

To get help, run the following command:

```bash
python ./img_accessibility_a_i.py -h
```

**Cross-Platform Compatibility:**

This sample is designed to be cross-platform compatible. It has been tested on Linux, macOS, and Windows.

## Licensing

- **Pdftools SDK** doesn't require a license key for evaluation. Without a license key, the SDK adds a watermark to output files.
- **Toolbox add-on** requires a trial or full license key to run. Without a valid license key, processing fails.

**Important:** Toolbox add-on processing fails without a valid license key.

To get a trial license key, create a user account at the [Pdftools portal](https://portal.pdf-tools.com/). For more information, refer to [Trial license overview](https://www.pdf-tools.com/docs/licenses/products/pdf-tools-sdk-license/#trial-license-overview).

## Technical Support

Do you need technical support or want to report an issue?
Open a ticket through the [support form](https://www.pdf-tools.com/docs/support/).