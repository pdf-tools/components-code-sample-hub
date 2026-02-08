/****************************************************************************
 *
 * File:            pdftoolsimg2pdfaccessibility.c
 *
 * Usage:           pdftoolsimg2pdfaccessibility <inputPath> <alternateText> <outputPath>
 *
 * Title:           Convert an image to an accessible PDF/A document
 *
 * Description:     Convert an image to an accessible PDF/A-2a document.
 *                  Alternative text is added to the image, as required for
 *                  PDF/A level A, to ensure accessibility.
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
    printf("Usage: pdftoolsimg2pdfaccessibility <inputPath> <alternateText> <outputPath>.\n");
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
    if (argc < 4 || argc > 4)
    {
        return Usage();
    }

    TCHAR*                              szInPath        = argv[1];
    TCHAR*                              szAlternateText = argv[2];
    TCHAR*                              szOutPath       = argv[3];
    FILE*                               pInStream       = NULL;
    FILE*                               pOutStream      = NULL;
    TPdfToolsImage_Document*            pInDoc          = NULL;
    TPdfToolsPdf_Document*              pOutDoc         = NULL;
    TPdfToolsImage2PdfProfiles_Archive* pProfile        = NULL;
    TPdfToolsImage2Pdf_Converter*       pConverter      = NULL;

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
    pInDoc = PdfToolsImage_Document_Open(&inDesc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pInDoc, _T("Failed to create a document from the input file \"%s\". %s (ErrorCode: 0x%08x).\n"), szInPath,
        szErrorBuff, PdfTools_GetLastError());

    // Create output stream for writing
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutStream, _T("Failed to open the output file \"%s\" for writing.\n"), szOutPath);
    TPdfToolsSys_StreamDescriptor outDesc;
    PdfToolsSysCreateFILEStreamDescriptor(&outDesc, pOutStream, 0);

    // Create the Archive profile for PDF/A conversion
    pProfile = PdfToolsImage2PdfProfiles_Archive_New();
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pProfile, _T("Failed to create Archive profile. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, PdfTools_GetLastError());

    // Set conformance to PDF/A-2a
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
        PdfToolsImage2PdfProfiles_Archive_SetConformance(pProfile, ePdfToolsPdf_Conformance_PdfA2A),
        _T("Failed to set conformance. %s (ErrorCode: 0x%08x).\n"), szErrorBuff, PdfTools_GetLastError());

    // Set the document language
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
        PdfToolsImage2PdfProfiles_Archive_SetLanguageA(pProfile, "en"),
        _T("Failed to set language. %s (ErrorCode: 0x%08x).\n"), szErrorBuff, PdfTools_GetLastError());

    // Add alternate text for the image to ensure accessibility
    TPdfTools_StringList* pAltTexts =
        PdfToolsImage2PdfProfiles_Archive_GetAlternateText(pProfile);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pAltTexts, _T("Failed to get alternate text list. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, PdfTools_GetLastError());
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfTools_StringList_Add(pAltTexts, szAlternateText),
                                      _T("Failed to add alternate text. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      PdfTools_GetLastError());

    // Convert the image to a PDF document
    pConverter = PdfToolsImage2Pdf_Converter_New();
    pOutDoc    = (TPdfToolsPdf_Document*)PdfToolsImage2Pdf_Converter_Convert(
        pConverter, pInDoc, &outDesc, (TPdfToolsImage2PdfProfiles_Profile*)pProfile, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("The processing has failed. (ErrorCode: 0x%08x).\n"),
                                     PdfTools_GetLastError());

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pOutDoc)
        PdfToolsPdf_Document_Close(pOutDoc);
    PdfTools_Release(pConverter);
    PdfTools_Release(pProfile);
    if (pOutStream)
        fclose(pOutStream);
    if (pInDoc)
        PdfToolsImage_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);

    PdfTools_Uninitialize();

    return iRet;
}
