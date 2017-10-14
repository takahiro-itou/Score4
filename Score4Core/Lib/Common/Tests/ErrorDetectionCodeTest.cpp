//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  The Score4 Core Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2017, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'ErrorDetectionCode'.
**
**      @file       Common/Tests/ErrorDetectionCodeTest.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Common/ErrorDetectionCode.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ErrorDetectionCodeTest  class.
//
/**
**    クラス ErrorDetectionCode の単体テスト。
**/

class  ErrorDetectionCodeTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ErrorDetectionCodeTest);
    CPPUNIT_TEST(testErrorDetectionCode);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testErrorDetectionCode();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ErrorDetectionCodeTest );

//========================================================================
//
//    Tests.
//

void  ErrorDetectionCodeTest::testErrorDetectionCode()
{
    ErrorDetectionCode  testEDC;
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
