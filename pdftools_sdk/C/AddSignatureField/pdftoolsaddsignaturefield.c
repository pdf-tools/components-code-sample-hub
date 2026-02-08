/****************************************************************************
 *
 * File:            pdftoolsaddsignaturefield.c
 *
 * Usage:           pdftoolsaddsignaturefield <inputPath> <outputPath>
 *
 * Title:           Add a signature field to a PDF
 *
 * Description:     Add an unsigned signature field that can be signed in
 *                  another application.
 *                  The signature field indicates that the document requires
 *                  a signature and defines the page and position
 *                  where the signature's visual appearance will be placed.
 *                  This is especially useful for forms and contracts
 *                  with designated signature spaces. The signature visual
 *                  appearance is irrelevant to the signature validation
 *                  process and only serves as a visual cue for the user.
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

#define GOTO_CLEANUP_IF_NULL_PRINT_ERROR(inVar, ...)                                           \
    do                                                                                         \
    {                                                                                          \
        if ((inVar) == NULL)                                                                   \
        {                                                                                      \
            nBufSize = PdfTools_GetLastErrorMessage(NULL, 0);                                  \
            PdfTools_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                             \
            iRet = 1;                                                                          \
            goto cleanup;                                                                      \
        }                                                                                      \
    } while (0);

#define GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(outBool, ...)                                        \
    do                                                                                         \
    {                                                                                          \
        if ((outBool) == FALSE)                                                                \
        {                                                                                      \
            nBufSize = PdfTools_GetLastErrorMessage(NULL, 0);                                  \
            PdfTools_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                             \
            iRet = 1;                                                                          \
            goto cleanup;                                                                      \
        }                                                                                      \
    } while (0);

int Usage()
{
    printf("Usage: pdftoolsaddsignaturefield <inputPath> <outputPath>.\n");
    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

int _tmain(int argc, TCHAR* argv[])
{
    int    iRet = 0;
    size_t nBufSize;
    TCHAR  szErrorBuff[1024];

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 3 || argc > 3)
    {
        return Usage();
    }

    TCHAR*                          szInPath       = argv[1];
    TCHAR*                          szOutPath      = argv[2];
    FILE*                           pInStream      = NULL;
    FILE*                           pOutStream     = NULL;
    TPdfToolsPdf_Document*          pInDoc         = NULL;
    TPdfToolsSign_Appearance*       pAppearance    = NULL;
    TPdfToolsSign_SignatureFieldOptions* pFieldOptions = NULL;
    TPdfToolsSign_Signer*           pSigner        = NULL;
    TPdfToolsPdf_Document*          pOutDoc        = NULL;

    // Initialize library
    PdfTools_Initialize();

    // By default, a test license key is active. In this case, a watermark is added to the output.
    // If you have a license key, please uncomment the following call and set the license key.
    // GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfTools_Sdk_Initialize(_T("<PDFSDK,V1,MGAASQD6L2JMQHL54PK08RQX8GG4SS0M8DAHVPH0VMP3NB8R9DUK>"), NULL),
    //                                     _T("Failed to set the license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
    //                                     PdfTools_GetLastError());

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInStream, _T("Failed to open the input file \"%s\" for reading.\n"), szInPath);
    TPdfToolsSys_StreamDescriptor inDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&inDesc, pInStream, 0);
    pInDoc = PdfToolsPdf_Document_Open(&inDesc, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pInDoc, _T("Failed to create a document from the input file \"%s\". %s (ErrorCode: 0x%08x).\n"), szInPath,
        szErrorBuff, PdfTools_GetLastError());

    // Create empty field appearance that is 6cm by 3cm in size
    TPdfToolsGeomUnits_Size fieldSize = {6.0 * 72.0 / 2.54, 3.0 * 72.0 / 2.54};
    pAppearance = PdfToolsSign_Appearance_CreateFieldBoundingBox(&fieldSize);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pAppearance, _T("Failed to create appearance. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
        PdfTools_GetLastError());

    // Add field to last page of document
    int nPageCount = PdfToolsPdf_Document_GetPageCount(pInDoc);
    PdfToolsSign_Appearance_SetPageNumber(pAppearance, &nPageCount);

    // Position field
    double dBottom = 3.0 * 72.0 / 2.54;
    double dLeft = 6.5 * 72.0 / 2.54;
    PdfToolsSign_Appearance_SetBottom(pAppearance, &dBottom);
    PdfToolsSign_Appearance_SetLeft(pAppearance, &dLeft);

    // Create a signature field configuration
    pFieldOptions = PdfToolsSign_SignatureFieldOptions_New(pAppearance);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pFieldOptions, _T("Failed to create signature field options. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
        PdfTools_GetLastError());

    // Create output stream for writing
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to open the output file \"%s\" for writing.\n"), szOutPath);
    TPdfToolsSys_StreamDescriptor outDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);

    // Add the signature field to the input document
    pSigner = PdfToolsSign_Signer_New();
    pOutDoc = PdfToolsSign_Signer_AddSignatureField(pSigner, pInDoc, pFieldOptions, &outDesc, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("The processing has failed. (ErrorCode: 0x%08x).\n"),
                                     PdfTools_GetLastError());

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pOutDoc)
        PdfToolsPdf_Document_Close(pOutDoc);
    PdfTools_Release(pSigner);
    PdfTools_Release(pFieldOptions);
    PdfTools_Release(pAppearance);
    if (pOutStream)
        fclose(pOutStream);
    if (pInDoc)
        PdfToolsPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);

    PdfTools_Uninitialize();

    return iRet;
}
