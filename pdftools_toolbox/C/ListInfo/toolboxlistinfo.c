/****************************************************************************
 *
 * File:            toolboxlistinfo.c
 *
 * Usage:           toolboxlistinfo <inputPath> [<pdfPassword>]
 *                  
 * Title:           List document information of PDF
 *                  
 * Description:     List attributes of a PDF document (i.e. conformance and
 *                  encryption information) and metadata (i.e. author, title,
 *                  creation date etc.).
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

#define GOTO_CLEANUP(...)      \
    do                         \
    {                          \
        _tprintf(__VA_ARGS__); \
        iReturnValue = 1;      \
        goto cleanup;          \
    } while (0);

#define GOTO_CLEANUP_IF_NULL(inFile, ...) \
    do                                    \
    {                                     \
        if ((inFile) == NULL)             \
            GOTO_CLEANUP(__VA_ARGS__);    \
    } while (0);

#define GOTO_CLEANUP_IF_NULL_PRINT_ERROR(inVar, ...)                                      \
    do                                                                                    \
    {                                                                                     \
        if ((inVar) == NULL)                                                              \
        {                                                                                 \
            nBufSize = Ptx_GetLastErrorMessage(NULL, 0);                                  \
            Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            GOTO_CLEANUP(__VA_ARGS__);                                                    \
        }                                                                                 \
    } while (0);

#define GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(outBool, ...)                                   \
    do                                                                                    \
    {                                                                                     \
        if ((outBool) == FALSE)                                                           \
        {                                                                                 \
            nBufSize = Ptx_GetLastErrorMessage(NULL, 0);                                  \
            Ptx_GetLastErrorMessage(szErrorBuff, MIN(ARRAY_SIZE(szErrorBuff), nBufSize)); \
            GOTO_CLEANUP(__VA_ARGS__);                                                    \
        }                                                                                 \
    } while (0);

int Usage()
{
    printf("Usage: toolboxlistinfo <inputPath> [<pdfPassword>].\n");
    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

size_t nBufSize;
TCHAR  szErrorBuff[1024];

int _tmain(int argc, TCHAR* argv[])
{
    FILE*                    pInStream = NULL;
    TPtxSys_StreamDescriptor descriptor;
    TPtxPdf_Document*        pInDoc    = NULL;
    TPtxPdf_Metadata*        pMetadata = NULL;
    TCHAR*                   szInPath;
    TCHAR*                   szPassword;
    TPtxSys_Date             date;
    int                      iReturnValue = 0;

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 2 || argc > 3)
    {
        return Usage();
    }

    // Initialize library
    Ptx_Initialize();

    // Set and check license key
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(Ptx_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
                                      _T("Failed to set license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    szInPath   = argv[1];
    szPassword = (argc == 3) ? argv[2] : NULL;

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL(pInStream, _T("Failed to open input file \"%s\".\n"), szInPath);
    PtxSysCreateFILEStreamDescriptor(&descriptor, pInStream, 0);
    pInDoc = PtxPdf_Document_Open(&descriptor, szPassword);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Input file \"%s\" cannot be opened. %s (ErrorCode: 0x%08x).\n"),
                                     szInPath, szErrorBuff, Ptx_GetLastError());

    // Conformance
    TPtxPdf_Conformance conformance = PtxPdf_Document_GetConformance(pInDoc);
    if (conformance == 0)
    {
        GOTO_CLEANUP(szErrorBuff, Ptx_GetLastError());
    }
    _tprintf(_T("Conformance: "));
    switch (conformance)
    {
    case ePtxPdf_Conformance_Pdf10:
        _tprintf(_T("PDF 1.0\n"));
        break;
    case ePtxPdf_Conformance_Pdf11:
        _tprintf(_T("PDF 1.1\n"));
        break;
    case ePtxPdf_Conformance_Pdf12:
        _tprintf(_T("PDF 1.2\n"));
        break;
    case ePtxPdf_Conformance_Pdf13:
        _tprintf(_T("PDF 1.3\n"));
        break;
    case ePtxPdf_Conformance_Pdf14:
        _tprintf(_T("PDF 1.4\n"));
        break;
    case ePtxPdf_Conformance_Pdf15:
        _tprintf(_T("PDF 1.5\n"));
        break;
    case ePtxPdf_Conformance_Pdf16:
        _tprintf(_T("PDF 1.6\n"));
        break;
    case ePtxPdf_Conformance_Pdf17:
        _tprintf(_T("PDF 1.7\n"));
        break;
    case ePtxPdf_Conformance_Pdf20:
        _tprintf(_T("PDF 2.0\n"));
        break;
    case ePtxPdf_Conformance_PdfA1B:
        _tprintf(_T("PDF/A1-b\n"));
        break;
    case ePtxPdf_Conformance_PdfA1A:
        _tprintf(_T("PDF/A1-a\n"));
        break;
    case ePtxPdf_Conformance_PdfA2B:
        _tprintf(_T("PDF/A2-b\n"));
        break;
    case ePtxPdf_Conformance_PdfA2U:
        _tprintf(_T("PDF/A2-u\n"));
        break;
    case ePtxPdf_Conformance_PdfA2A:
        _tprintf(_T("PDF/A2-a\n"));
        break;
    case ePtxPdf_Conformance_PdfA3B:
        _tprintf(_T("PDF/A3-b\n"));
        break;
    case ePtxPdf_Conformance_PdfA3U:
        _tprintf(_T("PDF/A3-u\n"));
        break;
    case ePtxPdf_Conformance_PdfA3A:
        _tprintf(_T("PDF/A3-a\n"));
        break;
    }

    // Encryption information
    TPtxPdf_Permission permissions;
    BOOL               iRet = PtxPdf_Document_GetPermissions(pInDoc, &permissions);
    if (iRet == FALSE)
    {
        if (Ptx_GetLastError() != ePtx_Error_Success)
            GOTO_CLEANUP(szErrorBuff, Ptx_GetLastError());
        _tprintf(_T("Not encrypted\n"));
    }
    else
    {
        _tprintf(_T("Encryption:\n"));
        _tprintf(_T("  - Permissions: "));
        if (permissions & ePtxPdf_Permission_Print)
            _tprintf(_T("Print, "));
        if (permissions & ePtxPdf_Permission_Modify)
            _tprintf(_T("Modify, "));
        if (permissions & ePtxPdf_Permission_Copy)
            _tprintf(_T("Copy, "));
        if (permissions & ePtxPdf_Permission_Annotate)
            _tprintf(_T("Annotate, "));
        if (permissions & ePtxPdf_Permission_FillForms)
            _tprintf(_T("FillForms, "));
        if (permissions & ePtxPdf_Permission_SupportDisabilities)
            _tprintf(_T("SupportDisabilities, "));
        if (permissions & ePtxPdf_Permission_Assemble)
            _tprintf(_T("Assemble, "));
        if (permissions & ePtxPdf_Permission_DigitalPrint)
            _tprintf(_T("DigitalPrint, "));
        _tprintf(_T("\n"));
    }

    // Get metadata of input PDF
    pMetadata = PtxPdf_Document_GetMetadata(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pMetadata, _T("Failed to get metadata. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                     Ptx_GetLastError());
    _tprintf(_T("Document information:\n"));

    // Get title
    size_t nTitle = PtxPdf_Metadata_GetTitle(pMetadata, NULL, 0);
    if (nTitle != 0)
    {
        TCHAR* szTitle = (TCHAR*)malloc(nTitle * sizeof(TCHAR));
        if (szTitle != NULL)
        {
            PtxPdf_Metadata_GetTitle(pMetadata, szTitle, nTitle);
            _tprintf(_T("  - Title: %s\n"), szTitle);
            free(szTitle);
        }
    }

    // Get author
    size_t nAuthor = PtxPdf_Metadata_GetAuthor(pMetadata, NULL, 0);
    if (nAuthor != 0)
    {
        TCHAR* szAuthor = (TCHAR*)malloc(nAuthor * sizeof(TCHAR));
        if (szAuthor != NULL)
        {
            PtxPdf_Metadata_GetAuthor(pMetadata, szAuthor, nAuthor);
            _tprintf(_T("  - Author: %s\n"), szAuthor);
            free(szAuthor);
        }
    }

    // Get creator
    size_t nCreator = PtxPdf_Metadata_GetCreator(pMetadata, NULL, 0);
    if (nCreator != 0)
    {
        TCHAR* szCreator = (TCHAR*)malloc(nCreator * sizeof(TCHAR));
        if (szCreator != NULL)
        {
            PtxPdf_Metadata_GetCreator(pMetadata, szCreator, nCreator);
            _tprintf(_T("  - Creator: %s\n"), szCreator);
            free(szCreator);
        }
    }

    // Get producer
    size_t nProducer = PtxPdf_Metadata_GetProducer(pMetadata, NULL, 0);
    if (nProducer != 0)
    {
        TCHAR* szProducer = (TCHAR*)malloc(nProducer * sizeof(TCHAR));
        if (szProducer != NULL)
        {
            PtxPdf_Metadata_GetProducer(pMetadata, szProducer, nProducer);
            _tprintf(_T("  - Producer: %s\n"), szProducer);
            free(szProducer);
        }
    }

    // Get subject
    size_t nSubject = PtxPdf_Metadata_GetSubject(pMetadata, NULL, 0);
    if (nSubject != 0)
    {
        TCHAR* szSubject = (TCHAR*)malloc(nSubject * sizeof(TCHAR));
        if (szSubject != NULL)
        {
            PtxPdf_Metadata_GetSubject(pMetadata, szSubject, nSubject);
            _tprintf(_T("  - Subject: %s\n"), szSubject);
            free(szSubject);
        }
    }

    // Get keywords
    size_t nKeywords = PtxPdf_Metadata_GetKeywords(pMetadata, NULL, 0);
    if (nKeywords != 0)
    {
        TCHAR* szKeywords = (TCHAR*)malloc(nKeywords * sizeof(TCHAR));
        if (szKeywords != NULL)
        {
            PtxPdf_Metadata_GetKeywords(pMetadata, szKeywords, nKeywords);
            _tprintf(_T("  - Keywords: %s\n"), szKeywords);
            free(szKeywords);
        }
    }

    // Get creation date
    if (PtxPdf_Metadata_GetCreationDate(pMetadata, &date) == TRUE)
    {
        _tprintf(_T("  - Creation Date: %02d-%02d-%d %02d:%02d:%02d%c%02d:%02d\n"), date.iYear, date.iMonth, date.iDay,
                 date.iHour, date.iMinute, date.iSecond, date.iTZSign >= 0 ? '+' : '-', date.iTZHour, date.iTZMinute);
    }

    // Get modification date
    if (PtxPdf_Metadata_GetModificationDate(pMetadata, &date) == TRUE)
    {
        _tprintf(_T("  - Modification Date: %02d-%02d-%d %02d:%02d:%02d%c%02d:%02d\n"), date.iYear, date.iMonth,
                 date.iDay, date.iHour, date.iMinute, date.iSecond, date.iTZSign >= 0 ? '+' : '-', date.iTZHour,
                 date.iTZMinute);
    }

    // Get custom entries
    _tprintf(_T("Custom entries:\n"));
    TPtx_StringMap* pCustomEntries = PtxPdf_Metadata_GetCustomEntries(pMetadata);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pCustomEntries, _T("Failed to get custom entries. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    for (int i = Ptx_StringMap_GetBegin(pCustomEntries), iEnd = Ptx_StringMap_GetEnd(pCustomEntries); i != iEnd;
         i = Ptx_StringMap_GetNext(pCustomEntries, i))
    {
        size_t nKeySize = Ptx_StringMap_GetKey(pCustomEntries, i, NULL, 0);
        TCHAR* szKey    = (TCHAR*)malloc(nKeySize * sizeof(TCHAR));
        nKeySize        = Ptx_StringMap_GetKey(pCustomEntries, i, szKey, nKeySize);

        size_t nValueSize = Ptx_StringMap_GetValue(pCustomEntries, i, NULL, 0);
        TCHAR* szValue    = (TCHAR*)malloc(nValueSize * sizeof(TCHAR));
        nValueSize        = Ptx_StringMap_GetValue(pCustomEntries, i, szValue, nValueSize);

        if (szKey && nKeySize && szValue && nValueSize)
            _tprintf(_T("  - %s: %s\n"), szKey, szValue);

        free(szKey);
        free(szValue);
    }


    _tprintf(_T("Execution successful.\n"));

cleanup:
    if (pInDoc != NULL)
        PtxPdf_Document_Close(pInDoc);
    if (pInStream != NULL)
        fclose(pInStream);
    Ptx_Uninitialize();

    return iReturnValue;
} 