/******************************************************************************
 *
 * File:            PdfTools_PdfToolsPdfAValidation.h
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

#ifndef PDFTOOLS_PDFTOOLSPDFAVALIDATION_H__
#define PDFTOOLS_PDFTOOLSPDFAVALIDATION_H__

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
#define TPdfToolsPdfAValidation_Validator_Error             TPdfToolsPdfAValidation_Validator_ErrorW
#define PdfToolsPdfAValidation_Validator_AddErrorHandler    PdfToolsPdfAValidation_Validator_AddErrorHandlerW
#define PdfToolsPdfAValidation_Validator_RemoveErrorHandler PdfToolsPdfAValidation_Validator_RemoveErrorHandlerW

#else
#define TPdfToolsPdfAValidation_Validator_Error             TPdfToolsPdfAValidation_Validator_ErrorA
#define PdfToolsPdfAValidation_Validator_AddErrorHandler    PdfToolsPdfAValidation_Validator_AddErrorHandlerA
#define PdfToolsPdfAValidation_Validator_RemoveErrorHandler PdfToolsPdfAValidation_Validator_RemoveErrorHandlerA

#endif

/**
Report a validation issue found in \ref PdfToolsPdfAValidation_Validator_Analyze "" or \ref
PdfToolsPdfAValidation_Validator_Validate "".

* @param[in,out] pContext Context of the event callback.

* @param[in] szDataPart The data part is `NULL` for the main file and a data part specification for embedded files.
Examples:
  - `embedded-file:file.pdf`: For a file `file.pdf` that is embedded in the main file.
  - `embedded-file:file1.pdf/embedded-file:file2.pdf`: For a file `file2.pdf` that is embedded in an embedded file
`file1.pdf`.

* @param[in] szMessage The validation message

* @param[in] iCategory The category of the validation error

* @param[in] szContext A description of the context where the error occurred

* @param[in] iPageNo The page number this error is associated to or `0`

* @param[in] iObjectNo The number of the PDF object this error is associated to


 */
typedef void(PDFTOOLS_CALL* TPdfToolsPdfAValidation_Validator_ErrorA)(void* pContext, const char* szDataPart,
                                                                      const char*                           szMessage,
                                                                      TPdfToolsPdfAValidation_ErrorCategory iCategory,
                                                                      const char* szContext, int iPageNo,
                                                                      int iObjectNo);
/**
Report a validation issue found in \ref PdfToolsPdfAValidation_Validator_Analyze "" or \ref
PdfToolsPdfAValidation_Validator_Validate "".

* @param[in,out] pContext Context of the event callback.

* @param[in] szDataPart The data part is `NULL` for the main file and a data part specification for embedded files.
Examples:
  - `embedded-file:file.pdf`: For a file `file.pdf` that is embedded in the main file.
  - `embedded-file:file1.pdf/embedded-file:file2.pdf`: For a file `file2.pdf` that is embedded in an embedded file
`file1.pdf`.

* @param[in] szMessage The validation message

* @param[in] iCategory The category of the validation error

* @param[in] szContext A description of the context where the error occurred

* @param[in] iPageNo The page number this error is associated to or `0`

* @param[in] iObjectNo The number of the PDF object this error is associated to


 */
typedef void(PDFTOOLS_CALL* TPdfToolsPdfAValidation_Validator_ErrorW)(void* pContext, const WCHAR* szDataPart,
                                                                      const WCHAR*                          szMessage,
                                                                      TPdfToolsPdfAValidation_ErrorCategory iCategory,
                                                                      const WCHAR* szContext, int iPageNo,
                                                                      int iObjectNo);

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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAValidation_Validator_AddErrorHandlerA(
    TPdfToolsPdfAValidation_Validator* pValidator, void* pContext, TPdfToolsPdfAValidation_Validator_ErrorA pFunction);
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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAValidation_Validator_AddErrorHandlerW(
    TPdfToolsPdfAValidation_Validator* pValidator, void* pContext, TPdfToolsPdfAValidation_Validator_ErrorW pFunction);
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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAValidation_Validator_RemoveErrorHandlerA(
    TPdfToolsPdfAValidation_Validator* pValidator, void* pContext, TPdfToolsPdfAValidation_Validator_ErrorA pFunction);
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
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAValidation_Validator_RemoveErrorHandlerW(
    TPdfToolsPdfAValidation_Validator* pValidator, void* pContext, TPdfToolsPdfAValidation_Validator_ErrorW pFunction);

/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdfAValidation_Validator* PDFTOOLS_CALL PdfToolsPdfAValidation_Validator_New(void);

/**
 * @brief Validate the standards conformance of a PDF document.
* @param[in,out] pValidator Acts as a handle to the native object of type \ref TPdfToolsPdfAValidation_Validator.

* @param[in,out] pDocument The document to check the quality of

* @param[in,out] pOptions The options or `NULL` for default validation options


 * @return   The result of the validation

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_Processing The processing has failed.


 */
PDFTOOLS_EXPORT TPdfToolsPdfAValidation_ValidationResult* PDFTOOLS_CALL PdfToolsPdfAValidation_Validator_Validate(
    TPdfToolsPdfAValidation_Validator* pValidator, TPdfToolsPdf_Document* pDocument,
    TPdfToolsPdfAValidation_ValidationOptions* pOptions);
/**
 * @brief Analyze a PDF document in preparation for its conversion to PDF/A.
This method validates the document's standards conformance like \ref PdfToolsPdfAValidation_Validator_Validate "".
In addition to that, certain additional checks can be performed.
However, the main difference is that the analysis result can be used in \ref PdfToolsPdfAConversion_Converter_Convert ""
to convert the PDF document to PDF/A.

* @param[in,out] pValidator Acts as a handle to the native object of type \ref TPdfToolsPdfAValidation_Validator.

* @param[in,out] pDocument The document to analyze

* @param[in,out] pOptions The options or `NULL` for default analysis options


 * @return   The result of the analysis

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IllegalArgument The conformance of the <b>pOptions</b> argument is not PDF/A.


 */
PDFTOOLS_EXPORT TPdfToolsPdfAValidation_AnalysisResult* PDFTOOLS_CALL PdfToolsPdfAValidation_Validator_Analyze(
    TPdfToolsPdfAValidation_Validator* pValidator, TPdfToolsPdf_Document* pDocument,
    TPdfToolsPdfAValidation_AnalysisOptions* pOptions);

/******************************************************************************
 * ValidationOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdfAValidation_ValidationOptions* PDFTOOLS_CALL
PdfToolsPdfAValidation_ValidationOptions_New(void);

/**
 * @brief The conformance to be validated

The required conformance or `NULL` to validate the document's claimed conformance, i.e. \ref
PdfToolsPdf_Document_GetConformance "".

The PDF validation verifies if the input document conforms to all standards associated with this conformance.

Note that it is generally only meaningful to validate the claimed conformance of a document.

Default value: `NULL`, i.e. validate the document's claimed conformance.

* @param[in,out] pValidationOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_ValidationOptions.

* @param[out] pConformance Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAValidation_ValidationOptions_GetConformance(
    TPdfToolsPdfAValidation_ValidationOptions* pValidationOptions, TPdfToolsPdf_Conformance* pConformance);
/**
 * @brief The conformance to be validated

The required conformance or `NULL` to validate the document's claimed conformance, i.e. \ref
PdfToolsPdf_Document_GetConformance "".

The PDF validation verifies if the input document conforms to all standards associated with this conformance.

Note that it is generally only meaningful to validate the claimed conformance of a document.

Default value: `NULL`, i.e. validate the document's claimed conformance.

* @param[in,out] pValidationOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_ValidationOptions.

* @param[in] pConformance Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAValidation_ValidationOptions_SetConformance(
    TPdfToolsPdfAValidation_ValidationOptions* pValidationOptions, const TPdfToolsPdf_Conformance* pConformance);

/******************************************************************************
 * ValidationResult
 *****************************************************************************/
/**
 * @brief The validated conformance
* @param[in,out] pValidationResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_ValidationResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Conformance PDFTOOLS_CALL
PdfToolsPdfAValidation_ValidationResult_GetConformance(TPdfToolsPdfAValidation_ValidationResult* pValidationResult);
/**
 * @brief Whether the document is conforming
Whether the document conforms to all standards referenced to the \ref
PdfToolsPdfAValidation_ValidationResult_GetConformance "". Any issues found are reported as \ref
TPdfToolsPdfAValidation_Validator_Error "".

* @param[in,out] pValidationResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_ValidationResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdfAValidation_ValidationResult_IsConforming(TPdfToolsPdfAValidation_ValidationResult* pValidationResult);

/******************************************************************************
 * AnalysisOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdfAValidation_AnalysisOptions* PDFTOOLS_CALL PdfToolsPdfAValidation_AnalysisOptions_New(void);

/**
 * @brief The PDF/A conformance to validate

It is recommended to use:
  - The input document's claimed conformance \ref PdfToolsPdf_Document_GetConformance "", if it is an acceptable
conversion conformance. No conversion is needed, if the analysis result's property \ref
PdfToolsPdfAValidation_AnalysisResult_IsConversionRecommended "" is \ref "FALSE".
  - PDF/A-2b for the conversion to PDF/A-2. This is the recommended value for all other input documents.
  - PDF/A-3b for the conversion to PDF/A-3
  - PDF/A-1b for the conversion to PDF/A-1

Default: "PDF/A-2b"

* @param[in,out] pAnalysisOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Conformance PDFTOOLS_CALL
PdfToolsPdfAValidation_AnalysisOptions_GetConformance(TPdfToolsPdfAValidation_AnalysisOptions* pAnalysisOptions);
/**
 * @brief The PDF/A conformance to validate

It is recommended to use:
  - The input document's claimed conformance \ref PdfToolsPdf_Document_GetConformance "", if it is an acceptable
conversion conformance. No conversion is needed, if the analysis result's property \ref
PdfToolsPdfAValidation_AnalysisResult_IsConversionRecommended "" is \ref "FALSE".
  - PDF/A-2b for the conversion to PDF/A-2. This is the recommended value for all other input documents.
  - PDF/A-3b for the conversion to PDF/A-3
  - PDF/A-1b for the conversion to PDF/A-1

Default: "PDF/A-2b"

* @param[in,out] pAnalysisOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisOptions.

* @param[in] iConformance Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAValidation_AnalysisOptions_SetConformance(
    TPdfToolsPdfAValidation_AnalysisOptions* pAnalysisOptions, TPdfToolsPdf_Conformance iConformance);
/**
 * @brief Whether to enable additional, strict validation checks

Whether to check for potential issues that are corner cases of the PDF/A ISO Standard in which a conversion is strongly
advised. Also see the documentation of \ref PdfToolsPdfAValidation_AnalysisResult_IsConversionRecommended "".

Default: \ref "TRUE"

* @param[in,out] pAnalysisOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdfAValidation_AnalysisOptions_GetStrictMode(TPdfToolsPdfAValidation_AnalysisOptions* pAnalysisOptions);
/**
 * @brief Whether to enable additional, strict validation checks

Whether to check for potential issues that are corner cases of the PDF/A ISO Standard in which a conversion is strongly
advised. Also see the documentation of \ref PdfToolsPdfAValidation_AnalysisResult_IsConversionRecommended "".

Default: \ref "TRUE"

* @param[in,out] pAnalysisOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisOptions.

* @param[in] bStrictMode Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAValidation_AnalysisOptions_SetStrictMode(
    TPdfToolsPdfAValidation_AnalysisOptions* pAnalysisOptions, BOOL bStrictMode);

/******************************************************************************
 * AnalysisResult
 *****************************************************************************/
/**
 * @brief The conformance used for analysis

The PDF/A level might differ from the \ref PdfToolsPdfAValidation_AnalysisOptions_GetConformance "".
If the claimed PDF/A level of the input document is higher than  \ref
PdfToolsPdfAValidation_AnalysisOptions_GetConformance "", the higher level is used for \ref
PdfToolsPdfAValidation_AnalysisResult_GetConformance "".

For example, if  \ref PdfToolsPdfAValidation_AnalysisOptions_GetConformance "" is PDF/A-2b, but the document's claimed
conformance is PDF/A-2u, the analysis checks if the document actually conforms to its claimed conformance PDF/A-2u.
Because otherwise a conversion is required.

* @param[in,out] pAnalysisResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Conformance PDFTOOLS_CALL
PdfToolsPdfAValidation_AnalysisResult_GetConformance(TPdfToolsPdfAValidation_AnalysisResult* pAnalysisResult);
/**
 * @brief The recommended conversion conformance
The optimal PDF/A conformance for the conversion (i.e. the \ref PdfToolsPdfAConversion_ConversionOptions_GetConformance
""). The recommended conformance level might be higher than the analysis conformance, if the document actually contains
all data required for the higher level. It might also be lower, if the document is missing some required data.

* @param[in,out] pAnalysisResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `0` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdf_Conformance PDFTOOLS_CALL PdfToolsPdfAValidation_AnalysisResult_GetRecommendedConformance(
    TPdfToolsPdfAValidation_AnalysisResult* pAnalysisResult);
/**
 * @brief Whether the document should be converted to PDF/A

A conversion is generally recommended in the following cases:
  - If \ref PdfToolsPdfAValidation_AnalysisResult_IsConforming "" is \ref "FALSE", i.e. if the document does not conform
to the \ref PdfToolsPdfAValidation_AnalysisResult_GetConformance "".
  - If the document is conforming, but other issues are found for which a conversion is highly recommended.
For example, if certain corner cases of the specification are detected.

Note that in certain processes it might also be beneficial to convert a document if its conformance does not match the
\ref PdfToolsPdfAValidation_AnalysisResult_GetRecommendedConformance "". This will actually upgrade the PDF/A level of
the input document.

* @param[in,out] pAnalysisResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdfAValidation_AnalysisResult_IsConversionRecommended(TPdfToolsPdfAValidation_AnalysisResult* pAnalysisResult);
/**
 * @brief Whether the document is conforming
Whether the document conforms to the \ref PdfToolsPdfAValidation_AnalysisResult_GetConformance "".
Note that even if this property returns \ref "TRUE" a conversion might still be recommended as indicated by \ref
PdfToolsPdfAValidation_AnalysisResult_IsConversionRecommended "".

* @param[in,out] pAnalysisResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdfAValidation_AnalysisResult_IsConforming(TPdfToolsPdfAValidation_AnalysisResult* pAnalysisResult);
/**
 * @brief Whether the document is digitally signed
* @param[in,out] pAnalysisResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdfAValidation_AnalysisResult_IsSigned(TPdfToolsPdfAValidation_AnalysisResult* pAnalysisResult);
/**
 * @brief Whether the document contains embedded files
* @param[in,out] pAnalysisResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdfAValidation_AnalysisResult_GetHasEmbeddedFiles(TPdfToolsPdfAValidation_AnalysisResult* pAnalysisResult);
/**
 * @brief The number of fonts used in the document
* @param[in,out] pAnalysisResult Acts as a handle to the native object of type \ref
TPdfToolsPdfAValidation_AnalysisResult.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when `-1` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT int PDFTOOLS_CALL
PdfToolsPdfAValidation_AnalysisResult_GetFontCount(TPdfToolsPdfAValidation_AnalysisResult* pAnalysisResult);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSPDFAVALIDATION_H__ */
