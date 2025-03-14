/******************************************************************************
 *
 * File:            PdfTools_PdfToolsCryptoProvidersPkcs11.h
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

#ifndef PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSPKCS11_H__
#define PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSPKCS11_H__

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
#define PdfToolsCryptoProvidersPkcs11_Module_Load PdfToolsCryptoProvidersPkcs11_Module_LoadW

#define PdfToolsCryptoProvidersPkcs11_Device_CreateSession PdfToolsCryptoProvidersPkcs11_Device_CreateSessionW

#define PdfToolsCryptoProvidersPkcs11_Device_GetDescription PdfToolsCryptoProvidersPkcs11_Device_GetDescriptionW

#define PdfToolsCryptoProvidersPkcs11_Device_GetManufacturerID PdfToolsCryptoProvidersPkcs11_Device_GetManufacturerIDW

#define PdfToolsCryptoProvidersPkcs11_Session_Login PdfToolsCryptoProvidersPkcs11_Session_LoginW
#define PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromName \
    PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromNameW
#define PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyLabel \
    PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyLabelW

#define PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrl PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrlW
#define PdfToolsCryptoProvidersPkcs11_Session_SetTimestampUrl PdfToolsCryptoProvidersPkcs11_Session_SetTimestampUrlW

#else
#define PdfToolsCryptoProvidersPkcs11_Module_Load PdfToolsCryptoProvidersPkcs11_Module_LoadA

#define PdfToolsCryptoProvidersPkcs11_Device_CreateSession PdfToolsCryptoProvidersPkcs11_Device_CreateSessionA

#define PdfToolsCryptoProvidersPkcs11_Device_GetDescription PdfToolsCryptoProvidersPkcs11_Device_GetDescriptionA

#define PdfToolsCryptoProvidersPkcs11_Device_GetManufacturerID PdfToolsCryptoProvidersPkcs11_Device_GetManufacturerIDA

#define PdfToolsCryptoProvidersPkcs11_Session_Login PdfToolsCryptoProvidersPkcs11_Session_LoginA
#define PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromName \
    PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromNameA
#define PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyLabel \
    PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyLabelA

#define PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrl PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrlA
#define PdfToolsCryptoProvidersPkcs11_Session_SetTimestampUrl PdfToolsCryptoProvidersPkcs11_Session_SetTimestampUrlA

#endif

/******************************************************************************
 * SignatureConfiguration
 *****************************************************************************/
/**
 * @brief Add a certificate
Add a certificate to the signature configuration.
Adding certificates of the trust chain is often required, if they are missing in the PKCS#11 device's store and
validation information is added (see \ref PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_GetValidationInformation
""). For example, if this object has been created using \ref
PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyId "".

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.

* @param[in] pCertificate The certificate in either PEM (.pem, ASCII text) or DER (.cer, binary) form


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt If the certificate is corrupt and cannot be read


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_AddCertificate(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration,
    const TPdfToolsSys_StreamDescriptor*                   pCertificate);

/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_GetHashAlgorithm(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.

* @param[in] iHashAlgorithm Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_SetHashAlgorithm(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_HashAlgorithm                          iHashAlgorithm);
/**
 * @brief The padding type of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignaturePaddingType_RsaSsaPss "" for RSA and \ref
ePdfToolsCrypto_SignaturePaddingType_Default "" for ECDSA certificates

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_SignaturePaddingType PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_GetSignaturePaddingType(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The padding type of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignaturePaddingType_RsaSsaPss "" for RSA and \ref
ePdfToolsCrypto_SignaturePaddingType_Default "" for ECDSA certificates

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.

* @param[in] iSignaturePaddingType Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_SetSignaturePaddingType(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_SignaturePaddingType                   iSignaturePaddingType);
/**
 * @brief The format (encoding) of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignatureFormat_EtsiCadesDetached ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_SignatureFormat PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_GetSignatureFormat(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The format (encoding) of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignatureFormat_EtsiCadesDetached ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.

* @param[in] iSignatureFormat Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_SetSignatureFormat(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_SignatureFormat                        iSignatureFormat);
/**
 * @brief Whether to add a trusted time-stamp to the signature

If \ref "TRUE", the \ref PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrl "" must be set.

Default: \ref "FALSE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_GetAddTimestamp(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief Whether to add a trusted time-stamp to the signature

If \ref "TRUE", the \ref PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrl "" must be set.

Default: \ref "FALSE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.

* @param[in] bAddTimestamp Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_SetAddTimestamp(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration, BOOL bAddTimestamp);
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
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_ValidationInformation PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_GetValidationInformation(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration);
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
TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration.

* @param[in] iValidationInformation Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_SetValidationInformation(
    TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_ValidationInformation                  iValidationInformation);

/******************************************************************************
 * TimestampConfiguration
 *****************************************************************************/
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the time-stamp signature is created.

<b>Note:</b> This algorithm must be supported by the time-stamp server; many support only SHA-256.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_TimestampConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_TimestampConfiguration_GetHashAlgorithm(
    TPdfToolsCryptoProvidersPkcs11_TimestampConfiguration* pTimestampConfiguration);
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the time-stamp signature is created.

<b>Note:</b> This algorithm must be supported by the time-stamp server; many support only SHA-256.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_TimestampConfiguration.

* @param[in] iHashAlgorithm Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_TimestampConfiguration_SetHashAlgorithm(
    TPdfToolsCryptoProvidersPkcs11_TimestampConfiguration* pTimestampConfiguration,
    TPdfToolsCrypto_HashAlgorithm                          iHashAlgorithm);

/******************************************************************************
 * Module
 *****************************************************************************/
/**
 * @brief Load a PKCS#11 driver module
* @param[in] szLibrary The name or path to the driver module (middleware).
This can be found in the documentation of your cryptographic device.
Examples:
  - For Securosys SA Primus HSM or CloudsHSM use `primusP11.dll` on Windows and `libprimusP11.so`
on Linux.
  - For Google Cloud HSM (Cloud KMS) use `libkmsp11.so` and \ref
PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyLabel ""
  - For SafeNet Luna HSM use `cryptoki.dll` on Windows or `libCryptoki2_64.so` on Linux/UNIX.
  - The CardOS API from Atos (Siemens) uses `siecap11.dll`
  - The IBM 4758 cryptographic coprocessor uses `cryptoki.dll`
  - Devices from Aladdin Ltd. use `etpkcs11.dll`


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_NotFound The library cannot be found.

 * - \ref ePdfTools_Error_Exists The module has been loaded already by this application.

 * - \ref ePdfTools_Error_IllegalArgument The given <b>szLibrary</b> is not a PKCS#11 driver module.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_Module* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Module_LoadA(const char* szLibrary);
/**
 * @brief Load a PKCS#11 driver module
* @param[in] szLibrary The name or path to the driver module (middleware).
This can be found in the documentation of your cryptographic device.
Examples:
  - For Securosys SA Primus HSM or CloudsHSM use `primusP11.dll` on Windows and `libprimusP11.so`
on Linux.
  - For Google Cloud HSM (Cloud KMS) use `libkmsp11.so` and \ref
PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyLabel ""
  - For SafeNet Luna HSM use `cryptoki.dll` on Windows or `libCryptoki2_64.so` on Linux/UNIX.
  - The CardOS API from Atos (Siemens) uses `siecap11.dll`
  - The IBM 4758 cryptographic coprocessor uses `cryptoki.dll`
  - Devices from Aladdin Ltd. use `etpkcs11.dll`


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_NotFound The library cannot be found.

 * - \ref ePdfTools_Error_Exists The module has been loaded already by this application.

 * - \ref ePdfTools_Error_IllegalArgument The given <b>szLibrary</b> is not a PKCS#11 driver module.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_Module* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Module_LoadW(const WCHAR* szLibrary);

/**
 * @brief Enable full parallelization

The PKCS#11 standard specifies that "an application can specify that it will be accessing the library concurrently from
multiple threads, and the library must [...] ensure proper thread-safe behavior." However, some PKCS#11 modules
(middleware) implementations are not thread-safe. For this reason, the SDK synchronizes all access to the module. If the
middleware is thread-safe, full parallel usage of the cryptographic device can be enabled by setting this property to
\ref "TRUE" and thereby improving the performance.

Default: \ref "FALSE"

* @param[in,out] pModule Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Module.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Module_GetEnableFullParallelization(TPdfToolsCryptoProvidersPkcs11_Module* pModule);
/**
 * @brief Enable full parallelization

The PKCS#11 standard specifies that "an application can specify that it will be accessing the library concurrently from
multiple threads, and the library must [...] ensure proper thread-safe behavior." However, some PKCS#11 modules
(middleware) implementations are not thread-safe. For this reason, the SDK synchronizes all access to the module. If the
middleware is thread-safe, full parallel usage of the cryptographic device can be enabled by setting this property to
\ref "TRUE" and thereby improving the performance.

Default: \ref "FALSE"

* @param[in,out] pModule Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Module.

* @param[in] bEnableFullParallelization Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Module_SetEnableFullParallelization(
    TPdfToolsCryptoProvidersPkcs11_Module* pModule, BOOL bEnableFullParallelization);
/**
 * @brief The list of devices managed by this module
Most often there is only a single device, so the method \ref PdfToolsCryptoProvidersPkcs11_DeviceList_GetSingle "" can
be used.

* @param[in,out] pModule Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Module.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_DeviceList* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Module_GetDevices(TPdfToolsCryptoProvidersPkcs11_Module* pModule);

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
PdfToolsCryptoProvidersPkcs11_Module_Close(TPdfToolsCryptoProvidersPkcs11_Module* pObject);
/******************************************************************************
 * Device
 *****************************************************************************/
/**
 * @brief Create a session
* @param[in,out] pDevice Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Device.

* @param[in] szPassword If this parameter is not `NULL`, the session is created and \ref
PdfToolsCryptoProvidersPkcs11_Session_Login "" executed.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_Session* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Device_CreateSessionA(TPdfToolsCryptoProvidersPkcs11_Device* pDevice,
                                                    const char*                            szPassword);
/**
 * @brief Create a session
* @param[in,out] pDevice Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Device.

* @param[in] szPassword If this parameter is not `NULL`, the session is created and \ref
PdfToolsCryptoProvidersPkcs11_Session_Login "" executed.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_Session* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Device_CreateSessionW(TPdfToolsCryptoProvidersPkcs11_Device* pDevice,
                                                    const WCHAR*                           szPassword);

/**
 * @brief Description of the device
* @param[in,out] pDevice Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Device.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Device_GetDescriptionA(
    TPdfToolsCryptoProvidersPkcs11_Device* pDevice, char* pBuffer, size_t nBufferSize);
/**
 * @brief Description of the device
* @param[in,out] pDevice Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Device.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Device_GetDescriptionW(
    TPdfToolsCryptoProvidersPkcs11_Device* pDevice, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief ID of the device's manufacturer
* @param[in,out] pDevice Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Device.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Device_GetManufacturerIDA(
    TPdfToolsCryptoProvidersPkcs11_Device* pDevice, char* pBuffer, size_t nBufferSize);
/**
 * @brief ID of the device's manufacturer
* @param[in,out] pDevice Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Device.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Device_GetManufacturerIDW(
    TPdfToolsCryptoProvidersPkcs11_Device* pDevice, WCHAR* pBuffer, size_t nBufferSize);

/******************************************************************************
 * Session
 *****************************************************************************/
/**
 * @brief Log in user into the cryptographic device

Login is typically required to enable cryptographic operations.
Furthermore, some of the device's objects such as certificates or private keys might only be visible when logged in.

Note that many devices are locked after a number of failed login attempts.
Therefore, it is crucial to not retry this method using the same <b>szPassword</b> after a failed attempt.

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] szPassword The user's password


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Password If the <b>szPassword</b> is not correct

 * - \ref ePdfTools_Error_Permission If the <b>szPassword</b> has been locked or is expired

 * - \ref ePdfTools_Error_UnsupportedOperation If the user has already logged in


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_LoginA(TPdfToolsCryptoProvidersPkcs11_Session* pSession, const char* szPassword);
/**
 * @brief Log in user into the cryptographic device

Login is typically required to enable cryptographic operations.
Furthermore, some of the device's objects such as certificates or private keys might only be visible when logged in.

Note that many devices are locked after a number of failed login attempts.
Therefore, it is crucial to not retry this method using the same <b>szPassword</b> after a failed attempt.

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] szPassword The user's password


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Password If the <b>szPassword</b> is not correct

 * - \ref ePdfTools_Error_Permission If the <b>szPassword</b> has been locked or is expired

 * - \ref ePdfTools_Error_UnsupportedOperation If the user has already logged in


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_LoginW(TPdfToolsCryptoProvidersPkcs11_Session* pSession, const WCHAR* szPassword);
/**
 * @brief Create a signature configuration based on signing certificate
* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in,out] pCertificate The signing certificate from \ref PdfToolsCryptoProvidersPkcs11_Session_GetCertificates ""


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the <b>pCertificate</b> is not a valid signing certificate.

 * - \ref ePdfTools_Error_IllegalArgument If the <b>pCertificate</b> has expired.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_CreateSignature(TPdfToolsCryptoProvidersPkcs11_Session* pSession,
                                                      TPdfToolsCryptoProviders_Certificate*   pCertificate);
/**
 * @brief Create a signature configuration based on certificate name
* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] szName The name of the signing certificate (\ref PdfToolsCryptoProviders_Certificate_GetName "")


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_NotFound If the certificate cannot be found in \ref
PdfToolsCryptoProvidersPkcs11_Session_GetCertificates ""

 * - \ref ePdfTools_Error_IllegalArgument If the certificate is not a valid signing certificate


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromNameA(TPdfToolsCryptoProvidersPkcs11_Session* pSession,
                                                               const char*                             szName);
/**
 * @brief Create a signature configuration based on certificate name
* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] szName The name of the signing certificate (\ref PdfToolsCryptoProviders_Certificate_GetName "")


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_NotFound If the certificate cannot be found in \ref
PdfToolsCryptoProvidersPkcs11_Session_GetCertificates ""

 * - \ref ePdfTools_Error_IllegalArgument If the certificate is not a valid signing certificate


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromNameW(TPdfToolsCryptoProvidersPkcs11_Session* pSession,
                                                               const WCHAR*                            szName);
/**
 * @brief Create a signature configuration based on the private key's ID and an external certificate

Create a signature configuration where only the private key is contained in the PKCS#11 device and
the signing certificate is provided externally.
This is intended for PKCS#11 devices that can only store private keys, e.g. the Google Cloud Key Management (KMS).

The private key object is identified using its ID,
i.e. the `CKA_ID` object attribute in the PKCS#11 store.

The certificates of the trust chain should be added using \ref
PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_AddCertificate "".

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] pId The ID of the private key object in the PKCS#11 store

* @param[in] nIds Size of the array `pId`.

* @param[in] pCertificate The signing certificate in either PEM (.pem, ASCII text) or DER (.cer, binary) form


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_NotFound If the private key cannot be found in the PKCS#11 store

 * - \ref ePdfTools_Error_IllegalArgument If the certificate is not a valid signing certificate

 * - \ref ePdfTools_Error_IllegalArgument If the key specification matches more than one key


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyId(TPdfToolsCryptoProvidersPkcs11_Session* pSession,
                                                               const unsigned char* pId, size_t nIds,
                                                               const TPdfToolsSys_StreamDescriptor* pCertificate);
/**
 * @brief Create a signature configuration based on the private key's label (name) and an external certificate

Create a signature configuration where only the private key is contained in the PKCS#11 device and
the signing certificate is provided externally.
This is intended for PKCS#11 devices that can only store private keys, e.g. the Google Cloud Key Management (KMS).

The private key object is identified using its label,
i.e. the `CKA_LABEL` object attribute in the PKCS#11 store.

The certificates of the trust chain should be added using \ref
PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_AddCertificate "".

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] szLabel The label of the private key object in the PKCS#11 store

* @param[in] pCertificate The signing certificate in either PEM (.pem, ASCII text) or DER (.cer, binary) form


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_NotFound If the private key cannot be found in the PKCS#11 store

 * - \ref ePdfTools_Error_IllegalArgument If the certificate is not a valid signing certificate

 * - \ref ePdfTools_Error_IllegalArgument If the key specification matches more than one key


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyLabelA(TPdfToolsCryptoProvidersPkcs11_Session* pSession,
                                                                   const char*                             szLabel,
                                                                   const TPdfToolsSys_StreamDescriptor* pCertificate);
/**
 * @brief Create a signature configuration based on the private key's label (name) and an external certificate

Create a signature configuration where only the private key is contained in the PKCS#11 device and
the signing certificate is provided externally.
This is intended for PKCS#11 devices that can only store private keys, e.g. the Google Cloud Key Management (KMS).

The private key object is identified using its label,
i.e. the `CKA_LABEL` object attribute in the PKCS#11 store.

The certificates of the trust chain should be added using \ref
PdfToolsCryptoProvidersPkcs11_SignatureConfiguration_AddCertificate "".

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] szLabel The label of the private key object in the PKCS#11 store

* @param[in] pCertificate The signing certificate in either PEM (.pem, ASCII text) or DER (.cer, binary) form


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_NotFound If the private key cannot be found in the PKCS#11 store

 * - \ref ePdfTools_Error_IllegalArgument If the certificate is not a valid signing certificate

 * - \ref ePdfTools_Error_IllegalArgument If the key specification matches more than one key


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_CreateSignatureFromKeyLabelW(TPdfToolsCryptoProvidersPkcs11_Session* pSession,
                                                                   const WCHAR*                            szLabel,
                                                                   const TPdfToolsSys_StreamDescriptor* pCertificate);
/**
 * @brief Create a time-stamp configuration
Note that to create time-stamps, the \ref PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrl "" must be set.

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_TimestampConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_CreateTimestamp(TPdfToolsCryptoProvidersPkcs11_Session* pSession);

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

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrlA(
    TPdfToolsCryptoProvidersPkcs11_Session* pSession, char* pBuffer, size_t nBufferSize);
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

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Session_GetTimestampUrlW(
    TPdfToolsCryptoProvidersPkcs11_Session* pSession, WCHAR* pBuffer, size_t nBufferSize);
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

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] szTimestampUrl Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Session_SetTimestampUrlA(
    TPdfToolsCryptoProvidersPkcs11_Session* pSession, const char* szTimestampUrl);
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

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.

* @param[in] szTimestampUrl Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersPkcs11_Session_SetTimestampUrlW(
    TPdfToolsCryptoProvidersPkcs11_Session* pSession, const WCHAR* szTimestampUrl);
/**
 * @brief The cerfificates of the device
The certificates available in this device.
Note that some certificates or their private keys (see \ref PdfToolsCryptoProviders_Certificate_GetHasPrivateKey "")
might only be visible after \ref PdfToolsCryptoProvidersPkcs11_Session_Login "".

* @param[in,out] pSession Acts as a handle to the native object of type \ref TPdfToolsCryptoProvidersPkcs11_Session.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProviders_CertificateList* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_Session_GetCertificates(TPdfToolsCryptoProvidersPkcs11_Session* pSession);

/******************************************************************************
 * DeviceList
 *****************************************************************************/
/**
 * @brief Get the single device
* @param[in,out] pDeviceList Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_DeviceList.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_NotFound No device was found.
Make sure the device is connected and the right PKCS#11 modules has been loaded.

 * - \ref ePdfTools_Error_UnsupportedOperation More than one device available.
Choose the right one from the device list, e.g. by looking at \ref PdfToolsCryptoProvidersPkcs11_Device_GetDescription
"" or its \ref PdfToolsCryptoProvidersPkcs11_Session_GetCertificates "".


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_Device* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_DeviceList_GetSingle(TPdfToolsCryptoProvidersPkcs11_DeviceList* pDeviceList);
/**
 * @brief Get the number of elements in the list.
* @param[in,out] pDeviceList Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_DeviceList.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_DeviceList_GetCount(TPdfToolsCryptoProvidersPkcs11_DeviceList* pDeviceList);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pDeviceList Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersPkcs11_DeviceList.

* @param[in] iIndex

 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersPkcs11_Device* PDFTOOLS_CALL
PdfToolsCryptoProvidersPkcs11_DeviceList_Get(TPdfToolsCryptoProvidersPkcs11_DeviceList* pDeviceList, int iIndex);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSPKCS11_H__ */
