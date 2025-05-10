/******************************************************************************
 *
 * File:            PdfTools_PdfToolsImage2Pdf.h
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

#ifndef PDFTOOLS_PDFTOOLSIMAGE2PDF_H__
#define PDFTOOLS_PDFTOOLSIMAGE2PDF_H__

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

/**
 * @brief Get actual derived type of base type \ref TPdfToolsImage2Pdf_ImageMapping.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pImageMapping Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsImage2Pdf_ImageMappingType that refers to the actual derived type.
 * `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsImage2Pdf_ImageMappingType PDFTOOLS_CALL
PdfToolsImage2Pdf_ImageMapping_GetType(TPdfToolsImage2Pdf_ImageMapping* pImageMapping);
/******************************************************************************
 * Auto
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2Pdf_Auto* PDFTOOLS_CALL PdfToolsImage2Pdf_Auto_New(void);

/**
 * @brief The maximum page size

Each image is scaled individually such that neither the
width nor the height exceeds the maximum page size.
For landscape images the maximum page size is assumed
to be landscape, and equivalently for portrait images.

Default value: "A4" (210mm 297mm)

* @param[in,out] pAuto Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_Auto.

* @param[out] pMaxPageSize Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument is smaller than "3pt 3pt" or larger than "14400pt 14400pt".


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_Auto_GetMaxPageSize(TPdfToolsImage2Pdf_Auto* pAuto,
                                                                         TPdfToolsGeomUnits_Size* pMaxPageSize);
/**
 * @brief The maximum page size

Each image is scaled individually such that neither the
width nor the height exceeds the maximum page size.
For landscape images the maximum page size is assumed
to be landscape, and equivalently for portrait images.

Default value: "A4" (210mm 297mm)

* @param[in,out] pAuto Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_Auto.

* @param[in] pMaxPageSize Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument is smaller than "3pt 3pt" or larger than "14400pt 14400pt".


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_Auto_SetMaxPageSize(TPdfToolsImage2Pdf_Auto*       pAuto,
                                                                         const TPdfToolsGeomUnits_Size* pMaxPageSize);
/**
 * @brief The default page margin
Default value: 20mm (0.79in)

* @param[in,out] pAuto Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_Auto.

* @param[out] pDefaultPageMargin Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument has negative margin values.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_Auto_GetDefaultPageMargin(
    TPdfToolsImage2Pdf_Auto* pAuto, TPdfToolsGeomUnits_Margin* pDefaultPageMargin);
/**
 * @brief The default page margin
Default value: 20mm (0.79in)

* @param[in,out] pAuto Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_Auto.

* @param[in] pDefaultPageMargin Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument has negative margin values.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_Auto_SetDefaultPageMargin(
    TPdfToolsImage2Pdf_Auto* pAuto, const TPdfToolsGeomUnits_Margin* pDefaultPageMargin);

/******************************************************************************
 * ShrinkToPage
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2Pdf_ShrinkToPage* PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPage_New(void);

/**
 * @brief The page size

All output pages are created with that size.
The default page orientation is portrait, but
if the image fits better, the page is rotated to landscape.

Default value: "A4" (210mm 297mm)

* @param[in,out] pShrinkToPage Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ShrinkToPage.

* @param[out] pPageSize Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument is smaller than "3pt 3pt" or larger than "14400pt 14400pt".


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPage_GetPageSize(
    TPdfToolsImage2Pdf_ShrinkToPage* pShrinkToPage, TPdfToolsGeomUnits_Size* pPageSize);
/**
 * @brief The page size

All output pages are created with that size.
The default page orientation is portrait, but
if the image fits better, the page is rotated to landscape.

Default value: "A4" (210mm 297mm)

* @param[in,out] pShrinkToPage Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ShrinkToPage.

* @param[in] pPageSize Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument is smaller than "3pt 3pt" or larger than "14400pt 14400pt".


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPage_SetPageSize(
    TPdfToolsImage2Pdf_ShrinkToPage* pShrinkToPage, const TPdfToolsGeomUnits_Size* pPageSize);
/**
 * @brief The page margin
Default value: 20mm (0.79in)

* @param[in,out] pShrinkToPage Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ShrinkToPage.

* @param[out] pPageMargin Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument has negative margin values.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPage_GetPageMargin(
    TPdfToolsImage2Pdf_ShrinkToPage* pShrinkToPage, TPdfToolsGeomUnits_Margin* pPageMargin);
/**
 * @brief The page margin
Default value: 20mm (0.79in)

* @param[in,out] pShrinkToPage Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ShrinkToPage.

* @param[in] pPageMargin Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument has negative margin values.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPage_SetPageMargin(
    TPdfToolsImage2Pdf_ShrinkToPage* pShrinkToPage, const TPdfToolsGeomUnits_Margin* pPageMargin);

/******************************************************************************
 * ShrinkToFit
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2Pdf_ShrinkToFit* PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToFit_New(void);

/**
 * @brief The page size

All output pages are created as that size.

Default value: "A4" (210mm 297mm)

* @param[in,out] pShrinkToFit Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ShrinkToFit.

* @param[out] pPageSize Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument is smaller than "3pt 3pt" or larger than "14400pt 14400pt".


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToFit_GetPageSize(
    TPdfToolsImage2Pdf_ShrinkToFit* pShrinkToFit, TPdfToolsGeomUnits_Size* pPageSize);
/**
 * @brief The page size

All output pages are created as that size.

Default value: "A4" (210mm 297mm)

* @param[in,out] pShrinkToFit Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ShrinkToFit.

* @param[in] pPageSize Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument is smaller than "3pt 3pt" or larger than "14400pt 14400pt".


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToFit_SetPageSize(
    TPdfToolsImage2Pdf_ShrinkToFit* pShrinkToFit, const TPdfToolsGeomUnits_Size* pPageSize);
/**
 * @brief The page margin
Default value: 20mm (0.79in)

* @param[in,out] pShrinkToFit Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ShrinkToFit.

* @param[out] pPageMargin Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument has negative margin values.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToFit_GetPageMargin(
    TPdfToolsImage2Pdf_ShrinkToFit* pShrinkToFit, TPdfToolsGeomUnits_Margin* pPageMargin);
/**
 * @brief The page margin
Default value: 20mm (0.79in)

* @param[in,out] pShrinkToFit Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ShrinkToFit.

* @param[in] pPageMargin Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument has negative margin values.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToFit_SetPageMargin(
    TPdfToolsImage2Pdf_ShrinkToFit* pShrinkToFit, const TPdfToolsGeomUnits_Margin* pPageMargin);

/******************************************************************************
 * ShrinkToPortrait
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2Pdf_ShrinkToPortrait* PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPortrait_New(void);

/**
 * @brief The page size

All output pages are created as that size and in portrait mode.

Default value: "A4" (210mm 297mm)

* @param[in,out] pShrinkToPortrait Acts as a handle to the native object of type \ref
TPdfToolsImage2Pdf_ShrinkToPortrait.

* @param[out] pPageSize Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument is smaller than "3pt 3pt" or larger than "14400pt 14400pt".


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPortrait_GetPageSize(
    TPdfToolsImage2Pdf_ShrinkToPortrait* pShrinkToPortrait, TPdfToolsGeomUnits_Size* pPageSize);
/**
 * @brief The page size

All output pages are created as that size and in portrait mode.

Default value: "A4" (210mm 297mm)

* @param[in,out] pShrinkToPortrait Acts as a handle to the native object of type \ref
TPdfToolsImage2Pdf_ShrinkToPortrait.

* @param[in] pPageSize Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument is smaller than "3pt 3pt" or larger than "14400pt 14400pt".


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPortrait_SetPageSize(
    TPdfToolsImage2Pdf_ShrinkToPortrait* pShrinkToPortrait, const TPdfToolsGeomUnits_Size* pPageSize);
/**
 * @brief The page margin
Default value: 20mm (0.79in)

* @param[in,out] pShrinkToPortrait Acts as a handle to the native object of type \ref
TPdfToolsImage2Pdf_ShrinkToPortrait.

* @param[out] pPageMargin Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument has negative margin values.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPortrait_GetPageMargin(
    TPdfToolsImage2Pdf_ShrinkToPortrait* pShrinkToPortrait, TPdfToolsGeomUnits_Margin* pPageMargin);
/**
 * @brief The page margin
Default value: 20mm (0.79in)

* @param[in,out] pShrinkToPortrait Acts as a handle to the native object of type \ref
TPdfToolsImage2Pdf_ShrinkToPortrait.

* @param[in] pPageMargin Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The argument has negative margin values.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ShrinkToPortrait_SetPageMargin(
    TPdfToolsImage2Pdf_ShrinkToPortrait* pShrinkToPortrait, const TPdfToolsGeomUnits_Margin* pPageMargin);

/******************************************************************************
 * ImageOptions
 *****************************************************************************/
/**
 * @brief The image mapping

The image mapping specifies how an input image is transformed and placed
onto the output PDF page.

Default: \ref TPdfToolsImage2Pdf_ShrinkToFit ""

* @param[in,out] pImageOptions Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ImageOptions.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2Pdf_ImageMapping* PDFTOOLS_CALL
PdfToolsImage2Pdf_ImageOptions_GetMapping(TPdfToolsImage2Pdf_ImageOptions* pImageOptions);
/**
 * @brief The image mapping

The image mapping specifies how an input image is transformed and placed
onto the output PDF page.

Default: \ref TPdfToolsImage2Pdf_ShrinkToFit ""

* @param[in,out] pImageOptions Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_ImageOptions.

* @param[in,out] pMapping Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2Pdf_ImageOptions_SetMapping(
    TPdfToolsImage2Pdf_ImageOptions* pImageOptions, TPdfToolsImage2Pdf_ImageMapping* pMapping);

/******************************************************************************
 * Converter
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2Pdf_Converter* PDFTOOLS_CALL PdfToolsImage2Pdf_Converter_New(void);

/**
 * @brief Convert an image to a PDF document
* @param[in,out] pConverter Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_Converter.

* @param[in,out] pImage The input image document containing one or more pages.

* @param[in,out] pOutStreamDesc The stream to which the PDF is written.

* @param[in,out] pProfile The profile defines the properties of the output document and
how the images are placed onto the pages.
For details, see \ref TPdfToolsImage2PdfProfiles_Profile "".

* @param[in,out] pOutOptions The PDF output options, e.g. to encrypt the output document.


 * @return
  The resulting output PDF which can be used as a new input
  for further processing.

  Note that, this object must be disposed before the output stream
  object (method argument <b>pOutStreamDesc</b>).

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license is invalid.

 * - \ref ePdfTools_Error_IO Writing to the output PDF failed.

 * - \ref ePdfTools_Error_Corrupt The input image document is corrupt and cannot be read.

 * - \ref ePdfTools_Error_Generic An unexpected failure occurred.

 * - \ref ePdfTools_Error_Processing The conversion failed.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pProfile</b> specifies invalid options.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pOutOptions</b> specifies document encryption and the <b>pProfile</b>
PDF/A conformance, which is not allowed.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsImage2Pdf_Converter_Convert(
    TPdfToolsImage2Pdf_Converter* pConverter, TPdfToolsImage_Document* pImage,
    const TPdfToolsSys_StreamDescriptor* pOutStreamDesc, TPdfToolsImage2PdfProfiles_Profile* pProfile,
    TPdfToolsPdf_OutputOptions* pOutOptions);
/**
 * @brief Convert a list of images to a PDF document
* @param[in,out] pConverter Acts as a handle to the native object of type \ref TPdfToolsImage2Pdf_Converter.

* @param[in,out] pImages The input image document list, each image containing one or more pages.

* @param[in,out] pOutStreamDesc The stream to which the PDF is written.

* @param[in,out] pProfile The profile defines the properties of the output document and
how the images are placed onto the pages.
For details, see \ref TPdfToolsImage2PdfProfiles_Profile "".

* @param[in,out] pOutOptions The PDF output options, e.g. to encrypt the output document.


 * @return
  The resulting output PDF which can be used as a new input
  for further processing.

  Note that, this object must be disposed before the output stream
  object (method argument <b>pOutStreamDesc</b>).

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license is invalid.

 * - \ref ePdfTools_Error_IO Writing to the output PDF failed.

 * - \ref ePdfTools_Error_Corrupt An input image document is corrupt and cannot be read.

 * - \ref ePdfTools_Error_Generic An unexpected failure occurred.

 * - \ref ePdfTools_Error_Processing The conversion failed.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pProfile</b> specifies invalid options.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pOutOptions</b> specifies document encryption and the <b>pProfile</b>
PDF/A conformance, which is not allowed.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsImage2Pdf_Converter_ConvertMultiple(
    TPdfToolsImage2Pdf_Converter* pConverter, TPdfToolsImage_DocumentList* pImages,
    const TPdfToolsSys_StreamDescriptor* pOutStreamDesc, TPdfToolsImage2PdfProfiles_Profile* pProfile,
    TPdfToolsPdf_OutputOptions* pOutOptions);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSIMAGE2PDF_H__ */
