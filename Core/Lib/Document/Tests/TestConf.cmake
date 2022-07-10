
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  DocumentFileTest
    COMMAND  $<TARGET_FILE:DocumentFileTest>
)

Add_Test (NAME  ScoreDocumentTest
    COMMAND  $<TARGET_FILE:ScoreDocumentTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (DocumentFileTest        DocumentFileTest.cpp)
Add_Executable (ScoreDocumentTest       ScoreDocumentTest.cpp)

