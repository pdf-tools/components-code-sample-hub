/******************************************************************************
 *
 * File:            PdfTools_PdfToolsPdf.h
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

#ifndef PDFTOOLS_PDFTOOLSPDF_H__
#define PDFTOOLS_PDFTOOLSPDF_H__

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
#define PdfToolsPdf_MetadataSettings_GetTitle    PdfToolsPdf_MetadataSettings_GetTitleW
#define PdfToolsPdf_MetadataSettings_SetTitle    PdfToolsPdf_MetadataSettings_SetTitleW
#define PdfToolsPdf_MetadataSettings_GetAuthor   PdfToolsPdf_MetadataSettings_GetAuthorW
#define PdfToolsPdf_MetadataSettings_SetAuthor   PdfToolsPdf_MetadataSettings_SetAuthorW
#define PdfToolsPdf_MetadataSettings_GetSubject  PdfToolsPdf_MetadataSettings_GetSubjectW
#define PdfToolsPdf_MetadataSettings_SetSubject  PdfToolsPdf_MetadataSettings_SetSubjectW
#define PdfToolsPdf_MetadataSettings_GetKeywords PdfToolsPdf_MetadataSettings_GetKeywordsW
#define PdfToolsPdf_MetadataSettings_SetKeywords PdfToolsPdf_MetadataSettings_SetKeywordsW
#define PdfToolsPdf_MetadataSettings_GetCreator  PdfToolsPdf_MetadataSettings_GetCreatorW
#define PdfToolsPdf_MetadataSettings_SetCreator  PdfToolsPdf_MetadataSettings_SetCreatorW
#define PdfToolsPdf_MetadataSettings_GetProducer PdfToolsPdf_MetadataSettings_GetProducerW
#define PdfToolsPdf_MetadataSettings_SetProducer PdfToolsPdf_MetadataSettings_SetProducerW

#define PdfToolsPdf_Encryption_New            PdfToolsPdf_Encryption_NewW
#define PdfToolsPdf_Encryption_SetPermissions PdfToolsPdf_Encryption_SetPermissionsW

#define PdfToolsPdf_Encryption_GetUserPassword  PdfToolsPdf_Encryption_GetUserPasswordW
#define PdfToolsPdf_Encryption_SetUserPassword  PdfToolsPdf_Encryption_SetUserPasswordW
#define PdfToolsPdf_Encryption_GetOwnerPassword PdfToolsPdf_Encryption_GetOwnerPasswordW

#define PdfToolsPdf_Document_Open PdfToolsPdf_Document_OpenW

#define PdfToolsPdf_Metadata_GetTitle PdfToolsPdf_Metadata_GetTitleW

#define PdfToolsPdf_Metadata_GetAuthor PdfToolsPdf_Metadata_GetAuthorW

#define PdfToolsPdf_Metadata_GetSubject PdfToolsPdf_Metadata_GetSubjectW

#define PdfToolsPdf_Metadata_GetKeywords PdfToolsPdf_Metadata_GetKeywordsW

#define PdfToolsPdf_Metadata_GetCreator PdfToolsPdf_Metadata_GetCreatorW

#define PdfToolsPdf_Metadata_GetProducer PdfToolsPdf_Metadata_GetProducerW

#define PdfToolsPdf_SignatureField_GetFieldName PdfToolsPdf_SignatureField_GetFieldNameW

#define PdfToolsPdf_SignedSignatureField_GetName PdfToolsPdf_SignedSignatureField_GetNameW

#define PdfToolsPdf_Signature_GetLocation PdfToolsPdf_Signature_GetLocationW

#define PdfToolsPdf_Signature_GetReason PdfToolsPdf_Signature_GetReasonW

#define PdfToolsPdf_Signature_GetContactInfo PdfToolsPdf_Signature_GetContactInfoW

#else
#define PdfToolsPdf_MetadataSettings_GetTitle    PdfToolsPdf_MetadataSettings_GetTitleA
#define PdfToolsPdf_MetadataSettings_SetTitle    PdfToolsPdf_MetadataSettings_SetTitleA
#define PdfToolsPdf_MetadataSettings_GetAuthor   PdfToolsPdf_MetadataSettings_GetAuthorA
#define PdfToolsPdf_MetadataSettings_SetAuthor   PdfToolsPdf_MetadataSettings_SetAuthorA
#define PdfToolsPdf_MetadataSettings_GetSubject  PdfToolsPdf_MetadataSettings_GetSubjectA
#define PdfToolsPdf_MetadataSettings_SetSubject  PdfToolsPdf_MetadataSettings_SetSubjectA
#define PdfToolsPdf_MetadataSettings_GetKeywords PdfToolsPdf_MetadataSettings_GetKeywordsA
#define PdfToolsPdf_MetadataSettings_SetKeywords PdfToolsPdf_MetadataSettings_SetKeywordsA
#define PdfToolsPdf_MetadataSettings_GetCreator  PdfToolsPdf_MetadataSettings_GetCreatorA
#define PdfToolsPdf_MetadataSettings_SetCreator  PdfToolsPdf_MetadataSettings_SetCreatorA
#define PdfToolsPdf_MetadataSettings_GetProducer PdfToolsPdf_MetadataSettings_GetProducerA
#define PdfToolsPdf_MetadataSettings_SetProducer PdfToolsPdf_MetadataSettings_SetProducerA

#define PdfToolsPdf_Encryption_New            PdfToolsPdf_Encryption_NewA
#define PdfToolsPdf_Encryption_SetPermissions PdfToolsPdf_Encryption_SetPermissionsA

#define PdfToolsPdf_Encryption_GetUserPassword  PdfToolsPdf_Encryption_GetUserPasswordA
#define PdfToolsPdf_Encryption_SetUserPassword  PdfToolsPdf_Encryption_SetUserPasswordA
#define PdfToolsPdf_Encryption_GetOwnerPassword PdfToolsPdf_Encryption_GetOwnerPasswordA

#define PdfToolsPdf_Document_Open PdfToolsPdf_Document_OpenA

#define PdfToolsPdf_Metadata_GetTitle PdfToolsPdf_Metadata_GetTitleA

#define PdfToolsPdf_Metadata_GetAuthor PdfToolsPdf_Metadata_GetAuthorA

#define PdfToolsPdf_Metadata_GetSubject PdfToolsPdf_Metadata_GetSubjectA

#define PdfToolsPdf_Metadata_GetKeywords PdfToolsPdf_Metadata_GetKeywordsA

#define PdfToolsPdf_Metadata_GetCreator PdfToolsPdf_Metadata_GetCreatorA

#define PdfToolsPdf_Metadata_GetProducer PdfToolsPdf_Metadata_GetProducerA

#define PdfToolsPdf_SignatureField_GetFieldName PdfToolsPdf_SignatureField_GetFieldNameA

#define PdfToolsPdf_SignedSignatureField_GetName PdfToolsPdf_SignedSignatureField_GetNameA

#define PdfToolsPdf_Signature_GetLocation PdfToolsPdf_Signature_GetLocationA

#define PdfToolsPdf_Signature_GetReason PdfToolsPdf_Signature_GetReasonA

#define PdfToolsPdf_Signature_GetContactInfo PdfToolsPdf_Signature_GetContactInfoA

#endif

/******************************************************************************
 * MetadataSettings
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_MetadataSettings* PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_New(void);

/**
 * @brief The title of the document or resource.
This property corresponds to the "dc:title" entry
in the XMP metadata and to the "Title" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetTitleA(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, char* pBuffer, size_t nBufferSize);
/**
 * @brief The title of the document or resource.
This property corresponds to the "dc:title" entry
in the XMP metadata and to the "Title" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetTitleW(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The title of the document or resource.
This property corresponds to the "dc:title" entry
in the XMP metadata and to the "Title" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szTitle Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetTitleA(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const char* szTitle);
/**
 * @brief The title of the document or resource.
This property corresponds to the "dc:title" entry
in the XMP metadata and to the "Title" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szTitle Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetTitleW(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const WCHAR* szTitle);
/**
 * @brief The name of the person who created the document or resource.
This property corresponds to the "dc:creator" entry
in the XMP metadata and to the "Author" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetAuthorA(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the person who created the document or resource.
This property corresponds to the "dc:creator" entry
in the XMP metadata and to the "Author" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetAuthorW(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the person who created the document or resource.
This property corresponds to the "dc:creator" entry
in the XMP metadata and to the "Author" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szAuthor Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetAuthorA(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const char* szAuthor);
/**
 * @brief The name of the person who created the document or resource.
This property corresponds to the "dc:creator" entry
in the XMP metadata and to the "Author" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szAuthor Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetAuthorW(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const WCHAR* szAuthor);
/**
 * @brief The subject of the document or resource.
This property corresponds to the "dc:description" entry
in the XMP metadata and to the "Subject" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetSubjectA(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, char* pBuffer, size_t nBufferSize);
/**
 * @brief The subject of the document or resource.
This property corresponds to the "dc:description" entry
in the XMP metadata and to the "Subject" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetSubjectW(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The subject of the document or resource.
This property corresponds to the "dc:description" entry
in the XMP metadata and to the "Subject" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szSubject Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetSubjectA(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const char* szSubject);
/**
 * @brief The subject of the document or resource.
This property corresponds to the "dc:description" entry
in the XMP metadata and to the "Subject" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szSubject Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetSubjectW(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const WCHAR* szSubject);
/**
 * @brief Keywords associated with the document or resource.

Keywords can be separated by:
  - carriage return / line feed
  - comma
  - semicolon
  - tab
  - double space

This property corresponds to the "pdf:Keywords" entry
in the XMP metadata and to the "Keywords" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetKeywordsA(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, char* pBuffer, size_t nBufferSize);
/**
 * @brief Keywords associated with the document or resource.

Keywords can be separated by:
  - carriage return / line feed
  - comma
  - semicolon
  - tab
  - double space

This property corresponds to the "pdf:Keywords" entry
in the XMP metadata and to the "Keywords" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetKeywordsW(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Keywords associated with the document or resource.

Keywords can be separated by:
  - carriage return / line feed
  - comma
  - semicolon
  - tab
  - double space

This property corresponds to the "pdf:Keywords" entry
in the XMP metadata and to the "Keywords" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szKeywords Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetKeywordsA(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const char* szKeywords);
/**
 * @brief Keywords associated with the document or resource.

Keywords can be separated by:
  - carriage return / line feed
  - comma
  - semicolon
  - tab
  - double space

This property corresponds to the "pdf:Keywords" entry
in the XMP metadata and to the "Keywords" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szKeywords Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetKeywordsW(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const WCHAR* szKeywords);
/**
 * @brief The original application that created the document.

The name of the first known tool used to create the document or resource.

This property corresponds to the "xmp:CreatorTool" entry
in the XMP metadata and to the "Creator" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetCreatorA(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, char* pBuffer, size_t nBufferSize);
/**
 * @brief The original application that created the document.

The name of the first known tool used to create the document or resource.

This property corresponds to the "xmp:CreatorTool" entry
in the XMP metadata and to the "Creator" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetCreatorW(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The original application that created the document.

The name of the first known tool used to create the document or resource.

This property corresponds to the "xmp:CreatorTool" entry
in the XMP metadata and to the "Creator" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szCreator Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetCreatorA(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const char* szCreator);
/**
 * @brief The original application that created the document.

The name of the first known tool used to create the document or resource.

This property corresponds to the "xmp:CreatorTool" entry
in the XMP metadata and to the "Creator" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szCreator Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetCreatorW(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const WCHAR* szCreator);
/**
 * @brief The application that created the PDF

If the document has been converted to PDF from another format,
the name of the PDF processor that converted the document to PDF.

This property corresponds to the "pdf:Producer" entry
in the XMP metadata and to the "Producer" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetProducerA(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, char* pBuffer, size_t nBufferSize);
/**
 * @brief The application that created the PDF

If the document has been converted to PDF from another format,
the name of the PDF processor that converted the document to PDF.

This property corresponds to the "pdf:Producer" entry
in the XMP metadata and to the "Producer" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetProducerW(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The application that created the PDF

If the document has been converted to PDF from another format,
the name of the PDF processor that converted the document to PDF.

This property corresponds to the "pdf:Producer" entry
in the XMP metadata and to the "Producer" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szProducer Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetProducerA(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const char* szProducer);
/**
 * @brief The application that created the PDF

If the document has been converted to PDF from another format,
the name of the PDF processor that converted the document to PDF.

This property corresponds to the "pdf:Producer" entry
in the XMP metadata and to the "Producer" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] szProducer Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdf_MetadataSettings_SetProducerW(TPdfToolsPdf_MetadataSettings* pMetadataSettings, const WCHAR* szProducer);
/**
 * @brief The date and time the document or resource was originally created.
This property corresponds to the "xmp:CreateDate" entry
in the XMP metadata and to the "CreationDate" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pCreationDate Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed

 * - \ref ePdfTools_Error_IllegalArgument The date is invalid.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetCreationDate(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, TPdfToolsSys_Date* pCreationDate);
/**
 * @brief The date and time the document or resource was originally created.
This property corresponds to the "xmp:CreateDate" entry
in the XMP metadata and to the "CreationDate" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] pCreationDate Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed

 * - \ref ePdfTools_Error_IllegalArgument The date is invalid.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_SetCreationDate(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, const TPdfToolsSys_Date* pCreationDate);
/**
 * @brief The date and time the document or resource was most recently modified.
This property corresponds to the "xmp:ModifyDate" entry
in the XMP metadata and to the "ModDate" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[out] pModificationDate Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed

 * - \ref ePdfTools_Error_IllegalArgument The date is invalid.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_GetModificationDate(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, TPdfToolsSys_Date* pModificationDate);
/**
 * @brief The date and time the document or resource was most recently modified.
This property corresponds to the "xmp:ModifyDate" entry
in the XMP metadata and to the "ModDate" entry in
the document information dictionary.

* @param[in,out] pMetadataSettings Acts as a handle to the native object of type \ref TPdfToolsPdf_MetadataSettings.

* @param[in] pModificationDate Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the metadata settings have already been closed

 * - \ref ePdfTools_Error_IllegalArgument The date is invalid.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_MetadataSettings_SetModificationDate(
    TPdfToolsPdf_MetadataSettings* pMetadataSettings, const TPdfToolsSys_Date* pModificationDate);

/******************************************************************************
 * Encryption
 *****************************************************************************/
/**
* @param[in] szUserPassword Set the user password of the output document (see \ref
PdfToolsPdf_Encryption_GetUserPassword ""). If `NULL` or empty, no user password is set.

* @param[in] szOwnerPassword Set the owner password and permissions of the output document (see \ref
PdfToolsPdf_Encryption_GetOwnerPassword ""). If `NULL` or empty, no owner password is set.

* @param[in] iPermissions The permissions to be set on the PDF document.
If no owner password is set, the permissions must not be restricted, i.e. the `permissions` must be `All`.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Encryption* PDFTOOLS_CALL PdfToolsPdf_Encryption_NewA(
    const char* szUserPassword, const char* szOwnerPassword, TPdfToolsPdf_Permission iPermissions);
/**
* @param[in] szUserPassword Set the user password of the output document (see \ref
PdfToolsPdf_Encryption_GetUserPassword ""). If `NULL` or empty, no user password is set.

* @param[in] szOwnerPassword Set the owner password and permissions of the output document (see \ref
PdfToolsPdf_Encryption_GetOwnerPassword ""). If `NULL` or empty, no owner password is set.

* @param[in] iPermissions The permissions to be set on the PDF document.
If no owner password is set, the permissions must not be restricted, i.e. the `permissions` must be `All`.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Encryption* PDFTOOLS_CALL PdfToolsPdf_Encryption_NewW(
    const WCHAR* szUserPassword, const WCHAR* szOwnerPassword, TPdfToolsPdf_Permission iPermissions);

/**
 * @brief Set the owner password and access permissions.
Only the given permissions are granted when opening the document.
To the owner of the document, all permissions are granted.
For this, the document must be opened by specifying the owner password (see \ref PdfToolsPdf_Encryption_GetOwnerPassword
"").

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.

* @param[in] szOwnerPassword The owner password to be set on the PDF document (see \ref
PdfToolsPdf_Encryption_GetOwnerPassword "").

* @param[in] iPermissions The permissions to be set on the PDF document.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If restricted <b>iPermissions</b> (i.e. not `All`) are specified without
<b>szOwnerPassword</b>.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Encryption_SetPermissionsA(TPdfToolsPdf_Encryption* pEncryption,
                                                                          const char*              szOwnerPassword,
                                                                          TPdfToolsPdf_Permission  iPermissions);
/**
 * @brief Set the owner password and access permissions.
Only the given permissions are granted when opening the document.
To the owner of the document, all permissions are granted.
For this, the document must be opened by specifying the owner password (see \ref PdfToolsPdf_Encryption_GetOwnerPassword
"").

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.

* @param[in] szOwnerPassword The owner password to be set on the PDF document (see \ref
PdfToolsPdf_Encryption_GetOwnerPassword "").

* @param[in] iPermissions The permissions to be set on the PDF document.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If restricted <b>iPermissions</b> (i.e. not `All`) are specified without
<b>szOwnerPassword</b>.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Encryption_SetPermissionsW(TPdfToolsPdf_Encryption* pEncryption,
                                                                          const WCHAR*             szOwnerPassword,
                                                                          TPdfToolsPdf_Permission  iPermissions);

/**
 * @brief The user password

This password protects the document against unauthorized opening and reading.

If a PDF document is protected by a user password, it cannot be opened without a password.
The user or, if set, owner password must be provided to open and read the document.

If a document is not protected by a user password, it can be opened by without a password, even if an owner password is
set.

If the password contains characters that are not in the Windows ANSI encoding (Windows Code Page 1252),
the output document's compliance level is automatically upgraded to PDF version 1.7.
This is because older PDF versions do not support Unicode passwords.

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Encryption_GetUserPasswordA(TPdfToolsPdf_Encryption* pEncryption,
                                                                             char* pBuffer, size_t nBufferSize);
/**
 * @brief The user password

This password protects the document against unauthorized opening and reading.

If a PDF document is protected by a user password, it cannot be opened without a password.
The user or, if set, owner password must be provided to open and read the document.

If a document is not protected by a user password, it can be opened by without a password, even if an owner password is
set.

If the password contains characters that are not in the Windows ANSI encoding (Windows Code Page 1252),
the output document's compliance level is automatically upgraded to PDF version 1.7.
This is because older PDF versions do not support Unicode passwords.

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Encryption_GetUserPasswordW(TPdfToolsPdf_Encryption* pEncryption,
                                                                             WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The user password

This password protects the document against unauthorized opening and reading.

If a PDF document is protected by a user password, it cannot be opened without a password.
The user or, if set, owner password must be provided to open and read the document.

If a document is not protected by a user password, it can be opened by without a password, even if an owner password is
set.

If the password contains characters that are not in the Windows ANSI encoding (Windows Code Page 1252),
the output document's compliance level is automatically upgraded to PDF version 1.7.
This is because older PDF versions do not support Unicode passwords.

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.

* @param[in] szUserPassword Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Encryption_SetUserPasswordA(TPdfToolsPdf_Encryption* pEncryption,
                                                                           const char*              szUserPassword);
/**
 * @brief The user password

This password protects the document against unauthorized opening and reading.

If a PDF document is protected by a user password, it cannot be opened without a password.
The user or, if set, owner password must be provided to open and read the document.

If a document is not protected by a user password, it can be opened by without a password, even if an owner password is
set.

If the password contains characters that are not in the Windows ANSI encoding (Windows Code Page 1252),
the output document's compliance level is automatically upgraded to PDF version 1.7.
This is because older PDF versions do not support Unicode passwords.

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.

* @param[in] szUserPassword Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Encryption_SetUserPasswordW(TPdfToolsPdf_Encryption* pEncryption,
                                                                           const WCHAR*             szUserPassword);
/**
 * @brief The owner password

This password is sometimes also referred to as the author’s password.
This password grants full access to the document.
Not only can the document be opened and read, it also allows the document's security settings, access permissions, and
passwords to be changed.

If the password contains characters that are not in the Windows ANSI encoding (Windows Code Page 1252),
the output document's compliance level is automatically upgraded to PDF version 1.7.
This is because older PDF versions do not support Unicode passwords.

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Encryption_GetOwnerPasswordA(TPdfToolsPdf_Encryption* pEncryption,
                                                                              char* pBuffer, size_t nBufferSize);
/**
 * @brief The owner password

This password is sometimes also referred to as the author’s password.
This password grants full access to the document.
Not only can the document be opened and read, it also allows the document's security settings, access permissions, and
passwords to be changed.

If the password contains characters that are not in the Windows ANSI encoding (Windows Code Page 1252),
the output document's compliance level is automatically upgraded to PDF version 1.7.
This is because older PDF versions do not support Unicode passwords.

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Encryption_GetOwnerPasswordW(TPdfToolsPdf_Encryption* pEncryption,
                                                                              WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The access permissions granted when opening the document

The operations granted in a PDF document are controlled using permission flags.
In order to set permission flags, the PDF document must be encrypted and have an owner password.

The restricted permissions apply whenever the document is opened with a password other than the owner password.
The owner password is required to initially set or later change the permission flags.

When opening an encrypted document, the access permissions for the document can be read using \ref
PdfToolsPdf_Document_GetPermissions "". Note that the permissions might be different from the "Document Restrictions
Summary" displayed in Adobe Acrobat.

* @param[in,out] pEncryption Acts as a handle to the native object of type \ref TPdfToolsPdf_Encryption.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Permission PDFTOOLS_CALL
PdfToolsPdf_Encryption_GetPermissions(TPdfToolsPdf_Encryption* pEncryption);

/******************************************************************************
 * OutputOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_OutputOptions* PDFTOOLS_CALL PdfToolsPdf_OutputOptions_New(void);

/**
 * @brief The parameters to encrypt output PDFs

If `NULL`, no encryption is used.

Encryption is not allowed by the PDF/A ISO standards.
For that reason, it is recommended to use `NULL` when processing PDF/A documents.
Otherwise, most operations will remove PDF/A conformance from the output document.
More details can be found in the documentation of the operation.

Default: `NULL`, no encryption is used.

* @param[in,out] pOutputOptions Acts as a handle to the native object of type \ref TPdfToolsPdf_OutputOptions.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Encryption* PDFTOOLS_CALL
PdfToolsPdf_OutputOptions_GetEncryption(TPdfToolsPdf_OutputOptions* pOutputOptions);
/**
 * @brief The parameters to encrypt output PDFs

If `NULL`, no encryption is used.

Encryption is not allowed by the PDF/A ISO standards.
For that reason, it is recommended to use `NULL` when processing PDF/A documents.
Otherwise, most operations will remove PDF/A conformance from the output document.
More details can be found in the documentation of the operation.

Default: `NULL`, no encryption is used.

* @param[in,out] pOutputOptions Acts as a handle to the native object of type \ref TPdfToolsPdf_OutputOptions.

* @param[in,out] pEncryption Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_OutputOptions_SetEncryption(TPdfToolsPdf_OutputOptions* pOutputOptions,
                                                                           TPdfToolsPdf_Encryption*    pEncryption);
/**
Default: `NULL`, metadata are copied to the output document.

* @param[in,out] pOutputOptions Acts as a handle to the native object of type \ref TPdfToolsPdf_OutputOptions.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_MetadataSettings* PDFTOOLS_CALL
PdfToolsPdf_OutputOptions_GetMetadataSettings(TPdfToolsPdf_OutputOptions* pOutputOptions);
/**
Default: `NULL`, metadata are copied to the output document.

* @param[in,out] pOutputOptions Acts as a handle to the native object of type \ref TPdfToolsPdf_OutputOptions.

* @param[in,out] pMetadataSettings Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_OutputOptions_SetMetadataSettings(
    TPdfToolsPdf_OutputOptions* pOutputOptions, TPdfToolsPdf_MetadataSettings* pMetadataSettings);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsPdf_OutputOptions.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pOutputOptions Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsPdf_OutputOptionsType that refers to the actual derived type. `0`
 * in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsPdf_OutputOptionsType PDFTOOLS_CALL
PdfToolsPdf_OutputOptions_GetType(TPdfToolsPdf_OutputOptions* pOutputOptions);
/******************************************************************************
 * Document
 *****************************************************************************/
/**
 * @brief Open a PDF document.
Documents opened with this method are read-only and cannot be modified.

* @param[in] pStreamDesc The stream from which the PDF is read.

* @param[in] szPassword The password to open the PDF document.
If `NULL` or empty, no password is used.


 * @return   The newly created document instance

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_Password The document is encrypted and the `password` is invalid.

 * - \ref ePdfTools_Error_Corrupt The document is corrupt or not a PDF.

 * - \ref ePdfTools_Error_UnsupportedFeature The document is an unencrypted wrapper document.

 * - \ref ePdfTools_Error_Generic A generic error occurred.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL
PdfToolsPdf_Document_OpenA(const TPdfToolsSys_StreamDescriptor* pStreamDesc, const char* szPassword);
/**
 * @brief Open a PDF document.
Documents opened with this method are read-only and cannot be modified.

* @param[in] pStreamDesc The stream from which the PDF is read.

* @param[in] szPassword The password to open the PDF document.
If `NULL` or empty, no password is used.


 * @return   The newly created document instance

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_Password The document is encrypted and the `password` is invalid.

 * - \ref ePdfTools_Error_Corrupt The document is corrupt or not a PDF.

 * - \ref ePdfTools_Error_UnsupportedFeature The document is an unencrypted wrapper document.

 * - \ref ePdfTools_Error_Generic A generic error occurred.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL
PdfToolsPdf_Document_OpenW(const TPdfToolsSys_StreamDescriptor* pStreamDesc, const WCHAR* szPassword);

/**
 * @brief The claimed conformance of the document

This method only returns the claimed conformance level,
the document is not validated.

This property can return `NULL` if the document's conformance is unknown.

* @param[in,out] pDocument Acts as a handle to the native object of type \ref TPdfToolsPdf_Document.

* @param[out] pConformance Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Document_GetConformance(TPdfToolsPdf_Document*    pDocument,
                                                                       TPdfToolsPdf_Conformance* pConformance);
/**
 * @brief The number of pages in the document
If the document is a collection (also known as PDF Portfolio), then this property is `0`.

* @param[in,out] pDocument Acts as a handle to the native object of type \ref TPdfToolsPdf_Document.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `-1` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfToolsPdf_Document_GetPageCount(TPdfToolsPdf_Document* pDocument);
/**
 * @brief The access permissions applicable for this document

This property is `NULL`, if the document is not encrypted.

Note that these permissions might be different from the "Document Restrictions Summary" displayed in Adobe Acrobat.
This is because Acrobat's restrictions are also affected by other factors.
For example, "Document Assembly" is generally only allowed in Acrobat Pro and not the Acrobat Reader.

* @param[in,out] pDocument Acts as a handle to the native object of type \ref TPdfToolsPdf_Document.

* @param[out] pPermissions Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Document_GetPermissions(TPdfToolsPdf_Document*   pDocument,
                                                                       TPdfToolsPdf_Permission* pPermissions);
/**
 * @brief Whether the document is linearized
* @param[in,out] pDocument Acts as a handle to the native object of type \ref TPdfToolsPdf_Document.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Document_IsLinearized(TPdfToolsPdf_Document* pDocument);
/**
* @param[in,out] pDocument Acts as a handle to the native object of type \ref TPdfToolsPdf_Document.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Document_IsSigned(TPdfToolsPdf_Document* pDocument);
/**
* @param[in,out] pDocument Acts as a handle to the native object of type \ref TPdfToolsPdf_Document.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_SignatureFieldList* PDFTOOLS_CALL
PdfToolsPdf_Document_GetSignatureFields(TPdfToolsPdf_Document* pDocument);
/**
 * @brief Whether the document is an XML Forms Architecture (XFA) or a PDF document
While XFA documents may seem like regular PDF documents they are not and cannot be processed by many components (error
\ref ePdfTools_Error_UnsupportedFeature ""). An XFA form is included as a resource in a mere shell PDF. The PDF pages'
content is generated dynamically from the XFA data, which is a complex, non-standardized process. For this reason, XFA
is forbidden by the ISO Standards ISO 19'005-2 (PDF/A-2) and ISO 32'000-2 (PDF 2.0) and newer. It is recommended to
convert XFA documents to PDF using an Adobe product, e.g. by using the "Print to PDF" function of Adobe Acrobat Reader.

* @param[in,out] pDocument Acts as a handle to the native object of type \ref TPdfToolsPdf_Document.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_XfaType PDFTOOLS_CALL PdfToolsPdf_Document_GetXfa(TPdfToolsPdf_Document* pDocument);
/**
 * @brief The metadata of the document.
* @param[in,out] pDocument Acts as a handle to the native object of type \ref TPdfToolsPdf_Document.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Metadata* PDFTOOLS_CALL PdfToolsPdf_Document_GetMetadata(TPdfToolsPdf_Document* pDocument);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsPdf_Document.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pDocument Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsPdf_DocumentType that refers to the actual derived type. `0` in
 * case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsPdf_DocumentType PDFTOOLS_CALL PdfToolsPdf_Document_GetType(TPdfToolsPdf_Document* pDocument);
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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Document_Close(TPdfToolsPdf_Document* pObject);
/******************************************************************************
 * Metadata
 *****************************************************************************/
/**
 * @brief The title of the document or resource.
This property corresponds to the "dc:title" entry
in the XMP metadata and to the "Title" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetTitleA(TPdfToolsPdf_Metadata* pMetadata, char* pBuffer,
                                                                    size_t nBufferSize);
/**
 * @brief The title of the document or resource.
This property corresponds to the "dc:title" entry
in the XMP metadata and to the "Title" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetTitleW(TPdfToolsPdf_Metadata* pMetadata, WCHAR* pBuffer,
                                                                    size_t nBufferSize);
/**
 * @brief The name of the person who created the document or resource.
This property corresponds to the "dc:creator" entry
in the XMP metadata and to the "Author" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetAuthorA(TPdfToolsPdf_Metadata* pMetadata, char* pBuffer,
                                                                     size_t nBufferSize);
/**
 * @brief The name of the person who created the document or resource.
This property corresponds to the "dc:creator" entry
in the XMP metadata and to the "Author" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetAuthorW(TPdfToolsPdf_Metadata* pMetadata, WCHAR* pBuffer,
                                                                     size_t nBufferSize);
/**
 * @brief The subject of the document or resource.
This property corresponds to the "dc:description" entry
in the XMP metadata and to the "Subject" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetSubjectA(TPdfToolsPdf_Metadata* pMetadata, char* pBuffer,
                                                                      size_t nBufferSize);
/**
 * @brief The subject of the document or resource.
This property corresponds to the "dc:description" entry
in the XMP metadata and to the "Subject" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetSubjectW(TPdfToolsPdf_Metadata* pMetadata, WCHAR* pBuffer,
                                                                      size_t nBufferSize);
/**
 * @brief Keywords associated with the document or resource.

Keywords can be separated by:
  - carriage return / line feed
  - comma
  - semicolon
  - tab
  - double space

This property corresponds to the "pdf:Keywords" entry
in the XMP metadata and to the "Keywords" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetKeywordsA(TPdfToolsPdf_Metadata* pMetadata, char* pBuffer,
                                                                       size_t nBufferSize);
/**
 * @brief Keywords associated with the document or resource.

Keywords can be separated by:
  - carriage return / line feed
  - comma
  - semicolon
  - tab
  - double space

This property corresponds to the "pdf:Keywords" entry
in the XMP metadata and to the "Keywords" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetKeywordsW(TPdfToolsPdf_Metadata* pMetadata, WCHAR* pBuffer,
                                                                       size_t nBufferSize);
/**
 * @brief The original application that created the document.

The name of the first known tool used to create the document or resource.

This property corresponds to the "xmp:CreatorTool" entry
in the XMP metadata and to the "Creator" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetCreatorA(TPdfToolsPdf_Metadata* pMetadata, char* pBuffer,
                                                                      size_t nBufferSize);
/**
 * @brief The original application that created the document.

The name of the first known tool used to create the document or resource.

This property corresponds to the "xmp:CreatorTool" entry
in the XMP metadata and to the "Creator" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetCreatorW(TPdfToolsPdf_Metadata* pMetadata, WCHAR* pBuffer,
                                                                      size_t nBufferSize);
/**
 * @brief The application that created the PDF

If the document was converted to PDF from another format,
the name of the PDF processor that converted it to PDF.

This property corresponds to the "pdf:Producer" entry
in the XMP metadata and to the "Producer" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetProducerA(TPdfToolsPdf_Metadata* pMetadata, char* pBuffer,
                                                                       size_t nBufferSize);
/**
 * @brief The application that created the PDF

If the document was converted to PDF from another format,
the name of the PDF processor that converted it to PDF.

This property corresponds to the "pdf:Producer" entry
in the XMP metadata and to the "Producer" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Metadata_GetProducerW(TPdfToolsPdf_Metadata* pMetadata, WCHAR* pBuffer,
                                                                       size_t nBufferSize);
/**
 * @brief The date and time the document or resource was originally created.
This property corresponds to the "xmp:CreateDate" entry
in the XMP metadata and to the "CreationDate" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pCreationDate Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Metadata_GetCreationDate(TPdfToolsPdf_Metadata* pMetadata,
                                                                        TPdfToolsSys_Date*     pCreationDate);
/**
 * @brief The date and time the document or resource was most recently modified.
This property corresponds to the "xmp:ModifyDate" entry
in the XMP metadata and to the "ModDate" entry in
the document information dictionary.

* @param[in,out] pMetadata Acts as a handle to the native object of type \ref TPdfToolsPdf_Metadata.

* @param[out] pModificationDate Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The date is corrupt.

 * - \ref ePdfTools_Error_IllegalState if the metadata have already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Metadata_GetModificationDate(TPdfToolsPdf_Metadata* pMetadata,
                                                                            TPdfToolsSys_Date*     pModificationDate);

/******************************************************************************
 * SignatureField
 *****************************************************************************/
/**
 * @brief The name of the signature field
The field name uniquely identifies the signature field within the document.

* @param[in,out] pSignatureField Acts as a handle to the native object of type \ref TPdfToolsPdf_SignatureField.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_SignatureField_GetFieldNameA(
    TPdfToolsPdf_SignatureField* pSignatureField, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the signature field
The field name uniquely identifies the signature field within the document.

* @param[in,out] pSignatureField Acts as a handle to the native object of type \ref TPdfToolsPdf_SignatureField.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_SignatureField_GetFieldNameW(
    TPdfToolsPdf_SignatureField* pSignatureField, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The number of the page where this signature is located
Whether the signature field has a visual appearance on that page is indicated by the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

* @param[in,out] pSignatureField Acts as a handle to the native object of type \ref TPdfToolsPdf_SignatureField.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed.

 * - \ref ePdfTools_Error_NotFound If the field is not properly linked to a page.


 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsPdf_SignatureField_GetPageNumber(TPdfToolsPdf_SignatureField* pSignatureField);
/**
 * @brief The location on the page
The location of the signature field on the page.
Or `NULL` if the signature field has no visual appearance.

* @param[in,out] pSignatureField Acts as a handle to the native object of type \ref TPdfToolsPdf_SignatureField.

* @param[out] pBoundingBox Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_SignatureField_GetBoundingBox(
    TPdfToolsPdf_SignatureField* pSignatureField, TPdfToolsGeomUnits_Rectangle* pBoundingBox);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsPdf_SignatureField.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pSignatureField Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsPdf_SignatureFieldType that refers to the actual derived type. `0`
 * in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsPdf_SignatureFieldType PDFTOOLS_CALL
PdfToolsPdf_SignatureField_GetType(TPdfToolsPdf_SignatureField* pSignatureField);
/******************************************************************************
 * SignedSignatureField
 *****************************************************************************/
/**
 * @brief The name of the person or authority that signed the document

This is the name of the signing certificate.

<b>Note:</b> The name of the signing certificate can only be extracted for signatures conforming to the PAdES or PDF
standard and not for proprietary/non-standard signature formats. For non-standard signature formats, the name as stored
in the PDF is returned.

* @param[in,out] pSignedSignatureField Acts as a handle to the native object of type \ref
TPdfToolsPdf_SignedSignatureField.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_SignedSignatureField_GetNameA(
    TPdfToolsPdf_SignedSignatureField* pSignedSignatureField, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the person or authority that signed the document

This is the name of the signing certificate.

<b>Note:</b> The name of the signing certificate can only be extracted for signatures conforming to the PAdES or PDF
standard and not for proprietary/non-standard signature formats. For non-standard signature formats, the name as stored
in the PDF is returned.

* @param[in,out] pSignedSignatureField Acts as a handle to the native object of type \ref
TPdfToolsPdf_SignedSignatureField.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_SignedSignatureField_GetNameW(
    TPdfToolsPdf_SignedSignatureField* pSignedSignatureField, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The date and time of signing

This represents the date and time of signing as specified in the signature.
For signatures that contain a time-stamp, the trusted time-stamp time is returned.

<b>Note:</b> The value can only be extracted for signatures conforming to the PAdES or PDF standard
and not for proprietary/non-standard signature formats.
For non-standard signature formats, the date as stored in the PDF is returned.

* @param[in,out] pSignedSignatureField Acts as a handle to the native object of type \ref
TPdfToolsPdf_SignedSignatureField.

* @param[out] pDate Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_SignedSignatureField_GetDate(
    TPdfToolsPdf_SignedSignatureField* pSignedSignatureField, TPdfToolsSys_Date* pDate);
/**
 * @brief The document revision
The revision (version) of the document that the signature signs.

* @param[in,out] pSignedSignatureField Acts as a handle to the native object of type \ref
TPdfToolsPdf_SignedSignatureField.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed

 * - \ref ePdfTools_Error_Corrupt If the signature specifies an invalid document revision


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Revision* PDFTOOLS_CALL
PdfToolsPdf_SignedSignatureField_GetRevision(TPdfToolsPdf_SignedSignatureField* pSignedSignatureField);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsPdf_SignedSignatureField.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pSignedSignatureField Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsPdf_SignedSignatureFieldType that refers to the actual derived
 * type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsPdf_SignedSignatureFieldType PDFTOOLS_CALL
PdfToolsPdf_SignedSignatureField_GetType(TPdfToolsPdf_SignedSignatureField* pSignedSignatureField);
/******************************************************************************
 * Signature
 *****************************************************************************/
/**
 * @brief The location of signing
The CPU host name or physical location of the signing.

* @param[in,out] pSignature Acts as a handle to the native object of type \ref TPdfToolsPdf_Signature.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Signature_GetLocationA(TPdfToolsPdf_Signature* pSignature,
                                                                        char* pBuffer, size_t nBufferSize);
/**
 * @brief The location of signing
The CPU host name or physical location of the signing.

* @param[in,out] pSignature Acts as a handle to the native object of type \ref TPdfToolsPdf_Signature.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Signature_GetLocationW(TPdfToolsPdf_Signature* pSignature,
                                                                        WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The reason for signing
* @param[in,out] pSignature Acts as a handle to the native object of type \ref TPdfToolsPdf_Signature.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Signature_GetReasonA(TPdfToolsPdf_Signature* pSignature, char* pBuffer,
                                                                      size_t nBufferSize);
/**
 * @brief The reason for signing
* @param[in,out] pSignature Acts as a handle to the native object of type \ref TPdfToolsPdf_Signature.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Signature_GetReasonW(TPdfToolsPdf_Signature* pSignature,
                                                                      WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The contact information of the signer
Information provided by the signer to enable a recipient to contact
the signer to verify the signature.
For example, a phone number.

* @param[in,out] pSignature Acts as a handle to the native object of type \ref TPdfToolsPdf_Signature.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Signature_GetContactInfoA(TPdfToolsPdf_Signature* pSignature,
                                                                           char* pBuffer, size_t nBufferSize);
/**
 * @brief The contact information of the signer
Information provided by the signer to enable a recipient to contact
the signer to verify the signature.
For example, a phone number.

* @param[in,out] pSignature Acts as a handle to the native object of type \ref TPdfToolsPdf_Signature.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
  `0` if either an error occurred or the returned buffer is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `0` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsPdf_Signature_GetContactInfoW(TPdfToolsPdf_Signature* pSignature,
                                                                           WCHAR* pBuffer, size_t nBufferSize);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsPdf_Signature.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pSignature Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsPdf_SignatureType that refers to the actual derived type. `0` in
 * case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsPdf_SignatureType PDFTOOLS_CALL
PdfToolsPdf_Signature_GetType(TPdfToolsPdf_Signature* pSignature);
/******************************************************************************
 * CertificationSignature
 *****************************************************************************/
/**
 * @brief The access permissions granted for this document
Note that for encrypted PDF documents, the restrictions defined by this `CertificationSignature` are in addition
to the document's \ref PdfToolsPdf_Document_GetPermissions "".

* @param[in,out] pCertificationSignature Acts as a handle to the native object of type \ref
TPdfToolsPdf_CertificationSignature.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the object has already been closed


 */
PDFTOOLS_EXPORT TPdfToolsPdf_MdpPermissions PDFTOOLS_CALL
PdfToolsPdf_CertificationSignature_GetPermissions(TPdfToolsPdf_CertificationSignature* pCertificationSignature);

/******************************************************************************
 * SignatureFieldList
 *****************************************************************************/
/**
 * @brief Get the number of elements in the list.
* @param[in,out] pSignatureFieldList Acts as a handle to the native object of type \ref TPdfToolsPdf_SignatureFieldList.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsPdf_SignatureFieldList_GetCount(TPdfToolsPdf_SignatureFieldList* pSignatureFieldList);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pSignatureFieldList Acts as a handle to the native object of type \ref TPdfToolsPdf_SignatureFieldList.

* @param[in] iIndex

 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT TPdfToolsPdf_SignatureField* PDFTOOLS_CALL
PdfToolsPdf_SignatureFieldList_Get(TPdfToolsPdf_SignatureFieldList* pSignatureFieldList, int iIndex);

/******************************************************************************
 * Revision
 *****************************************************************************/
/**
 * @brief Write the contents of the document revision to a stream
* @param[in,out] pRevision Acts as a handle to the native object of type \ref TPdfToolsPdf_Revision.

* @param[out] pStreamDesc The stream to which the revision is written.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IO Unable to write to the stream.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Revision_Write(TPdfToolsPdf_Revision*               pRevision,
                                                              const TPdfToolsSys_StreamDescriptor* pStreamDesc);

/**
 * @brief Whether this is the latest document revision
* @param[in,out] pRevision Acts as a handle to the native object of type \ref TPdfToolsPdf_Revision.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdf_Revision_IsLatest(TPdfToolsPdf_Revision* pRevision);

/**
 * @brief Parse conformance string.
 *
 * Get conformance enumeration item of type \ref TPdfToolsPdf_Conformance from a string.
 *
 * @param[in] szConformanceString Conformance as string. Possible values:
 * "PDF 1.0", "PDF 1.1", "PDF 1.2", "PDF 1.3", "PDF 1.4", "PDF 1.5", "PDF 1.6", "PDF 1.7", "PDF 2.0",
 * "PDF/A-1b", "PDF/A-1a", "PDF/A-2b", "PDF/A-2u", "PDF/A-2a", "PDF/A-3b", "PDF/A-3u" and "PDF/A-3a"
 *
 * @return Conformance enumeration item. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_IllegalState
 */
PDFTOOLS_EXPORT TPdfToolsPdf_Conformance PDFTOOLS_CALL PdfToolsPdf_Conformance_ParseW(const WCHAR* szConformanceString);
/**
 * @brief Parse conformance string.
 *
 * Get conformance enumeration item of type \ref TPdfToolsPdf_Conformance from a string.
 *
 * @param[in] szConformanceString Conformance as string. Possible values:
 * "PDF 1.0", "PDF 1.1", "PDF 1.2", "PDF 1.3", "PDF 1.4", "PDF 1.5", "PDF 1.6", "PDF 1.7", "PDF 2.0",
 * "PDF/A-1b", "PDF/A-1a", "PDF/A-2b", "PDF/A-2u", "PDF/A-2a", "PDF/A-3b", "PDF/A-3u" and "PDF/A-3a"
 *
 * @return Conformance enumeration item. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_IllegalState
 */
PDFTOOLS_EXPORT TPdfToolsPdf_Conformance PDFTOOLS_CALL PdfToolsPdf_Conformance_ParseA(const char* szConformanceString);
/**
 * @brief Create string representation of conformance.
 *
 * Retrieve null-terminated string from a given conformance item from enumeration \ref TPdfToolsPdf_Conformance.
 *
 * @param[in] iConformance Conformance enumeration item.
 *
 * @return Null-terminated string that represents a given conformance; `NULL` in case an invalid conformance level was
 * set.
 *
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref
 * PdfTools_GetLastError. Get the error message with \ref PdfTools_GetLastErrorMessage. Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument
 */
PDFTOOLS_EXPORT const WCHAR* PDFTOOLS_CALL PdfToolsPdf_Conformance_ToStringW(TPdfToolsPdf_Conformance iConformance);
/**
 * @brief Create string representation of conformance.
 *
 * Retrieve null-terminated string from a given conformance item from enumeration \ref TPdfToolsPdf_Conformance.
 *
 * @param[in] iConformance Conformance enumeration item.
 *
 * @return Null-terminated string that represents a given conformance; `NULL` in case an invalid conformance level was
 * set.
 *
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref
 * PdfTools_GetLastError. Get the error message with \ref PdfTools_GetLastErrorMessage. Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument
 */
PDFTOOLS_EXPORT const char* PDFTOOLS_CALL PdfToolsPdf_Conformance_ToStringA(TPdfToolsPdf_Conformance iConformance);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSPDF_H__ */
