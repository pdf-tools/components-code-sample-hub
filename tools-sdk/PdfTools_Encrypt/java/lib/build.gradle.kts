plugins {
    // Apply the java-library plugin for API and implementation separation.
    `java-library`
    id("com.google.osdetector") version "1.7.3"
    id("application")
}

application {
    mainClass.set("PdfToolsEncrypt.PdfToolsEncrypt")
}
repositories {
    // Use Maven Central for resolving dependencies.
    mavenCentral()
} 

java {
    sourceSets {
        main {
            java {
                srcDir("lib/src/main/java")
            }
        }
    }
}


dependencies {
    implementation("com.pdftools:pdftools-sdk:1.5.0")

    val osDetector = project.extensions.getByType(com.google.gradle.osdetector.OsDetector::class.java)
    val osClassifier = osDetector.classifier

    if (osClassifier == "windows-x86_64") {
        runtimeOnly("com.pdftools:pdftools-sdk:1.5.0:win-x64@dll")
    } else if (osClassifier == "windows-x86") {
        runtimeOnly("com.pdftools:pdftools-sdk:1.5.0:win-x86@dll")
    } else if (osClassifier == "windows-arm64") {
        runtimeOnly("com.pdftools:pdftools-sdk:1.5.0:win-arm64@dll")
    } else if (osClassifier == "linux-x86_64") {
        runtimeOnly("com.pdftools:pdftools-sdk:1.5.0:linux-x64@so")
    } else if (osClassifier == "linux-x86_64-glibc2.12") {
        runtimeOnly("com.pdftools:pdftools-sdk:1.5.0:linux-x64-glibc2.12@so")
    } else if (osClassifier == "osx-x86_64") {
        runtimeOnly("com.pdftools:pdftools-sdk:1.5.0:osx-x64@dylib")
    } else if (osClassifier == "osx-arm64") {
        runtimeOnly("com.pdftools:pdftools-sdk:1.5.0:osx-arm64@dylib")
    } else {
        throw GradleException("No matching OS classifier found")
    }
}