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
**      An Implementation of ProgressCallback class.
**
**      @file       Common/ProgressCallback.cpp
**/

#include    "Score4Core/Common/ProgressCallback.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ProgressCallback  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ProgressCallback::ProgressCallback()
{
}

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

ProgressCallback::ProgressCallback(
        FnCallback  fnCallback,
        void  *     extParams)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ProgressCallback::~ProgressCallback()
{
}

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
//    Accessors.
//

//----------------------------------------------------------------
//    現在のコールバック関数を取得する。
//

ProgressCallback::FnCallback
ProgressCallback::getCallbackFunction()  const
{
}

//----------------------------------------------------------------
//    コールバック関数を設定する。
//

ErrCode
ProgressCallback::setCallbackFunction(
        FnCallback  fnCallback)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    コールバック関数に渡す追加パラメータを取得する。
//

void  *
ProgressCallback::getCallbackParameter()  const
{
}

//----------------------------------------------------------------
//    コールバック関数に渡す追加パラメータを設定する。
//

ErrCode
ProgressCallback::setCallbackParameter(
        void  *     extParams)
{
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
