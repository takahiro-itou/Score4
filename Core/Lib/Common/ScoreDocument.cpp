﻿//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  The Score4 Core Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of ScoreDocument class.
**
**      @file       Common/ScoreDocument.cpp
**/

#include    "Score4Core/Common/ScoreDocument.h"

#include    <memory.h>
#include    <stdio.h>
#include    <vector>


SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

inline  void
aggregateGotLostScoreValues(
        const   TeamIndex   idxEnemy,
        const   ScoreValue  svGot,
        const   ScoreValue  svLost,
        const   GameFilter  gType,
        CountedScores     & trgCS)
{
    trgCS.vsGotScores .at(idxEnemy)[gType]  += svGot;
    trgCS.vsLostScores.at(idxEnemy)[gType]  += svLost;
}

template <int SCDL, typename T, size_t N>
inline  void
aggregateHomeAway(
        std::array<T, N>    & w)
{
    w[FILTER_ALL_GAMES | SCDL]
            = w[FILTER_HOME_GAMES | SCDL]
            + w[FILTER_AWAY_GAMES | SCDL];
}

inline  void
aggregateRestGames(
        const   RestGamesArray  & src,
        RestGamesArray          & trg)
{
    trg[FILTER_HOME_GAMES]  += src[FILTER_HOME_GAMES];
    trg[FILTER_AWAY_GAMES]  += src[FILTER_AWAY_GAMES];
    trg[FILTER_ALL_GAMES]   += src[FILTER_ALL_GAMES];

    trg[FILTER_SCDL_HOMES]  += src[FILTER_SCDL_HOMES];
    trg[FILTER_SCDL_AWAYS]  += src[FILTER_SCDL_AWAYS];
    trg[FILTER_SCDL_ALLS]   += src[FILTER_SCDL_ALLS];
}

}   //  End of (Unnamed) namespace.

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
      m_teamInfos  (),
      m_gameResults(),
      m_fOptimized (BOOL_FALSE),
      m_lastActiveDate(0),
      m_lastRecordDate(0),
      m_lastImportDate(0)
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
//    ゲームレコードを追加登録する。
//

ErrCode
ScoreDocument::appendGameRecord(
        const   GameResult  &gameRecord)
{
    this->m_gameResults.push_back(gameRecord);
    return ( ERR_SUCCESS );
}

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
    this->m_gameResults.clear();

    this->m_fOptimized      = BOOL_FALSE;
    this->m_lastActiveDate  = 0;
    this->m_lastRecordDate  = 0;
    this->m_lastImportDate  = 0;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    集計済みの成績表から順位を計算する。
//

TeamIndex
ScoreDocument::computeCurrentRank(
        const  LeagueIndex  idxLeague,
        CountedScoreList    &csData)  const
{
    const   TeamIndex   numTeam = getNumTeams();

    std::vector<TeamIndex>  bufTeam(numTeam, -1);
    std::vector<double>     bufPerc(numTeam, 0.0);

    TeamIndex   cntIns  = 0;

    for ( TeamIndex i = 0; i < numTeam; ++ i ) {
        if ( getTeamInfo(i).leagueID != idxLeague ) {
            continue;       //  違うリーグなので無視。  //
        }

        CountedScores  & csTrg  = csData.at(i);

        //  現在の勝率を計算する。  //
        const   GamesCount  numGame
            = csTrg.numGames[FILTER_ALL_GAMES]
            - csTrg.numDraw [FILTER_ALL_GAMES];
        const   double  teamPercent = (numGame == 0)
            ? 0.5
            : (csTrg.numWons[FILTER_ALL_GAMES] * 1.0 / numGame);

        //  どの位置に入るか決定する。  //
        TeamIndex   idxIns  = 0;
        for ( ; idxIns < cntIns; ++ idxIns ) {
            if ( bufTeam[idxIns] == -1 ) {
                break;
            }
            if ( bufPerc[idxIns] < teamPercent ) {
                break;
            }
        }   //  End For (idxIns)

        //  勝率リストにデータを挿入する。  //
        for ( TeamIndex j = cntIns; j > idxIns; -- j ) {
            bufTeam[j]  = bufTeam[j - 1];
            bufPerc[j]  = bufPerc[j - 1];
        }
        bufTeam[idxIns] = i;
        bufPerc[idxIns] = teamPercent;
        ++  cntIns;
    }   //  End For (i)

    //  同率タイに注意して順位を書き込む。  //
    double      prvPercent  = 2.0;
    TeamIndex   prvRank     = 0;
    for ( TeamIndex i = 0; i < cntIns; ++ i ) {
        const   TeamIndex   idxTeam = bufTeam[i];
        if ( idxTeam < 0 ) { continue; }
        if ( bufPerc[i] == prvPercent ) {
            csData.at(idxTeam).currentRank  = prvRank;
        } else {
            prvRank     = i + 1;
            csData.at(idxTeam).currentRank  = prvRank;
            prvPercent  = bufPerc[i];
        }
    }

    return ( cntIns );
}

//----------------------------------------------------------------
//    指定したリーグに属するチームを、成績順にソートする。
//

TeamIndex
ScoreDocument::computeRankOrder(
        const  CountedScoreList &csData,
        const  LeagueIndex      idxLeague,
        std::vector<TeamIndex>  &bufIndex)  const
{
    const   TeamIndex   numTeam = getNumTeams();

    bufIndex.clear();
    bufIndex.resize(numTeam, -1);

    TeamIndex   cntTeam = 0;
    for ( TeamIndex i = 0; i < numTeam; ++ i ) {
        if ( getTeamInfo(i).leagueID != idxLeague ) {
            continue;       //  違うリーグなので無視。  //
        }
        TeamIndex  curRank  = csData.at(i).currentRank;
        if ( curRank <= 0 ) {
            curRank = 1;
        }

        //  挿入ソート。    //
        TeamIndex   idxIns  = 0;
        for ( ; idxIns < numTeam; ++ idxIns ) {
            TeamIndex   trgTeam = bufIndex[idxIns];
            if ( trgTeam == -1 ) {
                break;
            }
            if ( curRank < csData.at(trgTeam).currentRank ) {
                for ( TeamIndex j = cntTeam; j > idxIns; -- j ) {
                    bufIndex[j] = bufIndex[j - 1];
                }
                break;
            }
        }   //  End For (idxIns)
        bufIndex[idxIns]    = i;
        ++  cntTeam;
    }   //  End For (i)

    //  別のリーグに所属するチームも配列の末尾に格納しておく。  //
    TeamIndex   idxIns  = cntTeam;
    for ( TeamIndex i = 0; i < numTeam; ++ i ) {
        if ( getTeamInfo(i).leagueID != idxLeague ) {
            bufIndex[idxIns]    = i;
            ++  idxIns;
        }
    }

    return ( cntTeam );
}

//----------------------------------------------------------------
//    試合結果を集計する。
//

ErrCode
ScoreDocument::countScores(
        const   DateSerial  trgLastDate,
        CountedScoreList    &bufCounted)  const
{
    typedef     GameResultList::const_iterator  GR_Iter;

    clearCountedScoresList(bufCounted);

    //  レコードの内容を集計する。  //
    const  GR_Iter  itEndG  = this->m_gameResults.end();
    for ( GR_Iter itG = m_gameResults.begin(); itG != itEndG; ++ itG )
    {
        const  GameResult  &src = (* itG);
        if ( (trgLastDate > 0) && (src.recordDate > trgLastDate) ) {
            continue;
        }

        const   TeamIndex   idxHome = src.homeTeam;
        const   TeamIndex   idxAway = src.visitorTeam;

        CountedScores     & csHome  = bufCounted.at(idxHome);
        CountedScores     & csAway  = bufCounted.at(idxAway);

        if ( src.eGameFlags == GAME_RESULT ) {
            //  得点と失点を加算する。  //
            aggregateGotLostScoreValues(
                    idxAway, src.homeScore, src.visitorScore,
                    FILTER_HOME_GAMES,  csHome);
            aggregateGotLostScoreValues(
                    idxHome, src.visitorScore, src.homeScore,
                    FILTER_AWAY_GAMES,  csAway);

            //  得点を比較して勝敗を記録する。  //
            if ( src.homeScore < src.visitorScore ) {
                ++  csHome.vsLost.at(idxAway)[FILTER_HOME_GAMES];
                ++  csAway.vsWons.at(idxHome)[FILTER_AWAY_GAMES];
            } else if ( src.homeScore > src.visitorScore ) {
                ++  csHome.vsWons.at(idxAway)[FILTER_HOME_GAMES];
                ++  csAway.vsLost.at(idxHome)[FILTER_AWAY_GAMES];
            } else {
                ++  csHome.vsDraw.at(idxAway)[FILTER_HOME_GAMES];
                ++  csAway.vsDraw.at(idxHome)[FILTER_AWAY_GAMES];
            }

            //  試合数を引く。  //
            --  csHome.restGames.at(idxAway)[FILTER_HOME_GAMES];
            --  csHome.restGames   [idxAway][FILTER_SCDL_HOMES];
            --  csAway.restGames.at(idxHome)[FILTER_AWAY_GAMES];
            --  csAway.restGames   [idxHome][FILTER_SCDL_AWAYS];
        } else if ( src.eGameFlags == GAME_SCHEDULE ) {
            //  スケジュール上のデータを集計する。  //
            --  csHome.restGames.at(idxAway)[FILTER_SCDL_HOMES];
            --  csAway.restGames.at(idxHome)[FILTER_SCDL_AWAYS];
        }
    }

    //  対チーム毎に集計した結果から、合計を計算する。  //
    const   TeamIndex   numTeam = getNumTeams();
    for ( TeamIndex idxTeam = 0; idxTeam < numTeam; ++ idxTeam ) {
        countTotalScores(
                getTeamInfo(idxTeam).leagueID,
                bufCounted.at(idxTeam));
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    チーム情報を検索する。
//

TeamIndex
ScoreDocument::findTeamInfo(
        const  std::string  &teamName)  const
{
    const   TeamIndex  numTeam  = getNumTeams();
    for ( TeamIndex i = 0; i < numTeam; ++ i ) {
        if ( this->m_teamInfos.at(i).teamName == teamName ) {
            return ( i );
        }
    }

    return ( -1 );
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
//    最終試合日付を取得する。
//

DateSerial
ScoreDocument::getLastActiveDate()  const
{
    return ( this->m_lastActiveDate );
}

//----------------------------------------------------------------
//    最終試合日付を設定する。
//

ErrCode
ScoreDocument::setLastActiveDate(
        const   DateSerial  dsVal)
{
    this->m_lastActiveDate  =  dsVal;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    最終インポート日時を取得する。
//

DateSerial
ScoreDocument::getLastImportDate()  const
{
    return ( this->m_lastImportDate );
}

//----------------------------------------------------------------
//    最終インポート日時を設定する。
//

ErrCode
ScoreDocument::setLastImportDate(
        const   DateSerial  dsVal)
{
    this->m_lastImportDate  =  dsVal;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    最終レコード日付を取得する。
//

DateSerial
ScoreDocument::getLastRecordDate()  const
{
    return ( this->m_lastRecordDate );
}

//----------------------------------------------------------------
//    最終レコード日付を設定する。
//

ErrCode
ScoreDocument::setLastRecordDate(
        const   DateSerial  dsVal)
{
    this->m_lastRecordDate  =  dsVal;
    return ( ERR_SUCCESS );
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
//    最適化済みフラグを取得する。
//

Boolean
ScoreDocument::getOptimizedFlag()  const
{
    return ( this->m_fOptimized );
}

//----------------------------------------------------------------
//    最適化済みフラグを設定する。
//

ErrCode
ScoreDocument::setOptimizedFlag(
        const  Boolean  fVal)
{
    if ( (fVal == BOOL_TRUE) && (getNumRecords() > 1) ) {
        return ( ERR_FAILURE );
    }

    this->m_fOptimized  =  fVal;
    return ( ERR_SUCCESS );
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
//    集計結果を格納する配列をクリアする。
//

ErrCode
ScoreDocument::clearCountedScoresList(
        CountedScoreList  & bufCounted)  const
{
    const   TeamIndex   numTeam = getNumTeams();

    bufCounted.clear();
    bufCounted.resize(numTeam);
    for ( TeamIndex idxTeam = 0; idxTeam < numTeam; ++ idxTeam ) {
        CountedScores   & trgCS = bufCounted.at(idxTeam);

        trgCS.vsWons.clear();       trgCS.vsWons.resize(numTeam);
        trgCS.vsLost.clear();       trgCS.vsLost.resize(numTeam);
        trgCS.vsDraw.clear();       trgCS.vsDraw.resize(numTeam);

        trgCS.restGames.clear();
        trgCS.restGames.resize(numTeam);
        trgCS.vsGotScores.clear();
        trgCS.vsGotScores.resize(numTeam);
        trgCS.vsLostScores.clear();
        trgCS.vsLostScores.resize(numTeam);

        for ( TeamIndex j = 0; j < numTeam; ++ j ) {
            for ( int gt = FILTER_GAMES_FIRST;
                    gt < FILTER_GAMES_END; ++ gt )
            {
                trgCS.vsWons.at(j)[gt]  = 0;
                trgCS.vsLost.at(j)[gt]  = 0;
                trgCS.vsDraw.at(j)[gt]  = 0;

                const   GamesCount  nTotalGames
                    = getGameCount(idxTeam, j, FILTER_ALL_GAMES);
                trgCS.restGames.at(j)[gt] = nTotalGames;
                trgCS.restGames[j][gt | FILTER_SCHEDULE] = nTotalGames;
                trgCS.vsGotScores.at(j)[gt]     = 0;
                trgCS.vsLostScores.at(j)[gt]    = 0;
            }   //  End For (gt)

            trgCS.restGames.at(j)[FILTER_ALL_GAMES] = 0;
            trgCS.restGames.at(j)[FILTER_SCHEDULE]  = 0;
        }   //  End For (j)
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    対チーム毎の集計結果から、合計を計算する。
//

ErrCode
ScoreDocument::countTotalScores(
        const  LeagueIndex  idxLeague,
        CountedScores     & trgCS)  const
{
    for ( int gt = FILTER_GAMES_FIRST; gt < FILTER_GAMES_END; ++ gt )
    {
        trgCS.numWons[gt]   = 0;
        trgCS.numLost[gt]   = 0;
        trgCS.numDraw[gt]   = 0;
        trgCS.numLeagueRestGames[gt]    = 0;
        trgCS.numLeagueRestGames[gt | FILTER_SCHEDULE]  = 0;
        trgCS.numInterRestGames [gt]    = 0;
        trgCS.numInterRestGames [gt | FILTER_SCHEDULE]  = 0;
        trgCS.totalGotScores [gt]   = 0;
        trgCS.totalLostScores[gt]   = 0;
    }

    const   TeamIndex   numTeam = getNumTeams();
    for ( TeamIndex idxEnemy = 0; idxEnemy < numTeam; ++ idxEnemy ) {
        aggregateHomeAway<0>(trgCS.vsWons.at(idxEnemy));
        aggregateHomeAway<0>(trgCS.vsLost.at(idxEnemy));
        aggregateHomeAway<0>(trgCS.vsDraw.at(idxEnemy));
        aggregateHomeAway<0>(trgCS.restGames.at(idxEnemy));
        aggregateHomeAway<FILTER_SCHEDULE>(trgCS.restGames[idxEnemy]);
        aggregateHomeAway<0>(trgCS.vsGotScores .at(idxEnemy));
        aggregateHomeAway<0>(trgCS.vsLostScores.at(idxEnemy));

        const  LeagueIndex  enemyLeague = getTeamInfo(idxEnemy).leagueID;
        if ( idxLeague != enemyLeague ) {
            //  交流戦。    //
            aggregateRestGames(
                    trgCS.restGames.at(idxEnemy),
                    trgCS.numInterRestGames);
        } else {
            //  リーグ戦。  //
            aggregateRestGames(
                    trgCS.restGames.at(idxEnemy),
                    trgCS.numLeagueRestGames);
        }

        for ( int gt = FILTER_GAMES_FIRST; gt < FILTER_GAMES_END; ++ gt )
        {
            trgCS.numWons[gt]   += trgCS.vsWons[idxEnemy][gt];
            trgCS.numLost[gt]   += trgCS.vsLost[idxEnemy][gt];
            trgCS.numDraw[gt]   += trgCS.vsDraw[idxEnemy][gt];
            trgCS.totalGotScores [gt] += trgCS.vsGotScores [idxEnemy][gt];
            trgCS.totalLostScores[gt] += trgCS.vsLostScores[idxEnemy][gt];
        }
    }   //  End For (idxEnemy)

    for ( int gt = FILTER_GAMES_FIRST; gt < FILTER_GAMES_END; ++ gt )
    {
        trgCS.numGames[gt]
                = trgCS.numWons[gt]
                + trgCS.numLost[gt]
                + trgCS.numDraw[gt];
        trgCS.numTotalRestGames[gt]
                = trgCS.numLeagueRestGames[gt]
                + trgCS.numInterRestGames [gt];
        trgCS.numTotalRestGames[gt | FILTER_SCHEDULE]
                = trgCS.numLeagueRestGames[gt | FILTER_SCHEDULE]
                + trgCS.numInterRestGames [gt | FILTER_SCHEDULE];
    }

    return ( ERR_SUCCESS );
}

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