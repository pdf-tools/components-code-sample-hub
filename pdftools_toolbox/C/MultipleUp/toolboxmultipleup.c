/****************************************************************************
 *
 * File:            toolboxmultipleup.c
 *
 * Usage:           toolboxmultipleup <inputPath> <outputPath>
 *                  
 * Title:           Place multiple pages on one page
 *                  
 * Description:     Place four pages of a PDF document on a single page.
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
#include <math.h>
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

int Usage()
{
    printf("Usage: toolboxmultipleup <inputPath> <outputPath>.\n");
    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

TPtxGeomReal_Size PageSize;
size_t            nBufSize;
TCHAR             szErrorBuff[1024];
int               nNx     = 2;
int               nNy     = 2;
double            dBorder = 10;

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

int _tmain(int argc, TCHAR* argv[])
{
    FILE*                            pOutStream = NULL;
    TPtxSys_StreamDescriptor         outDescriptor;
    TPtxPdf_Document*                pOutDoc      = NULL;
    TPtxPdf_PageList*                pOutPageList = NULL;
    FILE*                            pInStream    = NULL;
    TPtxSys_StreamDescriptor         descriptor;
    TPtxPdf_Document*                pInDoc       = NULL;
    TPtxPdf_PageList*                pInPageList  = NULL;
    TPtxPdf_Page*                    pInPage      = NULL;
    TPtxPdf_Page*                    pOutPage     = NULL;
    TPtxPdf_PageCopyOptions*         pCopyOptions = NULL;
    TPtxPdf_Conformance              iConformance;
    TPtxPdfContent_ContentGenerator* pGenerator = NULL;
    TPtxPdfContent_Group*            pGroup     = NULL;
    TCHAR*                           szInPath;
    TCHAR*                           szOutPath;
    int                              iReturnValue = 0;

    // Set page Size
    PageSize.dWidth  = 595.0;
    PageSize.dHeight = 842.0;

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 3 || argc > 3)
    {
        return Usage();
    }

    // Initialize library
    Ptx_Initialize();

    // Set and check license key
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(Ptx_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
                                      _T("Failed to set license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    szInPath  = argv[1];
    szOutPath = argv[2];

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL(pInStream, _T("Failed to open input file \"%s\".\n"), szInPath);
    PtxSysCreateFILEStreamDescriptor(&descriptor, pInStream, 0);
    pInDoc = PtxPdf_Document_Open(&descriptor, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Input file \"%s\" cannot be opened. %s (ErrorCode: 0x%08x).\n"),
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

    // Copy all pages
    pInPageList = PtxPdf_Document_GetPages(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageList,
                                     _T("Failed to get the pages of the input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pOutPageList = PtxPdf_Document_GetPages(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageList,
                                     _T("Failed to get pages of the output document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    int nPageCount = 0;
    for (int iPage = 0; iPage < PtxPdf_PageList_GetCount(pInPageList); iPage++)
    {
        pInPage = PtxPdf_PageList_Get(pInPageList, iPage);

        if (nPageCount == nNx * nNy)
        {
            // Add to output document
            PtxPdfContent_ContentGenerator_Close(pGenerator);
            GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_Add(pOutPageList, pOutPage),
                                              _T("Failed to add page to output document. %s (ErrorCode: 0x%08x).\n"),
                                              szErrorBuff, Ptx_GetLastError());
            Ptx_Release(pOutPage);
            pOutPage   = NULL;
            nPageCount = 0;
        }
        if (pOutPage == NULL)
        {
            // Create a new output page
            pOutPage = PtxPdf_Page_Create(pOutDoc, &PageSize);
            GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPage,
                                             _T("Failed to create a new output page. %s (ErrorCode: 0x%08x).\n"),
                                             szErrorBuff, Ptx_GetLastError());
            TPtxPdfContent_Content* pContent = PtxPdf_Page_GetContent(pOutPage);
            pGenerator                       = PtxPdfContent_ContentGenerator_New(pContent, FALSE);
            GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pGenerator,
                                             _T("Failed to create content generator. %s (ErrorCode: 0x%08x).\n"),
                                             szErrorBuff, Ptx_GetLastError());
        }

        // Get area where group has to be
        int x = nPageCount % nNx;
        int y = nNy - (nPageCount / nNx) - 1;

        // Calculate cell size
        TPtxGeomReal_Size cellSize;
        cellSize.dWidth  = (PageSize.dWidth - ((nNx + 1) * dBorder)) / nNx;
        cellSize.dHeight = (PageSize.dHeight - ((nNy + 1) * dBorder)) / nNy;

        // Calculate cell position
        TPtxGeomReal_Point cellPosition;
        cellPosition.dX = dBorder + x * (cellSize.dWidth + dBorder);
        cellPosition.dY = dBorder + y * (cellSize.dHeight + dBorder);

        // Copy page group from input to output
        pGroup = PtxPdfContent_Group_CopyFromPage(pOutDoc, pInPage, pCopyOptions);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
            pGroup, _T("Failed to copy page group from input to output. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
            Ptx_GetLastError());

        // Calculate group position
        TPtxGeomReal_Size groupSize;
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_Group_GetSize(pGroup, &groupSize),
                                          _T("%s (ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());
        double dScale = MIN(cellSize.dWidth / groupSize.dWidth, cellSize.dHeight / groupSize.dHeight);

        // Calculate target size
        TPtxGeomReal_Size targetSize;
        targetSize.dWidth  = groupSize.dWidth * dScale;
        targetSize.dHeight = groupSize.dHeight * dScale;

        // Calculate position
        TPtxGeomReal_Point targetPos;
        targetPos.dX = cellPosition.dX + ((cellSize.dWidth - targetSize.dWidth) / 2);
        targetPos.dY = cellPosition.dY + ((cellSize.dHeight - targetSize.dHeight) / 2);

        // Calculate rectangle
        TPtxGeomReal_Rectangle targetRect;
        targetRect.dLeft   = targetPos.dX;
        targetRect.dBottom = targetPos.dY;
        targetRect.dRight  = targetPos.dX + targetSize.dWidth;
        targetRect.dTop    = targetPos.dY + targetSize.dHeight;

        // Add group to page
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
            PtxPdfContent_ContentGenerator_PaintGroup(pGenerator, pGroup, &targetRect, NULL),
            _T("Failed to paint the group. %s (ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());

        if (pGroup != NULL)
        {
            Ptx_Release(pGroup);
            pGroup = NULL;
        }
        if (pInPage != NULL)
        {
            Ptx_Release(pInPage);
            pInPage = NULL;
        }

        nPageCount++;
    }

    // Add partially filled page
    if (pOutPage != NULL)
    {
        PtxPdfContent_ContentGenerator_Close(pGenerator);
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_Add(pOutPageList, pOutPage),
                                          _T("Failed to add page to output document. %s (ErrorCode: 0x%08x).\n"),
                                          szErrorBuff, Ptx_GetLastError());
        Ptx_Release(pOutPage);
        pOutPage = NULL;
    }


    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pGroup != NULL)
        Ptx_Release(pGroup);
    if (pOutPage != NULL)
        Ptx_Release(pOutPage);
    if (pOutPageList != NULL)
        Ptx_Release(pOutPageList);
    if (pInPage != NULL)
        Ptx_Release(pInPage);
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