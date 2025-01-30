About this kit
==============

This kit contains the Encrypt samples for the Pdftools SDK for different languages.
The Pdftools SDK is a comprehensive development library that lets developers integrate advanced PDF functionalities into in-house applications. Find more information about this kit in Pdftools [documentation portal](https://www.pdf-tools.com/docs/).

By cloning and using this kit, you accept PDF Tools AG's [license agreement](https://www.pdf-tools.com/license-agreement/), [privacy policy](https://www.pdf-tools.com/privacy-policy/), and allow PDF Tools AG to track your usage data.

## Quick start

### Prerequisites
- Supported Programming Languages:
  - **C**: Requires CMake 3.16 or higher
           Use CMake to generate a make file which in turn can be used to compile the sample `pdftoolsencrypt`.
           The input configuration file for CMake is `c/CMakeLists.txt`.
           Native libraries are linked and header files are included automatically. Supported platforms are Windows, Linux and MacOS.
  - **C#**: Ensure that a supported version of .NET is installed:
            .NET and .NET Core: 2.0, 2.1, 2.2, 3.0, 3.1, 5.0, 6.0, 7.0, 8.0
            .NET Framework: 4.6.1, 4.6.2, 4.7, 4.7.1, 4.7.2, 4.8, 4.8.1
  - **Python**: Python 3.7 or higher
                On some systems, mostly Linux based ones, only Python 3 is installed and `python` is not aliased, so on these systems you need to run `python3` instead.
- Ensure all dependencies (e.g., libraries) for the selected language are properly installed.


### Running the Samples

1. Clone the repository and navigate to the desired sample folder.
2. Follow the language-specific instructions below:

#### **C**
1. navigate to the `c` folder to find the file `CMakeLists.txt`
2. Execute the following command lines
    ```bash
    cmake .
    cmake --build .
    ./pdftoolsencrypt <password> <inputPath> <outputPath>
    ```

#### **C#**

**Via command line:**

1. Execute in the `cs` sample folder:
    ```
    `dotnet run --framework net6.0 --project PdfToolsEncrypt.csproj <password> <inputPath> <outputPath>`
    ```

**Via Visual Studio:**

1. At least Visual Studio 2022 installed
2. Double click on `PdfToolsEncrypt.csproj`
3. Compile project in Visual Studio
4. Run:
    ```
    `PdfToolsEncrypt.exe <password> <inputPath> <outputPath>`
    ```

#### **Java**

**Via Eclipse:**

1. Import present .project file into Eclipse. The source file `PdfToolsEncrypt.java` is compiled automatically.
2. Start new Java application and pass arguments of the form `<password> <inputPath> <outputPath>`.

**Via command line:**

1. Compile the Java source file:
    ```
    `javac -cp jar/com.pdftools.jar;. PdfToolsEncrypt.java`
    ```
2. Execute:
    ```
    `java -cp jar/com.pdftools.jar;bin;. PdfToolsEncrypt <password> <inputPath> <outputPath>`
    ```

Native library: Either way the library PdfToolsSdk.dll/.so/.dylib matching your operating system and the bitness of your JRE is loaded automatically by the sample.

#### **Python**

**Installation**

Install the package for the Pdftools SDK by executing:

    ```bash
    pip install pip install https://pdftools-public-downloads-production.s3.eu-west-1.amazonaws.com/productkits/PDFSDK/latest/pdftools_sdk-latest.tar.gz
    ```

**Via Command line:**

To run the sample, use the following command:

    ```bash
    python ./encrypt.py <password> <input_path> <output_path>
    ```

To get help, run the following command:

    ```bash
    python ./encrypt.py -h
    ```

**Cross-Platform Compatibility:**

This sample is designed to be cross-platform compatible. It has been tested on Linux, macOS and Windows.

## Licensing

This kit requires a license key to leverage its full potential and process documents without a watermark.

Do you need a full product license, a new license key, or an upgrade to your current license, or do you want to ask us anything else? Get in touch with our sales team through the [Contact page](https://www.pdf-tools.com/contact/).

## Technical Support

Do you need technical support or want to report an issue?
Open a ticket through the [support form](https://www.pdf-tools.com/docs/support/).