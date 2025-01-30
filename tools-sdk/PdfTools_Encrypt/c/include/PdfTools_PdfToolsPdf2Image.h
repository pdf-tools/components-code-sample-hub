/******************************************************************************
 *
 * File:            PdfTools_PdfToolsPdf2Image.h
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

#ifndef PDFTOOLS_PDFTOOLSPDF2IMAGE_H__
#define PDFTOOLS_PDFTOOLSPDF2IMAGE_H__

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
 * ContentOptions
 *****************************************************************************/
/**
 * @brief The render strategy for annotations

Defines whether to render annotation popups.
For details, see \ref TPdfToolsPdf2Image_AnnotationOptions "".

Default: \ref ePdfToolsPdf2Image_AnnotationOptions_ShowAnnotations ""

* @param[in,out] pContentOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_ContentOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_AnnotationOptions PDFTOOLS_CALL
PdfToolsPdf2Image_ContentOptions_GetAnnotations(TPdfToolsPdf2Image_ContentOptions* pContentOptions);
/**
 * @brief The render strategy for annotations

Defines whether to render annotation popups.
For details, see \ref TPdfToolsPdf2Image_AnnotationOptions "".

Default: \ref ePdfToolsPdf2Image_AnnotationOptions_ShowAnnotations ""

* @param[in,out] pContentOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_ContentOptions.

* @param[in] iAnnotations Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_ContentOptions_SetAnnotations(
    TPdfToolsPdf2Image_ContentOptions* pContentOptions, TPdfToolsPdf2Image_AnnotationOptions iAnnotations);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsPdf2Image_ImageOptions.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pImageOptions Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsPdf2Image_ImageOptionsType that refers to the actual derived type.
 * `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_ImageOptionsType PDFTOOLS_CALL
PdfToolsPdf2Image_ImageOptions_GetType(TPdfToolsPdf2Image_ImageOptions* pImageOptions);
/******************************************************************************
 * FaxImageOptions
 *****************************************************************************/
/**
 * @brief The vertical image resolution

This property allows a choice of which vertical
resolution to use.
For details, see \ref TPdfToolsPdf2Image_FaxVerticalResolution "".

Note that the horizontal resolution is fixed at 204 DPI by the
Fax standard.

Default: \ref ePdfToolsPdf2Image_FaxVerticalResolution_Standard ""

* @param[in,out] pFaxImageOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_FaxImageOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_FaxVerticalResolution PDFTOOLS_CALL
PdfToolsPdf2Image_FaxImageOptions_GetVerticalResolution(TPdfToolsPdf2Image_FaxImageOptions* pFaxImageOptions);
/**
 * @brief The vertical image resolution

This property allows a choice of which vertical
resolution to use.
For details, see \ref TPdfToolsPdf2Image_FaxVerticalResolution "".

Note that the horizontal resolution is fixed at 204 DPI by the
Fax standard.

Default: \ref ePdfToolsPdf2Image_FaxVerticalResolution_Standard ""

* @param[in,out] pFaxImageOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_FaxImageOptions.

* @param[in] iVerticalResolution Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_FaxImageOptions_SetVerticalResolution(
    TPdfToolsPdf2Image_FaxImageOptions* pFaxImageOptions, TPdfToolsPdf2Image_FaxVerticalResolution iVerticalResolution);
/**
 * @brief The Fax compression algorithm

This property allows a choice of which compression
type to use.
For details, see \ref TPdfToolsPdf2Image_TiffBitonalCompressionType "".

Default: \ref ePdfToolsPdf2Image_TiffBitonalCompressionType_G3 ""

* @param[in,out] pFaxImageOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_FaxImageOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_TiffBitonalCompressionType PDFTOOLS_CALL
PdfToolsPdf2Image_FaxImageOptions_GetCompression(TPdfToolsPdf2Image_FaxImageOptions* pFaxImageOptions);
/**
 * @brief The Fax compression algorithm

This property allows a choice of which compression
type to use.
For details, see \ref TPdfToolsPdf2Image_TiffBitonalCompressionType "".

Default: \ref ePdfToolsPdf2Image_TiffBitonalCompressionType_G3 ""

* @param[in,out] pFaxImageOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_FaxImageOptions.

* @param[in] iCompression Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_FaxImageOptions_SetCompression(
    TPdfToolsPdf2Image_FaxImageOptions* pFaxImageOptions, TPdfToolsPdf2Image_TiffBitonalCompressionType iCompression);

/******************************************************************************
 * TiffJpegImageOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_TiffJpegImageOptions* PDFTOOLS_CALL PdfToolsPdf2Image_TiffJpegImageOptions_New(void);

/**
 * @brief The JPEG quality factor

Get or set the JPEG compression quality.
Valid values are `1`, or `100`, or in between.

Default: `85`

* @param[in,out] pTiffJpegImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffJpegImageOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is smaller than 1 or greater than 100.


 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsPdf2Image_TiffJpegImageOptions_GetJpegQuality(TPdfToolsPdf2Image_TiffJpegImageOptions* pTiffJpegImageOptions);
/**
 * @brief The JPEG quality factor

Get or set the JPEG compression quality.
Valid values are `1`, or `100`, or in between.

Default: `85`

* @param[in,out] pTiffJpegImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffJpegImageOptions.

* @param[in] iJpegQuality Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is smaller than 1 or greater than 100.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_TiffJpegImageOptions_SetJpegQuality(
    TPdfToolsPdf2Image_TiffJpegImageOptions* pTiffJpegImageOptions, int iJpegQuality);
/**
 * @brief The color space of the output image

Get or set the color space. If null, the blending color space of the page is used.

Default: \ref ePdfToolsPdf2Image_JpegColorSpace_Rgb ""

* @param[in,out] pTiffJpegImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffJpegImageOptions.

* @param[out] pColorSpace Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_TiffJpegImageOptions_GetColorSpace(
    TPdfToolsPdf2Image_TiffJpegImageOptions* pTiffJpegImageOptions, TPdfToolsPdf2Image_JpegColorSpace* pColorSpace);
/**
 * @brief The color space of the output image

Get or set the color space. If null, the blending color space of the page is used.

Default: \ref ePdfToolsPdf2Image_JpegColorSpace_Rgb ""

* @param[in,out] pTiffJpegImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffJpegImageOptions.

* @param[in] pColorSpace Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf2Image_TiffJpegImageOptions_SetColorSpace(TPdfToolsPdf2Image_TiffJpegImageOptions* pTiffJpegImageOptions,
                                                     const TPdfToolsPdf2Image_JpegColorSpace* pColorSpace);

/******************************************************************************
 * TiffLzwImageOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_TiffLzwImageOptions* PDFTOOLS_CALL PdfToolsPdf2Image_TiffLzwImageOptions_New(void);

/**
 * @brief Combine a background with the image

This property allows a choice of which background
to combine with the image.

Default: \ref ePdfToolsPdf2Image_BackgroundType_White ""

* @param[in,out] pTiffLzwImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffLzwImageOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_BackgroundType PDFTOOLS_CALL
PdfToolsPdf2Image_TiffLzwImageOptions_GetBackground(TPdfToolsPdf2Image_TiffLzwImageOptions* pTiffLzwImageOptions);
/**
 * @brief Combine a background with the image

This property allows a choice of which background
to combine with the image.

Default: \ref ePdfToolsPdf2Image_BackgroundType_White ""

* @param[in,out] pTiffLzwImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffLzwImageOptions.

* @param[in] iBackground Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_TiffLzwImageOptions_SetBackground(
    TPdfToolsPdf2Image_TiffLzwImageOptions* pTiffLzwImageOptions, TPdfToolsPdf2Image_BackgroundType iBackground);
/**
 * @brief The color space of the output image

Get or set the color space. If null, the blending color space of the page is used.

Default: \ref ePdfToolsPdf2Image_ColorSpace_Rgb ""

* @param[in,out] pTiffLzwImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffLzwImageOptions.

* @param[out] pColorSpace Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_TiffLzwImageOptions_GetColorSpace(
    TPdfToolsPdf2Image_TiffLzwImageOptions* pTiffLzwImageOptions, TPdfToolsPdf2Image_ColorSpace* pColorSpace);
/**
 * @brief The color space of the output image

Get or set the color space. If null, the blending color space of the page is used.

Default: \ref ePdfToolsPdf2Image_ColorSpace_Rgb ""

* @param[in,out] pTiffLzwImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffLzwImageOptions.

* @param[in] pColorSpace Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_TiffLzwImageOptions_SetColorSpace(
    TPdfToolsPdf2Image_TiffLzwImageOptions* pTiffLzwImageOptions, const TPdfToolsPdf2Image_ColorSpace* pColorSpace);

/******************************************************************************
 * TiffFlateImageOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_TiffFlateImageOptions* PDFTOOLS_CALL
PdfToolsPdf2Image_TiffFlateImageOptions_New(void);

/**
 * @brief Combine a background with the image

This property allows a choice of which background
to combine with the image.

Default: \ref ePdfToolsPdf2Image_BackgroundType_White ""

* @param[in,out] pTiffFlateImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffFlateImageOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_BackgroundType PDFTOOLS_CALL
PdfToolsPdf2Image_TiffFlateImageOptions_GetBackground(TPdfToolsPdf2Image_TiffFlateImageOptions* pTiffFlateImageOptions);
/**
 * @brief Combine a background with the image

This property allows a choice of which background
to combine with the image.

Default: \ref ePdfToolsPdf2Image_BackgroundType_White ""

* @param[in,out] pTiffFlateImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffFlateImageOptions.

* @param[in] iBackground Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_TiffFlateImageOptions_SetBackground(
    TPdfToolsPdf2Image_TiffFlateImageOptions* pTiffFlateImageOptions, TPdfToolsPdf2Image_BackgroundType iBackground);
/**
 * @brief The color space of the output image

If `NULL`, the blending color space of the page is used.

Default: \ref ePdfToolsPdf2Image_ColorSpace_Rgb ""

* @param[in,out] pTiffFlateImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffFlateImageOptions.

* @param[out] pColorSpace Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_TiffFlateImageOptions_GetColorSpace(
    TPdfToolsPdf2Image_TiffFlateImageOptions* pTiffFlateImageOptions, TPdfToolsPdf2Image_ColorSpace* pColorSpace);
/**
 * @brief The color space of the output image

If `NULL`, the blending color space of the page is used.

Default: \ref ePdfToolsPdf2Image_ColorSpace_Rgb ""

* @param[in,out] pTiffFlateImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_TiffFlateImageOptions.

* @param[in] pColorSpace Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_TiffFlateImageOptions_SetColorSpace(
    TPdfToolsPdf2Image_TiffFlateImageOptions* pTiffFlateImageOptions, const TPdfToolsPdf2Image_ColorSpace* pColorSpace);

/******************************************************************************
 * PngImageOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_PngImageOptions* PDFTOOLS_CALL PdfToolsPdf2Image_PngImageOptions_New(void);

/**
 * @brief Combine a background with the image

This property allows a choice of which background
to combine with the image.

Default: \ref ePdfToolsPdf2Image_BackgroundType_White ""

* @param[in,out] pPngImageOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_PngImageOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_BackgroundType PDFTOOLS_CALL
PdfToolsPdf2Image_PngImageOptions_GetBackground(TPdfToolsPdf2Image_PngImageOptions* pPngImageOptions);
/**
 * @brief Combine a background with the image

This property allows a choice of which background
to combine with the image.

Default: \ref ePdfToolsPdf2Image_BackgroundType_White ""

* @param[in,out] pPngImageOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_PngImageOptions.

* @param[in] iBackground Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_PngImageOptions_SetBackground(
    TPdfToolsPdf2Image_PngImageOptions* pPngImageOptions, TPdfToolsPdf2Image_BackgroundType iBackground);
/**
 * @brief The color space of the output image

Get or set the color space.

Default: \ref ePdfToolsPdf2Image_PngColorSpace_Rgb ""

* @param[in,out] pPngImageOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_PngImageOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_PngColorSpace PDFTOOLS_CALL
PdfToolsPdf2Image_PngImageOptions_GetColorSpace(TPdfToolsPdf2Image_PngImageOptions* pPngImageOptions);
/**
 * @brief The color space of the output image

Get or set the color space.

Default: \ref ePdfToolsPdf2Image_PngColorSpace_Rgb ""

* @param[in,out] pPngImageOptions Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_PngImageOptions.

* @param[in] iColorSpace Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_PngImageOptions_SetColorSpace(
    TPdfToolsPdf2Image_PngImageOptions* pPngImageOptions, TPdfToolsPdf2Image_PngColorSpace iColorSpace);

/******************************************************************************
 * JpegImageOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_JpegImageOptions* PDFTOOLS_CALL PdfToolsPdf2Image_JpegImageOptions_New(void);

/**
 * @brief The color space of the output image

Get or set the color space of the image.
If `NULL`, the blending color space of the page is used.

Default: \ref ePdfToolsPdf2Image_JpegColorSpace_Rgb ""

* @param[in,out] pJpegImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_JpegImageOptions.

* @param[out] pColorSpace Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_JpegImageOptions_GetColorSpace(
    TPdfToolsPdf2Image_JpegImageOptions* pJpegImageOptions, TPdfToolsPdf2Image_JpegColorSpace* pColorSpace);
/**
 * @brief The color space of the output image

Get or set the color space of the image.
If `NULL`, the blending color space of the page is used.

Default: \ref ePdfToolsPdf2Image_JpegColorSpace_Rgb ""

* @param[in,out] pJpegImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_JpegImageOptions.

* @param[in] pColorSpace Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_JpegImageOptions_SetColorSpace(
    TPdfToolsPdf2Image_JpegImageOptions* pJpegImageOptions, const TPdfToolsPdf2Image_JpegColorSpace* pColorSpace);
/**
 * @brief The JPEG quality factor

Get or set the JPEG compression quality.
Valid values are 1, or 100, or in between.

Default: `85`

* @param[in,out] pJpegImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_JpegImageOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is smaller than 1 or greater than 100.


 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsPdf2Image_JpegImageOptions_GetJpegQuality(TPdfToolsPdf2Image_JpegImageOptions* pJpegImageOptions);
/**
 * @brief The JPEG quality factor

Get or set the JPEG compression quality.
Valid values are 1, or 100, or in between.

Default: `85`

* @param[in,out] pJpegImageOptions Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_JpegImageOptions.

* @param[in] iJpegQuality Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given value is smaller than 1 or greater than 100.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_JpegImageOptions_SetJpegQuality(
    TPdfToolsPdf2Image_JpegImageOptions* pJpegImageOptions, int iJpegQuality);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsPdf2Image_ImageSectionMapping.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pImageSectionMapping Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsPdf2Image_ImageSectionMappingType that refers to the actual derived
 * type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_ImageSectionMappingType PDFTOOLS_CALL
PdfToolsPdf2Image_ImageSectionMapping_GetType(TPdfToolsPdf2Image_ImageSectionMapping* pImageSectionMapping);
/******************************************************************************
 * RenderPageAtResolution
 *****************************************************************************/
/**
* @param[in] pResolution The resolution of the output image.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The resolution is smaller than 0.0 or greater than 10000.0.


 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_RenderPageAtResolution* PDFTOOLS_CALL
PdfToolsPdf2Image_RenderPageAtResolution_New(const TPdfToolsGeomUnits_Resolution* pResolution);

/**
 * @brief The resolution of the output image
Valid values are 0.0, 10000.0 or in between.

* @param[in,out] pRenderPageAtResolution Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_RenderPageAtResolution.

* @param[out] pResolution Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_RenderPageAtResolution_GetResolution(
    TPdfToolsPdf2Image_RenderPageAtResolution* pRenderPageAtResolution, TPdfToolsGeomUnits_Resolution* pResolution);
/**
 * @brief The resolution of the output image
Valid values are 0.0, 10000.0 or in between.

* @param[in,out] pRenderPageAtResolution Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_RenderPageAtResolution.

* @param[in] pResolution Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_RenderPageAtResolution_SetResolution(
    TPdfToolsPdf2Image_RenderPageAtResolution* pRenderPageAtResolution,
    const TPdfToolsGeomUnits_Resolution*       pResolution);

/******************************************************************************
 * RenderPageToMaxImageSize
 *****************************************************************************/
/**
* @param[in] pSize The maximum size of the image in pixels.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The dimensions of `size` are smaller than 1.


 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_RenderPageToMaxImageSize* PDFTOOLS_CALL
PdfToolsPdf2Image_RenderPageToMaxImageSize_New(const TPdfToolsGeomInt_Size* pSize);

/**
 * @brief The maximum size of the image in pixels

Set or get the image size.

The dimensions of `size` must be 1 or greater.

* @param[in,out] pRenderPageToMaxImageSize Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_RenderPageToMaxImageSize.

* @param[out] pSize Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The dimensions of `size` are smaller than 1.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_RenderPageToMaxImageSize_GetSize(
    TPdfToolsPdf2Image_RenderPageToMaxImageSize* pRenderPageToMaxImageSize, TPdfToolsGeomInt_Size* pSize);
/**
 * @brief The maximum size of the image in pixels

Set or get the image size.

The dimensions of `size` must be 1 or greater.

* @param[in,out] pRenderPageToMaxImageSize Acts as a handle to the native object of type \ref
TPdfToolsPdf2Image_RenderPageToMaxImageSize.

* @param[in] pSize Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The dimensions of `size` are smaller than 1.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2Image_RenderPageToMaxImageSize_SetSize(
    TPdfToolsPdf2Image_RenderPageToMaxImageSize* pRenderPageToMaxImageSize, const TPdfToolsGeomInt_Size* pSize);

/******************************************************************************
 * Converter
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_Converter* PDFTOOLS_CALL PdfToolsPdf2Image_Converter_New(void);

/**
 * @brief Convert all pages of a PDF document to a rasterized image
* @param[in,out] pConverter Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_Converter.

* @param[in,out] pInDoc The input PDF document

* @param[in,out] pOutStreamDesc The stream to which the rasterized image is written.

* @param[in,out] pProfile The profile defines how the PDF pages are rendered and what type of output image is used.
Note that the profile's image options must support multi-page images (TIFF).
For other profiles, the method \ref PdfToolsPdf2Image_Converter_ConvertPage "" should be used.
For details, see \ref TPdfToolsPdf2ImageProfiles_Profile "".


 * @return
  The output image document.
  The object can be used as input for further processing.

  Note that, this object must be disposed before the output stream
  object (method argument <b>pOutStreamDesc</b>).

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license is invalid.

 * - \ref ePdfTools_Error_IO Writing to the output image failed.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF is a PDF collection (Portfolio) that has no cover pages.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF contains unrendered XFA form fields.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_Generic An unexpected failure occurred.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pProfile</b> does not support multi-page output.

 * - \ref ePdfTools_Error_Processing The processing has failed.

 * - \ref ePdfTools_Error_IllegalState Internal error has occured.


 */
PDFTOOLS_EXPORT TPdfToolsImage_MultiPageDocument* PDFTOOLS_CALL PdfToolsPdf2Image_Converter_ConvertDocument(
    TPdfToolsPdf2Image_Converter* pConverter, TPdfToolsPdf_Document* pInDoc,
    const TPdfToolsSys_StreamDescriptor* pOutStreamDesc, TPdfToolsPdf2ImageProfiles_Profile* pProfile);
/**
 * @brief Convert a single page of a PDF document to a rasterized image
* @param[in,out] pConverter Acts as a handle to the native object of type \ref TPdfToolsPdf2Image_Converter.

* @param[in,out] pInDoc The input PDF document

* @param[in,out] pOutStreamDesc The stream to which the rasterized image is written.

* @param[in,out] pProfile The profile defines how the PDF page is rendered and what type of output image is used.
For details, see \ref TPdfToolsPdf2ImageProfiles_Profile "".

* @param[in] iPageNumber The PDF page number to be converted.
The number must be in the range of `1` (first page) to \ref PdfToolsPdf_Document_GetPageCount "" (last page).


 * @return
  The image object allowing to open and read the
  output image and treat it as a new input for further processing.

  Note that, this object must be disposed before the output stream
  object (method argument <b>pOutStreamDesc</b>).

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license is invalid.

 * - \ref ePdfTools_Error_IllegalArgument The <b>iPageNumber</b> is not in the allowed range.

 * - \ref ePdfTools_Error_IO Writing to the output image failed.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF is a collection that has no cover pages.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF contains unrendered XFA form fields.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_Generic An unexpected failure occurred.

 * - \ref ePdfTools_Error_Processing The processing has failed.


 */
PDFTOOLS_EXPORT TPdfToolsImage_Document* PDFTOOLS_CALL PdfToolsPdf2Image_Converter_ConvertPage(
    TPdfToolsPdf2Image_Converter* pConverter, TPdfToolsPdf_Document* pInDoc,
    const TPdfToolsSys_StreamDescriptor* pOutStreamDesc, TPdfToolsPdf2ImageProfiles_Profile* pProfile, int iPageNumber);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSPDF2IMAGE_H__ */
