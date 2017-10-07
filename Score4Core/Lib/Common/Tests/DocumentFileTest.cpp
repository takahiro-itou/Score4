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
**      An Implementation of Test Case 'DocumentFile'.
**
**      @file       Common/Tests/DocumentFileTest.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Common/DocumentFile.h"

#include    <fstream>
#include    <sstream>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    DocumentFileTest  class.
//
/**
**    クラス DocumentFile の単体テスト。
**/

class  DocumentFileTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(DocumentFileTest);
    CPPUNIT_TEST(testDocumentFile);
    CPPUNIT_TEST(testReadFromBinaryBuffer);
    CPPUNIT_TEST(testReadFromTextStream);
    CPPUNIT_TEST(testSaveToBinaryBuffer);
    CPPUNIT_TEST(testSaveToTextStream);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testDocumentFile();

    void  testReadFromBinaryBuffer();
    void  testReadFromTextStream();
    void  testSaveToBinaryBuffer();
    void  testSaveToTextStream();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DocumentFileTest );

//========================================================================
//
//    Tests.
//

void  DocumentFileTest::testDocumentFile()
{
    DocumentFile    docFile;
    return;
}

void  DocumentFileTest::testReadFromBinaryBuffer()
{
    DocumentFile    docFile;
    return;
}

void  DocumentFileTest::testReadFromTextStream()
{
    DocumentFile    docFile;

    std::ifstream   ifs;
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            docFile.readFromTextStream(ifs)
    );

    return;
}

void  DocumentFileTest::testSaveToBinaryBuffer()
{
    DocumentFile    docFile;
    return;
}

void  DocumentFileTest::testSaveToTextStream()
{
    DocumentFile    docFile;

    std::stringstream   ss;
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            docFile.saveToTextStream(ss)
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
