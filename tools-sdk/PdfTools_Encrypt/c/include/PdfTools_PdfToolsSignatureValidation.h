/******************************************************************************
 *
 * File:            PdfTools_PdfToolsSignatureValidation.h
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

#ifndef PDFTOOLS_PDFTOOLSSIGNATUREVALIDATION_H__
#define PDFTOOLS_PDFTOOLSSIGNATUREVALIDATION_H__

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
#define PdfToolsSignatureValidation_ConstraintResult_GetMessage PdfToolsSignatureValidation_ConstraintResult_GetMessageW

#define TPdfToolsSignatureValidation_Validator_Constraint TPdfToolsSignatureValidation_Validator_ConstraintW
#define PdfToolsSignatureValidation_Validator_AddConstraintHandler \
    PdfToolsSignatureValidation_Validator_AddConstraintHandlerW
#define PdfToolsSignatureValidation_Validator_RemoveConstraintHandler \
    PdfToolsSignatureValidation_Validator_RemoveConstraintHandlerW

#define PdfToolsSignatureValidation_Certificate_GetSubjectName PdfToolsSignatureValidation_Certificate_GetSubjectNameW

#define PdfToolsSignatureValidation_Certificate_GetSubject PdfToolsSignatureValidation_Certificate_GetSubjectW

#define PdfToolsSignatureValidation_Certificate_GetIssuerName PdfToolsSignatureValidation_Certificate_GetIssuerNameW

#define PdfToolsSignatureValidation_Certificate_GetFingerprint PdfToolsSignatureValidation_Certificate_GetFingerprintW

#define PdfToolsSignatureValidation_CustomTrustList_AddArchive PdfToolsSignatureValidation_CustomTrustList_AddArchiveW

#else
#define PdfToolsSignatureValidation_ConstraintResult_GetMessage PdfToolsSignatureValidation_ConstraintResult_GetMessageA

#define TPdfToolsSignatureValidation_Validator_Constraint TPdfToolsSignatureValidation_Validator_ConstraintA
#define PdfToolsSignatureValidation_Validator_AddConstraintHandler \
    PdfToolsSignatureValidation_Validator_AddConstraintHandlerA
#define PdfToolsSignatureValidation_Validator_RemoveConstraintHandler \
    PdfToolsSignatureValidation_Validator_RemoveConstraintHandlerA

#define PdfToolsSignatureValidation_Certificate_GetSubjectName PdfToolsSignatureValidation_Certificate_GetSubjectNameA

#define PdfToolsSignatureValidation_Certificate_GetSubject PdfToolsSignatureValidation_Certificate_GetSubjectA

#define PdfToolsSignatureValidation_Certificate_GetIssuerName PdfToolsSignatureValidation_Certificate_GetIssuerNameA

#define PdfToolsSignatureValidation_Certificate_GetFingerprint PdfToolsSignatureValidation_Certificate_GetFingerprintA

#define PdfToolsSignatureValidation_CustomTrustList_AddArchive PdfToolsSignatureValidation_CustomTrustList_AddArchiveA

#endif

/**
Report the result of a constraint validation of \ref PdfToolsSignatureValidation_Validator_Validate "".

* @param[in,out] pContext Context of the event callback.

* @param[in] szMessage The validation message

* @param[in] iIndication The main indication

* @param[in] iSubIndication The sub indication

* @param[in,out] pSignature The signature field

* @param[in] szDataPart The data part is `NULL` for constraints of the main signature and a path for constraints related
to elements of the signature. Examples:
  - `certificate:"Some Certificate"`: When validating a certificate "Some Certificate" of the main signature.
  - `time-stamp":Some TSA Responder"/certificate:"Intermediate TSA Responder Certificate"`: When validating a
certificate "Intermediate TSA Responder Certificate" of the time-stamp embedded into the main signature.


 */
typedef void(PDFTOOLS_CALL* TPdfToolsSignatureValidation_Validator_ConstraintA)(
    void* pContext, const char* szMessage, TPdfToolsSignatureValidation_Indication iIndication,
    TPdfToolsSignatureValidation_SubIndication iSubIndication, TPdfToolsPdf_SignedSignatureField* pSignature,
    const char* szDataPart);
/**
Report the result of a constraint validation of \ref PdfToolsSignatureValidation_Validator_Validate "".

* @param[in,out] pContext Context of the event callback.

* @param[in] szMessage The validation message

* @param[in] iIndication The main indication

* @param[in] iSubIndication The sub indication

* @param[in,out] pSignature The signature field

* @param[in] szDataPart The data part is `NULL` for constraints of the main signature and a path for constraints related
to elements of the signature. Examples:
  - `certificate:"Some Certificate"`: When validating a certificate "Some Certificate" of the main signature.
  - `time-stamp":Some TSA Responder"/certificate:"Intermediate TSA Responder Certificate"`: When validating a
certificate "Intermediate TSA Responder Certificate" of the time-stamp embedded into the main signature.


 */
typedef void(PDFTOOLS_CALL* TPdfToolsSignatureValidation_Validator_ConstraintW)(
    void* pContext, const WCHAR* szMessage, TPdfToolsSignatureValidation_Indication iIndication,
    TPdfToolsSignatureValidation_SubIndication iSubIndication, TPdfToolsPdf_SignedSignatureField* pSignature,
    const WCHAR* szDataPart);

/******************************************************************************
 * ConstraintResult
 *****************************************************************************/
/**
 * @brief The validation message
* @param[in,out] pConstraintResult Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_ConstraintResult.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_ConstraintResult_GetMessageA(
    TPdfToolsSignatureValidation_ConstraintResult* pConstraintResult, char* pBuffer, size_t nBufferSize);
/**
 * @brief The validation message
* @param[in,out] pConstraintResult Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_ConstraintResult.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_ConstraintResult_GetMessageW(
    TPdfToolsSignatureValidation_ConstraintResult* pConstraintResult, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The main indication
* @param[in,out] pConstraintResult Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_ConstraintResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_Indication PDFTOOLS_CALL
PdfToolsSignatureValidation_ConstraintResult_GetIndication(
    TPdfToolsSignatureValidation_ConstraintResult* pConstraintResult);
/**
 * @brief The sub indication
* @param[in,out] pConstraintResult Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_ConstraintResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_SubIndication PDFTOOLS_CALL
PdfToolsSignatureValidation_ConstraintResult_GetSubIndication(
    TPdfToolsSignatureValidation_ConstraintResult* pConstraintResult);

/******************************************************************************
 * Validator
 *****************************************************************************/
/**
 * @brief Adds event handler.
 *
 * @param[in,out] pValidator Pointer to the object to which the event handler is added.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is added.
 *
 * @return \ref TRUE if adding event handler was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_Validator_AddConstraintHandlerA(
    TPdfToolsSignatureValidation_Validator* pValidator, void* pContext,
    TPdfToolsSignatureValidation_Validator_ConstraintA pFunction);
/**
 * @brief Adds event handler.
 *
 * @param[in,out] pValidator Pointer to the object to which the event handler is added.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is added.
 *
 * @return \ref TRUE if adding event handler was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_Validator_AddConstraintHandlerW(
    TPdfToolsSignatureValidation_Validator* pValidator, void* pContext,
    TPdfToolsSignatureValidation_Validator_ConstraintW pFunction);
/**
 * @brief Removes event handler.
 *
 * @param[in,out] pValidator Pointer to the object from which the event handler is removed.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is removed.
 *
 * @return \ref TRUE if removal was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_Validator_RemoveConstraintHandlerA(
    TPdfToolsSignatureValidation_Validator* pValidator, void* pContext,
    TPdfToolsSignatureValidation_Validator_ConstraintA pFunction);
/**
 * @brief Removes event handler.
 *
 * @param[in,out] pValidator Pointer to the object from which the event handler is removed.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is removed.
 *
 * @return \ref TRUE if removal was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_Validator_RemoveConstraintHandlerW(
    TPdfToolsSignatureValidation_Validator* pValidator, void* pContext,
    TPdfToolsSignatureValidation_Validator_ConstraintW pFunction);

/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_Validator* PDFTOOLS_CALL PdfToolsSignatureValidation_Validator_New(void);

/**
 * @brief Validate the signatures of a PDF document
* @param[in,out] pValidator Acts as a handle to the native object of type \ref TPdfToolsSignatureValidation_Validator.

* @param[in,out] pDocument The document to check the signatures of

* @param[in,out] pProfile The validation profile

* @param[in] iSelector The signatures to validate


 * @return   The result of the validation

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_Processing The processing has failed.


 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_ValidationResults* PDFTOOLS_CALL
PdfToolsSignatureValidation_Validator_Validate(TPdfToolsSignatureValidation_Validator*        pValidator,
                                               TPdfToolsPdf_Document*                         pDocument,
                                               TPdfToolsSignatureValidationProfiles_Profile*  pProfile,
                                               TPdfToolsSignatureValidation_SignatureSelector iSelector);

/******************************************************************************
 * Certificate
 *****************************************************************************/
/**
 * @brief The name (subject) of the certificate
The common name (CN) of the person or authority that owns the certificate.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetSubjectNameA(
    TPdfToolsSignatureValidation_Certificate* pCertificate, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name (subject) of the certificate
The common name (CN) of the person or authority that owns the certificate.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetSubjectNameW(
    TPdfToolsSignatureValidation_Certificate* pCertificate, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The subject of the certificate
The distinguished name (DN) of the person or authority that owns the certificate.
Formatted according to RFC 4514.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetSubjectA(
    TPdfToolsSignatureValidation_Certificate* pCertificate, char* pBuffer, size_t nBufferSize);
/**
 * @brief The subject of the certificate
The distinguished name (DN) of the person or authority that owns the certificate.
Formatted according to RFC 4514.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetSubjectW(
    TPdfToolsSignatureValidation_Certificate* pCertificate, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the certificate's issuer (CA)
The common name (CN) of the certificate authority (CA) that issued the certificate.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetIssuerNameA(
    TPdfToolsSignatureValidation_Certificate* pCertificate, char* pBuffer, size_t nBufferSize);
/**
 * @brief The name of the certificate's issuer (CA)
The common name (CN) of the certificate authority (CA) that issued the certificate.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetIssuerNameW(
    TPdfToolsSignatureValidation_Certificate* pCertificate, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The date after which the certificate is no longer valid.
* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

* @param[out] pNotAfter Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetNotAfter(
    TPdfToolsSignatureValidation_Certificate* pCertificate, TPdfToolsSys_Date* pNotAfter);
/**
 * @brief The date on which the certificate becomes valid.
* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

* @param[out] pNotBefore Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetNotBefore(
    TPdfToolsSignatureValidation_Certificate* pCertificate, TPdfToolsSys_Date* pNotBefore);
/**
 * @brief The certificate's fingerprint
The hex string representation of the certificate’s SHA-1 digest.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetFingerprintA(
    TPdfToolsSignatureValidation_Certificate* pCertificate, char* pBuffer, size_t nBufferSize);
/**
 * @brief The certificate's fingerprint
The hex string representation of the certificate’s SHA-1 digest.

* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved string `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `0` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetFingerprintW(
    TPdfToolsSignatureValidation_Certificate* pCertificate, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The raw data of the certificate as a byte array
* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.

* @param[out] pBuffer Retrieved value.
To determine the required buffer size, the function has to be called with `NULL`.
The return value of this function specifies the buffer size.

* @param[in] nBufferSize The buffer size of the retrieved array `pBuffer`.


 * @return   The amount of data written to the buffer `pBuffer`.
   `-1` if there is an error.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsSignatureValidation_Certificate_GetRawData(
    TPdfToolsSignatureValidation_Certificate* pCertificate, unsigned char* pBuffer, size_t nBufferSize);
/**
 * @brief Source of the certificate
* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_DataSource PDFTOOLS_CALL
PdfToolsSignatureValidation_Certificate_GetSource(TPdfToolsSignatureValidation_Certificate* pCertificate);
/**
 * @brief Whether the certificate is valid according to the validation profile used
* @param[in,out] pCertificate Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_Certificate.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_ConstraintResult* PDFTOOLS_CALL
PdfToolsSignatureValidation_Certificate_GetValidity(TPdfToolsSignatureValidation_Certificate* pCertificate);

/******************************************************************************
 * CertificateChain
 *****************************************************************************/
/**
 * @brief Get the number of elements in the list.
* @param[in,out] pCertificateChain Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CertificateChain.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsSignatureValidation_CertificateChain_GetCount(TPdfToolsSignatureValidation_CertificateChain* pCertificateChain);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pCertificateChain Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CertificateChain.

* @param[in] iIndex

 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_Certificate* PDFTOOLS_CALL
PdfToolsSignatureValidation_CertificateChain_Get(TPdfToolsSignatureValidation_CertificateChain* pCertificateChain,
                                                 int                                            iIndex);

/**
 * @brief Whether all certificates of the chain are available
* @param[in,out] pCertificateChain Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CertificateChain.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_CertificateChain_IsComplete(
    TPdfToolsSignatureValidation_CertificateChain* pCertificateChain);

/******************************************************************************
 * ValidationResults
 *****************************************************************************/
/**
 * @brief Get the number of elements in the list.
* @param[in,out] pValidationResults Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_ValidationResults.


 * @return    May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL PdfToolsSignatureValidation_ValidationResults_GetCount(
    TPdfToolsSignatureValidation_ValidationResults* pValidationResults);
/**
 * @brief Returns the element at the specified position in the given list.
* @param[in,out] pValidationResults Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_ValidationResults.

* @param[in] iIndex

 * @return    `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalState
 * - \ref ePdfTools_Error_IllegalArgument
 * - \ref ePdfTools_Error_UnsupportedOperation

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_ValidationResult* PDFTOOLS_CALL
PdfToolsSignatureValidation_ValidationResults_Get(TPdfToolsSignatureValidation_ValidationResults* pValidationResults,
                                                  int                                             iIndex);

/******************************************************************************
 * ValidationResult
 *****************************************************************************/
/**
 * @brief The signature field
* @param[in,out] pValidationResult Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_ValidationResult.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_SignedSignatureField* PDFTOOLS_CALL
PdfToolsSignatureValidation_ValidationResult_GetSignatureField(
    TPdfToolsSignatureValidation_ValidationResult* pValidationResult);
/**
 * @brief The data and validation result of the cryptographic signature
* @param[in,out] pValidationResult Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_ValidationResult.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_SignatureContent* PDFTOOLS_CALL
PdfToolsSignatureValidation_ValidationResult_GetSignatureContent(
    TPdfToolsSignatureValidation_ValidationResult* pValidationResult);

/******************************************************************************
 * SignatureContent
 *****************************************************************************/
/**
 * @brief Whether the cryptographic signature is valid according to the validation profile used
* @param[in,out] pSignatureContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_SignatureContent.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_ConstraintResult* PDFTOOLS_CALL
PdfToolsSignatureValidation_SignatureContent_GetValidity(
    TPdfToolsSignatureValidation_SignatureContent* pSignatureContent);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsSignatureValidation_SignatureContent.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pSignatureContent Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsSignatureValidation_SignatureContentType that refers to the actual
 * derived type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_SignatureContentType PDFTOOLS_CALL
PdfToolsSignatureValidation_SignatureContent_GetType(TPdfToolsSignatureValidation_SignatureContent* pSignatureContent);
/******************************************************************************
 * CmsSignatureContent
 *****************************************************************************/
/**
 * @brief The time at which the signature has been validated
* @param[in,out] pCmsSignatureContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CmsSignatureContent.

* @param[out] pValidationTime Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_CmsSignatureContent_GetValidationTime(
    TPdfToolsSignatureValidation_CmsSignatureContent* pCmsSignatureContent, TPdfToolsSys_Date* pValidationTime);
/**
 * @brief The source for the validation time
* @param[in,out] pCmsSignatureContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CmsSignatureContent.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_TimeSource PDFTOOLS_CALL
PdfToolsSignatureValidation_CmsSignatureContent_GetValidationTimeSource(
    TPdfToolsSignatureValidation_CmsSignatureContent* pCmsSignatureContent);
/**
 * @brief The hash algorithm used to calculate the signature's message digest
* @param[in,out] pCmsSignatureContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CmsSignatureContent.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsSignatureValidation_CmsSignatureContent_GetHashAlgorithm(
    TPdfToolsSignatureValidation_CmsSignatureContent* pCmsSignatureContent);
/**
 * @brief The data and validation result of the embedded time-stamp
* @param[in,out] pCmsSignatureContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CmsSignatureContent.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_TimeStampContent* PDFTOOLS_CALL
PdfToolsSignatureValidation_CmsSignatureContent_GetTimeStamp(
    TPdfToolsSignatureValidation_CmsSignatureContent* pCmsSignatureContent);
/**
 * @brief The signing certificate
* @param[in,out] pCmsSignatureContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CmsSignatureContent.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_Certificate* PDFTOOLS_CALL
PdfToolsSignatureValidation_CmsSignatureContent_GetSigningCertificate(
    TPdfToolsSignatureValidation_CmsSignatureContent* pCmsSignatureContent);
/**
 * @brief The certificate chain of the signing certificate
* @param[in,out] pCmsSignatureContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CmsSignatureContent.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_CertificateChain* PDFTOOLS_CALL
PdfToolsSignatureValidation_CmsSignatureContent_GetCertificateChain(
    TPdfToolsSignatureValidation_CmsSignatureContent* pCmsSignatureContent);

/******************************************************************************
 * TimeStampContent
 *****************************************************************************/
/**
 * @brief The time at which the signature has been validated
* @param[in,out] pTimeStampContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_TimeStampContent.

* @param[out] pValidationTime Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_TimeStampContent_GetValidationTime(
    TPdfToolsSignatureValidation_TimeStampContent* pTimeStampContent, TPdfToolsSys_Date* pValidationTime);
/**
 * @brief The source for the validation time
* @param[in,out] pTimeStampContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_TimeStampContent.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_TimeSource PDFTOOLS_CALL
PdfToolsSignatureValidation_TimeStampContent_GetValidationTimeSource(
    TPdfToolsSignatureValidation_TimeStampContent* pTimeStampContent);
/**
 * @brief The hash algorithm used to calculate the signature's message digest
* @param[in,out] pTimeStampContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_TimeStampContent.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsCrypto_HashAlgorithm PDFTOOLS_CALL
PdfToolsSignatureValidation_TimeStampContent_GetHashAlgorithm(
    TPdfToolsSignatureValidation_TimeStampContent* pTimeStampContent);
/**
 * @brief The time-stamp time
* @param[in,out] pTimeStampContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_TimeStampContent.

* @param[out] pDate Retrieved value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_TimeStampContent_GetDate(
    TPdfToolsSignatureValidation_TimeStampContent* pTimeStampContent, TPdfToolsSys_Date* pDate);
/**
 * @brief The signing certificate
* @param[in,out] pTimeStampContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_TimeStampContent.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_Certificate* PDFTOOLS_CALL
PdfToolsSignatureValidation_TimeStampContent_GetSigningCertificate(
    TPdfToolsSignatureValidation_TimeStampContent* pTimeStampContent);
/**
 * @brief The certificate chain of the signing certificate
* @param[in,out] pTimeStampContent Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_TimeStampContent.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_CertificateChain* PDFTOOLS_CALL
PdfToolsSignatureValidation_TimeStampContent_GetCertificateChain(
    TPdfToolsSignatureValidation_TimeStampContent* pTimeStampContent);

/******************************************************************************
 * CustomTrustList
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_CustomTrustList* PDFTOOLS_CALL
PdfToolsSignatureValidation_CustomTrustList_New(void);

/**
 * @brief Add one or more certificates
Add certificates to the trust list.

* @param[in,out] pCustomTrustList Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CustomTrustList.

* @param[in] pCertificate The sequence of certificates in either PEM (.pem, ASCII text) or DER (.cer, binary) form


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt If the certificate is corrupt and cannot be read


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_CustomTrustList_AddCertificates(
    TPdfToolsSignatureValidation_CustomTrustList* pCustomTrustList, const TPdfToolsSys_StreamDescriptor* pCertificate);
/**
 * @brief Add certificates from a PFX (PKCS#12) archive
Add certificates to the trust list.

* @param[in,out] pCustomTrustList Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CustomTrustList.

* @param[in] pStreamDesc The certificates in PKCS#12 format (.p12, .pfx)

* @param[in] szPassword The password required to decrypt the archive.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The PFX (PKCS#12) archive is corrupt and cannot be read.

 * - \ref ePdfTools_Error_Password The password is invalid.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_CustomTrustList_AddArchiveA(
    TPdfToolsSignatureValidation_CustomTrustList* pCustomTrustList, const TPdfToolsSys_StreamDescriptor* pStreamDesc,
    const char* szPassword);
/**
 * @brief Add certificates from a PFX (PKCS#12) archive
Add certificates to the trust list.

* @param[in,out] pCustomTrustList Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidation_CustomTrustList.

* @param[in] pStreamDesc The certificates in PKCS#12 format (.p12, .pfx)

* @param[in] szPassword The password required to decrypt the archive.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_Corrupt The PFX (PKCS#12) archive is corrupt and cannot be read.

 * - \ref ePdfTools_Error_Password The password is invalid.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidation_CustomTrustList_AddArchiveW(
    TPdfToolsSignatureValidation_CustomTrustList* pCustomTrustList, const TPdfToolsSys_StreamDescriptor* pStreamDesc,
    const WCHAR* szPassword);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSSIGNATUREVALIDATION_H__ */
