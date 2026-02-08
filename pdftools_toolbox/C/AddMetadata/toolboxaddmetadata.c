/****************************************************************************
 *
 * File:            toolboxaddmetadata.c
 *
 * Usage:           toolboxaddmetadata <inputPath> <outputPath> [<mdatafile>]
 *                  Example: in.pdf out.pdf MetadataTest.xmp
 *                  
 * Title:           Add metadata to PDF
 *                  
 * Description:     Set metadata such as author, title, and creator of a PDF
 *                  document. Optionally use the metadata of another PDF
 *                  document or the content of an XMP file.
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
    printf("Usage: toolboxaddmetadata <inputPath> <outputPath> [<mdatafile>].\n");
    printf("       Example: in.pdf out.pdf MetadataTest.xmp\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

size_t nBufSize;
TCHAR  szErrorBuff[1024];
int    iReturnValue = 0;

int copyDocumentData(TPtxPdf_Document* pInDoc, TPtxPdf_Document* pOutDoc)
{
    // Copy document-wide data (excluding metadata)

    TPtxPdf_FileReferenceList* pInFileRefList;
    TPtxPdf_FileReferenceList* pOutFileRefList;

    // Output intent
    if (PtxPdf_Document_GetOutputIntent(pInDoc) != NULL)
        if (PtxPdf_Document_SetOutputIntent(pOutDoc, PtxPdfContent_IccBasedColorSpace_Copy(
                                                         pOutDoc, PtxPdf_Document_GetOutputIntent(pInDoc))) == FALSE)
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
    FILE*                    pInStream = NULL;
    TPtxSys_StreamDescriptor descriptor;
    TPtxPdf_Document*        pInDoc     = NULL;
    FILE*                    pOutStream = NULL;
    TPtxSys_StreamDescriptor outDescriptor;
    TPtxPdf_Document*        pOutDoc = NULL;
    TPtxSys_StreamDescriptor mdataDescriptor;
    TPtxPdf_Document*        pMetaDoc     = NULL;
    FILE*                    pMdataStream = NULL;
    TPtxPdf_PageList*        pInPageList  = NULL;
    TPtxPdf_PageList*        pOutPageList = NULL;
    TPtxPdf_PageList*        pCopiedPages = NULL;
    TPtxPdf_PageCopyOptions* pCopyOptions = NULL;
    TPtxPdf_Conformance      iConformance;
    TCHAR*                   szInPath;
    TCHAR*                   szOutPath;
    TCHAR*                   szMdatafile;
    TCHAR                    szExtension[20];

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 3 || argc > 4)
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

    if (argc == 4)
    {
        szMdatafile = argv[3];
    }

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
                                     _T("Failed to get pages of the input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    pCopiedPages = PtxPdf_PageList_Copy(pOutDoc, pInPageList, pCopyOptions);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pCopiedPages, _T("Failed to copy pages. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                     Ptx_GetLastError());

    // Add copied pages to output
    pOutPageList = PtxPdf_Document_GetPages(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutPageList,
                                     _T("Failed to get pages of the output document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_PageList_AddRange(pOutPageList, pCopiedPages),
                                      _T("Failed to add copied pages to output. %s (ErrorCode: 0x%08x).\n"),
                                      szErrorBuff, Ptx_GetLastError());

    if (argc == 4)
    {
        // Add metadata from a input file
        pMdataStream = _tfopen(szMdatafile, _T("rb"));
        GOTO_CLEANUP_IF_NULL(pMdataStream, _T("Failed to open metadata file \"%s\".\n"), szMdatafile);
        PtxSysCreateFILEStreamDescriptor(&mdataDescriptor, pMdataStream, 0);

        // Get file extension
        TCHAR* szExt = _tcsrchr(szMdatafile, '.');
        _tcscpy(szExtension, szExt);

        if (_tcscmp(szExtension, _T(".pdf")) == 0)
        {
            // Use the metadata of another PDF file
            TPtxPdf_Document* pMetaDoc = PtxPdf_Document_Open(&mdataDescriptor, _T(""));
            GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pMetaDoc, _T("Failed to open metadata file. %s (ErrorCode: 0x%08x).\n"),
                                             szErrorBuff, Ptx_GetLastError());
            TPtxPdf_Metadata* pMetadata = PtxPdf_Metadata_Copy(pOutDoc, PtxPdf_Document_GetMetadata(pMetaDoc));
            GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pMetadata, _T("Failed to copy metadata. %s (ErrorCode: 0x%08x)."),
                                             szErrorBuff, Ptx_GetLastError());
            GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Document_SetMetadata(pOutDoc, pMetadata),
                                              _T("Failed to set metadata. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                              Ptx_GetLastError());
        }
        else
        {
            // Use the content of an XMP metadata file
            GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
                PtxPdf_Document_SetMetadata(pOutDoc, PtxPdf_Metadata_Create(pOutDoc, &mdataDescriptor)),
                _T("Failed to set metadata. %s (ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());
        }
    }
    else
    {
        // Set some metadata properties
        TPtxPdf_Metadata* pMetadata = PtxPdf_Document_GetMetadata(pOutDoc);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pMetadata, _T("Failed to get metadata. %s (ErrorCode: 0x%08x).\n"),
                                         szErrorBuff, Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Metadata_SetAuthor(pMetadata, _T("Your Author")),
                                          _T("%s (ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Metadata_SetTitle(pMetadata, _T("Your Title")),
                                          _T("%s(ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Metadata_SetSubject(pMetadata, _T("Your Subject")),
                                          _T("%s(ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdf_Metadata_SetCreator(pMetadata, _T("Your Creator")),
                                          _T("%s (ErrorCode: 0x%08x).\n"), szErrorBuff, Ptx_GetLastError());
    }

    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pCopiedPages != NULL)
        Ptx_Release(pCopiedPages);
    if (pOutPageList != NULL)
        Ptx_Release(pOutPageList);
    if (pInPageList != NULL)
        Ptx_Release(pInPageList);
    if (pOutDoc != NULL)
        PtxPdf_Document_Close(pOutDoc);
    if (pOutStream != NULL)
        fclose(pOutStream);
    if (pMetaDoc != NULL)
        PtxPdf_Document_Close(pMetaDoc);
    if (pMdataStream != NULL)
        fclose(pMdataStream);
    if (pInDoc != NULL)
        PtxPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);
    Ptx_Uninitialize();

    return iReturnValue;
} 