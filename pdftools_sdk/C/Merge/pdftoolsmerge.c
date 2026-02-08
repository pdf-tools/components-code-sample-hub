/****************************************************************************
 *
 * File:            pdftoolsmerge.c
 *
 * Usage:           pdftoolsmerge <inputPath> [<inputPath2> ...] <outputPath>
 *                  
 * Title:           Merge PDFs
 *                  
 * Description:     Merge multiple PDF documents into a single file.
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
    printf("Usage: pdftoolsmerge <inputPath> [<inputPath2> ...] <outputPath>.\n");
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
    if (argc < 3)
    {
        return Usage();
    }

    TCHAR*                 szInPath   = NULL;           // /absolute/path/to/input.pdf
    TCHAR*                 szOutPath  = argv[argc - 1]; // /absolute/path/to/output.pdf
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

    // Create output stream
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to create output file \"%s\" for writing.\n"), szOutPath);
    TPdfToolsSys_StreamDescriptor outDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);
    pAssembler = PdfToolsDocumentAssembly_DocumentAssembler_New(&outDesc, NULL, NULL);

    for (int i = 1; i < argc - 1; i++)
    {
        szInPath = argv[i];
        // Open input document
        pInStream = _tfopen(szInPath, _T("rb"));
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInStream, _T("Failed to open the input file \"%s\" for reading.\n"),
                                         szInPath);
        TPdfToolsSys_StreamDescriptor inDesc;
        PdfToolsSysCreateFILEStreamDescriptor(&inDesc, pInStream, 0);
        pInDoc = PdfToolsPdf_Document_Open(&inDesc, _T(""));
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
            pInDoc, _T("Failed to create a document from the input file \"%s\". %s (ErrorCode: 0x%08x).\n"), szInPath,
            szErrorBuff, PdfTools_GetLastError());

        // Append the content of the input documents to the output document
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
            PdfToolsDocumentAssembly_DocumentAssembler_Append(pAssembler, pInDoc, NULL, NULL, NULL, NULL),
            _T("Failed to append a page. (ErrorCode: 0x%08x).\n"), PdfTools_GetLastError());

        PdfToolsPdf_Document_Close(pInDoc);
        fclose(pInStream);
        pInDoc    = NULL;
        pInStream = NULL;
    }
    // Merge input documents into an output document
    pOutDoc = PdfToolsDocumentAssembly_DocumentAssembler_Assemble(pAssembler);

    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("The processing has failed. (ErrorCode: 0x%08x).\n"),
                                     PdfTools_GetLastError());

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pAssembler)
        PdfToolsDocumentAssembly_DocumentAssembler_Close(pAssembler);
    if (pOutDoc)
        PdfToolsPdf_Document_Close(pOutDoc);
    if (pOutStream)
        fclose(pOutStream);
    if (pInDoc)
        PdfToolsPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);

    PdfTools_Uninitialize();

    return iRet;
}
