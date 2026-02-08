/****************************************************************************
 *
 * File:            pdftoolsextracttextlayout.c
 *
 * Usage:           pdftoolsextracttextlayout <inputPath> <outputDir>
 *
 * Title:           Extract text mimicking layout
 *
 * Description:     Extracting text from a PDF page by page into text files,
 *                  preserving the original layout by adding whitespaces to the
 *                  monospace text.
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
#include <sys/stat.h>
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
    printf("Usage: pdftoolsextracttextlayout <inputPath> <outputDir>.\n");
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

    TCHAR*                           szInPath    = argv[1];
    TCHAR*                           szOutDir    = argv[2];
    FILE*                            pInStream   = NULL;
    FILE*                            pOutStream  = NULL;
    TPdfToolsPdf_Document*           pInDoc      = NULL;
    TPdfToolsExtraction_TextOptions* pOptions    = NULL;
    TPdfToolsExtraction_Extractor*   pExtractor  = NULL;

    // Initialize library
    PdfTools_Initialize();

    // By default, a test license key is active. In this case, a watermark is added to the output.
    // If you have a license key, please uncomment the following call and set the license key.
    // GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfTools_Sdk_Initialize(_T("<PDFSDK,V1,MGAASQD6L2JMQHL54PK08RQX8GG4SS0M8DAHVPH0VMP3NB8R9DUK>"), NULL),
    //                                     _T("Failed to set the license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
    //                                     PdfTools_GetLastError());

    // Create output directory
#if defined(WIN32)
    _tmkdir(szOutDir);
#else
    mkdir(szOutDir, 0755);
#endif

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInStream, _T("Failed to open the input file \"%s\" for reading.\n"), szInPath);
    TPdfToolsSys_StreamDescriptor inDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&inDesc, pInStream, 0);
    pInDoc = PdfToolsPdf_Document_Open(&inDesc, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pInDoc, _T("Failed to create a document from the input file \"%s\". %s (ErrorCode: 0x%08x).\n"), szInPath,
        szErrorBuff, PdfTools_GetLastError());

    // Get the number of pages in the document
    int nPageCount = PdfToolsPdf_Document_GetPageCount(pInDoc);

    // Create text extraction options
    pOptions = PdfToolsExtraction_TextOptions_New();
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOptions, _T("Failed to create text options. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, PdfTools_GetLastError());

    // Set extraction format to monospace to preserve the original layout
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
        PdfToolsExtraction_TextOptions_SetExtractionFormat(pOptions,
                                                           ePdfToolsExtraction_TextExtractionFormat_Monospace),
        _T("Failed to set extraction format. %s (ErrorCode: 0x%08x).\n"), szErrorBuff, PdfTools_GetLastError());

    // Set advance width for monospace text (9.2pt)
    double dAdvanceWidth = 9.2;
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfToolsExtraction_TextOptions_SetAdvanceWidth(pOptions, &dAdvanceWidth),
                                      _T("Failed to set advance width. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      PdfTools_GetLastError());

    // Create text extractor
    pExtractor = PdfToolsExtraction_Extractor_New();
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pExtractor, _T("Failed to create extractor. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, PdfTools_GetLastError());

    // Extract text page by page
    for (int i = 1; i <= nPageCount; i++)
    {
        // Build output filename for each page
        TCHAR szPageFile[512];
        _stprintf(szPageFile, _T("%s/page%d.txt"), szOutDir, i);

        // Create output stream for writing
        pOutStream = _tfopen(szPageFile, _T("wb+"));
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to open the output file \"%s\" for writing.\n"),
                                         szPageFile);
        TPdfToolsSys_StreamDescriptor outDesc;
        PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);

        // Extract text for the current page
        int iFirstPage = i;
        int iLastPage  = i;
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
            PdfToolsExtraction_Extractor_ExtractText(pExtractor, pInDoc, &outDesc, pOptions, &iFirstPage, &iLastPage),
            _T("Failed to extract text for page %d. %s (ErrorCode: 0x%08x).\n"), i, szErrorBuff,
            PdfTools_GetLastError());

        fclose(pOutStream);
        pOutStream = NULL;
    }

    _tprintf(_T("Execution successful.\n"));

cleanup:
    PdfTools_Release(pExtractor);
    PdfTools_Release(pOptions);
    if (pOutStream)
        fclose(pOutStream);
    if (pInDoc)
        PdfToolsPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);

    PdfTools_Uninitialize();

    return iRet;
}
