/******************************************************************************
 *
 * File:            PdfTools_PdfToolsPdf2ImageProfiles.h
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

#ifndef PDFTOOLS_PDFTOOLSPDF2IMAGEPROFILES_H__
#define PDFTOOLS_PDFTOOLSPDF2IMAGEPROFILES_H__

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
 * @brief The parameters how to render PDF content elements
* @param[in,out] pProfile Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Profile.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_ContentOptions* PDFTOOLS_CALL
PdfToolsPdf2ImageProfiles_Profile_GetContentOptions(TPdfToolsPdf2ImageProfiles_Profile* pProfile);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsPdf2ImageProfiles_Profile.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pProfile Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsPdf2ImageProfiles_ProfileType that refers to the actual derived
 * type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsPdf2ImageProfiles_ProfileType PDFTOOLS_CALL
PdfToolsPdf2ImageProfiles_Profile_GetType(TPdfToolsPdf2ImageProfiles_Profile* pProfile);
/******************************************************************************
 * Fax
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2ImageProfiles_Fax* PDFTOOLS_CALL PdfToolsPdf2ImageProfiles_Fax_New(void);

/**
 * @brief The settings for the output image
* @param[in,out] pFax Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Fax.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_FaxImageOptions* PDFTOOLS_CALL
PdfToolsPdf2ImageProfiles_Fax_GetImageOptions(TPdfToolsPdf2ImageProfiles_Fax* pFax);
/**
 * @brief The image section mapping
This property specifies how a PDF page is placed onto the target image.

* @param[in,out] pFax Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Fax.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_RenderPageAsFax* PDFTOOLS_CALL
PdfToolsPdf2ImageProfiles_Fax_GetImageSectionMapping(TPdfToolsPdf2ImageProfiles_Fax* pFax);

/******************************************************************************
 * Archive
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2ImageProfiles_Archive* PDFTOOLS_CALL PdfToolsPdf2ImageProfiles_Archive_New(void);

/**
 * @brief The settings for the output TIFF

Defines the compression algorithm of the TIFF output image.

Supported types are:
  - \ref TPdfToolsPdf2Image_TiffJpegImageOptions ""
  - \ref TPdfToolsPdf2Image_TiffLzwImageOptions ""
  - \ref TPdfToolsPdf2Image_TiffFlateImageOptions ""

Default: \ref TPdfToolsPdf2Image_TiffLzwImageOptions ""

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Archive.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given object has the wrong type.


 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_ImageOptions* PDFTOOLS_CALL
PdfToolsPdf2ImageProfiles_Archive_GetImageOptions(TPdfToolsPdf2ImageProfiles_Archive* pArchive);
/**
 * @brief The settings for the output TIFF

Defines the compression algorithm of the TIFF output image.

Supported types are:
  - \ref TPdfToolsPdf2Image_TiffJpegImageOptions ""
  - \ref TPdfToolsPdf2Image_TiffLzwImageOptions ""
  - \ref TPdfToolsPdf2Image_TiffFlateImageOptions ""

Default: \ref TPdfToolsPdf2Image_TiffLzwImageOptions ""

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Archive.

* @param[in,out] pImageOptions Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given object has the wrong type.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2ImageProfiles_Archive_SetImageOptions(
    TPdfToolsPdf2ImageProfiles_Archive* pArchive, TPdfToolsPdf2Image_ImageOptions* pImageOptions);
/**
 * @brief The image section mapping

This property defines the resolution of the output images.

Default: 300 DPI.

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Archive.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_RenderPageAtResolution* PDFTOOLS_CALL
PdfToolsPdf2ImageProfiles_Archive_GetImageSectionMapping(TPdfToolsPdf2ImageProfiles_Archive* pArchive);

/******************************************************************************
 * Viewing
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf2ImageProfiles_Viewing* PDFTOOLS_CALL PdfToolsPdf2ImageProfiles_Viewing_New(void);

/**
 * @brief The settings for the output image

Supported types are:
  - \ref TPdfToolsPdf2Image_PngImageOptions "" to create PNG images
  - \ref TPdfToolsPdf2Image_JpegImageOptions "" to create JPEG images

Default: \ref TPdfToolsPdf2Image_PngImageOptions ""

* @param[in,out] pViewing Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Viewing.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given object has the wrong type.


 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_ImageOptions* PDFTOOLS_CALL
PdfToolsPdf2ImageProfiles_Viewing_GetImageOptions(TPdfToolsPdf2ImageProfiles_Viewing* pViewing);
/**
 * @brief The settings for the output image

Supported types are:
  - \ref TPdfToolsPdf2Image_PngImageOptions "" to create PNG images
  - \ref TPdfToolsPdf2Image_JpegImageOptions "" to create JPEG images

Default: \ref TPdfToolsPdf2Image_PngImageOptions ""

* @param[in,out] pViewing Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Viewing.

* @param[in,out] pImageOptions Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given object has the wrong type.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2ImageProfiles_Viewing_SetImageOptions(
    TPdfToolsPdf2ImageProfiles_Viewing* pViewing, TPdfToolsPdf2Image_ImageOptions* pImageOptions);
/**
 * @brief The image section mapping

This property specifies how a PDF page is placed onto the target image.

Supported types are:
  - \ref TPdfToolsPdf2Image_RenderPageAtResolution "" to define the resolution of the output images.
  - \ref TPdfToolsPdf2Image_RenderPageToMaxImageSize "" to define the maximum image size of the output images.

Default: \ref TPdfToolsPdf2Image_RenderPageAtResolution "" with 150 DPI.

* @param[in,out] pViewing Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Viewing.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given object has the wrong type.


 */
PDFTOOLS_EXPORT TPdfToolsPdf2Image_ImageSectionMapping* PDFTOOLS_CALL
PdfToolsPdf2ImageProfiles_Viewing_GetImageSectionMapping(TPdfToolsPdf2ImageProfiles_Viewing* pViewing);
/**
 * @brief The image section mapping

This property specifies how a PDF page is placed onto the target image.

Supported types are:
  - \ref TPdfToolsPdf2Image_RenderPageAtResolution "" to define the resolution of the output images.
  - \ref TPdfToolsPdf2Image_RenderPageToMaxImageSize "" to define the maximum image size of the output images.

Default: \ref TPdfToolsPdf2Image_RenderPageAtResolution "" with 150 DPI.

* @param[in,out] pViewing Acts as a handle to the native object of type \ref TPdfToolsPdf2ImageProfiles_Viewing.

* @param[in,out] pImageSectionMapping Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The given object has the wrong type.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf2ImageProfiles_Viewing_SetImageSectionMapping(
    TPdfToolsPdf2ImageProfiles_Viewing* pViewing, TPdfToolsPdf2Image_ImageSectionMapping* pImageSectionMapping);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSPDF2IMAGEPROFILES_H__ */
