/****************************************************************************
 *
 * File:            toolboxcreatebooklet.c
 *
 * Usage:           toolboxcreatebooklet <inputPath> <outputPath>
 *                  
 * Title:           Create a booklet from PDF
 *                  
 * Description:     Place up to two A4 pages in the right order on an A3
 *                  page, so that duplex printing and folding the A3 pages
 *                  results in a booklet.
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
#include <stdbool.h>
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

#define GOTO_CLEANUP_IF_NONZERO(val, ...) \
    do                                    \
    {                                     \
        if ((val) != 0)                   \
        {                                 \
            _tprintf(__VA_ARGS__);        \
            iReturnValue = 1;             \
            goto cleanup;                 \
        }                                 \
    } while (0);

#define GOTO_CLEANUP_IF_NULL(val, ...) \
    do                                 \
    {                                  \
        if ((val) == NULL)             \
        {                              \
            _tprintf(__VA_ARGS__);     \
            iReturnValue = 1;          \
            goto cleanup;              \
        }                              \
    } while (0);

#define GOTO_CLEANUP_IF_NULL_PRINT_ERROR(val, ...)                                        \
    do                                                                                    \
    {                                                                                     \
        if ((val) == NULL)                                                                \
        {                                                                                 \
            nBufSize = Ptx_GetLastErrorMessage(NULL, 0);                                  \
            Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                        \
            iReturnValue = 1;                                                             \
            goto cleanup;                                                                 \
        }                                                                                 \
    } while (0);

#define GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(val, ...)                                       \
    do                                                                                    \
    {                                                                                     \
        if (!(val))                                                                       \
        {                                                                                 \
            nBufSize = Ptx_GetLastErrorMessage(NULL, 0);                                  \
            Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            _tprintf(__VA_ARGS__);                                                        \
            iReturnValue = 1;                                                             \
            goto cleanup;                                                                 \
        }                                                                                 \
    } while (0);

#define GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(...)                                            \
    do                                                                                    \
    {                                                                                     \
        if (Ptx_GetLastError() != ePtx_Error_Success)                                     \
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
    printf("Usage: toolboxcreatebooklet <inputPath> <outputPath>.\n");
    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

TPtxGeomReal_Size pageSize;
double            dBorder = 10.0;
double            dCellWidth;
double            dCellHeight;
double            dCellLeft;
double            dCellRight;
double            dCellYPos;
TCHAR             szErrorBuff[1024];
size_t            nBufSize;
int               iReturnValue = 0;

int copyDocumentData(TPtxPdf_Document* pInDoc, TPtxPdf_Document* pOutDoc)
{
    // Objects that need releasing or closing
    TPtxPdfContent_IccBasedColorSpace* pInOutputIntent    = NULL;
    TPtxPdfContent_IccBasedColorSpace* pOutOutputIntent   = NULL;
    TPtxPdf_Metadata*                  pInMetadata        = NULL;
    TPtxPdf_Metadata*                  pOutMetadata       = NULL;
    TPtxPdfNav_ViewerSettings*         pInViewerSettings  = NULL;
    TPtxPdfNav_ViewerSettings*         pOutViewerSettings = NULL;
    TPtxPdf_FileReferenceList*         pInFileRefList     = NULL;
    TPtxPdf_FileReferenceList*         pOutFileRefList    = NULL;
    TPtxPdf_FileReference*             pInFileRef         = NULL;
    TPtxPdf_FileReference*             pOutFileRef        = NULL;

    iReturnValue = 0;

    // Output intent
    pInOutputIntent = PtxPdf_Document_GetOutputIntent(pInDoc);
    if (pInOutputIntent != NULL)
    {
        pOutOutputIntent = PtxPdfContent_IccBasedColorSpace_Copy(pOutDoc, pInOutputIntent);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutOutputIntent,
                                         _T("Failed to copy ICC-based color space. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Document_SetOutputIntent(pOutDoc, pOutOutputIntent),
                                          _T("Failed to set output intent. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
    }
    else
        GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get output intent. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());

    // Metadata
    pInMetadata = PtxPdf_Document_GetMetadata(pInDoc);
    if (pInMetadata != NULL)
    {
        pOutMetadata = PtxPdf_Metadata_Copy(pOutDoc, pInMetadata);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutMetadata, _T("Failed to copy metadata. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Document_SetMetadata(pOutDoc, pOutMetadata),
                                          _T("Failed to set metadata. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
    }
    else
        GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get metadata. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());

    // Viewer settings
    pInViewerSettings = PtxPdf_Document_GetViewerSettings(pInDoc);
    if (pInViewerSettings != NULL)
    {
        pOutViewerSettings = PtxPdfNav_ViewerSettings_Copy(pOutDoc, pInViewerSettings);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutViewerSettings,
                                         _T("Failed to copy viewer settings. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                         Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Document_SetViewerSettings(pOutDoc, pOutViewerSettings),
                                          _T("Failed to set viewer settings. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
    }
    else
        GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get viewer settings. %s (ErrorCode: 0x%08x)"), szErrorBuff,
                                          Ptx_GetLastError());

    // Associated files (for PDF/A-3 and PDF 2.0 only)
    pInFileRefList = PtxPdf_Document_GetAssociatedFiles(pInDoc);
    GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get associated files of input document. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());
    pOutFileRefList = PtxPdf_Document_GetAssociatedFiles(pOutDoc);
    GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get associated files of output document. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());
    int nFileRefs = PtxPdf_FileReferenceList_GetCount(pInFileRefList);
    GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get count of associated files. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());
    for (int iFileRef = 0; iFileRef < nFileRefs; iFileRef++)
    {
        pInFileRef = PtxPdf_FileReferenceList_Get(pInFileRefList, iFileRef);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInFileRef, _T("Failed to get file reference. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());
        pOutFileRef = PtxPdf_FileReference_Copy(pOutDoc, pInFileRef);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutFileRef, _T("Failed to copy file reference. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_FileReferenceList_Add(pOutFileRefList, pOutFileRef),
                                          _T("Failed to add file reference. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
        Ptx_Release(pInFileRef);
        pInFileRef = NULL;
        Ptx_Release(pOutFileRef);
        pOutFileRef = NULL;
    }
    Ptx_Release(pInFileRefList);
    pInFileRefList = NULL;
    Ptx_Release(pOutFileRefList);
    pOutFileRefList = NULL;

    // Plain embedded files
    pInFileRefList = PtxPdf_Document_GetPlainEmbeddedFiles(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pInFileRefList, _T("Failed to get plain embedded files of input document %s (ErrorCode: 0x%08x)\n"),
        szErrorBuff, Ptx_GetLastError());
    pOutFileRefList = PtxPdf_Document_GetPlainEmbeddedFiles(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
        pInFileRefList, _T("Failed to get plain embedded files of output document %s (ErrorCode: 0x%08x)\n"),
        szErrorBuff, Ptx_GetLastError());
    nFileRefs = PtxPdf_FileReferenceList_GetCount(pInFileRefList);
    GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get count of plain embedded files. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());
    for (int iFileRef = 0; iFileRef < nFileRefs; iFileRef++)
    {
        pInFileRef = PtxPdf_FileReferenceList_Get(pInFileRefList, iFileRef);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInFileRef, _T("Failed to get file reference. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());
        pOutFileRef = PtxPdf_FileReference_Copy(pOutDoc, pInFileRef);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutFileRef, _T("Failed to copy file reference. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_FileReferenceList_Add(pOutFileRefList, pOutFileRef),
                                          _T("Failed to add file reference. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
        Ptx_Release(pInFileRef);
        pInFileRef = NULL;
        Ptx_Release(pOutFileRef);
        pOutFileRef = NULL;
    }

cleanup:
    if (pInOutputIntent != NULL)
        Ptx_Release(pInOutputIntent);
    if (pOutOutputIntent != NULL)
        Ptx_Release(pOutOutputIntent);
    if (pInMetadata != NULL)
        Ptx_Release(pInMetadata);
    if (pOutMetadata != NULL)
        Ptx_Release(pOutMetadata);
    if (pInViewerSettings != NULL)
        Ptx_Release(pInViewerSettings);
    if (pOutViewerSettings != NULL)
        Ptx_Release(pOutViewerSettings);
    if (pInFileRefList != NULL)
        Ptx_Release(pInFileRefList);
    if (pOutFileRefList != NULL)
        Ptx_Release(pOutFileRefList);
    if (pInFileRef != NULL)
        Ptx_Release(pInFileRef);
    if (pOutFileRef != NULL)
        Ptx_Release(pOutFileRef);
    return iReturnValue;
}

int StampPageNumber(TPtxPdf_Document* pDocument, TPtxPdfContent_Font* pFont,
                    TPtxPdfContent_ContentGenerator* pGenerator, int nPageNo, BOOL bIsLeftPage)
{
    // Objects that need releasing or closing
    TPtxPdfContent_Text*          pText          = NULL;
    TPtxPdfContent_TextGenerator* pTextGenerator = NULL;

    // Create text object
    pText = PtxPdfContent_Text_Create(pDocument);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pText, _T("Failed to create text object. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                     Ptx_GetLastError());

    // Create text generator
    pTextGenerator = PtxPdfContent_TextGenerator_New(pText, pFont, 8.0, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pTextGenerator, _T("Failed to create text generator. %s (ErrorCode: 0x%08x)\n"),
                                     szErrorBuff, Ptx_GetLastError());

    TCHAR szStampText[50];
    _stprintf(szStampText, _T("Page %d"), nPageNo);

    // Get width of stamp text
    double dStampWidth = PtxPdfContent_TextGenerator_GetWidth(pTextGenerator, szStampText);
    if (dStampWidth == 0.0)
        GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get text width. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());

    // Compute position
    TPtxGeomReal_Point point = {
        .dX = bIsLeftPage ? dBorder + 0.5 * dCellWidth - dStampWidth / 2
                          : 2 * dBorder + 1.5 * dCellWidth - dStampWidth / 2,
        .dY = dBorder,
    };

    // Move to position
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_TextGenerator_MoveTo(pTextGenerator, &point),
                                      _T("Failed to move to position. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                      Ptx_GetLastError());
    // Add page number
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_TextGenerator_Show(pTextGenerator, szStampText),
                                      _T("Failed to show text. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                      Ptx_GetLastError());

    BOOL bClose    = PtxPdfContent_TextGenerator_Close(pTextGenerator);
    pTextGenerator = NULL;
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(bClose, _T("Failed to close text generator. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());

    // Paint the positioned text
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_ContentGenerator_PaintText(pGenerator, pText),
                                      _T("Failed to paint text. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                      Ptx_GetLastError());

cleanup:
    if (pText != NULL)
        Ptx_Release(pText);
    if (pTextGenerator != NULL)
        PtxPdfContent_TextGenerator_Close(pTextGenerator);
    return iReturnValue;
}

void ComputeTargetRect(TPtxGeomReal_Rectangle* pRectangle, const TPtxGeomReal_Size* pBBox, BOOL bIsLeftPage)
{
    // Compute factor for fitting page into rectangle
    double dScale       = MIN(dCellWidth / pBBox->dWidth, dCellHeight / pBBox->dHeight);
    double dGroupWidth  = pBBox->dWidth * dScale;
    double dGroupHeight = pBBox->dHeight * dScale;

    // Compute x-value
    double dGroupXPos =
        bIsLeftPage ? dCellLeft + (dCellWidth - dGroupWidth) / 2 : dCellRight + (dCellWidth - dGroupWidth) / 2;

    // Compute y-value
    double dGroupYPos = dCellYPos + (dCellHeight - dGroupHeight) / 2;

    // Set rectangle
    pRectangle->dLeft   = dGroupXPos;
    pRectangle->dBottom = dGroupYPos;
    pRectangle->dRight  = dGroupXPos + dGroupWidth;
    pRectangle->dTop    = dGroupYPos + dGroupHeight;
}

int CreateBooklet(TPtxPdf_PageList* pInDocList, TPtxPdf_Document* pOutDoc, TPtxPdf_PageList* pOutDocList,
                  int nLeftPageIndex, int nRightPageIndex, TPtxPdfContent_Font* pFont)
{
    // Objects that need releasing or closing
    TPtxPdf_PageCopyOptions*         pCopyOptions = NULL;
    TPtxPdf_Page*                    pOutPage     = NULL;
    TPtxPdfContent_Content*          pContent     = NULL;
    TPtxPdfContent_ContentGenerator* pGenerator   = NULL;
    TPtxPdf_Page*                    pInPage      = NULL;
    TPtxPdfContent_Group*            pGroup       = NULL;

    // Configure copy options
    pCopyOptions = PtxPdf_PageCopyOptions_New();

    // Create page object
    pOutPage = PtxPdf_Page_Create(pOutDoc, &pageSize);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPage, _T("Failed to create page object. %s (ErrorCode: 0x%08x)\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Create content generator
    pContent = PtxPdf_Page_GetContent(pOutPage);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pContent, _T("Failed to get content. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                     Ptx_GetLastError());
    pGenerator = PtxPdfContent_ContentGenerator_New(pContent, FALSE);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pGenerator, _T("Failed to create content generator. %s (ErrorCode: 0x%08x)\n"),
                                     szErrorBuff, Ptx_GetLastError());

    int nPageCount = PtxPdf_PageList_GetCount(pInDocList);
    GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get page list count. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                      Ptx_GetLastError());

    // Left page
    if (nLeftPageIndex < nPageCount)
    {
        // Get the input page
        pInPage = PtxPdf_PageList_Get(pInDocList, nLeftPageIndex);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPage, _T("Failed to get page. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                         Ptx_GetLastError());

        // Copy page from input to output
        pGroup = PtxPdfContent_Group_CopyFromPage(pOutDoc, pInPage, pCopyOptions);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pGroup, _T("Failed to copy page as group. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());

        // Compute group location
        TPtxGeomReal_Size groupSize;
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_Group_GetSize(pGroup, &groupSize),
                                          _T("Failed to get group size. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
        TPtxGeomReal_Rectangle targetRect;
        ComputeTargetRect(&targetRect, &groupSize, TRUE);

        // Paint group at location
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
            PtxPdfContent_ContentGenerator_PaintGroup(pGenerator, pGroup, &targetRect, NULL),
            _T("Failed to paint group. %s (ErrorCode: 0x%08x)\n"), szErrorBuff, Ptx_GetLastError());

        // Add page number to page
        if (StampPageNumber(pOutDoc, pFont, pGenerator, nLeftPageIndex + 1, TRUE) != 0)
            goto cleanup;

        Ptx_Release(pInPage);
        pInPage = NULL;
        Ptx_Release(pGroup);
        pGroup = NULL;
    }

    // Right page
    if (nRightPageIndex < nPageCount)
    {
        // Get the input Page
        pInPage = PtxPdf_PageList_Get(pInDocList, nRightPageIndex);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPage, _T("Failed to get page. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                         Ptx_GetLastError());

        // Copy page from input to output
        pGroup = PtxPdfContent_Group_CopyFromPage(pOutDoc, pInPage, pCopyOptions);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pGroup, _T("Failed to copy page as group. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());

        // Compute group location
        TPtxGeomReal_Size groupSize;
        PtxPdfContent_Group_GetSize(pGroup, &groupSize);
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_Group_GetSize(pGroup, &groupSize),
                                          _T("Failed to get group size. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
        TPtxGeomReal_Rectangle targetRect;
        ComputeTargetRect(&targetRect, &groupSize, FALSE);

        // Paint group on the Computed rectangle
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
            PtxPdfContent_ContentGenerator_PaintGroup(pGenerator, pGroup, &targetRect, NULL),
            _T("Failed to paint group. %s (ErrorCode: 0x%08x)\n"), szErrorBuff, Ptx_GetLastError());

        // Add page number to page
        if (StampPageNumber(pOutDoc, pFont, pGenerator, nRightPageIndex + 1, FALSE) != 0)
            goto cleanup;
    }

    BOOL bClose = PtxPdfContent_ContentGenerator_Close(pGenerator);
    pGenerator  = NULL;
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(bClose, _T("Failed to close content generator. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());

    // Add page to output document
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_Add(pOutDocList, pOutPage),
                                      _T("Failed to add page to output document. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());

cleanup:
    if (pGenerator != NULL)
        PtxPdfContent_ContentGenerator_Close(pGenerator);
    if (pCopyOptions != NULL)
        Ptx_Release(pCopyOptions);
    if (pOutPage != NULL)
        Ptx_Release(pOutPage);
    if (pContent != NULL)
        Ptx_Release(pContent);
    if (pInPage != NULL)
        Ptx_Release(pInPage);
    if (pGroup != NULL)
        Ptx_Release(pGroup);
    return iReturnValue;
}

int _tmain(int argc, TCHAR* argv[])
{
    // Objects that need releasing or closing
    FILE*                pInStream    = NULL;
    TPtxPdf_Document*    pInDoc       = NULL;
    FILE*                pOutStream   = NULL;
    TPtxPdf_Document*    pOutDoc      = NULL;
    TPtxPdfContent_Font* pFont        = NULL;
    TPtxPdf_PageList*    pInPageList  = NULL;
    TPtxPdf_PageList*    pOutPageList = NULL;
    TPtxPdf_Conformance  iConformance;

    // A3 portrait
    pageSize.dWidth  = 1190;
    pageSize.dHeight = 842;
    dCellWidth       = (pageSize.dWidth - 3 * dBorder) / 2;
    dCellHeight      = (pageSize.dHeight - 2 * dBorder);
    dCellLeft        = dBorder;
    dCellRight       = 2 * dBorder + dCellWidth;
    dCellYPos        = dBorder;

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
                                      _T("Failed to set license key. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                      Ptx_GetLastError());

    TCHAR* szInPath  = argv[1];
    TCHAR* szOutPath = argv[2];

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL(pInStream, _T("Failed to open input file \"%s\".\n"), szInPath);
    TPtxSys_StreamDescriptor inDescriptor;
    PtxSysCreateFILEStreamDescriptor(&inDescriptor, pInStream, 0);
    pInDoc = PtxPdf_Document_Open(&inDescriptor, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Input file \"%s\" cannot be opened. %s (ErrorCode: 0x%08x)\n"),
                                     szInPath, szErrorBuff, Ptx_GetLastError());

    // Create output document
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL(pOutStream, _T("Failed to open output file \"%s\".\n"), szOutPath);
    TPtxSys_StreamDescriptor outDescriptor;
    PtxSysCreateFILEStreamDescriptor(&outDescriptor, pOutStream, 0);
    iConformance = PtxPdf_Document_GetConformance(pInDoc);
    if (iConformance == 0)
        GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get conformance. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
    pOutDoc = PtxPdf_Document_Create(&outDescriptor, &iConformance, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("Output file \"%s\" cannot be created. %s (ErrorCode: 0x%08x)\n"),
                                     szOutPath, szErrorBuff, Ptx_GetLastError());

    // Create font
    pFont = PtxPdfContent_Font_CreateFromSystem(pOutDoc, _T("Arial"), _T("Italic"), TRUE);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pFont, _T("Failed to create font. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                     Ptx_GetLastError());

    // Copy document-wide data
    if (copyDocumentData(pInDoc, pOutDoc) != 0)
        goto cleanup;

    // Copy pages
    pInPageList = PtxPdf_Document_GetPages(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageList,
                                     _T("Failed to get the pages of the input document. %s (ErrorCode: 0x%08x)\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pOutPageList = PtxPdf_Document_GetPages(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageList,
                                     _T("Failed to get the pages of the output document. %s (ErrorCode: 0x%08x)\n"),
                                     szErrorBuff, Ptx_GetLastError());
    int nNumberOfSheets = (PtxPdf_PageList_GetCount(pInPageList) + 3) / 4;

    for (int nSheetNumber = 0; nSheetNumber < nNumberOfSheets; nSheetNumber++)
    {
        // Add on front side
        if (CreateBooklet(pInPageList, pOutDoc, pOutPageList, 4 * nNumberOfSheets - 2 * nSheetNumber - 1,
                          2 * nSheetNumber, pFont) != 0)
            goto cleanup;

        // Add on back side
        if (CreateBooklet(pInPageList, pOutDoc, pOutPageList, 2 * nSheetNumber + 1,
                          4 * nNumberOfSheets - 2 * nSheetNumber - 2, pFont) != 0)
            goto cleanup;
    }

    // Close documents and files
    BOOL bClose = PtxPdf_Document_Close(pOutDoc);
    pOutDoc     = NULL;
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(bClose, _T("Failed to close the output document. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());
    int iClose = fclose(pOutStream);
    pOutStream = NULL;
    GOTO_CLEANUP_IF_NONZERO(iClose, _T("Failed to close the output file.\n"));
    bClose = PtxPdf_Document_Close(pInDoc);
    pInDoc = NULL;
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(bClose, _T("Failed to close the input document. %s (ErrorCode: 0x%08x)\n"),
                                      szErrorBuff, Ptx_GetLastError());
    iClose    = fclose(pInStream);
    pInStream = NULL;
    GOTO_CLEANUP_IF_NONZERO(iClose, _T("Failed to close the input file.\n"));

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pOutDoc != NULL)
        PtxPdf_Document_Close(pOutDoc);
    if (pOutStream != NULL)
        fclose(pOutStream);
    if (pInDoc != NULL)
        PtxPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);
    if (pFont != NULL)
        Ptx_Release(pFont);
    if (pInPageList != NULL)
        Ptx_Release(pInPageList);
    if (pOutPageList != NULL)
        Ptx_Release(pOutPageList);

    Ptx_Uninitialize();

    return iReturnValue;
} 