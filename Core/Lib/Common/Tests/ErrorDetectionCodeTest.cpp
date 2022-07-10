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

private:
    typedef     ErrorDetectionCode::EDCode      EDCode;
};

CPPUNIT_TEST_SUITE_REGISTRATION( ErrorDetectionCodeTest );

//========================================================================
//
//    Tests.
//

void  ErrorDetectionCodeTest::testErrorDetectionCode()
{
    ErrorDetectionCode  testEDC;
    EDCode              valCRC;

    BtByte  buf1[] = { 1, 0, 0, 0, 0 };

    testEDC.setupGenPoly(0x04C11DB7);
    valCRC  =  testEDC.checkCRC32(buf1, sizeof(buf1));
    CPPUNIT_ASSERT_EQUAL( EDCode(0x04C11DB7), valCRC );

    BtByte  buf2[] = { 0x80, 1, 2, 3, 4, 0, 0, 0, 0 };

    testEDC.setupGenPoly(0x04C11DB7);
    valCRC  =  testEDC.checkCRC32(buf2, sizeof(buf2));
    CPPUNIT_ASSERT_EQUAL( EDCode(0xB3A7EC0A), valCRC );

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
