About this kit
==============

This kit contains the SetOpenDestination sample for the PdfTools SDK for Java. The Pdftools SDK is a comprehensive development library that lets developers integrate advanced PDF functionalities into in-house applications. Find more information about this kit in Pdftools [documentation portal](https://www.pdf-tools.com/docs/).

By downloading and using this kit, you accept PDF Tools AG's [license agreement](https://www.pdf-tools.com/license-agreement/), [privacy policy](https://www.pdf-tools.com/privacy-policy/), and allow PDF Tools AG to track your usage data.

## Prerequisites

Before importing the project, ensure you have the following installed on your system:

1. **Java Development Kit (JDK)**
2. **Eclipse IDE** or **IntelliJ IDEA**
3. **Maven** and/or **Gradle** installed if you want to run the program from the command line (optional, as the IDEs handle this).

## Importing the Project

### Using Eclipse

#### Importing as a Maven Project

1. Open **Eclipse**.
2. Navigate to **File** > **Import**.
3. Select **Maven** > **Existing Maven Projects** and click **Next**.
4. Browse to the project's root directory and click **Finish**.

#### Importing as a Gradle Project

1. Open **Eclipse**.
2. Navigate to **File** > **Import**.
3. Select **Gradle** > **Existing Gradle Project** and click **Next**.
4. Browse to the project's root directory and click **Finish**.

### Using IntelliJ IDEA

1. Open **IntelliJ IDEA**.
2. Go to **File** > **Open**.
3. Select the project's root directory.
4. IntelliJ IDEA will automatically detect both `pom.xml` and `build.gradle` files in the directory.
5. IntelliJ will prompt you to choose whether to import the project as a **Maven** or **Gradle** project. Select your preferred option.
6. Follow the on-screen instructions to configure the project.

### Notes for IntelliJ IDEA

- Ensure that the IDE downloads the necessary dependencies by enabling the auto-import feature for Maven/Gradle.
- You can verify and modify the build system settings in **File** > **Project Structure**.

### Running the Project from an IDE

#### Eclipse

1. Open **Eclipse** and ensure the project is fully imported.
2. In the **Package Explorer**, locate the main class containing the `main` method.
3. Right-click the file containing the `main` method and select **Run As** > **Java Application**.
4. Eclipse will build and run the project automatically.

#### IntelliJ IDEA

1. Open **IntelliJ IDEA** and ensure the project is fully imported.
2. Navigate to the **Project Explorer** window and locate the main class containing the `main` method.
3. Right-click the file containing the `main` method and select **Run 'ToolboxSetOpenDestination'**.
4. IntelliJ IDEA will build and run the project automatically.

#### Alternative (Both IDEs):
- Use the **Run/Debug Configurations** to create a custom run configuration if needed.


## Building and Running the Project from the command line

### Using Maven

  ```bash
  mvn clean install
  mvn exec:java -Dexec.mainClass="ToolboxSetOpenDestination.ToolboxSetOpenDestination" -Dexec.args="<inputPath> <pageNumber> <outputPath>"
  ```

### Using Gradle

  ```bash
  gradle build
  ./gradlew run --args="<inputPath> <pageNumber> <outputPath>"
  ```

Native library: Either way the library PdfTools_Toolbox.dll/.so/.dylib matching your operating system and the bitness of your JRE is loaded automatically by the sample.

## Licensing

- **Pdftools SDK** doesn't require a license key for evaluation. Without a license key, the SDK adds a watermark to output files.
- **Toolbox add-on** requires a trial or full license key to run. Without a valid license key, processing fails.

**Important:** Toolbox add-on processing fails without a valid license key.

To get a trial license key, create a user account at the [Pdftools portal](https://portal.pdf-tools.com/). For more information, refer to [Trial license overview](https://www.pdf-tools.com/docs/licenses/products/pdf-tools-sdk-license/#trial-license-overview).

## Technical Support

Do you need technical support or want to report an issue?
Open a ticket through the [support form](https://www.pdf-tools.com/docs/support/).