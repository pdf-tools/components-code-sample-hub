/******************************************************************************
 *
 * File:            PdfTools_PdfToolsCryptoProvidersGlobalSignDss.h
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

#ifndef PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSGLOBALSIGNDSS_H__
#define PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSGLOBALSIGNDSS_H__

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
#define PdfToolsCryptoProvidersGlobalSignDss_Session_New PdfToolsCryptoProvidersGlobalSignDss_Session_NewW
#define PdfToolsCryptoProvidersGlobalSignDss_Session_CreateSignatureForDynamicIdentity \
    PdfToolsCryptoProvidersGlobalSignDss_Session_CreateSignatureForDynamicIdentityW

#else
#define PdfToolsCryptoProvidersGlobalSignDss_Session_New PdfToolsCryptoProvidersGlobalSignDss_Session_NewA
#define PdfToolsCryptoProvidersGlobalSignDss_Session_CreateSignatureForDynamicIdentity \
    PdfToolsCryptoProvidersGlobalSignDss_Session_CreateSignatureForDynamicIdentityA

#endif

/******************************************************************************
 * SignatureConfiguration
 *****************************************************************************/
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Value: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 "".

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration_GetHashAlgorithm(
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The padding type of the cryptographic signature
Value: \ref ePdfToolsCrypto_SignaturePaddingType_RsaRsa ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_SignaturePaddingType PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration_GetSignaturePaddingType(
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The format (encoding) of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignatureFormat_EtsiCadesDetached ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_SignatureFormat PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration_GetSignatureFormat(
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The format (encoding) of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignatureFormat_EtsiCadesDetached ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration.

* @param[in] iSignatureFormat Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration_SetSignatureFormat(
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_SignatureFormat                               iSignatureFormat);
/**
 * @brief Whether to add a trusted time-stamp to the signature
Default: \ref "FALSE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration_GetAddTimestamp(
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief Whether to add a trusted time-stamp to the signature
Default: \ref "FALSE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration.

* @param[in] bAddTimestamp Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration_SetAddTimestamp(
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* pSignatureConfiguration, BOOL bAddTimestamp);
/**
 * @brief Whether to add validation information (LTV)

<b>Note:</b> This has no effect for signing certificates that do not offer revocation information.

Default: \ref ePdfToolsCrypto_ValidationInformation_EmbedInDocument ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_ValidationInformation PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration_GetValidationInformation(
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief Whether to add validation information (LTV)

<b>Note:</b> This has no effect for signing certificates that do not offer revocation information.

Default: \ref ePdfToolsCrypto_ValidationInformation_EmbedInDocument ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration.

* @param[in] iValidationInformation Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration_SetValidationInformation(
    TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_ValidationInformation                         iValidationInformation);

/******************************************************************************
 * TimestampConfiguration
 *****************************************************************************/
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the time-stamp is created.

Value: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 "".

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_TimestampConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_TimestampConfiguration_GetHashAlgorithm(
    TPdfToolsCryptoProvidersGlobalSignDss_TimestampConfiguration* pTimestampConfiguration);

/******************************************************************************
 * Session
 *****************************************************************************/
/**
 * @brief Establish a session to the service
* @param[in] szUrl The URL to the service endpoint.
Typically: `https://emea.api.dss.globalsign.com:8443`

* @param[in] szApi_key Your account credentials’ key parameter for the login request.

* @param[in] szApi_secret Your account credentials’ secret parameter for the login request.

* @param[in,out] pHttpClientHandler The SSL configuration with the client certificate and trust store.
Use \ref PdfTools_HttpClientHandler_SetClientCertificateAndKey "" to set your SSL client certificate "clientcert.crt"
and private key "privateKey.key" of your GlobalSign account.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Http If a network error occurs.

 * - \ref ePdfTools_Error_Permission If a login error occurs, e.g. because the client certificate is rejected or the
credentials are incorrect.

 * - \ref ePdfTools_Error_Retry If the login rate limit is exceeded.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersGlobalSignDss_Session* PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_Session_NewA(const char* szUrl, const char* szApi_key, const char* szApi_secret,
                                                  TPdfTools_HttpClientHandler* pHttpClientHandler);
/**
 * @brief Establish a session to the service
* @param[in] szUrl The URL to the service endpoint.
Typically: `https://emea.api.dss.globalsign.com:8443`

* @param[in] szApi_key Your account credentials’ key parameter for the login request.

* @param[in] szApi_secret Your account credentials’ secret parameter for the login request.

* @param[in,out] pHttpClientHandler The SSL configuration with the client certificate and trust store.
Use \ref PdfTools_HttpClientHandler_SetClientCertificateAndKey "" to set your SSL client certificate "clientcert.crt"
and private key "privateKey.key" of your GlobalSign account.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Http If a network error occurs.

 * - \ref ePdfTools_Error_Permission If a login error occurs, e.g. because the client certificate is rejected or the
credentials are incorrect.

 * - \ref ePdfTools_Error_Retry If the login rate limit is exceeded.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersGlobalSignDss_Session* PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_Session_NewW(const WCHAR* szUrl, const WCHAR* szApi_key, const WCHAR* szApi_secret,
                                                  TPdfTools_HttpClientHandler* pHttpClientHandler);

/**
 * @brief Create a signing certificate for an account with a static identity
The returned signature configuration can be used for multiple signature operations.

* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_Session.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Http If a network error occurs.

 * - \ref ePdfTools_Error_Permission If the request is not authorized by the service.

 * - \ref ePdfTools_Error_Retry If the rate limit for creating new identities has been exceeded.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_Session_CreateSignatureForStaticIdentity(
    TPdfToolsCryptoProvidersGlobalSignDss_Session* pSession);
/**
 * @brief Create a signing certificate for an account with a dynamic identity.
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_Session.

* @param[in] szIdentity The dynamic identity as JSON string.
Example:
`{ "subject_dn": {"common_name": "John Doe" } }`


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Http If a network error occurs.

 * - \ref ePdfTools_Error_Permission If the request is not authorized by the service.

 * - \ref ePdfTools_Error_Retry If the rate limit for creating new identities has been exceeded.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_Session_CreateSignatureForDynamicIdentityA(
    TPdfToolsCryptoProvidersGlobalSignDss_Session* pSession, const char* szIdentity);
/**
 * @brief Create a signing certificate for an account with a dynamic identity.
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_Session.

* @param[in] szIdentity The dynamic identity as JSON string.
Example:
`{ "subject_dn": {"common_name": "John Doe" } }`


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Http If a network error occurs.

 * - \ref ePdfTools_Error_Permission If the request is not authorized by the service.

 * - \ref ePdfTools_Error_Retry If the rate limit for creating new identities has been exceeded.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersGlobalSignDss_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_Session_CreateSignatureForDynamicIdentityW(
    TPdfToolsCryptoProvidersGlobalSignDss_Session* pSession, const WCHAR* szIdentity);
/**
 * @brief Create a time-stamp configuration
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersGlobalSignDss_Session.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersGlobalSignDss_TimestampConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersGlobalSignDss_Session_CreateTimestamp(TPdfToolsCryptoProvidersGlobalSignDss_Session* pSession);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSGLOBALSIGNDSS_H__ */
