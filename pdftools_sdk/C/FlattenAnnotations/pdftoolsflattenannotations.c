/****************************************************************************
 *
 * File:            pdftoolsflattenannotations.c
 *
 * Usage:           pdftoolsflattenannotations <inputPath> <outputPath>
 *                  
 * Title:           Flatten annotations
 *                  
 * Description:     Optimize a PDF document by flattening the annotations of
 *                  the PDF. As a result, the annotations are converted to
 *                  static content.
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
    printf("Usage: pdftoolsflattenannotations <inputPath> <outputPath>.\n");
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

    TCHAR*                                 szInPath   = argv[1];
    TCHAR*                                 szOutPath  = argv[2];
    FILE*                                  pInStream  = NULL;
    FILE*                                  pOutStream = NULL;
    TPdfToolsPdf_Document*                 pInDoc     = NULL;
    TPdfToolsOptimizationProfiles_Profile* pProfile   = NULL;
    TPdfToolsOptimization_Optimizer*       pOptimizer = NULL;
    TPdfToolsPdf_Document*                 pOutDoc    = NULL;

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

    // Create output stream for writing
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to open the output file \"%s\" for writing.\n"), szOutPath);
    TPdfToolsSys_StreamDescriptor outDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);

    // Create the profile that defines the optimization parameters.
    // The MinimalFileSize profile is used to to produce a minimal file size
    pProfile = (TPdfToolsOptimizationProfiles_Profile*)PdfToolsOptimizationProfiles_MinimalFileSize_New();

    // Optionally the profile's parameters can be changed according to the
    // requirements of your optimization process.
    // Set the profile to flatten annotations (include as well Forms and Links)
    TPdfToolsOptimization_RemovalOptions* pRemovalOptions =
        PdfToolsOptimizationProfiles_Profile_GetRemovalOptions(pProfile);
    PdfToolsOptimization_RemovalOptions_SetAnnotations(pRemovalOptions,
                                                       ePdfToolsOptimization_ConversionStrategy_Flatten);
    PdfToolsOptimization_RemovalOptions_SetFormFields(pRemovalOptions,
                                                      ePdfToolsOptimization_ConversionStrategy_Flatten);
    PdfToolsOptimization_RemovalOptions_SetLinks(pRemovalOptions, ePdfToolsOptimization_ConversionStrategy_Flatten);

    // Optimize the document
    pOptimizer = PdfToolsOptimization_Optimizer_New();
    pOutDoc    = PdfToolsOptimization_Optimizer_OptimizeDocument(pOptimizer, pInDoc, &outDesc, pProfile, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("The processing has failed. (ErrorCode: 0x%08x).\n"),
                                     PdfTools_GetLastError());

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pOutDoc)
        PdfToolsPdf_Document_Close(pOutDoc);
    PdfTools_Release(pOptimizer);
    PdfTools_Release(pProfile);
    if (pOutStream)
        fclose(pOutStream);
    if (pInDoc)
        PdfToolsPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);

    PdfTools_Uninitialize();

    return iRet;
} 