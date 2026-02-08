/****************************************************************************
 *
 * File:            toolboxfillformfields.c
 *
 * Usage:           toolboxfillformfields <fieldID> <value> <inputPath> <outputPath>
 *                  Example: TextField1 \"New Text\" Form2None.pdf out.pdf
 *                  
 * Title:           Fill form fields
 *                  
 * Description:     Change values of AcroForm form fields.
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

#define GOTO_CLEANUP_IF_ZERO(val, ...) \
    do                                 \
    {                                  \
        if ((val) == 0)                \
        {                              \
            _tprintf(__VA_ARGS__);     \
            iReturnValue = 1;          \
            goto cleanup;              \
        }                              \
    } while (0);

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
        if ((val) == FALSE)                                                               \
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
    printf("Usage: toolboxfillformfields <fieldID> <value> <inputPath> <outputPath>.\n");
    printf("       Example: TextField1 \"New Text\" Form2None.pdf out.pdf\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

TCHAR  szErrorBuff[1024];
size_t nBufSize;
int    iReturnValue = 0;

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

int copyFields(TPtxPdf_Document* pInDoc, TPtxPdf_Document* pOutDoc)
{
    // Objects that need releasing or closing
    TPtxPdfForms_FieldNodeMap* pInFields     = NULL;
    TPtxPdfForms_FieldNodeMap* pOutFields    = NULL;
    TCHAR*                     szFieldKey    = NULL;
    TPtxPdfForms_FieldNode*    pInFieldNode  = NULL;
    TPtxPdfForms_FieldNode*    pOutFieldNode = NULL;

    iReturnValue = 0;

    pInFields = PtxPdf_Document_GetFormFields(pInDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInFields,
                                     _T("Failed to get form fields of the input document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    pOutFields = PtxPdf_Document_GetFormFields(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutFields,
                                     _T("Failed to get form fields of the output document. %s (ErrorCode: 0x%08x).\n"),
                                     szErrorBuff, Ptx_GetLastError());

    for (int iField = PtxPdfForms_FieldNodeMap_GetBegin(pInFields);
         iField != PtxPdfForms_FieldNodeMap_GetEnd(pInFields);
         iField = PtxPdfForms_FieldNodeMap_GetNext(pInFields, iField))
    {
        if (iField == 0)
            GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get form field. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                              Ptx_GetLastError());
        // Get key
        size_t nKey = PtxPdfForms_FieldNodeMap_GetKey(pInFields, iField, szFieldKey, 0);
        GOTO_CLEANUP_IF_ZERO(nKey, _T("Failed to get form field key\n"));
        szFieldKey = (TCHAR*)malloc(nKey * sizeof(TCHAR*));
        GOTO_CLEANUP_IF_NULL(szFieldKey, _T("Failed to allocate memory for field key\n"));
        if (PtxPdfForms_FieldNodeMap_GetKey(pInFields, iField, szFieldKey, nKey) != nKey)
        {
            GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get form field key. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                              Ptx_GetLastError());
        }
        // Get input field node
        pInFieldNode = PtxPdfForms_FieldNodeMap_GetValue(pInFields, iField);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pInFieldNode, _T("Failed to get form field. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());
        // Copy field node to output document
        pOutFieldNode = PtxPdfForms_FieldNode_Copy(pOutDoc, pInFieldNode);
        GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutFieldNode, _T("Failed to copy form field. %s (ErrorCode: 0x%08x)\n"),
                                         szErrorBuff, Ptx_GetLastError());
        // Add copied field node to output fields
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfForms_FieldNodeMap_Set(pOutFields, szFieldKey, pOutFieldNode),
                                          _T("Failed to add form field \"%s\". %s (ErrorCode: 0x%08x)\n"), szFieldKey,
                                          szErrorBuff, Ptx_GetLastError());
        // Clean up for next iteration
        free(szFieldKey);
        szFieldKey = NULL;
        Ptx_Release(pOutFieldNode);
        pOutFieldNode = NULL;
        Ptx_Release(pInFieldNode);
        pInFieldNode = NULL;
    }

cleanup:
    if (pOutFieldNode != NULL)
        Ptx_Release(pOutFieldNode);
    if (pInFieldNode != NULL)
        Ptx_Release(pInFieldNode);
    if (szFieldKey != NULL)
        free(szFieldKey);
    if (pOutFields != NULL)
        Ptx_Release(pOutFields);
    if (pInFields != NULL)
        Ptx_Release(pInFields);
    return iReturnValue;
}

int fillFormField(TPtxPdfForms_Field* pField, const TCHAR* szValue)
{
    // Objects that need releasing or closing
    TPtxPdfForms_RadioButtonList* pButtonList     = NULL;
    TPtxPdfForms_RadioButton*     pButton         = NULL;
    TPtxPdfForms_ChoiceItemList*  pChoiceItemList = NULL;
    TPtxPdfForms_ChoiceItem*      pItem           = NULL;
    TCHAR*                        szName          = NULL;

    // Other variables
    TPtxPdfForms_FieldType         iType             = 0;
    TPtxPdfForms_CheckBox*         pCheckBox         = NULL;
    TPtxPdfForms_RadioButtonGroup* pRadioButtonGroup = NULL;

    iReturnValue = 0;
    iType        = PtxPdfForms_Field_GetType(pField);

    if (iType == ePtxPdfForms_FieldType_GeneralTextField || iType == ePtxPdfForms_FieldType_CombTextField)
    {
        GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfForms_TextField_SetText((TPtxPdfForms_TextField*)pField, szValue),
                                          _T("Failed to set text field value. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                          Ptx_GetLastError());
    }
    else if (iType == ePtxPdfForms_FieldType_CheckBox)
    {
        pCheckBox = (TPtxPdfForms_CheckBox*)pField;
        if (_tcscmp(szValue, _T("on")) == 0)
        {
            GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfForms_CheckBox_SetChecked(pCheckBox, TRUE),
                                              _T("Failed to set check box. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                              Ptx_GetLastError());
        }
        else
        {
            GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(PtxPdfForms_CheckBox_SetChecked(pCheckBox, FALSE),
                                              _T("Failed to set check box. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                              Ptx_GetLastError());
        }
    }
    else if (iType == ePtxPdfForms_FieldType_RadioButtonGroup)
    {
        pRadioButtonGroup = (TPtxPdfForms_RadioButtonGroup*)pField;
        pButtonList       = PtxPdfForms_RadioButtonGroup_GetButtons(pRadioButtonGroup);
        for (int iButton = 0; iButton < PtxPdfForms_RadioButtonList_GetCount(pButtonList); iButton++)
        {
            pButton = PtxPdfForms_RadioButtonList_Get(pButtonList, iButton);
            GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pButton, _T("Failed to get radio button. %s (ErrorCode: 0x%08x)\n"),
                                             szErrorBuff, Ptx_GetLastError())
            size_t nName = PtxPdfForms_RadioButton_GetExportName(pButton, szName, 0);
            GOTO_CLEANUP_IF_ZERO(nName, _T("Failed to get radio button name\n"));
            szName = (TCHAR*)malloc(nName * sizeof(TCHAR*));
            GOTO_CLEANUP_IF_NULL(szName, _T("Failed to allocate memory for radio button name\n"));
            if (PtxPdfForms_RadioButton_GetExportName(pButton, szName, nName) != nName)
            {
                GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get radio button name. %s (ErrorCode: 0x%08x)\n"),
                                                  szErrorBuff, Ptx_GetLastError());
            }
            if (_tcscmp(szValue, szName) == 0)
            {
                GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
                    PtxPdfForms_RadioButtonGroup_SetChosenButton(pRadioButtonGroup, pButton),
                    _T("Failed to set radio button. %s (ErrorCode: 0x%08x)\n"), szErrorBuff, Ptx_GetLastError());
            }
            free(szName);
            szName = NULL;
            Ptx_Release(pButton);
            pButton = NULL;
        }
    }
    else if (iType == ePtxPdfForms_FieldType_ComboBox || iType == ePtxPdfForms_FieldType_ListBox)
    {
        pChoiceItemList = PtxPdfForms_ChoiceField_GetItems((TPtxPdfForms_ChoiceField*)pField);
        for (int iItem = 0; iItem < PtxPdfForms_ChoiceItemList_GetCount(pChoiceItemList); iItem++)
        {
            pItem = PtxPdfForms_ChoiceItemList_Get(pChoiceItemList, iItem);
            GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pItem,
                                             _T("Failed to get item from choice field. %s (ErrorCode: 0x%08x)\n"),
                                             szErrorBuff, Ptx_GetLastError());
            size_t nName = PtxPdfForms_ChoiceItem_GetDisplayName(pItem, szName, 0);
            GOTO_CLEANUP_IF_ZERO(nName, _T("Failed to get choice item name\n"));
            szName = (TCHAR*)malloc(nName * sizeof(TCHAR*));
            GOTO_CLEANUP_IF_NULL(szName, _T("Failed to allocate memory for choice item name\n"));
            if (PtxPdfForms_ChoiceItem_GetDisplayName(pItem, szName, nName) != nName)
            {
                GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to get choice item name. %s (ErrorCode: 0x%08x)\n"),
                                                  szErrorBuff, Ptx_GetLastError());
            }
            if (_tcscmp(szValue, szName) == 0)
            {
                break;
            }
            free(szName);
            szName = NULL;
            Ptx_Release(pItem);
            pItem = NULL;
        }
        if (pItem != NULL)
        {
            free(szName);
            szName = NULL;
            if (iType == ePtxPdfForms_FieldType_ComboBox)
            {
                GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
                    PtxPdfForms_ComboBox_SetChosenItem((TPtxPdfForms_ComboBox*)pField, pItem),
                    _T("Failed to set choice item for combo box. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                    Ptx_GetLastError());
            }
            else // iType == ePtxPdfForms_FieldType_ListBox
            {
                Ptx_Release(pChoiceItemList);
                pChoiceItemList = PtxPdfForms_ListBox_GetChosenItems((TPtxPdfForms_ListBox*)pField);
                GOTO_CLEANUP_IF_NULL_PRINT_ERROR(
                    pChoiceItemList, _T("Failed to get list of chosen items for list box. %s (ErrorCode: 0x%08x)\n"),
                    szErrorBuff, Ptx_GetLastError());
                GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
                    PtxPdfForms_ChoiceItemList_Clear(pChoiceItemList),
                    _T("Failed to clear list of chosen items for list box. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                    Ptx_GetLastError());
                GOTO_CLEANUP_IF_FALSE_PRINT_ERROR(
                    PtxPdfForms_ChoiceItemList_Add(pChoiceItemList, pItem),
                    _T("Failed to add item to list of chosen items for list box. %s (ErrorCode: 0x%08x)\n"),
                    szErrorBuff, Ptx_GetLastError());
            }
        }
    }

cleanup:
    if (szName != NULL)
        free(szName);
    if (pItem == NULL)
        Ptx_Release(pItem);
    if (pChoiceItemList == NULL)
        Ptx_Release(pChoiceItemList);
    if (pButton != NULL)
        Ptx_Release(pButton);
    if (pButtonList != NULL)
        Ptx_Release(pButton);

    return iReturnValue;
}


int _tmain(int argc, TCHAR* argv[])
{
    // Objects that need releasing or closing
    FILE*                      pInStream    = NULL;
    TPtxPdf_Document*          pInDoc       = NULL;
    FILE*                      pOutStream   = NULL;
    TPtxPdf_Document*          pOutDoc      = NULL;
    TPtxPdf_PageList*          pInPageList  = NULL;
    TPtxPdf_PageList*          pOutPageList = NULL;
    TPtxPdfForms_FieldNodeMap* pFields      = NULL;
    TPtxPdf_PageList*          pCopiedPages = NULL;
    TPtxPdfForms_FieldNode*    pFieldNode   = NULL;
    TPtxPdfForms_Field*        pField       = NULL;
    TPtxPdf_PageCopyOptions*   pCopyOptions = NULL;
    TCHAR*                     szFieldID    = NULL;
    TCHAR*                     szFieldValue = NULL;

    // Other variables
    TCHAR*                   szInPath  = NULL;
    TCHAR*                   szOutPath = NULL;
    TPtxPdf_Conformance      iConformance;
    TPtxSys_StreamDescriptor inDescriptor;
    TPtxSys_StreamDescriptor outDescriptor;

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
                                      _T("Failed to set license key. %s (ErrorCode: 0x%08x)\n"), szErrorBuff,
                                      Ptx_GetLastError());

    szFieldID    = argv[1];
    szFieldValue = argv[2];
    szInPath     = argv[3];
    szOutPath    = argv[4];

    // Open input document
    pInStream = _tfopen(szInPath, _T("rb"));
    GOTO_CLEANUP_IF_NULL(pInStream, _T("Failed to open input file \"%s\".\n"), szInPath);
    PtxSysCreateFILEStreamDescriptor(&inDescriptor, pInStream, 0);
    pInDoc = PtxPdf_Document_Open(&inDescriptor, _T(""));
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
    if (copyDocumentData(pInDoc, pOutDoc) == 1)
    {
        iReturnValue = 1;
        goto cleanup;
    }

    if (copyFields(pInDoc, pOutDoc) == 1)
    {
        iReturnValue = 1;
        goto cleanup;
    }

    pFields = PtxPdf_Document_GetFormFields(pOutDoc);
    GOTO_CLEANUP_IF_NULL_PRINT_ERROR(pOutDoc, _T("Failed to get form fields. %s (ErrorCode: 0x%08x).\n"), szErrorBuff,
                                     Ptx_GetLastError());
    pFieldNode = PtxPdfForms_FieldNodeMap_Lookup(pFields, szFieldID);
    if (pFieldNode == NULL)
    {
        GOTO_CLEANUP_IF_ERROR_PRINT_ERROR(_T("Failed to lookup form field with ID \"%s\". %s (ErrorCode: 0x%08x)\n"),
                                          szFieldID, szErrorBuff, Ptx_GetLastError());
    }
    else if (PtxPdfForms_FieldNode_GetType(pFieldNode) != ePtxPdfForms_FieldNodeType_FieldNode)
    {
        if (fillFormField((TPtxPdfForms_Field*)pFieldNode, szFieldValue) == 1)
        {
            iReturnValue = 1;
            goto cleanup;
        }
    }

    // Configure copy options
    pCopyOptions = PtxPdf_PageCopyOptions_New();
    PtxPdf_PageCopyOptions_SetFormFields(pCopyOptions, ePtxPdfForms_FormFieldCopyStrategy_CopyAndUpdateWidgets);
    PtxPdf_PageCopyOptions_SetUnsignedSignatures(pCopyOptions, ePtxPdf_CopyStrategy_Remove);

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
    if (pCopyOptions != NULL)
        Ptx_Release(pCopyOptions);
    if (pFieldNode != NULL)
        Ptx_Release(pFieldNode);
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
    if (pInDoc != NULL)
        PtxPdf_Document_Close(pInDoc);
    if (pInStream)
        fclose(pInStream);

    Ptx_Uninitialize();

    return iReturnValue;
} 