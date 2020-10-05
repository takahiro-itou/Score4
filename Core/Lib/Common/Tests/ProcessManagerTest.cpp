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
**      An Implementation of Test Case 'ProcessManager'.
**
**      @file       Common/Tests/ProcessManager.cpp
**/

#include    "TestDriver.h"
#include    "Score4Core/Common/ProcessManager.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ProcessManagerTest  class.
//
/**
**    クラス ProcessManager の単体テスト。
**/

class  ProcessManagerTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ProcessManagerTest);
    CPPUNIT_TEST(testProcessManager);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testProcessManager();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ProcessManagerTest );

//========================================================================
//
//    Tests.
//

void  ProcessManagerTest::testProcessManager()
{
    ProcessManager      testee;

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
