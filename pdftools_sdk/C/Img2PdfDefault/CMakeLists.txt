cmake_minimum_required(VERSION 3.16)

project(pdftoolsimg2pdfdefault_sample LANGUAGES C)

set(PDFTOOLS_SDK_URL
    "https://pdftools-public-downloads-production.s3.eu-west-1.amazonaws.com/productkits/PDFSDK/1.13.0/PdfToolsSDK_C-1.13.0.zip"
    CACHE STRING "URL to the PdfTools SDK archive (.zip)")

set(SDK_DIR     "${CMAKE_BINARY_DIR}/pdftools_sdk")
set(SDK_ARCHIVE "${CMAKE_BINARY_DIR}/PdfToolsSDK.zip")

if(NOT EXISTS "${SDK_DIR}/.sdk_ready")
    message(STATUS "Downloading PdfTools SDK from ${PDFTOOLS_SDK_URL} ...")
    file(DOWNLOAD
        "${PDFTOOLS_SDK_URL}" "${SDK_ARCHIVE}"
        STATUS DOWNLOAD_STATUS
        SHOW_PROGRESS
        INACTIVITY_TIMEOUT 30
        TLS_VERIFY ON
    )
    list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
    list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)
    if(NOT STATUS_CODE EQUAL 0)
        message(FATAL_ERROR "Failed to download PdfTools SDK: ${ERROR_MESSAGE}")
    endif()

    message(STATUS "Extracting PdfTools SDK ...")
    file(ARCHIVE_EXTRACT
        INPUT "${SDK_ARCHIVE}"
        DESTINATION "${SDK_DIR}"
    )

    file(REMOVE "${SDK_ARCHIVE}")
    file(TOUCH "${SDK_DIR}/.sdk_ready")
endif()

if(EXISTS "${SDK_DIR}/lib")
    set(SDK_ROOT "${SDK_DIR}")
else()
    file(GLOB SDK_CHILDREN LIST_DIRECTORIES true "${SDK_DIR}/*")
    list(FILTER SDK_CHILDREN EXCLUDE REGEX "\.sdk_ready$")
    list(LENGTH SDK_CHILDREN SDK_CHILDREN_LEN)
    if(SDK_CHILDREN_LEN EQUAL 1)
        list(GET SDK_CHILDREN 0 SDK_ROOT)
    else()
        message(FATAL_ERROR
            "Cannot locate lib/ in extracted SDK. "
            "Check the archive structure at ${SDK_DIR}")
    endif()
    if(NOT EXISTS "${SDK_ROOT}/lib")
        message(FATAL_ERROR
            "Cannot locate lib/ in extracted SDK. "
            "Found top-level dir ${SDK_ROOT} but it has no lib/ subdirectory.")
    endif()
endif()

if(NOT EXISTS "${SDK_ROOT}/include")
    message(FATAL_ERROR
        "Cannot locate include/ in extracted SDK at ${SDK_ROOT}.")
endif()

set(PRODUCT_SRC pdftoolsimg2pdfdefault.c)

add_executable(pdftoolsimg2pdfdefault ${PRODUCT_SRC})

if(WIN32)
    if(MSVC)
        add_compile_definitions(UNICODE)
    endif()

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM64|arm64|aarch64")
            set(PLATFORM_DIR win-arm64)
        else()
            set(PLATFORM_DIR win-x64)
        endif()
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(PLATFORM_DIR win-x86)
    endif()

    set(PRODUCT_LIB ${SDK_ROOT}/lib/${PLATFORM_DIR}/PdfToolsSdk.dll)
    set(API_LIB ${SDK_ROOT}/lib/${PLATFORM_DIR}/PdfToolsSdk.lib)
    add_custom_command(TARGET pdftoolsimg2pdfdefault POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PRODUCT_LIB}"
        "$<TARGET_FILE_DIR:pdftoolsimg2pdfdefault>")
elseif(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(PLATFORM_DIR osx-arm64)
    else()
        set(PLATFORM_DIR osx-x64)
    endif()

    find_library(API_LIB PdfToolsSdk PATHS ${SDK_ROOT}/lib/${PLATFORM_DIR})
elseif(UNIX)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM64|arm64|aarch64")
        set(PLATFORM_DIR linux-arm64)
    else()
        set(PLATFORM_DIR linux-x64)
    endif()
    find_library(API_LIB PdfToolsSdk PATHS ${SDK_ROOT}/lib/${PLATFORM_DIR})
endif()

target_link_libraries(pdftoolsimg2pdfdefault ${API_LIB})
target_include_directories(pdftoolsimg2pdfdefault PUBLIC ${SDK_ROOT}/include)
