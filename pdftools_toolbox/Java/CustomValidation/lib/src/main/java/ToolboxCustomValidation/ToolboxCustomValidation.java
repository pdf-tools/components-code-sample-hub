/****************************************************************************
 *
 * File:            toolboxcustomvalidation.java
 *
 * Usage:           java toolboxcustomvalidation <inputPath> <iniPath> [<pdfPassword>]
 *                  Example: in.pdf properties.ini \"my_password\"
 *                  
 * Title:           Validate custom properties of a PDF file
 *                  
 * Description:     Validates the properties defined in a custom properties
 *                  file. The validation results are written to the console.
 *                  
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2026 PDF Tools AG, Switzerland
 *                  Permission to use, copy, modify, and distribute this
 *                  software and its documentation for any purpose and without
 *                  fee is hereby granted, provided that the above copyright
 *                  notice appear in all copies and that both that copyright
 *                  notice and this permission notice appear in supporting
 *                  documentation. This software is provided "as is" without
 *                  express or implied warranty.
 *
 ***************************************************************************/

package ToolboxCustomValidation;

import java.util.stream.Collectors;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.pdftools.toolbox.ConformanceException;
import com.pdftools.toolbox.CorruptException;
import com.pdftools.toolbox.PasswordException;
import com.pdftools.toolbox.pdf.content.ContentElement;
import com.pdftools.toolbox.pdf.content.ContentExtractor;
import com.pdftools.toolbox.pdf.content.Text;
import com.pdftools.toolbox.pdf.content.TextElement;
import com.pdftools.toolbox.pdf.content.TextFragment;
import com.pdftools.toolbox.pdf.content.UngroupingSelection;
import com.pdftools.toolbox.pdf.Document;
import com.pdftools.toolbox.pdf.Page;
import com.pdftools.toolbox.pdf.Permission;
import com.pdftools.toolbox.pdf.Conformance;
import com.pdftools.toolbox.Sdk;
import com.pdftools.toolbox.sys.FileStream;
import com.pdftools.toolbox.ToolboxException;
import com.pdftools.toolbox.UnsupportedFeatureException;

public class ToolboxCustomValidation {

    static void usage() {
        System.out.println("Usage: java toolboxcustomvalidation <inputPath> <iniPath> [<pdfPassword>]");
        System.out.println("       Example: in.pdf properties.ini \"my_password\"");

    }

    public static void main(String[] args) {
        // Check command line parameters
        if (args.length < 2 || args.length > 3) {
            usage();
            return;
        }

        try {
            // Set and check license key. If the license key is not valid, an exception is thrown.
            Sdk.initialize("LICENSE-KEY", null);

            String pdfPath = args[0];
            String iniPath = args[1];
            String password = null;
            if (args.length == 3)
            	password = args[2];

            IniFile iniFile = new IniFile(iniPath);
            DocumentValidator documentValidator = new DocumentValidator(iniFile, pdfPath, password);

            try {
               if (documentValidator.validateDocument())
                    System.out.println("\nThe document does conform the specified properties.");
                else
                    System.out.println("\nThe document does not conform the specified properties.");
            }
            catch(Exception e) {
            	System.out.println("The document could not be validated. The following error happened: " + e.getMessage());

                System.exit(-1);
            }


            System.out.println("Execution successful.");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static class IniFile {
        private final Map<String, Map<String, String>> sections = new LinkedHashMap<>();

        public IniFile(String path) throws IOException {
            load(path);
        }

        private void load(String path) throws IOException {
            try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
                String currentSection = null;
                String line;

                while ((line = reader.readLine()) != null) {
                    line = line.trim();

                    if (line.isEmpty() || line.startsWith(";") || line.startsWith("#")) {
                        // Skip empty lines and comments
                        continue;
                    }

                    if (line.startsWith("[") && line.endsWith("]")) {
                        // New section
                        currentSection = line.substring(1, line.length() - 1).trim();
                        sections.putIfAbsent(currentSection, new LinkedHashMap<>());
                    } else if (currentSection != null) {
                        // Key-value pair within a section
                        String[] keyValue = line.split("=", 2);
                        if (keyValue.length == 2) {
                            sections.get(currentSection).put(keyValue[0].trim(), keyValue[1].trim());
                        }
                    }
                }
            }
        }

        public String getValue(String section, String key, String defaultValue) {
            Map<String, String> sectionData = sections.get(section);
            if (sectionData != null) {
                return sectionData.getOrDefault(key, defaultValue);
            }
            return defaultValue;
        }

        public String getValue(String section, String key) {
            return getValue(section, key, null);
        }

        public List<String> getKeysMatchingPattern(String section, String pattern) {
            List<String> matchingKeys = new ArrayList<>();

            Map<String, String> sectionData = sections.get(section);
            if (sectionData != null) {
                Pattern regexPattern = Pattern.compile(pattern, Pattern.CASE_INSENSITIVE);
                for (String key : sectionData.keySet()) {
                    Matcher matcher = regexPattern.matcher(key);
                    if (matcher.find()) {
                        matchingKeys.add(sectionData.get(key));
                    }
                }
            }

            return matchingKeys;
        }
    }

    public static class DocumentValidator {

        private final String inputPath;
        private String pdfPassword;

        // Tolerance used for size comparison: default 3pt
        private String sizeTolerance = "3.0";
        private String iniMaxPageSize;
        private String iniMaxPdfVersionStr;
        private String iniEncryption;
        private String iniFileSize;
        private String iniEmbedding;
        private final List<String> embeddingExceptionFonts;


        public DocumentValidator(IniFile iniFile, String inputPath, String pdfPassword) {
            this.inputPath = inputPath;
            this.pdfPassword = pdfPassword;

            // Extract values from INI file
            String iniSizeTolerance = iniFile.getValue("Pages", "SizeTolerance");
            this.sizeTolerance = (iniSizeTolerance != null && !iniSizeTolerance.isEmpty()) ? iniSizeTolerance : this.sizeTolerance;
            this.iniMaxPageSize = iniFile.getValue("Pages", "MaxPageSize");
            this.iniMaxPdfVersionStr = iniFile.getValue("File", "MaxPdfVersion");
            this.iniEncryption = iniFile.getValue("File", "Encryption");
            this.iniFileSize = iniFile.getValue("File", "FileSize");
            this.iniEmbedding = iniFile.getValue("Fonts", "Embedding");
            this.embeddingExceptionFonts = iniFile.getKeysMatchingPattern("Fonts", "EmbeddingExcFont\\d+");
        }

        public boolean validateDocument() throws IOException, CorruptException, ConformanceException, UnsupportedFeatureException, ToolboxException {
            boolean isValid = validateFileSize(inputPath);

            try (FileStream inStream = new FileStream(inputPath, FileStream.Mode.READ_ONLY);
                Document inDoc = Document.open(inStream, pdfPassword)) {

                isValid &= validateConformance(inDoc.getConformance());
                isValid &= validateEncryption(inDoc.getPermissions());
                isValid &= validatePagesSize(inDoc);
                isValid &= validateFonts(inDoc);
            }
            catch(PasswordException e) {
            	if (pdfPassword == null)
            		System.out.println("The content of the document could not be validated as it is password protected. Please provide a password.");
            	else
            		System.out.println("The content of the document could not be validated as the password provided is not correct.");

                return false;
            }

            return isValid;
        }

        private boolean validateFileSize(String inputPath) {
            File file = new File(inputPath);
            double fileSizeInMB = file.length() / (1024.0 * 1024.0);

            if (iniFileSize != null) {
                double iniFileSizeInMB = Double.parseDouble(iniFileSize);
                if (fileSizeInMB <= iniFileSizeInMB) {
                    System.out.println("The PDF file size does not exceed the specified custom limit.");
                    return true;
                } else {
                    System.out.println("The PDF file size exceeds the specified custom limit.");
                    return false;
                }
            }
            return true;
        }

        private boolean validateConformance(Conformance currentConformance) {
            if (iniMaxPdfVersionStr != null) {
                if (ConformanceValidator.validateConformance(iniMaxPdfVersionStr, currentConformance)) {
                    System.out.println("The PDF version does not exceed the specified custom maximum version.");
                    return true;
                } else {
                    System.out.println("The PDF version exceeds the specified custom maximum version.");
                    return false;
                }
            }

            return true;
        }

        private boolean validateEncryption(EnumSet<Permission> enumSet) {
            if (iniEncryption != null) {
                boolean isEncrypted = enumSet != null;

                if ("true".equalsIgnoreCase(iniEncryption) && !isEncrypted) {
                    System.out.println("Encryption not conform: the PDF file is not encrypted. The custom encryption value specifies that the PDF file should be encrypted.");
                    return false;
                } else if ("false".equalsIgnoreCase(iniEncryption) && isEncrypted) {
                    System.out.println("Encryption not conform: the PDF file is encrypted. The custom encryption value specifies that the PDF file should not be encrypted.");
                    return false;
                } else {
                    System.out.println("The PDF encryption is conform to the specified custom value.");
                    return true;
                }
            }
            return true;
        }

        private boolean validatePagesSize(Document inDoc) {
            boolean isValid = true;

            if (iniMaxPageSize != null) {
                int pageNumber = 0;
                for (Page page : inDoc.getPages()) {
                    pageNumber++;
                    com.pdftools.toolbox.geometry.real.Size pageSize = page.getSize();
                    isValid &= validatePageSize(pageNumber, pageSize);
                }
            }

            return isValid;
        }

        private boolean validatePageSize(int pageNumber, com.pdftools.toolbox.geometry.real.Size pageSize) {
            if (iniMaxPageSize != null) {
                PageSizeValidator validator = new PageSizeValidator(iniMaxPageSize, sizeTolerance);
                if (validator.validatePageSize(pageSize.getWidth(), pageSize.getHeight())) {
                    System.out.println(String.format("The size of page %d is within the specified custom maximum page size value.", pageNumber));
                    return true;
                } else {
                    System.out.println(String.format("The size of page %d exceeds the specified custom maximum page size value.", pageNumber));
                    return false;
                }
            }

            return true;
        }

        public boolean validateFonts(Document inDoc) throws CorruptException, IOException {
            boolean isValid = true;

            if (iniEmbedding != null)
            {
                boolean embeddingRequired = "true".equalsIgnoreCase(iniEmbedding);
	            int pageNumber = 0;

	            for (Page page : inDoc.getPages()) {
	                pageNumber++;
	                ContentExtractor extractor = new ContentExtractor(page.getContent());
	                extractor.setUngrouping(UngroupingSelection.ALL);

	                for (ContentElement element : extractor) {
	                    if (element instanceof TextElement) {
	                        TextElement textElement = (TextElement) element;
	                        Text text = textElement.getText();

	                        for (int iFragment = 0; iFragment < text.size(); iFragment++) {
	                        	TextFragment currFragment = text.get(iFragment);
	                            String fontName = currFragment.getFont().getBaseFont();
	                            boolean isEmbedded = currFragment.getFont().getIsEmbedded();

	                            // Check if the font is in the exception list
	                            boolean isCurrentFontAnException = embeddingExceptionFonts.stream()
	                                .anyMatch(exception -> Pattern.compile(exception.replace("*", ".*"), Pattern.CASE_INSENSITIVE).matcher(fontName).matches());

                                // Validate based on the embedding setting
                                // _iniEmbedding = true => The font has to be embedded or it should appear in the exception list
                                // _iniEmbedding = false => The font cannot be embedded or it should appear in the exception list
                                if ((embeddingRequired && !isEmbedded && !isCurrentFontAnException) || (!embeddingRequired && isEmbedded && !isCurrentFontAnException)) {
                                    isValid = false;
                                    String statusText = embeddingRequired ? "be embedded" : "not be embedded";
                                    System.out.println("The font '" + fontName + "' on page " + pageNumber + " should " + statusText + " as specified by the property 'Embedding' or it should be added to the list of exceptions.");
                                }
                                else {
                                    String statusText = embeddingRequired != isEmbedded ? "in the exception list" : isEmbedded ? "embedded" : "not embedded";
                                    System.out.println("The font '" + fontName + "' on page " + pageNumber + " is conform to the 'Embedding' property as it is " + statusText + ".");
                                }
                            }
	                    }
	                }
	            }
            }

            return isValid;
        }
    }

    public static class ConformanceValidator {
        private static final Map<String, Conformance> versionMap = new HashMap<>();

        static {
            versionMap.put("1.0", Conformance.PDF10);
            versionMap.put("1.1", Conformance.PDF11);
            versionMap.put("1.2", Conformance.PDF12);
            versionMap.put("1.3", Conformance.PDF13);
            versionMap.put("1.4", Conformance.PDF14);
            versionMap.put("1.5", Conformance.PDF15);
            versionMap.put("1.6", Conformance.PDF16);
            versionMap.put("1.7", Conformance.PDF17);
            versionMap.put("2.0", Conformance.PDF20);
        }

        public static Conformance parseVersionString(String version) {
            // Extract the major and minor version numbers (e.g., "1.7")
            String[] versionParts = version.split("\\.");
            if (versionParts.length == 2) {
                String majorMinorVersion = versionParts[0] + "." + versionParts[1];
                Conformance conformance = versionMap.get(majorMinorVersion);
                if (conformance != null) {
                    return conformance;
                }
            }

            throw new IllegalArgumentException("Unsupported version or conformance level: " + version);
        }

        public static boolean validateConformance(String maxPdfVersionStr, Conformance currentConformance) {
            Conformance maxPdfConformance = parseVersionString(maxPdfVersionStr);
            // Convert the current conformance level to the corresponding PDF version (Major.Minor) as it can be based on the PDF/A version
            Conformance currentConformanceVersion = getVersionFromConformance(currentConformance);

            return currentConformanceVersion.ordinal() <= maxPdfConformance.ordinal();
        }

        public static Conformance getVersionFromConformance(Conformance conformance) {
         	if (versionMap.containsValue(conformance)) {
        		return conformance;
        	}

           switch (conformance) {
                case PDF_A1_A:
                case PDF_A1_B:
                    return Conformance.PDF14; // PDF/A-1 is based on PDF 1.4

                case PDF_A2_A:
                case PDF_A2_B:
                case PDF_A2_U:
                case PDF_A3_A:
                case PDF_A3_B:
                case PDF_A3_U:
                    return Conformance.PDF17; // PDF/A-2 and PDF/A-3 are based on PDF 1.7

                default:
                    throw new IllegalArgumentException("Unsupported conformance level: " + conformance);
            }
        }
    }

    public static class PageSizeValidator {
        private final double maxWidth;
        private final double maxHeight;
        private final double sizeTolerance;

        // Named page sizes like "Letter", "A4", etc.
        private static final Map<String, double[]> NAMED_PAGE_SIZES = new HashMap<>();

        static {
            NAMED_PAGE_SIZES.put("Letter", new double[]{612, 792}); // 8.5 x 11 inches in points
            NAMED_PAGE_SIZES.put("A0", new double[]{2384, 3370});
            NAMED_PAGE_SIZES.put("A1", new double[]{1684, 2384});
            NAMED_PAGE_SIZES.put("A2", new double[]{1191, 1684});
            NAMED_PAGE_SIZES.put("A3", new double[]{842, 1191});
            NAMED_PAGE_SIZES.put("A4", new double[]{595, 842});    // 210 x 297 mm in points
            NAMED_PAGE_SIZES.put("A5", new double[]{420, 595});
            NAMED_PAGE_SIZES.put("A6", new double[]{298, 420});
            NAMED_PAGE_SIZES.put("A7", new double[]{210, 298});
            NAMED_PAGE_SIZES.put("A8", new double[]{147, 210});
            NAMED_PAGE_SIZES.put("A9", new double[]{105, 147});
            NAMED_PAGE_SIZES.put("A10", new double[]{74, 105});
            NAMED_PAGE_SIZES.put("DL", new double[]{283, 595});    // 99 x 210 mm in points
        }

        public PageSizeValidator(String maxPageSize, String sizeToleranceStr) {
            double[] size = parsePageSize(maxPageSize);
            this.maxWidth = size[0];
            this.maxHeight = size[1];
            this.sizeTolerance = parseSizeTolerance(sizeToleranceStr);
        }

        private double[] parsePageSize(String maxPageSize) {
            if (maxPageSize == null || maxPageSize.isEmpty()) {
                throw new IllegalArgumentException("MaxPageSize cannot be null or empty");
            }

            // First, check if it's a named size
            if (NAMED_PAGE_SIZES.containsKey(maxPageSize)) {
                return NAMED_PAGE_SIZES.get(maxPageSize);
            }

            // If not a named size, try to parse it as a custom size
            Pattern pattern = Pattern.compile("(\\d+(\\.\\d+)?)\\s*x\\s*(\\d+(\\.\\d+)?)(\\s*(pt|in|cm|mm))?", Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher(maxPageSize);
            if (!matcher.matches()) {
                throw new IllegalArgumentException("Invalid MaxPageSize format: " + maxPageSize);
            }

            double width = Double.parseDouble(matcher.group(1));
            double height = Double.parseDouble(matcher.group(3));
            String unit = matcher.group(6).toLowerCase();

            switch (unit) {
                case "in":
                    return new double[]{width * 72, height * 72};
                case "cm":
                    return new double[]{width * 28.3465, height * 28.3465};
                case "mm":
                    return new double[]{width * 2.83465, height * 2.83465};
                case "pt":
                default:
                    return new double[]{width, height};
            }
        }

        private double parseSizeTolerance(String sizeToleranceStr) {
            if (sizeToleranceStr == null || sizeToleranceStr.isEmpty()) {
                return 3; // Default tolerance in points
            }

            Pattern pattern = Pattern.compile("(\\d+(\\.\\d+)?)\\s*(%)?", Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher(sizeToleranceStr);
            if (!matcher.matches()) {
                throw new IllegalArgumentException("Invalid SizeTolerance format: " + sizeToleranceStr);
            }

            double value = Double.parseDouble(matcher.group(1));
            return matcher.group(3) != null ? value / 100.0 : value; // Percentage tolerance or direct value
        }

        public boolean validatePageSize(double actualWidth, double actualHeight) {
            // Check both portrait and landscape orientations
            boolean isValid = (actualWidth <= maxWidth + sizeTolerance && actualHeight <= maxHeight + sizeTolerance) ||
                              (actualHeight <= maxWidth + sizeTolerance && actualWidth <= maxHeight + sizeTolerance);

            return isValid;
        }
    }
}