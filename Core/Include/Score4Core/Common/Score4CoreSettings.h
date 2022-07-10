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
**      プロジェクトの設定。
**
**      @file       Common/Score4CoreSettings.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_SCORE4_CORE_SETTINGS_H )
#    define   SCORE4CORE_COMMON_INCLUDED_SCORE4_CORE_SETTINGS_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#if defined( SCORE4_USE_PRE_CONFIGURED_MSVC )
#    include    "Score4Core/.Config/PreConfigScore4Core.msvc.h"
#else
#    include    "Score4Core/.Config/ConfiguredScore4Core.h"
#endif

SCORE4_CORE_NAMESPACE_BEGIN

SCORE4_CORE_NAMESPACE_END

#endif
