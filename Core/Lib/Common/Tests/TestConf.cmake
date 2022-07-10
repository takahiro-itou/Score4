
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

Add_Test (NAME  ProcessManagerTest
    COMMAND  $<TARGET_FILE:ProcessManagerTest>
)

Add_Test (NAME  ProgressCallbackTest
    COMMAND  $<TARGET_FILE:ProgressCallbackTest>
)

Add_Test (NAME  Score4CoreSettingsTest
    COMMAND  $<TARGET_FILE:Score4CoreSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (DateTimeFormatTest      DateTimeFormatTest.cpp)
Add_Executable (ErrorDetectionCodeTest  ErrorDetectionCodeTest.cpp)
Add_Executable (ProcessManagerTest      ProcessManagerTest.cpp)
Add_Executable (ProgressCallbackTest    ProgressCallbackTest.cpp)
Add_Executable (Score4CoreSettingsTest  Score4CoreSettingsTest.cpp)

