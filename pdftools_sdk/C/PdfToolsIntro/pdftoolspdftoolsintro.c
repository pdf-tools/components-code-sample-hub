/****************************************************************************
 *
 * File:            pdftoolspdftoolsintro.c
 *
 * Usage:           pdftoolspdftoolsintro <coverImage> <contentPdfPath> <outputPath>
 *                  
 * Title:           Hello, Pdftools SDK!
 *                  
 * Description:     Add a cover page from an image to a PDF.
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
    printf("Usage: pdftoolspdftoolsintro <coverImage> <contentPdfPath> <outputPath>.\n");
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

    char*                                        szCoverImagePath  = argv[1];
    char*                                        szInContentPath   = argv[2];
    char*                                        szOutFinalPath    = argv[3];
    FILE*                                        pCoverImageStream = NULL;
    FILE*                                        pInputPdfStream   = NULL;
    FILE*                                        pOutFinalStream   = NULL;
    TPdfToolsImage_Document*                     pCoverImageDoc    = NULL;
    TPdfToolsPdf_Document*                       pOutCoverPdfDoc   = NULL;
    TPdfToolsPdf_Document*                       pInContentDoc     = NULL;
    TPdfToolsPdf_Document*                       pOutFinalDoc      = NULL;
    TPdfToolsImage2PdfProfiles_Profile*          pProfile          = NULL;
    TPdfToolsImage2Pdf_Converter*                pConverter        = NULL;
    TPdfToolsDocumentAssembly_DocumentAssembler* pAssembler        = NULL;

    TPdfToolsSys_StreamDescriptor inImageDesc, outImageDesc, inContentDesc, outFinalDesc;

    // Initialize library
    PdfTools_Initialize();

    // By default, a test license key is active. In this case, a watermark is added to the output. 
    // If you have a license key, please uncomment the following call and set the license key.
    // GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfTools_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
    //                                     _T("Failed to set the license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
    //                                     PdfTools_GetLastError());

    // 1. Open input image document using memory stream
    pCoverImageStream = _tfopen(szCoverImagePath, _T("rb"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pCoverImageStream, _T("Failed to open the input file \"%s\" for reading.\n"),
                                     szCoverImagePath);
    PdfToolsSysCreateFILEStreamDescriptor(&inImageDesc, pCoverImageStream, 0);
    pCoverImageDoc = PdfToolsImage_Document_Open(&inImageDesc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pCoverImageDoc, _T("Failed to create a document from the input file \"%s\". %s (ErrorCode: 0x%08x).\n"),
        szCoverImagePath, szErrorBuff, PdfTools_GetLastError());

    // 2. Create output stream in memory for the cover page (image as PDF)
    PdfToolsSys_MemoryStreamDescriptor_Create(&outImageDesc);
    pProfile        = (TPdfToolsImage2PdfProfiles_Profile*)PdfToolsImage2PdfProfiles_Default_New();
    pConverter      = PdfToolsImage2Pdf_Converter_New();
    pOutCoverPdfDoc = (TPdfToolsPdf_Document*)PdfToolsImage2Pdf_Converter_Convert(pConverter, pCoverImageDoc,
                                                                                  &outImageDesc, pProfile, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pOutCoverPdfDoc, "The processing 'Image to PDF' has failed. (ErrorCode: 0x%08x).\n", PdfTools_GetLastError());

    // 3. Open input content document in-memory
    pInputPdfStream = _tfopen(szInContentPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInputPdfStream, _T("Failed to open the input file \"%s\" for reading.\n"),
                                     szInContentPath);
    PdfToolsSysCreateFILEStreamDescriptor(&inContentDesc, pInputPdfStream, 0);
    pInContentDoc = PdfToolsPdf_Document_Open(&inContentDesc, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pInContentDoc, _T("Failed to create a document from the input file \"%s\". %s (ErrorCode: 0x%08x).\n"),
        szInContentPath, szErrorBuff, PdfTools_GetLastError());

    // 4. Create final output document in-memory
    pOutFinalStream = _tfopen(szOutFinalPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutFinalStream, _T("Failed to create output file \"%s\" for writing.\n"),
                                     szOutFinalPath);
    PdfToolsSysCreateFILEStreamDescriptor(&outFinalDesc, pOutFinalStream, 0);
    pAssembler = PdfToolsDocumentAssembly_DocumentAssembler_New(&outFinalDesc, NULL, NULL);

    // Define first and last page (only one page for the cover)
    int firstPage = 1;
    int lastPage  = 1;
    // 5. Append the first page of the image document to the final output
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PdfToolsDocumentAssembly_DocumentAssembler_Append(
                                          pAssembler, pOutCoverPdfDoc, &firstPage, &lastPage, NULL, NULL),
                                      "Failed to append the image document. (ErrorCode: 0x%08x).\n",
                                      PdfTools_GetLastError());

    // 6. Append content document to the final output
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
        PdfToolsDocumentAssembly_DocumentAssembler_Append(pAssembler, pInContentDoc, NULL, NULL, NULL, NULL),
        "Failed to append the content document. (ErrorCode: 0x%08x).\n", PdfTools_GetLastError());

    // 7. Merge input documents into an output document
    pOutFinalDoc = PdfToolsDocumentAssembly_DocumentAssembler_Assemble(pAssembler);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pOutFinalDoc,
        "The processing of merging the first page with the PDF content has failed. (ErrorCode: 0x%08x).\n",
        PdfTools_GetLastError());

    _tprintf(_T("Execution successful.\n"));

cleanup:
    // Release resources
    if (pCoverImageDoc)
        PdfToolsImage_Document_Close(pCoverImageDoc);
    if (pOutCoverPdfDoc)
        PdfToolsPdf_Document_Close(pOutCoverPdfDoc);
    if (pInContentDoc)
        PdfToolsPdf_Document_Close(pInContentDoc);
    if (pOutFinalDoc)
        PdfToolsPdf_Document_Close(pOutFinalDoc);
    if (pAssembler)
        PdfToolsDocumentAssembly_DocumentAssembler_Close(pAssembler);

    PdfTools_Release(pConverter);
    PdfTools_Release(pProfile);

    // Close stream descriptors
    PdfToolsSys_MemoryStreamDescriptor_Close(&outImageDesc);

    if (pCoverImageStream)
        fclose(pCoverImageStream);
    if (pInputPdfStream)
        fclose(pInputPdfStream);
    if (pOutFinalStream)
        fclose(pOutFinalStream);

    PdfTools_Uninitialize();

    return iRet;
}
