﻿//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
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
    CPPUNIT_TEST(testGetDateTimeFromSerial);
    CPPUNIT_TEST(testGetSerialFromDate);
    CPPUNIT_TEST(testGetSerialFromString);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testDateTimeFormat();

    void  testGetDateTimeFromSerial();
    void  testGetSerialFromDate();
    void  testGetSerialFromString();
    void  testToString();
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

void  DateTimeFormatTest::testGetDateTimeFromSerial()
{
    DateTimeFormat::TDateTime   dt;

    DateTimeFormat::getDateTimeFromSerial(  2,  &dt);
    CPPUNIT_ASSERT_EQUAL( 1900, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    1, dt.month  );
    CPPUNIT_ASSERT_EQUAL(    1, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial( 60,  &dt);
    CPPUNIT_ASSERT_EQUAL( 1900, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    2, dt.month  );
    CPPUNIT_ASSERT_EQUAL(   28, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial( 61,  &dt);
    CPPUNIT_ASSERT_EQUAL( 1900, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    3, dt.month  );
    CPPUNIT_ASSERT_EQUAL(    1, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42369,  &dt);
    CPPUNIT_ASSERT_EQUAL( 2015, dt.year   );
    CPPUNIT_ASSERT_EQUAL(   12, dt.month  );
    CPPUNIT_ASSERT_EQUAL(   31, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42370,  &dt);
    CPPUNIT_ASSERT_EQUAL( 2016, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    1, dt.month  );
    CPPUNIT_ASSERT_EQUAL(    1, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42400,  &dt);
    CPPUNIT_ASSERT_EQUAL( 2016, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    1, dt.month  );
    CPPUNIT_ASSERT_EQUAL(   31, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42428,  &dt);
    CPPUNIT_ASSERT_EQUAL( 2016, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    2, dt.month  );
    CPPUNIT_ASSERT_EQUAL(   28, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42429,  &dt);
    CPPUNIT_ASSERT_EQUAL( 2016, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    2, dt.month  );
    CPPUNIT_ASSERT_EQUAL(   29, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42430,  &dt);
    CPPUNIT_ASSERT_EQUAL( 2016, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    3, dt.month  );
    CPPUNIT_ASSERT_EQUAL(    1, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42454,  &dt);
    CPPUNIT_ASSERT_EQUAL( 2016, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    3, dt.month  );
    CPPUNIT_ASSERT_EQUAL(   25, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    0, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.0, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42454.5, &dt);
    CPPUNIT_ASSERT_EQUAL( 2016, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    3, dt.month  );
    CPPUNIT_ASSERT_EQUAL(   25, dt.day    );
    CPPUNIT_ASSERT_EQUAL(   12, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(    0, dt.minute );
    CPPUNIT_ASSERT_EQUAL(    0, dt.second );
    CPPUNIT_ASSERT_EQUAL(  0.5, dt.remsec );

    DateTimeFormat::getDateTimeFromSerial(42454.109375, &dt);
    CPPUNIT_ASSERT_EQUAL( 2016, dt.year   );
    CPPUNIT_ASSERT_EQUAL(    3, dt.month  );
    CPPUNIT_ASSERT_EQUAL(   25, dt.day    );
    CPPUNIT_ASSERT_EQUAL(    2, dt.hour   );
    CPPUNIT_ASSERT_EQUAL(   37, dt.minute );
    CPPUNIT_ASSERT_EQUAL(   30, dt.second );
    CPPUNIT_ASSERT_EQUAL( 0.109375, dt.remsec );
}

void  DateTimeFormatTest::testGetSerialFromDate()
{
    CPPUNIT_ASSERT_EQUAL(
            DateSerial(2),
            DateTimeFormat::getSerialFromDate(1900,  1,  1) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(60),
            DateTimeFormat::getSerialFromDate(1900,  2, 28) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(61),
            DateTimeFormat::getSerialFromDate(1900,  3,  1) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42369),
            DateTimeFormat::getSerialFromDate(2015, 12, 31) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42370),
            DateTimeFormat::getSerialFromDate(2016,  1,  1) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42400),
            DateTimeFormat::getSerialFromDate(2016,  1, 31) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42428),
            DateTimeFormat::getSerialFromDate(2016,  2, 28) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42429),
            DateTimeFormat::getSerialFromDate(2016,  2, 29) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42430),
            DateTimeFormat::getSerialFromDate(2016,  3,  1) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42454),
            DateTimeFormat::getSerialFromDate(2016,  3, 25) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42454.5),
            DateTimeFormat::getSerialFromDate(2016,  3, 25, 12, 0, 0) );

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42454.109375),
            DateTimeFormat::getSerialFromDate(2016,  3, 25, 2, 37, 30) );

    return;
}

void  DateTimeFormatTest::testGetSerialFromString()
{

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(2),
            DateTimeFormat::getSerialFromString("4000000000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(60),
            DateTimeFormat::getSerialFromString("404E000000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(61),
            DateTimeFormat::getSerialFromString("404E800000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42369),
            DateTimeFormat::getSerialFromString("40E4B02000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42370),
            DateTimeFormat::getSerialFromString("40E4B04000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42400),
            DateTimeFormat::getSerialFromString("40E4B40000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42428),
            DateTimeFormat::getSerialFromString("40E4B78000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42429),
            DateTimeFormat::getSerialFromString("40E4B7A000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42430),
            DateTimeFormat::getSerialFromString("40E4B7C000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42454),
            DateTimeFormat::getSerialFromString("40E4BAC000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42454.5),
            DateTimeFormat::getSerialFromString("40E4BAD000000000"));

    CPPUNIT_ASSERT_EQUAL(
            DateSerial(42454.109375),
            DateTimeFormat::getSerialFromString("40E4BAC380000000"));

    return;
}

void  DateTimeFormatTest::testToString()
{

    CPPUNIT_ASSERT_EQUAL(
            std::string("4000000000000000"),
            DateTimeFormat::toString(DateSerial(2)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("4000000000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(1900,  1,  1)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("404E000000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(1900,  2, 28)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("404E800000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(1900,  3,  1)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4B02000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(2015, 12, 31)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4B04000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(2016,  1,  1)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4B40000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(2016,  1, 31)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4B78000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(2016,  2, 28)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4B7A000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(2016,  2, 29)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4B7C000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(2016,  3,  1)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4BAC000000000"),
            DateTimeFormat::toString(
                    DateTimeFormat::getSerialFromDate(2016,  3, 25)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4BAD000000000"),
            DateTimeFormat::toString(
            DateTimeFormat::getSerialFromDate(2016,  3, 25, 12, 0, 0)) );

    CPPUNIT_ASSERT_EQUAL(
            std::string("40E4BAC380000000"),
            DateTimeFormat::toString(
            DateTimeFormat::getSerialFromDate(2016,  3, 25, 2, 37, 30)) );

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
