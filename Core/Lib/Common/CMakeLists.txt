
##----------------------------------------------------------------
##
##    モジュールの設定。
##

Set (MODULE_DIR_NAME       "Common")
Set (MODULE_OUTPUT_NAME    "Common")
Set (MODULE_TITLE          "Common")

Set (INCLIB_SOURCE_DIR     "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
Set (INCLIB_BINARY_DIR     "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

Set (LIBRARY_SOURCE_FILES
        DateTimeFormat.cpp
        ErrorDetectionCode.cpp
        ProcessManager.cpp
        ProgressCallback.cpp
        TextParser.cpp
)

Set (INCLIB_HEADER_FILES
        ${INCLIB_SOURCE_DIR}/DateTimeFormat.h
        ${INCLIB_SOURCE_DIR}/ErrorDetectionCode.h
        ${INCLIB_SOURCE_DIR}/ProcessManager.h
        ${INCLIB_SOURCE_DIR}/ProgressCallback.h
        ${INCLIB_SOURCE_DIR}/Score4CoreSettings.h
        ${INCLIB_SOURCE_DIR}/Score4Types.h
        ${INCLIB_SOURCE_DIR}/ScoreInterface.h
        ${INCLIB_SOURCE_DIR}/TextParser.h
)

Set (MODULE_NEEDS_LIBRARIES
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

Include (${COMMON_CMAKE_DIR}/BuildLibraryCommon.cmake)

##----------------------------------------------------------------
##
##    テストの設定。
##

Add_SubDirectory (Tests)

