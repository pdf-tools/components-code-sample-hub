/******************************************************************************
 *
 * File:            PdfTools_PdfToolsImage.h
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

#ifndef PDFTOOLS_PDFTOOLSIMAGE_H__
#define PDFTOOLS_PDFTOOLSIMAGE_H__

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
 * Page
 *****************************************************************************/
/**
 * @brief The size of the page in number of pixels
* @param[in,out] pPage Acts as a handle to the native object of type \ref TPdfToolsImage_Page.

* @param[out] pSize Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Generic A generic error occurred.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage_Page_GetSize(TPdfToolsImage_Page* pPage, TPdfToolsGeomInt_Size* pSize);
/**
 * @brief The resolution of the page
The resolution can be `NULL` if the image does not specify a resolution.

* @param[in,out] pPage Acts as a handle to the native object of type \ref TPdfToolsImage_Page.

* @param[out] pResolution Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Generic A generic error occurred.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage_Page_GetResolution(TPdfToolsImage_Page*           pPage,
                                                                    TPdfToolsGeomUnits_Resolution* pResolution);

/******************************************************************************
 * PageList
 *****************************************************************************/
/**
 * @brief Get the number of elements in the list.
* @param[in,out] pPageList Acts as a handle to the native object of type \ref TPdfToolsImage_PageList.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfToolsImage_PageList_GetCount(TPdfToolsImage_PageList* pPageList);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pPageList Acts as a handle to the native object of type \ref TPdfToolsImage_PageList.

* @param[in] iIndex

 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT TPdfToolsImage_Page* PDFTOOLS_CALL PdfToolsImage_PageList_Get(TPdfToolsImage_PageList* pPageList,
                                                                              int                      iIndex);

/******************************************************************************
 * Document
 *****************************************************************************/
/**
 * @brief Open an image document
Documents opened with this method are read-only and cannot be modified.

* @param[in] pStreamDesc The stream from which the image is read.


 * @return   The newly created document instance

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_UnknownFormat The document has a not recognized image format.

 * - \ref ePdfTools_Error_Corrupt The document is corrupt or not an image.


 */
PDFTOOLS_EXPORT TPdfToolsImage_Document* PDFTOOLS_CALL
PdfToolsImage_Document_Open(const TPdfToolsSys_StreamDescriptor* pStreamDesc);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsImage_Document.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pDocument Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsImage_DocumentType that refers to the actual derived type. `0` in
 * case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsImage_DocumentType PDFTOOLS_CALL
PdfToolsImage_Document_GetType(TPdfToolsImage_Document* pDocument);
/**
 * @brief Close object.
 *
 * Close disposable objects by invoking this function.
 *
 * @param[in] pObject Disposable object.
 *
 * @return   \ref TRUE if the object was closed successfully; \ref FALSE if an error occured while closing the object.
 *           Retrieve the error code by calling \ref PdfTools_GetLastError .
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage_Document_Close(TPdfToolsImage_Document* pObject);
/******************************************************************************
 * SinglePageDocument
 *****************************************************************************/
/**
 * @brief The page of the image
* @param[in,out] pSinglePageDocument Acts as a handle to the native object of type \ref
TPdfToolsImage_SinglePageDocument.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage_Page* PDFTOOLS_CALL
PdfToolsImage_SinglePageDocument_GetPage(TPdfToolsImage_SinglePageDocument* pSinglePageDocument);

/******************************************************************************
 * MultiPageDocument
 *****************************************************************************/
/**
 * @brief The pages of the image
* @param[in,out] pMultiPageDocument Acts as a handle to the native object of type \ref TPdfToolsImage_MultiPageDocument.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage_PageList* PDFTOOLS_CALL
PdfToolsImage_MultiPageDocument_GetPages(TPdfToolsImage_MultiPageDocument* pMultiPageDocument);

/******************************************************************************
 * DocumentList
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage_DocumentList* PDFTOOLS_CALL PdfToolsImage_DocumentList_New(void);

/**
 * @brief Get the number of elements in the list.
* @param[in,out] pDocumentList Acts as a handle to the native object of type \ref TPdfToolsImage_DocumentList.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfToolsImage_DocumentList_GetCount(TPdfToolsImage_DocumentList* pDocumentList);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pDocumentList Acts as a handle to the native object of type \ref TPdfToolsImage_DocumentList.

* @param[in] iIndex

 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT TPdfToolsImage_Document* PDFTOOLS_CALL
PdfToolsImage_DocumentList_Get(TPdfToolsImage_DocumentList* pDocumentList, int iIndex);
/**
 * @brief Add an element to the end of the list.
* @param[in,out] pDocumentList Acts as a handle to the native object of type \ref TPdfToolsImage_DocumentList.

* @param[in,out] pDocument

 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage_DocumentList_Add(TPdfToolsImage_DocumentList* pDocumentList,
                                                                  TPdfToolsImage_Document*     pDocument);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSIMAGE_H__ */
