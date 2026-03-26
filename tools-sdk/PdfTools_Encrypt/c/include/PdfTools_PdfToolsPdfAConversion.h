/******************************************************************************
 *
 * File:            PdfTools_PdfToolsPdfAConversion.h
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

#ifndef PDFTOOLS_PDFTOOLSPDFACONVERSION_H__
#define PDFTOOLS_PDFTOOLSPDFACONVERSION_H__

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
#define TPdfToolsPdfAConversion_Converter_ConversionEvent TPdfToolsPdfAConversion_Converter_ConversionEventW
#define PdfToolsPdfAConversion_Converter_AddConversionEventHandler \
    PdfToolsPdfAConversion_Converter_AddConversionEventHandlerW
#define PdfToolsPdfAConversion_Converter_RemoveConversionEventHandler \
    PdfToolsPdfAConversion_Converter_RemoveConversionEventHandlerW

#else
#define TPdfToolsPdfAConversion_Converter_ConversionEvent TPdfToolsPdfAConversion_Converter_ConversionEventA
#define PdfToolsPdfAConversion_Converter_AddConversionEventHandler \
    PdfToolsPdfAConversion_Converter_AddConversionEventHandlerA
#define PdfToolsPdfAConversion_Converter_RemoveConversionEventHandler \
    PdfToolsPdfAConversion_Converter_RemoveConversionEventHandlerA

#endif

/**
 * @brief The event for errors, warnings, and informational messages that occur during conversion

Report a conversion event that occurred in \ref PdfToolsPdfAConversion_Converter_Convert "".
These events can be used to:
  - Generate a detailed conversion report.
  - Detect and handle critical conversion events.

Note that if a document cannot be converted to the requested conformance, the \ref
PdfToolsPdfAConversion_Converter_Convert "" throws an exception. However, even if the output document meets all required
standards, the conversion might have resulted in differences that might be acceptable in some processes but not in
others. Such potentially critical conversion issues are reported as conversion events.

We suggest checking which conversion events can be tolerated in your conversion process and which must be considered
critical:
  - <b>Review the suggested severity of events.</b>
Each event has a default severity indicated by `severity` which is based on the event's `category`.
Review the suggested severity of each \ref TPdfToolsPdfAConversion_EventCategory "" and determine the \ref
TPdfToolsPdfAConversion_EventSeverity "" to be used in your process.
  - <b>Handle events according to their severity</b>.
    - <b>Events of severity</b> \ref ePdfToolsPdfAConversion_EventSeverity_Error "":
The conversion must be considered as failed.
    - <b>Events of severity</b> \ref ePdfToolsPdfAConversion_EventSeverity_Warning "":
In case of a warning, the output file is best presented to a user to decide if the result is acceptable.
The properties `message`, `context`, and `page` in combination with the output file are helpful to make this decision.
    If a manual review is not feasible, critical warnings should be classified as an \ref
ePdfToolsPdfAConversion_EventSeverity_Error "". An exception to this is, if all processed input documents are similar in
their content, e.g. because they have been created by a single source (application). In this case, the conversion result
can be verified using representative test files and the event severity chosen accordingly.
    - <b>Events of severity</b> \ref ePdfToolsPdfAConversion_EventSeverity_Information "":
No further action is required.

* @param[in,out] pContext Context of the event callback.

* @param[in] szDataPart The data part is `NULL` for the main file and a data part specification for embedded files.
Examples:
  - `embedded-file:file.pdf`: For a file `file.pdf` that is embedded in the main file.
  - `embedded-file:file1.pdf/embedded-file:file2.pdf`: For a file `file2.pdf` that is embedded in an embedded file
`file1.pdf`.

* @param[in] szMessage The event message

* @param[in] iSeverity The suggested severity of the event.
We suggest checking, which conversion events are tolerable in your conversion process and which must be considered
critical. See the documentation of \ref TPdfToolsPdfAConversion_Converter_ConversionEvent "" for a more detailed
description.

* @param[in] iCategory The category of the event. This parameter can be used to:
  - Classify the severity of an event
  - Specialized handling of events
See the documentation of \ref TPdfToolsPdfAConversion_Converter_ConversionEvent "" for a more detailed description.

* @param[in] iCode The code identifying particular events which can be used for detection and specialized handling of
specific events. For most applications, it suffices to handle events by `category`.

* @param[in] szContext A description of the context where the event occurred

* @param[in] iPageNo The page this event is associated to or `0`


 */
typedef void(PDFTOOLS_CALL* TPdfToolsPdfAConversion_Converter_ConversionEventA)(
    void* pContext, const char* szDataPart, const char* szMessage, TPdfToolsPdfAConversion_EventSeverity iSeverity,
    TPdfToolsPdfAConversion_EventCategory iCategory, TPdfToolsPdfAConversion_EventCode iCode, const char* szContext,
    int iPageNo);
/**
 * @brief The event for errors, warnings, and informational messages that occur during conversion

Report a conversion event that occurred in \ref PdfToolsPdfAConversion_Converter_Convert "".
These events can be used to:
  - Generate a detailed conversion report.
  - Detect and handle critical conversion events.

Note that if a document cannot be converted to the requested conformance, the \ref
PdfToolsPdfAConversion_Converter_Convert "" throws an exception. However, even if the output document meets all required
standards, the conversion might have resulted in differences that might be acceptable in some processes but not in
others. Such potentially critical conversion issues are reported as conversion events.

We suggest checking which conversion events can be tolerated in your conversion process and which must be considered
critical:
  - <b>Review the suggested severity of events.</b>
Each event has a default severity indicated by `severity` which is based on the event's `category`.
Review the suggested severity of each \ref TPdfToolsPdfAConversion_EventCategory "" and determine the \ref
TPdfToolsPdfAConversion_EventSeverity "" to be used in your process.
  - <b>Handle events according to their severity</b>.
    - <b>Events of severity</b> \ref ePdfToolsPdfAConversion_EventSeverity_Error "":
The conversion must be considered as failed.
    - <b>Events of severity</b> \ref ePdfToolsPdfAConversion_EventSeverity_Warning "":
In case of a warning, the output file is best presented to a user to decide if the result is acceptable.
The properties `message`, `context`, and `page` in combination with the output file are helpful to make this decision.
    If a manual review is not feasible, critical warnings should be classified as an \ref
ePdfToolsPdfAConversion_EventSeverity_Error "". An exception to this is, if all processed input documents are similar in
their content, e.g. because they have been created by a single source (application). In this case, the conversion result
can be verified using representative test files and the event severity chosen accordingly.
    - <b>Events of severity</b> \ref ePdfToolsPdfAConversion_EventSeverity_Information "":
No further action is required.

* @param[in,out] pContext Context of the event callback.

* @param[in] szDataPart The data part is `NULL` for the main file and a data part specification for embedded files.
Examples:
  - `embedded-file:file.pdf`: For a file `file.pdf` that is embedded in the main file.
  - `embedded-file:file1.pdf/embedded-file:file2.pdf`: For a file `file2.pdf` that is embedded in an embedded file
`file1.pdf`.

* @param[in] szMessage The event message

* @param[in] iSeverity The suggested severity of the event.
We suggest checking, which conversion events are tolerable in your conversion process and which must be considered
critical. See the documentation of \ref TPdfToolsPdfAConversion_Converter_ConversionEvent "" for a more detailed
description.

* @param[in] iCategory The category of the event. This parameter can be used to:
  - Classify the severity of an event
  - Specialized handling of events
See the documentation of \ref TPdfToolsPdfAConversion_Converter_ConversionEvent "" for a more detailed description.

* @param[in] iCode The code identifying particular events which can be used for detection and specialized handling of
specific events. For most applications, it suffices to handle events by `category`.

* @param[in] szContext A description of the context where the event occurred

* @param[in] iPageNo The page this event is associated to or `0`


 */
typedef void(PDFTOOLS_CALL* TPdfToolsPdfAConversion_Converter_ConversionEventW)(
    void* pContext, const WCHAR* szDataPart, const WCHAR* szMessage, TPdfToolsPdfAConversion_EventSeverity iSeverity,
    TPdfToolsPdfAConversion_EventCategory iCategory, TPdfToolsPdfAConversion_EventCode iCode, const WCHAR* szContext,
    int iPageNo);

/******************************************************************************
 * Converter
 *****************************************************************************/
/**
 * @brief Adds event handler.
 *
 * @param[in,out] pConverter Pointer to the object to which the event handler is added.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is added.
 *
 * @return \ref TRUE if adding event handler was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAConversion_Converter_AddConversionEventHandlerA(
    TPdfToolsPdfAConversion_Converter* pConverter, void* pContext,
    TPdfToolsPdfAConversion_Converter_ConversionEventA pFunction);
/**
 * @brief Adds event handler.
 *
 * @param[in,out] pConverter Pointer to the object to which the event handler is added.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is added.
 *
 * @return \ref TRUE if adding event handler was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAConversion_Converter_AddConversionEventHandlerW(
    TPdfToolsPdfAConversion_Converter* pConverter, void* pContext,
    TPdfToolsPdfAConversion_Converter_ConversionEventW pFunction);
/**
 * @brief Removes event handler.
 *
 * @param[in,out] pConverter Pointer to the object from which the event handler is removed.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is removed.
 *
 * @return \ref TRUE if removal was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAConversion_Converter_RemoveConversionEventHandlerA(
    TPdfToolsPdfAConversion_Converter* pConverter, void* pContext,
    TPdfToolsPdfAConversion_Converter_ConversionEventA pFunction);
/**
 * @brief Removes event handler.
 *
 * @param[in,out] pConverter Pointer to the object from which the event handler is removed.
 * @param[in,out] pContext The context of the event handler.
 * @param[in] pFunction The event callback that is removed.
 *
 * @return \ref TRUE if removal was successful; \ref FALSE if error occured.
 *
 * @note In case of an error, Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAConversion_Converter_RemoveConversionEventHandlerW(
    TPdfToolsPdfAConversion_Converter* pConverter, void* pContext,
    TPdfToolsPdfAConversion_Converter_ConversionEventW pFunction);

/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdfAConversion_Converter* PDFTOOLS_CALL PdfToolsPdfAConversion_Converter_New(void);

/**
 * @brief Convert a document to PDF/A.
Note that it is highly recommended to use \ref TPdfToolsPdfAConversion_Converter_ConversionEvent "" to detect critical
conversion events.

* @param[in,out] pConverter Acts as a handle to the native object of type \ref TPdfToolsPdfAConversion_Converter.

* @param[in,out] pAnalysis The result of the document's analysis using \ref PdfToolsPdfAValidation_Validator_Analyze "".

* @param[in,out] pDocument The document to convert

* @param[in,out] pOutStreamDesc The stream where the converted document is written

* @param[in,out] pOptions The conversion options

* @param[in,out] pOutOptions The output options object


 * @return   The result of the conversion

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.
 * Possible error codes:
 * - \ref ePdfTools_Error_License The license check has failed.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pOutOptions</b> argument is invalid.

 * - \ref ePdfTools_Error_IllegalArgument The output stream could not be opened for writing.

 * - \ref ePdfTools_Error_IllegalState The <b>pDocument</b> has already been closed.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pAnalysis</b> has already been closed, e.g. due to a previous
conversion.

 * - \ref ePdfTools_Error_IllegalArgument The PDF/A version of the analysis and the conversion options do not match.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pAnalysis</b> is not the analysis result of <b>pDocument</b>.

 * - \ref ePdfTools_Error_IO Error reading from or writing to the <b>pOutStreamDesc</b>.

 * - \ref ePdfTools_Error_Conformance The conformance required by <b>pOptions</b> cannot be achieved.
  - PDF/A level U: All text of the input document must be extractable.
  - PDF/A level A: In addition to the requirements of level U, the input document must be tagged.

 * - \ref ePdfTools_Error_Conformance The PDF/A version of the conformances of <b>pAnalysis</b> and <b>pOptions</b>
differ. The same PDF/A version must be used for the analysis and conversion.

 * - \ref ePdfTools_Error_IllegalArgument The <b>pOutOptions</b> specifies document encryption, which is not allowed in
PDF/A documents.

 * - \ref ePdfTools_Error_Generic The document cannot be converted to PDF/A.

 * - \ref ePdfTools_Error_Corrupt The analysis has been stopped.

 * - \ref ePdfTools_Error_UnsupportedFeature The document is not a PDF, but an XFA document.
See \ref PdfToolsPdf_Document_GetXfa "" for more information on how to detect and handle XFA documents.

 * - \ref ePdfTools_Error_NotFound A required font is missing from the installed font directories.


 */
PDFTOOLS_EXPORT TPdfToolsPdf_Document* PDFTOOLS_CALL PdfToolsPdfAConversion_Converter_Convert(
    TPdfToolsPdfAConversion_Converter* pConverter, TPdfToolsPdfAValidation_AnalysisResult* pAnalysis,
    TPdfToolsPdf_Document* pDocument, const TPdfToolsSys_StreamDescriptor* pOutStreamDesc,
    TPdfToolsPdfAConversion_ConversionOptions* pOptions, TPdfToolsPdf_OutputOptions* pOutOptions);

/******************************************************************************
 * ConversionOptions
 *****************************************************************************/
/**
 * @return   Handle to the newly created native object.

   `NULL` if there is an error.
 * @note An error occurred when `NULL` was returned. Retrieve specific error code by calling \ref PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT TPdfToolsPdfAConversion_ConversionOptions* PDFTOOLS_CALL
PdfToolsPdfAConversion_ConversionOptions_New(void);

/**
 * @brief The minimal target conformance

If a conformance is set, it is used as the minimal target conformance.
The PDF/A version of the conformance must match the PDF/A version of the analysisOptions of \ref
PdfToolsPdfAValidation_Validator_Analyze "". If the conformance level cannot be achieved, the conversion will abort with
the error \ref ePdfTools_Error_Conformance "". If a higher conformance level can be achieved, it is used automatically.

If `NULL` is used, the optimal conformance determined in the analysis
(i.e. \ref PdfToolsPdfAValidation_AnalysisResult_GetRecommendedConformance "") is used.
It is highly recommended to use `NULL`.

Default value: `NULL`

* @param[in,out] pConversionOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAConversion_ConversionOptions.

* @param[out] pConformance Retrieved value.


 * @return   \ref FALSE if either an error occurred or the `[out]` argument returns `NULL`.
   To determine if an error has occurred, check the error code as described in the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAConversion_ConversionOptions_GetConformance(
    TPdfToolsPdfAConversion_ConversionOptions* pConversionOptions, TPdfToolsPdf_Conformance* pConformance);
/**
 * @brief The minimal target conformance

If a conformance is set, it is used as the minimal target conformance.
The PDF/A version of the conformance must match the PDF/A version of the analysisOptions of \ref
PdfToolsPdfAValidation_Validator_Analyze "". If the conformance level cannot be achieved, the conversion will abort with
the error \ref ePdfTools_Error_Conformance "". If a higher conformance level can be achieved, it is used automatically.

If `NULL` is used, the optimal conformance determined in the analysis
(i.e. \ref PdfToolsPdfAValidation_AnalysisResult_GetRecommendedConformance "") is used.
It is highly recommended to use `NULL`.

Default value: `NULL`

* @param[in,out] pConversionOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAConversion_ConversionOptions.

* @param[in] pConformance Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAConversion_ConversionOptions_SetConformance(
    TPdfToolsPdfAConversion_ConversionOptions* pConversionOptions, const TPdfToolsPdf_Conformance* pConformance);
/**
 * @brief Whether to copy metadata
Copy document information dictionary and XMP metadata.
Default: \ref "TRUE".

* @param[in,out] pConversionOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAConversion_ConversionOptions.


 * @return   Retrieved value.

   May indicate an error in certain scenarios. For further information see the note section below.
 * @note An error occurred when \ref FALSE was returned <b>and</b> the error code returned by \ref PdfTools_GetLastError
is different from \ref ePdfTools_Error_Success.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsPdfAConversion_ConversionOptions_GetCopyMetadata(TPdfToolsPdfAConversion_ConversionOptions* pConversionOptions);
/**
 * @brief Whether to copy metadata
Copy document information dictionary and XMP metadata.
Default: \ref "TRUE".

* @param[in,out] pConversionOptions Acts as a handle to the native object of type \ref
TPdfToolsPdfAConversion_ConversionOptions.

* @param[in] bCopyMetadata Set value.


 * @return    \ref TRUE if the operation is successful; \ref FALSE if there is an error.
 * @note An error occurred when \ref FALSE was returned. Retrieve specific error code by calling \ref
PdfTools_GetLastError.
 * Get the error message with \ref PdfTools_GetLastErrorMessage.

 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsPdfAConversion_ConversionOptions_SetCopyMetadata(
    TPdfToolsPdfAConversion_ConversionOptions* pConversionOptions, BOOL bCopyMetadata);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSPDFACONVERSION_H__ */
