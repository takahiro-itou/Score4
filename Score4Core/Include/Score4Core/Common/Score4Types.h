//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  The Score4 Core Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
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
    ERR_FILE_IO_ERROR       = 3,

    /**   無効なインデックス指定。  **/
    ERR_INDEX_OUT_OF_RANGE  = 4
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
**    ゲームフィルタフラグ。
**/

enum  GameFilter
{
    FILTER_HOME_GAMES   =  0,
    FILTER_AWAY_GAMES   =  1,
    FILTER_ALL_GAMES    =  2,

    FILTER_SCHEDULE     =  4,
    FILTER_SCDL_HOMES   =  (FILTER_HOME_GAMES | FILTER_SCHEDULE),
    FILTER_SCDL_AWAYS   =  (FILTER_AWAY_GAMES | FILTER_SCHEDULE),
    FILTER_SCDL_ALLS    =  (FILTER_ALL_GAMES  | FILTER_SCHEDULE),

    FILTER_GAMES_FITST  =  FILTER_HOME_GAMES,
    FILTER_GAMES_END    =  (FILTER_ALL_GAMES + 1)
    FILTER_SCDL_FIRST   =  FILTER_HOME_GAMES,
    FILTER_SCDL_END     =  (FILTER_SCDL_ALLS + 1)
};

//----------------------------------------------------------------
/**
**    日付型。
**/

typedef     double              DateSerial;

//----------------------------------------------------------------
/**
**    チーム番号。
**/

typedef     int                 TeamIndex;

//----------------------------------------------------------------
/**   リーグ番号。
**/

typedef     int                 LeagueIndex;

//----------------------------------------------------------------
/**
**    ゲーム数、勝数、負数などを表す型。
**/

typedef     int                 GamesCount;

/**
**    ゲームレコードのインデックス。
**/
typedef     GamesCount          RecordIndex;

//----------------------------------------------------------------
/**
**    スコア（点数）の型。
**/

typedef     int                 ScoreValue;

//----------------------------------------------------------------
/**
**    ファイルの長さを表す型。
**/

typedef     size_t              FileLength;

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

//----------------------------------------------------------------
/**
**    バイト型。
**/

typedef     unsigned  char      BtByte;

/**
**    バイト型の読み取り専用バッファ。
**/
typedef     const  BtByte  *    LpcByte;

/**
**    バイト型の読み書き両用バッファ。
**/

typedef     BtByte  *           LpByte;

//========================================================================
//
//    安全なポインタ型のキャスト。
//

template  <typename  T>
T  pointer_cast(void  *  p)
{
    return ( static_cast<T>(p) );
}

template  <typename  T>
T  pointer_cast(const  void  *  p)
{
    return ( static_cast<T>(p) );
}

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
