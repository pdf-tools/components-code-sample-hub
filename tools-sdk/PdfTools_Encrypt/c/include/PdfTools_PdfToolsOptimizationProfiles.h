/******************************************************************************
 *
 * File:            PdfTools_PdfToolsOptimizationProfiles.h
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

#ifndef PDFTOOLS_PDFTOOLSOPTIMIZATIONPROFILES_H__
#define PDFTOOLS_PDFTOOLSOPTIMIZATIONPROFILES_H__

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
 * Profile
 *****************************************************************************/
/**
 * @brief The image recompression options
* @param[in,out] pProfile Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Profile.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_ImageRecompressionOptions* PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Profile_GetImageRecompressionOptions(TPdfToolsOptimizationProfiles_Profile* pProfile);
/**
 * @brief The font optimization options
* @param[in,out] pProfile Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Profile.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_FontOptions* PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Profile_GetFontOptions(TPdfToolsOptimizationProfiles_Profile* pProfile);
/**
 * @brief The parameters defining the optional data to remove or flatten
* @param[in,out] pProfile Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Profile.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimization_RemovalOptions* PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Profile_GetRemovalOptions(TPdfToolsOptimizationProfiles_Profile* pProfile);
/**
 * @brief Whether to copy metadata
Copy document information dictionary and XMP metadata.
Default: \ref "TRUE".

* @param[in,out] pProfile Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Profile.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Profile_GetCopyMetadata(TPdfToolsOptimizationProfiles_Profile* pProfile);
/**
 * @brief Whether to copy metadata
Copy document information dictionary and XMP metadata.
Default: \ref "TRUE".

* @param[in,out] pProfile Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Profile.

* @param[in] bCopyMetadata Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimizationProfiles_Profile_SetCopyMetadata(
    TPdfToolsOptimizationProfiles_Profile* pProfile, BOOL bCopyMetadata);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsOptimizationProfiles_Profile.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pProfile Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsOptimizationProfiles_ProfileType that refers to the actual derived
 * type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsOptimizationProfiles_ProfileType PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Profile_GetType(TPdfToolsOptimizationProfiles_Profile* pProfile);
/******************************************************************************
 * Web
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimizationProfiles_Web* PDFTOOLS_CALL PdfToolsOptimizationProfiles_Web_New(void);

/**
 * @brief The target resolution of images in DPI

The target resolution in DPI (dots per inch) for color and grayscale images.

Images with a resolution above \ref PdfToolsOptimizationProfiles_Web_GetThresholdDPI "" are down-sampled.

Valid values are in the range 1.0 to 10000.

Set to `NULL` to deactivate down-sampling of images.

Default: `150`.

* @param[in,out] pWeb Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Web.

* @param[out] pResolutionDPI Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is outside of range 1.0 to 10000.0.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Web_GetResolutionDPI(TPdfToolsOptimizationProfiles_Web* pWeb, double* pResolutionDPI);
/**
 * @brief The target resolution of images in DPI

The target resolution in DPI (dots per inch) for color and grayscale images.

Images with a resolution above \ref PdfToolsOptimizationProfiles_Web_GetThresholdDPI "" are down-sampled.

Valid values are in the range 1.0 to 10000.

Set to `NULL` to deactivate down-sampling of images.

Default: `150`.

* @param[in,out] pWeb Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Web.

* @param[in] pResolutionDPI Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is outside of range 1.0 to 10000.0.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimizationProfiles_Web_SetResolutionDPI(
    TPdfToolsOptimizationProfiles_Web* pWeb, const double* pResolutionDPI);
/**
 * @brief The threshold resolution of images in DPI.

The threshold resolution in DPI (dots per inch) to selectively activate downsampling for color and grayscale images.

Valid values are in the range 1.0 to 10000.
To deactivate down-sampling of images set \ref PdfToolsOptimizationProfiles_Web_GetResolutionDPI "" to `NULL`.

Default: `1.4` times \ref PdfToolsOptimizationProfiles_Web_GetResolutionDPI "".

* @param[in,out] pWeb Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Web.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is outside of range 1.0 to 10000.0.


 */
PDFTOOLS_EXPORT double PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Web_GetThresholdDPI(TPdfToolsOptimizationProfiles_Web* pWeb);
/**
 * @brief The threshold resolution of images in DPI.

The threshold resolution in DPI (dots per inch) to selectively activate downsampling for color and grayscale images.

Valid values are in the range 1.0 to 10000.
To deactivate down-sampling of images set \ref PdfToolsOptimizationProfiles_Web_GetResolutionDPI "" to `NULL`.

Default: `1.4` times \ref PdfToolsOptimizationProfiles_Web_GetResolutionDPI "".

* @param[in,out] pWeb Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Web.

* @param[in] dThresholdDPI Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is outside of range 1.0 to 10000.0.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Web_SetThresholdDPI(TPdfToolsOptimizationProfiles_Web* pWeb, double dThresholdDPI);

/******************************************************************************
 * Print
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimizationProfiles_Print* PDFTOOLS_CALL PdfToolsOptimizationProfiles_Print_New(void);

/******************************************************************************
 * Archive
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimizationProfiles_Archive* PDFTOOLS_CALL PdfToolsOptimizationProfiles_Archive_New(void);

/******************************************************************************
 * MinimalFileSize
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimizationProfiles_MinimalFileSize* PDFTOOLS_CALL
PdfToolsOptimizationProfiles_MinimalFileSize_New(void);

/**
 * @brief The target resolution of images in DPI

The target resolution in DPI (dots per inch) for color and grayscale images.

Images with a resolution above \ref PdfToolsOptimizationProfiles_MinimalFileSize_GetThresholdDPI "" are down-sampled.

Valid values are in the range 1.0 to 10000.

If `NULL`, then resolution setting is disabled.

Default: `130`.

* @param[in,out] pMinimalFileSize Acts as a handle to the native object of type \ref
TPdfToolsOptimizationProfiles_MinimalFileSize.

* @param[out] pResolutionDPI Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is outside of range 1.0 to 10000.0.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimizationProfiles_MinimalFileSize_GetResolutionDPI(
    TPdfToolsOptimizationProfiles_MinimalFileSize* pMinimalFileSize, double* pResolutionDPI);
/**
 * @brief The target resolution of images in DPI

The target resolution in DPI (dots per inch) for color and grayscale images.

Images with a resolution above \ref PdfToolsOptimizationProfiles_MinimalFileSize_GetThresholdDPI "" are down-sampled.

Valid values are in the range 1.0 to 10000.

If `NULL`, then resolution setting is disabled.

Default: `130`.

* @param[in,out] pMinimalFileSize Acts as a handle to the native object of type \ref
TPdfToolsOptimizationProfiles_MinimalFileSize.

* @param[in] pResolutionDPI Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is outside of range 1.0 to 10000.0.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimizationProfiles_MinimalFileSize_SetResolutionDPI(
    TPdfToolsOptimizationProfiles_MinimalFileSize* pMinimalFileSize, const double* pResolutionDPI);
/**
 * @brief The threshold resolution of images in DPI.

The threshold resolution in DPI (dots per inch) to selectively activate downsampling for color and grayscale images.

Valid values are in the range 1.0 to 10000.
To deactivate down-sampling of images set \ref PdfToolsOptimizationProfiles_MinimalFileSize_GetResolutionDPI "" to
`NULL`.

Default: `1.4` times \ref PdfToolsOptimizationProfiles_MinimalFileSize_GetResolutionDPI "".

* @param[in,out] pMinimalFileSize Acts as a handle to the native object of type \ref
TPdfToolsOptimizationProfiles_MinimalFileSize.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is outside of range 1.0 to 10000.0.


 */
PDFTOOLS_EXPORT double PDFTOOLS_CALL PdfToolsOptimizationProfiles_MinimalFileSize_GetThresholdDPI(
    TPdfToolsOptimizationProfiles_MinimalFileSize* pMinimalFileSize);
/**
 * @brief The threshold resolution of images in DPI.

The threshold resolution in DPI (dots per inch) to selectively activate downsampling for color and grayscale images.

Valid values are in the range 1.0 to 10000.
To deactivate down-sampling of images set \ref PdfToolsOptimizationProfiles_MinimalFileSize_GetResolutionDPI "" to
`NULL`.

Default: `1.4` times \ref PdfToolsOptimizationProfiles_MinimalFileSize_GetResolutionDPI "".

* @param[in,out] pMinimalFileSize Acts as a handle to the native object of type \ref
TPdfToolsOptimizationProfiles_MinimalFileSize.

* @param[in] dThresholdDPI Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is outside of range 1.0 to 10000.0.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimizationProfiles_MinimalFileSize_SetThresholdDPI(
    TPdfToolsOptimizationProfiles_MinimalFileSize* pMinimalFileSize, double dThresholdDPI);

/******************************************************************************
 * Mrc
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsOptimizationProfiles_Mrc* PDFTOOLS_CALL PdfToolsOptimizationProfiles_Mrc_New(void);

/**
 * @brief The image quality for MRC foreground and background layers

This is a value between `0` (lowest quality) and `1` (highest quality).

Default:
  - \ref ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality "" algorithm: `1`.
  - \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced "" algorithm: `0.25`.
  - \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Speed "" algorithm: `0.25`.

* @param[in,out] pMrc Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Mrc.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is smaller than `0` or greater than `1`.


 */
PDFTOOLS_EXPORT double PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Mrc_GetLayerCompressionQuality(TPdfToolsOptimizationProfiles_Mrc* pMrc);
/**
 * @brief The image quality for MRC foreground and background layers

This is a value between `0` (lowest quality) and `1` (highest quality).

Default:
  - \ref ePdfToolsOptimization_CompressionAlgorithmSelection_PreserveQuality "" algorithm: `1`.
  - \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Balanced "" algorithm: `0.25`.
  - \ref ePdfToolsOptimization_CompressionAlgorithmSelection_Speed "" algorithm: `0.25`.

* @param[in,out] pMrc Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Mrc.

* @param[in] dLayerCompressionQuality Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is smaller than `0` or greater than `1`.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimizationProfiles_Mrc_SetLayerCompressionQuality(
    TPdfToolsOptimizationProfiles_Mrc* pMrc, double dLayerCompressionQuality);
/**
 * @brief The target resolution in DPI (dots per inch) for downsampling MRC foreground and background layers

Valid values are 1, or 10000, or in between.
Set to `NULL` to deactivate downsampling of images.

Default: `70`.

* @param[in,out] pMrc Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Mrc.

* @param[out] pLayerResolutionDPI Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is smaller than 1 or greater than 10000.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimizationProfiles_Mrc_GetLayerResolutionDPI(
    TPdfToolsOptimizationProfiles_Mrc* pMrc, double* pLayerResolutionDPI);
/**
 * @brief The target resolution in DPI (dots per inch) for downsampling MRC foreground and background layers

Valid values are 1, or 10000, or in between.
Set to `NULL` to deactivate downsampling of images.

Default: `70`.

* @param[in,out] pMrc Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Mrc.

* @param[in] pLayerResolutionDPI Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is smaller than 1 or greater than 10000.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsOptimizationProfiles_Mrc_SetLayerResolutionDPI(
    TPdfToolsOptimizationProfiles_Mrc* pMrc, const double* pLayerResolutionDPI);
/**
 * @brief The option to recognize photographic regions when doing MRC.

Regardless of this property’s setting, monochrome (grayscale) images are always treated as entire photographic regions
(cut­out pictures) by the MRC algorithm.

Default: \ref "FALSE".

* @param[in,out] pMrc Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Mrc.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Mrc_GetRecognizePictures(TPdfToolsOptimizationProfiles_Mrc* pMrc);
/**
 * @brief The option to recognize photographic regions when doing MRC.

Regardless of this property’s setting, monochrome (grayscale) images are always treated as entire photographic regions
(cut­out pictures) by the MRC algorithm.

Default: \ref "FALSE".

* @param[in,out] pMrc Acts as a handle to the native object of type \ref TPdfToolsOptimizationProfiles_Mrc.

* @param[in] bRecognizePictures Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsOptimizationProfiles_Mrc_SetRecognizePictures(TPdfToolsOptimizationProfiles_Mrc* pMrc, BOOL bRecognizePictures);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSOPTIMIZATIONPROFILES_H__ */
