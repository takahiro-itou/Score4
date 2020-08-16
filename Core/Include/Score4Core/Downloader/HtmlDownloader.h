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
**      An Interface of HtmlDownloader class.
**
**      @file       Downloader/HtmlDownloader.h
**/

#if !defined( SCORE4CORE_DOWNLOADER_INCLUDED_HTML_DOWNLOADER_H )
#    define   SCORE4CORE_DOWNLOADER_INCLUDED_HTML_DOWNLOADER_H

#include    "Score4Core/Common/Score4Types.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Downloader  {

//========================================================================
//
//    HtmlDownloader  class.
//

class  HtmlDownloader
{

//========================================================================
//
//    Internal Type Definitions.
//

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
    HtmlDownloader();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~HtmlDownloader();

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
    friend  class   HtmlDownloaderTest;
};

}   //  End of namespace  Downloader
SCORE4_CORE_NAMESPACE_END

#endif
