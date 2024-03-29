
##----------------------------------------------------------------
##
##    Package Configurations.
##    パッケージ設定。
##

##
##    要求するツールのバージョンを指定する。
##

cmake_minimum_required(VERSION  3.0.2)

##
##    パッケージの情報を指定する。
##

set(PROJECT_NAME        Score4Core)
set(serial              "0.0.0")

project(${PROJECT_NAME}     VERSION  1.0.0)

##----------------------------------------------------------------
##
##    プロジェクトの基本設定。
##

enable_testing ()

set(COMMON_CMAKE_DIR        "${PROJECT_SOURCE_DIR}/.CMake")
set(INCTOP_DIR_NAME         "Include")
set(BINTOP_DIR_NAME         "Bin")
set(LIBTOP_DIR_NAME         "Lib")
set(INCPKG_DIR_NAME         "${PROJECT_NAME}")
set(PACKAGE_INCLUDE_DIR     "${INCTOP_DIR_NAME}/${INCPKG_DIR_NAME}")

set(INCTOP_SOURCE_DIR       "${PROJECT_SOURCE_DIR}/${INCTOP_DIR_NAME}")
set(INCTOP_BINARY_DIR       "${PROJECT_BINARY_DIR}/${INCTOP_DIR_NAME}")
set(LIBTOP_SOURCE_DIR       "${PROJECT_SOURCE_DIR}/${LIBTOP_DIR_NAME}")
set(LIBTOP_BINARY_DIR       "${PROJECT_BINARY_DIR}/${LIBTOP_DIR_NAME}")

set(INCLUDE_SOURCE_DIR      "${INCTOP_SOURCE_DIR}/${INCPKG_DIR_NAME}")
set(INCLUDE_BINARY_DIR      "${INCTOP_BINARY_DIR}/${INCPKG_DIR_NAME}")

##----------------------------------------------------------------
##
##    ビルド環境の検査。
##

Include (${COMMON_CMAKE_DIR}/EnableCxx11.cmake)

Include (${COMMON_CMAKE_DIR}/CheckConstExpr.cmake)
Include (${COMMON_CMAKE_DIR}/CheckNullPtr.cmake)
Include (${COMMON_CMAKE_DIR}/CheckOverride.cmake)

##
##    Project Name Space.
##

set(SCORE4CORE_CNF_NAMESPACE    Score4Core)

##----------------------------------------------------------------
##
##    インクルードパスの設定。
##

include_directories("${PROJECT_SOURCE_DIR}/Include")
include_directories("${PROJECT_BINARY_DIR}/Include")

##----------------------------------------------------------------
##
##    Additional Packages.
##    外部ライブラリ。
##

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}  ${COMMON_CMAKE_DIR}/Modules
)

Find_Package (CppUnit)

##----------------------------------------------------------------
##
##    設定を書き込んだファイルを生成。
##

configure_file(
    "${INCLUDE_SOURCE_DIR}/.Config/ConfiguredScore4Core.h.in"
    "${INCLUDE_BINARY_DIR}/.Config/ConfiguredScore4Core.h"
)

configure_file(
    "${INCLUDE_SOURCE_DIR}/.Config/Config.h.cmake.in"
    "${INCLUDE_BINARY_DIR}/.Config/.${PROJECT_NAME}.Config.h"
)

##----------------------------------------------------------------
##
##    パッケージコンフィグレーション。
##

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    @ONLY
)

install(FILES   "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION  .
)

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

add_subdirectory(Lib)
add_subdirectory(Bin)
