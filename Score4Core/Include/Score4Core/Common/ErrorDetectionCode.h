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
**      An Interface of ErrorDetectionCode class.
**
**      @file       Common/ErrorDetectionCode.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_ERROR_DETECTION_CODE_H )
#    define   SCORE4CORE_COMMON_INCLUDED_ERROR_DETECTION_CODE_H

#include    "Score4Types.h"

#include    <iosfwd>
#include    <string>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //
class   ScoreDocument;

//========================================================================
//
//    ErrorDetectionCode  class.
//

class  ErrorDetectionCode
{

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    ErrorDetectionCode();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ErrorDetectionCode();

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ErrorDetectionCodeTest;
};

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
