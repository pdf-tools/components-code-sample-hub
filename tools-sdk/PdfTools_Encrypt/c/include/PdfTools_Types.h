/******************************************************************************
 *
 * File:            PdfTools_Types.h
 *
 * Description:     Types definition for Pdftools SDK
 *
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2023 - 2024 PDF Tools AG, Switzerland
 *                  All rights reserved.
 *
 * Notice:          By downloading and using this artifact, you accept PDF Tools AG's
 *                  [license agreement](https://www.pdf-tools.com/license-agreement/),
 *                  [privacy policy](https://www.pdf-tools.com/privacy-policy/),
 *                  and allow PDF Tools AG to track your usage data.
 *
 *****************************************************************************/

#ifndef PDFTOOLS_TYPES_H__
#define PDFTOOLS_TYPES_H__

#ifndef BOOL
#define BOOL  int
#define TRUE  1
#define FALSE 0
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum TPdfTools_ErrorCode
{
    ePdfTools_Error_Success              = 0,
    ePdfTools_Error_UnsupportedOperation = 1,
    ePdfTools_Error_IllegalState         = 2,
    ePdfTools_Error_IllegalArgument      = 3,
    ePdfTools_Error_IO                   = 4,
    ePdfTools_Error_NotFound             = 5,
    ePdfTools_Error_Unknown              = 6,
    /**
     * @brief A generic error occurred.
     */
    ePdfTools_Error_Generic = 10,
    /**
     * @brief The license is not valid.
     */
    ePdfTools_Error_License = 12,
    /**
     * @brief The format is not known.
     */
    ePdfTools_Error_UnknownFormat = 15,
    /**
     * @brief The file is corrupt and cannot be opened.
     */
    ePdfTools_Error_Corrupt = 16,
    /**
     * @brief Invalid password specified.
     */
    ePdfTools_Error_Password = 17,
    /**
     * @brief The document has an invalid conformance level.
     */
    ePdfTools_Error_Conformance = 18,
    /**
     * @brief The document contains an unsupported feature.
     */
    ePdfTools_Error_UnsupportedFeature = 19,
    /**
     * @brief The file cannot be processed.
     */
    ePdfTools_Error_Processing = 21,
    /**
     * @brief The specified item already exists.
     */
    ePdfTools_Error_Exists = 22,
    /**
     * @brief The operation is not allowed.
     */
    ePdfTools_Error_Permission = 23,
    /**
     * @brief An error occurred during the processing of a HTTP request.
     */
    ePdfTools_Error_Http = 24,
    /**
     * @brief A resource or service is temporarily unavailable.
     */
    ePdfTools_Error_Retry = 25,
} TPdfTools_ErrorCode;

/**
 * @brief The permissions allowed by a PDF document
  - See \ref PdfToolsPdf_Document_GetPermissions "" to read the permissions of a PDF document.
  - See \ref PdfToolsPdf_OutputOptions_GetEncryption "" to set the permissions when encrypting a PDF document.

 */
typedef enum TPdfToolsPdf_Permission
{
    /**
     * @brief No permission.
     */
    ePdfToolsPdf_Permission_None = 0,
    /**
     * @brief Allow low resolution printing.
     */
    ePdfToolsPdf_Permission_Print = 4,
    /**
     * @brief Allow changing the document.
     */
    ePdfToolsPdf_Permission_Modify = 8,
    /**
     * @brief Allow content copying or extraction.
     */
    ePdfToolsPdf_Permission_Copy = 16,
    /**
     * @brief Allow annotations.
     */
    ePdfToolsPdf_Permission_Annotate = 32,
    /**
     * @brief Allow filling of form fields.
     */
    ePdfToolsPdf_Permission_FillForms = 256,
    /**
     * @brief Allow support for disabilities.
     */
    ePdfToolsPdf_Permission_SupportDisabilities = 512,
    /**
     * @brief Allow document assembly.
     */
    ePdfToolsPdf_Permission_Assemble = 1024,
    /**
     * @brief Allow high resolution printing.
     */
    ePdfToolsPdf_Permission_DigitalPrint = 2048,
    ePdfToolsPdf_Permission_All          = 3900,
} TPdfToolsPdf_Permission;

/**
 * @brief The XFA type of a PDF document
See \ref PdfToolsPdf_Document_GetXfa "" to get the XFA type of a PDF document.

 */
typedef enum TPdfToolsPdf_XfaType
{
    /**
     * @brief No XFA document
    The document is not an XFA document but a regular PDF document.

     */
    ePdfToolsPdf_XfaType_NoXfa = 0,
    /**
     * @brief XFA document
    The document is an XFA document.
    The document cannot be processed by many components, so it is recommended to convert it to a PDF document
    beforehand.

     */
    ePdfToolsPdf_XfaType_XfaNeedsRendering = 1,
    /**
     * @brief Rendered XFA document
    The document is a "rendered" XFA document where the PDF pages' content has been generated from the XFA form.
    Such documents can be processed as regular PDF documents.
    However, there is no guarantee that the generated pages accurately reflect the XFA document.

     */
    ePdfToolsPdf_XfaType_XfaRendered = 2,
} TPdfToolsPdf_XfaType;

/**
 */
typedef enum TPdfToolsPdf_MdpPermissions
{
    /**
    No changes to the document shall be permitted;
    any change to the document invalidates the signature.

     */
    ePdfToolsPdf_MdpPermissions_NoChanges = 1,
    /**
    Permitted changes are filling in forms, instantiating page templates, and signing;
    other changes invalidate the signature.

     */
    ePdfToolsPdf_MdpPermissions_FormFilling = 2,
    /**
    Permitted changes are the same as for \ref ePdfToolsPdf_MdpPermissions_FormFilling "",
    as well as annotation creation, deletion, and modification;
    other changes invalidate the signature.

     */
    ePdfToolsPdf_MdpPermissions_Annotate = 3,
} TPdfToolsPdf_MdpPermissions;

/**
 */
typedef enum TPdfToolsPdf_Conformance
{
    /**
     * @brief PDF Version 1.0
     */
    ePdfToolsPdf_Conformance_Pdf10 = 0x1000,
    /**
     * @brief PDF Version 1.1
     */
    ePdfToolsPdf_Conformance_Pdf11 = 0x1100,
    /**
     * @brief PDF Version 1.2
     */
    ePdfToolsPdf_Conformance_Pdf12 = 0x1200,
    /**
     * @brief PDF Version 1.3
     */
    ePdfToolsPdf_Conformance_Pdf13 = 0x1300,
    /**
     * @brief PDF Version 1.4 (corresponds to Acrobat 5)
     */
    ePdfToolsPdf_Conformance_Pdf14 = 0x1400,
    /**
     * @brief PDF Version 1.5
     */
    ePdfToolsPdf_Conformance_Pdf15 = 0x1500,
    /**
     * @brief PDF Version 1.6 (corresponds to Acrobat 7)
     */
    ePdfToolsPdf_Conformance_Pdf16 = 0x1600,
    /**
     * @brief PDF Version 1.7, ISO 32000-1
     */
    ePdfToolsPdf_Conformance_Pdf17 = 0x1700,
    /**
     * @brief PDF Version 2.0, ISO 32000-2
     */
    ePdfToolsPdf_Conformance_Pdf20 = 0x2000,
    /**
     * @brief PDF/A-1b, ISO 19005-1, level B conformance
     */
    ePdfToolsPdf_Conformance_PdfA1B = 0x1401,
    /**
     * @brief PDF/A-1a, ISO 19005-1, level A conformance
     */
    ePdfToolsPdf_Conformance_PdfA1A = 0x1402,
    /**
     * @brief PDF/A-2b, ISO 19005-2, level B conformance
     */
    ePdfToolsPdf_Conformance_PdfA2B = 0x1701,
    /**
     * @brief PDF/A-2u, ISO 19005-2, level U conformance
     */
    ePdfToolsPdf_Conformance_PdfA2U = 0x1702,
    /**
     * @brief PDF/A-2a, ISO 19005-2, level A conformance
     */
    ePdfToolsPdf_Conformance_PdfA2A = 0x1703,
    /**
     * @brief PDF/A-3b, ISO 19005-3, level B conformance
     */
    ePdfToolsPdf_Conformance_PdfA3B = 0x1711,
    /**
     * @brief PDF/A-3u, ISO 19005-3, level U conformance
     */
    ePdfToolsPdf_Conformance_PdfA3U = 0x1712,
    /**
     * @brief PDF/A-3a, ISO 19005-3, level A conformance
     */
    ePdfToolsPdf_Conformance_PdfA3A = 0x1713,
} TPdfToolsPdf_Conformance;

/**
 */
typedef enum TPdfToolsDocumentAssembly_CopyStrategy
{
    /**
    The elements are copied as-is to the output document.

     */
    ePdfToolsDocumentAssembly_CopyStrategy_Copy = 1,
    /**
    The visual appearance of elements is preserved, but they are not interactive anymore.

     */
    ePdfToolsDocumentAssembly_CopyStrategy_Flatten = 2,
    /**
    The elements are removed completely.

     */
    ePdfToolsDocumentAssembly_CopyStrategy_Remove = 3,
} TPdfToolsDocumentAssembly_CopyStrategy;

/**
 */
typedef enum TPdfToolsDocumentAssembly_RemovalStrategy
{
    /**
    The visual appearance of elements is preserved, but they are not interactive anymore.

     */
    ePdfToolsDocumentAssembly_RemovalStrategy_Flatten = 1,
    /**
    The elements are removed completely.

     */
    ePdfToolsDocumentAssembly_RemovalStrategy_Remove = 2,
} TPdfToolsDocumentAssembly_RemovalStrategy;

/**
 */
typedef enum TPdfToolsDocumentAssembly_NamedDestinationCopyStrategy
{
    /**
     * @brief Copy named destinations
    Named destinations are copyied as-is.

     */
    ePdfToolsDocumentAssembly_NamedDestinationCopyStrategy_Copy = 1,
    /**
     * @brief Resolve named destinations
    Named destinations are resolved and converted to direct destinations.

     */
    ePdfToolsDocumentAssembly_NamedDestinationCopyStrategy_Resolve = 2,
} TPdfToolsDocumentAssembly_NamedDestinationCopyStrategy;

/**
 */
typedef enum TPdfToolsDocumentAssembly_NameConflictResolution
{
    /**
    Elements with the same name are considered the same and are merged if possible.

     */
    ePdfToolsDocumentAssembly_NameConflictResolution_Merge = 1,
    /**
    Elements with the same name are considered different and the later occurrence is renamed.

     */
    ePdfToolsDocumentAssembly_NameConflictResolution_Rename = 2,
} TPdfToolsDocumentAssembly_NameConflictResolution;

/**
 * @brief The conversion strategy for PDF objects
 */
typedef enum TPdfToolsOptimization_ConversionStrategy
{
    /**
    The object is copied onto the output page.

     */
    ePdfToolsOptimization_ConversionStrategy_Copy = 1,
    /**
    The object is removed, but its visual appearance is drawn as
    non-editable graphic onto the output page.

     */
    ePdfToolsOptimization_ConversionStrategy_Flatten = 2,
} TPdfToolsOptimization_ConversionStrategy;

/**
 * @brief The removal strategy for PDF objects
 */
typedef enum TPdfToolsOptimization_RemovalStrategy
{
    /**
    The object is removed, but its visual appearance is drawn as
    non-editable graphic onto the output page.

     */
    ePdfToolsOptimization_RemovalStrategy_Flatten = 2,
    /**
    The object is removed together with its visual appearance.

     */
    ePdfToolsOptimization_RemovalStrategy_Remove = 3,
} TPdfToolsOptimization_RemovalStrategy;

/**
 * @brief The strategy for recompressing images
The strategy expresses the broad goal when recompressing images.

 */
typedef enum TPdfToolsOptimization_CompressionAlgorithmSelection
{
    /**
    The image quality is preserved as far as possible.

     */
    ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality = 1,
    /**
    A compromise between
    \ref ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality ""
    and
    \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Speed "".

     */
    ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced = 2,
    /**
    Favor fast compression time over image quality.

     */
    ePdfToolsOptimization_CompressionAlgorithmSelection_Speed = 3,
} TPdfToolsOptimization_CompressionAlgorithmSelection;

/**
 * @brief The vertical resolution of Fax images
The two resolutions available in Fax images.

 */
typedef enum TPdfToolsPdf2Image_FaxVerticalResolution
{
    /**
     * @brief A vertical resolution of 98 DPI (dots per inch)
     */
    ePdfToolsPdf2Image_FaxVerticalResolution_Standard = 1,
    /**
     * @brief A vertical resolution of 196 DPI (dots per inch)
     */
    ePdfToolsPdf2Image_FaxVerticalResolution_High = 2,
} TPdfToolsPdf2Image_FaxVerticalResolution;

/**
 * @brief The compression type for bitonal (Fax) TIFF images
 */
typedef enum TPdfToolsPdf2Image_TiffBitonalCompressionType
{
    /**
     * @brief CCITT Group 3
    CCITT Group 3 is the predecessor to CCITT Group 4, it is a simpler
    algorithm that normally results in a lower compression ratio.

     */
    ePdfToolsPdf2Image_TiffBitonalCompressionType_G3 = 1,
    /**
     * @brief CCITT Group 4
    CCITT Group 4 is the standard compression for bitonal TIFF images
    (i.e. facsimile).

     */
    ePdfToolsPdf2Image_TiffBitonalCompressionType_G4 = 2,
} TPdfToolsPdf2Image_TiffBitonalCompressionType;

/**
 * @brief The background type to use when rendering into an image
 */
typedef enum TPdfToolsPdf2Image_BackgroundType
{
    /**
     * @brief White background
    The input PDF content will be rendered on a white background.

     */
    ePdfToolsPdf2Image_BackgroundType_White = 1,
    /**
     * @brief Transparent background
    The input PDF content will be rendered into an image with an
    alpha channel and no background.

     */
    ePdfToolsPdf2Image_BackgroundType_Transparent = 2,
} TPdfToolsPdf2Image_BackgroundType;

/**
 * @brief The color space used in PNG images
 */
typedef enum TPdfToolsPdf2Image_PngColorSpace
{
    /**
     */
    ePdfToolsPdf2Image_PngColorSpace_Rgb = 1,
    /**
     */
    ePdfToolsPdf2Image_PngColorSpace_Gray = 2,
} TPdfToolsPdf2Image_PngColorSpace;

/**
 * @brief The color space used in JPEG images
 */
typedef enum TPdfToolsPdf2Image_JpegColorSpace
{
    /**
     */
    ePdfToolsPdf2Image_JpegColorSpace_Rgb = 1,
    /**
     */
    ePdfToolsPdf2Image_JpegColorSpace_Gray = 2,
    /**
     */
    ePdfToolsPdf2Image_JpegColorSpace_Cmyk = 3,
} TPdfToolsPdf2Image_JpegColorSpace;

/**
 * @brief The color space used in various image formats
 */
typedef enum TPdfToolsPdf2Image_ColorSpace
{
    /**
     */
    ePdfToolsPdf2Image_ColorSpace_Rgb = 1,
    /**
     */
    ePdfToolsPdf2Image_ColorSpace_Gray = 2,
    /**
     */
    ePdfToolsPdf2Image_ColorSpace_Cmyk = 3,
} TPdfToolsPdf2Image_ColorSpace;

/**
 * @brief Defines how to render annotations and their popups

Annotations associate an object such as a sticky note, link or rich media
with a location on a PDF page; they may also provide user interaction
by means of the mouse and keyboard.

Some annotations have an associated popup.

 */
typedef enum TPdfToolsPdf2Image_AnnotationOptions
{
    /**
     * @brief Render the annotation without the associated popup
     */
    ePdfToolsPdf2Image_AnnotationOptions_ShowAnnotations = 1,
    /**
     * @brief Render the annotation and the associated popup
     */
    ePdfToolsPdf2Image_AnnotationOptions_ShowAnnotationsAndPopups = 2,
} TPdfToolsPdf2Image_AnnotationOptions;

/**
 * @brief The validation error category
 */
typedef enum TPdfToolsPdfAValidation_ErrorCategory
{
    /**
    The file format (header, trailer, objects, xref, streams) is corrupted.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Format = 0x00000001,
    /**
    The document doesn't conform to the PDF reference or PDF/A Specification (missing required entries, wrong value
    types, etc.).

     */
    ePdfToolsPdfAValidation_ErrorCategory_Pdf = 0x00000002,
    /**
    The file is encrypted.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Encryption = 0x00000004,
    /**
    The document contains device-specific color spaces.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Color = 0x00000008,
    /**
    The document contains illegal rendering hints (unknown intents, interpolation, transfer and halftone functions).

     */
    ePdfToolsPdfAValidation_ErrorCategory_Rendering = 0x00000010,
    /**
    The document contains alternate information (images).

     */
    ePdfToolsPdfAValidation_ErrorCategory_Alternate = 0x00000020,
    /**
    The document contains embedded PostScript code.

     */
    ePdfToolsPdfAValidation_ErrorCategory_PostScript = 0x00000040,
    /**
    The document contains references to external content (reference XObjects, OPI).

     */
    ePdfToolsPdfAValidation_ErrorCategory_External = 0x00000080,
    /**
    The document contains fonts without embedded font programs or encoding information (CMAPs)

     */
    ePdfToolsPdfAValidation_ErrorCategory_Font = 0x00000100,
    /**
    The document contains fonts without appropriate character to Unicode mapping information (ToUnicode maps)

     */
    ePdfToolsPdfAValidation_ErrorCategory_Unicode = 0x00000200,
    /**
    The document contains transparency.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Transparency = 0x00000400,
    /**
    The document contains unknown annotation types.

     */
    ePdfToolsPdfAValidation_ErrorCategory_UnsupportedAnnotation = 0x00000800,
    /**
    The document contains multimedia annotations (sound, movies).

     */
    ePdfToolsPdfAValidation_ErrorCategory_Multimedia = 0x00001000,
    /**
    The document contains hidden, invisible, non-viewable or non-printable annotations.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Print = 0x00002000,
    /**
    The document contains annotations or form fields with ambiguous or without appropriate appearances.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Appearance = 0x00004000,
    /**
    The document contains actions types other than for navigation (launch, JavaScript, ResetForm, etc.)

     */
    ePdfToolsPdfAValidation_ErrorCategory_Action = 0x00008000,
    /**
    The document's meta data is either missing or inconsistent or corrupt.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Metadata = 0x00010000,
    /**
    The document doesn't provide appropriate logical structure information.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Structure = 0x00020000,
    /**
    The document contains optional content (layers).

     */
    ePdfToolsPdfAValidation_ErrorCategory_OptionalContent = 0x00040000,
    /**
    The document contains embedded files.

     */
    ePdfToolsPdfAValidation_ErrorCategory_EmbeddedFile = 0x00080000,
    /**
    The document contains signatures.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Signature = 0x00100000,
    /**
    Violations of custom corporate directives.

     */
    ePdfToolsPdfAValidation_ErrorCategory_Custom = 0x40000000,
} TPdfToolsPdfAValidation_ErrorCategory;

/**
 * @brief The severity of conversion events
See \ref TPdfToolsPdfAConversion_Converter_ConversionEvent "" for more information on conversion events.

 */
typedef enum TPdfToolsPdfAConversion_EventSeverity
{
    /**
     * @brief A conversion event which is of an informational nature

    An informational event requires no further action.

    By default events of the following \ref TPdfToolsPdfAConversion_EventCategory "" are classified as \ref
    ePdfToolsPdfAConversion_EventSeverity_Information "":
      - \ref ePdfToolsPdfAConversion_EventCategory_ManagedColors ""
      - \ref ePdfToolsPdfAConversion_EventCategory_ChangedColorant ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedExternalContent ""
      - \ref ePdfToolsPdfAConversion_EventCategory_ConvertedFont ""
      - \ref ePdfToolsPdfAConversion_EventCategory_SubstitutedFont ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedAnnotation ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedMultimedia ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedAction ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedMetadata ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedStructure ""
      - \ref ePdfToolsPdfAConversion_EventCategory_ConvertedEmbeddedFile ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedSignature ""

     */
    ePdfToolsPdfAConversion_EventSeverity_Information = 1,
    /**
     * @brief A conversion event which is generally considered a non-critical issue

    An warning that might require further actions.

    By default events of the following \ref TPdfToolsPdfAConversion_EventCategory "" are classified as \ref
    ePdfToolsPdfAConversion_EventSeverity_Warning "":
      - \ref ePdfToolsPdfAConversion_EventCategory_VisualDifferences ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RepairedCorruption ""
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedTransparency "" (PDF/A-1 only)
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedEmbeddedFile ""  (PDF/A-1 and PDF/A-2 only)
      - \ref ePdfToolsPdfAConversion_EventCategory_RemovedOptionalContent "" (PDF/A-1 only)

     */
    ePdfToolsPdfAConversion_EventSeverity_Warning = 2,
    /**
     * @brief A conversion event which is generally considered a critical issue

    A critical issue for which the conversion must be considered as failed.

    By default no event uses this severity.

     */
    ePdfToolsPdfAConversion_EventSeverity_Error = 3,
} TPdfToolsPdfAConversion_EventSeverity;

/**
 * @brief The category of conversion events
See \ref TPdfToolsPdfAConversion_Converter_ConversionEvent "" for more information on conversion events.

 */
typedef enum TPdfToolsPdfAConversion_EventCategory
{
    /**
     * @brief The conversion resulted in visual differences to the document.

    The conversion is optimized to preserve the visual appearance of documents.
    However, under some circumstances visual differences cannot be avoided.
    This is typically the case for low quality and erroneous input documents.

    Examples:
      - The visual appearance of a proprietary annotation type could not be generated.
      - Numbers that exceed the allowed value range have been clipped.
      - Text of an invalid font is unclear because its mapping to glyphs is ambiguous.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Warning ""

    It is not possible for the SDK to gauge the effect of the visual differences on the document's content.
    Therefore, it is recommended to let a user assess, whether or not the conversion result is acceptable.
    If a manual review is not feasible, events of this category should be classified as an \ref
    ePdfToolsPdfAConversion_EventSeverity_Error "".

     */
    ePdfToolsPdfAConversion_EventCategory_VisualDifferences = 0x00000001,
    /**
     * @brief Repaired a corrupt document.

    Corrupt documents are repaired automatically.
    Since the specification does not define how corrupt documents should be repaired, each viewer has its own heuristics
    for doing so. Therefore, the repaired document might have visual differences to the input document in your viewer.
    For that reason, an event is generated such that the repaired document can be reviewed, similarly to \ref
    ePdfToolsPdfAConversion_EventCategory_VisualDifferences "".

    Examples for documents that must be repaired:
      - The document has been damaged, e.g. during an incomplete file upload.
      - The document has been created by an erroneous application.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Warning ""

     */
    ePdfToolsPdfAConversion_EventCategory_RepairedCorruption = 0x00000002,
    /**
     * @brief Managed colors of input document.

    Purely informational messages related to color management.

    Examples:
      - Copied PDF/A output intent from input file.
      - Embedded ICC color profile.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_ManagedColors = 0x00000004,
    /**
     * @brief Resolved ambiguous or conflicting descriptions of colorants (spot colors).

    Colorants are special inks used in addition to the process colors (e.g. red, green, and blue in the RGB color space
    or cyan, magenta, yellow and black in the CMYK color space). Popular colorants are PANTONE colors typically used in
    printing; or also metallic or fluorescent inks.

    Colorants in PDF documents contain a description that is required to paint a good approximation of the intended
    color in case the colorant is unavailable. Within the same document all descriptions for the same colorant should be
    equal. This warning is generated if conflicting descriptions must be harmonized, for example during PDF/A
    conversion.

    This has no effect on output devices where the colorant is available, e.g. on certain printers.
    For other output devices this warning may indicate visual differences.
    However, for well-formed documents (i.e. not maliciously created documents), the visual differences are not
    noticeable.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_ChangedColorant = 0x00000008,
    /**
     * @brief Removed references to external content.

    Examples:
      - Removed references to external files containing stream data used in the document.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedExternalContent = 0x00000010,
    /**
     * @brief Converted fonts of input document.

    Purely informational messages related to font management.

    Examples:
      - Embedded a font.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_ConvertedFont = 0x00000020,
    /**
     * @brief Substituted a font for a similar one.

    If a required font is not embedded and not available in the installed fonts, a similar font must be chosen and used.
    This is a commonly performed when viewing or printing a PDF document.
    While this may lead to minor visual differences, all text is preserved.

    It is important that the installed fonts contain all fonts that are not embedded in the input documents.
    See the product's installation documentation for a list of fonts that are recommended to install.

    Examples:
      - Substituted font 'GothicBBB-Medium' with 'MS-Gothic'.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_SubstitutedFont = 0x00000040,
    /**
     * @brief Converted transparent object to opaque.

    Because transparency is not allowed in PDF/A-1, transparent objects have to be converted to opaque when converting a
    document to PDF/A-1. This can lead to visual differences. Even though the conversion has been optimized to reduce
    visual differences, they might be noticeable. Therefore, it is highly recommended to convert documents to PDF/A-2 or
    higher. These versions of the standard allow transparency, which results in a higher conversion quality.

    This conversion event should be handled similarly to \ref ePdfToolsPdfAConversion_EventCategory_VisualDifferences
    "".

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Warning ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedTransparency = 0x00000080,
    /**
     * @brief Removed prohibited annotation type.

    Removing annotations does not lead to visual differences, but merely removes the interactivity of the elements.

    Examples:
      - Removed proprietary annotation types.
      - Removed forbidden annotation types, e.g. 3D.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedAnnotation = 0x00000100,
    /**
     * @brief Removed multimedia content (sound, movie).


    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedMultimedia = 0x00000200,
    /**
     * @brief Removed prohibited action type.

    Removing actions does not lead to visual differences.

    Examples:
      - Removed JavaScript actions in interactive form fields.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedAction = 0x00000400,
    /**
     * @brief Removed parts of the XMP metadata that could not be repaired.

    This event indicates that metadata properties have been removed during conversion.
    This includes any kind of metadata like e.g. the XMP metadata of a PDF document.

    Examples:
      - Parts of the XMP metadata of a PDF did not conform to the PDF/A standard and had to be removed.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedMetadata = 0x00000800,
    /**
     * @brief Removed logical structure (tagging) information.

    The logical structure of the document is a description of the content of its pages.
    This description has to be provided by the creator of the document.
    It consists of a fine granular hierarchical tagging that distinguishes between the actual content and artifacts
    (such as page numbers, layout artifacts, etc.). The tagging provides a meaningful description, for example "This is
    a header", "This color image shows a small sailing boat at sunset", etc. This information can be used e.g. to read
    the document to the visually impaired.

    The SDK has been optimized to preserve tagging information.
    Typically, tagging information only has to be removed if it is invalid or corrupt.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedStructure = 0x00001000,
    /**
     * @brief Removed optional content groups (layers).

    Because optional content is not allowed in PDF/A-1, it has to be removed when converting a document to PDF/A-1.
    Removing layers does not change the initial appearance of pages.
    However, the visibility of content cannot be changed anymore.
    Therefore, it is highly recommended to convert documents to PDF/A-2 or higher.
    These versions of the standard allow optional content, which results in a higher conversion quality.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Warning ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedOptionalContent = 0x00002000,
    /**
     * @brief Converted embedded file.

    Purely informational messages related to the conversion of embedded files.

    Examples:
      - Copied an embedded file.
      - Embedded a file that has successfully been converted to PDF/A.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_ConvertedEmbeddedFile = 0x00004000,
    /**
     * @brief Removed embedded files.

    Whether embedded files have to be removed depends on the conformance:
      - <b>PDF/A-1:</b>
    Embedded files are not allowed.
        All embedded files have to be removed.
      - <b>PDF/A-2:</b>
    Only embedded files are allowed, that conform to PDF/A.
        All embedded PDF documents are converted to PDF/A.
    All other files have to be removed.
        The Conversion Service can be used to convert PDF documents with other types of embedded files, e.g. Microsoft
    Office documents, images, and mails, to PDF/A-2.
      - <b>PDF/A-3:</b>
    All types of embedded files are allowed and copied as-is.
        The Conversion Service can be used, if a more fine-grained control over the conversion and copying of embedded
    files is required.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Warning ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedEmbeddedFile = 0x00008000,
    /**
     * @brief Removed signatures of signed input file.

    Converting a signed document invalidates its signatures.
    For that reason, the cryptographic parts of the signatures are removed while their visual appearances are preserved.

    Note that we generally recommend to sign PDF/A documents only for two reasons.
    First, this ensures that the file is not corrupt and its visual appearance is well defined, such than it can be
    reproduced flawlessly and authentically in any environment. Second, PDF/A conformance is typically required if the
    file is to be archived, e.g. by the recipient. Because signed files cannot be converted to PDF/A without breaking
    the signature, the signature must be removed before the file can be archived. By converting files to PDF/A before
    applying the signature, this dilemma can be avoided.

    Suggested severity: \ref ePdfToolsPdfAConversion_EventSeverity_Information ""

     */
    ePdfToolsPdfAConversion_EventCategory_RemovedSignature = 0x00010000,
} TPdfToolsPdfAConversion_EventCategory;

/**
 * @brief The code identifying particular conversion events
See \ref TPdfToolsPdfAConversion_Converter_ConversionEvent "" for more information on conversion events.

 */
typedef enum TPdfToolsPdfAConversion_EventCode
{
    /**
    Code for events that do not have a specific code associated.

     */
    ePdfToolsPdfAConversion_EventCode_Generic = 0x00000001,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_VisualDifferences ""

     */
    ePdfToolsPdfAConversion_EventCode_RemovedXfa = 0x01000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_VisualDifferences ""

     */
    ePdfToolsPdfAConversion_EventCode_FontNonEmbeddedOrderingIdentity = 0x01000001,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_VisualDifferences ""

     */
    ePdfToolsPdfAConversion_EventCode_FontNoRotate = 0x01000002,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_VisualDifferences ""

     */
    ePdfToolsPdfAConversion_EventCode_FontNoItalicSimulation = 0x01000003,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_VisualDifferences ""

     */
    ePdfToolsPdfAConversion_EventCode_ClippedNumberValue = 0x01000004,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_RepairedCorruption ""

     */
    ePdfToolsPdfAConversion_EventCode_RecoveredImageSize = 0x02000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_RepairedCorruption ""

     */
    ePdfToolsPdfAConversion_EventCode_RepairedFont = 0x02000001,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ManagedColors ""

     */
    ePdfToolsPdfAConversion_EventCode_CopiedOutputIntent = 0x03000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ManagedColors ""

     */
    ePdfToolsPdfAConversion_EventCode_SetOutputIntent = 0x03000001,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ManagedColors ""

     */
    ePdfToolsPdfAConversion_EventCode_GeneratedOutputIntent = 0x03000002,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ManagedColors ""

     */
    ePdfToolsPdfAConversion_EventCode_SetColorProfile = 0x03000003,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ManagedColors ""

     */
    ePdfToolsPdfAConversion_EventCode_GeneratedColorProfile = 0x03000004,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ManagedColors ""

     */
    ePdfToolsPdfAConversion_EventCode_CreatedCalibrated = 0x03000005,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ChangedColorant ""

     */
    ePdfToolsPdfAConversion_EventCode_RenamedColorant = 0x04000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ChangedColorant ""

     */
    ePdfToolsPdfAConversion_EventCode_ResolvedColorantCollision = 0x04000001,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ConvertedFont ""

     */
    ePdfToolsPdfAConversion_EventCode_EmbededFont = 0x06000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_SubstitutedFont ""

     */
    ePdfToolsPdfAConversion_EventCode_SubstitutedFont = 0x07000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_SubstitutedFont ""

     */
    ePdfToolsPdfAConversion_EventCode_SubstitutedMultipleMaster = 0x07000001,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_RemovedAnnotation ""

     */
    ePdfToolsPdfAConversion_EventCode_ConvertedToStamp = 0x09000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_RemovedMetadata ""

     */
    ePdfToolsPdfAConversion_EventCode_RemovedDocumentMetadata = 0x0C000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ConvertedEmbeddedFile ""

     */
    ePdfToolsPdfAConversion_EventCode_CopiedEmbeddedFile = 0x0F000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ConvertedEmbeddedFile ""

     */
    ePdfToolsPdfAConversion_EventCode_ConvertingEmbeddedFileStart = 0x0F000001,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_ConvertedEmbeddedFile ""

     */
    ePdfToolsPdfAConversion_EventCode_ConvertingEmbeddedFileSuccess = 0x0F000002,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_RemovedEmbeddedFile ""

     */
    ePdfToolsPdfAConversion_EventCode_ChangedToInitialDocument = 0x10000000,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_RemovedEmbeddedFile ""

     */
    ePdfToolsPdfAConversion_EventCode_ConvertingEmbeddedFileError = 0x10000001,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_RemovedEmbeddedFile ""

     */
    ePdfToolsPdfAConversion_EventCode_RemovedEmbeddedFile = 0x10000002,
    /**
    see \ref ePdfToolsPdfAConversion_EventCategory_RemovedEmbeddedFile ""

     */
    ePdfToolsPdfAConversion_EventCode_RemovedFileAttachmentAnnotation = 0x10000003,
} TPdfToolsPdfAConversion_EventCode;

/**
 * @brief The warning category
The category of the warning of \ref TPdfToolsSign_Signer_Warning "".

 */
typedef enum TPdfToolsSign_WarningCategory
{
    /**
    PDF/A conformance of input file removed due to file encryption (i.e. \ref PdfToolsPdf_OutputOptions_GetEncryption ""
    is not `NULL`). Removal of PDF/A conformance is necessary, because encryption is not allowed by the PDF/A standard.

     */
    ePdfToolsSign_WarningCategory_PdfARemoved = 1,
    /**

    When processing signed documents, their encryption parameters (user password, owner password, permissions) cannot be
    changed. Therefore, the property \ref PdfToolsPdf_OutputOptions_GetEncryption "" has no effect.

    This warning is generated so that the following situations can be detected:
      - If \ref PdfToolsPdf_OutputOptions_GetEncryption "" is `NULL` and the input document is encrypted.
    The output document is also encrypted.
      - If \ref PdfToolsPdf_OutputOptions_GetEncryption "" not `NULL` and the input document is encrypted using
    different encryption parameters. The output document is also encrypted, preserving the encryption parameters of the
    input document.
      - If \ref PdfToolsPdf_OutputOptions_GetEncryption "" not `NULL` and the input document is not encrypted.
    The output document is not encrypted.

    Encryption parameters of signed documents can be changed by removing all existing signatures using the property \ref
    PdfToolsSign_OutputOptions_GetRemoveSignatures "". In this case, this warning is not generated.

     */
    ePdfToolsSign_WarningCategory_SignedDocEncryptionUnchanged = 2,
    /**

    Error adding validation information to existing signatures of input document as requested by
    \ref PdfToolsSign_OutputOptions_GetAddValidationInformation "".
    The warning's `context` contains a description of the affected signature.

    Potential causes of this warning are:
      - <b>Missing issuer certificate:</b>
    All certificates of the trust chain are required to add validation information.
    Preferably, the certificates should be present in the cryptographic provider's certificate store.
    Alternatively, if supported by the certificate,
    the issuer certificate is downloaded from the certificate authority's server and
    stored in the user's `Certificates` directory (see \ref TPdfToolsCryptoProvidersBuiltIn_Provider "").
      - <b>Network problem:</b>
    The network must allow OCSP and CRL responses to be downloaded from the certificate authority's server.
    Make sure your proxy configuration (see \ref PdfTools_Sdk_GetProxy "") is correct.

     */
    ePdfToolsSign_WarningCategory_AddValidationInformationFailed = 3,
} TPdfToolsSign_WarningCategory;

/**
 */
typedef enum TPdfToolsSign_SignatureRemoval
{
    /**
    Do not remove any signatures.

     */
    ePdfToolsSign_SignatureRemoval_None = 1,
    /**

    Remove all signed signatures, but no unsigned signature fields.
    This lets you change the encryption parameters of signed input documents, e.g. to encrypt or decrypt them (see \ref
    ePdfToolsSign_WarningCategory_SignedDocEncryptionUnchanged "").

    While the cryptographic parts of the signatures are removed, their visual appearances are preserved.

     */
    ePdfToolsSign_SignatureRemoval_Signed = 2,
    /**
    Remove all signed (see \ref ePdfToolsSign_SignatureRemoval_Signed "") and unsigned signature fields.

     */
    ePdfToolsSign_SignatureRemoval_All = 3,
} TPdfToolsSign_SignatureRemoval;

/**
 */
typedef enum TPdfToolsSign_AddValidationInformation
{
    /**
    Do not add validation information to any existing signatures of input document.

     */
    ePdfToolsSign_AddValidationInformation_None = 1,
    /**
    Add validation information to latest existing signature of input document.

     */
    ePdfToolsSign_AddValidationInformation_Latest = 2,
    /**
    Add validation information to all existing signatures of input document.

     */
    ePdfToolsSign_AddValidationInformation_All = 3,
} TPdfToolsSign_AddValidationInformation;

/**
 */
typedef enum TPdfToolsCrypto_HashAlgorithm
{
    /**
     * @brief MD5
    This algorithm is considered broken and therefore strongly discouraged by the cryptographic community.

     */
    ePdfToolsCrypto_HashAlgorithm_Md5 = 1,
    /**
     * @brief RIPEMD-160
     */
    ePdfToolsCrypto_HashAlgorithm_RipeMd160 = 2,
    /**
     * @brief SHA-1
    This algorithm is considered broken and therefore strongly discouraged by the cryptographic community.

     */
    ePdfToolsCrypto_HashAlgorithm_Sha1 = 3,
    /**
     * @brief SHA-256
     */
    ePdfToolsCrypto_HashAlgorithm_Sha256 = 4,
    /**
     * @brief SHA-384
     */
    ePdfToolsCrypto_HashAlgorithm_Sha384 = 5,
    /**
     * @brief SHA-512
     */
    ePdfToolsCrypto_HashAlgorithm_Sha512 = 6,
    /**
     * @brief SHA3-256
    `SHA3-256` is a new hashing algorithm and may not be supported by some applications.

     */
    ePdfToolsCrypto_HashAlgorithm_Sha3_256 = 7,
    /**
     * @brief SHA3-384
    `SHA3-384` is a new hashing algorithm and may not be supported by some applications.

     */
    ePdfToolsCrypto_HashAlgorithm_Sha3_384 = 8,
    /**
     * @brief SHA3-512
    `SHA3-512` is a new hashing algorithm and may not be supported by some applications.

     */
    ePdfToolsCrypto_HashAlgorithm_Sha3_512 = 9,
} TPdfToolsCrypto_HashAlgorithm;

/**
 * @brief Cryptographic signature algorithm
 */
typedef enum TPdfToolsCrypto_SignatureAlgorithm
{
    /**
     * @brief RSA with PKCS#1 v1.5
    This is the RSA with PKCS#1 v1.5 algorithm which is widely supported by cryptographic providers.

     */
    ePdfToolsCrypto_SignatureAlgorithm_RsaRsa = 1,
    /**
     * @brief RSA with SSA-PSS (PKCS#1 v2.1)
    This algorithm is generally recommended because it is considered a more secure alternative to `RSA_RSA`.
    However, it is not supported by all cryptographic providers.

     */
    ePdfToolsCrypto_SignatureAlgorithm_RsaSsaPss = 2,
    /**
     * @brief Elliptic Curve Digital Signature Algorithm
    This algorithm is generally recommended for new applications.
    However, it is not supported by all cryptographic providers.

     */
    ePdfToolsCrypto_SignatureAlgorithm_Ecdsa = 3,
} TPdfToolsCrypto_SignatureAlgorithm;

/**
 * @brief Padding scheme of the cryptographic signature algorithm
The signature algorithm is defined by the signing certificate's key type.
For example, RSA or ECDSA.
For some keys, e.g. RSA keys, there are different padding algorithms.
Some cryptographic providers let you set this padding algorithm.
However, this only has an effect on signatures created by the cryptographic provider itself.
All signed data acquired from external sources may use other signing algorithms;
more specifically, the issuer certificates of the trust chain, the time-stamp’s signature,
or those used for the revocation information (CRL, OCSP).
It is recommended to verify that the algorithms of all signatures provide a similar level of security.

 */
typedef enum TPdfToolsCrypto_SignaturePaddingType
{
    /**
     * @brief Default padding scheme
    The default padding scheme.
    Used for the \ref ePdfToolsCrypto_SignatureAlgorithm_Ecdsa "" signature algorithm.

     */
    ePdfToolsCrypto_SignaturePaddingType_Default = 0,
    /**
     * @brief RSA with PKCS#1 padding scheme
    Padding scheme for RSA keys that corresponds to the \ref ePdfToolsCrypto_SignatureAlgorithm_RsaRsa "" signature
    algorithm.

     */
    ePdfToolsCrypto_SignaturePaddingType_RsaRsa = 1,
    /**
     * @brief RSA with Probabilistic Signature Scheme (PSS)
    Padding scheme for RSA keys that corresponds to the \ref ePdfToolsCrypto_SignatureAlgorithm_RsaSsaPss "" signature
    algorithm.

     */
    ePdfToolsCrypto_SignaturePaddingType_RsaSsaPss = 2,
} TPdfToolsCrypto_SignaturePaddingType;

/**
 */
typedef enum TPdfToolsCrypto_SignatureFormat
{
    /**
     * @brief Legacy PAdES Basic signature (PDF 1.6)
    Legacy PAdES Basic signature specified by ETSI TS 102 778, Part 2.
    This type can be used for document signatures and certification (MDP) signatures.

     */
    ePdfToolsCrypto_SignatureFormat_AdbePkcs7Detached = 1,
    /**
     * @brief PAdES signature (PDF 2.0)
    PAdES signature as specified by European Standard ETSI EN 319 142.
    This type can be used for document signatures and certification (MDP) signatures.

     */
    ePdfToolsCrypto_SignatureFormat_EtsiCadesDetached = 2,
} TPdfToolsCrypto_SignatureFormat;

/**
 * @brief Whether to embed validation information to enable the long-term validation (LTV) of the signature

Embed revocation information such as online certificate status response (OCSP - RFC2560) and certificate revocation
lists (CRL - RFC3280). Revocation information of a certificate is provided by a validation service at the time of
signing and acts as proof that the certificate was valid at the time of signing. This is useful because even when the
certificate expires or is revoked at a later time, the signature in the signed document remains valid.

Embedding revocation information is optional but suggested when applying advanced or qualified electronic signatures.
This feature is not always available.
It has to be supported by the signing certificate and the cryptographic provider.
Also, it is not supported by document time-stamp signatures.
For these cases, a subsequent invocation of \ref PdfToolsSign_Signer_Process "" with
\ref PdfToolsSign_OutputOptions_GetAddValidationInformation ""
is required.

Revocation information is embedded for the signing certificate and all certificates of its trust chain.
This implies that both OCSP responses and CRLs can be present in the same message.
The disadvantages of embedding revocation information are the increase of the file size (normally by around 20KB),
and that it requires a web request to a validation service, which delays the process of signing.
Embedding revocation information requires an online connection to the CA that issues them.
The firewall must be configured accordingly.
If a web proxy is used (see \ref PdfTools_Sdk_GetProxy ""), make sure the following MIME types are supported:
  - `application/ocsp-request`
  - `application/ocsp-response`

 */
typedef enum TPdfToolsCrypto_ValidationInformation
{
    /**
     * @brief Basic: Do not add any validation information
     */
    ePdfToolsCrypto_ValidationInformation_None = 0,
    /**
     * @brief LTV: Embed validation information into the signature
    This is only possible for Legacy PAdES Basic signatures (signature format \ref
    ePdfToolsCrypto_SignatureFormat_AdbePkcs7Detached "").

     */
    ePdfToolsCrypto_ValidationInformation_EmbedInSignature = 1,
    /**
     * @brief LTV: Embed validation information into the document

    Embedding validation information into the document security store (DSS) is recommended,
    because it creates smaller files and is supported for all signature formats.

    The document security store has been standardized in 2009 by the standard for PAdES-LTV Profiles (ETSI TS 102
    778-4). Therefore, some legacy signature validation software may not support this. For these cases, it is necessary
    to use `EmbedInSignature`.

     */
    ePdfToolsCrypto_ValidationInformation_EmbedInDocument = 2,
} TPdfToolsCrypto_ValidationInformation;

/**
 * @brief Main status indication of the signature validation process
See ETSI TS 102 853 and ETSI EN 319 102-1.

 */
typedef enum TPdfToolsSignatureValidation_Indication
{
    /**
     * @brief The constraint is valid according to the chosen signature validation profile.
     */
    ePdfToolsSignatureValidation_Indication_Valid = 1,
    /**
     * @brief The constraint is invalid according to the chosen signature validation profile.
     */
    ePdfToolsSignatureValidation_Indication_Invalid = 2,
    /**
     * @brief The available information is insufficient to determine whether the signature is valid or invalid.
     */
    ePdfToolsSignatureValidation_Indication_Indeterminate = 3,
} TPdfToolsSignatureValidation_Indication;

/**
 * @brief Sub-status indication of the signature validation process
See ETSI TS 102 853 and ETSI EN 319 102-1.

 */
typedef enum TPdfToolsSignatureValidation_SubIndication
{
    /**
     * @brief The signer's certificate has been revoked.
     */
    ePdfToolsSignatureValidation_SubIndication_Revoked = 1,
    /**
     * @brief The signature is invalid because at least one hash of the signed data object(s) included in the signing
     * process does not match the corresponding hash value in the signature.
     */
    ePdfToolsSignatureValidation_SubIndication_HashFailure = 2,
    /**
     * @brief The signature is invalid because the signature value in the signature could not be verified using the
     * signer's public key in the signer's certificate.
     */
    ePdfToolsSignatureValidation_SubIndication_SigCryptoFailure = 3,
    /**
     * @brief The signature is considered invalid because one or more properties of the signature do not match the
     * validation constraints.
     */
    ePdfToolsSignatureValidation_SubIndication_SigConstraintsFailure = 4,
    /**
     * @brief The signature is considered invalid because the certificate chain used in the validation process does not
     * match the validation constraints related to the certificate.
     */
    ePdfToolsSignatureValidation_SubIndication_ChainConstraintsFailure = 5,
    /**
     * @brief The signature is considered invalid because at least one of the algorithms used in an element (e.g. the
     * signature value, a certificate, etc.) has been considered unreliable. Either the algorithm used to invalidate the
     * signature or the size of the keys used by the algorithm are no longer considered secure. The Signature Validation
     * Algorithm has detected that this element was generated after this algorithm was deemed insecure.
     */
    ePdfToolsSignatureValidation_SubIndication_CryptoConstraintsFailure = 6,
    /**
     * @brief The signature is considered invalid because the Signature Validation Algorithm has detected that the
     * signing time is after the expiration date (notAfter) of the signer's certificate.
     */
    ePdfToolsSignatureValidation_SubIndication_Expired = 7,
    /**
     * @brief The signature is considered invalid because the Signature Validation Algorithm has detected that the
     * signing time is before the issue date (notBefore) of the signer's certificate.
     */
    ePdfToolsSignatureValidation_SubIndication_NotYetValid = 8,
    /**
     * @brief The signature is not conformant to one of the base standards
     */
    ePdfToolsSignatureValidation_SubIndication_FormatFailure = 9,
    /**
     * @brief The formal policy file could not be processed (e.g. not accessible, not parsable, etc.)
     */
    ePdfToolsSignatureValidation_SubIndication_PolicyProcessingError = 10,
    /**
     * @brief The signature was created using a policy and commitment type that is unknown to the SVA.
     */
    ePdfToolsSignatureValidation_SubIndication_UnknownCommitmentType = 11,
    /**
     * @brief Constraints on the order of signature time-stamps and/or signed data object (s) time-stamps are not
     * respected.
     */
    ePdfToolsSignatureValidation_SubIndication_TimestampOrderFailure = 12,
    /**
     * @brief The signer's certificate cannot be identified.
     */
    ePdfToolsSignatureValidation_SubIndication_NoSignerCertificateFound = 13,
    /**
     * @brief No certificate chain has been found for the identified signer's certificate.
     */
    ePdfToolsSignatureValidation_SubIndication_NoCertificateChainFound = 14,
    /**
     * @brief The signer's certificate was revoked at the validation date/time. The Signature Validation Algorithm
     * cannot determine whether the signing time is before or after the revocation time.
     */
    ePdfToolsSignatureValidation_SubIndication_RevokedNoPoe = 15,
    /**
     * @brief At least one certificate chain was found, but an intermediate CA certificate has been revoked.
     */
    ePdfToolsSignatureValidation_SubIndication_RevokedCaNoPoe = 16,
    /**
     * @brief The signer's certificate is expired or not yet valid at the validation date/time. The Signature Validation
     * Algorithm cannot determine that the signing time is within the validity interval of the signer's certificate.
     */
    ePdfToolsSignatureValidation_SubIndication_OutOfBoundsNoPoe = 17,
    /**
     * @brief At least one of the algorithms used in an element (e.g. the signature value, a certificate, etc.) to
     * validate the signature or the size of the keys used in the algorithm are no longer considered reliable at the
     * validation date/time. The Signature Validation Algorithm cannot determine whether the element was generated
     * before or after the algorithm or the size of the keys were considered unreliable.
     */
    ePdfToolsSignatureValidation_SubIndication_CryptoConstraintsFailureNoPoe = 18,
    /**
     * @brief A proof of existence that proves whether a signed object was produced before a compromising event (e.g.
     * broken algorithm) is missing
     */
    ePdfToolsSignatureValidation_SubIndication_NoPoe = 19,
    /**
     * @brief Insufficient information to fulfill all constraints. It may be possible to fulfill all constraints with
     * additional revocation information that will be available at a later point of time.
     */
    ePdfToolsSignatureValidation_SubIndication_TryLater = 20,
    /**
     * @brief The policy to use for validation could not be identified.
     */
    ePdfToolsSignatureValidation_SubIndication_NoPolicy = 21,
    /**
     * @brief Cannot obtain signed data.
     */
    ePdfToolsSignatureValidation_SubIndication_SignedDataNotFound = 22,
    /**
     * @brief The certificate's chain is incomplete. The Signature Validation Algorithm cannot determine whether the
     * certificate is trusted.
     */
    ePdfToolsSignatureValidation_SubIndication_IncompleteCertificateChain = 512,
    /**
     * @brief The certificate has no revocation information. The Signature Validation Algorithm cannot determine whether
     * the certificate has been revoked.
     */
    ePdfToolsSignatureValidation_SubIndication_CertificateNoRevocationInformation = 513,
    /**
     * @brief No revocation information is available in the revocation information sources. The Signature Validation
     * Algorithm cannot determine whether the certificate has been revoked.
     */
    ePdfToolsSignatureValidation_SubIndication_MissingRevocationInformation = 514,
    /**
     * @brief The certificate has expired and no revocation information is available in the signature or document. The
     * Signature Validation Algorithm cannot determine whether the certificate has been revoked.
     */
    ePdfToolsSignatureValidation_SubIndication_ExpiredNoRevocationInformation = 515,
    /**
     * @brief The certificate is not trusted because there is no valid path to a trust anchor.
     */
    ePdfToolsSignatureValidation_SubIndication_Untrusted = 516,
    /**
     * @brief Any other reason
     */
    ePdfToolsSignatureValidation_SubIndication_Generic = 1024,
} TPdfToolsSignatureValidation_SubIndication;

/**
 * @brief Select the signatures
 */
typedef enum TPdfToolsSignatureValidation_SignatureSelector
{
    /**
     * @brief Select the latest signature.
     */
    ePdfToolsSignatureValidation_SignatureSelector_Latest = 1,
    /**
     * @brief Select all signatures.
     */
    ePdfToolsSignatureValidation_SignatureSelector_All = 2,
} TPdfToolsSignatureValidation_SignatureSelector;

/**
 * @brief The source of the validation time
 */
typedef enum TPdfToolsSignatureValidation_TimeSource
{
    /**
     * @brief Proof of Existence
    A proof of existence is evidence that proves that an object (a certificate, a CRL, signature value, hash value,
    etc.) existed at a specific time, which may be a time in the past. The presence of a given object at the current
    time is a proof of its existence at the current time. A suitable way of providing proof of existence of an object at
    a time in the past is to generate a time-stamp for that object.

     */
    ePdfToolsSignatureValidation_TimeSource_ProofOfExistence = 0x0001,
    /**
     * @brief Expired time stamp
    An expired time-stamp was used.
    Note that for expired time-stamps revocation information checks might not be possible.

     */
    ePdfToolsSignatureValidation_TimeSource_ExpiredTimeStamp = 0x0002,
    /**
     * @brief Signature time
    Use the claimed (untrusted) time of the signature.

     */
    ePdfToolsSignatureValidation_TimeSource_SignatureTime = 0x0004,
} TPdfToolsSignatureValidation_TimeSource;

/**
 * @brief The source of data such as certificates, OCRPs or CRLs
 */
typedef enum TPdfToolsSignatureValidation_DataSource
{
    /**
     * @brief Data embedded in the signature
    Allowed data: certificates, OCSP, CRL

     */
    ePdfToolsSignatureValidation_DataSource_EmbedInSignature = 0x0001,
    /**
     * @brief Data embedded in the document security store (DSS)
    Allowed data: certificates, OCSP, CRL

     */
    ePdfToolsSignatureValidation_DataSource_EmbedInDocument = 0x0002,
    /**
     * @brief Data retrieved online or from the local download cache

    Allowed data: issuer certificates (for certificates that have caIssuers extension), OCSP, CRL

    Note: only data for certificates that are time-valid at the current time can be downloaded.
    For example, OCSP and CRL can only be downloaded for certificates that have not yet expired.

     */
    ePdfToolsSignatureValidation_DataSource_Download = 0x0004,
    /**
     * @brief Data from the local system cache
    Allowed data: certificates

     */
    ePdfToolsSignatureValidation_DataSource_System = 0x0008,
    /**
     * @brief From the Adobe Approved Trust List (AATL)

    NOTE: Support for this trust list has not yet been implemented.

    Allowed data: issuer certificates

     */
    ePdfToolsSignatureValidation_DataSource_Aatl = 0x0100,
    /**
     * @brief From the European Trust List (EUTL)

    NOTE: Support for this trust list has not yet been implemented.

    Allowed data: issuer certificates

     */
    ePdfToolsSignatureValidation_DataSource_Eutl = 0x0200,
    /**
     * @brief From the custom trust list

    The list of certificates defined by the \ref TPdfToolsSignatureValidation_CustomTrustList "".
    If no custom trust list has been defined, this value has no effect.

    Allowed data: issuer certificates

     */
    ePdfToolsSignatureValidation_DataSource_CustomTrustList = 0x0400,
} TPdfToolsSignatureValidation_DataSource;

/**
 * @brief The revocation check policy
 */
typedef enum TPdfToolsSignatureValidationProfiles_RevocationCheckPolicy
{
    /**
      - Certificate must have revocation information (OCSP or CRL)
      - Revocation information is acquired from revocation sources
      - Revocation information is validated

     */
    ePdfToolsSignatureValidationProfiles_RevocationCheckPolicy_Required = 1,
    /**
    Same as `Required` for certificates that have revocation information and `NoCheck` otherwise.

     */
    ePdfToolsSignatureValidationProfiles_RevocationCheckPolicy_Supported = 2,
    /**
    Same as `Supported` if revocation information is available in the `RevocationInformationSources` and `NoCheck`
    otherwise.

     */
    ePdfToolsSignatureValidationProfiles_RevocationCheckPolicy_Optional = 3,
    /**
     * @brief Do not check revocation information.
     */
    ePdfToolsSignatureValidationProfiles_RevocationCheckPolicy_NoCheck = 4,
} TPdfToolsSignatureValidationProfiles_RevocationCheckPolicy;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsPdf_OutputOptions
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsPdf_OutputOptions. The other items refer to
 * the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsPdf_OutputOptions*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsPdf_OutputOptions_GetType function of
 * the parent class: `TPdfToolsPdf_OutputOptionsType iChildType = PdfToolsPdf_OutputOptions_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsPdf_OutputOptionsType
{
    ePdfToolsPdf_OutputOptionsType_OutputOptions,
    ePdfToolsPdf_OutputOptionsType_PdfToolsSign_OutputOptions
} TPdfToolsPdf_OutputOptionsType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsPdf_Document
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsPdf_Document. The other items refer to the
 * derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsPdf_Document*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsPdf_Document_GetType function of the
 * parent class: `TPdfToolsPdf_DocumentType iChildType = PdfToolsPdf_Document_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsPdf_DocumentType
{
    ePdfToolsPdf_DocumentType_Document,
    ePdfToolsPdf_DocumentType_PdfToolsSign_PreparedDocument
} TPdfToolsPdf_DocumentType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsPdf_SignatureField
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsPdf_SignatureField. The other items refer to
 * the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsPdf_SignatureField*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsPdf_SignatureField_GetType function of
 * the parent class: `TPdfToolsPdf_SignatureFieldType iChildType =
 * PdfToolsPdf_SignatureField_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsPdf_SignatureFieldType
{
    ePdfToolsPdf_SignatureFieldType_SignatureField,
    ePdfToolsPdf_SignatureFieldType_UnsignedSignatureField,
    ePdfToolsPdf_SignatureFieldType_SignedSignatureField,
    ePdfToolsPdf_SignatureFieldType_Signature,
    ePdfToolsPdf_SignatureFieldType_DocumentSignature,
    ePdfToolsPdf_SignatureFieldType_CertificationSignature,
    ePdfToolsPdf_SignatureFieldType_DocumentTimestamp
} TPdfToolsPdf_SignatureFieldType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsPdf_SignedSignatureField
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsPdf_SignedSignatureField. The other items
 * refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsPdf_SignedSignatureField*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsPdf_SignedSignatureField_GetType
 * function of the parent class: `TPdfToolsPdf_SignedSignatureFieldType iChildType =
 * PdfToolsPdf_SignedSignatureField_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsPdf_SignedSignatureFieldType
{
    ePdfToolsPdf_SignedSignatureFieldType_SignedSignatureField,
    ePdfToolsPdf_SignedSignatureFieldType_Signature,
    ePdfToolsPdf_SignedSignatureFieldType_DocumentSignature,
    ePdfToolsPdf_SignedSignatureFieldType_CertificationSignature,
    ePdfToolsPdf_SignedSignatureFieldType_DocumentTimestamp
} TPdfToolsPdf_SignedSignatureFieldType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsPdf_Signature
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsPdf_Signature. The other items refer to the
 * derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsPdf_Signature*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsPdf_Signature_GetType function of the
 * parent class: `TPdfToolsPdf_SignatureType iChildType = PdfToolsPdf_Signature_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsPdf_SignatureType
{
    ePdfToolsPdf_SignatureType_Signature,
    ePdfToolsPdf_SignatureType_DocumentSignature,
    ePdfToolsPdf_SignatureType_CertificationSignature
} TPdfToolsPdf_SignatureType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsImage_Document
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsImage_Document. The other items refer to the
 * derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsImage_Document*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsImage_Document_GetType function of the
 * parent class: `TPdfToolsImage_DocumentType iChildType = PdfToolsImage_Document_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsImage_DocumentType
{
    ePdfToolsImage_DocumentType_Document,
    ePdfToolsImage_DocumentType_SinglePageDocument,
    ePdfToolsImage_DocumentType_MultiPageDocument
} TPdfToolsImage_DocumentType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsOptimizationProfiles_Profile
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsOptimizationProfiles_Profile. The other items
 * refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsOptimizationProfiles_Profile*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsOptimizationProfiles_Profile_GetType
 * function of the parent class: `TPdfToolsOptimizationProfiles_ProfileType iChildType =
 * PdfToolsOptimizationProfiles_Profile_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsOptimizationProfiles_ProfileType
{
    ePdfToolsOptimizationProfiles_ProfileType_Profile,
    ePdfToolsOptimizationProfiles_ProfileType_Web,
    ePdfToolsOptimizationProfiles_ProfileType_Print,
    ePdfToolsOptimizationProfiles_ProfileType_Archive,
    ePdfToolsOptimizationProfiles_ProfileType_MinimalFileSize,
    ePdfToolsOptimizationProfiles_ProfileType_Mrc
} TPdfToolsOptimizationProfiles_ProfileType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsPdf2Image_ImageOptions
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsPdf2Image_ImageOptions. The other items refer
 * to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsPdf2Image_ImageOptions*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsPdf2Image_ImageOptions_GetType function
 * of the parent class: `TPdfToolsPdf2Image_ImageOptionsType iChildType =
 * PdfToolsPdf2Image_ImageOptions_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsPdf2Image_ImageOptionsType
{
    ePdfToolsPdf2Image_ImageOptionsType_ImageOptions,
    ePdfToolsPdf2Image_ImageOptionsType_FaxImageOptions,
    ePdfToolsPdf2Image_ImageOptionsType_TiffJpegImageOptions,
    ePdfToolsPdf2Image_ImageOptionsType_TiffLzwImageOptions,
    ePdfToolsPdf2Image_ImageOptionsType_TiffFlateImageOptions,
    ePdfToolsPdf2Image_ImageOptionsType_PngImageOptions,
    ePdfToolsPdf2Image_ImageOptionsType_JpegImageOptions
} TPdfToolsPdf2Image_ImageOptionsType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsPdf2Image_ImageSectionMapping
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsPdf2Image_ImageSectionMapping. The other
 * items refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsPdf2Image_ImageSectionMapping*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsPdf2Image_ImageSectionMapping_GetType
 * function of the parent class: `TPdfToolsPdf2Image_ImageSectionMappingType iChildType =
 * PdfToolsPdf2Image_ImageSectionMapping_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsPdf2Image_ImageSectionMappingType
{
    ePdfToolsPdf2Image_ImageSectionMappingType_ImageSectionMapping,
    ePdfToolsPdf2Image_ImageSectionMappingType_RenderPageAsFax,
    ePdfToolsPdf2Image_ImageSectionMappingType_RenderPageAtResolution,
    ePdfToolsPdf2Image_ImageSectionMappingType_RenderPageToMaxImageSize
} TPdfToolsPdf2Image_ImageSectionMappingType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsPdf2ImageProfiles_Profile
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsPdf2ImageProfiles_Profile. The other items
 * refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsPdf2ImageProfiles_Profile*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsPdf2ImageProfiles_Profile_GetType
 * function of the parent class: `TPdfToolsPdf2ImageProfiles_ProfileType iChildType =
 * PdfToolsPdf2ImageProfiles_Profile_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsPdf2ImageProfiles_ProfileType
{
    ePdfToolsPdf2ImageProfiles_ProfileType_Profile,
    ePdfToolsPdf2ImageProfiles_ProfileType_Fax,
    ePdfToolsPdf2ImageProfiles_ProfileType_Archive,
    ePdfToolsPdf2ImageProfiles_ProfileType_Viewing
} TPdfToolsPdf2ImageProfiles_ProfileType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsImage2Pdf_ImageMapping
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsImage2Pdf_ImageMapping. The other items refer
 * to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsImage2Pdf_ImageMapping*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsImage2Pdf_ImageMapping_GetType function
 * of the parent class: `TPdfToolsImage2Pdf_ImageMappingType iChildType =
 * PdfToolsImage2Pdf_ImageMapping_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsImage2Pdf_ImageMappingType
{
    ePdfToolsImage2Pdf_ImageMappingType_ImageMapping,
    ePdfToolsImage2Pdf_ImageMappingType_Auto,
    ePdfToolsImage2Pdf_ImageMappingType_ShrinkToPage,
    ePdfToolsImage2Pdf_ImageMappingType_ShrinkToFit,
    ePdfToolsImage2Pdf_ImageMappingType_ShrinkToPortrait
} TPdfToolsImage2Pdf_ImageMappingType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsImage2PdfProfiles_Profile
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsImage2PdfProfiles_Profile. The other items
 * refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsImage2PdfProfiles_Profile*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsImage2PdfProfiles_Profile_GetType
 * function of the parent class: `TPdfToolsImage2PdfProfiles_ProfileType iChildType =
 * PdfToolsImage2PdfProfiles_Profile_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsImage2PdfProfiles_ProfileType
{
    ePdfToolsImage2PdfProfiles_ProfileType_Profile,
    ePdfToolsImage2PdfProfiles_ProfileType_Default,
    ePdfToolsImage2PdfProfiles_ProfileType_Archive
} TPdfToolsImage2PdfProfiles_ProfileType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsSign_SignatureConfiguration
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsSign_SignatureConfiguration. The other items
 * refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsSign_SignatureConfiguration*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsSign_SignatureConfiguration_GetType
 * function of the parent class: `TPdfToolsSign_SignatureConfigurationType iChildType =
 * PdfToolsSign_SignatureConfiguration_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsSign_SignatureConfigurationType
{
    ePdfToolsSign_SignatureConfigurationType_SignatureConfiguration,
    ePdfToolsSign_SignatureConfigurationType_PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration,
    ePdfToolsSign_SignatureConfigurationType_PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration,
    ePdfToolsSign_SignatureConfigurationType_PdfToolsCryptoProvidersPkcs11_SignatureConfiguration,
    ePdfToolsSign_SignatureConfigurationType_PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration
} TPdfToolsSign_SignatureConfigurationType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsSign_TimestampConfiguration
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsSign_TimestampConfiguration. The other items
 * refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsSign_TimestampConfiguration*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsSign_TimestampConfiguration_GetType
 * function of the parent class: `TPdfToolsSign_TimestampConfigurationType iChildType =
 * PdfToolsSign_TimestampConfiguration_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsSign_TimestampConfigurationType
{
    ePdfToolsSign_TimestampConfigurationType_TimestampConfiguration,
    ePdfToolsSign_TimestampConfigurationType_PdfToolsCryptoProvidersGlobalSignDss_TimestampConfiguration,
    ePdfToolsSign_TimestampConfigurationType_PdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration,
    ePdfToolsSign_TimestampConfigurationType_PdfToolsCryptoProvidersPkcs11_TimestampConfiguration,
    ePdfToolsSign_TimestampConfigurationType_PdfToolsCryptoProvidersBuiltIn_TimestampConfiguration
} TPdfToolsSign_TimestampConfigurationType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsCryptoProviders_Provider
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsCryptoProviders_Provider. The other items
 * refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsCryptoProviders_Provider*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref PdfToolsCryptoProviders_Provider_GetType
 * function of the parent class: `TPdfToolsCryptoProviders_ProviderType iChildType =
 * PdfToolsCryptoProviders_Provider_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsCryptoProviders_ProviderType
{
    ePdfToolsCryptoProviders_ProviderType_Provider,
    ePdfToolsCryptoProviders_ProviderType_PdfToolsCryptoProvidersGlobalSignDss_Session,
    ePdfToolsCryptoProviders_ProviderType_PdfToolsCryptoProvidersSwisscomSigSrv_Session,
    ePdfToolsCryptoProviders_ProviderType_PdfToolsCryptoProvidersPkcs11_Session,
    ePdfToolsCryptoProviders_ProviderType_PdfToolsCryptoProvidersBuiltIn_Provider
} TPdfToolsCryptoProviders_ProviderType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsSignatureValidation_SignatureContent
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsSignatureValidation_SignatureContent. The
 * other items refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsSignatureValidation_SignatureContent*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref
 * PdfToolsSignatureValidation_SignatureContent_GetType function of the parent class:
 * `TPdfToolsSignatureValidation_SignatureContentType iChildType =
 * PdfToolsSignatureValidation_SignatureContent_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsSignatureValidation_SignatureContentType
{
    ePdfToolsSignatureValidation_SignatureContentType_SignatureContent,
    ePdfToolsSignatureValidation_SignatureContentType_UnsupportedSignatureContent,
    ePdfToolsSignatureValidation_SignatureContentType_CmsSignatureContent,
    ePdfToolsSignatureValidation_SignatureContentType_TimeStampContent
} TPdfToolsSignatureValidation_SignatureContentType;

/**
 * @brief Type and subtype enumeration of \ref TPdfToolsSignatureValidationProfiles_Profile
 *
 * This SDK uses a class hierarchy, where child types can be derived from parent types.
 * The first item of the enumeration refers to the base type \ref TPdfToolsSignatureValidationProfiles_Profile. The
 * other items refer to the derived types.
 *
 * Downcasting may be necessary. For example, to call the functions of an object’s parent class.
 * In this case, a handle of the child type can be casted using a simple C-style cast:
 * `(TPdfToolsSignatureValidationProfiles_Profile*)pChildTypeHandle`.
 *
 * Upcasting is also possible using a C-style cast.
 * Before casting, determine the child type of the handle using the \ref
 * PdfToolsSignatureValidationProfiles_Profile_GetType function of the parent class:
 * `TPdfToolsSignatureValidationProfiles_ProfileType iChildType =
 * PdfToolsSignatureValidationProfiles_Profile_GetType(pParentTypeHandle)`.
 */
typedef enum TPdfToolsSignatureValidationProfiles_ProfileType
{
    ePdfToolsSignatureValidationProfiles_ProfileType_Profile,
    ePdfToolsSignatureValidationProfiles_ProfileType_Default
} TPdfToolsSignatureValidationProfiles_ProfileType;

/**
 * \class TPdfTools_ConsumptionData
This class contains page-based license usage data.

 */
typedef struct TPdfTools_ConsumptionData TPdfTools_ConsumptionData;
/**
 * \class TPdfTools_LicenseInfo
This class contains license information.

 */
typedef struct TPdfTools_LicenseInfo TPdfTools_LicenseInfo;
/**
 * \class TPdfTools_Sdk
 * @brief SDK initialization and product information
 */
typedef struct TPdfTools_Sdk TPdfTools_Sdk;
/**
 * \class TPdfTools_StringList
 */
typedef struct TPdfTools_StringList TPdfTools_StringList;
/**
 * \class TPdfTools_MetadataDictionary
 */
typedef struct TPdfTools_MetadataDictionary TPdfTools_MetadataDictionary;
/**
 * \class TPdfTools_HttpClientHandler
 * @brief The handler and options for communication to remote server

This class can be used to configure HTTP and HTTPS communication.

Also see \ref PdfTools_Sdk_GetProxy "" for the product wide proxy configuration.

For HTTPS (SSL/TLS) communication, the server certificate's trustworthiness is verified using the system's default trust
store (CA certificate store). If the server certificate's trustworthiness cannot be determined, the connection to the
server is aborted.

The default trust store is:
  - <b>Windows:</b>
    The Windows certificate store for "Trusted Root Certification Authorities" is used.
You can manually install the root certificate of a private CA on a computer by using the `CertMgr` tool.
The certificate store is only available if the user profile has been loaded.
  - <b>Linux:</b>
    The certificates available in `CAfile` and `CApath` are trusted:
    - `CAfile`:
    The file can contain a concatenated sequence of CA certificates in PEM format.
    The SDK searches for the file at the following locations:
    - The file of your local OpenSSL installation (if `libssl.so` is found), or
    - the environment variable `SSL_CERT_FILE`, or
    - the default location `/etc/ssl/cert.pem`.
    - `CApath`:
    A directory containing CA certificates in PEM format.
The files are looked up by the CA subject name hash value, e.g. `9d66eef0.0`.
    The SDK searches for the directory at the following locations:
    - The directory of your local OpenSSL installation (if `libssl.so` is found), or
    - the environment variable `SSL_CERT_DIR`, or
    - the default location `/etc/ssl/certs/`.
  - <b>macOS: </b>
    The trusted certificates from the macOS keychain are used.
You can manually install the root certificate of a private CA by dragging the certificate file onto the Keychain Access
app.

You can add more certificates to the trust store using \ref PdfTools_HttpClientHandler_AddTrustedCertificate "".

Instances of this class can be used in multiple threads concurrently, as long as they are not modified concurrently.

 */
typedef struct TPdfTools_HttpClientHandler TPdfTools_HttpClientHandler;
/**
 * \class TPdfToolsPdf_MetadataSettings
It allows you to set and update individual metadata properties.
Any metadata properties that have been explicitly set are included in the output document.

 */
typedef struct TPdfToolsPdf_MetadataSettings TPdfToolsPdf_MetadataSettings;
/**
 * \class TPdfToolsPdf_Encryption
 * @brief The parameters to encrypt PDF documents

PDF document can be encrypted to protect content from unauthorized access.
The encryption process applies encryption to all streams (e.g. images) and strings, but not to other items in the PDF
document. This means the structure of the PDF document is accessible, but the content of its pages is encrypted.

The standard security handler allows access permissions and up to two passwords to be specified for a document:
A user password (see \ref PdfToolsPdf_Encryption_GetUserPassword "") and an owner password (see \ref
PdfToolsPdf_Encryption_GetOwnerPassword "").

The following list shows the four possible combinations of passwords and how an application processing such a PDF
document behaves:

  - <b>No user password, no owner password (no encryption):</b>
    Everyone can read, i.e. no password required to open the document.
Everyone can change security settings.
  - <b>No user password, owner password:</b>
    Everyone can read, i.e. no password required to open the document.
Access permissions are restricted (unless the owner password is provided).
Owner password required to change security settings.
  - <b>User password, no owner password:</b>
    User password required to read.
All access permissions are granted.
  - <b>User password, owner password:</b>
    User or owner password required to read.
Access permissions are restricted (unless the owner password is provided).
Owner password required to change security settings.

Since encryption is not allowed by the PDF/A ISO standards, PDF/A documents must not be encrypted.

 */
typedef struct TPdfToolsPdf_Encryption TPdfToolsPdf_Encryption;
/**
 * \class TPdfToolsPdf_OutputOptions
 * @brief The parameters for document-level features of output PDFs
Output options are used in many operations that create PDF documents.

 */
typedef struct TPdfToolsPdf_OutputOptions TPdfToolsPdf_OutputOptions;
/**
 * \class TPdfToolsPdf_Document
 * @brief The PDF document
PDF documents are either opened using \ref PdfToolsPdf_Document_Open "" or the result of an operation, e.g. of PDF
optimization (see \ref PdfToolsOptimization_Optimizer_OptimizeDocument "").

 */
typedef struct TPdfToolsPdf_Document TPdfToolsPdf_Document;
/**
 * \class TPdfToolsPdf_Metadata

Represents the metadata of a document or an object in a document.

For document level metadata,
all changes are reflected in both,
XMP metadata and document info dictionary depending on the conformance
of the document.

 */
typedef struct TPdfToolsPdf_Metadata TPdfToolsPdf_Metadata;
/**
 * \class TPdfToolsPdf_SignatureField
 * @brief A digital signature field
 */
typedef struct TPdfToolsPdf_SignatureField TPdfToolsPdf_SignatureField;
/**
 * \class TPdfToolsPdf_UnsignedSignatureField
 * @brief An unsigned signature field
An unsigned signature field that can be signed.
The purpose of the signature field is to indicate that the document should be signed and to
define the page and position where the visual appearance of the signature should be placed.
This is especially useful for forms and contracts that have dedicated spaces for signatures.

 */
typedef struct TPdfToolsPdf_UnsignedSignatureField TPdfToolsPdf_UnsignedSignatureField;
/**
 * \class TPdfToolsPdf_SignedSignatureField
 * @brief A base class for signature fields that have been signed
The existence of a signed signature field does not imply that the signature is valid.
The signature is not validated at all.

 */
typedef struct TPdfToolsPdf_SignedSignatureField TPdfToolsPdf_SignedSignatureField;
/**
 * \class TPdfToolsPdf_Signature
 * @brief A base class for certain signature types
 */
typedef struct TPdfToolsPdf_Signature TPdfToolsPdf_Signature;
/**
 * \class TPdfToolsPdf_DocumentSignature
 * @brief A document signature that signs the document
Document signatures are sometimes also called approval signatures.
This type of signature lets you verify the integrity of the signed part of the document and authenticate the signer’s
identity.

 */
typedef struct TPdfToolsPdf_DocumentSignature TPdfToolsPdf_DocumentSignature;
/**
 * \class TPdfToolsPdf_CertificationSignature
 * @brief A document certification (MDP) signature that certifies the document
These signatures are also called Document Modification Detection and Prevention (MDP) signatures.
This type of signature enables the detection of rejected changes specified by the author.

 */
typedef struct TPdfToolsPdf_CertificationSignature TPdfToolsPdf_CertificationSignature;
/**
 * \class TPdfToolsPdf_DocumentTimestamp
 * @brief A document time-stamp signature that time-stamps the document
This type of signature provides evidence that the document existed at a specific time and protects the document’s
integrity.

 */
typedef struct TPdfToolsPdf_DocumentTimestamp TPdfToolsPdf_DocumentTimestamp;
/**
 * \class TPdfToolsPdf_SignatureFieldList
 */
typedef struct TPdfToolsPdf_SignatureFieldList TPdfToolsPdf_SignatureFieldList;
/**
 * \class TPdfToolsPdf_Revision
 * @brief The document revision
 */
typedef struct TPdfToolsPdf_Revision TPdfToolsPdf_Revision;
/**
 * \class TPdfToolsImage_Page
 * @brief The page of an image document
 */
typedef struct TPdfToolsImage_Page TPdfToolsImage_Page;
/**
 * \class TPdfToolsImage_PageList
 * @brief The list of image pages
 */
typedef struct TPdfToolsImage_PageList TPdfToolsImage_PageList;
/**
 * \class TPdfToolsImage_Document
 * @brief The base class for image documents
Image documents are either opened using \ref PdfToolsImage_Document_Open "" or the result of an operation, e.g. of PDF
to image conversion using \ref PdfToolsPdf2Image_Converter_ConvertPage "".

 */
typedef struct TPdfToolsImage_Document TPdfToolsImage_Document;
/**
 * \class TPdfToolsImage_SinglePageDocument
 * @brief The image document of an image format that only supports single-page images
This class is used for the following image formats:
  - JPEG
  - BMP
  - GIF
  - HEIC/HEIF
  - PNG
  - JBIG2
  - JPEG2000

 */
typedef struct TPdfToolsImage_SinglePageDocument TPdfToolsImage_SinglePageDocument;
/**
 * \class TPdfToolsImage_MultiPageDocument
 * @brief The image document of an image format that supports multi-page images
This class is used for TIFF images, which can contain one or more pages.

 */
typedef struct TPdfToolsImage_MultiPageDocument TPdfToolsImage_MultiPageDocument;
/**
 * \class TPdfToolsImage_DocumentList
 * @brief List of image documents
 */
typedef struct TPdfToolsImage_DocumentList TPdfToolsImage_DocumentList;
/**
 * \class TPdfToolsDocumentAssembly_PageCopyOptions
This class determines whether and how different PDF elements are copied.

 */
typedef struct TPdfToolsDocumentAssembly_PageCopyOptions TPdfToolsDocumentAssembly_PageCopyOptions;
/**
 * \class TPdfToolsDocumentAssembly_DocumentCopyOptions
The document-level copy options applied when copying a document.

 */
typedef struct TPdfToolsDocumentAssembly_DocumentCopyOptions TPdfToolsDocumentAssembly_DocumentCopyOptions;
/**
 * \class TPdfToolsDocumentAssembly_DocumentAssembler
 * @brief The class for splitting or merging PDF documents
 */
typedef struct TPdfToolsDocumentAssembly_DocumentAssembler TPdfToolsDocumentAssembly_DocumentAssembler;
/**
 * \class TPdfToolsOptimization_ImageRecompressionOptions
 * @brief The parameters for image recompression
 */
typedef struct TPdfToolsOptimization_ImageRecompressionOptions TPdfToolsOptimization_ImageRecompressionOptions;
/**
 * \class TPdfToolsOptimization_FontOptions
 * @brief The parameters for font optimization
 */
typedef struct TPdfToolsOptimization_FontOptions TPdfToolsOptimization_FontOptions;
/**
 * \class TPdfToolsOptimization_RemovalOptions
 * @brief The parameters defining the optional data to remove or flatten

Removal options specify the PDF data structures to copy or remove,
e.g. article threads, metadata, or alternate images.

In addition, the visual appearances of signatures, annotations, form fields,
and links can be flattened.

Flattening means, that the appearance of such a data structure is drawn as
non-editable graphic onto the page; for visual appearances of signatures,
flattening has a slightly different meaning
(see property \ref PdfToolsOptimization_RemovalOptions_GetRemoveSignatureAppearances "").

 */
typedef struct TPdfToolsOptimization_RemovalOptions TPdfToolsOptimization_RemovalOptions;
/**
 * \class TPdfToolsOptimization_Optimizer
 * @brief The class to optimize PDF documents
 */
typedef struct TPdfToolsOptimization_Optimizer TPdfToolsOptimization_Optimizer;
/**
 * \class TPdfToolsOptimizationProfiles_Profile
 * @brief The base class for PDF optimization profiles
The profile defines the optimization parameters suitable for a particular
use case, e.g. archiving, or publication on the web.

 */
typedef struct TPdfToolsOptimizationProfiles_Profile TPdfToolsOptimizationProfiles_Profile;
/**
 * \class TPdfToolsOptimizationProfiles_Web
 * @brief The optimization profile suitable for electronic document exchange

All colors are converted to RGB.
Spider (web capture) information is removed.

Images above 210 DPI are down-sampled and recompressed to 150 DPI.
This leads to smaller output files. The property
\ref PdfToolsOptimizationProfiles_Web_SetResolutionDPI "" has influence on both values.

When an image is recompressed, the
\ref ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced ""
strategy is used; this can be overridden through
\ref PdfToolsOptimizationProfiles_Profile_GetImageRecompressionOptions "".

With this profile, the output PDF version is updated to PDF 1.7 or higher and
PDF/A conformance removed.

 */
typedef struct TPdfToolsOptimizationProfiles_Web TPdfToolsOptimizationProfiles_Web;
/**
 * \class TPdfToolsOptimizationProfiles_Print
 * @brief The optimization profile suitable for printing

All colors are converted to CMYK for optimal output on printing devices.
Spider (web capture) information is removed.
Embedded Type1 (PostScript) fonts are converted to Type1C
(Compact Font Format) which further reduces the file size.
The resolution of images stays untouched.

When an image is recompressed, the
\ref ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality ""
strategy is used; this can be overridden through the
property \ref PdfToolsOptimizationProfiles_Profile_GetImageRecompressionOptions "".

With this profile, the output PDF version is updated to PDF 1.7 or higher and
PDF/A conformance removed.

 */
typedef struct TPdfToolsOptimizationProfiles_Print TPdfToolsOptimizationProfiles_Print;
/**
 * \class TPdfToolsOptimizationProfiles_Archive
 * @brief The optimization profile suitable for archiving

This profile provides minimal document modification and is well suited for
reducing the file size prior to converting to PDF/A.
The optimizer itself does not create PDF/A output but
merely tries to preserve PDF/A conformance.

Alternate images and thumbnails are removed.
The resolution and color space of images stay untouched.

When an image is recompressed, the
\ref ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality ""
strategy is used; this can be overridden through the
property \ref PdfToolsOptimizationProfiles_Profile_GetImageRecompressionOptions "".

For PDF/A conforming input files, the PDF/A conformance is preserved if possible.
For other files, the PDF version is updated to PDF 1.7 or higher.

 */
typedef struct TPdfToolsOptimizationProfiles_Archive TPdfToolsOptimizationProfiles_Archive;
/**
 * \class TPdfToolsOptimizationProfiles_MinimalFileSize
 * @brief The optimization profile producing a minimal file size

This profile optimizes the output PDF for minimal file size.
This is achieved by using a varied palette of image compression
algorithms, appropriate resolution setting and higher
compression rates at the price of slightly lower image quality.

The output file size is further reduced by converting Embedded
Type1 (PostScript) fonts to Type1C (Compact Font Format) and
removing metadata and output intents
(see \ref PdfToolsOptimizationProfiles_Profile_GetRemovalOptions "").
Also Spider (web capture) information is removed.

Images above 182 DPI are down-sampled and recompressed to 130 DPI.
This leads to smaller output files. The property
\ref PdfToolsOptimizationProfiles_MinimalFileSize_SetResolutionDPI "" has influence on both values.

When an image is recompressed, the
\ref ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced ""
strategy is used; this can be overridden through the
property \ref PdfToolsOptimizationProfiles_Profile_GetImageRecompressionOptions "".

With this profile, the output PDF version is updated to PDF 1.7 or higher and
PDF/A conformance removed.

 */
typedef struct TPdfToolsOptimizationProfiles_MinimalFileSize TPdfToolsOptimizationProfiles_MinimalFileSize;
/**
 * \class TPdfToolsOptimizationProfiles_Mrc
 * @brief The optimization profile suitable for documents with Mixed Raster Content
Reduce the file size for documents containing large images, e.g. scanned pages, while maintaining the readability of
text. This is accomplished by separating the images into a foreground, background and a mask layer. The foreground and
background layers are heavily down-sampled and compressed. The textual information is stored in the mask with a lossless
compression type. Additionally, redundant objects are removed, resources are optimized and embedded fonts are merged.

 */
typedef struct TPdfToolsOptimizationProfiles_Mrc TPdfToolsOptimizationProfiles_Mrc;
/**
 * \class TPdfToolsPdf2Image_ContentOptions
 * @brief The parameters how to render PDF content elements
 */
typedef struct TPdfToolsPdf2Image_ContentOptions TPdfToolsPdf2Image_ContentOptions;
/**
 * \class TPdfToolsPdf2Image_ImageOptions
 * @brief The base class for output image options
 */
typedef struct TPdfToolsPdf2Image_ImageOptions TPdfToolsPdf2Image_ImageOptions;
/**
 * \class TPdfToolsPdf2Image_FaxImageOptions
 * @brief The settings for TIFF Fax output images
Create a black-and-white (bitonal) TIFF Fax output image.
For the output file name, it is recommended to use the file extension ".tif".

 */
typedef struct TPdfToolsPdf2Image_FaxImageOptions TPdfToolsPdf2Image_FaxImageOptions;
/**
 * \class TPdfToolsPdf2Image_TiffJpegImageOptions
 * @brief The settings for TIFF output images using the JPEG compression algorithm

TIFF allows images to be compressed with JPEG (Joint Photographic Experts Group), which is a lossy
compression algorithm. JPEG provides a high compression ratio for
8 and 24 bit images. It is best suited for TIFFs containing
photographs and little or no text.

For the output file name, it is recommended to use the file extension ".tif".

 */
typedef struct TPdfToolsPdf2Image_TiffJpegImageOptions TPdfToolsPdf2Image_TiffJpegImageOptions;
/**
 * \class TPdfToolsPdf2Image_TiffLzwImageOptions
 * @brief The settings for TIFF output images using the LZW compression algorithm

LZW (Lempel-Ziv-Welch) is a lossless compression algorithm for images. Please
consult the copyright laws of your country prior to using this
compression algorithm.

For the output file name, it is recommended to use the file extension ".tif".

 */
typedef struct TPdfToolsPdf2Image_TiffLzwImageOptions TPdfToolsPdf2Image_TiffLzwImageOptions;
/**
 * \class TPdfToolsPdf2Image_TiffFlateImageOptions
 * @brief The settings for TIFF output images using the Flate compression algorithm

Flate is a lossless compression algorithm. It is useful for the
compression of large images with no loss in quality.

For the output file name, it is recommended to use the file extension ".tif".

 */
typedef struct TPdfToolsPdf2Image_TiffFlateImageOptions TPdfToolsPdf2Image_TiffFlateImageOptions;
/**
 * \class TPdfToolsPdf2Image_PngImageOptions
 * @brief The settings for PNG output images
For the output file name, it is recommended to use the file extension ".png".

 */
typedef struct TPdfToolsPdf2Image_PngImageOptions TPdfToolsPdf2Image_PngImageOptions;
/**
 * \class TPdfToolsPdf2Image_JpegImageOptions
 * @brief The settings for JPEG output images

JPEG images use a lossy compression algorithm that provides a high compression ratio.
It is best suited for photographs and content with little or no text.

For the output file name, it is recommended to use the file extension ".jpg".

 */
typedef struct TPdfToolsPdf2Image_JpegImageOptions TPdfToolsPdf2Image_JpegImageOptions;
/**
 * \class TPdfToolsPdf2Image_ImageSectionMapping
 * @brief The base class for image section mappings
An image section mapping specifies how a PDF page, or a section of
it, is transformed (e.g. cropped or scaled) and placed
onto the target image.

 */
typedef struct TPdfToolsPdf2Image_ImageSectionMapping TPdfToolsPdf2Image_ImageSectionMapping;
/**
 * \class TPdfToolsPdf2Image_RenderPageAsFax
 * @brief The image section mapping suitable for Fax output images

Render a PDF page without scaling onto the image, top-aligned
and horizontally centered.

Note that, the image has a fixed width of 1728 pixels / 8.5 inches.

A page larger than the target image is scaled down to fit in.

 */
typedef struct TPdfToolsPdf2Image_RenderPageAsFax TPdfToolsPdf2Image_RenderPageAsFax;
/**
 * \class TPdfToolsPdf2Image_RenderPageAtResolution
 * @brief The image section mapping to render entire pages at a specific resolution

The entire PDF page is rendered into an image of the same size and the specified resolution.

For example, this mapping is suitable to create images of entire PDF pages.

 */
typedef struct TPdfToolsPdf2Image_RenderPageAtResolution TPdfToolsPdf2Image_RenderPageAtResolution;
/**
 * \class TPdfToolsPdf2Image_RenderPageToMaxImageSize
 * @brief The image section mapping to render entire pages using a specific image pixel size

Render a PDF page and scale it, thereby preserving the aspect
ratio, to fit best on the target image size. The image size is
specified in number of pixels.

For example, this mapping is suitable to create thumbnail images.

 */
typedef struct TPdfToolsPdf2Image_RenderPageToMaxImageSize TPdfToolsPdf2Image_RenderPageToMaxImageSize;
/**
 * \class TPdfToolsPdf2Image_Converter
 * @brief The class to convert a PDF document to a rasterized image
 */
typedef struct TPdfToolsPdf2Image_Converter TPdfToolsPdf2Image_Converter;
/**
 * \class TPdfToolsPdf2ImageProfiles_Profile
 * @brief The base class for PDF to image conversion profiles
The profile defines how the PDF pages are rendered and what type of output image is used.
A profile implements the converter settings suitable for a practical
use case, e.g. create images for sending over Facsimile, for
viewing, or for archiving.

 */
typedef struct TPdfToolsPdf2ImageProfiles_Profile TPdfToolsPdf2ImageProfiles_Profile;
/**
 * \class TPdfToolsPdf2ImageProfiles_Fax
 * @brief The profile to convert PDF documents to TIFF Fax images

This profile is suitable for converting PDFs into
TIFF-F conforming rasterized images for Facsimile transmission.

The output format is a multi-page TIFF file containing all
rasterized PDF pages.

By default,
  - the output images are Group 3 - compressed
  - scaled to a width of 1728 pixels, a horizontal
resolution of 204 DPI, and a vertical resolution
of 98 DPI
  - all colors and gray scale tones are converted
to bitonal by using dithering

The compression type and the vertical resolution can be set
through \ref PdfToolsPdf2ImageProfiles_Fax_GetImageOptions "".

 */
typedef struct TPdfToolsPdf2ImageProfiles_Fax TPdfToolsPdf2ImageProfiles_Fax;
/**
 * \class TPdfToolsPdf2ImageProfiles_Archive
 * @brief The profile to convert PDF documents to TIFF images for archiving

This profile is suitable for archiving PDF documents as rasterized images.

The output format is TIFF and cannot be changed.
Several compression types are configurable through
\ref PdfToolsPdf2ImageProfiles_Archive_GetImageOptions "".

By default,
  - \ref PdfToolsPdf2ImageProfiles_Archive_GetImageOptions "" is set to
\ref TPdfToolsPdf2Image_TiffLzwImageOptions ""
  - the color space of each image corresponds to the color
space of the PDF page

 */
typedef struct TPdfToolsPdf2ImageProfiles_Archive TPdfToolsPdf2ImageProfiles_Archive;
/**
 * \class TPdfToolsPdf2ImageProfiles_Viewing
 * @brief The profile to convert PDF documents to JPEG or PNG images for viewing

This profile is suitable for converting PDFs to
rasterized images for using in web and desktop viewing
applications or as thumbnails.

By default, \ref PdfToolsPdf2ImageProfiles_Viewing_GetImageOptions "" is set to
\ref TPdfToolsPdf2Image_PngImageOptions "" which uses the output format
PNG and lossless compression.
If set to \ref TPdfToolsPdf2Image_JpegImageOptions "", the output format
is JPEG.

 */
typedef struct TPdfToolsPdf2ImageProfiles_Viewing TPdfToolsPdf2ImageProfiles_Viewing;
/**
 * \class TPdfToolsImage2Pdf_ImageMapping
 * @brief The base class for image mappings
The image mapping specifies how an input image is transformed and placed
onto the output PDF page.

 */
typedef struct TPdfToolsImage2Pdf_ImageMapping TPdfToolsImage2Pdf_ImageMapping;
/**
 * \class TPdfToolsImage2Pdf_Auto
 * @brief The image mapping that automatically determines a suitable conversion

Images with a meaningful resolution, e.g. scans or graphics,
are converted to PDF pages fitting the image. The
image size is preserved if it is smaller than \ref PdfToolsImage2Pdf_Auto_GetMaxPageSize "".
Otherwise, it is scaled down.
For all images except scans, a margin \ref PdfToolsImage2Pdf_Auto_GetDefaultPageMargin "" is used.

Images with no meaningful resolution, e.g. photos are scaled, to fit onto
\ref PdfToolsImage2Pdf_Auto_GetMaxPageSize "".

 */
typedef struct TPdfToolsImage2Pdf_Auto TPdfToolsImage2Pdf_Auto;
/**
 * \class TPdfToolsImage2Pdf_ShrinkToPage
 * @brief The image mapping that places the image onto pages of the specified size
Place images onto portrait or landscape pages.
If an image is too large to fit on a page, the page may be rotated to better accommodate the image.
Large images are scaled down to fit onto the PDF page size
\ref PdfToolsImage2Pdf_ShrinkToPage_GetPageSize "".

 */
typedef struct TPdfToolsImage2Pdf_ShrinkToPage TPdfToolsImage2Pdf_ShrinkToPage;
/**
 * \class TPdfToolsImage2Pdf_ShrinkToFit
 * @brief The image mapping that places the image onto pages of the specified size
Place images onto portrait or landscape pages. Large images are scaled down
to fit onto \ref PdfToolsImage2Pdf_ShrinkToFit_GetPageSize "".

 */
typedef struct TPdfToolsImage2Pdf_ShrinkToFit TPdfToolsImage2Pdf_ShrinkToFit;
/**
 * \class TPdfToolsImage2Pdf_ShrinkToPortrait
 * @brief The image mapping that places the image onto portrait pages of the specified size
Place images onto portrait pages. Large images are scaled down
to fit onto \ref PdfToolsImage2Pdf_ShrinkToPortrait_GetPageSize "".

 */
typedef struct TPdfToolsImage2Pdf_ShrinkToPortrait TPdfToolsImage2Pdf_ShrinkToPortrait;
/**
 * \class TPdfToolsImage2Pdf_ImageOptions
 * @brief The conversion options related to the images
 */
typedef struct TPdfToolsImage2Pdf_ImageOptions TPdfToolsImage2Pdf_ImageOptions;
/**
 * \class TPdfToolsImage2Pdf_Converter
 * @brief The class to convert one or more images to a PDF document
 */
typedef struct TPdfToolsImage2Pdf_Converter TPdfToolsImage2Pdf_Converter;
/**
 * \class TPdfToolsImage2PdfProfiles_Profile
 * @brief The base class for image to PDF conversion profiles
A profile implements the conversion settings suitable for a practical
use case.

 */
typedef struct TPdfToolsImage2PdfProfiles_Profile TPdfToolsImage2PdfProfiles_Profile;
/**
 * \class TPdfToolsImage2PdfProfiles_Default
 * @brief The default profile for image to PDF conversion
This profile is suitable for the conversion of input images to PDF.

 */
typedef struct TPdfToolsImage2PdfProfiles_Default TPdfToolsImage2PdfProfiles_Default;
/**
 * \class TPdfToolsImage2PdfProfiles_Archive
 * @brief The profile for image to PDF/A conversion for archiving
This profile is suitable for archiving images as PDFs.

 */
typedef struct TPdfToolsImage2PdfProfiles_Archive TPdfToolsImage2PdfProfiles_Archive;
/**
 * \class TPdfToolsPdfAValidation_Validator
 * @brief The class to validate the standard conformance of documents
 */
typedef struct TPdfToolsPdfAValidation_Validator TPdfToolsPdfAValidation_Validator;
/**
 * \class TPdfToolsPdfAValidation_ValidationOptions
 * @brief The PDF validation options
Options to check the quality and standard conformance of documents using the validator's method \ref
PdfToolsPdfAValidation_Validator_Validate "".

 */
typedef struct TPdfToolsPdfAValidation_ValidationOptions TPdfToolsPdfAValidation_ValidationOptions;
/**
 * \class TPdfToolsPdfAValidation_ValidationResult
 * @brief The PDF validation result
Result of the validator's method \ref PdfToolsPdfAValidation_Validator_Validate "".

 */
typedef struct TPdfToolsPdfAValidation_ValidationResult TPdfToolsPdfAValidation_ValidationResult;
/**
 * \class TPdfToolsPdfAValidation_AnalysisOptions
 * @brief The PDF/A analysis options
Options for the analysis of documents using the validator's method \ref PdfToolsPdfAValidation_Validator_Analyze "" in
preparation for the document's conversion to PDF/A.

 */
typedef struct TPdfToolsPdfAValidation_AnalysisOptions TPdfToolsPdfAValidation_AnalysisOptions;
/**
 * \class TPdfToolsPdfAValidation_AnalysisResult
 * @brief The PDF/A analysis result

Result of the validator's method \ref PdfToolsPdfAValidation_Validator_Analyze "" which is required for the conversion
to PDF/A with \ref PdfToolsPdfAConversion_Converter_Convert "".

Note that \ref TPdfToolsPdfAValidation_AnalysisResult "" objects remain valid as long as their \ref
TPdfToolsPdf_Document "" has not been closed and the analysis result has not been used in \ref
PdfToolsPdfAConversion_Converter_Convert "".

 */
typedef struct TPdfToolsPdfAValidation_AnalysisResult TPdfToolsPdfAValidation_AnalysisResult;
/**
 * \class TPdfToolsPdfAConversion_Converter
 * @brief The class to convert PDF documents to PDF/A
 */
typedef struct TPdfToolsPdfAConversion_Converter TPdfToolsPdfAConversion_Converter;
/**
 * \class TPdfToolsPdfAConversion_ConversionOptions
 * @brief The PDF/A conversion options
The options for the conversion of documents using the converter's method \ref PdfToolsPdfAConversion_Converter_Convert
""

 */
typedef struct TPdfToolsPdfAConversion_ConversionOptions TPdfToolsPdfAConversion_ConversionOptions;
/**
 * \class TPdfToolsSign_CustomTextVariableMap
A map that maps custom text variable names to its value.

 */
typedef struct TPdfToolsSign_CustomTextVariableMap TPdfToolsSign_CustomTextVariableMap;
/**
 * \class TPdfToolsSign_Appearance
 * @brief The visual appearance of signatures

A signature may have a visual appearance on a page of the document.
The visual appearance is optional and has no effect on the validity of the signature.
Because of this and because a visual appearance may cover important content of the page,
it is recommended to create invisible signatures by default.

Typically, a visual appearance is created for forms with a dedicated area reserved for the appearance.
Other transaction documents, e.g. invoices, correspondence, or bank statements, are usually signed without a visual
appearance.

The appearance can be positioned on a page using \ref PdfToolsSign_Appearance_GetPageNumber "", \ref
PdfToolsSign_Appearance_GetTop "", \ref PdfToolsSign_Appearance_GetRight "", \ref PdfToolsSign_Appearance_GetBottom "",
and \ref PdfToolsSign_Appearance_GetLeft "". It is recommended to set either \ref PdfToolsSign_Appearance_GetTop "" or
\ref PdfToolsSign_Appearance_GetBottom "" and \ref PdfToolsSign_Appearance_GetRight "" or \ref
PdfToolsSign_Appearance_GetLeft "". If all are `NULL`, the default is to position the appearance in the lower right
corner with `12 pt`
(`1/6 inch` or `4.2 mm`) distance to the bottom and right edge of the page,
i.e. `Bottom = 12` and `Right = 12`.

 */
typedef struct TPdfToolsSign_Appearance TPdfToolsSign_Appearance;
/**
 * \class TPdfToolsSign_SignatureConfiguration
 * @brief Configuration for signature creation

This configuration controls the signature creation in \ref PdfToolsSign_Signer_Sign "" and \ref
PdfToolsSign_Signer_Certify "".

Use a \ref TPdfToolsCryptoProviders_Provider "" to create a signature configuration.

Note that this object can be re-used to sign multiple documents for mass-signing applications.

 */
typedef struct TPdfToolsSign_SignatureConfiguration TPdfToolsSign_SignatureConfiguration;
/**
 * \class TPdfToolsSign_TimestampConfiguration
 * @brief Configuration for adding time-stamps

This configuration controls the creation of time-stamps in \ref PdfToolsSign_Signer_AddTimestamp "".

Use a \ref TPdfToolsCryptoProviders_Provider "" to create a time-stamp configuration.

Note that this object can be re-used to add time-stamps to multiple documents for mass-signing applications.

 */
typedef struct TPdfToolsSign_TimestampConfiguration TPdfToolsSign_TimestampConfiguration;
/**
 * \class TPdfToolsSign_OutputOptions
 * @brief Additional document level options

These options are available for all signature operations of the \ref TPdfToolsSign_Signer "".
They can also be used without a signature operation with the method \ref PdfToolsSign_Signer_Process "".

Notes on document encryption when processing files with the \ref TPdfToolsSign_Signer "":
  - PDF/A conformance is removed from input files.
In this case, a \ref TPdfToolsSign_Signer_Warning "" with an \ref ePdfToolsSign_WarningCategory_PdfARemoved "" is
generated.
  - Signed documents cannot be encrypted or decrypted.
In this case, a \ref TPdfToolsSign_Signer_Warning "" with an \ref
ePdfToolsSign_WarningCategory_SignedDocEncryptionUnchanged "" is generated.

 */
typedef struct TPdfToolsSign_OutputOptions TPdfToolsSign_OutputOptions;
/**
 * \class TPdfToolsSign_MdpPermissionOptions
 * @brief The permission options when certifying a document
 */
typedef struct TPdfToolsSign_MdpPermissionOptions TPdfToolsSign_MdpPermissionOptions;
/**
 * \class TPdfToolsSign_SignatureFieldOptions
 * @brief Options for adding unsigned signature fields
These options control the creation of unsigned signature fields in \ref PdfToolsSign_Signer_AddSignatureField "".

 */
typedef struct TPdfToolsSign_SignatureFieldOptions TPdfToolsSign_SignatureFieldOptions;
/**
 * \class TPdfToolsSign_PreparedDocument
 * @brief A document that has been prepared for signing
 */
typedef struct TPdfToolsSign_PreparedDocument TPdfToolsSign_PreparedDocument;
/**
 * \class TPdfToolsSign_Signer
 * @brief Process signatures and signature fields
 */
typedef struct TPdfToolsSign_Signer TPdfToolsSign_Signer;
/**
 * \class TPdfToolsCryptoProviders_Provider
 * @brief Base class for cryptographic providers

The cryptographic provider manages certificates, their private keys and implements cryptographic algorithms.

This SDK supports various different cryptographic providers.
The following list shows the signing certificate type that can be used for each provider.

  - <b>Soft Certificate</b>:
    Soft certificates are typically PKCS#12 files that have the extension `.pfx` or `.p12` and contain
the signing certificate as well as the private key and trust chain (issuer certificates).
Soft certificates can be used with the \ref TPdfToolsCryptoProvidersBuiltIn_Provider "", where they can be loaded using
\ref PdfToolsCryptoProvidersBuiltIn_Provider_CreateSignatureFromCertificate "".
  - <b>Hardware Security Module (HSM)</b>:
    HSMs always offer very good PKCS#11 support, so the \ref TPdfToolsCryptoProvidersPkcs11_Session "" is suitable.
For more information and installation instructions, consult the separate document "TechNotePKCS11.pdf".
  - <b>USB Token or Smart Card</b>:
    These devices typically offer a PKCS#11 interface, so the recommended provider is the \ref
TPdfToolsCryptoProvidersPkcs11_Session "". Note that in any case, signing documents is only possible in an interactive
user session. So these devices cannot be used in a service or web application environment.
  - <b>Swisscom Signing Service</b>:
    The \ref TPdfToolsCryptoProvidersSwisscomSigSrv_Session "" supports both static and on-demand signing certificates.
  - <b>GlobalSign Digital Signing Service</b>:
    The \ref TPdfToolsCryptoProvidersGlobalSignDss_Session "" supports all features of the service.

 */
typedef struct TPdfToolsCryptoProviders_Provider TPdfToolsCryptoProviders_Provider;
/**
 * \class TPdfToolsCryptoProviders_Certificate
 * @brief A X.509 certificate
 */
typedef struct TPdfToolsCryptoProviders_Certificate TPdfToolsCryptoProviders_Certificate;
/**
 * \class TPdfToolsCryptoProviders_CertificateList
 */
typedef struct TPdfToolsCryptoProviders_CertificateList TPdfToolsCryptoProviders_CertificateList;
/**
 * \class TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration
 * @brief The signature configuration
 */
typedef struct TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration;
/**
 * \class TPdfToolsCryptoProvidersGlobalSignDss_TimestampConfiguration
 */
typedef struct TPdfToolsCryptoProvidersGlobalSignDss_TimestampConfiguration
    TPdfToolsCryptoProvidersGlobalSignDss_TimestampConfiguration;
/**
 * \class TPdfToolsCryptoProvidersGlobalSignDss_Session
 * @brief GlobalSign Digital Signing Service

In this session, signatures can be created using different identities, i.e. signing certificates.
Signing sessions and signing certificates expire after 10 minutes.
After this time, they are renewed automatically.

When signing with this provider, these errors can occur:
  - \ref ePdfTools_Error_Permission "": If the account's quota is reached.
  - \ref ePdfTools_Error_Retry "": If one of the account's rate limits is exceeded.
    The service enforces rate limits for both creating new identities and signing operations.
So, if multiple documents must be signed at once, it is advisable to re-use the signature configuration
(and hence its signing certificates) for signing.
  - \ref ePdfTools_Error_Http "": If a network error occurs or the service is not operational.

 */
typedef struct TPdfToolsCryptoProvidersGlobalSignDss_Session TPdfToolsCryptoProvidersGlobalSignDss_Session;
/**
 * \class TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration
 * @brief The signature configuration
 */
typedef struct TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration;
/**
 * \class TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration
 * @brief The time-stamp configuration
 */
typedef struct TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration
    TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration;
/**
 * \class TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp
 * @brief The options for step-up authorization using Mobile ID
 */
typedef struct TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp;
/**
 * \class TPdfToolsCryptoProvidersSwisscomSigSrv_Session
 * @brief The Swisscom Signing Service


When signing with this provider, these errors can occur:
  - \ref ePdfTools_Error_Permission "": The server did not accept the SSL client certificate or the Claimed Identity
string.
  - \ref ePdfTools_Error_Permission "": The requested requested distinguished name of the on-demand certificate is not
allowed (\ref PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForOnDemandIdentity "").
  - \ref ePdfTools_Error_Retry "": The signing request could not be processed on time by the service.
The service may be overloaded.
  - \ref ePdfTools_Error_IllegalArgument "": The key identity of the Claimed Identity string is invalid or not allowed.
  - \ref ePdfTools_Error_Http "": If a network error occurs or the service is not operational.

When signing with step-up authorization, these errors can also occur.
  - \ref ePdfTools_Error_Permission "": The user canceled the authorization request or failed to enter correct
authentication data (password, OTP).

 */
typedef struct TPdfToolsCryptoProvidersSwisscomSigSrv_Session TPdfToolsCryptoProvidersSwisscomSigSrv_Session;
/**
 * \class TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration
 * @brief The signature configuration
 */
typedef struct TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration;
/**
 * \class TPdfToolsCryptoProvidersPkcs11_TimestampConfiguration
 * @brief The time-stamp configuration
 */
typedef struct TPdfToolsCryptoProvidersPkcs11_TimestampConfiguration
    TPdfToolsCryptoProvidersPkcs11_TimestampConfiguration;
/**
 * \class TPdfToolsCryptoProvidersPkcs11_Module
 * @brief The PKCS#11 driver module

The PKCS#11 driver module (middleware) manages the cryptographic devices of a particular type.

<b>Note:</b> The PKCS#11 interface requires special handling of the driver modules:
  - In each application, the module can only be loaded once,
so there can only be a single `Module` instance for each driver.
Since this object is fully thread-safe, it might be used by multiple threads though.
  - The object must be closed before the application terminates.

 */
typedef struct TPdfToolsCryptoProvidersPkcs11_Module TPdfToolsCryptoProvidersPkcs11_Module;
/**
 * \class TPdfToolsCryptoProvidersPkcs11_Device
 * @brief The cryptographic device (HSM, USB token, etc.)
 */
typedef struct TPdfToolsCryptoProvidersPkcs11_Device TPdfToolsCryptoProvidersPkcs11_Device;
/**
 * \class TPdfToolsCryptoProvidersPkcs11_Session
 * @brief A session to a cryptographic device (HSM, USB token, etc.) to perform cryptographic operations

The session can be used to create signature configuration to sign documents.

To acquire a session, the following steps must be performed:
  - Load the PKCS#11 driver module using \ref PdfToolsCryptoProvidersPkcs11_Module_Load "".
  - Get the appropriate cryptographic device from the module's \ref PdfToolsCryptoProvidersPkcs11_Module_GetDevices "".
If it can be assumed that there is only a single device available, the \ref
PdfToolsCryptoProvidersPkcs11_DeviceList_GetSingle "" can be used.
  - Create a session to the device using \ref PdfToolsCryptoProvidersPkcs11_Device_CreateSession "".

 */
typedef struct TPdfToolsCryptoProvidersPkcs11_Session TPdfToolsCryptoProvidersPkcs11_Session;
/**
 * \class TPdfToolsCryptoProvidersPkcs11_DeviceList
 * @brief The list of devices managed by a PKCS#11 module
 */
typedef struct TPdfToolsCryptoProvidersPkcs11_DeviceList TPdfToolsCryptoProvidersPkcs11_DeviceList;
/**
 * \class TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration
 * @brief The signature configuration
 */
typedef struct TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration;
/**
 * \class TPdfToolsCryptoProvidersBuiltIn_TimestampConfiguration
 * @brief The time-stamp configuration
 */
typedef struct TPdfToolsCryptoProvidersBuiltIn_TimestampConfiguration
    TPdfToolsCryptoProvidersBuiltIn_TimestampConfiguration;
/**
 * \class TPdfToolsCryptoProvidersBuiltIn_Provider
 * @brief The built-in cryptographic provider

The built-in cryptographic provider requires no cryptographic hardware or external service (except for the optional
\ref PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrl "").

Signing certificates with private keys can be loaded using \ref
PdfToolsCryptoProvidersBuiltIn_Provider_CreateSignatureFromCertificate "".

<b>Certificates Directory</b>:
Additional certificates, e.g. issuer certificates, can be stored in the certificates directory.
These certificates are required when adding validation information to signatures that do not have the full trust chain
embedded. The certificates directory may contain certificates in either PEM (.pem, ASCII text) or DER (.cer, binary)
form.
  - Windows:
    - `%LOCALAPPDATA%\PDF Tools AG\Certificates`
    - `%ProgramData%\PDF Tools AG\Certificates`
  - Linux:
    - `~/.pdf-tools/Certificates` or `$TMP/pdf-tools/Certificates`
    - `/usr/share/pdf-tools/Certificates`
  - macOS:
    - `~/.pdf-tools/Certificates` or `$TMP/pdf-tools/Certificates`

 */
typedef struct TPdfToolsCryptoProvidersBuiltIn_Provider TPdfToolsCryptoProvidersBuiltIn_Provider;
/**
 * \class TPdfToolsSignatureValidation_ConstraintResult
 * @brief The result of a constraint validation.
 */
typedef struct TPdfToolsSignatureValidation_ConstraintResult TPdfToolsSignatureValidation_ConstraintResult;
/**
 * \class TPdfToolsSignatureValidation_Validator
 * @brief The class to check the validity of signatures
 */
typedef struct TPdfToolsSignatureValidation_Validator TPdfToolsSignatureValidation_Validator;
/**
 * \class TPdfToolsSignatureValidation_Certificate
 * @brief A X.509 certificate
 */
typedef struct TPdfToolsSignatureValidation_Certificate TPdfToolsSignatureValidation_Certificate;
/**
 * \class TPdfToolsSignatureValidation_CertificateChain
 */
typedef struct TPdfToolsSignatureValidation_CertificateChain TPdfToolsSignatureValidation_CertificateChain;
/**
 * \class TPdfToolsSignatureValidation_ValidationResults
 */
typedef struct TPdfToolsSignatureValidation_ValidationResults TPdfToolsSignatureValidation_ValidationResults;
/**
 * \class TPdfToolsSignatureValidation_ValidationResult
 * @brief The result of a signature validation
 */
typedef struct TPdfToolsSignatureValidation_ValidationResult TPdfToolsSignatureValidation_ValidationResult;
/**
 * \class TPdfToolsSignatureValidation_SignatureContent
 * @brief The data and validation result of the cryptographic signature
 */
typedef struct TPdfToolsSignatureValidation_SignatureContent TPdfToolsSignatureValidation_SignatureContent;
/**
 * \class TPdfToolsSignatureValidation_UnsupportedSignatureContent
 * @brief The validation result of a signature that cannot be read either because it has an unsupported type or is
 * corrupt
 */
typedef struct TPdfToolsSignatureValidation_UnsupportedSignatureContent
    TPdfToolsSignatureValidation_UnsupportedSignatureContent;
/**
 * \class TPdfToolsSignatureValidation_CmsSignatureContent
 * @brief The data and validation result of the cryptographic signature
 */
typedef struct TPdfToolsSignatureValidation_CmsSignatureContent TPdfToolsSignatureValidation_CmsSignatureContent;
/**
 * \class TPdfToolsSignatureValidation_TimeStampContent
 * @brief The data and validation result of the cryptographic time-stamp
 */
typedef struct TPdfToolsSignatureValidation_TimeStampContent TPdfToolsSignatureValidation_TimeStampContent;
/**
 * \class TPdfToolsSignatureValidation_CustomTrustList
 * @brief The custom collection of trusted certificates
This class defines a custom collection of trusted certificates.
They define the certificates used for \ref ePdfToolsSignatureValidation_DataSource_CustomTrustList "" and can be set in
the validation profile with \ref PdfToolsSignatureValidationProfiles_Profile_SetCustomTrustList "".

 */
typedef struct TPdfToolsSignatureValidation_CustomTrustList TPdfToolsSignatureValidation_CustomTrustList;
/**
 * \class TPdfToolsSignatureValidationProfiles_Profile
 * @brief The base class for signature validation profiles
The profile defines the validation constraints.

 */
typedef struct TPdfToolsSignatureValidationProfiles_Profile TPdfToolsSignatureValidationProfiles_Profile;
/**
 * \class TPdfToolsSignatureValidationProfiles_ValidationOptions
 * @brief Signature validation options
 */
typedef struct TPdfToolsSignatureValidationProfiles_ValidationOptions
    TPdfToolsSignatureValidationProfiles_ValidationOptions;
/**
 * \class TPdfToolsSignatureValidationProfiles_TrustConstraints
 * @brief Certificate trust constraints
 */
typedef struct TPdfToolsSignatureValidationProfiles_TrustConstraints
    TPdfToolsSignatureValidationProfiles_TrustConstraints;
/**
 * \class TPdfToolsSignatureValidationProfiles_Default
 * @brief The default signature validation profile

This profile is suitable for general signature validation.
It is not very strict.

The default values are:
  - \ref PdfToolsSignatureValidationProfiles_Profile_GetValidationOptions "":
    - \ref PdfToolsSignatureValidationProfiles_ValidationOptions_GetTimeSource "": \ref
ePdfToolsSignatureValidation_TimeSource_ProofOfExistence "" + \ref
ePdfToolsSignatureValidation_TimeSource_ExpiredTimeStamp ""
    - \ref PdfToolsSignatureValidationProfiles_ValidationOptions_GetCertificateSources "": all
    - \ref PdfToolsSignatureValidationProfiles_ValidationOptions_GetRevocationInformationSources "": all
  - \ref PdfToolsSignatureValidationProfiles_Profile_GetSigningCertTrustConstraints "":
    - \ref PdfToolsSignatureValidationProfiles_TrustConstraints_GetTrustSources "": \ref
ePdfToolsSignatureValidation_DataSource_Aatl "" + \ref ePdfToolsSignatureValidation_DataSource_Eutl "" + \ref
ePdfToolsSignatureValidation_DataSource_CustomTrustList ""
    - \ref PdfToolsSignatureValidationProfiles_TrustConstraints_GetRevocationCheckPolicy "": \ref
ePdfToolsSignatureValidationProfiles_RevocationCheckPolicy_Optional ""
  - \ref PdfToolsSignatureValidationProfiles_Profile_GetTimeStampTrustConstraints "":
    - \ref PdfToolsSignatureValidationProfiles_TrustConstraints_GetTrustSources "": \ref
ePdfToolsSignatureValidation_DataSource_Aatl "" + \ref ePdfToolsSignatureValidation_DataSource_Eutl "" + \ref
ePdfToolsSignatureValidation_DataSource_CustomTrustList ""
    - \ref PdfToolsSignatureValidationProfiles_TrustConstraints_GetRevocationCheckPolicy "": \ref
ePdfToolsSignatureValidationProfiles_RevocationCheckPolicy_Optional ""

 */
typedef struct TPdfToolsSignatureValidationProfiles_Default TPdfToolsSignatureValidationProfiles_Default;

/**
 */
typedef struct TPdfToolsGeomInt_Size
{
    /**
     * @brief Width (horizontal size)
     */
    int iWidth;
    /**
     * @brief Height (vertical size)
     */
    int iHeight;
} TPdfToolsGeomInt_Size;

/**
 */
typedef struct TPdfToolsGeomUnits_Resolution
{
    /**
     * @brief Horizontal resolution in DPI
     */
    double dXDpi;
    /**
     * @brief Vertical resolution in DPI
     */
    double dYDpi;
} TPdfToolsGeomUnits_Resolution;

/**
 */
typedef struct TPdfToolsGeomUnits_Size
{
    /**
     * @brief Width (horizontal size) in point
     */
    double dWidth;
    /**
     * @brief Height (vertical size) in point
     */
    double dHeight;
} TPdfToolsGeomUnits_Size;

/**
 */
typedef struct TPdfToolsGeomUnits_Margin
{
    /**
     * @brief Left margin in point
     */
    double dLeft;
    /**
     * @brief Bottom margin in point
     */
    double dBottom;
    /**
     * @brief Right margin in point
     */
    double dRight;
    /**
     * @brief Top margin in point
     */
    double dTop;
} TPdfToolsGeomUnits_Margin;

/**
 */
typedef struct TPdfToolsGeomUnits_Point
{
    /**
     * @brief X-coordinate in point
     */
    double dX;
    /**
     * @brief Y-coordinate in point
     */
    double dY;
} TPdfToolsGeomUnits_Point;

/**
 */
typedef struct TPdfToolsGeomUnits_Rectangle
{
    /**
     * @brief X-coordinate of bottom-left point of the rectangle expressed in points
     */
    double dX;
    /**
     * @brief Y-coordinate of bottom-left point of the rectangle expressed in points
     */
    double dY;
    /**
     * @brief Width of rectangle in point
     */
    double dWidth;
    /**
     * @brief Height of rectangle in point
     */
    double dHeight;
} TPdfToolsGeomUnits_Rectangle;

typedef struct TPdfToolsSys_Date
{
    short iYear;
    short iMonth;
    short iDay;
    short iHour;
    short iMinute;
    short iSecond;
    short iTZSign;
    short iTZHour;
    short iTZMinute;
} TPdfToolsSys_Date;

struct TPdfToolsSys_StreamDescriptor;

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_TYPES_H__ */
