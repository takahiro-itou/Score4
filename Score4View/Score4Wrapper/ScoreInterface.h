﻿//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      Type Definitions.
**
**      @file       ScoreInterface.h
**/

#pragma     once

#include    "Score4Core/Common/ScoreDocument.h"

#include    "Score4Types.h"

namespace  Score4Wrapper  {
namespace  Common  {

//========================================================================
//
//    Type Definitions.
//

typedef     cli::array<GamesCount, 1>       GameCountArray;

typedef     cli::array<GamesCount, 2>       GameCountTable;

typedef     cli::array<GamesCount, 1>       GameCountList;

typedef     cli::array<ScoreValue, 1>       ScoreArray;

typedef     cli::array<ScoreValue, 2>       ScoreTable;

typedef     cli::array<GamesCount, 1>       RestGamesArray;

typedef     cli::array<GamesCount, 2>       RestGamesTable;

//----------------------------------------------------------------
/**
**    リーグ情報。
**/

public ref  class   LeagueInfo
{
public:

    /**   リーグ名。    **/
    property    System::String^     leagueName;

    /**   プレーオフに進出できるチーム数。  **/
    property    TeamIndex           numPlayOff;
};

//----------------------------------------------------------------
/**
**    チーム情報。
**/

public ref  class   TeamInfo
{
public:

    /**   所属リーグ。          **/
    property    LeagueIndex         leagueID;

    /**   チーム名。            **/
    property    System::String^     teamName;

    /**   試合数のリスト。      **/
    property    cli::array<GamesCount>^         gameCounts;
};

//----------------------------------------------------------------
/**
**    ゲーム結果のレコード。
**/

public ref  class   GameResult
{
public:

    property    RecordFlag      eGameFlags;
    property    DateSerial      recordDate;
    property    TeamIndex       visitorTeam;
    property    TeamIndex       homeTeam;
    property    ScoreValue      visitorScore;
    property    ScoreValue      homeScore;
};

//----------------------------------------------------------------
/**
**    マジックまたは自力での優勝／プレーオフ進出の可能性。
**/

public ref  class   MagicInfo
{
public:

    /**   可能性のある最低順位。    **/
    property    TeamIndex       rankLow;

    /**   可能性のある最高順位。    **/
    property    TeamIndex       rankHigh;

    cli::array<Boolean>^        bMagic;

    /**   マジック。                **/
    cli::array<GamesCount>^     magicNumber;
};

//----------------------------------------------------------------
/**
**    集計結果。
**/

public ref  class   CountedScores
{
public:

    /**   勝ち数。      **/
    property    GameCountArray^     numWons;

    /**   負け数。      **/
    property    GameCountArray^     numLost;

    /**   引分け。      **/
    property    GameCountArray^     numDraw;

    /**   消化試合数。  **/
    property    RestGamesArray^     numGames;

    /**   対チーム毎の勝ち数。  **/
    property    GameCountTable^     vsWons;

    /**   対チーム毎の負け数。  **/
    property    GameCountTable^     vsLost;

    /**   対チーム毎の引分け。  **/
    property    GameCountTable^     vsDraw;

    /**   各チームとの残り試合数。      **/
    property    RestGamesTable^     restGames;

    /**   所属リーグ内での残り試合数。  **/
    property    RestGamesArray^     numLeagueRestGames;

    /**   交流戦の残り試合数。          **/
    property    RestGamesArray^     numInterRestGames;

    /**
    **    リーグ内と交流戦を合わせた残り試合数。
    **/
    property    RestGamesArray^     numTotalRestGames;

    /**   マジック関連の集計結果。  **/
    property    MagicInfo^          totalMagic;

    /**   現在の順位。              **/
    property    TeamIndex           currentRank;

    property    GameCountList^      beatProbability;
    property    GameCountList^      vsMagic;
    property    GameCountList^      numWinsForMatch;
    property    GameCountList^      numRestForMatch;

    /**   総得点。  **/
    property    ScoreArray^         totalGotScores;

    /**   総失点。  **/
    property    ScoreArray^         totalLostScores;

    /**  対チーム毎の得点。 **/
    property    ScoreTable^         vsGotScores;

    /**  対チーム毎の失点。 **/
    property    ScoreTable^         vsLostScores;
};

//========================================================================
//
//    Support Functions.
//

//----------------------------------------------------------------
/**   アンマネージ型をマネージ型に変換する。
**
**/

template <typename T, size_t N>
cli::array<T, 1>^
copyToManageArray(
        const  std::array<T, N>  &  arySrc)
{
    cli::array<T, 1>^   aryDest = gcnew cli::array<T, 1>(N);
    for ( size_t i = 0; i < N; ++ i ) {
        aryDest[i]  = arySrc[i];
    }
    return ( aryDest );
}

template <typename T, size_t N>
cli::array<T, 2>^
copyToManageTable(
        const  std::vector< std::array<T, N> >  & tblSrc)
{
    const   size_t  num = tblSrc.size();

    cli::array<T, 2>^   tblDest
                = gcnew cli::array<T, 2>(num, N);
    for ( size_t i = 0; i < num; ++ i ) {
        for ( size_t j = 0; j < N; ++ j ) {
            tblDest[i, j]   = tblSrc[i][j];
        }
    }

    return ( tblDest );
}

//----------------------------------------------------------------
/**   アンマネージ型をマネージ型に変換する。
**
**/

ErrCode
copyToManageType(
        const  Score4Core::Common::CountedScores  & csSrc,
        Score4Wrapper::Common::CountedScores      ^ csTrg);

}   //  End of namespace  Common
}   //  End of namespace  Score4Wrapper
