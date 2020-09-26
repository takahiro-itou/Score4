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
**      An Implementation of Test Case 'ProgressCallback'.
**
**      @file       Common/Tests/ProgressCallback.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Common/ProgressCallback.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ProgressCallbackTest  class.
//
/**
**    クラス ProgressCallback の単体テスト。
**/

class  ProgressCallbackTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ProgressCallbackTest);
    CPPUNIT_TEST(testProgressCallback);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testProgressCallback();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ProgressCallbackTest );

//========================================================================
//
//    Tests.
//

void  ProgressCallbackTest::testProgressCallback()
{
    ProgressCallback    cbProgress;

    return;
}

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
