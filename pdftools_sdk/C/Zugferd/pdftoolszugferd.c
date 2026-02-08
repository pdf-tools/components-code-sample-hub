/****************************************************************************
 *
 * File:            pdftoolszugferd.c
 *
 * Usage:           pdftoolszugferd <inputPath> <invoicePath> <outputPath>
 *                  
 * Title:           Create a ZUGFeRD invoice
 *                  
 * Description:     Convert a PDF to PDF/A-3 and embed XML data to create a
 *                  ZUGFeRD-compliant invoice.
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
    printf("Usage: pdftoolszugferd <inputPath> <invoicePath> <outputPath>.\n");
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

void AddZugferdInvoice(const TCHAR* szInPath, const TCHAR* szInvoicePath, const TCHAR* szOutPath)
{
    TPdfToolsPdfAValidation_AnalysisOptions*   pAOpt          = NULL;
    TPdfToolsPdfAValidation_Validator*         pValidator     = NULL;
    TPdfToolsPdfAValidation_AnalysisResult*    pARes          = NULL;
    TPdfToolsPdfAConversion_ConversionOptions* pConvOpt       = NULL;
    TPdfToolsPdfAConversion_Converter*         pConv          = NULL;
    TPdfToolsPdf_Document*                     pOutDoc        = NULL;
    TPdfToolsPdf_Document*                     pInDoc         = NULL;
    FILE*                                      pInStream      = NULL;
    FILE*                                      pInvoiceStream = NULL;
    FILE*                                      pOutStream     = NULL;

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
    // The conformance has to be set to PDF/A-3 when adding the XML invoice file
    PdfToolsPdfAValidation_AnalysisOptions_SetConformance(pAOpt, ePdfToolsPdf_Conformance_PdfA3U);
    pValidator = PdfToolsPdfAValidation_Validator_New();
    pARes      = PdfToolsPdfAValidation_Validator_Analyze(pValidator, pInDoc, pAOpt);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pARes, _T("Failed to analyze document. %s (ErrorCode: 0x%08x).\n"), szErrBuf,
                                     PdfTools_GetLastError());

    // Create output stream for writing
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to create the output file \"%s\".\n"), szOutPath);
    TPdfToolsSys_StreamDescriptor outDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);

    // Create a converter object and add a conversion event handler
    pConvOpt = PdfToolsPdfAConversion_ConversionOptions_New();
    pConv    = PdfToolsPdfAConversion_Converter_New();
    PdfToolsPdfAConversion_Converter_AddConversionEventHandlerA(
        pConv, NULL, (TPdfToolsPdfAConversion_Converter_ConversionEventA)EventListener);

    // Create invoice stream for reading
    pInvoiceStream = _tfopen(szInvoicePath, _T("rb"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInvoiceStream, _T("Failed to open the invoice file \"%s\" for reading.\n"),
                                     szInvoicePath);
    TPdfToolsSys_StreamDescriptor invoiceDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&invoiceDesc, pInvoiceStream, 0);
    // Add invoice XML file
    PdfToolsPdfAConversion_Converter_AddInvoiceXml(pConv, ePdfToolsPdfAConversion_InvoiceType_Zugferd, &invoiceDesc,
                                                   NULL);
    // Convert the input document to PDF/A-3U
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
        printf("Unable to convert document to PDF/A-3U because of critical conversion events.\n");
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
    if (pInvoiceStream)
        fclose(pInvoiceStream);
}

int _tmain(int argc, TCHAR* argv[])
{
    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 4 || argc > 4)
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

    AddZugferdInvoice(argv[1], argv[2], argv[3]);

    PdfTools_Uninitialize();

    return iRet;
}
