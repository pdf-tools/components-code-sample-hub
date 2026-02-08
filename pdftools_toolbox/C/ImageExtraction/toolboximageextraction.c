/****************************************************************************
 *
 * File:            toolboximageextraction.c
 *
 * Usage:           toolboximageextraction <inputPath> <outputDir>
 *                  Example: in.pdf dir/subdir/
 *                  
 * Title:           Extract all images and image masks from a PDF
 *                  
 * Description:     Extract the embedded image data as JPEG or TIFF,
 *                  depending on the compression format used.
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

int Usage()
{
    printf("Usage: toolboximageextraction <inputPath> <outputDir>.\n");
    printf("       Example: in.pdf dir/subdir/\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

size_t nBufSize;
TCHAR  szErrorBuff[1024];
int    iReturnValue = 0;

int extractImages(TPtxPdfContent_ContentExtractor* pExtractor, int iPageNo, const TCHAR* szOutputDir)
{
    int                                      iImgCount       = 0;
    int                                      iImgMaskCount   = 0;
    TPtxPdfContent_ContentExtractorIterator* pIterator       = NULL;
    TPtxPdfContent_ContentElement*           pContentElement = NULL;
    TPtxPdfContent_Image*                    pImage          = NULL;
    TPtxPdfContent_ImageMask*                pImageMask      = NULL;
    TCHAR*                                   szExtension     = NULL;
    FILE*                                    pOutStream      = NULL;

    pIterator = PtxPdfContent_ContentExtractor_GetIterator(pExtractor);
    GOTO_CLEANUP_IF_NULL(pIterator, _T("Failed to get iterator.\n"));
    PtxPdfContent_ContentExtractorIterator_MoveNext(pIterator);
    while (pContentElement = PtxPdfContent_ContentExtractorIterator_GetValue(pIterator))
    {
        TPtxPdfContent_ContentElementType iType = PtxPdfContent_ContentElement_GetType(pContentElement);
        if (iType == ePtxPdfContent_ContentElementType_ImageElement)
        {
            iImgCount++;
            pImage = PtxPdfContent_ImageElement_GetImage((TPtxPdfContent_ImageElement*)pContentElement);
            GOTO_CLEANUP_IF_NULL(pImage, _T("Failed to get image.\n"));

            const TPtxPdfContent_ImageType iImageType = PtxPdfContent_Image_GetDefaultImageType(pImage);
            if (iImageType == ePtxPdfContent_ImageType_Jpeg)
                szExtension = _T(".jpg");
            else
                szExtension = _T(".tiff");

            TCHAR szOutPath[256] = {'\0'};
            _stprintf(szOutPath, _T("%s/image_page%d_%d%s"), szOutputDir, iPageNo, iImgCount, szExtension);

            pOutStream = _tfopen(szOutPath, _T("wb+"));
            GOTO_CLEANUP_IF_NULL(pOutStream, _T("Failed to open output file \"%s\".\n"), szOutPath);

            TPtxSys_StreamDescriptor outDescriptor;
            PtxSysCreateFILEStreamDescriptor(&outDescriptor, pOutStream, 0);
            if (PtxPdfContent_Image_Extract(pImage, &outDescriptor, NULL) == FALSE)
            {
                if (Ptx_GetLastError() == ePtx_Error_Generic)
                {
                    nBufSize = Ptx_GetLastErrorMessage(NULL, 0);
                    Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize));
                    _tprintf(szErrorBuff);
                }
                else
                    return FALSE;
            }

            if (pImage != NULL)
            {
                Ptx_Release(pImage);
                pImage = NULL;
            }
            if (pOutStream != NULL)
            {
                fclose(pOutStream);
                pOutStream = NULL;
            }
        }
        else if (iType == ePtxPdfContent_ContentElementType_ImageMaskElement)
        {
            iImgMaskCount++;
            pImageMask = PtxPdfContent_ImageMaskElement_GetImageMask((TPtxPdfContent_ImageMaskElement*)pContentElement);
            GOTO_CLEANUP_IF_NULL(pImageMask, _T("Failed to get image.\n"));

            szExtension = _T(".tiff");

            TCHAR szOutPath[256] = {'\0'};
            _stprintf(szOutPath, _T("%s/image_mask_page%d_%d%s"), szOutputDir, iPageNo, iImgMaskCount, szExtension);

            pOutStream = _tfopen(szOutPath, _T("wb+"));
            GOTO_CLEANUP_IF_NULL(pOutStream, _T("Failed to open output file \"%s\".\n"), szOutPath);

            TPtxSys_StreamDescriptor outDescriptor;
            PtxSysCreateFILEStreamDescriptor(&outDescriptor, pOutStream, 0);
            if (PtxPdfContent_ImageMask_Extract(pImageMask, &outDescriptor, NULL) == FALSE)
            {
                if (Ptx_GetLastError() == ePtx_Error_Generic)
                {
                    nBufSize = Ptx_GetLastErrorMessage(NULL, 0);
                    Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize));
                    _tprintf(szErrorBuff);
                }
                else
                    return FALSE;
            }

            if (pImageMask != NULL)
            {
                Ptx_Release(pImageMask);
                pImageMask = NULL;
            }
            if (pOutStream != NULL)
            {
                fclose(pOutStream);
                pOutStream = NULL;
            }
        }
        if (pContentElement != NULL)
        {
            Ptx_Release(pContentElement);
            pContentElement = NULL;
        }
        PtxPdfContent_ContentExtractorIterator_MoveNext(pIterator);
    }

cleanup:
    if (pImage != NULL)
        Ptx_Release(pImage);
    if (pImageMask != NULL)
        Ptx_Release(pImageMask);
    if (pContentElement != NULL)
        Ptx_Release(pContentElement);
    if (pIterator != NULL)
        Ptx_Release(pIterator);
    if (pOutStream != NULL)
        fclose(pOutStream);

    return iReturnValue == 1 ? FALSE : TRUE;
}

int _tmain(int argc, TCHAR* argv[])
{
    FILE*                            pInStream = NULL;
    TPtxSys_StreamDescriptor         descriptor;
    TPtxPdf_Document*                pInDoc      = NULL;
    TPtxPdf_PageList*                pInPageList = NULL;
    TPtxPdf_Page*                    pPage       = NULL;
    TPtxPdfContent_Content*          pContent    = NULL;
    TPtxPdfContent_ContentExtractor* pExtractor  = NULL;
    TCHAR*                           szInPath;
    TCHAR*                           szOutputDir;

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

    szInPath    = argv[1];
    szOutputDir = argv[2];

    // TODO: Create output directory?

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL(pInStream, _T("Failed to open input file \"%s\".\n"), szInPath);
    PtxSysCreateFILEStreamDescriptor(&descriptor, pInStream, 0);
    pInDoc = PtxPdf_Document_Open(&descriptor, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Input file \"%s\" cannot be opened. %s (ErrorCode: 0x%08x).\n"),
                                     szInPath, szErrorBuff, Ptx_GetLastError());

    // Loop over all pages and extract images
    pInPageList = PtxPdf_Document_GetPages(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInPageList,
                                     _T("Failed to get the pages of the input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    for (int iPageNo = 0; iPageNo < PtxPdf_PageList_GetCount(pInPageList); iPageNo++)
    {
        pPage    = PtxPdf_PageList_Get(pInPageList, iPageNo);
        pContent = PtxPdf_Page_GetContent(pPage);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pContent, _T("Failed to get content from page %d. %s (ErrorCode: 0x%08x).\n"),
                                         iPageNo + 1, szErrorBuff, Ptx_GetLastError());

        pExtractor = PtxPdfContent_ContentExtractor_New(pContent);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pExtractor,
                                         _T("Failed to create content extractor. %s (ErrorCode: 0x%08x).\n"),
                                         szErrorBuff, Ptx_GetLastError());

        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(extractImages(pExtractor, iPageNo + 1, szOutputDir),
                                          _T("Error occurred while extracting images. %s (ErrorCode: 0x%08x).\n"),
                                          szErrorBuff, Ptx_GetLastError());

        if (pPage != NULL)
        {
            Ptx_Release(pPage);
            pPage = NULL;
        }
        if (pContent != NULL)
        {
            Ptx_Release(pContent);
            pContent = NULL;
        }
    }


    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pExtractor != NULL)
        Ptx_Release(pExtractor);
    if (pPage != NULL)
        Ptx_Release(pPage);
    if (pContent != NULL)
        Ptx_Release(pContent);
    if (pInPageList != NULL)
        Ptx_Release(pInPageList);
    if (pInDoc != NULL)
        PtxPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);
    Ptx_Uninitialize();

    return iReturnValue;
} 