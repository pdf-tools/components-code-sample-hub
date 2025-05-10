/******************************************************************************
 *
 * File:            PdfTools_PdfToolsCryptoProviders.h
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

#ifndef PDFTOOLS_PDFTOOLSCRYPTOPROVIDERS_H__
#define PDFTOOLS_PDFTOOLSCRYPTOPROVIDERS_H__

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
#define PdfToolsCryptoProviders_Certificate_GetName PdfToolsCryptoProviders_Certificate_GetNameW

#define PdfToolsCryptoProviders_Certificate_GetSubject PdfToolsCryptoProviders_Certificate_GetSubjectW

#define PdfToolsCryptoProviders_Certificate_GetIssuer PdfToolsCryptoProviders_Certificate_GetIssuerW

#define PdfToolsCryptoProviders_Certificate_GetFingerprint PdfToolsCryptoProviders_Certificate_GetFingerprintW

#else
#define PdfToolsCryptoProviders_Certificate_GetName PdfToolsCryptoProviders_Certificate_GetNameA

#define PdfToolsCryptoProviders_Certificate_GetSubject PdfToolsCryptoProviders_Certificate_GetSubjectA

#define PdfToolsCryptoProviders_Certificate_GetIssuer PdfToolsCryptoProviders_Certificate_GetIssuerA

#define PdfToolsCryptoProviders_Certificate_GetFingerprint PdfToolsCryptoProviders_Certificate_GetFingerprintA

#endif

/**
 * @brief Get actual derived type of base type \ref TPdfToolsCryptoProviders_Provider.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pProvider Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsCryptoProviders_ProviderType that refers to the actual derived
 * type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsCryptoProviders_ProviderType PDFTOOLS_CALL
PdfToolsCryptoProviders_Provider_GetType(TPdfToolsCryptoProviders_Provider* pProvider);
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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProviders_Provider_Close(TPdfToolsCryptoProviders_Provider* pObject);
/******************************************************************************
 * Certificate
 *****************************************************************************/
/**
 * @brief The name (subject) of the certificate
The common name (CN) of the person or authority who owns the certificate.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProviders_Certificate_GetNameA(
    TPdfToolsCryptoProviders_Certificate* pCertificate, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name (subject) of the certificate
The common name (CN) of the person or authority who owns the certificate.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProviders_Certificate_GetNameW(
    TPdfToolsCryptoProviders_Certificate* pCertificate, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The subject of the certificate
The distinguished name (DN) of the person or authority who owns the certificate.
Formatted according to RFC 4514.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProviders_Certificate_GetSubjectA(
    TPdfToolsCryptoProviders_Certificate* pCertificate, char* pBuffer, size_t nBufferSize);
/**
 * @brief The subject of the certificate
The distinguished name (DN) of the person or authority who owns the certificate.
Formatted according to RFC 4514.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProviders_Certificate_GetSubjectW(
    TPdfToolsCryptoProviders_Certificate* pCertificate, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the certificate's issuer (CA)
The common name (CN) of the certificate authority (CA) who issued the certificate.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProviders_Certificate_GetIssuerA(
    TPdfToolsCryptoProviders_Certificate* pCertificate, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the certificate's issuer (CA)
The common name (CN) of the certificate authority (CA) who issued the certificate.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProviders_Certificate_GetIssuerW(
    TPdfToolsCryptoProviders_Certificate* pCertificate, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The certificate's fingerprint
The hex string representation of the certificate’s SHA-1 digest.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProviders_Certificate_GetFingerprintA(
    TPdfToolsCryptoProviders_Certificate* pCertificate, char* pBuffer, size_t nBufferSize);
/**
 * @brief The certificate's fingerprint
The hex string representation of the certificate’s SHA-1 digest.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProviders_Certificate_GetFingerprintW(
    TPdfToolsCryptoProviders_Certificate* pCertificate, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief Whether the cryptographic provider has a private key for the certificate.
Note that whether the private key is found and whether it can actually be used for signing may depend on the provider's
login state.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref TPdfToolsCryptoProviders_Certificate.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsCryptoProviders_Certificate_GetHasPrivateKey(TPdfToolsCryptoProviders_Certificate* pCertificate);

/******************************************************************************
 * CertificateList
 *****************************************************************************/
/**
 * @brief Get the number of elements in the list.
* @param[in,out] pCertificateList Acts as a handle to the native object of type \ref
TPdfToolsCryptoProviders_CertificateList.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsCryptoProviders_CertificateList_GetCount(TPdfToolsCryptoProviders_CertificateList* pCertificateList);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pCertificateList Acts as a handle to the native object of type \ref
TPdfToolsCryptoProviders_CertificateList.

* @param[in] iIndex

 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProviders_Certificate* PDFTOOLS_CALL
PdfToolsCryptoProviders_CertificateList_Get(TPdfToolsCryptoProviders_CertificateList* pCertificateList, int iIndex);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSCRYPTOPROVIDERS_H__ */
