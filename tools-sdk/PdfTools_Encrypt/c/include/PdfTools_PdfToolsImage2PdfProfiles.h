/******************************************************************************
 *
 * File:            PdfTools_PdfToolsImage2PdfProfiles.h
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

#ifndef PDFTOOLS_PDFTOOLSIMAGE2PDFPROFILES_H__
#define PDFTOOLS_PDFTOOLSIMAGE2PDFPROFILES_H__

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
#define PdfToolsImage2PdfProfiles_Archive_GetLanguage PdfToolsImage2PdfProfiles_Archive_GetLanguageW
#define PdfToolsImage2PdfProfiles_Archive_SetLanguage PdfToolsImage2PdfProfiles_Archive_SetLanguageW

#else
#define PdfToolsImage2PdfProfiles_Archive_GetLanguage PdfToolsImage2PdfProfiles_Archive_GetLanguageA
#define PdfToolsImage2PdfProfiles_Archive_SetLanguage PdfToolsImage2PdfProfiles_Archive_SetLanguageA

#endif

/******************************************************************************
 * Profile
 *****************************************************************************/
/**
 * @brief The image conversion options
* @param[in,out] pProfile Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Profile.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2Pdf_ImageOptions* PDFTOOLS_CALL
PdfToolsImage2PdfProfiles_Profile_GetImageOptions(TPdfToolsImage2PdfProfiles_Profile* pProfile);

/**
 * @brief Get actual derived type of base type \ref TPdfToolsImage2PdfProfiles_Profile.
 *
 * This function is invoked prior to downcasting to ascertain the derived object type.
 *
 * @param[in,out] pProfile Acts as a handle to a native object.
 *
 * @return The item of the enumeration \ref TPdfToolsImage2PdfProfiles_ProfileType that refers to the actual derived
 * type. `0` in case of an error.
 *
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 *       Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT TPdfToolsImage2PdfProfiles_ProfileType PDFTOOLS_CALL
PdfToolsImage2PdfProfiles_Profile_GetType(TPdfToolsImage2PdfProfiles_Profile* pProfile);
/******************************************************************************
 * Default
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2PdfProfiles_Default* PDFTOOLS_CALL PdfToolsImage2PdfProfiles_Default_New(void);

/**
 * @brief The PDF conformance of the output document

All PDF conformances are supported.
For PDF/A the \ref TPdfToolsImage2PdfProfiles_Archive "" profile must be used.

Default value: "PDF 1.7"

* @param[in,out] pDefault Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Default.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The conformance is PDF/A but must be PDF for this profile.
Use the profile \ref TPdfToolsImage2PdfProfiles_Archive "" to create PDF/A documents.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Conformance PDFTOOLS_CALL
PdfToolsImage2PdfProfiles_Default_GetConformance(TPdfToolsImage2PdfProfiles_Default* pDefault);
/**
 * @brief The PDF conformance of the output document

All PDF conformances are supported.
For PDF/A the \ref TPdfToolsImage2PdfProfiles_Archive "" profile must be used.

Default value: "PDF 1.7"

* @param[in,out] pDefault Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Default.

* @param[in] iConformance Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The conformance is PDF/A but must be PDF for this profile.
Use the profile \ref TPdfToolsImage2PdfProfiles_Archive "" to create PDF/A documents.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2PdfProfiles_Default_SetConformance(
    TPdfToolsImage2PdfProfiles_Default* pDefault, TPdfToolsPdf_Conformance iConformance);

/******************************************************************************
 * Archive
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsImage2PdfProfiles_Archive* PDFTOOLS_CALL PdfToolsImage2PdfProfiles_Archive_New(void);

/**
 * @brief The PDF/A conformance of the output document

The supported PDF/A conformance are:
  - "PDF/A-1b"
  - "PDF/A-1a"
  - "PDF/A-2b"
  - "PDF/A-2u"
  - "PDF/A-2a"
  - "PDF/A-3b"
  - "PDF/A-3u"
  - "PDF/A-3a"
With level A conformances (PDF/A-1a, PDF/A-2a, PDF/A-3a),
the properties \ref PdfToolsImage2PdfProfiles_Archive_GetAlternateText ""
and \ref PdfToolsImage2PdfProfiles_Archive_GetLanguage "" must be set.

Default value: "PDF/A-2b"

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Archive.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The conformance is PDF but must be PDF/A for this profile.
Use the profile \ref TPdfToolsImage2PdfProfiles_Default "" to create PDF documents.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Conformance PDFTOOLS_CALL
PdfToolsImage2PdfProfiles_Archive_GetConformance(TPdfToolsImage2PdfProfiles_Archive* pArchive);
/**
 * @brief The PDF/A conformance of the output document

The supported PDF/A conformance are:
  - "PDF/A-1b"
  - "PDF/A-1a"
  - "PDF/A-2b"
  - "PDF/A-2u"
  - "PDF/A-2a"
  - "PDF/A-3b"
  - "PDF/A-3u"
  - "PDF/A-3a"
With level A conformances (PDF/A-1a, PDF/A-2a, PDF/A-3a),
the properties \ref PdfToolsImage2PdfProfiles_Archive_GetAlternateText ""
and \ref PdfToolsImage2PdfProfiles_Archive_GetLanguage "" must be set.

Default value: "PDF/A-2b"

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Archive.

* @param[in] iConformance Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_IllegalArgument The conformance is PDF but must be PDF/A for this profile.
Use the profile \ref TPdfToolsImage2PdfProfiles_Default "" to create PDF documents.


 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2PdfProfiles_Archive_SetConformance(
    TPdfToolsImage2PdfProfiles_Archive* pArchive, TPdfToolsPdf_Conformance iConformance);
/**
 * @brief The alternate text describing the image

The alternate text provides a meaningful description of the images.
For example, "This color image shows a small sailing boat at sunset".
This information can be used to read the document to the visually impaired.

The list must contain a description for each page of the input image document.
For the conversion of \ref TPdfToolsImage_SinglePageDocument "", a single description
is sufficient. For \ref TPdfToolsImage_MultiPageDocument "", multiple descriptions may be
required.

Alternate text is required for PDF/A level A conformance.
It is not advisable to add "dummy" tagging solely for the purpose of achieving level A
conformance. Instead, for scanned text documents, the Conversion Service can be used to
recognize the characters in the documents (OCR) and tag the image with the recognized structure and text.
For other types of images, such as photos, logos or graphics, alternate text descriptions
should be written manually by a user.

Default: empty list

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Archive.


 * @return   Retrieved value.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfTools_StringList* PDFTOOLS_CALL
PdfToolsImage2PdfProfiles_Archive_GetAlternateText(TPdfToolsImage2PdfProfiles_Archive* pArchive);
/**
 * @brief The alternate text describing the image

The alternate text provides a meaningful description of the images.
For example, "This color image shows a small sailing boat at sunset".
This information can be used to read the document to the visually impaired.

The list must contain a description for each page of the input image document.
For the conversion of \ref TPdfToolsImage_SinglePageDocument "", a single description
is sufficient. For \ref TPdfToolsImage_MultiPageDocument "", multiple descriptions may be
required.

Alternate text is required for PDF/A level A conformance.
It is not advisable to add "dummy" tagging solely for the purpose of achieving level A
conformance. Instead, for scanned text documents, the Conversion Service can be used to
recognize the characters in the documents (OCR) and tag the image with the recognized structure and text.
For other types of images, such as photos, logos or graphics, alternate text descriptions
should be written manually by a user.

Default: empty list

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Archive.

* @param[in,out] pAlternateText Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsImage2PdfProfiles_Archive_SetAlternateText(
    TPdfToolsImage2PdfProfiles_Archive* pArchive, TPdfTools_StringList* pAlternateText);
/**
 * @brief The language of the output PDF

The language code that specifies the language of the PDF and specifically
its \ref PdfToolsImage2PdfProfiles_Archive_GetAlternateText "" descriptions.
Specifying the language is highly recommended for PDF/A level A conformance.

The codes are defined in BCP 47 and ISO 3166:2013 and can
be obtained from the Internet Engineering Task Force and
the International Organization for Standardization.

If no code is set, the language will be specified as
unknown.

Examples:
  - "en"
  - "en-US"
  - "de"
  - "de-CH"
  - "fr-FR"
  - "zxx" (for non linguistic content)

Default: `NULL` (unknown)

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Archive.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsImage2PdfProfiles_Archive_GetLanguageA(
    TPdfToolsImage2PdfProfiles_Archive* pArchive, char* pBuffer, size_t nBufferSize);
/**
 * @brief The language of the output PDF

The language code that specifies the language of the PDF and specifically
its \ref PdfToolsImage2PdfProfiles_Archive_GetAlternateText "" descriptions.
Specifying the language is highly recommended for PDF/A level A conformance.

The codes are defined in BCP 47 and ISO 3166:2013 and can
be obtained from the Internet Engineering Task Force and
the International Organization for Standardization.

If no code is set, the language will be specified as
unknown.

Examples:
  - "en"
  - "en-US"
  - "de"
  - "de-CH"
  - "fr-FR"
  - "zxx" (for non linguistic content)

Default: `NULL` (unknown)

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Archive.

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
PDFTOOLS_EXPORT size_t PDFTOOLS_CALL PdfToolsImage2PdfProfiles_Archive_GetLanguageW(
    TPdfToolsImage2PdfProfiles_Archive* pArchive, WCHAR* pBuffer, size_t nBufferSize);
/**
 * @brief The language of the output PDF

The language code that specifies the language of the PDF and specifically
its \ref PdfToolsImage2PdfProfiles_Archive_GetAlternateText "" descriptions.
Specifying the language is highly recommended for PDF/A level A conformance.

The codes are defined in BCP 47 and ISO 3166:2013 and can
be obtained from the Internet Engineering Task Force and
the International Organization for Standardization.

If no code is set, the language will be specified as
unknown.

Examples:
  - "en"
  - "en-US"
  - "de"
  - "de-CH"
  - "fr-FR"
  - "zxx" (for non linguistic content)

Default: `NULL` (unknown)

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Archive.

* @param[in] szLanguage Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsImage2PdfProfiles_Archive_SetLanguageA(TPdfToolsImage2PdfProfiles_Archive* pArchive, const char* szLanguage);
/**
 * @brief The language of the output PDF

The language code that specifies the language of the PDF and specifically
its \ref PdfToolsImage2PdfProfiles_Archive_GetAlternateText "" descriptions.
Specifying the language is highly recommended for PDF/A level A conformance.

The codes are defined in BCP 47 and ISO 3166:2013 and can
be obtained from the Internet Engineering Task Force and
the International Organization for Standardization.

If no code is set, the language will be specified as
unknown.

Examples:
  - "en"
  - "en-US"
  - "de"
  - "de-CH"
  - "fr-FR"
  - "zxx" (for non linguistic content)

Default: `NULL` (unknown)

* @param[in,out] pArchive Acts as a handle to the native object of type \ref TPdfToolsImage2PdfProfiles_Archive.

* @param[in] szLanguage Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsImage2PdfProfiles_Archive_SetLanguageW(TPdfToolsImage2PdfProfiles_Archive* pArchive, const WCHAR* szLanguage);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSIMAGE2PDFPROFILES_H__ */
