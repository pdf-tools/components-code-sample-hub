/****************************************************************************
 *
 * File:            toolboxaddimage.c
 *
 * Usage:           toolboxaddimage <inputPath> <imagePath> <pageNumber> <outputPath>
 *                  Example: in.pdf in.png 1 out.pdf
 *                  
 * Title:           Add image to PDF
 *                  
 * Description:     Place an image with a specified size at a specific
 *                  location of a page.
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
#include "PdfTools_Toolbox.h"

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

#define GOTO_CLEANUP_IF_NULL(inFile, ...) \
    do                                    \
    {                                     \
        if ((inFile) == NULL)             \
        {                                 \
            _tprintf(__VA_ARGS__);        \
            iReturnValue = 1;             \
            goto cleanup;                 \
        }                                 \
    } while (0);

#define GOTO_CLEANUP_IF_NULL_PRINT_ERROR(inVar, ...)                                      \
    do                                                                                    \
    {                                                                                     \
        if ((inVar) == NULL)                                                              \
        {                                                                                 \
            nBufSize = Ptx_GetLastErrorMessage(NULL, 0);                                  \
            Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                        \
            iReturnValue = 1;                                                             \
            goto cleanup;                                                                 \
        }                                                                                 \
    } while (0);

#define GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(outBool, ...)                                   \
    do                                                                                    \
    {                                                                                     \
        if ((outBool) == FALSE)                                                           \
        {                                                                                 \
            nBufSize = Ptx_GetLastErrorMessage(NULL, 0);                                  \
            Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                        \
            iReturnValue = 1;                                                             \
            goto cleanup;                                                                 \
        }                                                                                 \
    } while (0);

#define GOTO_CLEANUP_IF_ZERO_PRINT_ERROR(outDouble, ...)                                  \
    do                                                                                    \
    {                                                                                     \
        if ((outDouble) == 0.0)                                                           \
        {                                                                                 \
            nBufSize = Ptx_GetLastErrorMessage(NULL, 0);                                  \
            Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                        \
            iReturnValue = 1;                                                             \
            goto cleanup;                                                                 \
        }                                                                                 \
    } while (0);

int Usage()
{
    printf("Usage: toolboxaddimage <inputPath> <imagePath> <pageNumber> <outputPath>.\n");
    printf("       Example: in.pdf in.png 1 out.pdf\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

TPtxGeomReal_Size size;
size_t            nBufSize;
TCHAR             szErrorBuff[1024];
int               iReturnValue = 0;

int copyDocumentData(TPtxPdf_Document* pInDoc, TPtxPdf_Document* pOutDoc)
{
    TPtxPdf_FileReferenceList* pInFileRefList;
    TPtxPdf_FileReferenceList* pOutFileRefList;

    // Output intent
    if (PtxPdf_Document_GetOutputIntent(pInDoc) != NULL)
        if (PtxPdf_Document_SetOutputIntent(pOutDoc, PtxPdfContent_IccBasedColorSpace_Copy(
                                                         pOutDoc, PtxPdf_Document_GetOutputIntent(pInDoc))) == FALSE)
            return FALSE;

    // Metadata
    if (PtxPdf_Document_SetMetadata(pOutDoc, PtxPdf_Metadata_Copy(pOutDoc, PtxPdf_Document_GetMetadata(pInDoc))) ==
        FALSE)
        return FALSE;

    // Viewer settings
    if (PtxPdf_Document_SetViewerSettings(
            pOutDoc, PtxPdfNav_ViewerSettings_Copy(pOutDoc, PtxPdf_Document_GetViewerSettings(pInDoc))) == FALSE)
        return FALSE;

    // Associated files (for PDF/A-3 and PDF 2.0 only)
    pInFileRefList  = PtxPdf_Document_GetAssociatedFiles(pInDoc);
    pOutFileRefList = PtxPdf_Document_GetAssociatedFiles(pOutDoc);
    if (pInFileRefList == NULL || pOutFileRefList == NULL)
        return FALSE;
    for (int iFileRef = 0; iFileRef < PtxPdf_FileReferenceList_GetCount(pInFileRefList); iFileRef++)
        if (PtxPdf_FileReferenceList_Add(
                pOutFileRefList,
                PtxPdf_FileReference_Copy(pOutDoc, PtxPdf_FileReferenceList_Get(pInFileRefList, iFileRef))) == FALSE)
            return FALSE;

    // Plain embedded files
    pInFileRefList  = PtxPdf_Document_GetPlainEmbeddedFiles(pInDoc);
    pOutFileRefList = PtxPdf_Document_GetPlainEmbeddedFiles(pOutDoc);
    if (pInFileRefList == NULL || pOutFileRefList == NULL)
        return FALSE;
    for (int iFileRef = 0; iFileRef < PtxPdf_FileReferenceList_GetCount(pInFileRefList); iFileRef++)
        if (PtxPdf_FileReferenceList_Add(
                pOutFileRefList,
                PtxPdf_FileReference_Copy(pOutDoc, PtxPdf_FileReferenceList_Get(pInFileRefList, iFileRef))) == FALSE)
            return FALSE;

    return TRUE;
}
int addImage(TPtxPdf_Document* pOutDoc, TPtxPdf_Page* pOutPage, TCHAR* szImagePath, double x, double y)
{
    TPtxPdfContent_Content*          pContent   = NULL;
    TPtxPdfContent_ContentGenerator* pGenerator = NULL;
    TPtxSys_StreamDescriptor         imageDescriptor;
    FILE*                            pImageStream = NULL;
    TPtxPdfContent_Image*            pImage       = NULL;

    pContent = PtxPdf_Page_GetContent(pOutPage);

    // Create content generator
    pGenerator = PtxPdfContent_ContentGenerator_New(pContent, FALSE);

    // Load image from input path
    pImageStream = _tfopen(szImagePath, _T("rb"));
    PtxSysCreateFILEStreamDescriptor(&imageDescriptor, pImageStream, 0);

    // Create image object
    pImage = PtxPdfContent_Image_Create(pOutDoc, &imageDescriptor);

    double dResolution = 150.0;

    TPtxGeomInt_Size size;
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_Image_GetSize(pImage, &size),
                                      _T("Failed to get image size. %s(ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    // Calculate Rectangle for data matrix
    TPtxGeomReal_Rectangle rect;
    rect.dLeft   = x;
    rect.dBottom = y;
    rect.dRight  = x + (double)size.iWidth * 72.0 / dResolution;
    rect.dTop    = y + (double)size.iHeight * 72.0 / dResolution;

    // Paint image into the specified rectangle
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_ContentGenerator_PaintImage(pGenerator, pImage, &rect),
                                      _T("Failed to paint image. %s(ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

cleanup:
    if (pGenerator != NULL)
        PtxPdfContent_ContentGenerator_Close(pGenerator);
    if (pContent != NULL)
        Ptx_Release(pContent);

    return iReturnValue;
}

int _tmain(int argc, TCHAR* argv[])
{
    FILE*                    pInStream = NULL;
    TPtxSys_StreamDescriptor descriptor;
    TPtxPdf_Document*        pInDoc     = NULL;
    FILE*                    pOutStream = NULL;
    TPtxSys_StreamDescriptor outDescriptor;
    TPtxPdf_Document*        pOutDoc       = NULL;
    TPtxPdf_PageList*        pInPageList   = NULL;
    TPtxPdf_PageList*        pOutPageList  = NULL;
    TPtxPdf_PageList*        pInPageRange  = NULL;
    TPtxPdf_PageList*        pOutPageRange = NULL;
    TPtxPdf_Page*            pInPage       = NULL;
    TPtxPdf_Page*            pOutPage      = NULL;
    TPtxPdf_PageCopyOptions* pCopyOptions  = NULL;
    TPtxPdf_Conformance      iConformance;
    TCHAR*                   szInPath;
    TCHAR*                   szImagePath;
    TCHAR*                   szOutPath;
    int                      iPageNumber;

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 5 || argc > 5)
    {
        return Usage();
    }

    // Initialize library
    Ptx_Initialize();

    // Set and check license key
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(Ptx_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
                                      _T("Failed to set license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    szInPath    = argv[1];
    szImagePath = argv[2];
    iPageNumber = (int)atoi(argv[3]);
    szOutPath   = argv[4];

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL(pInStream, _T("Failed to open input file \"%s\".\n"), szInPath);
    PtxSysCreateFILEStreamDescriptor(&descriptor, pInStream, 0);
    pInDoc = PtxPdf_Document_Open(&descriptor, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Input file \"%s\" cannot cannot be opened. %s (ErrorCode: 0x%08x).\n"),
                                     szInPath, szErrorBuff, Ptx_GetLastError());

    // Create output document
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL(pOutStream, _T("Failed to open output file \"%s\".\n"), szOutPath);
    PtxSysCreateFILEStreamDescriptor(&outDescriptor, pOutStream, 0);
    iConformance = PtxPdf_Document_GetConformance(pInDoc);
    pOutDoc      = PtxPdf_Document_Create(&outDescriptor, &iConformance, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("Output file \"%s\" cannot be created. %s (ErrorCode: 0x%08x).\n"),
                                     szOutPath, szErrorBuff, Ptx_GetLastError());

    // Copy document-wide data
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(copyDocumentData(pInDoc, pOutDoc),
                                      _T("Failed to copy document-wide data. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    // Configure copy options
    pCopyOptions = PtxPdf_PageCopyOptions_New();

    // Get input and output page lists
    pInPageList = PtxPdf_Document_GetPages(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageList,
                                     _T("Failed to get the pages of the input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pOutPageList = PtxPdf_Document_GetPages(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageList,
                                     _T("Failed to get the pages of the output document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Copy pages preceding selected page
    pInPageRange = PtxPdf_PageList_GetRange(pInPageList, 0, iPageNumber - 1);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageRange, _T("Failed to get page range. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pOutPageRange = PtxPdf_PageList_Copy(pOutDoc, pInPageRange, pCopyOptions);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageRange, _T("Failed to copy page range. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_AddRange(pOutPageList, pOutPageRange),
                                      _T("Failed to add page range. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());
    Ptx_Release(pInPageRange);
    pInPageRange = NULL;
    Ptx_Release(pOutPageRange);
    pOutPageRange = NULL;

    // Copy selected page an add image
    pInPage = PtxPdf_PageList_Get(pInPageList, iPageNumber - 1);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPage, _T("Failed to get page. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                     Ptx_GetLastError());
    pOutPage = PtxPdf_Page_Copy(pOutDoc, pInPage, pCopyOptions);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPage, _T("Failed to copy page. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                     Ptx_GetLastError());
    if (addImage(pOutDoc, pOutPage, szImagePath, 150.0, 150.0) != 0)
        goto cleanup;
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_Add(pOutPageList, pOutPage),
                                      _T("Failed to add page. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    // Copy remaining pages
    pInPageRange = PtxPdf_PageList_GetRange(pInPageList, 1, PtxPdf_PageList_GetCount(pInPageList) - 1);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageRange,
                                     _T("Failed to get page range from input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pOutPageRange = PtxPdf_PageList_Copy(pOutDoc, pInPageRange, pCopyOptions);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageRange,
                                     _T("Failed to copy page range to output document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_AddRange(pOutPageList, pOutPageRange),
                                      _T("Failed to add page range to output page list. %s (ErrorCode: 0x%08x).\n"),
                                      szErrorBuff, Ptx_GetLastError());

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pOutPage != NULL)
        Ptx_Release(pOutPage);
    if (pInPage != NULL)
        Ptx_Release(pInPage);
    if (pInPageRange != NULL)
        Ptx_Release(pInPageRange);
    if (pOutPageRange != NULL)
        Ptx_Release(pOutPageRange);
    if (pOutPageList != NULL)
        Ptx_Release(pOutPageList);
    if (pInPageList != NULL)
        Ptx_Release(pInPageList);
    if (pOutDoc != NULL)
        PtxPdf_Document_Close(pOutDoc);
    if (pOutStream != NULL)
        fclose(pOutStream);
    if (pInDoc != NULL)
        PtxPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);
    Ptx_Uninitialize();

    return iReturnValue;
} 