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
**      スクリプトによる設定値が書き込まれるヘッダファイル。
**
**      @file       .Config/ConfiguredScore4Core.h.in
**/

#if !defined( SCORE4CORE_CONFIG_INCLUDED_CONFIGURED_SCORE4_CORE_H )
#    define   SCORE4CORE_CONFIG_INCLUDED_CONFIGURED_SCORE4_CORE_H

//========================================================================
//
//    Name Space.
//

/**
**    スクリプトによって設定された名前空間。
**/

#define     SCORE4_CORE_CNF_NS              Score4Core

/**
**    名前空間。
**/

#define     SCORE4_CORE_NAMESPACE           SCORE4_CORE_CNF_NS

#define     SCORE4_CORE_NAMESPACE_BEGIN     namespace  SCORE4_CORE_CNF_NS  {

#define     SCORE4_CORE_NAMESPACE_END       }


//========================================================================
//
//    Compiler Features.
//

//
//    キーワード constexpr  の検査。
//

#if ( 0 )
#    define     SCORE4_CORE_ENABLE_CONSTEXPR        1
#else
#    undef      SCORE4_CORE_ENABLE_CONSTEXPR
#endif

#if !defined( CONSTEXPR_VAR ) && !defined( CONSTEXPR_FUNC )
#    if ( SCORE4_CORE_ENABLE_CONSTEXPR )
#        define     CONSTEXPR_VAR       constexpr
#        define     CONSTEXPR_FUNC      constexpr
#    else
#        define     CONSTEXPR_VAR       const
#        define     CONSTEXPR_FUNC
#    endif
#endif

//
//    キーワード nullptr  の検査。
//

#if ( 1 )
#    define     SCORE4_CORE_ENABLE_NULLPTR          1
#else
#    if !defined( nullptr )
#        define     nullptr     NULL
#    endif
#    undef      SCORE4_CORE_ENABLE_NULLPTR
#endif

//
//    キーワード override の検査。
//

#if ( 1 )
#    define     SCORE4_CORE_ENABLE_OVERRIDE         1
#else
#    if !defined( override )
#        define     override
#    endif
#    undef      SCORE4_CORE_ENABLE_OVERRIDE
#endif

#endif
