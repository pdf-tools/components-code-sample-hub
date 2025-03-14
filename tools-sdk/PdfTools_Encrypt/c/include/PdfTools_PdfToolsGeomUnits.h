/******************************************************************************
 *
 * File:            PdfTools_PdfToolsGeomUnits.h
 *
 * Description:     Sub Header file for Pdftools SDK
 *
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2023 - 2024 PDF Tools AG, Switzerland
 *                  All rights reserved.
 *
 * Notice:          By downloading and using this artifact, you accept PDF Tools AG's
 *                  [license agreement](https://www.pdf-tools.com/license-agreement/),
 *                  [privacy policy](https://www.pdf-tools.com/privacy-policy/),
 *                  and allow PDF Tools AG to track your usage data.
 *
 *****************************************************************************/

#ifndef PDFTOOLS_PDFTOOLSGEOMUNITS_H__
#define PDFTOOLS_PDFTOOLSGEOMUNITS_H__

#ifndef PDFTOOLS_CALL
#if defined(WIN32)
#define PDFTOOLS_CALL __stdcall
#else
#define PDFTOOLS_CALL
#endif
#endif

#include "PdfTools_Types.h"
#include "PdfTools_PdfToolsSys.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _UNICODE
#else
#endif

/**
 * @brief Convert inch to point.
 *
 * Helper function for the conversion between units.
 *
 * @param[in] dInches Length in inch that is subject to conversion.
 *
 * @return Length in point.
 */
PDFTOOLS_EXPORT double PDFTOOLS_CALL PdfToolsGeomUnits_Length_CreateFrom_inch(double dInches);
/**
 * @brief Convert millimetre to point.
 *
 * Helper function for the conversion between units.
 *
 * @param[in] dMillimetres Length in millimetre that is subject to conversion.
 *
 * @return Length in point.
 */
PDFTOOLS_EXPORT double PDFTOOLS_CALL PdfToolsGeomUnits_Length_CreateFrom_mm(double dMillimetres);
/**
 * @brief Convert point to inch.
 *
 * Helper function for the conversion between units.
 *
 * @param[in] dLength Length in point that is subject to conversion.
 *
 * @return Length in inch.
 */
PDFTOOLS_EXPORT double PDFTOOLS_CALL PdfToolsGeomUnits_Length_ConvertTo_inch(double dLength);
/**
 * @brief Convert point to millimetre.
 *
 * Helper function for the conversion between units.
 *
 * @param[in] dLength Length in point that is subject to conversion.
 *
 * @return Length in millimetre.
 */
PDFTOOLS_EXPORT double PDFTOOLS_CALL PdfToolsGeomUnits_Length_ConvertTo_mm(double dLength);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSGEOMUNITS_H__ */
