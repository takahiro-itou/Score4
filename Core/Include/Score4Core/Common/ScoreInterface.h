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
**    マジックまたは自力での優勝／プレーオフ進出の可能性。
**/

struct  MagicInfo
{
    /**   可能性のある最低順位。    **/
    TeamIndex       rankLow;

    /**   可能性のある最高順位。    **/
    TeamIndex       rankHigh;

    Boolean         bMagic[2];

    /**   マジック。                **/
    GamesCount      magicNumber[2];
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

    GameCountList   beatProbability;
    GameCountList   vsMagic;
    GameCountList   numWinsForMatch;
    GameCountList   numRestForMatch;

    /**   総得点。  **/
    ScoreArray      totalGotScores;

    /**   総失点。  **/
    ScoreArray      totalLostScores;

    /**  対チーム毎の得点。 **/
    ScoreTable      vsGotScores;

    /**  対チーム毎の失点。 **/
    ScoreTable      vsLostScores;
};

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
