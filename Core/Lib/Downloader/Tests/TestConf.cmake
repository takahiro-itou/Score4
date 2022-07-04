
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  HtmlDownloaderTest
    COMMAND  $<TARGET_FILE:HtmlDownloaderTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (HtmlDownloaderTest      HtmlDownloaderTest.cpp)

