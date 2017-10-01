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
**      Type Definitions.
**
**      @file       Common/Score4Types.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_SCORE4_TYPES_H )
#    define   SCORE4CORE_COMMON_INCLUDED_SCORE4_TYPES_H

#include    "Score4CoreSettings.h"

#include    <stddef.h>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum  ErrCode
{

    /**   正常終了。    **/
    ERR_SUCCESS             = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    ERR_FAILURE             = 1,

    /**   ファイルオープンエラー。  **/
    ERR_FILE_OPEN_ERROR     = 2,

    /**   ファイル入出力エラー。    **/
    ERR_FILE_IO_ERROR       = 3
};

//----------------------------------------------------------------
/**
**    型安全なブール型。
**/

enum  Boolean
{
    BOOL_FALSE  =  0,       /**<  偽。  **/
    BOOL_TRUE   =  1        /**<  真。  **/
};

//----------------------------------------------------------------
/**
**    レコードフラグ。
**/

enum  RecordFlag
{
    GAME_EMPTY          =   0,      /**<  未使用のデータ領域。  **/
    GAME_SCHEDULE       =   1,      /**<  試合の予定のみ。      **/
    GAME_CANCEL         =   2,      /**<  中止。                **/
    GAME_RESULT         =   3,      /**<  試合結果。            **/

    /**
    **    勝敗をカウントするゲーム（レギュラーシーズン）。
    **/
    GAME_REGULAR        =   0,

    /**
    **    勝敗をカウントしないゲーム。
    **  オープン戦、オールスター、プレーオフなど。
    **/
    GAME_NOT_REGULAR    = 256
};

//----------------------------------------------------------------
/**
**    日付型。
**/

typedef     double          DateSerial;

//----------------------------------------------------------------
/**
**    チーム番号。
**/

typedef     int             TeamIndex;

//----------------------------------------------------------------
/**   リーグ番号。
**/

typedef     int             LeagueIndex;

//----------------------------------------------------------------
/**
**    ゲーム数、勝数、負数などを表す型。
**/

typedef     int             GamesCount;

//----------------------------------------------------------------
/**
**    スコア（点数）の型。
**/

typedef     int             ScoreValue;

//----------------------------------------------------------------
/**
**    ファイルの長さを表す型。
**/

typedef     size_t          FileLength;

//----------------------------------------------------------------
/**
**    読み取り専用バッファ。
**/

typedef     const  void  *      LpcReadBuf;

//----------------------------------------------------------------
/**
**    読み書き両用バッファ。
**/

typedef     void  *             LpWriteBuf;

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
