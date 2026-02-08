/****************************************************************************
 *
 * File:            pdftoolsmultipleimg2pdf.c
 *
 * Usage:           pdftoolsmultipleimg2pdf <inputPath> [<inputPath2> ...] <outputPath>
 *
 * Title:           Convert multiple images to a PDF
 *
 * Description:     Convert a list of images into a single PDF. Supported
 *                  image types are TIFF, JPEG, BMP, GIF, PNG, JBIG2, and
 *                  JPEG2000.
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

#define MAX_INPUTS 100

int Usage()
{
    printf("Usage: pdftoolsmultipleimg2pdf <inputPath> [<inputPath2> ...] <outputPath>.\n");
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

    TCHAR*                              szOutPath    = argv[argc - 1];
    int                                 nInputCount  = argc - 2;
    FILE*                               pInStreams[MAX_INPUTS]  = {NULL};
    TPdfToolsImage_Document*            pInDocs[MAX_INPUTS]     = {NULL};
    FILE*                               pOutStream   = NULL;
    TPdfToolsPdf_Document*              pOutDoc      = NULL;
    TPdfToolsImage_DocumentList*        pDocList     = NULL;
    TPdfToolsImage2PdfProfiles_Profile* pProfile     = NULL;
    TPdfToolsImage2Pdf_Converter*       pConverter   = NULL;

    // Initialize library
    PdfTools_Initialize();

    // By default, a test license key is active. In this case, a watermark is added to the output.
    // If you have a license key, please uncomment the following call and set the license key.
    // GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfTools_Sdk_Initialize(_T("<PDFSDK,V1,MGAASQD6L2JMQHL54PK08RQX8GG4SS0M8DAHVPH0VMP3NB8R9DUK>"), NULL),
    //                                     _T("Failed to set the license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
    //                                     PdfTools_GetLastError());

    // Create document list for input images
    pDocList = PdfToolsImage_DocumentList_New();
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pDocList, _T("Failed to create document list. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, PdfTools_GetLastError());

    // Open each input image and add to the document list
    for (int i = 0; i < nInputCount; i++)
    {
        TCHAR* szInPath = argv[i + 1];
        pInStreams[i]   = _tfopen(szInPath, _T("rb"));
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInStreams[i], _T("Failed to open the input file \"%s\" for reading.\n"),
                                         szInPath);
        TPdfToolsSys_StreamDescriptor inDesc;
        PdfToolsSysCreateFILEStreamDescriptor(&inDesc, pInStreams[i], 0);
        pInDocs[i] = PdfToolsImage_Document_Open(&inDesc);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
            pInDocs[i], _T("Failed to create a document from the input file \"%s\". %s (ErrorCode: 0x%08x).\n"),
            szInPath, szErrorBuff, PdfTools_GetLastError());

        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfToolsImage_DocumentList_Add(pDocList, pInDocs[i]),
                                          _T("Failed to add document to list. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                          PdfTools_GetLastError());
    }

    // Create output stream for writing
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to open the output file \"%s\" for writing.\n"), szOutPath);
    TPdfToolsSys_StreamDescriptor outDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);

    // Create the profile that defines the conversion parameters.
    // The Default profile converts images to PDF documents.
    pProfile = (TPdfToolsImage2PdfProfiles_Profile*)PdfToolsImage2PdfProfiles_Default_New();

    // Convert the images to a single PDF document
    pConverter = PdfToolsImage2Pdf_Converter_New();
    pOutDoc    = (TPdfToolsPdf_Document*)PdfToolsImage2Pdf_Converter_ConvertMultiple(pConverter, pDocList, &outDesc,
                                                                                     pProfile, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("The processing has failed. (ErrorCode: 0x%08x).\n"),
                                     PdfTools_GetLastError());

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pOutDoc)
        PdfToolsPdf_Document_Close(pOutDoc);
    PdfTools_Release(pConverter);
    PdfTools_Release(pProfile);
    PdfTools_Release(pDocList);
    if (pOutStream)
        fclose(pOutStream);
    for (int i = nInputCount - 1; i >= 0; i--)
    {
        if (pInDocs[i])
            PdfToolsImage_Document_Close(pInDocs[i]);
        if (pInStreams[i])
            fclose(pInStreams[i]);
    }

    PdfTools_Uninitialize();

    return iRet;
}
