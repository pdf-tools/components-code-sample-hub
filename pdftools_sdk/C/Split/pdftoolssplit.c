/****************************************************************************
 *
 * File:            pdftoolssplit.c
 *
 * Usage:           pdftoolssplit <inputPath> <outputPath>
 *                  
 * Title:           Split a PDF
 *                  
 * Description:     Divide a PDF document into multiple PDF files.
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

void CreateOutputFileName(TCHAR* buffer, const TCHAR* outPath, const int i)
{
    const TCHAR szExt[5]  = _T(".pdf");
    const TCHAR szPage[7] = _T("_page_");
    TCHAR       numBuffer[5];

#ifdef _UNICODE
    _itow(i, numBuffer, 10);
#else
    itoa(i, numBuffer, 10);
#endif

    _tcscpy(buffer, outPath);
    _tcsncat(buffer, szPage, _tcslen(szPage));
    _tcsncat(buffer, numBuffer, _tcslen(numBuffer));
    _tcsncat(buffer, szExt, _tcslen(szExt));
}

int Usage()
{
    printf("Usage: pdftoolssplit <inputPath> <outputPath>.\n");
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

    TCHAR*                 szInPath   = argv[1]; // /absolute/path/to/pdf_to_split.pdf
    TCHAR*                 szOutPath  = argv[2]; // /absolute/path/to/destination/
    FILE*                  pInStream  = NULL;
    FILE*                  pOutStream = NULL;
    TPdfToolsPdf_Document* pInDoc     = NULL;
    TPdfToolsPdf_Document* pOutDoc    = NULL;

    TPdfToolsDocumentAssembly_DocumentAssembler* pAssembler = NULL;

    // Initialize library
    PdfTools_Initialize();

    // By default, a test license key is active. In this case, a watermark is added to the output. 
    // If you have a license key, please uncomment the following call and set the license key.
    // GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfTools_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
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

    // Split input document by generating one output document per page
    int   nPageCount = PdfToolsPdf_Document_GetPageCount(pInDoc);
    TCHAR szPageFileName[256];
    for (int i = 1; i <= nPageCount; i++)
    {
        CreateOutputFileName(szPageFileName, szOutPath, i);

        // Create output stream for each page of the input document
        pOutStream = _tfopen(szPageFileName, _T("wb+"));
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to open the input file \"%s\" for reading.\n"),
                                         szPageFileName);
        TPdfToolsSys_StreamDescriptor outDesc;
        PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);

        // Split pdf into pages
        pAssembler = PdfToolsDocumentAssembly_DocumentAssembler_New(&outDesc, NULL, NULL);
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
            PdfToolsDocumentAssembly_DocumentAssembler_Append(pAssembler, pInDoc, &i, &i, NULL, NULL),
            _T("Failed to append a page. (ErrorCode: 0x%08x).\n"), PdfTools_GetLastError());
        pOutDoc = PdfToolsDocumentAssembly_DocumentAssembler_Assemble(pAssembler);
        PdfToolsDocumentAssembly_DocumentAssembler_Close(pAssembler);

        if (pOutDoc)
            PdfToolsPdf_Document_Close(pOutDoc);
        if (pOutStream)
            fclose(pOutStream);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("The processing has failed. (ErrorCode: 0x%08x).\n"),
                                         PdfTools_GetLastError());
    }
    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pInDoc)
        PdfToolsPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);

    PdfTools_Uninitialize();

    return iRet;
}
