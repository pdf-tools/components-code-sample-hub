/******************************************************************************
 *
 * File:            PdfTools_PdfToolsCryptoProvidersBuiltIn.h
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

#ifndef PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSBUILTIN_H__
#define PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSBUILTIN_H__

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
#define PdfToolsCryptoProvidersBuiltIn_Provider_CreateSignatureFromCertificate \
    PdfToolsCryptoProvidersBuiltIn_Provider_CreateSignatureFromCertificateW
#define PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignature \
    PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignatureW

#define PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrl PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrlW
#define PdfToolsCryptoProvidersBuiltIn_Provider_SetTimestampUrl PdfToolsCryptoProvidersBuiltIn_Provider_SetTimestampUrlW

#else
#define PdfToolsCryptoProvidersBuiltIn_Provider_CreateSignatureFromCertificate \
    PdfToolsCryptoProvidersBuiltIn_Provider_CreateSignatureFromCertificateA
#define PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignature \
    PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignatureA

#define PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrl PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrlA
#define PdfToolsCryptoProvidersBuiltIn_Provider_SetTimestampUrl PdfToolsCryptoProvidersBuiltIn_Provider_SetTimestampUrlA

#endif

/******************************************************************************
 * SignatureConfiguration
 *****************************************************************************/
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_GetHashAlgorithm(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.

* @param[in] iHashAlgorithm Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_SetHashAlgorithm(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_HashAlgorithm                           iHashAlgorithm);
/**
 * @brief The padding type of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignaturePaddingType_RsaSsaPss "" for RSA and for \ref
ePdfToolsCrypto_SignaturePaddingType_Default "" ECDSA certificates.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_SignaturePaddingType PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_GetSignaturePaddingType(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The padding type of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignaturePaddingType_RsaSsaPss "" for RSA and for \ref
ePdfToolsCrypto_SignaturePaddingType_Default "" ECDSA certificates.

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.

* @param[in] iSignaturePaddingType Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_SetSignaturePaddingType(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_SignaturePaddingType                    iSignaturePaddingType);
/**
 * @brief The format (encoding) of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignatureFormat_EtsiCadesDetached ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_SignatureFormat PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_GetSignatureFormat(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The format (encoding) of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignatureFormat_EtsiCadesDetached ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.

* @param[in] iSignatureFormat Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_SetSignatureFormat(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_SignatureFormat                         iSignatureFormat);
/**
 * @brief Whether to add a trusted time-stamp to the signature

If \ref "TRUE" the \ref PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrl "" must be set.

Default: \ref "FALSE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_GetAddTimestamp(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief Whether to add a trusted time-stamp to the signature

If \ref "TRUE" the \ref PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrl "" must be set.

Default: \ref "FALSE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.

* @param[in] bAddTimestamp Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_SetAddTimestamp(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration, BOOL bAddTimestamp);
/**
 * @brief Whether to add validation information (LTV)

For signing certificates that do not offer validation (revocation) information (OCSP or CRL),
this property is ignored.

If downloading validation information fails, an error \ref ePdfTools_Error_NotFound "" or \ref ePdfTools_Error_Http ""
is generated. See \ref ePdfToolsSign_WarningCategory_AddValidationInformationFailed "" for a description of possible
error causes and solutions.

Default: \ref ePdfToolsCrypto_ValidationInformation_EmbedInDocument "" if the signing certificate offers validation
information and \ref ePdfToolsCrypto_ValidationInformation_None "" otherwise

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_ValidationInformation PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_GetValidationInformation(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief Whether to add validation information (LTV)

For signing certificates that do not offer validation (revocation) information (OCSP or CRL),
this property is ignored.

If downloading validation information fails, an error \ref ePdfTools_Error_NotFound "" or \ref ePdfTools_Error_Http ""
is generated. See \ref ePdfToolsSign_WarningCategory_AddValidationInformationFailed "" for a description of possible
error causes and solutions.

Default: \ref ePdfToolsCrypto_ValidationInformation_EmbedInDocument "" if the signing certificate offers validation
information and \ref ePdfToolsCrypto_ValidationInformation_None "" otherwise

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration.

* @param[in] iValidationInformation Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_SignatureConfiguration_SetValidationInformation(
    TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_ValidationInformation                   iValidationInformation);

/******************************************************************************
 * TimestampConfiguration
 *****************************************************************************/
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the time-stamp signature is created.

<b>Note:</b> This algorithm must be supported by the time-stamp server; many support only SHA-256.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_TimestampConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_TimestampConfiguration_GetHashAlgorithm(
    TPdfToolsCryptoProvidersBuiltIn_TimestampConfiguration* pTimestampConfiguration);
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the time-stamp signature is created.

<b>Note:</b> This algorithm must be supported by the time-stamp server; many support only SHA-256.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersBuiltIn_TimestampConfiguration.

* @param[in] iHashAlgorithm Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_TimestampConfiguration_SetHashAlgorithm(
    TPdfToolsCryptoProvidersBuiltIn_TimestampConfiguration* pTimestampConfiguration,
    TPdfToolsCrypto_HashAlgorithm                           iHashAlgorithm);

/******************************************************************************
 * Provider
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersBuiltIn_Provider* PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_Provider_New(void);

/**
 * @brief Create a configuration to sign with a PFX (PKCS#12) soft certificate
The file must contain the certificate itself, all certificates of the trust chain, and the private key.

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

* @param[in] pStreamDesc The signing certificate in PKCS#12 format (.p12, .pfx).

* @param[in] szPassword The password required to decrypt the private key of the archive.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The PFX (PKCS#12) archive is corrupt and cannot be read.

 * - \ref ePdfTools_Error_Password The password is invalid.

 * - \ref ePdfTools_Error_IllegalArgument The certificate is not a valid signing certificate


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_Provider_CreateSignatureFromCertificateA(
    TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider, const TPdfToolsSys_StreamDescriptor* pStreamDesc,
    const char* szPassword);
/**
 * @brief Create a configuration to sign with a PFX (PKCS#12) soft certificate
The file must contain the certificate itself, all certificates of the trust chain, and the private key.

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

* @param[in] pStreamDesc The signing certificate in PKCS#12 format (.p12, .pfx).

* @param[in] szPassword The password required to decrypt the private key of the archive.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The PFX (PKCS#12) archive is corrupt and cannot be read.

 * - \ref ePdfTools_Error_Password The password is invalid.

 * - \ref ePdfTools_Error_IllegalArgument The certificate is not a valid signing certificate


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersBuiltIn_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_Provider_CreateSignatureFromCertificateW(
    TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider, const TPdfToolsSys_StreamDescriptor* pStreamDesc,
    const WCHAR* szPassword);
/**
 * @brief Create a time-stamp configuration
Note that to create time-stamps, the \ref PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrl "" must be set.

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersBuiltIn_TimestampConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_Provider_CreateTimestamp(TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider);
/**
 * @brief Create a configuration to prepare a signature for an external signature handler
This method is part of a very specialized use case requiring an external signature handler.
The process using an external signature handler is:
  - \ref PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignature "": Create the signature configuration.
  - \ref PdfToolsSign_Signer_AddPreparedSignature "": Create the document with the prepared signature.
  - \ref PdfToolsSign_PreparedDocument_GetHash "": Calculate the hash from the document and create the signature using
an external signature handler.
  - \ref PdfToolsCryptoProvidersBuiltIn_Provider_ReadExternalSignature "": Create signature configuration for the
external signature.
  - \ref PdfToolsSign_Signer_SignPreparedSignature "": Insert the external signature into the document with the prepared
signature.

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

* @param[in] iSize The expected size of the cryptographic signature that will be added later.
This is the number of bytes that will be reserved in the prepared signature.

* @param[in] szFormat The format (SubFilter) of the cryptographic signature that is added later.
For example, `"adbe.pkcs7.detached"` or `"ETSI.CAdES.detached"`.

* @param[in] szName The name of the signer of the cryptographic signature that will be added later.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignatureA(TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider,
                                                                 int iSize, const char* szFormat, const char* szName);
/**
 * @brief Create a configuration to prepare a signature for an external signature handler
This method is part of a very specialized use case requiring an external signature handler.
The process using an external signature handler is:
  - \ref PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignature "": Create the signature configuration.
  - \ref PdfToolsSign_Signer_AddPreparedSignature "": Create the document with the prepared signature.
  - \ref PdfToolsSign_PreparedDocument_GetHash "": Calculate the hash from the document and create the signature using
an external signature handler.
  - \ref PdfToolsCryptoProvidersBuiltIn_Provider_ReadExternalSignature "": Create signature configuration for the
external signature.
  - \ref PdfToolsSign_Signer_SignPreparedSignature "": Insert the external signature into the document with the prepared
signature.

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

* @param[in] iSize The expected size of the cryptographic signature that will be added later.
This is the number of bytes that will be reserved in the prepared signature.

* @param[in] szFormat The format (SubFilter) of the cryptographic signature that is added later.
For example, `"adbe.pkcs7.detached"` or `"ETSI.CAdES.detached"`.

* @param[in] szName The name of the signer of the cryptographic signature that will be added later.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignatureW(TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider,
                                                                 int iSize, const WCHAR* szFormat, const WCHAR* szName);
/**
 * @brief Read signature created by an external signature handler
See \ref PdfToolsCryptoProvidersBuiltIn_Provider_CreatePreparedSignature "" for more information on the signing process
using an external signature handler.

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

* @param[in] pSignature This signature must not be larger than the number of bytes reserved in the prepared signature.

* @param[in] nSignatures Size of the array `pSignature`.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSign_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersBuiltIn_Provider_ReadExternalSignature(TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider,
                                                              const unsigned char* pSignature, size_t nSignatures);

/**
 * @brief The URL of the trusted time-stamp authority (TSA) from which time-stamps shall be acquired

The TSA must support the time-stamp protocol as defined in RFC 3161.

The property’s value must be a URL with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›][/‹resource›]`

Where:
  - `http/https`: Protocol for connection to TSA.
  - `‹user›:‹password›` (optional): Credentials for connection to TSA (basic authorization).
  - `‹host›`: Hostname of TSA.
  - `‹port›`: Port for connection to TSA.
  - `‹resource›`: The resource.

Applying a time-stamp requires an online connection to a time server; the firewall must be configured accordingly.
If a web proxy is used (see \ref PdfTools_Sdk_GetProxy ""), make sure the following MIME types are supported:
  - `application/timestamp-query`
  - `application/timestamp-reply`

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrlA(
    TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider, char* pBuffer, size_t nBufferSize);
/**
 * @brief The URL of the trusted time-stamp authority (TSA) from which time-stamps shall be acquired

The TSA must support the time-stamp protocol as defined in RFC 3161.

The property’s value must be a URL with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›][/‹resource›]`

Where:
  - `http/https`: Protocol for connection to TSA.
  - `‹user›:‹password›` (optional): Credentials for connection to TSA (basic authorization).
  - `‹host›`: Hostname of TSA.
  - `‹port›`: Port for connection to TSA.
  - `‹resource›`: The resource.

Applying a time-stamp requires an online connection to a time server; the firewall must be configured accordingly.
If a web proxy is used (see \ref PdfTools_Sdk_GetProxy ""), make sure the following MIME types are supported:
  - `application/timestamp-query`
  - `application/timestamp-reply`

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_Provider_GetTimestampUrlW(
    TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The URL of the trusted time-stamp authority (TSA) from which time-stamps shall be acquired

The TSA must support the time-stamp protocol as defined in RFC 3161.

The property’s value must be a URL with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›][/‹resource›]`

Where:
  - `http/https`: Protocol for connection to TSA.
  - `‹user›:‹password›` (optional): Credentials for connection to TSA (basic authorization).
  - `‹host›`: Hostname of TSA.
  - `‹port›`: Port for connection to TSA.
  - `‹resource›`: The resource.

Applying a time-stamp requires an online connection to a time server; the firewall must be configured accordingly.
If a web proxy is used (see \ref PdfTools_Sdk_GetProxy ""), make sure the following MIME types are supported:
  - `application/timestamp-query`
  - `application/timestamp-reply`

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

* @param[in] szTimestampUrl Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_Provider_SetTimestampUrlA(
    TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider, const char* szTimestampUrl);
/**
 * @brief The URL of the trusted time-stamp authority (TSA) from which time-stamps shall be acquired

The TSA must support the time-stamp protocol as defined in RFC 3161.

The property’s value must be a URL with the following elements:

`http[s]://[‹user›[:‹password›]@]‹host›[:‹port›][/‹resource›]`

Where:
  - `http/https`: Protocol for connection to TSA.
  - `‹user›:‹password›` (optional): Credentials for connection to TSA (basic authorization).
  - `‹host›`: Hostname of TSA.
  - `‹port›`: Port for connection to TSA.
  - `‹resource›`: The resource.

Applying a time-stamp requires an online connection to a time server; the firewall must be configured accordingly.
If a web proxy is used (see \ref PdfTools_Sdk_GetProxy ""), make sure the following MIME types are supported:
  - `application/timestamp-query`
  - `application/timestamp-reply`

* @param[in,out] pProvider Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersBuiltIn_Provider.

* @param[in] szTimestampUrl Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersBuiltIn_Provider_SetTimestampUrlW(
    TPdfToolsCryptoProvidersBuiltIn_Provider* pProvider, const WCHAR* szTimestampUrl);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSBUILTIN_H__ */
