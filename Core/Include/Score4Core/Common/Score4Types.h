//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  The Score4 Core Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2022, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU General Public License (GPL) version 3,                 **
**          or (at your option) any later version.                      **
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

    FILTER_GAMES_FIRST  =  FILTER_HOME_GAMES,
    FILTER_GAMES_END    =  (FILTER_ALL_GAMES + 1),
    FILTER_SCDL_FIRST   =  FILTER_HOME_GAMES,
    FILTER_SCDL_END     =  (FILTER_SCDL_ALLS + 1)
};

//----------------------------------------------------------------
/**
**    マジック等の状態を示すフィルタフラグ。
**/

enum  MagicFilter
{
    /**   リーグが異なるので、データ無し。  **/
    MF_DIFFERENT_LEAGUE     = 0,

    /**
    **    マジックが点灯する。
    **
    **  すなわち直接対決は全敗しても、
    **  残りの試合に全勝すれば、対象チームを上回る。
    **/
    MF_ON_MAGIC             = 1,

    /**
    **    マジックは点灯しないが、直接対決は全敗しても、
    **  相手チームが、他のチームに負ければ良い。
    **
    **  すなわち、相手チームが負けるとマジックが点灯する。
    **/
    MF_MAGIC_IF_RIVAL_LOSE  = 2,

    /**
    **    マジックは点灯しないが、直接対決での全勝を含め、
    **  残りの試合に全勝すれば、対象チームを上回る。
    **/
    MF_BEAT_IF_WIN_DIRECT   = 3,

    /**
    **    他力本願。すなわち、残り試合に全勝しても、
    **  対象チームを上回ることができない。
    **  ただし、対象チームが他のチームに負ければ可能性がある。
    **/
    MF_CANNOT_BEAT_BY_SELF  = 4,

    /**
    **    すでに対象チームを上回ることができない。
    **
    **  すなわち、残り試合に全勝し、かつ、
    **  対象チームが全敗しても、対象チームを上回ることができない。
    **/
    MF_NEVER_BEAT           = 5
};

//----------------------------------------------------------------
/**
**    マジックの計算対象の種類を示す列挙型。
**/

enum  MagicNumberMode
{
    MAGIC_VICTORY   = 0,    /**<  優勝マジック。            **/
    MAGIC_PLAYOFF   = 1,    /**<  プレーオフ進出マジック。  **/

    NUM_MAGIC_MODES
};

enum  MagicInfoFlags
{
    /**   マジックが点灯していない。
    **
    **  代わりに、自力での可能性が残るギリギリのラインとの
    **  ゲーム差を表示する。
    **/
    MIF_WINS_DIFF   = 0,

    /**   マジックが点灯している。  **/
    MIF_ON_MAGIC    = 1
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
**    勝率を表す型。
**/

typedef     double              WinningRate;

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
**    桁数を表す型。
**/

typedef     int                 NumOfDigits;

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

SCORE4_CORE_NAMESPACE_END

#endif
