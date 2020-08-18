
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  DateTimeFormatTest
    COMMAND  $<TARGET_FILE:DateTimeFormatTest>
)

Add_Test (NAME  ErrorDetectionCodeTest
    COMMAND  $<TARGET_FILE:ErrorDetectionCodeTest>
)

Add_Test (NAME  Score4CoreSettingsTest
    COMMAND  $<TARGET_FILE:Score4CoreSettingsTest>
)

Add_Test (NAME  ScoreDocumentTest
    COMMAND  $<TARGET_FILE:ScoreDocumentTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (DateTimeFormatTest      DateTimeFormatTest.cpp)
Add_Executable (ErrorDetectionCodeTest  ErrorDetectionCodeTest.cpp)
Add_Executable (Score4CoreSettingsTest  Score4CoreSettingsTest.cpp)
Add_Executable (ScoreDocumentTest       ScoreDocumentTest.cpp)

