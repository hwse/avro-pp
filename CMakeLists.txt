cmake_minimum_required(VERSION 3.14)
project(avro-pp VERSION 0.0.0)
set(CMAKE_CXX_STANDARD 20)

include(cmake/get_cpm.cmake)

option(ENABLE_CPM_EVERYWHERE "Use CPM Package manager for all dependencies (zlib)" "${WIN32}")

CPMAddPackage("gh:fmtlib/fmt#10.2.1")

if (ENABLE_CPM_EVERYWHERE)
    CPMAddPackage(
            NAME zlib
            VERSION 1.3.1
            GIT_TAG v1.3.1
            GITHUB_REPOSITORY madler/zlib
            EXCLUDE_FROM_ALL
            OPTIONS
            "ZLIB_BUILD_TESTING OFF"
            "ZLIB_BUILD_SHARED OFF"
            "ZLIB_BUILD_STATIC ON"
            "ZLIB_INSTALL OFF"
            "ZLIB_INSTALL_COMPAT_DLL OFF"
    )
    add_library(ZLIB::ZLIB ALIAS zlibstatic)
else ()
    find_package(ZLIB REQUIRED)
    message(STATUS "Using local zlib ${ZLIB_VERSION_STRING}")
endif ()

CPMAddPackage(
        NAME avrocpp
        VERSION 356efee046234004e77a8719d24b9ca03fa79aea
        GIT_TAG 356efee046234004e77a8719d24b9ca03fa79aea
        GITHUB_REPOSITORY apache/avro
        DOWNLOAD_ONLY
)
set(AVRO_LANG_DIR ${avrocpp_SOURCE_DIR}/lang/c++)
add_library(avrocpp
        ${AVRO_LANG_DIR}/impl/Compiler.cc
        ${AVRO_LANG_DIR}/impl/Node.cc
        ${AVRO_LANG_DIR}/impl/LogicalType.cc
        ${AVRO_LANG_DIR}/impl/NodeImpl.cc
        ${AVRO_LANG_DIR}/impl/ResolverSchema.cc
        ${AVRO_LANG_DIR}/impl/Schema.cc
        ${AVRO_LANG_DIR}/impl/Types.cc
        ${AVRO_LANG_DIR}/impl/ValidSchema.cc
        ${AVRO_LANG_DIR}/impl/Zigzag.cc
        ${AVRO_LANG_DIR}/impl/BinaryEncoder.cc
        ${AVRO_LANG_DIR}/impl/BinaryDecoder.cc
        ${AVRO_LANG_DIR}/impl/Stream.cc
        ${AVRO_LANG_DIR}/impl/FileStream.cc
        ${AVRO_LANG_DIR}/impl/Generic.cc
        ${AVRO_LANG_DIR}/impl/GenericDatum.cc
        ${AVRO_LANG_DIR}/impl/DataFile.cc
        ${AVRO_LANG_DIR}/impl/parsing/Symbol.cc
        ${AVRO_LANG_DIR}/impl/parsing/ValidatingCodec.cc
        ${AVRO_LANG_DIR}/impl/parsing/JsonCodec.cc
        ${AVRO_LANG_DIR}/impl/parsing/ResolvingDecoder.cc
        ${AVRO_LANG_DIR}/impl/json/JsonIO.cc
        ${AVRO_LANG_DIR}/impl/json/JsonDom.cc
        ${AVRO_LANG_DIR}/impl/Resolver.cc
        ${AVRO_LANG_DIR}/impl/Validator.cc
        ${AVRO_LANG_DIR}/impl/CustomAttributes.cc
)
target_include_directories(avrocpp PUBLIC ${AVRO_LANG_DIR}/include)
target_include_directories(avrocpp PRIVATE ${AVRO_LANG_DIR}/include/avro)
target_link_libraries(avrocpp
        PRIVATE
        fmt::fmt-header-only
        ZLIB::ZLIB
)


add_executable(avro-pp src/main.cpp)
target_link_libraries(avro-pp PRIVATE avrocpp fmt::fmt-header-only)