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
    CPPUNIT_TEST(testProgressCallback1);
    CPPUNIT_TEST(testProgressCallback2);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testProgressCallback1();
    void  testProgressCallback2();

private:
    enum  {
        BUFFER_SIZE = 1024
    };

    typedef     ProgressCallback::FnCallback    FnCallback;
    typedef     ProgressCallback::ProgParams    ProgParams;

    static  Boolean
    callbackSampleProgress(
            const  int  curVal,
            const  int  minVal,
            const  int  maxVal,
            ProgParams  extArgs);

};

CPPUNIT_TEST_SUITE_REGISTRATION( ProgressCallbackTest );

//========================================================================
//
//    Tests.
//

void  ProgressCallbackTest::testProgressCallback1()
{
    char    buf[BUFFER_SIZE];
    ProgressCallback    cbProgress(&callbackSampleProgress, buf);
    ProgParams          extParams;

    CPPUNIT_ASSERT_EQUAL(
            &callbackSampleProgress,
            cbProgress.getCallbackFunction() );
    CPPUNIT_ASSERT_EQUAL(
            static_cast<void *>(buf),
            cbProgress.getCallbackParameter() );

    extParams.titleText = "description";

    buf[0]  = '\0';
    CPPUNIT_ASSERT_EQUAL(
            BOOL_TRUE,
            cbProgress(1, 0, 100, extParams));
    CPPUNIT_ASSERT_EQUAL(
            std::string("description: 1/100"),
            std::string(buf));

    buf[0]  = '\0';
    CPPUNIT_ASSERT_EQUAL(
            BOOL_TRUE,
            cbProgress(10, 1, 100, extParams));
    CPPUNIT_ASSERT_EQUAL(
            std::string("description: 9/99"),
            std::string(buf));

    return;
}

void  ProgressCallbackTest::testProgressCallback2()
{
    char    buf[BUFFER_SIZE];
    ProgressCallback    cbProgress;
    ProgParams          extParams;

    CPPUNIT_ASSERT_EQUAL(
            static_cast<FnCallback>(nullptr),
            cbProgress.getCallbackFunction() );
    CPPUNIT_ASSERT_EQUAL(
            static_cast<void *>(nullptr),
            cbProgress.getCallbackParameter() );

    cbProgress.setCallbackFunction(&callbackSampleProgress);
    cbProgress.setCallbackParameter(buf);

    extParams.titleText = "description";

    buf[0]  = '\0';
    CPPUNIT_ASSERT_EQUAL(
            BOOL_TRUE,
            cbProgress(1, 0, 100, extParams));
    CPPUNIT_ASSERT_EQUAL(
            std::string("description: 1/100"),
            std::string(buf));

    buf[0]  = '\0';
    CPPUNIT_ASSERT_EQUAL(
            BOOL_TRUE,
            cbProgress(10, 1, 100, extParams));
    CPPUNIT_ASSERT_EQUAL(
            std::string("description: 9/99"),
            std::string(buf));

    CPPUNIT_ASSERT_EQUAL(
            &callbackSampleProgress,
            cbProgress.getCallbackFunction() );
    CPPUNIT_ASSERT_EQUAL(
            static_cast<void *>(buf),
            cbProgress.getCallbackParameter() );

    return;
}

Boolean
ProgressCallbackTest::callbackSampleProgress(
        const  int  curVal,
        const  int  minVal,
        const  int  maxVal,
        ProgParams  extArgs)
{
    char *  const   buf = static_cast<char *>(extArgs.extParams);
    snprintf(
            buf, BUFFER_SIZE,
            "%s: %d/%d",
            (extArgs.titleText),
            (curVal - minVal),
            (maxVal - minVal)
    );

    return ( BOOL_TRUE );
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
