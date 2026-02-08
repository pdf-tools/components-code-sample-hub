/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           ToolboxCustomValidation <inputPath> <iniPath> [<pdfPassword>]
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

#nullable enable

using PdfTools.Toolbox;
using PdfTools.Toolbox.Geometry.Integer;
using PdfTools.Toolbox.Pdf;
using PdfTools.Toolbox.Pdf.Content;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text.RegularExpressions;

namespace ToolboxCustomValidation
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: ToolboxCustomValidation <inputPath> <iniPath> [<pdfPassword>]");
            Console.WriteLine("       Example: in.pdf properties.ini \"my_password\"");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2 || args.Length > 3)
            {
                Usage();
                return;
            }

            try
            {
                // Set and check license key. If the license key is not valid, an exception is thrown.
                Sdk.Initialize("LICENSE-KEY", null);

                var iniFile = new IniFile(args[1]);
                var password = args.Length == 3 ? args[2] : null;
                var documentValidator = new DocumentValidator(iniFile, args[0], password);

                try
                {
                    if (documentValidator.ValidateDocument())
                        Console.WriteLine("\nThe document does conform the specified properties.");
                    else
                        Console.WriteLine("\nThe document does not conform the specified properties.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine("The document could not be validated. The following error happened: " + ex.Message);
                    return;
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public class IniFile
        {
            private Dictionary<string, Dictionary<string, string>> _data;

            public IniFile(string path)
            {
                _data = new Dictionary<string, Dictionary<string, string>>();
                Load(path);
            }

            private void Load(string path)
            {
                var lines = File.ReadAllLines(path);
                var currentSection = "";

                foreach (var line in lines)
                {
                    var trimmedLine = line.Trim();

                    if (string.IsNullOrEmpty(trimmedLine) || trimmedLine.StartsWith(";") || trimmedLine.StartsWith("#"))
                    {
                        continue; // Skip empty lines and comments
                    }

                    if (trimmedLine.StartsWith("[") && trimmedLine.EndsWith("]"))
                    {
                        currentSection = trimmedLine.Substring(1, trimmedLine.Length - 2).Trim();
                        if (!_data.ContainsKey(currentSection))
                        {
                            _data[currentSection] = new Dictionary<string, string>();
                        }
                        else
                        {
                            throw new FormatException("Duplicate section: " + currentSection);
                        }
                    }
                    else if (currentSection != null)
                    {
                        var keyValuePair = trimmedLine.Split(new[] { '=' });
                        if (keyValuePair.Length == 2)
                        {
                            var key = keyValuePair[0].Trim();
                            var value = keyValuePair[1].Trim();
                            _data[currentSection][key] = value;
                        }
                    }
                }
            }

            public string? GetValue(string section, string key, string? defaultValue = null)
            {
                if (_data.TryGetValue(section, out var sectionData))
                {
                    if (sectionData.TryGetValue(key, out var value))
                    {
                        return value;
                    }
                }
                return defaultValue;
            }

            public List<string> GetKeysMatchingPattern(string section, string pattern)
            {
                var matchingKeys = new List<string>();

                if (_data.TryGetValue(section, out var sectionData))
                {
                    foreach (var key in sectionData.Keys)
                    {
                        if (Regex.IsMatch(key, pattern, RegexOptions.IgnoreCase))
                        {
                            matchingKeys.Add(sectionData[key]);
                        }
                    }
                }

                return matchingKeys;
            }
        }

        public class DocumentValidator
        {
            private readonly IniFile _iniFile;
            private readonly string _inputPath;
            private readonly string? _pdfPassword;

            // Tolerance used for size comparison: default 3pt
            private string _sizeTolerance = "3.0";
            private string? _iniMaxPageSize;
            private string? _iniMaxPdfVersionStr;
            private string? _iniEncryption;
            private string? _iniFileSize;
            private string? _iniEmbedding;
            private readonly List<string> _embeddingExceptionFonts;

            public DocumentValidator(IniFile iniFile, string inputPath, string? pdfPassword = null)
            {
                _iniFile = iniFile;
                _inputPath = inputPath;
                _pdfPassword = pdfPassword;

                // Extract values from INI file
                string? iniSizeTolerance = iniFile.GetValue("Pages", "SizeTolerance");
                _sizeTolerance = !string.IsNullOrEmpty(iniSizeTolerance) ? iniSizeTolerance : _sizeTolerance;
                _iniMaxPageSize = _iniFile.GetValue("Pages", "MaxPageSize");
                _iniMaxPdfVersionStr = _iniFile.GetValue("File", "MaxPdfVersion");
                _iniEncryption = _iniFile.GetValue("File", "Encryption");
                _iniFileSize = _iniFile.GetValue("File", "FileSize");
                _iniEmbedding = _iniFile.GetValue("Fonts", "Embedding");
                _embeddingExceptionFonts = _iniFile.GetKeysMatchingPattern("Fonts", @"EmbeddingExcFont\d+");
            }

            public bool ValidateDocument()
            {
                var isValid = ValidateFileSize();

                try
                {
                    using var inpath = File.OpenRead(_inputPath);
                    using var inDoc = Document.Open(inpath, _pdfPassword);

                    isValid &= ValidateConformance(inDoc.Conformance);
                    isValid &= ValidateEncryption(inDoc.Permissions);
                    isValid &= ValidatePagesSize(inDoc);
                    isValid &= ValidateFonts(inDoc);
                }
                catch (PasswordException)
                {
                    if (_pdfPassword == null)
                        Console.WriteLine("The content of the document could not be validated as it is password protected. Please provide a password.");
                    else
                        Console.WriteLine("The content of the document could not be validated as the password provided is not correct.");

                    return false;
                }

                return isValid;
            }

            private bool ValidateFileSize()
            {
                var fileInfo = new FileInfo(_inputPath);
                var fileSizeInMB = fileInfo.Length / (1024.0 * 1024.0);

                if (_iniFileSize != null)
                {
                    var iniFileSizeInMB = Convert.ToDouble(_iniFileSize);
                    if (fileSizeInMB <= iniFileSizeInMB)
                    {
                        Console.WriteLine("The PDF file size does not exceed the specified custom limit.");

                        return true;
                    }
                    else
                    {
                        Console.WriteLine("The PDF file size exceeds the specified custom limit.");

                        return false;
                    }
                }

                return true;
            }

            private bool ValidateConformance(Conformance currentConformance)
            {
                if (_iniMaxPdfVersionStr != null)
                {
                    if (ConformanceValidator.ValidateConformance(_iniMaxPdfVersionStr, currentConformance))
                    {
                        Console.WriteLine("The PDF version does not exceed the specified custom maximum version.");

                        return true;
                    }
                    else
                    {
                        Console.WriteLine("The PDF version exceeds the specified custom maximum version.");

                        return false;
                    }
                }

                return true;
            }

            private bool ValidateEncryption(Permission? permissions)
            {
                if (_iniEncryption != null)
                {
                    if (_iniEncryption.ToLower() == "true" && permissions == null)
                    {
                        Console.WriteLine("Encryption not conform: the PDF file is not encrypted. The custom encryption value specifies that the PDF file should be encrypted.");

                        return false;
                    }
                    else if (_iniEncryption.ToLower() == "false" && permissions != null)
                    {
                        Console.WriteLine("Encryption not conform: the PDF file is encrypted. The custom encryption value specifies that the PDF file should not be encrypted.");

                        return false;
                    }
                    else
                    {
                        Console.WriteLine("The PDF encryption is conform to the specified custom value.");

                        return true;
                    }
                }

                return true;
            }

            private bool ValidatePagesSize(Document inDoc)
            {
                var isValid = true;

                if (_iniMaxPageSize != null)
                {
                    var pageNumber = 0;
                    foreach (var page in inDoc.Pages)
                    {
                        pageNumber++;
                        var sizeWithInt = new Size { Width = (int)page.Size.Width, Height = (int)page.Size.Height };

                        isValid &= ValidatePageSize(pageNumber, sizeWithInt);
                    }
                }

                return isValid;
            }

            private bool ValidatePageSize(int pageNumber, Size pageSize)
            {
                if (_iniMaxPageSize != null)
                {
                    var validator = new PageSizeValidator(_iniMaxPageSize, _sizeTolerance);
                    if (validator.ValidatePageSize(pageNumber, pageSize))
                    {
                        Console.WriteLine("The size of page " + pageNumber + " is within the specified custom maximum page size value.");

                        return true;
                    }
                    else
                    {
                        Console.WriteLine("The size of page " + pageNumber + " exceeds the specified custom maximum page size value.");

                        return false;
                    }
                }

                return true;
            }

            private bool ValidateFonts(Document inDoc)
            {
                var isValid = true;

                if (_iniEmbedding != null)
                {
                    var embeddingRequired = _iniEmbedding.ToLower() == "true";
                    var pageNumber = 0;

                    foreach (var page in inDoc.Pages)
                    {
                        pageNumber++;
                        var extractor = new ContentExtractor(page.Content)
                        {
                            Ungrouping = UngroupingSelection.SafelyUngroupable
                        };

                        foreach (ContentElement element in extractor)
                        {
                            if (element is TextElement textElement)
                            {
                                foreach (var fragment in textElement.Text)
                                {
                                    var fontName = fragment.Font.BaseFont;
                                    var isEmbedded = fragment.Font.IsEmbedded;

                                    // Check if the font is in the exception list
                                    var isCurrentFontAnException = _embeddingExceptionFonts.Exists(exception => Regex.IsMatch(fontName, exception.Replace("*", ".*"), RegexOptions.IgnoreCase));

                                    // Validate based on the embedding setting
                                    // _iniEmbedding = true => The font has to be embedded or it should appear in the exception list
                                    // _iniEmbedding = false => The font cannot be embedded or it should appear in the exception list
                                    if ((embeddingRequired && !isEmbedded && !isCurrentFontAnException) || (!embeddingRequired && isEmbedded && !isCurrentFontAnException))
                                    {
                                        isValid = false;
                                        var statusText = embeddingRequired ? "be embedded" : "not be embedded";
                                        Console.WriteLine("The font '" + fontName + "' on page " + pageNumber + " should " + statusText + " as specified by the property 'Embedding' or it should be added to the list of exceptions.");
                                    }
                                    else
                                    {
                                        var statusText = embeddingRequired != isEmbedded ? "in the exception list" : isEmbedded ? "embedded" : "not embedded";
                                        Console.WriteLine("The font '" + fontName + "' on page " + pageNumber + " is conform to the 'Embedding' property as it is " + statusText + ".");
                                    }
                                }
                            }
                        }
                    }
                }

                return isValid;
            }
        }

        public class PageSizeValidator
        {
            private readonly Size maxSize;
            private readonly double sizeTolerance;

            // Named page sizes like "Letter", "A4", etc.
            private static readonly Dictionary<string, Size> NamedPageSizes = new Dictionary<string, Size>(StringComparer.OrdinalIgnoreCase)
            {
                { "Letter", new Size { Width = 612, Height = 792 } }, // 8.5 x 11 inches in points
                { "A0", new Size { Width = 2384, Height = 3370 } },
                { "A1", new Size { Width = 1684, Height = 2384 } },
                { "A2", new Size { Width = 1191, Height = 1684 } },
                { "A3", new Size { Width = 842, Height = 1191 } },
                { "A4", new Size { Width = 595, Height = 842 } },    // 210 x 297 mm in points
                { "A5", new Size { Width = 420, Height = 595 } },
                { "A6", new Size { Width = 298, Height = 420 } },
                { "A7", new Size { Width = 210, Height = 298 } },
                { "A8", new Size { Width = 147, Height = 210 } },
                { "A9", new Size { Width = 105, Height = 147 } },
                { "A10", new Size { Width = 74, Height = 105 } },
                { "DL", new Size { Width = 283, Height = 595 } }    // 99 x 210 mm in points
            };

            public PageSizeValidator(string maxPageSizeStr, string sizeToleranceStr)
            {
                maxSize = ParsePageSize(maxPageSizeStr);
                sizeTolerance = ParseSizeTolerance(sizeToleranceStr);
            }

            private Size ParsePageSize(string maxPageSize)
            {
                // First, check if it's a named size
                if (NamedPageSizes.TryGetValue(maxPageSize, out var namedSize))
                {
                    return namedSize;
                }

                // If not a named size, try to parse it as a custom size
                var match = Regex.Match(maxPageSize, @"(\d+(\.\d+)?)\s*x\s*(\d+(\.\d+)?)(\s*(pt|in|cm|mm))?", RegexOptions.IgnoreCase);
                if (!match.Success) throw new ArgumentException("Invalid MaxPageSize format: " + maxPageSize);

                double width = double.Parse(match.Groups[1].Value, CultureInfo.InvariantCulture);
                double height = double.Parse(match.Groups[3].Value, CultureInfo.InvariantCulture);
                string unit = match.Groups[6].Value.ToLower();

                return unit switch
                {
                    "in" => new Size { Width = (int)(width * 72), Height = (int)(height * 72) },
                    "cm" => new Size { Width = (int)(width * 28.3465), Height = (int)(height * 28.3465) },
                    "mm" => new Size { Width = (int)(width * 2.83465), Height = (int)(height * 2.83465) },
                    "pt" or "" => new Size { Width = (int)width, Height = (int)height },
                    _ => throw new ArgumentException("Unsupported unit: " + unit),
                };
            }

            private double ParseSizeTolerance(string sizeToleranceStr)
            {
                if (string.IsNullOrEmpty(sizeToleranceStr)) return 3; // Default tolerance in points

                var match = Regex.Match(sizeToleranceStr, @"(\d+(\.\d+)?)\s*(%)?", RegexOptions.IgnoreCase);
                if (!match.Success) throw new ArgumentException("Invalid SizeTolerance format: " + sizeToleranceStr);

                double value = double.Parse(match.Groups[1].Value, CultureInfo.InvariantCulture);
                return match.Groups[3].Success ? value / 100.0 : value; // Percentage tolerance or direct value
            }

            public bool ValidatePageSize(int pageNumber, Size actualSize)
            {
                // Check both portrait and landscape orientations
                bool isValid = (actualSize.Width <= maxSize.Width + sizeTolerance && actualSize.Height <= maxSize.Height + sizeTolerance) ||
                               (actualSize.Height <= maxSize.Width + sizeTolerance && actualSize.Width <= maxSize.Height + sizeTolerance);

                return isValid;
            }
        }

        public class ConformanceValidator
        {
            private static readonly Dictionary<string, Conformance> VersionMap = new Dictionary<string, Conformance>(StringComparer.OrdinalIgnoreCase)
            {
                { "1.0", Conformance.Pdf10 },
                { "1.1", Conformance.Pdf11 },
                { "1.2", Conformance.Pdf12 },
                { "1.3", Conformance.Pdf13 },
                { "1.4", Conformance.Pdf14 },
                { "1.5", Conformance.Pdf15 },
                { "1.6", Conformance.Pdf16 },
                { "1.7", Conformance.Pdf17 },
                { "2.0", Conformance.Pdf20 }
            };

            public static Conformance ParseVersionString(string version)
            {
                // Split the version string into parts based on the '.' delimiter
                string[] versionParts = version.Split('.');

                // Ensure there are only two parts (major and minor)
                if (versionParts.Length == 2)
                {
                    // Construct the major.minor version string (e.g., "1.7")
                    string majorMinorVersion = versionParts[0] + "." + versionParts[1];

                    // Try to get the corresponding Conformance enum value from the dictionary
                    if (VersionMap.TryGetValue(majorMinorVersion, out Conformance conformance))
                    {
                        return conformance;
                    }
                }

                // If the version is not supported, throw an exception
                throw new ArgumentException("Unsupported version or conformance level: " + version);
            }

            public static bool ValidateConformance(string maxPdfVersionStr, Conformance currentConformance)
            {
                var maxPdfConformance = ParseVersionString(maxPdfVersionStr);
                // Convert the current conformance level to the corresponding PDF version (Major.Minor) as it can be based on the PDF/A version
                var currentConformanceVersion = GetVersionFromConformance(currentConformance);

                return (int)currentConformanceVersion <= (int)maxPdfConformance;
            }

            public static Conformance GetVersionFromConformance(Conformance conformance)
            {
                if (VersionMap.ContainsValue(conformance))
                {
                    return conformance;
                }

                switch (conformance)
                {
                    case Conformance.PdfA1A:
                    case Conformance.PdfA1B:
                        return Conformance.Pdf14; // PDF/A-1 is based on PDF 1.4

                    case Conformance.PdfA2A:
                    case Conformance.PdfA2B:
                    case Conformance.PdfA2U:
                    case Conformance.PdfA3A:
                    case Conformance.PdfA3B:
                    case Conformance.PdfA3U:
                        return Conformance.Pdf17; // PDF/A-2 and PDF/A-3 are based on PDF 1.7

                    default:
                        throw new ArgumentException("Unsupported conformance level: " + conformance.ToString());
                }
            }
        }
    }
}