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
**      An Implementation of ScoreDocument class.
**
**      @file       Common/ScoreDocument.cpp
**/

#include    "Score4Core/Common/ScoreDocument.h"

#include    <fcntl.h>
#include    <memory.h>
#include    <stdio.h>
#include    <sys/stat.h>
#include    <unistd.h>
#include    <vector>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ScoreDocument  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ScoreDocument::ScoreDocument()
    : m_leagueInfos(),
      m_teamInfos  ()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ScoreDocument::~ScoreDocument()
{
}

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

//----------------------------------------------------------------
//    リーグ情報を追加登録する。
//

ErrCode
ScoreDocument::appendLeagueInfo(
        const   LeagueInfo  &leagueInfo)
{
    this->m_leagueInfos.push_back(leagueInfo);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    チーム情報を追加登録する。
//

ErrCode
ScoreDocument::appendTeamInfo(
        const   TeamInfo    &teamInfo)
{
    this->m_teamInfos.push_back(teamInfo);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    チーム情報を追加登録する。
//

ErrCode
ScoreDocument::appendTeamInfo(
        const  std::string  &teamName,
        const  LeagueIndex  leagueID)
{
    TeamInfo    tmpInfo;

    tmpInfo.leagueID    = leagueID;
    tmpInfo.teamName    = teamName;

    this->m_teamInfos.push_back(tmpInfo);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ドキュメントの内容をクリアする。
//

ErrCode
ScoreDocument::clearDocument()
{
    this->m_teamInfos.clear();
    this->m_leagueInfos.clear();

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    対戦試合数用の領域を確保し初期化する。
//

ErrCode
ScoreDocument::initializeGameCountTable()
{
    const   TeamIndex  numTeam  = getNumTeams();
    for ( TeamIndex i = 0; i < numTeam; ++ i ) {
        GameCountTable  & tblCount  = this->m_teamInfos.at(i).gameCounts;
        tblCount.resize(numTeam);
        for ( TeamIndex j = 0; j < numTeam; ++ j ) {
            tblCount.at(j) [FILTER_HOME_GAMES]  = 0;
            tblCount.at(j) [FILTER_AWAY_GAMES]  = 0;
            tblCount.at(j) [FILTER_ALL_GAMES ]  = 0;
        }
    }
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    チーム情報用の領域を確保する。
//

ErrCode
ScoreDocument::resizeTeamInfos(
        const   TeamIndex   numTeam)
{
    this->m_teamInfos.resize(numTeam);
    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    対戦カード毎の試合数を取得する。
//

GamesCount
ScoreDocument::getGameCount(
        const   TeamIndex   srcTeam,
        const   TeamIndex   trgTeam,
        const   GameFilter  flagGame)  const
{
    const   GameCountTable
        & tblCount  =  this->m_teamInfos.at(srcTeam).gameCounts;
    return ( tblCount.at(trgTeam)[flagGame] );
}

//----------------------------------------------------------------
//    対戦カード毎の試合数を取得する。
//

GamesCount
ScoreDocument::getGameCount(
        const   TeamIndex   homeTeam,
        const   TeamIndex   visitorTeam)  const
{
    return ( getGameCount(homeTeam, visitorTeam, FILTER_HOME_GAMES) );
}

//----------------------------------------------------------------
//    対戦カード毎の試合数を設定する。
//

ErrCode
ScoreDocument::setGameCount(
        const   TeamIndex   homeTeam,
        const   TeamIndex   visitorTeam,
        const   GamesCount  gameCount)
{
    setGameCount(homeTeam, visitorTeam, FILTER_HOME_GAMES,  gameCount);
    setGameCount(visitorTeam, homeTeam, FILTER_AWAY_GAMES,  gameCount);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ゲームレコードを取得する。
//

const   ScoreDocument::GameResult  &
ScoreDocument::getGameRecord(
        const  RecordIndex  idxRecord)  const
{
    return ( this->m_gameResults.at(idxRecord) );
}

//----------------------------------------------------------------
//    登録されているリーグの情報を取得する。
//

const   ScoreDocument::LeagueInfo  &
ScoreDocument::getLeagueInfo(
        const  LeagueIndex  idxLeague)  const
{
    return ( this->m_leagueInfos.at(idxLeague) );
}

//----------------------------------------------------------------
//    登録されているリーグの情報を更新する。
//

ErrCode
ScoreDocument::setLeagueInfo(
        const  LeagueIndex  idxLeague,
        const  LeagueInfo   &leagueInfo)
{
    if ( (idxLeague < 0) || (getNumLeagues() <= idxLeague) )
    {
        return ( ERR_INDEX_OUT_OF_RANGE );
    }
    this->m_leagueInfos.at(idxLeague)   = leagueInfo;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    登録されているリーグ数を取得する。
//

LeagueIndex
ScoreDocument::getNumLeagues()  const
{
    return ( this->m_leagueInfos.size() );
}

//----------------------------------------------------------------
//    記録されているゲームレコード数を取得する。
//

RecordIndex
ScoreDocument::getNumRecords()  const
{
    return ( this->m_gameResults.size() );
}

//----------------------------------------------------------------
//    登録されているチーム数を取得する。
//

TeamIndex
ScoreDocument::getNumTeams()  const
{
    return ( this->m_teamInfos.size() );
}

//----------------------------------------------------------------
//    登録されているチームの情報を取得する。
//

const   ScoreDocument::TeamInfo  &
ScoreDocument::getTeamInfo(
        const   TeamIndex   idxTeam)  const
{
    return ( this->m_teamInfos.at(idxTeam) );
}

//----------------------------------------------------------------
//    登録されているチームの情報を更新する。
//

ErrCode
ScoreDocument::setTeamInfo(
        const   TeamIndex   idxTeam,
        const   TeamInfo    &teamInfo)
{
    if ( (idxTeam < 0) || (getNumTeams() <= idxTeam) ) {
        return ( ERR_INDEX_OUT_OF_RANGE );
    }
    this->m_teamInfos.at(idxTeam)   =  teamInfo;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    登録されているチームの情報を更新する。
//

ErrCode
ScoreDocument::setTeamInfo(
        const  TeamIndex    idxTeam,
        const  std::string  &teamName,
        const  LeagueIndex  leagueID)
{
    if ( (idxTeam < 0) || (getNumTeams() <= idxTeam) ) {
        return ( ERR_INDEX_OUT_OF_RANGE );
    }

    TeamInfo  &  rdestInfo  =  this->m_teamInfos.at(idxTeam);

    rdestInfo.leagueID  = leagueID;
    rdestInfo.teamName  = teamName;

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    対戦カード毎の試合数を設定する。
//

ErrCode
ScoreDocument::setGameCount(
        const   TeamIndex   srcTeam,
        const   TeamIndex   trgTeam,
        const   GameFilter  flagGame,
        const   GamesCount  gameCount)
{
    if ( (srcTeam < 0) || (getNumTeams() <= srcTeam)
            || (trgTeam < 0) || (getNumTeams() <= trgTeam) )
    {
        return ( ERR_INDEX_OUT_OF_RANGE );
    }

    GameCountTable  & tblCount  =  this->m_teamInfos.at(srcTeam).gameCounts;

    tblCount.at(trgTeam)[flagGame]  = gameCount;

    tblCount.at(trgTeam) [FILTER_ALL_GAMES]
            =  tblCount.at(trgTeam) [FILTER_HOME_GAMES]
            +  tblCount.at(trgTeam) [FILTER_AWAY_GAMES];

    return ( ERR_SUCCESS );
}

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
