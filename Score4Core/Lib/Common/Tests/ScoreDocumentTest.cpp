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
**      An Implementation of Test Case 'ScoreDocument'.
**
**      @file       Common/Tests/ScoreDocumentTest.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Common/ScoreDocument.h"

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
    CPPUNIT_TEST(testReadFromBinaryBuffer);
    CPPUNIT_TEST(testReadFromTextStream);
    CPPUNIT_TEST(testSaveToBinaryBuffer);
    CPPUNIT_TEST(testSaveToTextStream);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testScoreDocument();

    void  testReadFromBinaryBuffer();
    void  testReadFromTextStream();
    void  testSaveToBinaryBuffer();
    void  testSaveToTextStream();
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

void  ScoreDocumentTest::testReadFromBinaryBuffer()
{
    ScoreDocument   sd;
    return;
}

void  ScoreDocumentTest::testReadFromTextStream()
{
    ScoreDocument   sd;

    std::ifstream   ifs;
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            sd.readFromTextStream(ifs)
    );

    return;
}

void  ScoreDocumentTest::testSaveToBinaryBuffer()
{
    ScoreDocument   sd;
    return;
}

void  ScoreDocumentTest::testSaveToTextStream()
{
    ScoreDocument   sd;

    std::stringstream   ss;
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            sd.saveToTextStream(ss)
    );

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
