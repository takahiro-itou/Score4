
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        DateTimeFormatTest      \
        ErrorDetectionCodeTest  \
        ProcessManagerTest      \
        ProgressCallbackTest    \
        Score4CoreSettingsTest  \
        ${EXTRATESTS}
##
##    Test Configurations.
##

TARGET_TESTEE_LIBRARY       +=  -lscore4Common

DIST_NOINST_DATA_FILES      +=
DIST_NOINST_HEADER_FILES    +=
EXTRA_TEST_DRIVERS          +=
LIBRARY_TEST_DRIVERS        +=
SOURCE_TEST_DRIVERS         +=

##
##    Compile and Link Options.
##

TEST_CPPFLAGS_COMMON        +=
TEST_LDFLAGS_COMMON         +=

##
##    Test Programs.
##

DateTimeFormatTest_SOURCES      =  DateTimeFormatTest.cpp
ErrorDetectionCodeTest_SOURCES  =  ErrorDetectionCodeTest.cpp
ProcessManagerTest_SOURCES      =  ProcessManagerTest.cpp
ProgressCallbackTest_SOURCES    =  ProgressCallbackTest.cpp
Score4CoreSettingsTest_SOURCES  =  Score4CoreSettingsTest.cpp

