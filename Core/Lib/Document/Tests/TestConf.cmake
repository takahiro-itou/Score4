
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  DocumentFileTest
    COMMAND  $<TARGET_FILE:DocumentFileTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (DocumentFileTest        DocumentFileTest.cpp)

