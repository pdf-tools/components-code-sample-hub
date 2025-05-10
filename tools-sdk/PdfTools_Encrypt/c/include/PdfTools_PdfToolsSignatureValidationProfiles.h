/******************************************************************************
 *
 * File:            PdfTools_PdfToolsSignatureValidationProfiles.h
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

#ifndef PDFTOOLS_PDFTOOLSSIGNATUREVALIDATIONPROFILES_H__
#define PDFTOOLS_PDFTOOLSSIGNATUREVALIDATIONPROFILES_H__

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
 * Profile
 *****************************************************************************/
/**
 * @brief Signature validation options
* @param[in,out] pProfile Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_Profile.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidationProfiles_ValidationOptions* PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_Profile_GetValidationOptions(
    TPdfToolsSignatureValidationProfiles_Profile* pProfile);
/**
 * @brief Trust constraints for certificates of signatures
* @param[in,out] pProfile Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_Profile.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidationProfiles_TrustConstraints* PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_Profile_GetSigningCertTrustConstraints(
    TPdfToolsSignatureValidationProfiles_Profile* pProfile);
/**
 * @brief Trust constraints for certificates of time-stamps
* @param[in,out] pProfile Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_Profile.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidationProfiles_TrustConstraints* PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_Profile_GetTimeStampTrustConstraints(
    TPdfToolsSignatureValidationProfiles_Profile* pProfile);
/**
 * @brief The custom list of trusted certificates
Default: `NULL` (no custom trust list)

* @param[in,out] pProfile Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_Profile.


 * @return   Retrieved value.

  `NULL` if either an error occurred or the returned object is actually `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when `NULL` was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError is
different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_CustomTrustList* PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_Profile_GetCustomTrustList(TPdfToolsSignatureValidationProfiles_Profile* pProfile);
/**
 * @brief The custom list of trusted certificates
Default: `NULL` (no custom trust list)

* @param[in,out] pProfile Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_Profile.

* @param[in,out] pCustomTrustList Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidationProfiles_Profile_SetCustomTrustList(
    TPdfToolsSignatureValidationProfiles_Profile* pProfile,
    TPdfToolsSignatureValidation_CustomTrustList* pCustomTrustList);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsSignatureValidationProfiles_Profile.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pProfile Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsSignatureValidationProfiles_ProfileType that refers to the actual
 * derived type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidationProfiles_ProfileType PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_Profile_GetType(TPdfToolsSignatureValidationProfiles_Profile* pProfile);
/******************************************************************************
 * ValidationOptions
 *****************************************************************************/
/**
 * @brief Allowed validation time sources
* @param[in,out] pValidationOptions Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_ValidationOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_TimeSource PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_ValidationOptions_GetTimeSource(
    TPdfToolsSignatureValidationProfiles_ValidationOptions* pValidationOptions);
/**
 * @brief Allowed validation time sources
* @param[in,out] pValidationOptions Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_ValidationOptions.

* @param[in] iTimeSource Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidationProfiles_ValidationOptions_SetTimeSource(
    TPdfToolsSignatureValidationProfiles_ValidationOptions* pValidationOptions,
    TPdfToolsSignatureValidation_TimeSource                 iTimeSource);
/**
 * @brief Allowed sources to get certificates, e.g. intermediate issuer certificates
* @param[in,out] pValidationOptions Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_ValidationOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_DataSource PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_ValidationOptions_GetCertificateSources(
    TPdfToolsSignatureValidationProfiles_ValidationOptions* pValidationOptions);
/**
 * @brief Allowed sources to get certificates, e.g. intermediate issuer certificates
* @param[in,out] pValidationOptions Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_ValidationOptions.

* @param[in] iCertificateSources Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidationProfiles_ValidationOptions_SetCertificateSources(
    TPdfToolsSignatureValidationProfiles_ValidationOptions* pValidationOptions,
    TPdfToolsSignatureValidation_DataSource                 iCertificateSources);
/**
 * @brief Allowed sources to get revocation information (OCSP, CRL)
* @param[in,out] pValidationOptions Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_ValidationOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_DataSource PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_ValidationOptions_GetRevocationInformationSources(
    TPdfToolsSignatureValidationProfiles_ValidationOptions* pValidationOptions);
/**
 * @brief Allowed sources to get revocation information (OCSP, CRL)
* @param[in,out] pValidationOptions Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_ValidationOptions.

* @param[in] iRevocationInformationSources Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_ValidationOptions_SetRevocationInformationSources(
    TPdfToolsSignatureValidationProfiles_ValidationOptions* pValidationOptions,
    TPdfToolsSignatureValidation_DataSource                 iRevocationInformationSources);

/******************************************************************************
 * TrustConstraints
 *****************************************************************************/
/**
 * @brief Allowed sources for trusted certificates
Note that the trust sources are implicitly added to the profile's \ref
PdfToolsSignatureValidationProfiles_ValidationOptions_GetCertificateSources "".

* @param[in,out] pTrustConstraints Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_TrustConstraints.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidation_DataSource PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_TrustConstraints_GetTrustSources(
    TPdfToolsSignatureValidationProfiles_TrustConstraints* pTrustConstraints);
/**
 * @brief Allowed sources for trusted certificates
Note that the trust sources are implicitly added to the profile's \ref
PdfToolsSignatureValidationProfiles_ValidationOptions_GetCertificateSources "".

* @param[in,out] pTrustConstraints Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_TrustConstraints.

* @param[in] iTrustSources Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidationProfiles_TrustConstraints_SetTrustSources(
    TPdfToolsSignatureValidationProfiles_TrustConstraints* pTrustConstraints,
    TPdfToolsSignatureValidation_DataSource                iTrustSources);
/**
 * @brief Whether to check certificate revocation
* @param[in,out] pTrustConstraints Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_TrustConstraints.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidationProfiles_RevocationCheckPolicy PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_TrustConstraints_GetRevocationCheckPolicy(
    TPdfToolsSignatureValidationProfiles_TrustConstraints* pTrustConstraints);
/**
 * @brief Whether to check certificate revocation
* @param[in,out] pTrustConstraints Acts as a handle to the native object of type \ref
TPdfToolsSignatureValidationProfiles_TrustConstraints.

* @param[in] iRevocationCheckPolicy Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSignatureValidationProfiles_TrustConstraints_SetRevocationCheckPolicy(
    TPdfToolsSignatureValidationProfiles_TrustConstraints*     pTrustConstraints,
    TPdfToolsSignatureValidationProfiles_RevocationCheckPolicy iRevocationCheckPolicy);

/******************************************************************************
 * Default
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsSignatureValidationProfiles_Default* PDFTOOLS_CALL
PdfToolsSignatureValidationProfiles_Default_New(void);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSSIGNATUREVALIDATIONPROFILES_H__ */
