/******************************************************************************
 *
 * File:            PdfTools_PdfToolsCryptoProvidersSwisscomSigSrv.h
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

#ifndef PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSSWISSCOMSIGSRV_H__
#define PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSSWISSCOMSIGSRV_H__

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
#define TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequired \
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequiredW
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_AddConsentRequiredHandler \
    PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_AddConsentRequiredHandlerW
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_RemoveConsentRequiredHandler \
    PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_RemoveConsentRequiredHandlerW

#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_New        PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_NewW
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMSISDN  PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMSISDNW
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMSISDN  PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMSISDNW
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMessage PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMessageW
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMessage PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMessageW
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetLanguage \
    PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetLanguageW
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetLanguage \
    PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetLanguageW

#define PdfToolsCryptoProvidersSwisscomSigSrv_Session_New PdfToolsCryptoProvidersSwisscomSigSrv_Session_NewW
#define PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForStaticIdentity \
    PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForStaticIdentityW
#define PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForOnDemandIdentity \
    PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForOnDemandIdentityW
#define PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateTimestamp \
    PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateTimestampW

#else
#define TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequired \
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequiredA
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_AddConsentRequiredHandler \
    PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_AddConsentRequiredHandlerA
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_RemoveConsentRequiredHandler \
    PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_RemoveConsentRequiredHandlerA

#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_New        PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_NewA
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMSISDN  PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMSISDNA
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMSISDN  PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMSISDNA
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMessage PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMessageA
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMessage PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMessageA
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetLanguage \
    PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetLanguageA
#define PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetLanguage \
    PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetLanguageA

#define PdfToolsCryptoProvidersSwisscomSigSrv_Session_New PdfToolsCryptoProvidersSwisscomSigSrv_Session_NewA
#define PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForStaticIdentity \
    PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForStaticIdentityA
#define PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForOnDemandIdentity \
    PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForOnDemandIdentityA
#define PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateTimestamp \
    PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateTimestampA

#endif

/**
Event containing the URL for step-up authentication using password and SMS challenge (OTP).
Password and SMS challenge are used as a fallback mechanism for the Mobile ID authentication.
For example, if the Mobile ID of the user is not activated.
The user must be redirected to this URL for consent of will.

* @param[in,out] pContext Context of the event callback.

* @param[in] szUrl The consent URL where the user must be redirected to acknowledge the declaration of will.


 */
typedef void(PDFTOOLS_CALL* TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequiredA)(void*       pContext,
                                                                                            const char* szUrl);
/**
Event containing the URL for step-up authentication using password and SMS challenge (OTP).
Password and SMS challenge are used as a fallback mechanism for the Mobile ID authentication.
For example, if the Mobile ID of the user is not activated.
The user must be redirected to this URL for consent of will.

* @param[in,out] pContext Context of the event callback.

* @param[in] szUrl The consent URL where the user must be redirected to acknowledge the declaration of will.


 */
typedef void(PDFTOOLS_CALL* TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequiredW)(void*        pContext,
                                                                                            const WCHAR* szUrl);

/******************************************************************************
 * SignatureConfiguration
 *****************************************************************************/
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_GetHashAlgorithm(
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration.

* @param[in] iHashAlgorithm Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_SetHashAlgorithm(
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_HashAlgorithm                                  iHashAlgorithm);
/**
 * @brief The format (encoding) of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignatureFormat_AdbePkcs7Detached ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_SignatureFormat PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_GetSignatureFormat(
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief The format (encoding) of the cryptographic signature
Default: \ref ePdfToolsCrypto_SignatureFormat_AdbePkcs7Detached ""

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration.

* @param[in] iSignatureFormat Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_SetSignatureFormat(
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* pSignatureConfiguration,
    TPdfToolsCrypto_SignatureFormat                                iSignatureFormat);
/**
 * @brief Whether to add a trusted time-stamp to the signature
Default: \ref "FALSE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_GetAddTimestamp(
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief Whether to add a trusted time-stamp to the signature
Default: \ref "FALSE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration.

* @param[in] bAddTimestamp Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_SetAddTimestamp(
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* pSignatureConfiguration, BOOL bAddTimestamp);
/**
 * @brief Whether to embed validation information into the signature (LTV)

  - \ref "TRUE": Create an LTV signature by embedding validation information
(see \ref ePdfToolsCrypto_ValidationInformation_EmbedInSignature "").
This value is only supported, if the \ref
PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_GetSignatureFormat "" is \ref
ePdfToolsCrypto_SignatureFormat_AdbePkcs7Detached "". LTV signatures for other formats can be created by adding
validation information to the signed document (see \ref PdfToolsSign_Signer_Process "" and \ref
PdfToolsSign_OutputOptions_GetAddValidationInformation "").
  - \ref "FALSE": Create a basic signature without validation information (see \ref
ePdfToolsCrypto_ValidationInformation_None "").

Default: \ref "TRUE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_GetEmbedValidationInformation(
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* pSignatureConfiguration);
/**
 * @brief Whether to embed validation information into the signature (LTV)

  - \ref "TRUE": Create an LTV signature by embedding validation information
(see \ref ePdfToolsCrypto_ValidationInformation_EmbedInSignature "").
This value is only supported, if the \ref
PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_GetSignatureFormat "" is \ref
ePdfToolsCrypto_SignatureFormat_AdbePkcs7Detached "". LTV signatures for other formats can be created by adding
validation information to the signed document (see \ref PdfToolsSign_Signer_Process "" and \ref
PdfToolsSign_OutputOptions_GetAddValidationInformation "").
  - \ref "FALSE": Create a basic signature without validation information (see \ref
ePdfToolsCrypto_ValidationInformation_None "").

Default: \ref "TRUE"

* @param[in,out] pSignatureConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration.

* @param[in] bEmbedValidationInformation Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration_SetEmbedValidationInformation(
    TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* pSignatureConfiguration,
    BOOL                                                           bEmbedValidationInformation);

/******************************************************************************
 * TimestampConfiguration
 *****************************************************************************/
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration_GetHashAlgorithm(
    TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration* pTimestampConfiguration);
/**
 * @brief The message digest algorithm

The algorithm used to hash the document and from which the cryptographic signature is created.

Default: \ref ePdfToolsCrypto_HashAlgorithm_Sha256 ""

* @param[in,out] pTimestampConfiguration Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration.

* @param[in] iHashAlgorithm Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument If the value is invalid or not supported.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration_SetHashAlgorithm(
    TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration* pTimestampConfiguration,
    TPdfToolsCrypto_HashAlgorithm                                  iHashAlgorithm);

/******************************************************************************
 * StepUp
 *****************************************************************************/
/**
 * @brief Adds event handler.
 *
 * @param[in,out] pStepUp Pointer to the object to which the event handler is added.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is added.
 *
 * @return \ref TRUE if adding event handler was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_AddConsentRequiredHandlerA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, void* pContext,
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequiredA pFunction);
/**
 * @brief Adds event handler.
 *
 * @param[in,out] pStepUp Pointer to the object to which the event handler is added.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is added.
 *
 * @return \ref TRUE if adding event handler was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_AddConsentRequiredHandlerW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, void* pContext,
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequiredW pFunction);
/**
 * @brief Removes event handler.
 *
 * @param[in,out] pStepUp Pointer to the object from which the event handler is removed.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is removed.
 *
 * @return \ref TRUE if removal was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_RemoveConsentRequiredHandlerA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, void* pContext,
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequiredA pFunction);
/**
 * @brief Removes event handler.
 *
 * @param[in,out] pStepUp Pointer to the object from which the event handler is removed.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is removed.
 *
 * @return \ref TRUE if removal was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_RemoveConsentRequiredHandlerW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, void* pContext,
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp_ConsentRequiredW pFunction);

/**
* @param[in] szMsisdn The mobile phone number

* @param[in] szMessage The message to be displayed on the mobile phone

* @param[in] szLanguage The language of the message


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_NewA(const char* szMsisdn, const char* szMessage, const char* szLanguage);
/**
* @param[in] szMsisdn The mobile phone number

* @param[in] szMessage The message to be displayed on the mobile phone

* @param[in] szLanguage The language of the message


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_NewW(const WCHAR* szMsisdn, const WCHAR* szMessage,
                                                  const WCHAR* szLanguage);

/**
 * @brief The mobile phone number
Example: `"+41798765432"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMSISDNA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, char* pBuffer, size_t nBufferSize);
/**
 * @brief The mobile phone number
Example: `"+41798765432"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMSISDNW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The mobile phone number
Example: `"+41798765432"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[in] szMSISDN Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMSISDNA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, const char* szMSISDN);
/**
 * @brief The mobile phone number
Example: `"+41798765432"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[in] szMSISDN Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMSISDNW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, const WCHAR* szMSISDN);
/**
 * @brief The message to be displayed on the mobile phone
Example: `"Do you authorize your signature on Contract.pdf?"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMessageA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, char* pBuffer, size_t nBufferSize);
/**
 * @brief The message to be displayed on the mobile phone
Example: `"Do you authorize your signature on Contract.pdf?"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetMessageW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The message to be displayed on the mobile phone
Example: `"Do you authorize your signature on Contract.pdf?"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[in] szMessage Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMessageA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, const char* szMessage);
/**
 * @brief The message to be displayed on the mobile phone
Example: `"Do you authorize your signature on Contract.pdf?"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[in] szMessage Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetMessageW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, const WCHAR* szMessage);
/**
 * @brief The language of the message
Example: `"DE"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetLanguageA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, char* pBuffer, size_t nBufferSize);
/**
 * @brief The language of the message
Example: `"DE"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_GetLanguageW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The language of the message
Example: `"DE"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[in] szLanguage Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetLanguageA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, const char* szLanguage);
/**
 * @brief The language of the message
Example: `"DE"`

* @param[in,out] pStepUp Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp.

* @param[in] szLanguage Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsCryptoProvidersSwisscomSigSrv_StepUp_SetLanguageW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp, const WCHAR* szLanguage);

/******************************************************************************
 * Session
 *****************************************************************************/
/**
* @param[in] szUrl The service endpoint base URL.
Example: `https://ais.swisscom.com`

* @param[in,out] pHttpClientHandler The SSL configuration with the client certificate and trust store.
Use \ref PdfTools_HttpClientHandler_SetClientCertificate "" to set your SSL client certificate "clientcert.p12"
of your Swisscom Signing Service account.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Http If a network error occurs.

 * - \ref ePdfTools_Error_Permission If the SSL client certificate is rejected.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_Session* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_Session_NewA(const char* szUrl, TPdfTools_HttpClientHandler* pHttpClientHandler);
/**
* @param[in] szUrl The service endpoint base URL.
Example: `https://ais.swisscom.com`

* @param[in,out] pHttpClientHandler The SSL configuration with the client certificate and trust store.
Use \ref PdfTools_HttpClientHandler_SetClientCertificate "" to set your SSL client certificate "clientcert.p12"
of your Swisscom Signing Service account.


 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Http If a network error occurs.

 * - \ref ePdfTools_Error_Permission If the SSL client certificate is rejected.


 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_Session* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_Session_NewW(const WCHAR* szUrl, TPdfTools_HttpClientHandler* pHttpClientHandler);

/**
 * @brief Create a signature configuration for a static certificate.
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_Session.

* @param[in] szIdentity The Claimed Identity string as provided by Swisscom: `‹customer name›:‹key identity›`
Example: `"ais-90days-trial:static-saphir4-ch"`

* @param[in] szName Name of the signer.
This parameter is not used for certificate selection, but for the signature appearance and signature description in the
PDF only. Example: `"Signing Service TEST account"`


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForStaticIdentityA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_Session* pSession, const char* szIdentity, const char* szName);
/**
 * @brief Create a signature configuration for a static certificate.
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_Session.

* @param[in] szIdentity The Claimed Identity string as provided by Swisscom: `‹customer name›:‹key identity›`
Example: `"ais-90days-trial:static-saphir4-ch"`

* @param[in] szName Name of the signer.
This parameter is not used for certificate selection, but for the signature appearance and signature description in the
PDF only. Example: `"Signing Service TEST account"`


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForStaticIdentityW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_Session* pSession, const WCHAR* szIdentity, const WCHAR* szName);
/**
 * @brief Create a signature configuration for an on-demand certificate
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_Session.

* @param[in] szIdentity The Claimed Identity string as provided by Swisscom: `‹customer name›:‹key identity›`
Example: `"ais-90days-trial:OnDemand-Advanced4"`

* @param[in] szDistinguishedName The requested distinguished name of the on-demand certificate.
Example: `"cn=Hans Muster,o=ACME,c=CH"`

* @param[in,out] pStepUp Options for step-up authorization using Mobile ID.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForOnDemandIdentityA(
    TPdfToolsCryptoProvidersSwisscomSigSrv_Session* pSession, const char* szIdentity, const char* szDistinguishedName,
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp);
/**
 * @brief Create a signature configuration for an on-demand certificate
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_Session.

* @param[in] szIdentity The Claimed Identity string as provided by Swisscom: `‹customer name›:‹key identity›`
Example: `"ais-90days-trial:OnDemand-Advanced4"`

* @param[in] szDistinguishedName The requested distinguished name of the on-demand certificate.
Example: `"cn=Hans Muster,o=ACME,c=CH"`

* @param[in,out] pStepUp Options for step-up authorization using Mobile ID.


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_SignatureConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateSignatureForOnDemandIdentityW(
    TPdfToolsCryptoProvidersSwisscomSigSrv_Session* pSession, const WCHAR* szIdentity, const WCHAR* szDistinguishedName,
    TPdfToolsCryptoProvidersSwisscomSigSrv_StepUp* pStepUp);
/**
 * @brief Create a time-stamp configuration
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_Session.

* @param[in] szIdentity The Claimed Identity string as provided by Swisscom: `‹customer name›`
Example: `"ais-90days-trial"`


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateTimestampA(TPdfToolsCryptoProvidersSwisscomSigSrv_Session* pSession,
                                                               const char* szIdentity);
/**
 * @brief Create a time-stamp configuration
* @param[in,out] pSession Acts as a handle to the native object of type \ref
TPdfToolsCryptoProvidersSwisscomSigSrv_Session.

* @param[in] szIdentity The Claimed Identity string as provided by Swisscom: `‹customer name›`
Example: `"ais-90days-trial"`


 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCryptoProvidersSwisscomSigSrv_TimestampConfiguration* PDFTOOLS_CALL
PdfToolsCryptoProvidersSwisscomSigSrv_Session_CreateTimestampW(TPdfToolsCryptoProvidersSwisscomSigSrv_Session* pSession,
                                                               const WCHAR* szIdentity);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSCRYPTOPROVIDERSSWISSCOMSIGSRV_H__ */
