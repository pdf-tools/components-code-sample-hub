/******************************************************************************
 *
 * File:            PdfTools_PdfToolsSign.h
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

#ifndef PDFTOOLS_PDFTOOLSSIGN_H__
#define PDFTOOLS_PDFTOOLSSIGN_H__

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
#define PdfToolsSign_CustomTextVariableMap_Get      PdfToolsSign_CustomTextVariableMap_GetW
#define PdfToolsSign_CustomTextVariableMap_GetKey   PdfToolsSign_CustomTextVariableMap_GetKeyW
#define PdfToolsSign_CustomTextVariableMap_GetValue PdfToolsSign_CustomTextVariableMap_GetValueW
#define PdfToolsSign_CustomTextVariableMap_Set      PdfToolsSign_CustomTextVariableMap_SetW
#define PdfToolsSign_CustomTextVariableMap_SetValue PdfToolsSign_CustomTextVariableMap_SetValueW

#define PdfToolsSign_SignatureConfiguration_GetFieldName PdfToolsSign_SignatureConfiguration_GetFieldNameW
#define PdfToolsSign_SignatureConfiguration_SetFieldName PdfToolsSign_SignatureConfiguration_SetFieldNameW
#define PdfToolsSign_SignatureConfiguration_GetName      PdfToolsSign_SignatureConfiguration_GetNameW

#define PdfToolsSign_SignatureConfiguration_GetLocation    PdfToolsSign_SignatureConfiguration_GetLocationW
#define PdfToolsSign_SignatureConfiguration_SetLocation    PdfToolsSign_SignatureConfiguration_SetLocationW
#define PdfToolsSign_SignatureConfiguration_GetReason      PdfToolsSign_SignatureConfiguration_GetReasonW
#define PdfToolsSign_SignatureConfiguration_SetReason      PdfToolsSign_SignatureConfiguration_SetReasonW
#define PdfToolsSign_SignatureConfiguration_GetContactInfo PdfToolsSign_SignatureConfiguration_GetContactInfoW
#define PdfToolsSign_SignatureConfiguration_SetContactInfo PdfToolsSign_SignatureConfiguration_SetContactInfoW

#define PdfToolsSign_TimestampConfiguration_GetFieldName PdfToolsSign_TimestampConfiguration_GetFieldNameW
#define PdfToolsSign_TimestampConfiguration_SetFieldName PdfToolsSign_TimestampConfiguration_SetFieldNameW

#define PdfToolsSign_SignatureFieldOptions_GetFieldName PdfToolsSign_SignatureFieldOptions_GetFieldNameW
#define PdfToolsSign_SignatureFieldOptions_SetFieldName PdfToolsSign_SignatureFieldOptions_SetFieldNameW

#define TPdfToolsSign_Signer_Warning             TPdfToolsSign_Signer_WarningW
#define PdfToolsSign_Signer_AddWarningHandler    PdfToolsSign_Signer_AddWarningHandlerW
#define PdfToolsSign_Signer_RemoveWarningHandler PdfToolsSign_Signer_RemoveWarningHandlerW

#else
#define PdfToolsSign_CustomTextVariableMap_Get      PdfToolsSign_CustomTextVariableMap_GetA
#define PdfToolsSign_CustomTextVariableMap_GetKey   PdfToolsSign_CustomTextVariableMap_GetKeyA
#define PdfToolsSign_CustomTextVariableMap_GetValue PdfToolsSign_CustomTextVariableMap_GetValueA
#define PdfToolsSign_CustomTextVariableMap_Set      PdfToolsSign_CustomTextVariableMap_SetA
#define PdfToolsSign_CustomTextVariableMap_SetValue PdfToolsSign_CustomTextVariableMap_SetValueA

#define PdfToolsSign_SignatureConfiguration_GetFieldName PdfToolsSign_SignatureConfiguration_GetFieldNameA
#define PdfToolsSign_SignatureConfiguration_SetFieldName PdfToolsSign_SignatureConfiguration_SetFieldNameA
#define PdfToolsSign_SignatureConfiguration_GetName      PdfToolsSign_SignatureConfiguration_GetNameA

#define PdfToolsSign_SignatureConfiguration_GetLocation    PdfToolsSign_SignatureConfiguration_GetLocationA
#define PdfToolsSign_SignatureConfiguration_SetLocation    PdfToolsSign_SignatureConfiguration_SetLocationA
#define PdfToolsSign_SignatureConfiguration_GetReason      PdfToolsSign_SignatureConfiguration_GetReasonA
#define PdfToolsSign_SignatureConfiguration_SetReason      PdfToolsSign_SignatureConfiguration_SetReasonA
#define PdfToolsSign_SignatureConfiguration_GetContactInfo PdfToolsSign_SignatureConfiguration_GetContactInfoA
#define PdfToolsSign_SignatureConfiguration_SetContactInfo PdfToolsSign_SignatureConfiguration_SetContactInfoA

#define PdfToolsSign_TimestampConfiguration_GetFieldName PdfToolsSign_TimestampConfiguration_GetFieldNameA
#define PdfToolsSign_TimestampConfiguration_SetFieldName PdfToolsSign_TimestampConfiguration_SetFieldNameA

#define PdfToolsSign_SignatureFieldOptions_GetFieldName PdfToolsSign_SignatureFieldOptions_GetFieldNameA
#define PdfToolsSign_SignatureFieldOptions_SetFieldName PdfToolsSign_SignatureFieldOptions_SetFieldNameA

#define TPdfToolsSign_Signer_Warning             TPdfToolsSign_Signer_WarningA
#define PdfToolsSign_Signer_AddWarningHandler    PdfToolsSign_Signer_AddWarningHandlerA
#define PdfToolsSign_Signer_RemoveWarningHandler PdfToolsSign_Signer_RemoveWarningHandlerA

#endif

/**
 * @brief Event for non-critical errors occurring during signature processing
* @param[in,out] pContext Context of the event callback.

* @param[in] szMessage The message describing the warning

* @param[in] iCategory The category of the warning

* @param[in] szContext A description of the context where the warning occurred


 */
typedef void(PDFTOOLS_CALL* TPdfToolsSign_Signer_WarningA)(void* pContext, const char* szMessage,
                                                           TPdfToolsSign_WarningCategory iCategory,
                                                           const char*                   szContext);
/**
 * @brief Event for non-critical errors occurring during signature processing
* @param[in,out] pContext Context of the event callback.

* @param[in] szMessage The message describing the warning

* @param[in] iCategory The category of the warning

* @param[in] szContext A description of the context where the warning occurred


 */
typedef void(PDFTOOLS_CALL* TPdfToolsSign_Signer_WarningW)(void* pContext, const WCHAR* szMessage,
                                                           TPdfToolsSign_WarningCategory iCategory,
                                                           const WCHAR*                  szContext);

/******************************************************************************
 * CustomTextVariableMap
 *****************************************************************************/
/**
 * @brief The number of key-value pairs in the map.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsSign_CustomTextVariableMap_GetCount(TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap);
/**
 * @brief The number of key-value pairs in the map.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 * @deprecated Deprecated in Version 1.1.0.
 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsSign_CustomTextVariableMap_GetSize(TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap);
/**
 * @brief Get the position of the first entry in the map.

The order of the entries is arbitrary and not significant.

If the returned position differs from \ref PdfToolsSign_CustomTextVariableMap_GetEnd,then the position can be used to
retrieve the map entry with \ref PdfToolsSign_CustomTextVariableMap_GetKey,  \ref
PdfToolsSign_CustomTextVariableMap_GetValue.

Use \ref PdfToolsSign_CustomTextVariableMap_GetNext to get the position of the next entry.

* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsSign_CustomTextVariableMap_GetBegin(TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap);
/**
 * @brief Get the end position of the map.

This position does not correspond to an actual entry in the map.

It must be used to determine whether the end of the map has been reached when using \ref
PdfToolsSign_CustomTextVariableMap_GetBegin and \ref PdfToolsSign_CustomTextVariableMap_GetNext.

* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsSign_CustomTextVariableMap_GetEnd(TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap);
/**
 * @brief Get the position of the next entry in the map.

The order of the entries is arbitrary and not significant.

If the returned position differs from \ref PdfToolsSign_CustomTextVariableMap_GetEnd, then the position can be used to
retrieve the map entry with \ref PdfToolsSign_CustomTextVariableMap_GetKey and \ref
PdfToolsSign_CustomTextVariableMap_GetValue.

* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] it

 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsSign_CustomTextVariableMap_GetNext(TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, int it);
/**
 * @brief Get the position of a key in the map.
If no error occurred, then the position can be used to get the corresponding value with \ref
PdfToolsSign_CustomTextVariableMap_GetValue.

* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] szKey

 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_NotFound
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsSign_CustomTextVariableMap_GetA(TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, const char* szKey);
/**
 * @brief Get the position of a key in the map.
If no error occurred, then the position can be used to get the corresponding value with \ref
PdfToolsSign_CustomTextVariableMap_GetValue.

* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] szKey

 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_NotFound
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_GetW(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, const WCHAR* szKey);
/**
 * @brief Get the key of the entry given a position.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] it
* @param[out] pBuffer To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_GetKeyA(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, int it, char* pBuffer, size_t nBufferSize);
/**
 * @brief Get the key of the entry given a position.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] it
* @param[out] pBuffer To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_GetKeyW(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, int it, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Get the value of the entry given a position.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] it
* @param[out] pBuffer To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_GetValueA(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, int it, char* pBuffer, size_t nBufferSize);
/**
 * @brief Get the value of the entry given a position.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] it
* @param[out] pBuffer To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_GetValueW(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, int it, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Set the value of an entry for a given key.
This operation invalidates all positions previously returned by‹pre›_‹map›_GetBegin, \ref
PdfToolsSign_CustomTextVariableMap_GetEnd, \ref PdfToolsSign_CustomTextVariableMap_GetNext, and \ref
PdfToolsSign_CustomTextVariableMap_Get.

* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] szKey
* @param[in] szValue

 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_SetA(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, const char* szKey, const char* szValue);
/**
 * @brief Set the value of an entry for a given key.
This operation invalidates all positions previously returned by‹pre›_‹map›_GetBegin, \ref
PdfToolsSign_CustomTextVariableMap_GetEnd, \ref PdfToolsSign_CustomTextVariableMap_GetNext, and \ref
PdfToolsSign_CustomTextVariableMap_Get.

* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] szKey
* @param[in] szValue

 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_SetW(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, const WCHAR* szKey, const WCHAR* szValue);
/**
 * @brief Set the value of the entry at a position in the map.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] it
* @param[in] szValue

 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_SetValueA(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, int it, const char* szValue);
/**
 * @brief Set the value of the entry at a position in the map.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] it
* @param[in] szValue

 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_CustomTextVariableMap_SetValueW(
    TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, int it, const WCHAR* szValue);
/**
 * @brief Remove all entries from the map.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsSign_CustomTextVariableMap_Clear(TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap);
/**
 * @brief Remove the entry at a position in the map.
* @param[in,out] pCustomTextVariableMap Acts as a handle to the native object of type \ref
TPdfToolsSign_CustomTextVariableMap.

* @param[in] it

 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsSign_CustomTextVariableMap_Remove(TPdfToolsSign_CustomTextVariableMap* pCustomTextVariableMap, int it);

/******************************************************************************
 * Appearance
 *****************************************************************************/
/**
 * @brief Create an appearance with the content loaded from a JSON file
The format of the JSON file is described in the user manual.

* @param[in] pStreamDesc The JSON file defining the content


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The file is not a valid JSON file.

 * - \ref ePdfTools_Error_NotFound An image or font referenced in the JSON was not found.

 * - \ref ePdfTools_Error_Generic The JSON file is not a valid appearance content specification.

 * - \ref ePdfTools_Error_Processing Could not process content of the JSON.


 */
PDFTOOLS_EXPORT TPdfToolsSign_Appearance* PDFTOOLS_CALL
PdfToolsSign_Appearance_CreateFromJson(const TPdfToolsSys_StreamDescriptor* pStreamDesc);
/**
 * @brief Create an appearance with the content loaded from an XML file
The format of the XML file is described in the user manual.

* @param[in] pStreamDesc The XML file defining the content


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The file is not a valid XML file.

 * - \ref ePdfTools_Error_NotFound An image or font referenced in the XML was not found.

 * - \ref ePdfTools_Error_Generic The XML file is not a valid appearance content specification.

 * - \ref ePdfTools_Error_Processing Could not process content of the XML.


 */
PDFTOOLS_EXPORT TPdfToolsSign_Appearance* PDFTOOLS_CALL
PdfToolsSign_Appearance_CreateFromXml(const TPdfToolsSys_StreamDescriptor* pStreamDesc);
/**
 * @brief Create the bounding box for an unsigned signature field
Unsigned signature fields can define a rectangle on a page.
When the field is signed, the signer creates a visual appearance within that rectangle.

* @param[in] pSize The size of the rectangle


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_Appearance* PDFTOOLS_CALL
PdfToolsSign_Appearance_CreateFieldBoundingBox(const TPdfToolsGeomUnits_Size* pSize);

/**
 * @brief The number of the page where the appearance is positioned

Page number must be in the range from `1` to \ref PdfToolsPdf_Document_GetPageCount "".

If `NULL`, the appearance is positioned on the last page.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[out] pPageNumber Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_GetPageNumber(TPdfToolsSign_Appearance* pAppearance,
                                                                         int*                      pPageNumber);
/**
 * @brief The number of the page where the appearance is positioned

Page number must be in the range from `1` to \ref PdfToolsPdf_Document_GetPageCount "".

If `NULL`, the appearance is positioned on the last page.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[in] pPageNumber Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_SetPageNumber(TPdfToolsSign_Appearance* pAppearance,
                                                                         const int*                pPageNumber);
/**
 * @brief Distance to top of page

This property specifies the distance between appearance's top edge and the top of the page.

If `NULL`, the distance to the top is unspecified.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[out] pTop Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is negative


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_GetTop(TPdfToolsSign_Appearance* pAppearance, double* pTop);
/**
 * @brief Distance to top of page

This property specifies the distance between appearance's top edge and the top of the page.

If `NULL`, the distance to the top is unspecified.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[in] pTop Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is negative


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_SetTop(TPdfToolsSign_Appearance* pAppearance,
                                                                  const double*             pTop);
/**
 * @brief Distance to right of page

This property specifies the distance between appearance's right edge and the right of the page.

If `NULL`, the distance to the right is unspecified.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[out] pRight Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is negative


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_GetRight(TPdfToolsSign_Appearance* pAppearance,
                                                                    double*                   pRight);
/**
 * @brief Distance to right of page

This property specifies the distance between appearance's right edge and the right of the page.

If `NULL`, the distance to the right is unspecified.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[in] pRight Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is negative


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_SetRight(TPdfToolsSign_Appearance* pAppearance,
                                                                    const double*             pRight);
/**
 * @brief Distance to bottom of page

This property specifies the distance between appearance's bottom edge and the bottom of the page.

If `NULL`, the distance to the bottom is unspecified.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[out] pBottom Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is negative


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_GetBottom(TPdfToolsSign_Appearance* pAppearance,
                                                                     double*                   pBottom);
/**
 * @brief Distance to bottom of page

This property specifies the distance between appearance's bottom edge and the bottom of the page.

If `NULL`, the distance to the bottom is unspecified.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[in] pBottom Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is negative


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_SetBottom(TPdfToolsSign_Appearance* pAppearance,
                                                                     const double*             pBottom);
/**
 * @brief Distance to left of page

This property specifies the distance between appearance's left edge and the left of the page.

If `NULL`, the distance to the left is unspecified.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[out] pLeft Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is negative


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_GetLeft(TPdfToolsSign_Appearance* pAppearance,
                                                                   double*                   pLeft);
/**
 * @brief Distance to left of page

This property specifies the distance between appearance's left edge and the left of the page.

If `NULL`, the distance to the left is unspecified.

Default: `NULL`

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.

* @param[in] pLeft Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the given value is negative


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Appearance_SetLeft(TPdfToolsSign_Appearance* pAppearance,
                                                                   const double*             pLeft);
/**
Maps the name of a custom text variable to its value.
These variables can parametrize the content of the text element in the appearance configuration XML and Json files.
They are used by setting "[custom:‹key›]".

* @param[in,out] pAppearance Acts as a handle to the native object of type \ref TPdfToolsSign_Appearance.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_CustomTextVariableMap* PDFTOOLS_CALL
PdfToolsSign_Appearance_GetCustomTextVariables(TPdfToolsSign_Appearance* pAppearance);

/******************************************************************************
 * SignatureConfiguration
 *****************************************************************************/
/**
 * @brief The name of the existing signature field

The \ref PdfToolsPdf_SignatureField_GetFieldName "" of an existing, unsigned signature field to sign.
Note that when an existing signature field is signed, the appearance's position is defined by the existing field.
Therefore, make sure the \ref PdfToolsSign_SignatureConfiguration_GetAppearance "" fits into the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

If `NULL` a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetFieldNameA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the existing signature field

The \ref PdfToolsPdf_SignatureField_GetFieldName "" of an existing, unsigned signature field to sign.
Note that when an existing signature field is signed, the appearance's position is defined by the existing field.
Therefore, make sure the \ref PdfToolsSign_SignatureConfiguration_GetAppearance "" fits into the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

If `NULL` a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetFieldNameW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the existing signature field

The \ref PdfToolsPdf_SignatureField_GetFieldName "" of an existing, unsigned signature field to sign.
Note that when an existing signature field is signed, the appearance's position is defined by the existing field.
Therefore, make sure the \ref PdfToolsSign_SignatureConfiguration_GetAppearance "" fits into the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

If `NULL` a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in] szFieldName Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetFieldNameA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, const char* szFieldName);
/**
 * @brief The name of the existing signature field

The \ref PdfToolsPdf_SignatureField_GetFieldName "" of an existing, unsigned signature field to sign.
Note that when an existing signature field is signed, the appearance's position is defined by the existing field.
Therefore, make sure the \ref PdfToolsSign_SignatureConfiguration_GetAppearance "" fits into the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

If `NULL` a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in] szFieldName Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetFieldNameW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, const WCHAR* szFieldName);
/**
 * @brief The visual appearance of the signature

The visual appearance or `NULL` to create a signature without a visual appearance.

Default: `NULL`

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT TPdfToolsSign_Appearance* PDFTOOLS_CALL
PdfToolsSign_SignatureConfiguration_GetAppearance(TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The visual appearance of the signature

The visual appearance or `NULL` to create a signature without a visual appearance.

Default: `NULL`

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in,out] pAppearance Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetAppearance(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, TPdfToolsSign_Appearance* pAppearance);
/**
 * @brief The name of the signing certificate
* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetNameA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the signing certificate
* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetNameW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The location of signing
The CPU host name or physical location of the signing.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetLocationA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, char* pBuffer, size_t nBufferSize);
/**
 * @brief The location of signing
The CPU host name or physical location of the signing.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetLocationW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The location of signing
The CPU host name or physical location of the signing.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in] szLocation Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetLocationA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, const char* szLocation);
/**
 * @brief The location of signing
The CPU host name or physical location of the signing.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in] szLocation Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetLocationW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, const WCHAR* szLocation);
/**
 * @brief The reason for signing
* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetReasonA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, char* pBuffer, size_t nBufferSize);
/**
 * @brief The reason for signing
* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetReasonW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The reason for signing
* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in] szReason Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetReasonA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, const char* szReason);
/**
 * @brief The reason for signing
* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in] szReason Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetReasonW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, const WCHAR* szReason);
/**
 * @brief The contact information of the signer
Information provided by the signer to enable a recipient to contact
the signer to verify the signature.
For example, a phone number.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetContactInfoA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, char* pBuffer, size_t nBufferSize);
/**
 * @brief The contact information of the signer
Information provided by the signer to enable a recipient to contact
the signer to verify the signature.
For example, a phone number.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_GetContactInfoW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The contact information of the signer
Information provided by the signer to enable a recipient to contact
the signer to verify the signature.
For example, a phone number.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in] szContactInfo Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetContactInfoA(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, const char* szContactInfo);
/**
 * @brief The contact information of the signer
Information provided by the signer to enable a recipient to contact
the signer to verify the signature.
For example, a phone number.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureConfiguration.

* @param[in] szContactInfo Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureConfiguration_SetContactInfoW(
    TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration, const WCHAR* szContactInfo);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsSign_SignatureConfiguration.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pSignatureConfiguration Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsSign_SignatureConfigurationType that refers to the actual derived
 * type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsSign_SignatureConfigurationType PDFTOOLS_CALL
PdfToolsSign_SignatureConfiguration_GetType(TPdfToolsSign_SignatureConfiguration* pSignatureConfiguration);
/******************************************************************************
 * TimestampConfiguration
 *****************************************************************************/
/**
 * @brief The name of the existing signature field

The \ref PdfToolsPdf_SignatureField_GetFieldName "" of an existing, unsigned signature field to time-stamp.
Note that when an existing signature field is used, the appearance's position is defined by the existing field.
Therefore, make sure the \ref PdfToolsSign_TimestampConfiguration_GetAppearance "" fits into the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

If `NULL`, a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_TimestampConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_TimestampConfiguration_GetFieldNameA(
    TPdfToolsSign_TimestampConfiguration* pTimestampConfiguration, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the existing signature field

The \ref PdfToolsPdf_SignatureField_GetFieldName "" of an existing, unsigned signature field to time-stamp.
Note that when an existing signature field is used, the appearance's position is defined by the existing field.
Therefore, make sure the \ref PdfToolsSign_TimestampConfiguration_GetAppearance "" fits into the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

If `NULL`, a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_TimestampConfiguration.

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
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_TimestampConfiguration_GetFieldNameW(
    TPdfToolsSign_TimestampConfiguration* pTimestampConfiguration, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the existing signature field

The \ref PdfToolsPdf_SignatureField_GetFieldName "" of an existing, unsigned signature field to time-stamp.
Note that when an existing signature field is used, the appearance's position is defined by the existing field.
Therefore, make sure the \ref PdfToolsSign_TimestampConfiguration_GetAppearance "" fits into the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

If `NULL`, a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_TimestampConfiguration.

* @param[in] szFieldName Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_TimestampConfiguration_SetFieldNameA(
    TPdfToolsSign_TimestampConfiguration* pTimestampConfiguration, const char* szFieldName);
/**
 * @brief The name of the existing signature field

The \ref PdfToolsPdf_SignatureField_GetFieldName "" of an existing, unsigned signature field to time-stamp.
Note that when an existing signature field is used, the appearance's position is defined by the existing field.
Therefore, make sure the \ref PdfToolsSign_TimestampConfiguration_GetAppearance "" fits into the \ref
PdfToolsPdf_SignatureField_GetBoundingBox "".

If `NULL`, a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_TimestampConfiguration.

* @param[in] szFieldName Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_TimestampConfiguration_SetFieldNameW(
    TPdfToolsSign_TimestampConfiguration* pTimestampConfiguration, const WCHAR* szFieldName);
/**
 * @brief The visual appearance of the time-stamp

The visual appearance or `NULL` to create a time-stamp without a visual appearance.

For time-stamps, not all text variables are available,
most notably the `[signature:name]`.

Default: `NULL`

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_TimestampConfiguration.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT TPdfToolsSign_Appearance* PDFTOOLS_CALL
PdfToolsSign_TimestampConfiguration_GetAppearance(TPdfToolsSign_TimestampConfiguration* pTimestampConfiguration);
/**
 * @brief The visual appearance of the time-stamp

The visual appearance or `NULL` to create a time-stamp without a visual appearance.

For time-stamps, not all text variables are available,
most notably the `[signature:name]`.

Default: `NULL`

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsSign_TimestampConfiguration.

* @param[in,out] pAppearance Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState If the creating provider has already been closed


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_TimestampConfiguration_SetAppearance(
    TPdfToolsSign_TimestampConfiguration* pTimestampConfiguration, TPdfToolsSign_Appearance* pAppearance);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsSign_TimestampConfiguration.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pTimestampConfiguration Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsSign_TimestampConfigurationType that refers to the actual derived
 * type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsSign_TimestampConfigurationType PDFTOOLS_CALL
PdfToolsSign_TimestampConfiguration_GetType(TPdfToolsSign_TimestampConfiguration* pTimestampConfiguration);
/******************************************************************************
 * OutputOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_OutputOptions* PDFTOOLS_CALL PdfToolsSign_OutputOptions_New(void);

/**
 * @brief Whether to remove any signatures

By default, all signatures of the input document are preserved.
Optionally, some or all of them can be removed.

Default: \ref ePdfToolsSign_SignatureRemoval_None ""

* @param[in,out] pOutputOptions Acts as a handle to the native object of type \ref TPdfToolsSign_OutputOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_SignatureRemoval PDFTOOLS_CALL
PdfToolsSign_OutputOptions_GetRemoveSignatures(TPdfToolsSign_OutputOptions* pOutputOptions);
/**
 * @brief Whether to remove any signatures

By default, all signatures of the input document are preserved.
Optionally, some or all of them can be removed.

Default: \ref ePdfToolsSign_SignatureRemoval_None ""

* @param[in,out] pOutputOptions Acts as a handle to the native object of type \ref TPdfToolsSign_OutputOptions.

* @param[in] iRemoveSignatures Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_OutputOptions_SetRemoveSignatures(
    TPdfToolsSign_OutputOptions* pOutputOptions, TPdfToolsSign_SignatureRemoval iRemoveSignatures);
/**
 * @brief Add validation information to existing signatures of input document

Add signature validation information to the document security store (DSS).
This information includes:
  - All certificates of the signing certificate’s trust chain, unless they are already embedded into the signature.
  - Revocation data (OCSP or CRL) for all certificates that support revocation information.
This method can be used to create signatures with long-term validation material or to enlarge the longevity of existing
signatures. For more details on validation information, see also \ref TPdfToolsCrypto_ValidationInformation "".

Validation information for embedded time-stamp tokens is added as well.

If adding validation information fails, an \ref TPdfToolsSign_Signer_Warning "" with an
\ref ePdfToolsSign_WarningCategory_AddValidationInformationFailed "" is generated.

All types of cryptographic providers support this method.
However, this method fails when using a provider whose certificate store is missing a required certificate.

<b>Note:</b>
This property has no effect on any new signatures or time-stamp that may also be added.
The validation information of signatures and time-stamps is controlled by the respective property in the signature or
time-stamp configuration object.

<b>Note:</b>
This method does not validate the signatures, but only downloads the information required.

<b>Note:</b>
Adding validation information for expired certificates is not possible.
Therefore, it is crucial to enlarge the longevity of signatures before they expire.

<b>Note:</b>
Adding validation information to document certification (MDP) signatures is not possible,
because it would break the signature.
Validation information must be added to certification signatures when creating them.

Default: \ref ePdfToolsSign_AddValidationInformation_None ""

* @param[in,out] pOutputOptions Acts as a handle to the native object of type \ref TPdfToolsSign_OutputOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_AddValidationInformation PDFTOOLS_CALL
PdfToolsSign_OutputOptions_GetAddValidationInformation(TPdfToolsSign_OutputOptions* pOutputOptions);
/**
 * @brief Add validation information to existing signatures of input document

Add signature validation information to the document security store (DSS).
This information includes:
  - All certificates of the signing certificate’s trust chain, unless they are already embedded into the signature.
  - Revocation data (OCSP or CRL) for all certificates that support revocation information.
This method can be used to create signatures with long-term validation material or to enlarge the longevity of existing
signatures. For more details on validation information, see also \ref TPdfToolsCrypto_ValidationInformation "".

Validation information for embedded time-stamp tokens is added as well.

If adding validation information fails, an \ref TPdfToolsSign_Signer_Warning "" with an
\ref ePdfToolsSign_WarningCategory_AddValidationInformationFailed "" is generated.

All types of cryptographic providers support this method.
However, this method fails when using a provider whose certificate store is missing a required certificate.

<b>Note:</b>
This property has no effect on any new signatures or time-stamp that may also be added.
The validation information of signatures and time-stamps is controlled by the respective property in the signature or
time-stamp configuration object.

<b>Note:</b>
This method does not validate the signatures, but only downloads the information required.

<b>Note:</b>
Adding validation information for expired certificates is not possible.
Therefore, it is crucial to enlarge the longevity of signatures before they expire.

<b>Note:</b>
Adding validation information to document certification (MDP) signatures is not possible,
because it would break the signature.
Validation information must be added to certification signatures when creating them.

Default: \ref ePdfToolsSign_AddValidationInformation_None ""

* @param[in,out] pOutputOptions Acts as a handle to the native object of type \ref TPdfToolsSign_OutputOptions.

* @param[in] iAddValidationInformation Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_OutputOptions_SetAddValidationInformation(
    TPdfToolsSign_OutputOptions* pOutputOptions, TPdfToolsSign_AddValidationInformation iAddValidationInformation);

/******************************************************************************
 * MdpPermissionOptions
 *****************************************************************************/
/**
* @param[in] iPermissions

 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_MdpPermissionOptions* PDFTOOLS_CALL
PdfToolsSign_MdpPermissionOptions_New(TPdfToolsPdf_MdpPermissions iPermissions);

/**
 * @brief The access permissions granted for the document
* @param[in,out] pMdpPermissionOptions Acts as a handle to the native object of type \ref
TPdfToolsSign_MdpPermissionOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_MdpPermissions PDFTOOLS_CALL
PdfToolsSign_MdpPermissionOptions_GetPermissions(TPdfToolsSign_MdpPermissionOptions* pMdpPermissionOptions);
/**
 * @brief The access permissions granted for the document
* @param[in,out] pMdpPermissionOptions Acts as a handle to the native object of type \ref
TPdfToolsSign_MdpPermissionOptions.

* @param[in] iPermissions Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_MdpPermissionOptions_SetPermissions(
    TPdfToolsSign_MdpPermissionOptions* pMdpPermissionOptions, TPdfToolsPdf_MdpPermissions iPermissions);

/******************************************************************************
 * SignatureFieldOptions
 *****************************************************************************/
/**
* @param[in,out] pBoundingBox The bounding box of the signature field


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the <b>pBoundingBox</b> argument is `NULL` or not a valid bounding box


 */
PDFTOOLS_EXPORT TPdfToolsSign_SignatureFieldOptions* PDFTOOLS_CALL
PdfToolsSign_SignatureFieldOptions_New(TPdfToolsSign_Appearance* pBoundingBox);

/**
 * @brief The bounding box of the signature field

The bounding box is the area where the visual appearance of the signature is inserted, when the signature field is
signed.

Use \ref PdfToolsSign_Appearance_CreateFieldBoundingBox "" to create the bounding box object.

* @param[in,out] pSignatureFieldOptions Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureFieldOptions.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_Appearance* PDFTOOLS_CALL
PdfToolsSign_SignatureFieldOptions_GetBoundingBox(TPdfToolsSign_SignatureFieldOptions* pSignatureFieldOptions);
/**
 * @brief The name of the new signature field

If `NULL`, a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pSignatureFieldOptions Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureFieldOptions.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureFieldOptions_GetFieldNameA(
    TPdfToolsSign_SignatureFieldOptions* pSignatureFieldOptions, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the new signature field

If `NULL`, a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pSignatureFieldOptions Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureFieldOptions.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_SignatureFieldOptions_GetFieldNameW(
    TPdfToolsSign_SignatureFieldOptions* pSignatureFieldOptions, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the new signature field

If `NULL`, a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pSignatureFieldOptions Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureFieldOptions.

* @param[in] szFieldName Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureFieldOptions_SetFieldNameA(
    TPdfToolsSign_SignatureFieldOptions* pSignatureFieldOptions, const char* szFieldName);
/**
 * @brief The name of the new signature field

If `NULL`, a new signature field is created using a unique field name.

Default: `NULL`

* @param[in,out] pSignatureFieldOptions Acts as a handle to the native object of type \ref
TPdfToolsSign_SignatureFieldOptions.

* @param[in] szFieldName Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_SignatureFieldOptions_SetFieldNameW(
    TPdfToolsSign_SignatureFieldOptions* pSignatureFieldOptions, const WCHAR* szFieldName);

/******************************************************************************
 * PreparedDocument
 *****************************************************************************/
/**
 * @brief Calculate the hash value
Calculate the hash value to create the signature from.

* @param[in,out] pPreparedDocument Acts as a handle to the native object of type \ref TPdfToolsSign_PreparedDocument.

* @param[in] iAlgorithm The hash algorithm

* @param[out] pBuffer To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved array `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `-1` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSign_PreparedDocument_GetHash(
    TPdfToolsSign_PreparedDocument* pPreparedDocument, TPdfToolsCrypto_HashAlgorithm iAlgorithm, unsigned char* pBuffer,
    size_t nBufferSize);

/******************************************************************************
 * Signer
 *****************************************************************************/
/**
 * @brief Adds event handler.
 *
 * @param[in,out] pSigner Pointer to the object to which the event handler is added.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is added.
 *
 * @return \ref TRUE if adding event handler was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Signer_AddWarningHandlerA(TPdfToolsSign_Signer* pSigner, void* pContext,
                                                                          TPdfToolsSign_Signer_WarningA pFunction);
/**
 * @brief Adds event handler.
 *
 * @param[in,out] pSigner Pointer to the object to which the event handler is added.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is added.
 *
 * @return \ref TRUE if adding event handler was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Signer_AddWarningHandlerW(TPdfToolsSign_Signer* pSigner, void* pContext,
                                                                          TPdfToolsSign_Signer_WarningW pFunction);
/**
 * @brief Removes event handler.
 *
 * @param[in,out] pSigner Pointer to the object from which the event handler is removed.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is removed.
 *
 * @return \ref TRUE if removal was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Signer_RemoveWarningHandlerA(TPdfToolsSign_Signer*         pSigner,
                                                                             void*                         pContext,
                                                                             TPdfToolsSign_Signer_WarningA pFunction);
/**
 * @brief Removes event handler.
 *
 * @param[in,out] pSigner Pointer to the object from which the event handler is removed.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is removed.
 *
 * @return \ref TRUE if removal was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSign_Signer_RemoveWarningHandlerW(TPdfToolsSign_Signer*         pSigner,
                                                                             void*                         pContext,
                                                                             TPdfToolsSign_Signer_WarningW pFunction);

/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_Signer* PDFTOOLS_CALL PdfToolsSign_Signer_New(void);

/**
 * @brief Add a document signature

Document signatures are sometimes also called approval signatures.
This type of signature lets you verify the integrity of the signed part of the document and authenticate the signer’s
identity.

The features and format of the signature are defined by the \ref TPdfToolsCryptoProviders_Provider "" and the
<b>pConfiguration</b>.

Non-critical processing errors raise a \ref TPdfToolsSign_Signer_Warning "".
It is recommended to review the \ref TPdfToolsSign_WarningCategory "" and handle them if necessary for the application.

* @param[in,out] pSigner Acts as a handle to the native object of type \ref TPdfToolsSign_Signer.

* @param[in,out] pDocument The input document to sign

* @param[in,out] pConfiguration The signature configuration

* @param[out] pStreamDesc The stream where the signed document is written

* @param[in,out] pOutputOptions Document-level output options not directly related to the signature


 * @return   The signed document

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IO Writing to the <b>pStreamDesc</b> failed.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF contains unrendered XFA form fields.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_IllegalArgument If the <b>pConfiguration</b> is invalid, e.g. because the creating provider
has been closed.

 * - \ref ePdfTools_Error_IllegalArgument If the <b>pConfiguration</b> is invalid, e.g. because it has been revoked.

 * - \ref ePdfTools_Error_NotFound If the \ref PdfToolsSign_SignatureConfiguration_GetFieldName "" does not exist in
<b>pDocument</b>.

 * - \ref ePdfTools_Error_NotFound If an image, a PDF or a font file for the visual appearance could not be found.

 * - \ref ePdfTools_Error_Retry If an unexpected error occurs that can be resolved by retrying the operation.
For example, if a signature service returns an unexpectedly large signature.

 * - \ref ePdfTools_Error_Retry If a resource required by the cryptographic provider is temporarily unavailable.

 * - \ref ePdfTools_Error_Http If a network error occurs, e.g. downloading revocation information (OCSP, CRL) or a
time-stamp.

 * - \ref ePdfTools_Error_UnsupportedFeature If the cryptographic provider does not support the requested signing
algorithm.

 * - \ref ePdfTools_Error_Permission If the cryptographic provider does not allow the signing operation.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL
PdfToolsSign_Signer_Sign(TPdfToolsSign_Signer* pSigner, TPdfToolsPdf_Document* pDocument,
                         TPdfToolsSign_SignatureConfiguration* pConfiguration,
                         const TPdfToolsSys_StreamDescriptor* pStreamDesc, TPdfToolsSign_OutputOptions* pOutputOptions);
/**
 * @brief Add a document certification signature

This type of signature lets you detect rejected changes specified by the author.
These signatures are also called Modification Detection and Prevention (MDP) signatures.
The allowed permissions are defined by <b>pPermissions</b>.

The features and format of the signature are defined by the \ref TPdfToolsCryptoProviders_Provider "" and the
<b>pConfiguration</b>.

Non-critical processing errors raise a \ref TPdfToolsSign_Signer_Warning "".
It is recommended to review the \ref TPdfToolsSign_WarningCategory "" and handle them if necessary for the application.

* @param[in,out] pSigner Acts as a handle to the native object of type \ref TPdfToolsSign_Signer.

* @param[in,out] pDocument The input document to certify

* @param[in,out] pConfiguration The signature configuration

* @param[out] pStreamDesc The stream where the certified document is written

* @param[in,out] pPermissions The permissions allowed. The default is \ref ePdfToolsPdf_MdpPermissions_NoChanges "".

* @param[in,out] pOutputOptions Document-level output options not directly related to the document certification


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IO Writing to the <b>pStreamDesc</b> failed.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF contains unrendered XFA form fields.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_IllegalArgument If the <b>pConfiguration</b> is invalid, e.g. because the creating provider
has been closed.

 * - \ref ePdfTools_Error_NotFound If the \ref PdfToolsSign_SignatureConfiguration_GetFieldName "" does not exist in
<b>pDocument</b>.

 * - \ref ePdfTools_Error_Retry If an unexpected error occurs that can be resolved by retrying the operation.
For example, if a signature service returns an unexpectedly large signature.

 * - \ref ePdfTools_Error_Retry If a resource required by the cryptographic provider is temporarily unavailable.

 * - \ref ePdfTools_Error_Http If a network error occurs, e.g. downloading revocation information (OCSP, CRL) or a
time-stamp.

 * - \ref ePdfTools_Error_UnsupportedFeature If the cryptographic provider does not support the requested signing
algorithm.

 * - \ref ePdfTools_Error_Permission If the cryptographic provider does not allow the signing operation.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsSign_Signer_Certify(
    TPdfToolsSign_Signer* pSigner, TPdfToolsPdf_Document* pDocument,
    TPdfToolsSign_SignatureConfiguration* pConfiguration, const TPdfToolsSys_StreamDescriptor* pStreamDesc,
    TPdfToolsSign_MdpPermissionOptions* pPermissions, TPdfToolsSign_OutputOptions* pOutputOptions);
/**
 * @brief Add a document time-stamp

This type of signature provides evidence that the document existed at a specific time and protects the document’s
integrity.

The features and format of the signature are defined by the \ref TPdfToolsCryptoProviders_Provider "" and the
<b>pConfiguration</b>.

Non-critical processing errors raise a \ref TPdfToolsSign_Signer_Warning "".
It is recommended to review the \ref TPdfToolsSign_WarningCategory "" and handle them if necessary for the application.

* @param[in,out] pSigner Acts as a handle to the native object of type \ref TPdfToolsSign_Signer.

* @param[in,out] pDocument The input document to add a time-stamp to

* @param[in,out] pConfiguration The time-stamp configuration

* @param[out] pStreamDesc The stream where the output document is written

* @param[in,out] pOutputOptions Document-level output options not directly related to the document time-stamp


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IO Writing to the <b>pStreamDesc</b> failed.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF contains unrendered XFA form fields.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_IllegalArgument If the <b>pConfiguration</b> is invalid, e.g. because the creating provider
has been closed.

 * - \ref ePdfTools_Error_NotFound If the \ref PdfToolsSign_SignatureConfiguration_GetFieldName "" does not exist in
<b>pDocument</b>.

 * - \ref ePdfTools_Error_Retry If an unexpected error occurs that can be resolved by retrying the operation.
For example, if a signature service returns an unexpectedly large signature.

 * - \ref ePdfTools_Error_Retry If a resource required by the cryptographic provider is temporarily unavailable.

 * - \ref ePdfTools_Error_Http If a network error occurs, e.g. downloading revocation information (OCSP, CRL) or a
time-stamp.

 * - \ref ePdfTools_Error_UnsupportedFeature If the cryptographic provider does not support the requested signing
algorithm.

 * - \ref ePdfTools_Error_Permission If the cryptographic provider does not allow the signing operation.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsSign_Signer_AddTimestamp(
    TPdfToolsSign_Signer* pSigner, TPdfToolsPdf_Document* pDocument,
    TPdfToolsSign_TimestampConfiguration* pConfiguration, const TPdfToolsSys_StreamDescriptor* pStreamDesc,
    TPdfToolsSign_OutputOptions* pOutputOptions);
/**
 * @brief Add an unsigned signature field

Add an unsigned signature field that can later be signed (see \ref TPdfToolsPdf_UnsignedSignatureField "").

Non-critical processing errors raise a \ref TPdfToolsSign_Signer_Warning "".
It is recommended to review the \ref TPdfToolsSign_WarningCategory "" and handle them if necessary for the application.

* @param[in,out] pSigner Acts as a handle to the native object of type \ref TPdfToolsSign_Signer.

* @param[in,out] pDocument The input document to add the signature field to

* @param[in,out] pOptions The options for the unsigned signature field

* @param[out] pStreamDesc The stream where the output document is written

* @param[in,out] pOutputOptions Document-level output options not directly related to the signature field


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IO Writing to the <b>pStreamDesc</b> failed.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF contains unrendered XFA form fields.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_Exists The \ref PdfToolsSign_SignatureFieldOptions_GetFieldName "" exists already in the input
document.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsSign_Signer_AddSignatureField(
    TPdfToolsSign_Signer* pSigner, TPdfToolsPdf_Document* pDocument, TPdfToolsSign_SignatureFieldOptions* pOptions,
    const TPdfToolsSys_StreamDescriptor* pStreamDesc, TPdfToolsSign_OutputOptions* pOutputOptions);
/**
 * @brief Add a prepared signature

Adding a prepared signature is only required in very particular or specialized use cases.
This method is the same as \ref PdfToolsSign_Signer_Sign "", but without actually creating the cryptographic signature.
The cryptographic signature can be inserted later using \ref PdfToolsSign_Signer_SignPreparedSignature "".

While the <b>pConfiguration</b> can be created by any \ref TPdfToolsCryptoProviders_Provider "",
it is typically created by \ref PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignature "".

* @param[in,out] pSigner Acts as a handle to the native object of type \ref TPdfToolsSign_Signer.

* @param[in,out] pDocument The input document to add the prepared signature

* @param[in,out] pConfiguration The signature configuration

* @param[out] pStreamDesc The stream where the output document is written

* @param[in,out] pOutputOptions Document-level output options not directly related to preparing the signature


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IO Writing to the <b>pStreamDesc</b> failed.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF contains unrendered XFA form fields.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_IllegalArgument If the <b>pConfiguration</b> is invalid, e.g. because the creating provider
has been closed

 * - \ref ePdfTools_Error_NotFound If the \ref PdfToolsSign_SignatureConfiguration_GetFieldName "" does not exist in
<b>pDocument</b>.

 * - \ref ePdfTools_Error_UnsupportedFeature If the cryptographic provider does not support the requested signing
algorithm.

 * - \ref ePdfTools_Error_Http If a network error occurs, e.g. downloading revocation information (OCSP, CRL).


 */
PDFTOOLS_EXPORT TPdfToolsSign_PreparedDocument* PDFTOOLS_CALL PdfToolsSign_Signer_AddPreparedSignature(
    TPdfToolsSign_Signer* pSigner, TPdfToolsPdf_Document* pDocument,
    TPdfToolsSign_SignatureConfiguration* pConfiguration, const TPdfToolsSys_StreamDescriptor* pStreamDesc,
    TPdfToolsSign_OutputOptions* pOutputOptions);
/**
 * @brief Sign a prepared signature
Sign a document that contains a prepared signature created using \ref PdfToolsSign_Signer_AddPreparedSignature "".
Note that the <b>pConfiguration</b> must be compatible to the configuration used when preparing the signature.

* @param[in,out] pSigner Acts as a handle to the native object of type \ref TPdfToolsSign_Signer.

* @param[in,out] pDocument The input document to sign

* @param[in,out] pConfiguration The signature configuration

* @param[out] pStreamDesc The stream where the signed document is written


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IO Writing to the <b>pStreamDesc</b> failed.

 * - \ref ePdfTools_Error_IllegalArgument If the <b>pDocument</b> does not contain a prepared signature created by \ref
PdfToolsSign_Signer_AddPreparedSignature ""

 * - \ref ePdfTools_Error_IllegalArgument If the <b>pConfiguration</b> is invalid, e.g. because the creating provider
has been closed.

 * - \ref ePdfTools_Error_Retry If an unexpected error occurs that can be resolved by retrying the operation.
For example, if a signature service returns an unexpectedly large signature.

 * - \ref ePdfTools_Error_Retry If a resource required by the cryptographic provider is temporarily unavailable.

 * - \ref ePdfTools_Error_Http If a network error occurs, e.g. downloading revocation information (OCSP, CRL) or a
time-stamp.

 * - \ref ePdfTools_Error_UnsupportedFeature If the cryptographic provider does not support the requested signing
algorithm.

 * - \ref ePdfTools_Error_Permission If the cryptographic provider does not allow the signing operation.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsSign_Signer_SignPreparedSignature(
    TPdfToolsSign_Signer* pSigner, TPdfToolsPdf_Document* pDocument,
    TPdfToolsSign_SignatureConfiguration* pConfiguration, const TPdfToolsSys_StreamDescriptor* pStreamDesc);
/**
 * @brief Process a document

Apply document-level processing options without any signature operation.
For example:
  - To encrypt or decrypt PDF documents that may be signed (see the samples "Encrypt" and "Decrypt").
  - To remove signatures and unsigned signature fields (see \ref PdfToolsSign_OutputOptions_GetRemoveSignatures "").
  - To add validation information to existing signatures (see \ref
PdfToolsSign_OutputOptions_GetAddValidationInformation "").

Non-critical processing errors raise a \ref TPdfToolsSign_Signer_Warning "".
It is recommended to review the \ref TPdfToolsSign_WarningCategory "" and handle them if necessary for the application.

* @param[in,out] pSigner Acts as a handle to the native object of type \ref TPdfToolsSign_Signer.

* @param[in,out] pDocument The input document to process

* @param[out] pStreamDesc The stream where the output document is written

* @param[in,out] pOutputOptions The document-level processing options

* @param[in,out] pProvider The cryptographic provider to use to add validation information to existing signatures of
input document (see \ref PdfToolsSign_OutputOptions_GetAddValidationInformation ""). Can be `NULL` if no validation
information is added or to use the default provider.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IO Writing to the <b>pStreamDesc</b> failed.

 * - \ref ePdfTools_Error_UnsupportedFeature The input PDF contains unrendered XFA form fields.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_Http If a network error occurs, e.g. downloading revocation information (OCSP, CRL).


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsSign_Signer_Process(
    TPdfToolsSign_Signer* pSigner, TPdfToolsPdf_Document* pDocument, const TPdfToolsSys_StreamDescriptor* pStreamDesc,
    TPdfToolsSign_OutputOptions* pOutputOptions, TPdfToolsCryptoProviders_Provider* pProvider);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSSIGN_H__ */
