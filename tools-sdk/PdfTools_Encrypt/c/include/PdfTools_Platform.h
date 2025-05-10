/******************************************************************************
 *
 * File:            PdfTools_Platform.h
 *
 * Description:     Header with platform specific defines.
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
 * Classification:  CONFIDENTIAL
 *
 *****************************************************************************/

#ifndef PDFTOOLS_PLATFORM_H__
#define PDFTOOLS_PLATFORM_H__

#include <stdarg.h>
#include <stdio.h>

#ifndef PDFTOOLS_CALL
#if defined(WIN32)
#define PDFTOOLS_CALL __stdcall
#else
#define PDFTOOLS_CALL
#endif
#endif

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#endif
/* Character strings on Windows can be either WinAnsi (CP1252) or Unicode (UTF16). */
/* On Unix only char strings (8-bit, ISO encoded) are used for OS interfaces. */
/* WCHAR strings are always UTF16 and may be different to wchar_t. */
/* This simplifies interoperability with Java. */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <tchar.h>
#ifndef WCHAR
#define WCHAR wchar_t
#endif
#ifndef CDECL
#define CDECL __cdecl
#endif
#ifndef STDCALL
#define STDCALL __stdcall
#endif
typedef __int64 pos_t;

#ifdef PDFTOOLS_STATIC_DEFINE
#define PDFTOOLS_EXPORT
#define PDFTOOLS_NO_EXPORT
#else
#ifndef PDFTOOLS_EXPORT
#ifdef PdfToolsSdk_EXPORTS
/* We are building this library */
#define PDFTOOLS_EXPORT __declspec(dllexport)
#else
/* We are using this library */
#define PDFTOOLS_EXPORT __declspec(dllimport)
#endif
#endif

#ifndef PDFTOOLS_NO_EXPORT
#define PDFTOOLS_NO_EXPORT
#endif
#endif

#ifndef PDFTOOLS_DEPRECATED
#define PDFTOOLS_DEPRECATED __declspec(deprecated)
#endif

#ifndef PDFTOOLS_DEPRECATED_EXPORT
#define PDFTOOLS_DEPRECATED_EXPORT PDFTOOLS_EXPORT PDFTOOLS_DEPRECATED
#endif

#ifndef PDFTOOLS_DEPRECATED_NO_EXPORT
#define PDFTOOLS_DEPRECATED_NO_EXPORT PDFTOOLS_NO_EXPORT PDFTOOLS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#ifndef PDFTOOLS_NO_DEPRECATED
#define PDFTOOLS_NO_DEPRECATED
#endif
#endif

#else
#include <stdlib.h>
#ifndef WCHAR
typedef unsigned short WCHAR;
#endif
#ifndef CDECL
#define CDECL
#endif
#ifndef STDCALL
#define STDCALL
#endif
typedef long long      pos_t;

#if defined(__APPLE__) || defined(__linux__)
#ifdef PDFTOOLS_STATIC_DEFINE
#define PDFTOOLS_EXPORT
#define PDFTOOLS_NO_EXPORT
#else
#ifndef PDFTOOLS_EXPORT
#ifdef PdfTools_EXPORTS
/* We are building this library */
#define PDFTOOLS_EXPORT __attribute__((visibility("default")))
#else
/* We are using this library */
#define PDFTOOLS_EXPORT __attribute__((visibility("default")))
#endif
#endif

#ifndef PDFTOOLS_NO_EXPORT
#define PDFTOOLS_NO_EXPORT __attribute__((visibility("hidden")))
#endif
#endif

#ifndef PDFTOOLS_DEPRECATED
#define PDFTOOLS_DEPRECATED __attribute__((__deprecated__))
#endif

#ifndef PDFTOOLS_DEPRECATED_EXPORT
#define PDFTOOLS_DEPRECATED_EXPORT PDFTOOLS_EXPORT PDFTOOLS_DEPRECATED
#endif

#ifndef PDFTOOLS_DEPRECATED_NO_EXPORT
#define PDFTOOLS_DEPRECATED_NO_EXPORT PDFTOOLS_NO_EXPORT PDFTOOLS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#ifndef PDFTOOLS_NO_DEPRECATED
#define PDFTOOLS_NO_DEPRECATED
#endif
#endif
#else
#define PDFTOOLS_EXPORT
#endif

#endif

#endif