/******************************************************************************
 *
 * File:            PdfTools_PdfToolsSys.h
 *
 * Description:     Sytem declaration file
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

#ifndef PDFTOOLS_PDFTOOLSSYS_H__
#define PDFTOOLS_PDFTOOLSSYS_H__

#include <stdarg.h>
#ifndef NO_FILE_STREAM_DESCRIPTOR
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _UNICODE
#define PdfToolsSys_PathStreamDescriptor_Create PdfToolsSys_PathStreamDescriptor_CreateW
#else
#define PdfToolsSys_PathStreamDescriptor_Create PdfToolsSys_PathStreamDescriptor_CreateA
#endif

typedef pos_t(STDCALL* TGetLength)(void* handle);
typedef int(STDCALL* TSeek)(void* handle, pos_t iPos);
typedef pos_t(STDCALL* TTell)(void* handle);
typedef size_t(STDCALL* TRead)(void* handle, void* pData, size_t nSize);
typedef size_t(STDCALL* TWrite)(void* handle, const void* pData, size_t nSize);
typedef void(STDCALL* TRelease)(void* handle);

/** @brief Structure that groups a set of callbacks that model streams. */
typedef struct TPdfToolsSys_StreamDescriptor
{
    /** \brief Get length of stream in bytes */
    TGetLength pfGetLength;

    /** \brief Set position
     *  \param iPos byte position, -1 for end of stream
     *  \return 1 on success, 0 on failure
     */
    TSeek pfSeek;

    /** \brief Get current byte position
     *  \return byte position, -1 if position unknown
     */
    TTell pfTell;

    /** \brief Read nSize bytes from stream
     *  \return number of bytes read, 0 for end of stream, -1 for an error
     */
    TRead pfRead;

    /** \brief Write nSize bytes to stream
     *  \return number of bytes written, -1 for error (0 is interpreted as error too)
     */
    TWrite pfWrite;

    /** \brief Release handle */
    TRelease pfRelease;

    /** \brief Stream handle */
    void* m_handle;
} TPdfToolsSys_StreamDescriptor;

#ifndef NO_FILE_STREAM_DESCRIPTOR
/******************************************************************************
 * Stream descriptor for FILE*
 * (always use binary mode to fopen file!)
 *****************************************************************************/

/** @brief Callback implementation for \ref TPdfToolsSys_StreamDescriptor#pfGetLength for `FILE*`.
 *
 * @param[in,out] handle Handle of stream.
 * @return Length of stream in bytes. `-1` in case of an error.
 */
static pos_t STDCALL PdfToolsSysFILEPtrGetLength__(void* handle)
{
    pos_t iPos, nLen;
    iPos = ftell((FILE*)handle);
    if (iPos == -1)
        return -1;
    if (fseek((FILE*)handle, 0L, SEEK_END) != 0)
        return -1;
    nLen = ftell((FILE*)handle);
    if (fseek((FILE*)handle, (long)iPos, SEEK_SET) != 0)
        return -1;
    return nLen;
}

/** @brief Callback implementation for \ref TPdfToolsSys_StreamDescriptor#pfSeek for `FILE*`.
 *
 * Set new stream position.
 * @param[in,out] handle Handle of stream.
 * @param[in] iPos Byte position of stream. `-1` set position to end of stream.
 * @return `1` for success; `0` for failure.
 */
static int STDCALL PdfToolsSysFILEPtrSeek__(void* handle, pos_t iPos)
{
    return fseek((FILE*)handle, (long)iPos, SEEK_SET) == 0 ? 1 : 0;
}

/** @brief Callback implementation for \ref TPdfToolsSys_StreamDescriptor#pfTell for `FILE*`.
 *
 * Get current position of stream.
 * @param[in,out] handle Handle of stream.
 * @return Current byte position of stream; `-1` if position is unknown.
 */
static pos_t STDCALL PdfToolsSysFILEPtrTell__(void* handle) { return ftell((FILE*)handle); }

/** @brief Callback implementation for \ref TPdfToolsSys_StreamDescriptor#pfRead for `FILE*`.
 *
 * Read from stream into buffer
 * @param[in,out] handle Handle of stream.
 * @param[out] pData Pointer to the buffer to which the data from the stream is written.
 * @param[in] nSize Size in bytes of the stream to be read.
 * @return Number of bytes read; `0` for end of stream, `-1` in case of an error.
 */
static size_t STDCALL PdfToolsSysFILEPtrRead__(void* handle, void* pData, size_t nSize)
{
    size_t nRead = fread(pData, 1, nSize, (FILE*)handle);
    if (nRead != nSize && ferror((FILE*)handle) != 0)
        return (size_t)-1;
    return nRead;
}

/** @brief Callback implementation for \ref TPdfToolsSys_StreamDescriptor#pfWrite for `FILE*`.
 *
 * Write to stream from buffer
 * @param[in,out] handle Handle of stream.
 * @param[in] pData Pointer to the buffer from which data is written to the stream.
 * @param[in] nSize Size in bytes to be written.
 * @return Number of bytes written to stream; `0` or `-1` indicate an error.
 */
static size_t STDCALL PdfToolsSysFILEPtrWrite__(void* handle, const void* pData, size_t nSize)
{
    if (fwrite(pData, 1, nSize, (FILE*)handle) != nSize)
        return (size_t)-1;
    return nSize;
}

/** @brief Callback implementation for \ref TPdfToolsSys_StreamDescriptor#pfRelease for `FILE*`.
 *
 * Release handle to stream.
 * @param[in,out] handle Handle of stream.
 */
static void STDCALL PdfToolsSysFILEPtrRelease__(void* handle) { fclose((FILE*)handle); }

/** @brief Initialization function for \ref TPdfToolsSys_StreamDescriptor for `FILE*`.
 *
 * @param[out] pDescriptor `FILE*` stream descriptor that is initialized.
 * @param[in] handle Handle of stream.
 * @param[in] bCloseOnRelease Determines if the stream needs to be explicitly closed by `fclose((FILE*)handle)`.
 *            If set \ref TRUE the stream does not need to be explicitly closed; if set \ref FALSE the stream needs to
 * be explicitly closed.
 */
static void PdfToolsSysCreateFILEStreamDescriptor(TPdfToolsSys_StreamDescriptor* pDescriptor, FILE* handle,
                                                  int bCloseOnRelease)
{
    pDescriptor->m_handle    = handle;
    pDescriptor->pfGetLength = &PdfToolsSysFILEPtrGetLength__;
    pDescriptor->pfSeek      = &PdfToolsSysFILEPtrSeek__;
    pDescriptor->pfTell      = &PdfToolsSysFILEPtrTell__;
    pDescriptor->pfRead      = &PdfToolsSysFILEPtrRead__;
    pDescriptor->pfWrite     = &PdfToolsSysFILEPtrWrite__;
    pDescriptor->pfRelease   = bCloseOnRelease ? &PdfToolsSysFILEPtrRelease__ : NULL; // NOLINT(modernize-use-nullptr)
}
#endif // NO_FILE_STREAM_DESCRIPTOR

/******************************************************************************
 * Path Stream Descriptor convenience function
 *****************************************************************************/

/** @brief Initialization function for \ref TPdfToolsSys_StreamDescriptor for a given path.
 *
 * @param[out] pDescriptor Stream descriptor that is initialized.
 * @param[in] szPath Path to a file for which a stream descriptor shall be initialized.
 * @param[in] bIsReadOnly If set \ref TRUE the stream only allows for reading; if set to \ref FALSE the stream allows
 * for reading and writing.
 * @return \ref TRUE file opened successfully; \ref FALSE failed to open the file.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSys_PathStreamDescriptor_CreateA(TPdfToolsSys_StreamDescriptor* pDescriptor,
                                                                            const char* szPath, BOOL bIsReadOnly);
/** @brief Initialization function for \ref TPdfToolsSys_StreamDescriptor for a given path.
 *
 * @param[out] pDescriptor Stream descriptor that is initialized.
 * @param[in] szPath Path to a file for which a stream descriptor shall be initialized.
 * @param[in] bIsReadOnly If set \ref TRUE the stream only allows for reading; if set to \ref FALSE the stream allows
 * for reading and writing.
 * @return \ref TRUE file opened successfully; \ref FALSE failed to open the file.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL PdfToolsSys_PathStreamDescriptor_CreateW(TPdfToolsSys_StreamDescriptor* pDescriptor,
                                                                            const WCHAR* szPath, BOOL bIsReadOnly);
/** @brief Close the underlying file.
 *
 * @param[in] pDescriptor Pointer to the \ref TPdfToolsSys_StreamDescriptor that wraps the file.
 */
PDFTOOLS_EXPORT void PDFTOOLS_CALL PdfToolsSys_PathStreamDescriptor_Close(TPdfToolsSys_StreamDescriptor* pDescriptor);

/******************************************************************************
 * Stream Descriptor for memory streams
 *****************************************************************************/

/** @brief Initialization function for \ref TPdfToolsSys_StreamDescriptor for the usage as memory streams.
 *
 * @param[out] pDescriptor Stream descriptor that is initialized.
 * @return \ref TRUE memory stream initalized successfully; \ref FALSE failed to initialize memory stream.
 */
PDFTOOLS_EXPORT BOOL PDFTOOLS_CALL
PdfToolsSys_MemoryStreamDescriptor_Create(TPdfToolsSys_StreamDescriptor* pDescriptor);

/** @brief Delete the underlying buffer.
 *
 * @param[in] pDescriptor Pointer to the \ref TPdfToolsSys_StreamDescriptor that wraps the underlying buffer.
 */
PDFTOOLS_EXPORT void PDFTOOLS_CALL PdfToolsSys_MemoryStreamDescriptor_Close(TPdfToolsSys_StreamDescriptor* pDescriptor);

#ifdef __cplusplus
}
#endif

#endif /* PDFTOOLS_PDFTOOLSSYS_H__ */
