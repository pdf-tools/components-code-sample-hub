/******************************************************************************
 *
 * File:            PdfTools_PdfToolsDocumentAssembly.h
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

#ifndef PDFTOOLS_PDFTOOLSDOCUMENTASSEMBLY_H__
#define PDFTOOLS_PDFTOOLSDOCUMENTASSEMBLY_H__

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
 * PageCopyOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_PageCopyOptions* PDFTOOLS_CALL
PdfToolsDocumentAssembly_PageCopyOptions_New(void);

/**
 * @brief Copy strategy for links.

Specifies how links (document internal and external links) are treated
when copying a page.

Default value: \ref ePdfToolsDocumentAssembly_CopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_CopyStrategy PDFTOOLS_CALL
PdfToolsDocumentAssembly_PageCopyOptions_GetLinks(TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Copy strategy for links.

Specifies how links (document internal and external links) are treated
when copying a page.

Default value: \ref ePdfToolsDocumentAssembly_CopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] iLinks Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetLinks(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions, TPdfToolsDocumentAssembly_CopyStrategy iLinks);
/**
 * @brief Copy strategy for form fields.

Specifies how form fields are treated when copying a page.

Default value: \ref ePdfToolsDocumentAssembly_CopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_CopyStrategy PDFTOOLS_CALL
PdfToolsDocumentAssembly_PageCopyOptions_GetFormFields(TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Copy strategy for form fields.

Specifies how form fields are treated when copying a page.

Default value: \ref ePdfToolsDocumentAssembly_CopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] iFormFields Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetFormFields(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions, TPdfToolsDocumentAssembly_CopyStrategy iFormFields);
/**
 * @brief Removal strategy for signed signature fields.

Signed digital signatures are always invalidated when copying a page
and therefore have to be removed.
This property specifies, whether the visual representation of the signature
is preserved.

Default value: \ref ePdfToolsDocumentAssembly_RemovalStrategy_Remove ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_RemovalStrategy PDFTOOLS_CALL
PdfToolsDocumentAssembly_PageCopyOptions_GetSignedSignatures(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Removal strategy for signed signature fields.

Signed digital signatures are always invalidated when copying a page
and therefore have to be removed.
This property specifies, whether the visual representation of the signature
is preserved.

Default value: \ref ePdfToolsDocumentAssembly_RemovalStrategy_Remove ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] iSignedSignatures Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetSignedSignatures(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions,
    TPdfToolsDocumentAssembly_RemovalStrategy  iSignedSignatures);
/**
 * @brief Copy strategy for unsigned signature fields.

Specifies how signature fields are treated, that are not yet signed.

Default value: \ref ePdfToolsDocumentAssembly_CopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_CopyStrategy PDFTOOLS_CALL
PdfToolsDocumentAssembly_PageCopyOptions_GetUnsignedSignatures(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Copy strategy for unsigned signature fields.

Specifies how signature fields are treated, that are not yet signed.

Default value: \ref ePdfToolsDocumentAssembly_CopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] iUnsignedSignatures Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetUnsignedSignatures(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions,
    TPdfToolsDocumentAssembly_CopyStrategy     iUnsignedSignatures);
/**
 * @brief Copy strategy for annotations.

Specifies how interactive annotations (like sticky notes or text highlights)
are treated when copying a page.
This does not include links, form fields and signature fields which
are not considered annotations in this product.

Default value: \ref ePdfToolsDocumentAssembly_CopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_CopyStrategy PDFTOOLS_CALL
PdfToolsDocumentAssembly_PageCopyOptions_GetAnnotations(TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Copy strategy for annotations.

Specifies how interactive annotations (like sticky notes or text highlights)
are treated when copying a page.
This does not include links, form fields and signature fields which
are not considered annotations in this product.

Default value: \ref ePdfToolsDocumentAssembly_CopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] iAnnotations Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetAnnotations(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions, TPdfToolsDocumentAssembly_CopyStrategy iAnnotations);
/**
 * @brief Copy outline items (bookmarks).

Specifies whether outline items (also known as bookmarks) pointing to the copied page
should be copied to the target document automatically.

Default value: \ref "TRUE"

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_GetCopyOutlineItems(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Copy outline items (bookmarks).

Specifies whether outline items (also known as bookmarks) pointing to the copied page
should be copied to the target document automatically.

Default value: \ref "TRUE"

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] bCopyOutlineItems Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetCopyOutlineItems(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions, BOOL bCopyOutlineItems);
/**
 * @brief Copy associated files.

Specifies whether embedded files associated with a page or any of its
subobjects are also copied when copying the page.

Default value: \ref "TRUE"

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_GetCopyAssociatedFiles(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Copy associated files.

Specifies whether embedded files associated with a page or any of its
subobjects are also copied when copying the page.

Default value: \ref "TRUE"

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] bCopyAssociatedFiles Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetCopyAssociatedFiles(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions, BOOL bCopyAssociatedFiles);
/**
 * @brief Copy the logical structure and tagging information.

Specifies whether the logical structure and tagging information associated
with a page or its content is also copied when copying the page.

This is required if the target document conformance is PDF/A Level a.

Default value: \ref "TRUE"

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_GetCopyLogicalStructure(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Copy the logical structure and tagging information.

Specifies whether the logical structure and tagging information associated
with a page or its content is also copied when copying the page.

This is required if the target document conformance is PDF/A Level a.

Default value: \ref "TRUE"

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] bCopyLogicalStructure Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetCopyLogicalStructure(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions, BOOL bCopyLogicalStructure);
/**
 * @brief Resolution of conflicting form field names.

Form field of different files can have the same name (identifier).
This property specifies how name conflicts are resolved,
when copying pages from multiple source files.

Default value: \ref ePdfToolsDocumentAssembly_NameConflictResolution_Merge ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_NameConflictResolution PDFTOOLS_CALL
PdfToolsDocumentAssembly_PageCopyOptions_GetFormFieldConflictResolution(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Resolution of conflicting form field names.

Form field of different files can have the same name (identifier).
This property specifies how name conflicts are resolved,
when copying pages from multiple source files.

Default value: \ref ePdfToolsDocumentAssembly_NameConflictResolution_Merge ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] iFormFieldConflictResolution Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetFormFieldConflictResolution(
    TPdfToolsDocumentAssembly_PageCopyOptions*       pPageCopyOptions,
    TPdfToolsDocumentAssembly_NameConflictResolution iFormFieldConflictResolution);
/**
 * @brief Copy strategy for named destinations

Specify whether named destinations are resolved when copying a page.

Default value: \ref ePdfToolsDocumentAssembly_NamedDestinationCopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_NamedDestinationCopyStrategy PDFTOOLS_CALL
PdfToolsDocumentAssembly_PageCopyOptions_GetNamedDestinations(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Copy strategy for named destinations

Specify whether named destinations are resolved when copying a page.

Default value: \ref ePdfToolsDocumentAssembly_NamedDestinationCopyStrategy_Copy ""

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] iNamedDestinations Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetNamedDestinations(
    TPdfToolsDocumentAssembly_PageCopyOptions*             pPageCopyOptions,
    TPdfToolsDocumentAssembly_NamedDestinationCopyStrategy iNamedDestinations);
/**
 * @brief Find and merge redundant resources.

Find and merge redundant resources such as fonts and images.
This can lead to much smaller files, especially when copying
pages from multiple similar source files.
However, it also results in longer processing time.

Default value: \ref "TRUE"

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_GetOptimizeResources(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Find and merge redundant resources.

Find and merge redundant resources such as fonts and images.
This can lead to much smaller files, especially when copying
pages from multiple similar source files.
However, it also results in longer processing time.

Default value: \ref "TRUE"

* @param[in,out] pPageCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_PageCopyOptions.

* @param[in] bOptimizeResources Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_PageCopyOptions_SetOptimizeResources(
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions, BOOL bOptimizeResources);

/******************************************************************************
 * DocumentCopyOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_DocumentCopyOptions* PDFTOOLS_CALL
PdfToolsDocumentAssembly_DocumentCopyOptions_New(void);

/**

Copy document information dictionary and XMP metadata.

Default: \ref "FALSE".

* @param[in,out] pDocumentCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentCopyOptions_GetCopyMetadata(
    TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions);
/**

Copy document information dictionary and XMP metadata.

Default: \ref "FALSE".

* @param[in,out] pDocumentCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentCopyOptions.

* @param[in] bCopyMetadata Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentCopyOptions_SetCopyMetadata(
    TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions, BOOL bCopyMetadata);
/**

Copy the PDF/A output intent.

Default: \ref "FALSE".

* @param[in,out] pDocumentCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentCopyOptions_GetCopyOutputIntent(
    TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions);
/**

Copy the PDF/A output intent.

Default: \ref "FALSE".

* @param[in,out] pDocumentCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentCopyOptions.

* @param[in] bCopyOutputIntent Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentCopyOptions_SetCopyOutputIntent(
    TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions, BOOL bCopyOutputIntent);
/**

Copy viewer properties, which include: Page Layout, Page Mode, Open Actions, Piece Info, and Collection properties.

Default: \ref "FALSE".

* @param[in,out] pDocumentCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentCopyOptions_GetCopyViewerSettings(
    TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions);
/**

Copy viewer properties, which include: Page Layout, Page Mode, Open Actions, Piece Info, and Collection properties.

Default: \ref "FALSE".

* @param[in,out] pDocumentCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentCopyOptions.

* @param[in] bCopyViewerSettings Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentCopyOptions_SetCopyViewerSettings(
    TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions, BOOL bCopyViewerSettings);
/**

If set to \ref "TRUE": All embedded files are copied. If set to \ref "FALSE": Only embedded files associated with pages
within the given page range are copied. (PDF/A-3 only, \ref
PdfToolsDocumentAssembly_PageCopyOptions_GetCopyAssociatedFiles "" must be set.)

Default: \ref "FALSE".

* @param[in,out] pDocumentCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentCopyOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentCopyOptions_GetCopyEmbeddedFiles(
    TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions);
/**

If set to \ref "TRUE": All embedded files are copied. If set to \ref "FALSE": Only embedded files associated with pages
within the given page range are copied. (PDF/A-3 only, \ref
PdfToolsDocumentAssembly_PageCopyOptions_GetCopyAssociatedFiles "" must be set.)

Default: \ref "FALSE".

* @param[in,out] pDocumentCopyOptions Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentCopyOptions.

* @param[in] bCopyEmbeddedFiles Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentCopyOptions_SetCopyEmbeddedFiles(
    TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions, BOOL bCopyEmbeddedFiles);

/******************************************************************************
 * DocumentAssembler
 *****************************************************************************/
/**
* @param[in,out] pOutStreamDesc The stream to which the output PDF is written

* @param[in,out] pOutOptions The PDF output options, e.g. to encrypt the output document.

* @param[in] pConformance The required conformance level of the PDF document.
Adding pages or content from incompatible documents or using
incompatible features will lead to a conformance error.
When using `NULL`, the conformance is determined automatically,
based on the conformance of the input documents used in the \ref PdfToolsDocumentAssembly_DocumentAssembler_Append ""
method and the requirements of the used features.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IllegalArgument An invalid encryption was specified in <b>pOutOptions</b>.

 * - \ref ePdfTools_Error_IO Unable to write to the stream.

 * - \ref ePdfTools_Error_Generic A generic error occurred.


 */
PDFTOOLS_EXPORT TPdfToolsDocumentAssembly_DocumentAssembler* PDFTOOLS_CALL
PdfToolsDocumentAssembly_DocumentAssembler_New(const TPdfToolsSys_StreamDescriptor* pOutStreamDesc,
                                               TPdfToolsPdf_OutputOptions*          pOutOptions,
                                               const TPdfToolsPdf_Conformance*      pConformance);

/**
This method copies document properties and a range of pages from <b>pInDoc</b>.

* @param[in,out] pDocumentAssembler Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentAssembler.

* @param[in,out] pInDoc
* @param[in] pFirstPage Optional parameter denoting the index of the first page to be copied. This index is one-based.
If set, the number must be in the range of `1` (first page) to \ref PdfToolsPdf_Document_GetPageCount "" (last page).
If not set, `1` is used.

* @param[in] pLastPage Optional parameter denoting the index of the last page to be copied. This index is one-based.
If set, the number must be in the range of `1` (first page) to \ref PdfToolsPdf_Document_GetPageCount "" (last page).
If not set, \ref PdfToolsPdf_Document_GetPageCount "" is used.

* @param[in,out] pDocumentCopyOptions
* @param[in,out] pPageCopyOptions

 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pFirstPage</b> or <b>pLastPage</b> are not in the allowed range.

 * - \ref ePdfTools_Error_IllegalArgument If the method has already been called with any of the following properties set
to \ref "TRUE":
  - \ref PdfToolsDocumentAssembly_DocumentCopyOptions_GetCopyMetadata ""
  - \ref PdfToolsDocumentAssembly_DocumentCopyOptions_GetCopyViewerSettings ""
  - \ref PdfToolsDocumentAssembly_DocumentCopyOptions_GetCopyOutputIntent ""

 * - \ref ePdfTools_Error_Conformance The conformance level of the input document is not compatible
with the conformance level of the output document.

 * - \ref ePdfTools_Error_Conformance The explicitly requested conformance level is PDF/A Level A
(\ref ePdfToolsPdf_Conformance_PdfA1A "", \ref ePdfToolsPdf_Conformance_PdfA2A "",
or \ref ePdfToolsPdf_Conformance_PdfA3A "")
and the copy option \ref PdfToolsDocumentAssembly_PageCopyOptions_GetCopyLogicalStructure "" is set to \ref "FALSE".

 * - \ref ePdfTools_Error_IllegalState If \ref PdfToolsDocumentAssembly_DocumentAssembler_Assemble "" has already been
called.

 * - \ref ePdfTools_Error_Processing The processing has failed.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsDocumentAssembly_DocumentAssembler_Append(
    TPdfToolsDocumentAssembly_DocumentAssembler* pDocumentAssembler, TPdfToolsPdf_Document* pInDoc,
    const int* pFirstPage, const int* pLastPage, TPdfToolsDocumentAssembly_DocumentCopyOptions* pDocumentCopyOptions,
    TPdfToolsDocumentAssembly_PageCopyOptions* pPageCopyOptions);
/**
 * @brief Assemble the input documents
The input documents appended with \ref PdfToolsDocumentAssembly_DocumentAssembler_Append "" are assembled into the
output PDF.

* @param[in,out] pDocumentAssembler Acts as a handle to the native object of type \ref
TPdfToolsDocumentAssembly_DocumentAssembler.


 * @return   The assembled PDF, which can be used as a new input for further processing.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If \ref PdfToolsDocumentAssembly_DocumentAssembler_Assemble "" has already been
called.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL
PdfToolsDocumentAssembly_DocumentAssembler_Assemble(TPdfToolsDocumentAssembly_DocumentAssembler* pDocumentAssembler);

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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsDocumentAssembly_DocumentAssembler_Close(TPdfToolsDocumentAssembly_DocumentAssembler* pObject);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSDOCUMENTASSEMBLY_H__ */
