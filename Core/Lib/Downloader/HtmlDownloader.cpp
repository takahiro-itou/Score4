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
**      An Implementation of HtmlDownloader class.
**
**      @file       Downloader/HtmlDownloader.cpp
**/

#include    "Score4Core/Downloader/HtmlDownloader.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Downloader  {

namespace  {

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    HtmlDownloader  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

HtmlDownloader::HtmlDownloader()
    : m_lpCallback(nullptr)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

HtmlDownloader::~HtmlDownloader()
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

//----------------------------------------------------------------
//    指定したリソースをダウンロードする。
//

ErrCode
HtmlDownloader::downloadResource(
        const  char  *  strURI,
        LpWriteBuf      outBuf)  const
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    指定したリソースをダウンロードする。
//

ErrCode
HtmlDownloader::downloadResource(
        const  char  *  strURI,
        const  char  *  outPath)  const
{
    return ( ERR_FAILURE );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    コールバックを取得する。
//

const  HtmlDownloader::Callback  &
HtmlDownloader::getCallback()  const
{
    return ( *(this->m_lpCallback) );
}

//----------------------------------------------------------------
//    コールバックを設定する。
//

ErrCode
HtmlDownloader::setCallback(
        Callback  & callback)
{
    return ( ERR_FAILURE );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Downloader
SCORE4_CORE_NAMESPACE_END
