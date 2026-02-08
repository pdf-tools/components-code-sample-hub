/****************************************************************************
 *
 * File:            toolboxlistsignatures.c
 *
 * Usage:           toolboxlistsignatures <inputPath>
 *                  
 * Title:           List Signatures in PDF
 *                  
 * Description:     List all signature fields in a PDF document and their
 *                  properties.
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
    printf("Usage: toolboxlistsignatures <inputPath>.\n");
    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

TPtxGeomReal_Size size;
size_t            nBufSize;
TCHAR             szErrorBuff[1024];

int _tmain(int argc, TCHAR* argv[])
{
    FILE*                            pInStream = NULL;
    TPtxSys_StreamDescriptor         descriptor;
    TPtxPdf_Document*                pInDoc = NULL;
    TPtxPdfForms_SignatureFieldList* pSignatureFields;
    TPtxPdfForms_SignatureField*     pSig;
    TCHAR*                           szInPath;
    TPtxSys_Date                     date;
    int                              iReturnValue = 0;

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 2 || argc > 2)
    {
        return Usage();
    }

    // Initialize library
    Ptx_Initialize();

    // Set and check license key
    GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(Ptx_Sdk_Initialize(_T("LICENSE-KEY"), NULL),
                                      _T("Failed to set license key. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                      Ptx_GetLastError());

    szInPath = argv[1];

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL(pInStream, _T("Failed to open input file \"%s\".\n"), szInPath);
    PtxSysCreateFILEStreamDescriptor(&descriptor, pInStream, 0);
    pInDoc = PtxPdf_Document_Open(&descriptor, _T(""));
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInDoc, _T("Input file \"%s\" cannot be opened. %s (ErrorCode: 0x%08x).\n"),
                                     szInPath, szErrorBuff, Ptx_GetLastError());

    // Get signatures of input PDF
    pSignatureFields = PtxPdf_Document_GetSignatureFields(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pSignatureFields,
                                     _T("Failed to get signatures of input PDF. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());
    _tprintf(_T("Number of signature fields: %d\n"), PtxPdfForms_SignatureFieldList_GetCount(pSignatureFields));

    for (int i = 0; i < PtxPdfForms_SignatureFieldList_GetCount(pSignatureFields); i++)
    {
        pSig = PtxPdfForms_SignatureFieldList_Get(pSignatureFields, i);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pSig, _T("Failed to get signature. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                         Ptx_GetLastError());

        TPtxPdfForms_SignatureFieldType iFieldType = PtxPdfForms_SignatureField_GetType(pSig);
        if (iFieldType == ePtxPdfForms_SignatureFieldType_Signature ||
            iFieldType == ePtxPdfForms_SignatureFieldType_DocMdpSignature ||
            iFieldType == ePtxPdfForms_SignatureFieldType_DocumentSignature)
        {
            // List name
            size_t nName = PtxPdfForms_SignedSignatureField_GetName(pSig, NULL, 0);
            _tprintf(_T("- %s fields"), PtxPdfForms_SignatureField_IsVisible(pSig) ? _T("Visible") : _T("Invisible"));
            if (nName != 0)
            {
                TCHAR* szName = (TCHAR*)malloc(nName * sizeof(TCHAR));
                if (szName != NULL)
                {
                    PtxPdfForms_SignedSignatureField_GetName(pSig, szName, nName);
                    _tprintf(_T(", signed by: %s"), szName);
                    free(szName);
                }
            }
            _tprintf(_T("\n"));

            // List location
            size_t nLocation = PtxPdfForms_Signature_GetLocation(pSig, NULL, 0);
            if (nLocation != 0)
            {
                TCHAR* szLocation = (TCHAR*)malloc(nLocation * sizeof(TCHAR));
                if (szLocation != NULL)
                {
                    PtxPdfForms_Signature_GetLocation(pSig, szLocation, nLocation);
                    _tprintf(_T("  - Location: %s\n"), szLocation);
                    free(szLocation);
                }
            }

            // List reason
            size_t nReason = PtxPdfForms_Signature_GetReason(pSig, NULL, 0);
            if (nReason != 0)
            {
                TCHAR* szReason = (TCHAR*)malloc(nReason * sizeof(TCHAR));
                if (szReason != NULL)
                {
                    PtxPdfForms_Signature_GetReason(pSig, szReason, nReason);
                    _tprintf(_T("  - Reason: %s\n"), szReason);
                    free(szReason);
                }
            }

            // List contact info
            size_t nContactInfo = PtxPdfForms_Signature_GetContactInfo(pSig, NULL, 0);
            if (nContactInfo != 0)
            {
                TCHAR* szContactInfo = (TCHAR*)malloc(nContactInfo * sizeof(TCHAR));
                if (szContactInfo != NULL)
                {
                    PtxPdfForms_Signature_GetContactInfo(pSig, szContactInfo, nContactInfo);
                    _tprintf(_T("  - Contact info: %s\n"), szContactInfo);
                    free(szContactInfo);
                }
            }

            // List date
            if (PtxPdfForms_SignedSignatureField_GetDate(pSig, &date) == TRUE)
            {
                _tprintf(_T("  - Date: %02d-%02d-%d %02d:%02d:%02d%c%02d:%02d\n"), date.iYear, date.iMonth, date.iDay,
                         date.iHour, date.iMinute, date.iSecond, date.iTZSign >= 0 ? '+' : '-', date.iTZHour,
                         date.iTZMinute);
            }
        }
        else
        {
            _tprintf(_T("- %s field, not signed\n"),
                     PtxPdfForms_SignatureField_IsVisible(pSig) ? _T("Visible") : _T("Invisible"));
        }
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