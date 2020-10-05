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
**      An Implementation of Test Case 'Score4CoreSettings'.
**
**      @file       Common/Tests/Score4CoreSettingsTest.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Common/Score4CoreSettings.h"

SCORE4_CORE_NAMESPACE_BEGIN

//========================================================================
//
//    Score4CoreSettingsTest  class.
//
/**
**    クラス Score4CoreSettings の単体テスト。
**/

class  Score4CoreSettingsTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(Score4CoreSettingsTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( Score4CoreSettingsTest );

//========================================================================
//
//    Tests.
//

void  Score4CoreSettingsTest::testNameSpace()
{
    return;
}

SCORE4_CORE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
