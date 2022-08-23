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
**      An Implementation of ScoreDocument class.
**
**      @file       Document/ScoreDocument.cpp
**/

#include    "Score4Core/Document/ScoreDocument.h"

#include    <memory.h>
#include    <stdio.h>
#include    <vector>


SCORE4_CORE_NAMESPACE_BEGIN
namespace  Document  {

namespace  {

inline  void
aggregateGotLostScoreValues(
        const   TeamIndex       idxEnemy,
        const   ScoreValue      svGot,
        const   ScoreValue      svLost,
        const   GameFilter      gType,
        Common::CountedScores   & trgCS)
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
        const   Common::RestGamesArray  & src,
        Common::RestGamesArray          & trg)
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
//    各チームのプレーオフ進出マジックを計算する。
//

ErrCode
ScoreDocument::calculateMagicNumbers(
        CountedScoreList    &bufCounted)  const
{
    WinningRateTable    dblPercent;
    NumOfDigitsTable    dummyDigitsBuffer;

    const   TeamIndex   numTeam = getNumTeams();
    const GamesCount lngMaxRest = makeWinningRateTable(
            bufCounted, -1, dblPercent, dummyDigitsBuffer);

    for ( TeamIndex i = 0; i < numTeam; ++ i ) {
        makeWinsForBeatTable(dblPercent, i, bufCounted);
    }

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
        ++ cntIns;
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
        ++ cntTeam;
    }   //  End For (i)

    //  別のリーグに所属するチームも配列の末尾に格納しておく。  //
    TeamIndex   idxIns  = cntTeam;
    for ( TeamIndex i = 0; i < numTeam; ++ i ) {
        if ( getTeamInfo(i).leagueID != idxLeague ) {
            bufIndex[idxIns]    = i;
            ++ idxIns;
        }
    }

    return ( cntTeam );
}

//----------------------------------------------------------------
//    確定順位を計算して書き込む。
//

ErrCode
ScoreDocument::computeRankRange(
        CountedScoreList    &bufCounted)  const
{
    return ( ERR_FAILURE );
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
                ++ csHome.vsLost.at(idxAway)[FILTER_HOME_GAMES];
                ++ csAway.vsWons.at(idxHome)[FILTER_AWAY_GAMES];
            } else if ( src.homeScore > src.visitorScore ) {
                ++ csHome.vsWons.at(idxAway)[FILTER_HOME_GAMES];
                ++ csAway.vsLost.at(idxHome)[FILTER_AWAY_GAMES];
            } else {
                ++ csHome.vsDraw.at(idxAway)[FILTER_HOME_GAMES];
                ++ csAway.vsDraw.at(idxHome)[FILTER_AWAY_GAMES];
            }

            //  試合数を引く。  //
            -- csHome.restGames.at(idxAway)[FILTER_HOME_GAMES];
            -- csHome.restGames   [idxAway][FILTER_SCDL_HOMES];
            -- csAway.restGames.at(idxHome)[FILTER_AWAY_GAMES];
            -- csAway.restGames   [idxHome][FILTER_SCDL_AWAYS];
        } else if ( src.eGameFlags == GAME_SCHEDULE ) {
            //  スケジュール上のデータを集計する。  //
            -- csHome.restGames.at(idxAway)[FILTER_SCDL_HOMES];
            -- csAway.restGames.at(idxHome)[FILTER_SCDL_AWAYS];
        }
    }

    //  対チーム毎に集計した結果から、合計を計算する。  //
    const   TeamIndex   numTeam = getNumTeams();
    for ( TeamIndex idxTeam = 0; idxTeam < numTeam; ++ idxTeam ) {
        countTotalScores(
                getTeamInfo(idxTeam).leagueID,
                bufCounted.at(idxTeam));
    }

    calculateMagicNumbers(bufCounted);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指定した日付の特定の対戦カードを検索する。
//

RecordIndex
ScoreDocument::findGameRecord(
        const  DateSerial   gameDate,
        const  TeamIndex    homeTeam,
        const  TeamIndex    visitorTeam,
        const  RecordIndex  multiGame)  const
{
    RecordIndex     multiIndex  = 0;
    const  RecordIndex
        numRecords  = static_cast<RecordIndex>(this->m_gameResults.size());
    for ( RecordIndex i = 0; i < numRecords; ++ i ) {
        const   GameResult  &gr = this->m_gameResults.at(i);
        if ( gr.eGameFlags == GAME_EMPTY ) {
            continue;
        }
        if ( gr.recordDate != gameDate ) {
            continue;
        }
        if ( (gr.homeTeam == homeTeam) && (gr.visitorTeam == visitorTeam) ) {
            if ( multiIndex >= multiGame ) {
                return ( i );
            }
            ++ multiIndex;
        }
    }

    //  見つからなかった。  //
    return ( -1 );
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
//    勝率テーブルを作成する。
//

GamesCount
ScoreDocument::makeWinningRateTable(
        const  CountedScoreList &csData,
        const  LeagueIndex      leagueIndex,
        WinningRateTable        &rateTable,
        NumOfDigitsTable        &digitsTable)  const
{
    const   TeamIndex  numTeam  = this->getNumTeams();

    //  配列を確保する。    //
    rateTable.resize(numTeam);
    digitsTable.resize(numTeam);

    GamesCount  maxRestGame = 0;
    for ( TeamIndex teamIndex = 0; teamIndex < numTeam; ++ teamIndex ) {
        const  CountedScores  & cs = csData.at(teamIndex);
        const  GamesCount
            teamRestGames = cs.numTotalRestGames[FILTER_ALL_GAMES];
        if ( maxRestGame < teamRestGames ) {
            maxRestGame = teamRestGames;
        }
        rateTable.at(teamIndex).resize(teamRestGames + 1);
        digitsTable.at(teamIndex).resize(teamRestGames + 1);
    }

    GamesCount  allPercentListCount = (maxRestGame + 1) * numTeam;

    std::vector<WinningRate>    allPercentList(allPercentListCount);
    std::vector<NumOfDigits>    digitsTempList(allPercentListCount);

    //  各チームの勝数と最終勝率のテーブルを作る。  //
    allPercentListCount = 0;
    for ( TeamIndex teamIndex = 0; teamIndex < numTeam; ++ teamIndex ) {
        const  LeagueIndex  teamLeague  = getTeamInfo(teamIndex).leagueID;
        const  CountedScores  & csTeam  = csData.at(teamIndex);

        const   GamesCount
            currentWonGames = csTeam.numWons[FILTER_ALL_GAMES];
        const   GamesCount
            teamRestGames   = csTeam.numTotalRestGames[FILTER_ALL_GAMES];
        const   GamesCount  totalGames  = currentWonGames
            + csTeam.numLost[FILTER_ALL_GAMES] + teamRestGames;

        for ( GamesCount win = 0; win <= teamRestGames; ++ win ) {
            //  勝率を計算する。    //
            const  WinningRate
                lastPercent = (currentWonGames + win) * 1.0 / totalGames;

            //  このデータをテンポラリリストにソートして挿入する。  //
            if ( teamLeague == leagueIndex ) {
                int insertIndex = allPercentListCount;
                for ( int i = 0; i < allPercentListCount; ++ i ) {
                    if ( allPercentList[i] == lastPercent ) {
                        insertIndex  = -1;
                        break;
                    }
                    if ( allPercentList[i] > lastPercent ) {
                        insertIndex = i;
                        break;
                    }
                }
                if ( insertIndex >= 0 ) {
                    for ( int i = allPercentListCount - 1;
                            i >= insertIndex; -- i )
                    {
                        allPercentList[i + 1] = allPercentList[i];
                    }
                    allPercentList[insertIndex] = lastPercent;
                    ++ allPercentListCount;
                }
            }

            //  データを勝率テーブルに書き込む。    //
            rateTable.at(teamIndex).at(win) = lastPercent;
        }
    }

    return ( maxRestGame );
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

//----------------------------------------------------------------
//    試合結果のレコードを比較する。
//

Boolean
ScoreDocument::verifyRecord(
        const  RecordIndex  recordIndex,
        const  RecordFlag   eGameFlags,
        const  DateSerial   gameDate,
        const  TeamIndex    visitorTeam,
        const  TeamIndex    homeTeam,
        const  ScoreValue   visitorScore,
        const  ScoreValue   homeScore)  const
{
    const   GameResult  &gr = this->m_gameResults.at(recordIndex);

    if ( gr.eGameFlags != eGameFlags )  {
        return ( BOOL_FALSE );
    }
    if ( gr.recordDate != gameDate ) {
        return ( BOOL_FALSE );
    }
    if ( (gr.visitorTeam != visitorTeam) || (gr.homeTeam != homeTeam) )
    {
        return ( BOOL_FALSE );
    }
    if ( (gr.visitorScore != visitorScore) || (gr.homeScore != homeScore) )
    {
        return ( BOOL_FALSE );
    }

    return ( BOOL_TRUE );
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    指定した相手を確実に上回るのに必要な勝数を計算する。
//

GamesCount
ScoreDocument::calculateGamesForWin(
        const   WinningRateTable  & rateTable,
        const   TeamIndex           teamIndex,
        const   TeamIndex           enemyIndex,
        const   GamesCount          teamRest,
        const   GamesCount          enemyRest,
        const   Boolean             allowEqual)
{
    GamesCount  winGames, loseGames, nResult;
    WinningRate wrTeamLast, wrEnemyLast;
    Boolean     flgSelf;

    wrTeamLast  = rateTable.at(teamIndex ).at(teamRest );
    wrEnemyLast = rateTable.at(enemyIndex).at(enemyRest);

    if ( wrEnemyLast < wrTeamLast ) {
        flgSelf = BOOL_TRUE;
    } else if ( (allowEqual != BOOL_FALSE) && (wrTeamLast == wrEnemyLast) ) {
        flgSelf = BOOL_TRUE;
    } else {
        flgSelf = BOOL_FALSE;
    }

    if ( flgSelf ) {
        //  自力で  //
        nResult = teamRest;
        for ( winGames = 0; winGames <= teamRest; ++ winGames ) {
            wrTeamLast  = rateTable.at(teamIndex).at(winGames);
            if ( wrEnemyLast < wrTeamLast ) {
                nResult = winGames;
                break;
            } else if ( (allowEqual) && (wrTeamLast == wrEnemyLast) ) {
                nResult = winGames;
                break;
            }
        }
    } else {
        //  他力本願。  //
        nResult = Common::MAGIC_NO_PROBABILITY_WONS + teamRest;
        for ( loseGames = 0; loseGames <= enemyRest; ++ loseGames ) {
            wrEnemyLast = rateTable.at(enemyIndex).at(enemyRest - loseGames);
            if ( wrEnemyLast < wrTeamLast ) {
                nResult = teamRest + loseGames;
                break;
            } else if ( (allowEqual) && (wrEnemyLast == wrTeamLast) ) {
                nResult = teamRest + loseGames;
                break;
            }
        }
    }

    return ( nResult );
}

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
    return ( static_cast<LeagueIndex>(this->m_leagueInfos.size()) );
}

//----------------------------------------------------------------
//    記録されているゲームレコード数を取得する。
//

RecordIndex
ScoreDocument::getNumRecords()  const
{
    return ( static_cast<RecordIndex>(this->m_gameResults.size()) );
}

//----------------------------------------------------------------
//    登録されているチーム数を取得する。
//

TeamIndex
ScoreDocument::getNumTeams()  const
{
    return ( static_cast<TeamIndex>(this->m_teamInfos.size()) );
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
//    可能性のある最終勝率の範囲を計算する。
//

ErrCode
ScoreDocument::computeWinningRateRange(
        const  CountedScores  & csData,
        Common::MagicInfo     & miOut)
{
    const   GamesCount  curWons = csData.numWons[FILTER_ALL_GAMES];
    const   GamesCount  numRest = csData.numTotalRestGames[FILTER_ALL_GAMES];
    const   GamesCount
        finNumGames = (curWons + csData.numLost[FILTER_ALL_GAMES] + numRest);
    const   GamesCount  finWons = (curWons + numRest);

    miOut.wrateLow  = (curWons * 1.0) / finNumGames;
    miOut.wrateHigh = (finWons * 1.0) / finNumGames;

    return ( ERR_SUCCESS );
}

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
                    = getGameCount(idxTeam, j, static_cast<GameFilter>(gt));
                trgCS.restGames.at(j)[gt] = nTotalGames;
                trgCS.restGames[j][gt | FILTER_SCHEDULE] = nTotalGames;
                trgCS.vsGotScores.at(j)[gt]     = 0;
                trgCS.vsLostScores.at(j)[gt]    = 0;
            }   //  End For (gt)

            trgCS.restGames.at(j)[FILTER_ALL_GAMES] = 0;
            trgCS.restGames.at(j)[FILTER_SCDL_ALLS] = 0;
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
//    敵チームを上回るのに必要な勝利数を計算する。
//

const   Common::NumWinsForBeat
ScoreDocument::makeWinsForBeatInfo(
        const   WinningRateTable  & rateTable,
        const   TeamIndex           srcTeam,
        const   TeamIndex           trgTeam,
        const   GamesCount          srcRest,
        const   GamesCount          trgRest,
        const   GamesCount          directRest)  const
{
    Common::NumWinsForBeat  retInfo;
    WinningRate srcRate, trgRate;

    //  自力で敵チームを上回る可能性を計算する。            //
    //  「自力」の意味は、直接対決は自チームが全て勝利し、  //
    //  敵チームはそれを除く残り試合に全勝すると仮定する。  //
    //  その時に、後何ゲーム負けても自力での可能性が残る、  //
    //  あるいは、既に自力の可能性がなくなっている場合は、  //
    //  敵が何ゲーム負ければ、可能性が復活するか計算する。  //
    retInfo.numWinsSelf = calculateGamesForWin(
            rateTable, srcTeam, trgTeam,
            srcRest, trgRest - directRest, BOOL_TRUE);
    retInfo.numWinsDiff = (srcRest - retInfo.numWinsSelf);

    //  まず直接対決で敵チームが全部勝利した時を計算する。  //
    srcRate = rateTable.at(srcTeam).at(srcRest - directRest);
    trgRate = rateTable.at(trgTeam).at(trgRest);

    if ( trgRate < srcRate ) {
        //  この時にお互い残り試合を全勝して、  //
        //  相手を上回るなら、マジックが点灯。  //
        retInfo.filterType  = MF_ON_MAGIC;
        retInfo.numNeedWins = calculateGamesForWin(
                rateTable, srcTeam, trgTeam,
                srcRest - directRest, trgRest, BOOL_FALSE);
        retInfo.numRestGame = srcRest - directRest;
        return ( retInfo );
    }

    const   GamesCount  winTemp = calculateGamesForWin(
            rateTable, srcTeam, trgTeam,
            srcRest, trgRest, BOOL_FALSE);
    if ( winTemp <= srcRest ) {
        retInfo.filterType  = MF_MAGIC_IF_RIVAL_LOSE;
        retInfo.numNeedWins = winTemp;
        retInfo.numRestGame = srcRest - directRest;
        return ( retInfo );
    }

    //  次に直接対決で自チームが全部勝利した時を計算する。  //
    {
        retInfo.numNeedWins = calculateGamesForWin(
                rateTable, srcTeam, trgTeam,
                srcRest, trgRest - directRest, BOOL_TRUE);
        retInfo.numRestGame = srcRest;
    }
    if ( retInfo.numNeedWins <= srcRest ) {
        retInfo.filterType  = MF_BEAT_IF_WIN_DIRECT;
    } else if ( retInfo.numNeedWins >= Common::MAGIC_NO_PROBABILITY_WONS) {
        retInfo.filterType  = MF_NEVER_BEAT;
    } else {
        retInfo.filterType  = MF_CANNOT_BEAT_BY_SELF;
    }
    return ( retInfo );
}

//----------------------------------------------------------------
//    各チームに対する必要勝利数テーブルを作成する。
//

ErrCode
ScoreDocument::makeWinsForBeatTable(
        const   WinningRateTable  & rateTable,
        const   TeamIndex           srcTeam,
        CountedScoreList          & bufCounted)  const
{
    const   TeamIndex   numTeam = getNumTeams();
    GamesCount  trgRest, directRest;

    const   LeagueIndex league  = getTeamInfo(srcTeam).leagueID;

    CountedScores   &cs = bufCounted.at(srcTeam);
    const   GamesCount  srcRest = cs.numTotalRestGames[FILTER_ALL_GAMES];

    cs.numWinsForBeat.clear();
    cs.numWinsForBeat.resize(numTeam);

    for ( TeamIndex j = 0; j < numTeam; ++ j ) {
        if ( (getTeamInfo(j).leagueID != league) || (j == srcTeam) ) {
            cs.numWinsForBeat[j].filterType     = MF_DIFFERENT_LEAGUE;
            cs.numWinsForBeat[j].numNeedWins    = -1;
            cs.numWinsForBeat[j].numRestGame    = -1;
            continue;
        }

        const   CountedScores  & csTrg  = bufCounted.at(j);
        trgRest     = csTrg.numTotalRestGames[FILTER_ALL_GAMES];
        directRest  = cs.restGames.at(j)[FILTER_ALL_GAMES];

        cs.numWinsForBeat[j] = makeWinsForBeatInfo(
                rateTable, srcTeam, j, srcRest, trgRest, directRest
        );
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

}   //  End of namespace  Document
SCORE4_CORE_NAMESPACE_END
