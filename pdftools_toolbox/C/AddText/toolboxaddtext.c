/****************************************************************************
 *
 * File:            toolboxaddtext.c
 *
 * Usage:           toolboxaddtext <inputPath> <textString> <outputPath>
 *                  Example: in.pdf \"Test String\" out.pdf
 *                  
 * Title:           Add text to PDF
 *                  
 * Description:     Add text at a specified position on the first page of a
 *                  PDF document.
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
    printf("Usage: toolboxaddtext <inputPath> <textString> <outputPath>.\n");
    printf("       Example: in.pdf \"Test String\" out.pdf\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

size_t nBufSize;
TCHAR  szErrorBuff[1024];
double dBorder      = 40.0;
int    iReturnValue = 0;

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
int addText(TPtxPdf_Document* pOutDoc, TPtxPdf_Page* pOutPage, TCHAR* szTextString, TPtxPdfContent_Font* pFont,
            double dFontSize)
{
    TPtxPdfContent_Content*          pContent       = NULL;
    TPtxPdfContent_ContentGenerator* pGenerator     = NULL;
    TPtxPdfContent_Text*             pText          = NULL;
    TPtxPdfContent_TextGenerator*    pTextGenerator = NULL;
    TPtxGeomReal_Size                size;
    TPtxGeomReal_Point               position;
    double                           dFontAscent;

    pContent = PtxPdf_Page_GetContent(pOutPage);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pContent, _T("Failed to get content of output file. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Create content generator
    pGenerator = PtxPdfContent_ContentGenerator_New(pContent, FALSE);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pGenerator, _T("Failed to create a content generator. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Create text object
    pText = PtxPdfContent_Text_Create(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pText, _T("Failed to create text object. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                     Ptx_GetLastError());

    // Create a text generator
    pTextGenerator = PtxPdfContent_TextGenerator_New(pText, pFont, dFontSize, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pTextGenerator, _T("Failed to create a text generator. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Get output page size
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Page_GetSize(pOutPage, &size),
                                      _T("Failed to read page size. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    dFontAscent = PtxPdfContent_Font_GetAscent(pFont);
    GOTO_CLEANUP_IF_ZERO_PRINT_ERROR(dFontAscent, _T("%s (ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());

    // Calculate position
    position.dX = dBorder;
    position.dY = size.dHeight - dBorder - dFontSize * dFontAscent;

    // Move to position
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_TextGenerator_MoveTo(pTextGenerator, &position),
                                      _T("Failed to move to position. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());
    // Add given text string
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_TextGenerator_ShowLine(pTextGenerator, szTextString),
                                      _T("Failed to add text string. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());
    // Close text generator
    PtxPdfContent_TextGenerator_Close(pTextGenerator);
    pTextGenerator = NULL;

    // Paint the positioned text
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_ContentGenerator_PaintText(pGenerator, pText),
                                      _T("Failed to paint the positioned text. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

cleanup:
    if (pTextGenerator != NULL)
        PtxPdfContent_TextGenerator_Close(pTextGenerator);
    if (pText != NULL)
        Ptx_Release(pText);
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
    TPtxPdfContent_Font*     pFont         = NULL;
    TPtxPdf_PageList*        pInPageList   = NULL;
    TPtxPdf_PageList*        pOutPageList  = NULL;
    TPtxPdf_PageList*        pInPageRange  = NULL;
    TPtxPdf_PageList*        pOutPageRange = NULL;
    TPtxPdf_Page*            pInPage       = NULL;
    TPtxPdf_Page*            pOutPage      = NULL;
    TPtxPdf_PageCopyOptions* pCopyOptions  = NULL;
    TPtxPdf_Conformance      iConformance;
    TCHAR*                   szInPath;
    TCHAR*                   szOutPath;
    TCHAR*                   szTextString;

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 4 || argc > 4)
    {
        return Usage();
    }

    // Initialize library
    Ptx_Initialize();

    // Set and check license key
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(Ptx_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
                                      _T("Failed to set license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    szInPath     = argv[1];
    szTextString = argv[2];
    szOutPath    = argv[3];

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

    // Create embedded font in output document
    pFont = PtxPdfContent_Font_CreateFromSystem(pOutDoc, _T("Arial"), _T("Italic"), TRUE);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pFont, _T("Failed to create font. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                     Ptx_GetLastError());

    // Copy document-wide data
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(copyDocumentData(pInDoc, pOutDoc),
                                      _T("Failed to copy document-wide data. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    // Configure copy options
    pCopyOptions = PtxPdf_PageCopyOptions_New();

    // Get page lists of input and output document
    pInPageList = PtxPdf_Document_GetPages(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageList,
                                     _T("Failed to get the pages of the input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pOutPageList = PtxPdf_Document_GetPages(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageList,
                                     _T("Failed to get the pages of the output document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Copy first page
    pInPage = PtxPdf_PageList_Get(pInPageList, 0);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPage, _T("Failed to get the first page. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pOutPage = PtxPdf_Page_Copy(pOutDoc, pInPage, pCopyOptions);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPage, _T("Failed to copy page. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                     Ptx_GetLastError());

    // Add text to copied page
    if (addText(pOutDoc, pOutPage, szTextString, pFont, 15) != 0)
        goto cleanup;

    // Add page to output document
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_Add(pOutPageList, pOutPage),
                                      _T("Failed to add page to output document. %s (ErrorCode: 0x%08x).\n"),
                                      szErrorBuff, Ptx_GetLastError());

    // Get remaining pages from input
    pInPageRange = PtxPdf_PageList_GetRange(pInPageList, 1, PtxPdf_PageList_GetCount(pInPageList) - 1);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageRange,
                                     _T("Failed to get page range from input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Copy remaining pages to output
    pOutPageRange = PtxPdf_PageList_Copy(pOutDoc, pInPageRange, pCopyOptions);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageRange,
                                     _T("Failed to copy page range to output document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Add the copied pages to the output document
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_AddRange(pOutPageList, pOutPageRange),
                                      _T("Failed to add page range to output page list. %s (ErrorCode: 0x%08x).\n"),
                                      szErrorBuff, Ptx_GetLastError());

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pOutPage != NULL)
        Ptx_Release(pOutPage);
    if (pInPage != NULL)
        Ptx_Release(pInPage);
    if (pOutPageRange != NULL)
        Ptx_Release(pOutPageRange);
    if (pInPageRange != NULL)
        Ptx_Release(pInPageRange);
    if (pOutPageList != NULL)
        Ptx_Release(pOutPageList);
    if (pInPageList != NULL)
        Ptx_Release(pInPageList);
    if (pFont != NULL)
        Ptx_Release(pFont);
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