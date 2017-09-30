
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        Score4CoreSettingsTest  \
        ScoreDocumentTest       \
        ${EXTRATESTS}
##
##    Test Configurations.
##

TARGET_TESTEE_LIBRARY       +=  ../libscore4Common.a

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

Score4CoreSettingsTest_SOURCES  =  Score4CoreSettingsTest.cpp
ScoreDocumentTest_SOURCES       =  ScoreDocumentTest.cpp

