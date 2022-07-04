//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  The Score4 Core Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2020, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU General Public License (GPL) version 3,                 **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'HtmlDownloader'.
**
**      @file       Downloader/Tests/HtmlDownloaderTest.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Downloader/HtmlDownloader.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Downloader  {

//========================================================================
//
//    HtmlDownloaderTest  class.
//
/**
**    クラス HtmlDownloader の単体テスト。
**/

class  HtmlDownloaderTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(HtmlDownloaderTest);
    CPPUNIT_TEST(testHtmlDownloader);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testHtmlDownloader();
};

CPPUNIT_TEST_SUITE_REGISTRATION( HtmlDownloaderTest );

//========================================================================
//
//    Tests.
//

void  HtmlDownloaderTest::testHtmlDownloader()
{
    HtmlDownloader  dtFormat;

    return;
}


}   //  End of namespace  Downloader
SCORE4_CORE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
