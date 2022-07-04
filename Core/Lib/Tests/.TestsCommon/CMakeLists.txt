
##----------------------------------------------------------------
##
##    モジュールの設定。
##

set(TARGET_TESTEE_LIBRARY   "${MODULE_TITLE}")

set(DRIVER_SOURCE_DIR       "${LIBTOP_SOURCE_DIR}/Tests")
set(DRIVER_BINARY_DIR       "${LIBTOP_BINARY_DIR}/Tests")

##----------------------------------------------------------------
##
##    テストの設定。
##

set(TESTER_LINK_LIBRARIES
        ${PROJECT_NAME}-${TARGET_TESTEE_LIBRARY}
        ${PROJECT_NAME}-TestDriver
)

include_directories(${PROJECT_SOURCE_DIR}/Lib/Tests)
link_libraries     (${TESTER_LINK_LIBRARIES})

Include (TestConf.cmake)
