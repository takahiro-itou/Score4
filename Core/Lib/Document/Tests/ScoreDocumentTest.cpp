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
**      An Implementation of Test Case 'ScoreDocument'.
**
**      @file       Document/Tests/ScoreDocumentTest.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Document/ScoreDocument.h"

#include    <fstream>
#include    <sstream>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ScoreDocumentTest  class.
//
/**
**    クラス ScoreDocument  の単体テスト。
**/

class  ScoreDocumentTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ScoreDocumentTest);
    CPPUNIT_TEST(testScoreDocument);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testScoreDocument();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ScoreDocumentTest );

//========================================================================
//
//    Tests.
//

void  ScoreDocumentTest::testScoreDocument()
{
    ScoreDocument   sd;
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
