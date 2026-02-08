/****************************************************************************
 *
 * File:            pdftoolsvalidateconvert.c
 *
 * Usage:           pdftoolsvalidateconvert <inputPath> <outputPath>
 *                  
 * Title:           Convert a PDF to PDF/A-2b if necessary
 *                  
 * Description:     Analyze the input PDF document. If it does not yet
 *                  conform to PDF/A-2b, convert it to PDF/A-2b.
 *                  
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2026 PDF Tools AG, Switzerland
 *                  Permission to use, copy, modify, and distribute this
 *                  software and its documentation for any purpose and without
 *                  fee is hereby granted, provided that the above copyright
 *                  notice appear in all copies and that both that copyright
 *                  notice and this permission notice appear in supporting
 *                  documentation. This software is provided "as is" without
 *                  express or implied warranty.
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PdfTools.h"

#include <locale.h>
#if !defined(WIN32)
#define TCHAR char
#define _tcslen strlen
#define _tcscat strcat
#define _tcscpy strcpy
#define _tcsrchr strrchr
#define _tcstok strtok
#define _tcslen strlen
#define _tcscmp strcmp
#define _tcsftime strftime
#define _tcsncpy strncpy
#define _tmain main
#define _tfopen fopen
#define _ftprintf fprintf
#define _stprintf sprintf
#define _tstof atof
#define _tremove remove
#define _tprintf printf
#define _T(str) str
#endif


#define MIN(a, b)     (((a) < (b) ? (a) : (b)))
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a)[0])

#define GOTO_CLEANUP_IF_NULL_PRINT_ERROR(inVar, ...)                                     \
    do                                                                                   \
    {                                                                                    \
        if ((inVar) == NULL)                                                             \
        {                                                                                \
            nBufSize = PdfTools_GetLastErrorMessage(NULL, 0);                            \
            PdfTools_GetLastErrorMessage(szErrBuf, MIN(ARRAY_SIZE(szErrBuf), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                       \
            iRet = 1;                                                                    \
            goto cleanup;                                                                \
        }                                                                                \
    } while (0);

#define GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(outBool, ...)                                  \
    do                                                                                   \
    {                                                                                    \
        if ((outBool) == FALSE)                                                          \
        {                                                                                \
            nBufSize = PdfTools_GetLastErrorMessage(NULL, 0);                            \
            PdfTools_GetLastErrorMessage(szErrBuf, MIN(ARRAY_SIZE(szErrBuf), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                       \
            iRet = 1;                                                                    \
            goto cleanup;                                                                \
        }                                                                                \
    } while (0);

#define IF_FALSE_PRINT_ERROR(outBool, ...)                                               \
    do                                                                                   \
    {                                                                                    \
        if ((outBool) == FALSE)                                                          \
        {                                                                                \
            nBufSize = PdfTools_GetLastErrorMessage(NULL, 0);                            \
            PdfTools_GetLastErrorMessage(szErrBuf, MIN(ARRAY_SIZE(szErrBuf), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                       \
            iRet = 1;                                                                    \
        }                                                                                \
    } while (0);

int Usage()
{
    printf("Usage: pdftoolsvalidateconvert <inputPath> <outputPath>.\n");
    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

int                                   iRet = 0;
size_t                                nBufSize;
TCHAR                                 szErrBuf[1024];
TPdfToolsPdfAConversion_EventSeverity iEventsSeverity = ePdfToolsPdfAConversion_EventSeverity_Information;

void EventListener(void* pContext, const char* szDataPart, const char* szMessage,
                   TPdfToolsPdfAConversion_EventSeverity iSeverity, TPdfToolsPdfAConversion_EventCategory iCategory,
                   TPdfToolsPdfAConversion_EventCode iCode, const char* szContext, int iPageNo)
{
    // iSeverity is the event's suggested severity
    // Optionally the suggested severity can be changed according to
    // the requirements of your conversion process and, for example,
    // the event's category (e.Category).

    if (iSeverity > iEventsSeverity)
        iEventsSeverity = iSeverity;

    // Report conversion event
    TCHAR cSeverity = iSeverity == ePdfToolsPdfAConversion_EventSeverity_Information ? 'I'
                      : ePdfToolsPdfAConversion_EventSeverity_Warning                ? 'W'
                                                                                     : 'E';
    if (iPageNo > 0)
        _tprintf(_T("- %c %d: %s (%s on page %d)\n"), cSeverity, iCategory, szMessage, szContext, iPageNo);
    else
        _tprintf(_T("- %c %d: %s (%s)\n"), cSeverity, iCategory, szMessage, szContext);
}

void ConvertIfNotConforming(const TCHAR* szInPath, const TCHAR* szOutPath, TPdfToolsPdf_Conformance iConf)
{
    TPdfToolsPdfAValidation_AnalysisOptions*   pAOpt      = NULL;
    TPdfToolsPdfAValidation_Validator*         pValidator = NULL;
    TPdfToolsPdfAValidation_AnalysisResult*    pARes      = NULL;
    TPdfToolsPdfAConversion_ConversionOptions* pConvOpt   = NULL;
    TPdfToolsPdfAConversion_Converter*         pConv      = NULL;
    TPdfToolsPdf_Document*                     pOutDoc    = NULL;
    TPdfToolsPdf_Document*                     pInDoc     = NULL;
    FILE*                                      pInStream  = NULL;
    FILE*                                      pOutStream = NULL;

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInStream, _T("Failed to open the input file \"%s\" for reading.\n"), szInPath);
    TPdfToolsSys_StreamDescriptor inDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&inDesc, pInStream, 0);
    pInDoc = PdfToolsPdf_Document_Open(&inDesc, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Failed to open document \"%s\". %s (ErrorCode: 0x%08x).\n"), szInPath,
                                     szErrBuf, PdfTools_GetLastError());

    // Create validator to analyze PDF/A standard conformance of input document
    pAOpt = PdfToolsPdfAValidation_AnalysisOptions_New();
    PdfToolsPdfAValidation_AnalysisOptions_SetConformance(pAOpt, iConf);
    pValidator = PdfToolsPdfAValidation_Validator_New();
    pARes      = PdfToolsPdfAValidation_Validator_Analyze(pValidator, pInDoc, pAOpt);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pARes, _T("Failed to analyze document. %s (ErrorCode: 0x%08x).\n"), szErrBuf,
                                     PdfTools_GetLastError());

    // Check if conversion to PDF/A is necessary
    if (PdfToolsPdfAValidation_AnalysisResult_IsConforming(pARes))
    {
        printf("Document conforms to %s already.\n", PdfToolsPdf_Conformance_ToStringA(iConf));
        goto cleanup;
    }

    // Create output stream for writing
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to create the output file \"%s\".\n"), szOutPath);
    TPdfToolsSys_StreamDescriptor outDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);

    // Convert the input document to PDF/A using the converter object
    // and its conversion event handler
    pConvOpt = PdfToolsPdfAConversion_ConversionOptions_New();
    pConv    = PdfToolsPdfAConversion_Converter_New();
    PdfToolsPdfAConversion_Converter_AddConversionEventHandlerA(
        pConv, NULL, (TPdfToolsPdfAConversion_Converter_ConversionEventA)EventListener);
    pOutDoc = PdfToolsPdfAConversion_Converter_Convert(pConv, pARes, pInDoc, &outDesc, pConvOpt, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("Failed to convert document. %s (ErrorCode: 0x%08x).\n"), szErrBuf,
                                     PdfTools_GetLastError());

    // Check if critical conversion events occurred
    switch (iEventsSeverity)
    {
    case ePdfToolsPdfAConversion_EventSeverity_Information:
    {
        TPdfToolsPdf_Conformance iOutConf;
        PdfToolsPdf_Document_GetConformance(pOutDoc, &iOutConf);
        printf("Successfully converted document to %s.\n", PdfToolsPdf_Conformance_ToStringA(iOutConf));
        break;
    }

    case ePdfToolsPdfAConversion_EventSeverity_Warning:
    {
        TPdfToolsPdf_Conformance iOutConf;
        PdfToolsPdf_Document_GetConformance(pOutDoc, &iOutConf);
        printf("Warnings occurred during the conversion of document to %s.\n",
               PdfToolsPdf_Conformance_ToStringA(iOutConf));
        printf("Check the output file to decide if the result is acceptable.\n");
        break;
    }

    case ePdfToolsPdfAConversion_EventSeverity_Error:
    {
        printf("Unable to convert document to %s because of critical conversion events.\n",
               PdfToolsPdf_Conformance_ToStringA(iConf));
        break;
    }
    }

cleanup:
    PdfToolsPdf_Document_Close(pOutDoc);
    PdfTools_Release(pConv);
    PdfTools_Release(pConvOpt);
    PdfTools_Release(pARes);
    PdfTools_Release(pValidator);
    PdfTools_Release(pAOpt);
    PdfToolsPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);
    if (pOutStream)
        fclose(pOutStream);
}

int _tmain(int argc, TCHAR* argv[])
{
    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 3 || argc > 3)
    {
        return Usage();
    }

    // Initialize library
    PdfTools_Initialize();

    // By default, a test license key is active. In this case, a watermark is added to the output. 
    // If you have a license key, please uncomment the following call and set the license key.
    // GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfTools_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
    //                                     _T("Failed to set the license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
    //                                     PdfTools_GetLastError());

    // Convert the document to PDF/A-2b
    TPdfToolsPdf_Conformance iConf = ePdfToolsPdf_Conformance_PdfA2B;
    ConvertIfNotConforming(argv[1], argv[2], iConf);

    PdfTools_Uninitialize();

    return iRet;
}
