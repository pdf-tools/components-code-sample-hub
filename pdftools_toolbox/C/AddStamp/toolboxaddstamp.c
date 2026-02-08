/****************************************************************************
 *
 * File:            toolboxaddstamp.c
 *
 * Usage:           toolboxaddstamp <inputPath> <stampString> <outputPath> [<alpha>]
 *                  Example: in.pdf APPROVED out.pdf 0.5
 *                  
 * Title:           Add stamp to PDF
 *                  
 * Description:     Add a semi-transparent stamp text onto each page of a PDF
 *                  document. Optionally specify the color and the opacity of
 *                  the stamp.
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
#include <stdarg.h>
#define _USE_MATH_DEFINES
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
    printf("Usage: toolboxaddstamp <inputPath> <stampString> <outputPath> [<alpha>].\n");
    printf("       Example: in.pdf APPROVED out.pdf 0.5\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

TPtxPdfContent_Paint* pPaint;
TCHAR                 szErrorBuff[1024];
size_t                nBufSize;
int                   iReturnValue = 0;

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
int addStamp(TPtxPdf_Document* pOutDoc, TPtxPdf_Page* pOutPage, TCHAR* szStampString, TPtxPdfContent_Font* pFont,
             double dFontSize)
{
    TPtxPdfContent_ContentGenerator* pGenerator     = NULL;
    TPtxPdfContent_Text*             pText          = NULL;
    TPtxPdfContent_TextGenerator*    pTextGenerator = NULL;
    TPtxGeomReal_AffineTransform     trans;
    TPtxGeomReal_Point               rotationCenter;
    double                           dTextWidth;
    double                           dFontAscent;

    TPtxPdfContent_Content* pContent = PtxPdf_Page_GetContent(pOutPage);

    // Create content generator
    pGenerator = PtxPdfContent_ContentGenerator_New(pContent, FALSE);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pGenerator, _T("Failed to create a content generator. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Create text object
    pText = PtxPdfContent_Text_Create(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pText, _T("Failed to create a text object. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Create a text generator
    pTextGenerator = PtxPdfContent_TextGenerator_New(pText, pFont, dFontSize, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pTextGenerator, _T("Failed to create a text generator. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Get output page size
    TPtxGeomReal_Size size;
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Page_GetSize(pOutPage, &size),
                                      _T("Failed to read page size. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    // Calculate point and angle of rotation
    rotationCenter.dX     = size.dWidth / 2.0;
    rotationCenter.dY     = size.dHeight / 2.0;
    double dRotationAngle = atan2(size.dHeight, size.dWidth) / M_PI * 180.0;

    // Rotate textinput around the calculated position
    PtxGeomReal_AffineTransform_GetIdentity(&trans);
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
        PtxGeomReal_AffineTransform_Rotate(&trans, dRotationAngle, &rotationCenter),
        _T("Failed to rotate textinput around the calculated position. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
        Ptx_GetLastError());
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_ContentGenerator_Transform(pGenerator, &trans),
                                      _T("Failed to modify the current transformation. %s (ErrorCode: 0x%08x).\n"),
                                      szErrorBuff, Ptx_GetLastError());

    // Calculate position
    TPtxGeomReal_Point position;
    dTextWidth = PtxPdfContent_TextGenerator_GetWidth(pTextGenerator, szStampString);
    GOTO_CLEANUP_IF_ZERO_PRINT_ERROR(dTextWidth, _T("%s (ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());
    dFontAscent = PtxPdfContent_Font_GetAscent(pFont);
    GOTO_CLEANUP_IF_ZERO_PRINT_ERROR(dFontAscent, _T("%s (ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());
    position.dX = (size.dWidth - dTextWidth) / 2.0;
    position.dY = (size.dHeight - dFontAscent * dFontSize) / 2.0;

    // Move to position
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_TextGenerator_MoveTo(pTextGenerator, &position),
                                      _T("Failed to move to position. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());
    // Set text rendering
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_TextGenerator_SetFill(pTextGenerator, pPaint),
                                      _T("Failed to set fill paint. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());
    // Add given stamp string
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfContent_TextGenerator_ShowLine(pTextGenerator, szStampString),
                                      _T("Failed to add stamp. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    // Close text generator
    if (pTextGenerator != NULL)
    {
        PtxPdfContent_TextGenerator_Close(pTextGenerator);
        pTextGenerator = NULL;
    }

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
    FILE*                        pInStream = NULL;
    TPtxSys_StreamDescriptor     inDescriptor;
    TPtxPdf_Document*            pInDoc     = NULL;
    FILE*                        pOutStream = NULL;
    TPtxSys_StreamDescriptor     outDescriptor;
    TPtxPdf_Document*            pOutDoc      = NULL;
    TPtxPdfContent_Font*         pFont        = NULL;
    TPtxPdf_PageList*            pInPageList  = NULL;
    TPtxPdf_PageList*            pOutPageList = NULL;
    TPtxPdf_Page*                pInPage      = NULL;
    TPtxPdf_Page*                pOutPage     = NULL;
    TPtxPdf_PageCopyOptions*     pCopyOptions = NULL;
    TPtxPdf_Conformance          iConformance;
    TPtxPdfContent_Transparency* pTransparency = NULL;
    double                       dAlpha        = 0.5;
    TCHAR*                       szInPath;
    TCHAR*                       szStampString;
    TCHAR*                       szOutPath;

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 4 || argc > 5)
    {
        return Usage();
    }

    // Initialize library
    Ptx_Initialize();

    // Set and check license key
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(Ptx_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
                                      _T("Failed to set license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    szInPath      = argv[1];
    szStampString = argv[2];
    szOutPath     = argv[3];

    if (argc == 5)
        dAlpha = _tstof(argv[4]);

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL(pInStream, _T("Failed to open input file \"%s\".\n"), szInPath);
    PtxSysCreateFILEStreamDescriptor(&inDescriptor, pInStream, FALSE);
    pInDoc = PtxPdf_Document_Open(&inDescriptor, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Input file \"%s\" cannot be opened. %s (ErrorCode: 0x%08x).\n"),
                                     szInPath, szErrorBuff, Ptx_GetLastError());

    // Create output document
    pOutStream = _tfopen(szOutPath, _T("wb+"));
    GOTO_CLEANUP_IF_NULL(pOutStream, _T("Failed to open output file %s.\n"), szOutPath);
    PtxSysCreateFILEStreamDescriptor(&outDescriptor, pOutStream, 0);
    iConformance = PtxPdf_Document_GetConformance(pInDoc);
    pOutDoc      = PtxPdf_Document_Create(&outDescriptor, &iConformance, NULL);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("Output file %s cannot be closed. %s (ErrorCode: 0x%08x).\n"),
                                     szOutPath, szErrorBuff, Ptx_GetLastError());

    // Create embedded font in output document
    pFont = PtxPdfContent_Font_CreateFromSystem(pOutDoc, _T("Arial"), _T("Italic"), TRUE);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pFont, _T("Embedded font cannot be created. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Copy document-wide data
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(copyDocumentData(pInDoc, pOutDoc),
                                      _T("Failed to copy document-wide data. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    // Get the color space
    TPtxPdfContent_ColorSpace* pColorSpace =
        PtxPdfContent_ColorSpace_CreateProcessColorSpace(pOutDoc, ePtxPdfContent_ProcessColorSpaceType_Rgb);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pColorSpace, _T("Failed to get the color space. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Chose the RGB color values
    double color[] = {1.0, 0.0, 0.0};
    size_t nColor  = sizeof(color) / sizeof(double);
    pTransparency  = PtxPdfContent_Transparency_New(dAlpha);

    // Create paint object
    pPaint = PtxPdfContent_Paint_Create(pOutDoc, pColorSpace, color, nColor, pTransparency);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pPaint, _T("Failed to create a transparent paint. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    // Configure copy options
    pCopyOptions = PtxPdf_PageCopyOptions_New();

    // Loop through all pages of input
    pInPageList = PtxPdf_Document_GetPages(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageList,
                                     _T("Failed to get the pages of the input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pOutPageList = PtxPdf_Document_GetPages(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageList,
                                     _T("Failed to get the pages of the output document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    for (int i = 0; i < PtxPdf_PageList_GetCount(pInPageList); i++)
    {
        // Get a list of pages
        pInPage = PtxPdf_PageList_Get(pInPageList, i);

        // Copy page from input to output
        pOutPage = PtxPdf_Page_Copy(pOutDoc, pInPage, pCopyOptions);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPage,
                                         _T("Failed to copy pages from input to output. %s (ErrorCode: 0x%08x).\n"),
                                         szErrorBuff, Ptx_GetLastError());

        // Add stamp to page
        if (addStamp(pOutDoc, pOutPage, szStampString, pFont, 50) == 1)
        {
            goto cleanup;
        }

        // Add page to output document
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_Add(pOutPageList, pOutPage),
                                          _T("Failed to add page to output document. %s (ErrorCode: 0x%08x).\n"),
                                          szErrorBuff, Ptx_GetLastError());

        if (pOutPage != NULL)
        {
            Ptx_Release(pOutPage);
            pOutPage = NULL;
        }

        if (pInPage != NULL)
        {
            Ptx_Release(pInPage);
            pInPage = NULL;
        }
    }

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pOutPage != NULL)
        Ptx_Release(pOutPage);
    if (pInPage != NULL)
        Ptx_Release(pInPage);
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