
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  ScoreDocumentTest
    COMMAND  $<TARGET_FILE:ScoreDocumentTest>
)

Add_Test (NAME  Score4CoreSettingsTest
    COMMAND  $<TARGET_FILE:Score4CoreSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (ScoreDocumentTest       ScoreDocumentTest.cpp)
Add_Executable (Score4CoreSettingsTest  Score4CoreSettingsTest.cpp)

