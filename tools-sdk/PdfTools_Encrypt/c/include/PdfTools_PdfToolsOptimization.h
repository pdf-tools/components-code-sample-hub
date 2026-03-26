/******************************************************************************
 *
 * File:            PdfTools_PdfToolsOptimization.h
 *
 * Description:     Sub Header file for Pdftools SDK
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

#ifndef PDFTOOLS_PDFTOOLSOPTIMIZATION_H__
#define PDFTOOLS_PDFTOOLSOPTIMIZATION_H__

#ifndef PDFTOOLS_CALL
#if defined(WIN32)
#define PDFTOOLS_CALL __stdcall
#else
#define PDFTOOLS_CALL
#endif
#endif

#include "PdfTools_Types.h"
#include "PdfTools_PdfToolsSys.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _UNICODE
#else
#endif

/******************************************************************************
 * ImageRecompressionOptions
 *****************************************************************************/
/**
 * @brief The strategy for image recompression

For each image to be recompressed, a specific choice of compression
algorithms are tried. The selection of algorithms depends on this strategy, the
type of the optimizer profile (e.g. \ref TPdfToolsOptimizationProfiles_Web ""),
the color space of the image, and \ref PdfToolsOptimization_ImageRecompressionOptions_GetCompressionQuality "".
The image is recompressed using the algorithm resulting in the
smallest output file.

Refer to \ref TPdfToolsOptimization_CompressionAlgorithmSelection "" for
more information on strategies.

Default:
  - \ref TPdfToolsOptimizationProfiles_Web "" profile: \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced
""
  - \ref TPdfToolsOptimizationProfiles_Print "" profile: \ref
ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality ""
  - \ref TPdfToolsOptimizationProfiles_Archive "" profile: \ref
ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality ""
  - \ref TPdfToolsOptimizationProfiles_MinimalFileSize "" profile: \ref
ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced ""
  - \ref TPdfToolsOptimizationProfiles_Mrc "" profile: \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced
""

* @param[in,out] pImageRecompressionOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_ImageRecompressionOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_CompressionAlgorithmSelection PDFTOOLS_CALL
PdfToolsOptimization_ImageRecompressionOptions_GetAlgorithmSelection(
    TPdfToolsOptimization_ImageRecompressionOptions* pImageRecompressionOptions);
/**
 * @brief The strategy for image recompression

For each image to be recompressed, a specific choice of compression
algorithms are tried. The selection of algorithms depends on this strategy, the
type of the optimizer profile (e.g. \ref TPdfToolsOptimizationProfiles_Web ""),
the color space of the image, and \ref PdfToolsOptimization_ImageRecompressionOptions_GetCompressionQuality "".
The image is recompressed using the algorithm resulting in the
smallest output file.

Refer to \ref TPdfToolsOptimization_CompressionAlgorithmSelection "" for
more information on strategies.

Default:
  - \ref TPdfToolsOptimizationProfiles_Web "" profile: \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced
""
  - \ref TPdfToolsOptimizationProfiles_Print "" profile: \ref
ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality ""
  - \ref TPdfToolsOptimizationProfiles_Archive "" profile: \ref
ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality ""
  - \ref TPdfToolsOptimizationProfiles_MinimalFileSize "" profile: \ref
ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced ""
  - \ref TPdfToolsOptimizationProfiles_Mrc "" profile: \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced
""

* @param[in,out] pImageRecompressionOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_ImageRecompressionOptions.

* @param[in] iAlgorithmSelection Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_ImageRecompressionOptions_SetAlgorithmSelection(
    TPdfToolsOptimization_ImageRecompressionOptions*    pImageRecompressionOptions,
    TPdfToolsOptimization_CompressionAlgorithmSelection iAlgorithmSelection);
/**
 * @brief The compression quality for lossy image compression algorithms

This property specifies the compression quality for the JPEG and JPEG2000 image compression algorithms.
Valid values are between 0 (lowest quality) and 1 (highest quality).

Although the JBIG2 algorithm for bi-tonal images also allows lossy compression, it is not influenced by this property.
The JBIG2 compression quality is fixed at 1 (lossless).

Default:
  - \ref TPdfToolsOptimizationProfiles_Web "" profile: 0.8
  - \ref TPdfToolsOptimizationProfiles_Print "" profile: 0.9
  - \ref TPdfToolsOptimizationProfiles_Archive "" profile: 0.9
  - \ref TPdfToolsOptimizationProfiles_MinimalFileSize "" profile: 0.75
  - \ref TPdfToolsOptimizationProfiles_Mrc "" profile: 0.75

* @param[in,out] pImageRecompressionOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_ImageRecompressionOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `-1.0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is outside of the range 0 - 1


 */
PDFTOOLS_EXPORT double PDFTOOLS_CALL PdfToolsOptimization_ImageRecompressionOptions_GetCompressionQuality(
    TPdfToolsOptimization_ImageRecompressionOptions* pImageRecompressionOptions);
/**
 * @brief The compression quality for lossy image compression algorithms

This property specifies the compression quality for the JPEG and JPEG2000 image compression algorithms.
Valid values are between 0 (lowest quality) and 1 (highest quality).

Although the JBIG2 algorithm for bi-tonal images also allows lossy compression, it is not influenced by this property.
The JBIG2 compression quality is fixed at 1 (lossless).

Default:
  - \ref TPdfToolsOptimizationProfiles_Web "" profile: 0.8
  - \ref TPdfToolsOptimizationProfiles_Print "" profile: 0.9
  - \ref TPdfToolsOptimizationProfiles_Archive "" profile: 0.9
  - \ref TPdfToolsOptimizationProfiles_MinimalFileSize "" profile: 0.75
  - \ref TPdfToolsOptimizationProfiles_Mrc "" profile: 0.75

* @param[in,out] pImageRecompressionOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_ImageRecompressionOptions.

* @param[in] dCompressionQuality Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is outside of the range 0 - 1


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_ImageRecompressionOptions_SetCompressionQuality(
    TPdfToolsOptimization_ImageRecompressionOptions* pImageRecompressionOptions, double dCompressionQuality);
/**
 * @brief Enable color complexity reduction.
When enabled, the software analyzes images that utilize device color spaces (DeviceRGB, DeviceCMYK, or DeviceGray) as
well as indexed images with a device color space as their base. If applicable, the images are converted according to the
following criteria:
  - Images in DeviceRGB or DeviceCMYK color space where all pixels are gray will be converted to grayscale using the
DeviceGray color space.
  - Images containing only black and white pixels will be converted to bitonal images.
  - Images where all pixels are of the same color will be downsampled to a single pixel.
Additionally, image masks and soft masks are optimized in the following ways:
  - Soft masks consisting only of black and white pixels will be converted into a standard mask.
  - Any (soft) mask that is completely opaque will be removed.
Default:
  - \ref TPdfToolsOptimizationProfiles_Web "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Print "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Archive "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_MinimalFileSize "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Mrc "" profile: \ref "FALSE"

* @param[in,out] pImageRecompressionOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_ImageRecompressionOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_ImageRecompressionOptions_GetReduceColorComplexity(
    TPdfToolsOptimization_ImageRecompressionOptions* pImageRecompressionOptions);
/**
 * @brief Enable color complexity reduction.
When enabled, the software analyzes images that utilize device color spaces (DeviceRGB, DeviceCMYK, or DeviceGray) as
well as indexed images with a device color space as their base. If applicable, the images are converted according to the
following criteria:
  - Images in DeviceRGB or DeviceCMYK color space where all pixels are gray will be converted to grayscale using the
DeviceGray color space.
  - Images containing only black and white pixels will be converted to bitonal images.
  - Images where all pixels are of the same color will be downsampled to a single pixel.
Additionally, image masks and soft masks are optimized in the following ways:
  - Soft masks consisting only of black and white pixels will be converted into a standard mask.
  - Any (soft) mask that is completely opaque will be removed.
Default:
  - \ref TPdfToolsOptimizationProfiles_Web "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Print "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Archive "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_MinimalFileSize "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Mrc "" profile: \ref "FALSE"

* @param[in,out] pImageRecompressionOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_ImageRecompressionOptions.

* @param[in] bReduceColorComplexity Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_ImageRecompressionOptions_SetReduceColorComplexity(
    TPdfToolsOptimization_ImageRecompressionOptions* pImageRecompressionOptions, BOOL bReduceColorComplexity);

/******************************************************************************
 * FontOptions
 *****************************************************************************/
/**
 * @brief Whether to merge fonts and font programs

A PDF document can have the same font, or a subset of it,
embedded multiple times.
This commonly occurs, when multiple PDFs are merged into
one large PDF.
Such fonts can be merged into one font.

Merging fonts and font programs can greatly reduce the file size.
However, it is computationally complex and can increase file processing time
and memory usage substantially.

Default: \ref "TRUE".

* @param[in,out] pFontOptions Acts as a handle to the native object of type \ref TPdfToolsOptimization_FontOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_FontOptions_GetMerge(TPdfToolsOptimization_FontOptions* pFontOptions);
/**
 * @brief Whether to merge fonts and font programs

A PDF document can have the same font, or a subset of it,
embedded multiple times.
This commonly occurs, when multiple PDFs are merged into
one large PDF.
Such fonts can be merged into one font.

Merging fonts and font programs can greatly reduce the file size.
However, it is computationally complex and can increase file processing time
and memory usage substantially.

Default: \ref "TRUE".

* @param[in,out] pFontOptions Acts as a handle to the native object of type \ref TPdfToolsOptimization_FontOptions.

* @param[in] bMerge Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_FontOptions_SetMerge(TPdfToolsOptimization_FontOptions* pFontOptions, BOOL bMerge);
/**
 * @brief Whether to remove standard fonts

Enable or disable un-embedding of the font programs of all embedded
standard fonts, such as Arial, Courier, CourierNew, Helvetica, Symbol,
Times, TimesNewRoman and ZapfDingbats.
This decreases the file size.

The fonts are replaced with one of the 14 PDF Standard Fonts, all of
which have no associated font program.
A PDF viewer must be able to display these 14 PDF Standard Fonts correctly.
Therefore, enabling this property usually does not visually alter the PDF
when it is displayed.

Un-embedding the font works based on the font's Unicode information,
i.e. the un-embedded font's characters are mapped to those of the
original font with the same Unicode.
Therefore, only fonts with Unicode information are un-embedded.

If a font's Unicode information is incorrect, un-embedding may lead
to visual differences.
The correctness of a Unicode information can be verified by extracting
text that uses the font.

If the extracted text is meaningful, the font's Unicode information is
correct, and un-embedding of the font does not cause visual differences.

Default: \ref "FALSE" (disabled) except in the profile \ref TPdfToolsOptimizationProfiles_MinimalFileSize "".

* @param[in,out] pFontOptions Acts as a handle to the native object of type \ref TPdfToolsOptimization_FontOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_FontOptions_GetRemoveStandardFonts(TPdfToolsOptimization_FontOptions* pFontOptions);
/**
 * @brief Whether to remove standard fonts

Enable or disable un-embedding of the font programs of all embedded
standard fonts, such as Arial, Courier, CourierNew, Helvetica, Symbol,
Times, TimesNewRoman and ZapfDingbats.
This decreases the file size.

The fonts are replaced with one of the 14 PDF Standard Fonts, all of
which have no associated font program.
A PDF viewer must be able to display these 14 PDF Standard Fonts correctly.
Therefore, enabling this property usually does not visually alter the PDF
when it is displayed.

Un-embedding the font works based on the font's Unicode information,
i.e. the un-embedded font's characters are mapped to those of the
original font with the same Unicode.
Therefore, only fonts with Unicode information are un-embedded.

If a font's Unicode information is incorrect, un-embedding may lead
to visual differences.
The correctness of a Unicode information can be verified by extracting
text that uses the font.

If the extracted text is meaningful, the font's Unicode information is
correct, and un-embedding of the font does not cause visual differences.

Default: \ref "FALSE" (disabled) except in the profile \ref TPdfToolsOptimizationProfiles_MinimalFileSize "".

* @param[in,out] pFontOptions Acts as a handle to the native object of type \ref TPdfToolsOptimization_FontOptions.

* @param[in] bRemoveStandardFonts Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_FontOptions_SetRemoveStandardFonts(
    TPdfToolsOptimization_FontOptions* pFontOptions, BOOL bRemoveStandardFonts);

/******************************************************************************
 * RemovalOptions
 *****************************************************************************/
/**
 * @brief Whether to remove additional or alternative versions of images
Default: \ref "FALSE" except in the profile \ref TPdfToolsOptimizationProfiles_Print "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetRemoveAlternateImages(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief Whether to remove additional or alternative versions of images
Default: \ref "FALSE" except in the profile \ref TPdfToolsOptimizationProfiles_Print "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] bRemoveAlternateImages Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetRemoveAlternateImages(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, BOOL bRemoveAlternateImages);
/**
 * @brief Whether to remove the sequential flows (threads) of articles
Default: \ref "TRUE" except in the profile \ref TPdfToolsOptimizationProfiles_Archive "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetRemoveArticleThreads(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief Whether to remove the sequential flows (threads) of articles
Default: \ref "TRUE" except in the profile \ref TPdfToolsOptimizationProfiles_Archive "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] bRemoveArticleThreads Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetRemoveArticleThreads(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, BOOL bRemoveArticleThreads);
/**
 * @brief Whether to remove document's XMP metadata
Default:
  - \ref TPdfToolsOptimizationProfiles_Web "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Print "" profile: \ref "FALSE"
  - \ref TPdfToolsOptimizationProfiles_Archive "" profile: \ref "FALSE"
  - \ref TPdfToolsOptimizationProfiles_MinimalFileSize "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Mrc "" profile: \ref "FALSE"

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetRemoveMetadata(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief Whether to remove document's XMP metadata
Default:
  - \ref TPdfToolsOptimizationProfiles_Web "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Print "" profile: \ref "FALSE"
  - \ref TPdfToolsOptimizationProfiles_Archive "" profile: \ref "FALSE"
  - \ref TPdfToolsOptimizationProfiles_MinimalFileSize "" profile: \ref "TRUE"
  - \ref TPdfToolsOptimizationProfiles_Mrc "" profile: \ref "FALSE"

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] bRemoveMetadata Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetRemoveMetadata(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, BOOL bRemoveMetadata);
/**
 * @brief Whether to remove all output intents

Output intents provide a means for matching the color characteristics
of PDF page content with those of a target output device or
production environment in which the document will be printed.

Default: \ref "FALSE" except in the profile \ref TPdfToolsOptimizationProfiles_MinimalFileSize "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetRemoveOutputIntents(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief Whether to remove all output intents

Output intents provide a means for matching the color characteristics
of PDF page content with those of a target output device or
production environment in which the document will be printed.

Default: \ref "FALSE" except in the profile \ref TPdfToolsOptimizationProfiles_MinimalFileSize "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] bRemoveOutputIntents Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetRemoveOutputIntents(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, BOOL bRemoveOutputIntents);
/**
 * @brief Whether to remove the piece-info dictionary (private PDF processor data)

The removal of this proprietary application data has no effect on the document's
visual appearance.

Default: \ref "TRUE" except in the profile \ref TPdfToolsOptimizationProfiles_Archive "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetRemovePieceInfo(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief Whether to remove the piece-info dictionary (private PDF processor data)

The removal of this proprietary application data has no effect on the document's
visual appearance.

Default: \ref "TRUE" except in the profile \ref TPdfToolsOptimizationProfiles_Archive "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] bRemovePieceInfo Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetRemovePieceInfo(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, BOOL bRemovePieceInfo);
/**
 * @brief Whether to remove the data describing the logical structure of a PDF

The logical structure of the document is a description of the content of its pages.
It consists of a fine granular hierarchical tagging that distinguishes between the actual content and artifacts (such as
page numbers, layout artifacts, etc.). The tagging provides a meaningful description, for example "This is a header",
"This color image shows a small sailing boat at sunset", etc. This information can be used e.g. to read the document to
the visually impaired.

Default: \ref "TRUE" except in the profile \ref TPdfToolsOptimizationProfiles_Archive "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetRemoveStructureTree(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief Whether to remove the data describing the logical structure of a PDF

The logical structure of the document is a description of the content of its pages.
It consists of a fine granular hierarchical tagging that distinguishes between the actual content and artifacts (such as
page numbers, layout artifacts, etc.). The tagging provides a meaningful description, for example "This is a header",
"This color image shows a small sailing boat at sunset", etc. This information can be used e.g. to read the document to
the visually impaired.

Default: \ref "TRUE" except in the profile \ref TPdfToolsOptimizationProfiles_Archive "".

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] bRemoveStructureTree Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetRemoveStructureTree(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, BOOL bRemoveStructureTree);
/**
 * @brief Whether to remove thumbnail images which represent the PDF pages in miniature form
Default: \ref "TRUE" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetRemoveThumbnails(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief Whether to remove thumbnail images which represent the PDF pages in miniature form
Default: \ref "TRUE" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] bRemoveThumbnails Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetRemoveThumbnails(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, BOOL bRemoveThumbnails);
/**
 * @brief Whether to remove or flatten signature appearances

A signature in a PDF consist of two parts:

  - <b>(a)</b> The invisible digital signature in the PDF.
  - <b>(b)</b> The visual appearance that was attributed to the signature.

Part (a) can be used by a viewing application, to verify that the PDF
has not changed since it has been signed and report this to the user.

During optimizing, the PDF is altered and hence its digital signature
(a) is broken and must be removed.

  - \ref ePdfToolsOptimization_RemovalStrategy_Flatten "": (a) is removed and (b) is drawn as non-editable graphic onto
the page. Within the context of signatures this is called "flattening".
  - \ref ePdfToolsOptimization_RemovalStrategy_Remove "": (a) and (b) are removed.

Default: \ref ePdfToolsOptimization_RemovalStrategy_Flatten "" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_RemovalStrategy PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetRemoveSignatureAppearances(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief Whether to remove or flatten signature appearances

A signature in a PDF consist of two parts:

  - <b>(a)</b> The invisible digital signature in the PDF.
  - <b>(b)</b> The visual appearance that was attributed to the signature.

Part (a) can be used by a viewing application, to verify that the PDF
has not changed since it has been signed and report this to the user.

During optimizing, the PDF is altered and hence its digital signature
(a) is broken and must be removed.

  - \ref ePdfToolsOptimization_RemovalStrategy_Flatten "": (a) is removed and (b) is drawn as non-editable graphic onto
the page. Within the context of signatures this is called "flattening".
  - \ref ePdfToolsOptimization_RemovalStrategy_Remove "": (a) and (b) are removed.

Default: \ref ePdfToolsOptimization_RemovalStrategy_Flatten "" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] iRemoveSignatureAppearances Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetRemoveSignatureAppearances(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions,
    TPdfToolsOptimization_RemovalStrategy iRemoveSignatureAppearances);
/**
 * @brief The conversion strategy for annotations

The conversion strategy for annotations.

Annotations in PDF are interactive elements on the pages, such as:
  - Sticky notes
  - Free text annotations
  - Line, square, circle, and polygon annotations
  - Highlight, underline and strikeout annotations
  - Stamp annotations
  - Ink annotations
  - File attachment annotation
  - Sound and movie annotations
  - 3D annotations

Note that this does not include form fields (see \ref PdfToolsOptimization_RemovalOptions_GetFormFields "") and links
(see \ref PdfToolsOptimization_RemovalOptions_GetLinks "").

Default: \ref ePdfToolsOptimization_ConversionStrategy_Copy "" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_ConversionStrategy PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetAnnotations(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief The conversion strategy for annotations

The conversion strategy for annotations.

Annotations in PDF are interactive elements on the pages, such as:
  - Sticky notes
  - Free text annotations
  - Line, square, circle, and polygon annotations
  - Highlight, underline and strikeout annotations
  - Stamp annotations
  - Ink annotations
  - File attachment annotation
  - Sound and movie annotations
  - 3D annotations

Note that this does not include form fields (see \ref PdfToolsOptimization_RemovalOptions_GetFormFields "") and links
(see \ref PdfToolsOptimization_RemovalOptions_GetLinks "").

Default: \ref ePdfToolsOptimization_ConversionStrategy_Copy "" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] iAnnotations Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetAnnotations(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, TPdfToolsOptimization_ConversionStrategy iAnnotations);
/**
 * @brief The conversion strategy for interactive forms
Default: \ref ePdfToolsOptimization_ConversionStrategy_Copy "" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_ConversionStrategy PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetFormFields(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief The conversion strategy for interactive forms
Default: \ref ePdfToolsOptimization_ConversionStrategy_Copy "" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] iFormFields Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetFormFields(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, TPdfToolsOptimization_ConversionStrategy iFormFields);
/**
 * @brief The conversion strategy for links
Default: \ref ePdfToolsOptimization_ConversionStrategy_Copy "" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_ConversionStrategy PDFTOOLS_CALL
PdfToolsOptimization_RemovalOptions_GetLinks(TPdfToolsOptimization_RemovalOptions* pRemovalOptions);
/**
 * @brief The conversion strategy for links
Default: \ref ePdfToolsOptimization_ConversionStrategy_Copy "" in all profiles.

* @param[in,out] pRemovalOptions Acts as a handle to the native object of type \ref
TPdfToolsOptimization_RemovalOptions.

* @param[in] iLinks Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimization_RemovalOptions_SetLinks(
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions, TPdfToolsOptimization_ConversionStrategy iLinks);

/******************************************************************************
 * Optimizer
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_Optimizer* PDFTOOLS_CALL PdfToolsOptimization_Optimizer_New(void);

/**
 * @brief Optimize the PDF document
* @param[in,out] pOptimizer Acts as a handle to the native object of type \ref TPdfToolsOptimization_Optimizer.

* @param[in,out] pInDoc The input PDF document

* @param[in,out] pOutStreamDesc The stream to which the output PDF is written

* @param[in,out] pProfile The profile defining the optimization parameters.

* @param[in,out] pOutOptions The PDF output options, e.g. to encrypt the output document.


 * @return
  The optimized result PDF, which can be used
  as a new input for further processing.

  Note that, this object must be disposed before the output stream
  object (method argument <b>pOutStreamDesc</b>).

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IllegalArgument An invalid encryption was specified in <b>pOutOptions</b>.

 * - \ref ePdfTools_Error_Processing The processing has failed.

 * - \ref ePdfTools_Error_IO Writing to the output PDF has failed.

 * - \ref ePdfTools_Error_Generic A generic error occurred.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsOptimization_Optimizer_OptimizeDocument(
    TPdfToolsOptimization_Optimizer* pOptimizer, TPdfToolsPdf_Document* pInDoc,
    const TPdfToolsSys_StreamDescriptor* pOutStreamDesc, TPdfToolsOptimizationProfiles_Profile* pProfile,
    TPdfToolsPdf_OutputOptions* pOutOptions);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSOPTIMIZATION_H__ */
