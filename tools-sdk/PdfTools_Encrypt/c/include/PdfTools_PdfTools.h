/******************************************************************************
 *
 * File:            PdfTools_PdfTools.h
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

#ifndef PDFTOOLS_PDFTOOLS_H__
#define PDFTOOLS_PDFTOOLS_H__

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
#define PdfTools_GetLastErrorMessage PdfTools_GetLastErrorMessageW
#define PdfTools_Sdk_Initialize      PdfTools_Sdk_InitializeW

#define PdfTools_Sdk_GetVersion PdfTools_Sdk_GetVersionW

#define PdfTools_Sdk_SetProducerSuffix   PdfTools_Sdk_SetProducerSuffixW
#define PdfTools_Sdk_GetProducerFullName PdfTools_Sdk_GetProducerFullNameW

#define PdfTools_Sdk_GetProxy            PdfTools_Sdk_GetProxyW
#define PdfTools_Sdk_SetProxy            PdfTools_Sdk_SetProxyW
#define PdfTools_Sdk_GetLicensingService PdfTools_Sdk_GetLicensingServiceW
#define PdfTools_Sdk_SetLicensingService PdfTools_Sdk_SetLicensingServiceW

#define PdfTools_StringList_Get PdfTools_StringList_GetW
#define PdfTools_StringList_Add PdfTools_StringList_AddW

#define PdfTools_MetadataDictionary_Get      PdfTools_MetadataDictionary_GetW
#define PdfTools_MetadataDictionary_GetKey   PdfTools_MetadataDictionary_GetKeyW
#define PdfTools_MetadataDictionary_GetValue PdfTools_MetadataDictionary_GetValueW
#define PdfTools_MetadataDictionary_Set      PdfTools_MetadataDictionary_SetW
#define PdfTools_MetadataDictionary_SetValue PdfTools_MetadataDictionary_SetValueW

#define PdfTools_HttpClientHandler_SetClientCertificate       PdfTools_HttpClientHandler_SetClientCertificateW
#define PdfTools_HttpClientHandler_SetClientCertificateAndKey PdfTools_HttpClientHandler_SetClientCertificateAndKeyW

#else
#define PdfTools_GetLastErrorMessage PdfTools_GetLastErrorMessageA
#define PdfTools_Sdk_Initialize      PdfTools_Sdk_InitializeA

#define PdfTools_Sdk_GetVersion PdfTools_Sdk_GetVersionA

#define PdfTools_Sdk_SetProducerSuffix   PdfTools_Sdk_SetProducerSuffixA
#define PdfTools_Sdk_GetProducerFullName PdfTools_Sdk_GetProducerFullNameA

#define PdfTools_Sdk_GetProxy            PdfTools_Sdk_GetProxyA
#define PdfTools_Sdk_SetProxy            PdfTools_Sdk_SetProxyA
#define PdfTools_Sdk_GetLicensingService PdfTools_Sdk_GetLicensingServiceA
#define PdfTools_Sdk_SetLicensingService PdfTools_Sdk_SetLicensingServiceA

#define PdfTools_StringList_Get PdfTools_StringList_GetA
#define PdfTools_StringList_Add PdfTools_StringList_AddA

#define PdfTools_MetadataDictionary_Get      PdfTools_MetadataDictionary_GetA
#define PdfTools_MetadataDictionary_GetKey   PdfTools_MetadataDictionary_GetKeyA
#define PdfTools_MetadataDictionary_GetValue PdfTools_MetadataDictionary_GetValueA
#define PdfTools_MetadataDictionary_Set      PdfTools_MetadataDictionary_SetA
#define PdfTools_MetadataDictionary_SetValue PdfTools_MetadataDictionary_SetValueA

#define PdfTools_HttpClientHandler_SetClientCertificate       PdfTools_HttpClientHandler_SetClientCertificateA
#define PdfTools_HttpClientHandler_SetClientCertificateAndKey PdfTools_HttpClientHandler_SetClientCertificateAndKeyA

#endif

/******************************************************************************
 * Library
 *****************************************************************************/

/**
 * @brief Initializes the library.
 *
 * The function that <b>must</b> be called before any other API function.
 * Failing to invoke this function results in undefined behavior.
 */
PDFTOOLS_EXPORT void PDFTOOLS_CALL PdfTools_Initialize();

/**
 * @brief Uninitializes the library.
 *
 * The function that <b>must</b> be called after all the other API functions.
 * Failing to invoke this function results in undefined behavior.
 */
PDFTOOLS_EXPORT void PDFTOOLS_CALL PdfTools_Uninitialize();

/**
 * @brief Retrieves the last error code.
 *
 * When a function returns a value indicating a potential error, determine the error by a specific error code.
 * An error is confirmed if the error code differs from \ref ePdfTools_Error_Success.
 * @return    The error code that last was set.
 */
PDFTOOLS_EXPORT TPdfTools_ErrorCode PDFTOOLS_CALL PdfTools_GetLastError();

/**
 * @brief Retrieves the last error message.
 *
 * Gets a detailed error message.
 *
 * @param[out] pBuffer The function has to be called twice, the first time by setting pBuffer to `NULL` to obtain the
 * actual buffer size and the second time with the allocated pBuffer and the buffer size obtained in the first call. The
 * return value of this function specifies the buffer size.
 * @param[in] nBufferSize The number of characters to be copied to `pBuffer`.
 *
 * @return   The amount of data written to the buffer `pBuffer`.
 *           `0` if there is an error.
 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_GetLastErrorMessageA(char* pBuffer, size_t nBufferSize);

/**
 * @brief Retrieve last error message.
 *
 * Gets a detailed error message.
 *
 * @param[out] pBuffer The function has to be called twice, the first time by setting pBuffer to `NULL` to obtain the
 * actual buffer size and the second time with the allocated pBuffer and the buffer size obtained in the first call. The
 * return value of this function specifies the buffer size.
 * @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.
 *
 * @return   The amount of data written to the buffer `pBuffer`.
 *           `0` if there is an error.
 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_GetLastErrorMessageW(WCHAR* pBuffer, size_t nBufferSize);

/**
 * @brief Set last error code and error message.
 *
 * Register errors by calling this function within a callback body.
 *
 * @param[in] iErrorCode Set error code.
 * @param[in] szErrorMessage Set null-terminated error message.
 */
PDFTOOLS_EXPORT void PDFTOOLS_CALL PdfTools_SetLastErrorA(TPdfTools_ErrorCode iErrorCode, const char* szErrorMessage);

/**
 * @brief Set last error code and error message.
 *
 * Register errors by calling this function within a callback body.
 *
 * @param[in] iErrorCode Set error code.
 * @param[in] szErrorMessage Set null-terminated error message.
 */
PDFTOOLS_EXPORT void PDFTOOLS_CALL PdfTools_SetLastErrorW(TPdfTools_ErrorCode iErrorCode, const WCHAR* szErrorMessage);

/******************************************************************************
 * Object
 *****************************************************************************/
/**
 * @brief Release object.
 *
 * Register errors by calling this function within a callback body.
 * Disposable objects should be properly disposed by using their respective close functions.
 *
 * @param[in] pObject Object to be released.
 */
PDFTOOLS_EXPORT void PDFTOOLS_CALL PdfTools_Release(void* pObject);

/**
 * @brief Increase reference count of object.
 *
 * Internally, the reference count is incremented by `1`.
 *
 * @param[in,out] pObject Object which reference count should be incremented by `1`.
 */
PDFTOOLS_EXPORT void PDFTOOLS_CALL PdfTools_AddRef(void* pObject);

/**
 * @brief Compare two native objects.
 *
 * Checks if two handles point to the same object.
 *
 * @param[in] pObject Pointer to one object.
 * @param[in] pOther Pointer to other object.
 *
 * @return   \ref TRUE if both pointers point to the same object; \ref FALSE otherwise.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Equals(void* pObject, void* pOther);

/**
 * @brief Get a hash code.
 *
 * Get a hash code for a given native object.
 *
 * @param[in] pObject Pointer to the object for which a hash code is calculated.
 *
 * @return   The hash code of the object.
 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfTools_GetHashCode(void* pObject);
/******************************************************************************
 * ConsumptionData
 *****************************************************************************/
/**
Denotes the number of pages left to consume before entering the over-consumption state.
When this value reaches zero, the SDK can still be used as long as \ref PdfTools_ConsumptionData_GetOverconsumption ""
is positive.

* @param[in,out] pConsumptionData Acts as a handle to the native object of type \ref TPdfTools_ConsumptionData.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfTools_ConsumptionData_GetRemainingPages(TPdfTools_ConsumptionData* pConsumptionData);
/**
Denotes the number of pages left to consume in the over-consumption state.
The over-consumption state begins after all \ref PdfTools_ConsumptionData_GetRemainingPages "" are consumed.
When this value reaches zero, a license error is thrown for every attempt to use the SDK.

* @param[in,out] pConsumptionData Acts as a handle to the native object of type \ref TPdfTools_ConsumptionData.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfTools_ConsumptionData_GetOverconsumption(TPdfTools_ConsumptionData* pConsumptionData);

/******************************************************************************
 * LicenseInfo
 *****************************************************************************/
/**
Denotes whether the license is valid.

* @param[in,out] pLicenseInfo Acts as a handle to the native object of type \ref TPdfTools_LicenseInfo.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_LicenseInfo_IsValid(TPdfTools_LicenseInfo* pLicenseInfo);
/**
The license expiration date.

* @param[in,out] pLicenseInfo Acts as a handle to the native object of type \ref TPdfTools_LicenseInfo.

* @param[out] pExpirationDate Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_LicenseInfo_GetExpirationDate(TPdfTools_LicenseInfo* pLicenseInfo,
                                                                          TPdfToolsSys_Date*     pExpirationDate);
/**
This property exists only for page-based licenses. It is `NULL` for all other licenses.

* @param[in,out] pLicenseInfo Acts as a handle to the native object of type \ref TPdfTools_LicenseInfo.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfTools_ConsumptionData* PDFTOOLS_CALL
PdfTools_LicenseInfo_GetConsumptionData(TPdfTools_LicenseInfo* pLicenseInfo);

/******************************************************************************
 * Sdk
 *****************************************************************************/
/**
 * @brief Initialize the product and the license key.
Before calling any of the other functions of the SDK, a license key must be set by calling this method.
For licensing questions, contact [pdfsales@pdftools.com](mailto:pdfsales@pdftools.com).

* @param[in] szLicense The license key.
The format of the license key is `"<PDFSDK,V1,...>"`

* @param[in] szProducerSuffix If neither `NULL` nor empty, this string is appended to the producer string
within metadata of PDF output documents (see \ref PdfTools_Sdk_GetProducerFullName "").


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_UnknownFormat The format (version) of the <b>szLicense</b> argument is unknown.

 * - \ref ePdfTools_Error_Corrupt The <b>szLicense</b> argument is not a correct license key.

 * - \ref ePdfTools_Error_License The <b>szLicense</b> argument can be read but the license check failed.

 * - \ref ePdfTools_Error_Http A network error occurred.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_InitializeA(const char* szLicense, const char* szProducerSuffix);
/**
 * @brief Initialize the product and the license key.
Before calling any of the other functions of the SDK, a license key must be set by calling this method.
For licensing questions, contact [pdfsales@pdftools.com](mailto:pdfsales@pdftools.com).

* @param[in] szLicense The license key.
The format of the license key is `"<PDFSDK,V1,...>"`

* @param[in] szProducerSuffix If neither `NULL` nor empty, this string is appended to the producer string
within metadata of PDF output documents (see \ref PdfTools_Sdk_GetProducerFullName "").


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_UnknownFormat The format (version) of the <b>szLicense</b> argument is unknown.

 * - \ref ePdfTools_Error_Corrupt The <b>szLicense</b> argument is not a correct license key.

 * - \ref ePdfTools_Error_License The <b>szLicense</b> argument can be read but the license check failed.

 * - \ref ePdfTools_Error_Http A network error occurred.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_InitializeW(const WCHAR* szLicense, const WCHAR* szProducerSuffix);

/**
 * @brief The version of the SDK
* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_Sdk_GetVersionA(char* pBuffer, size_t nBufferSize);
/**
 * @brief The version of the SDK
* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_Sdk_GetVersionW(WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The suffix for the producer
Suffix that is appended to the producer string within metadata of PDF output documents (see \ref
PdfTools_Sdk_GetProducerFullName "").

* @param[in] szProducerSuffix Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_SetProducerSuffixA(const char* szProducerSuffix);
/**
 * @brief The suffix for the producer
Suffix that is appended to the producer string within metadata of PDF output documents (see \ref
PdfTools_Sdk_GetProducerFullName "").

* @param[in] szProducerSuffix Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_SetProducerSuffixW(const WCHAR* szProducerSuffix);
/**
 * @brief The producer string that is set within the metadata of PDF output documents
The producer string depends on the license key and producer suffix set in \ref PdfTools_Sdk_Initialize "".

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_Sdk_GetProducerFullNameA(char* pBuffer, size_t nBufferSize);
/**
 * @brief The producer string that is set within the metadata of PDF output documents
The producer string depends on the license key and producer suffix set in \ref PdfTools_Sdk_Initialize "".

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_Sdk_GetProducerFullNameW(WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Proxy to use for all communication to remote servers

The SDK can use a proxy for all HTTP and HTTPS communication.

The default is `NULL`, i.e. no proxy is used.
Otherwise the property’s value must be a URI with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›]`

Where:
  - `http/https`: Protocol for connection to proxy.
  - `‹user›:‹password›` (optional): Credentials for connection to proxy (basic authorization).
  - `‹host›`: Hostname of proxy.
  - `‹port›`: Port for connection to proxy.

Example: `"http://myproxy:8080"`

For SSL/TLS connections, e.g. to a signature service, the proxy must allow the `HTTP CONNECT` request to the remote
server.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_Sdk_GetProxyA(char* pBuffer, size_t nBufferSize);
/**
 * @brief Proxy to use for all communication to remote servers

The SDK can use a proxy for all HTTP and HTTPS communication.

The default is `NULL`, i.e. no proxy is used.
Otherwise the property’s value must be a URI with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›]`

Where:
  - `http/https`: Protocol for connection to proxy.
  - `‹user›:‹password›` (optional): Credentials for connection to proxy (basic authorization).
  - `‹host›`: Hostname of proxy.
  - `‹port›`: Port for connection to proxy.

Example: `"http://myproxy:8080"`

For SSL/TLS connections, e.g. to a signature service, the proxy must allow the `HTTP CONNECT` request to the remote
server.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_Sdk_GetProxyW(WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Proxy to use for all communication to remote servers

The SDK can use a proxy for all HTTP and HTTPS communication.

The default is `NULL`, i.e. no proxy is used.
Otherwise the property’s value must be a URI with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›]`

Where:
  - `http/https`: Protocol for connection to proxy.
  - `‹user›:‹password›` (optional): Credentials for connection to proxy (basic authorization).
  - `‹host›`: Hostname of proxy.
  - `‹port›`: Port for connection to proxy.

Example: `"http://myproxy:8080"`

For SSL/TLS connections, e.g. to a signature service, the proxy must allow the `HTTP CONNECT` request to the remote
server.

* @param[in] szProxy Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_SetProxyA(const char* szProxy);
/**
 * @brief Proxy to use for all communication to remote servers

The SDK can use a proxy for all HTTP and HTTPS communication.

The default is `NULL`, i.e. no proxy is used.
Otherwise the property’s value must be a URI with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›]`

Where:
  - `http/https`: Protocol for connection to proxy.
  - `‹user›:‹password›` (optional): Credentials for connection to proxy (basic authorization).
  - `‹host›`: Hostname of proxy.
  - `‹port›`: Port for connection to proxy.

Example: `"http://myproxy:8080"`

For SSL/TLS connections, e.g. to a signature service, the proxy must allow the `HTTP CONNECT` request to the remote
server.

* @param[in] szProxy Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_SetProxyW(const WCHAR* szProxy);
/**
 * @brief The default handler for communication to remote servers
This instance is used wherever there is no dedicated HTTP client handler parameter.

 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfTools_HttpClientHandler* PDFTOOLS_CALL PdfTools_Sdk_GetHttpClientHandler(void);
/**
 * @brief Property denoting whether the usage tracking is enabled or disabled

The SDK is allowed to track usage when this property is set to \ref "TRUE".
The collected data includes only non-sensitive information, such as the features used,
the document type, the number of pages, etc.

The default is \ref "TRUE", i.e. usage tracking is enabled.

 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_GetUsageTracking(void);
/**
 * @brief Property denoting whether the usage tracking is enabled or disabled

The SDK is allowed to track usage when this property is set to \ref "TRUE".
The collected data includes only non-sensitive information, such as the features used,
the document type, the number of pages, etc.

The default is \ref "TRUE", i.e. usage tracking is enabled.

* @param[in] bUsageTracking Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_SetUsageTracking(BOOL bUsageTracking);
/**
 * @brief Licensing service to use for all licensing requests

This property is relevant only for page-based licenses and is used to set the Licensing Gateway Service.

The default is `"https://licensing.pdf-tools.com/api/v1/licenses/"` for the online Pdftools Licensing Service.
If you plan to use the Licensing Gateway Service instead of the Pdftools Licensing Service, the property’s value must be
a URI with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›]`

Where:
  - `http/https`: Protocol for connection to the Licensing Gateway Service.
  - `‹user›:‹password›` (optional): Credentials for connection to the Licensing Gateway Service (basic authorization).
  - `‹host›`: Hostname of the Licensing Gateway Service.
  - `‹port›`: Port for connection to the Licensing Gateway Service.

Example: `"http://localhost:9999"`

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The URI is invalid.


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_Sdk_GetLicensingServiceA(char* pBuffer, size_t nBufferSize);
/**
 * @brief Licensing service to use for all licensing requests

This property is relevant only for page-based licenses and is used to set the Licensing Gateway Service.

The default is `"https://licensing.pdf-tools.com/api/v1/licenses/"` for the online Pdftools Licensing Service.
If you plan to use the Licensing Gateway Service instead of the Pdftools Licensing Service, the property’s value must be
a URI with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›]`

Where:
  - `http/https`: Protocol for connection to the Licensing Gateway Service.
  - `‹user›:‹password›` (optional): Credentials for connection to the Licensing Gateway Service (basic authorization).
  - `‹host›`: Hostname of the Licensing Gateway Service.
  - `‹port›`: Port for connection to the Licensing Gateway Service.

Example: `"http://localhost:9999"`

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The URI is invalid.


 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_Sdk_GetLicensingServiceW(WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Licensing service to use for all licensing requests

This property is relevant only for page-based licenses and is used to set the Licensing Gateway Service.

The default is `"https://licensing.pdf-tools.com/api/v1/licenses/"` for the online Pdftools Licensing Service.
If you plan to use the Licensing Gateway Service instead of the Pdftools Licensing Service, the property’s value must be
a URI with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›]`

Where:
  - `http/https`: Protocol for connection to the Licensing Gateway Service.
  - `‹user›:‹password›` (optional): Credentials for connection to the Licensing Gateway Service (basic authorization).
  - `‹host›`: Hostname of the Licensing Gateway Service.
  - `‹port›`: Port for connection to the Licensing Gateway Service.

Example: `"http://localhost:9999"`

* @param[in] szLicensingService Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The URI is invalid.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_SetLicensingServiceA(const char* szLicensingService);
/**
 * @brief Licensing service to use for all licensing requests

This property is relevant only for page-based licenses and is used to set the Licensing Gateway Service.

The default is `"https://licensing.pdf-tools.com/api/v1/licenses/"` for the online Pdftools Licensing Service.
If you plan to use the Licensing Gateway Service instead of the Pdftools Licensing Service, the property’s value must be
a URI with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›]`

Where:
  - `http/https`: Protocol for connection to the Licensing Gateway Service.
  - `‹user›:‹password›` (optional): Credentials for connection to the Licensing Gateway Service (basic authorization).
  - `‹host›`: Hostname of the Licensing Gateway Service.
  - `‹port›`: Port for connection to the Licensing Gateway Service.

Example: `"http://localhost:9999"`

* @param[in] szLicensingService Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The URI is invalid.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_Sdk_SetLicensingServiceW(const WCHAR* szLicensingService);
/**

A new snapshot is created whenever this property is accessed.

Note: \ref PdfTools_Sdk_Initialize "" /><b>must</b> be called before accessing license information.
Otherwise, the license is considered invalid.

 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfTools_LicenseInfo* PDFTOOLS_CALL PdfTools_Sdk_GetLicenseInfoSnapshot(void);

/******************************************************************************
 * StringList
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfTools_StringList* PDFTOOLS_CALL PdfTools_StringList_New(void);

/**
 * @brief Get the number of elements in the list.
* @param[in,out] pStringList Acts as a handle to the native object of type \ref TPdfTools_StringList.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfTools_StringList_GetCount(TPdfTools_StringList* pStringList);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pStringList Acts as a handle to the native object of type \ref TPdfTools_StringList.

* @param[in] iIndex
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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_StringList_GetA(TPdfTools_StringList* pStringList, int iIndex,
                                                              char* pBuffer, size_t nBufferSize);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pStringList Acts as a handle to the native object of type \ref TPdfTools_StringList.

* @param[in] iIndex
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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_StringList_GetW(TPdfTools_StringList* pStringList, int iIndex,
                                                              WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Add an element to the end of the list.
* @param[in,out] pStringList Acts as a handle to the native object of type \ref TPdfTools_StringList.

* @param[in] szString

 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_StringList_AddA(TPdfTools_StringList* pStringList, const char* szString);
/**
 * @brief Add an element to the end of the list.
* @param[in,out] pStringList Acts as a handle to the native object of type \ref TPdfTools_StringList.

* @param[in] szString

 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_StringList_AddW(TPdfTools_StringList* pStringList, const WCHAR* szString);

/******************************************************************************
 * MetadataDictionary
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfTools_MetadataDictionary* PDFTOOLS_CALL PdfTools_MetadataDictionary_New(void);

/**
 * @brief The number of key-value pairs in the map.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfTools_MetadataDictionary_GetCount(TPdfTools_MetadataDictionary* pMetadataDictionary);
/**
 * @brief The number of key-value pairs in the map.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 * @deprecated Deprecated in Version 1.1.0.
 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfTools_MetadataDictionary_GetSize(TPdfTools_MetadataDictionary* pMetadataDictionary);
/**
 * @brief Get the position of the first entry in the map.

The order of the entries is arbitrary and not significant.

If the returned position differs from \ref PdfTools_MetadataDictionary_GetEnd,then the position can be used to retrieve
the map entry with \ref PdfTools_MetadataDictionary_GetKey,  \ref PdfTools_MetadataDictionary_GetValue.

Use \ref PdfTools_MetadataDictionary_GetNext to get the position of the next entry.

* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfTools_MetadataDictionary_GetBegin(TPdfTools_MetadataDictionary* pMetadataDictionary);
/**
 * @brief Get the end position of the map.

This position does not correspond to an actual entry in the map.

It must be used to determine whether the end of the map has been reached when using \ref
PdfTools_MetadataDictionary_GetBegin and \ref PdfTools_MetadataDictionary_GetNext.

* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfTools_MetadataDictionary_GetEnd(TPdfTools_MetadataDictionary* pMetadataDictionary);
/**
 * @brief Get the position of the next entry in the map.

The order of the entries is arbitrary and not significant.

If the returned position differs from \ref PdfTools_MetadataDictionary_GetEnd, then the position can be used to retrieve
the map entry with \ref PdfTools_MetadataDictionary_GetKey and \ref PdfTools_MetadataDictionary_GetValue.

* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

* @param[in] it

 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfTools_MetadataDictionary_GetNext(TPdfTools_MetadataDictionary* pMetadataDictionary,
                                                                      int                           it);
/**
 * @brief Get the position of a key in the map.
If no error occurred, then the position can be used to get the corresponding value with \ref
PdfTools_MetadataDictionary_GetValue.

* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfTools_MetadataDictionary_GetA(TPdfTools_MetadataDictionary* pMetadataDictionary,
                                                                   const char*                   szKey);
/**
 * @brief Get the position of a key in the map.
If no error occurred, then the position can be used to get the corresponding value with \ref
PdfTools_MetadataDictionary_GetValue.

* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfTools_MetadataDictionary_GetW(TPdfTools_MetadataDictionary* pMetadataDictionary,
                                                                   const WCHAR*                  szKey);
/**
 * @brief Get the key of the entry given a position.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_MetadataDictionary_GetKeyA(
    TPdfTools_MetadataDictionary* pMetadataDictionary, int it, char* pBuffer, size_t nBufferSize);
/**
 * @brief Get the key of the entry given a position.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_MetadataDictionary_GetKeyW(
    TPdfTools_MetadataDictionary* pMetadataDictionary, int it, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Get the value of the entry given a position.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_MetadataDictionary_GetValueA(
    TPdfTools_MetadataDictionary* pMetadataDictionary, int it, char* pBuffer, size_t nBufferSize);
/**
 * @brief Get the value of the entry given a position.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfTools_MetadataDictionary_GetValueW(
    TPdfTools_MetadataDictionary* pMetadataDictionary, int it, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Set the value of an entry for a given key.
This operation invalidates all positions previously returned by‹pre›_‹map›_GetBegin, \ref
PdfTools_MetadataDictionary_GetEnd, \ref PdfTools_MetadataDictionary_GetNext, and \ref PdfTools_MetadataDictionary_Get.

* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_MetadataDictionary_SetA(TPdfTools_MetadataDictionary* pMetadataDictionary,
                                                                    const char* szKey, const char* szValue);
/**
 * @brief Set the value of an entry for a given key.
This operation invalidates all positions previously returned by‹pre›_‹map›_GetBegin, \ref
PdfTools_MetadataDictionary_GetEnd, \ref PdfTools_MetadataDictionary_GetNext, and \ref PdfTools_MetadataDictionary_Get.

* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_MetadataDictionary_SetW(TPdfTools_MetadataDictionary* pMetadataDictionary,
                                                                    const WCHAR* szKey, const WCHAR* szValue);
/**
 * @brief Set the value of the entry at a position in the map.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfTools_MetadataDictionary_SetValueA(TPdfTools_MetadataDictionary* pMetadataDictionary, int it, const char* szValue);
/**
 * @brief Set the value of the entry at a position in the map.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfTools_MetadataDictionary_SetValueW(TPdfTools_MetadataDictionary* pMetadataDictionary, int it, const WCHAR* szValue);
/**
 * @brief Remove all entries from the map.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_MetadataDictionary_Clear(TPdfTools_MetadataDictionary* pMetadataDictionary);
/**
 * @brief Remove the entry at a position in the map.
* @param[in,out] pMetadataDictionary Acts as a handle to the native object of type \ref TPdfTools_MetadataDictionary.

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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_MetadataDictionary_Remove(TPdfTools_MetadataDictionary* pMetadataDictionary,
                                                                      int                           it);

/******************************************************************************
 * HttpClientHandler
 *****************************************************************************/
/**
The default values of newly created objects are not copied from the default handler \ref
PdfTools_Sdk_GetHttpClientHandler "", but are as described in this documentation.

 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfTools_HttpClientHandler* PDFTOOLS_CALL PdfTools_HttpClientHandler_New(void);

/**
 * @brief Set the SSL/TLS client certificate as PFX (PKCS#12) archive
The file must contain the certificate itself, all certificates of the trust chain, and the private key.

* @param[in,out] pHttpClientHandler Acts as a handle to the native object of type \ref TPdfTools_HttpClientHandler.

* @param[in] pArchive The SSL client certificate in PKCS#12 format (.p12, .pfx)

* @param[in] szPassword The password required to decrypt the private key of the archive


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The PFX (PKCS#12) archive is corrupt and cannot be read.

 * - \ref ePdfTools_Error_Password The password is invalid.

 * - \ref ePdfTools_Error_IllegalArgument The PFX (PKCS#12) archive is incomplete.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfTools_HttpClientHandler_SetClientCertificateA(TPdfTools_HttpClientHandler*         pHttpClientHandler,
                                                 const TPdfToolsSys_StreamDescriptor* pArchive, const char* szPassword);
/**
 * @brief Set the SSL/TLS client certificate as PFX (PKCS#12) archive
The file must contain the certificate itself, all certificates of the trust chain, and the private key.

* @param[in,out] pHttpClientHandler Acts as a handle to the native object of type \ref TPdfTools_HttpClientHandler.

* @param[in] pArchive The SSL client certificate in PKCS#12 format (.p12, .pfx)

* @param[in] szPassword The password required to decrypt the private key of the archive


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The PFX (PKCS#12) archive is corrupt and cannot be read.

 * - \ref ePdfTools_Error_Password The password is invalid.

 * - \ref ePdfTools_Error_IllegalArgument The PFX (PKCS#12) archive is incomplete.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_HttpClientHandler_SetClientCertificateW(
    TPdfTools_HttpClientHandler* pHttpClientHandler, const TPdfToolsSys_StreamDescriptor* pArchive,
    const WCHAR* szPassword);
/**
 * @brief Set the SSL/TLS client certificate and private key
The file must contain the certificate and its private key.
It is also recommended to include all certificates of the trust chain.

* @param[in,out] pHttpClientHandler Acts as a handle to the native object of type \ref TPdfTools_HttpClientHandler.

* @param[in] pCert The certificate may be in either PEM (.pem, ASCII text) or DER (.cer, binary) form.

* @param[in] pKey The encrypted private key of the certificate must be in PEM (ASCII text) form (.pem).

* @param[in] szPassword The password required to decrypt the private key.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Password The password is invalid.

 * - \ref ePdfTools_Error_Corrupt The certificate or key cannot be read.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_HttpClientHandler_SetClientCertificateAndKeyA(
    TPdfTools_HttpClientHandler* pHttpClientHandler, const TPdfToolsSys_StreamDescriptor* pCert,
    const TPdfToolsSys_StreamDescriptor* pKey, const char* szPassword);
/**
 * @brief Set the SSL/TLS client certificate and private key
The file must contain the certificate and its private key.
It is also recommended to include all certificates of the trust chain.

* @param[in,out] pHttpClientHandler Acts as a handle to the native object of type \ref TPdfTools_HttpClientHandler.

* @param[in] pCert The certificate may be in either PEM (.pem, ASCII text) or DER (.cer, binary) form.

* @param[in] pKey The encrypted private key of the certificate must be in PEM (ASCII text) form (.pem).

* @param[in] szPassword The password required to decrypt the private key.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Password The password is invalid.

 * - \ref ePdfTools_Error_Corrupt The certificate or key cannot be read.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_HttpClientHandler_SetClientCertificateAndKeyW(
    TPdfTools_HttpClientHandler* pHttpClientHandler, const TPdfToolsSys_StreamDescriptor* pCert,
    const TPdfToolsSys_StreamDescriptor* pKey, const WCHAR* szPassword);
/**
 * @brief Add a certificate to the trust store
Add a certificate to the trust store of this `HttpClientHandler` instance.
The certificates in the trust store are used to verify the certificate of the SSL/TLS server (see \ref
TPdfTools_HttpClientHandler ""). You should add trusted certification authorities (Root CA) certificates to the trust
store. However, you can also add server certificates (e.g. self-signed certificates) and intermediate CA certificates.

* @param[in,out] pHttpClientHandler Acts as a handle to the native object of type \ref TPdfTools_HttpClientHandler.

* @param[in] pCert The certificate may be in either PEM (.pem, ASCII text) or DER (.cer, binary) form.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The certificate cannot be read.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_HttpClientHandler_AddTrustedCertificate(
    TPdfTools_HttpClientHandler* pHttpClientHandler, const TPdfToolsSys_StreamDescriptor* pCert);

/**
 * @brief Verify the server certificate for SSL/TLS

If \ref "TRUE" the server certificate's trustworthiness is verified.
If the verification process fails, the handshake is immediately terminated and the connection is aborted.
The verification requires a trust store; otherwise, verification always fails.

Default: \ref "TRUE"

* @param[in,out] pHttpClientHandler Acts as a handle to the native object of type \ref TPdfTools_HttpClientHandler.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfTools_HttpClientHandler_GetSslVerifyServerCertificate(TPdfTools_HttpClientHandler* pHttpClientHandler);
/**
 * @brief Verify the server certificate for SSL/TLS

If \ref "TRUE" the server certificate's trustworthiness is verified.
If the verification process fails, the handshake is immediately terminated and the connection is aborted.
The verification requires a trust store; otherwise, verification always fails.

Default: \ref "TRUE"

* @param[in,out] pHttpClientHandler Acts as a handle to the native object of type \ref TPdfTools_HttpClientHandler.

* @param[in] bSslVerifyServerCertificate Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfTools_HttpClientHandler_SetSslVerifyServerCertificate(
    TPdfTools_HttpClientHandler* pHttpClientHandler, BOOL bSslVerifyServerCertificate);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLS_H__ */
