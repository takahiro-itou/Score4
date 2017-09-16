
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  Score4CoreSettingsTest
    COMMAND  $<TARGET_FILE:Score4CoreSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (Score4CoreSettingsTest  Score4CoreSettingsTest.cpp)

