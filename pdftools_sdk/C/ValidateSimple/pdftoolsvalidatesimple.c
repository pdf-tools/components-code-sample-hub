/****************************************************************************
 *
 * File:            pdftoolsvalidatesimple.c
 *
 * Usage:           pdftoolsvalidatesimple <inputPath>
 *                  
 * Title:           Validate PDF conformance
 *                  
 * Description:     Assess whether a PDF document adheres to specific
 *                  standards and conformance levels.
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
    printf("Usage: pdftoolsvalidatesimple <inputPath>.\n");
    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

int    iRet = 0;
size_t nBufSize;
TCHAR  szErrBuf[1024];

void ErrorListener(void* pContext, const TCHAR* szDataPart, const TCHAR* szMessage,
                   TPdfToolsPdfAValidation_ErrorCategory iCategory, const TCHAR* szContext, int iPageNo, int iObjectNo)
{
    if (iPageNo > 0)
        _tprintf(_T("- %d: %s (%s on page %d)\n"), iCategory, szMessage, szContext, iPageNo);
    else
        _tprintf(_T("- %d: %s (%s)\n"), iCategory, szMessage, szContext);
}

void Validate(const TCHAR* szInPath)
{
    TPdfToolsPdf_Document*                    pInDoc     = NULL;
    TPdfToolsPdfAValidation_Validator*        pValidator = NULL;
    TPdfToolsPdfAValidation_ValidationResult* pResult    = NULL;

    // Open input document
    FILE* pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInStream, _T("Failed to open the input file \"%s\" for reading.\n"), szInPath);
    TPdfToolsSys_StreamDescriptor inDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&inDesc, pInStream, 0);
    pInDoc = PdfToolsPdf_Document_Open(&inDesc, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Failed to open document \"%s\". %s (ErrorCode: 0x%08x).\n"), szInPath,
                                     szErrBuf, PdfTools_GetLastError());

    // Create a validator object that writes all validation error messages to the console
    pValidator = PdfToolsPdfAValidation_Validator_New();
    PdfToolsPdfAValidation_Validator_AddErrorHandler(pValidator, NULL,
                                                     (TPdfToolsPdfAValidation_Validator_Error)ErrorListener);

    // Validate the standard conformance of the document
    pResult = PdfToolsPdfAValidation_Validator_Validate(pValidator, pInDoc, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pResult, _T("Failed to validate document. %s (ErrorCode: 0x%08x).\n"), szErrBuf,
                                     PdfTools_GetLastError());

    // Report validation result
    TPdfToolsPdf_Conformance iClaimedConformance;
    PdfToolsPdf_Document_GetConformance(pInDoc, &iClaimedConformance);
    if (PdfToolsPdfAValidation_ValidationResult_IsConforming(pResult))
        printf("Document conforms to %s.\n", PdfToolsPdf_Conformance_ToStringA(iClaimedConformance));
    else
        printf("Document does not conform to %s.\n", PdfToolsPdf_Conformance_ToStringA(iClaimedConformance));

cleanup:
    PdfTools_Release(pResult);
    PdfTools_Release(pValidator);
    PdfToolsPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);
}

int _tmain(int argc, TCHAR* argv[])
{
    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 2 || argc > 2)
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

    Validate(argv[1]);

    PdfTools_Uninitialize();

    return iRet;
}
