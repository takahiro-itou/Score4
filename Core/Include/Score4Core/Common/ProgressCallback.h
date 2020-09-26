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
**      An Interface of ProgressCallback class.
**
**      @file       Common/ProgressCallback.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_PROGRESS_CALLBACK_H )
#    define   SCORE4CORE_COMMON_INCLUDED_PROGRESS_CALLBACK_H

#include    "Score4Types.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ProgressCallback  class.
//

class  ProgressCallback
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**
    **    コールバック関数のパラメータ型。
    **/
    struct  ProgParams
    {
        const  char  *  titleText;      /**<  タイトル文字列。  **/
        void  *         extPrams;       /**<  追加パラメータ。  **/
    };

    /**
    **    コールバック関数型。
    **
    **  @param [in] curVal    現在の値。
    **  @param [in] minVal    初期値。
    **  @param [in] maxVal    最大値。
    **  @param [in] extArgs   追加の引数。
    **  @retval     BOOL_TRUE  : 処理を継続する。
    **  @retval     BOOL_FALSE : 処理をキャンセルする。
    **/
    typedef     Boolean
    (* FnCallback)(
            const  int  curVal,
            const  int  minVal,
            const  int  maxVal,
            ProgParams  extArgs);

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
    ProgressCallback();

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] fnCallback    コールバック関数。
    **  @param [in] extParams     追加のパラメータ。

    **/
    ProgressCallback(
            FnCallback  fnCallback,
            void  *     extParams);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ProgressCallback();

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
public:

    //----------------------------------------------------------------
    /**   コールバック関数を呼び出す。
    **
    **  @param [in] curVal    現在の値。
    **  @param [in] minVal    初期値。
    **  @param [in] maxVal    最大値。
    **  @param [in] extArgs   追加の引数。
    **  @retval     BOOL_TRUE  : 処理を継続する。
    **  @retval     BOOL_FALSE : 処理をキャンセルする。
    **/
    inline  Boolean
    operator ()(
            const  int  curVal,
            const  int  minVal,
            const  int  maxVal,
            ProgParams  extArgs)  const
    {
        return ( BOOL_TRUE );
    }

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
    friend  class   ProgressCallbackTest;
};

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
