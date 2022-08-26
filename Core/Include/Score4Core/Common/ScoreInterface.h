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
**      @file       Common/ScoreInterface.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_SCORE_INTERFACE_H )
#    define   SCORE4CORE_COMMON_INCLUDED_SCORE_INTERFACE_H

#include    "Score4Types.h"

#include    <array>
#include    <string>
#include    <vector>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    Type Definitions.
//

typedef     std::array<GamesCount, FILTER_GAMES_END>
GameCountArray;

typedef     std::vector<GameCountArray>     GameCountTable;

typedef     std::vector<GamesCount>         GameCountList;

typedef     std::array<ScoreValue, FILTER_GAMES_END>
ScoreArray;

typedef     std::vector<ScoreArray>         ScoreTable;

typedef     std::array<GamesCount, FILTER_SCDL_END>
RestGamesArray;

typedef     std::vector<RestGamesArray>     RestGamesTable;

//----------------------------------------------------------------
/**
**    リーグ情報。
**/

struct  LeagueInfo
{
    /**   リーグ名。    **/
    std::string     leagueName;

    /**   プレーオフに進出できるチーム数。  **/
    TeamIndex       numPlayOff;

    LeagueInfo()
        : leagueName(), numPlayOff(0)
    { }
};

//----------------------------------------------------------------
/**
**    チーム情報。
**/

struct  TeamInfo
{
    LeagueIndex     leagueID;       /**<  所属リーグ。      **/
    std::string     teamName;       /**<  チーム名。        **/
    GameCountTable  gameCounts;     /**<  試合数のリスト。  **/

    TeamInfo()
        : leagueID(-1), teamName(), gameCounts()
    { }
};

//----------------------------------------------------------------
/**
**    ゲーム結果のレコード。
**/

struct  GameResult
{
    RecordFlag      eGameFlags;
    DateSerial      recordDate;
    TeamIndex       visitorTeam;
    TeamIndex       homeTeam;
    ScoreValue      visitorScore;
    ScoreValue      homeScore;
};

//----------------------------------------------------------------
/**
**    必要勝利数の情報をまとめる構造体。
**/

struct  NumWinsForBeat
{
    /**   必要勝利数が示している情報の種類。    **/
    MagicFilter     filterType;

    /**
    **    対象チームを上回るのに必要な勝利数。
    **/
    GamesCount      numNeedWins;

    /**
    **    残り試合数。ただし、マジックが点灯している時は、直接対決を除く。
    **/
    GamesCount      numRestGame;

    /**
    **    対象チームを自力で上回るのに必要な勝利数。
    **/
    GamesCount      numWinsSelf;

    /**
    **    対象チームを自力で上回る可能性ギリギリのラインとのゲーム差。
    **/
    GamesCount      numWinsDiff;
};

typedef     std::vector<NumWinsForBeat>     WinsForBeatList;

//----------------------------------------------------------------
/**
**    マジックまたは自力での優勝／プレーオフ進出の可能性。
**/

struct  MagicInfo
{
    /**   可能性のある最低順位。    **/
    TeamIndex       rankLow;

    /**   可能性のある最高順位。    **/
    TeamIndex       rankHigh;

    MagicInfoFlags  magicFlags [NUM_MAGIC_MODES];

    /**   マジック。                **/
    GamesCount      magicNumber[NUM_MAGIC_MODES];

    /**   可能性のある最低勝率。    **/
    WinningRate     wrateLow;

    /**   可能性のある最高勝率。    **/
    WinningRate     wrateHigh;
};

//----------------------------------------------------------------
/**
**    集計結果。
**/

struct  CountedScores
{
    /**   勝ち数。      **/
    GameCountArray  numWons;

    /**   負け数。      **/
    GameCountArray  numLost;

    /**   引分け。      **/
    GameCountArray  numDraw;

    /**   消化試合数。  **/
    RestGamesArray  numGames;

    /**   対チーム毎の勝ち数。  **/
    GameCountTable  vsWons;

    /**   対チーム毎の負け数。  **/
    GameCountTable  vsLost;

    /**   対チーム毎の引分け。  **/
    GameCountTable  vsDraw;

    /**   各チームとの残り試合数。      **/
    RestGamesTable  restGames;

    /**   所属リーグ内での残り試合数。  **/
    RestGamesArray  numLeagueRestGames;

    /**   交流戦の残り試合数。          **/
    RestGamesArray  numInterRestGames;

    /**
    **    リーグ内と交流戦を合わせた残り試合数。
    **/
    RestGamesArray  numTotalRestGames;

    /**   マジック関連の集計結果。  **/
    MagicInfo       totalMagic;

    /**   現在の順位。              **/
    TeamIndex       currentRank;

    /**
    **    必要勝利数等、マジック関連の補助計算データ。
    **/
    WinsForBeatList numWinsForBeat;

    /**   総得点。  **/
    ScoreArray      totalGotScores;

    /**   総失点。  **/
    ScoreArray      totalLostScores;

    /**  対チーム毎の得点。 **/
    ScoreTable      vsGotScores;

    /**  対チーム毎の失点。 **/
    ScoreTable      vsLostScores;

    CountedScores()
        : numWons(), numLost(), numDraw(),
          numGames(),
          vsWons(), vsLost(), vsDraw(),
          restGames(),
          numLeagueRestGames(), numInterRestGames(),
          numTotalRestGames(),
          totalMagic(),
          currentRank(),
          numWinsForBeat(),
          totalGotScores(), totalLostScores(),
          vsGotScores(), vsLostScores()
    { }
};

CONSTEXPR_VAR   GamesCount  MAGIC_NO_PROBABILITY_WONS   = 99999999;
CONSTEXPR_VAR   GamesCount  MAGICLIST_NO_DATA_ENTRY     = -1;

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
