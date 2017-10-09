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
**      An Implementation of Test Case 'DateTimeFormat'.
**
**      @file       Common/Tests/DateTimeFormatTest.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Common/DateTimeFormat.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    DateTimeFormatTest  class.
//
/**
**    クラス DateTimeFormat の単体テスト。
**/

class  DateTimeFormatTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(DateTimeFormatTest);
    CPPUNIT_TEST(testDateTimeFormat);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testDateTimeFormat();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DateTimeFormatTest );

//========================================================================
//
//    Tests.
//

void  DateTimeFormatTest::testDateTimeFormat()
{
    DateTimeFormat  dtFormat;
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
