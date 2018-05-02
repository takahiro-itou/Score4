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
**      @file       Common/ScoreInterface.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_SCORE_INTERFACE_H )
#    define   SCORE4CORE_COMMON_INCLUDED_SCORE_INTERFACE_H

#include    "Score4Types.h"

#include    <array>
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

typedef     std::array<ScoreValue, FILTER_GAMES_END>
ScoreArray;

typedef     std::vector<ScoreArray>         ScoreTable;

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

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
