//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of ScoreDocument class.
**
**      @file       ScoreDocument.cpp
**/

#include    "StdAfx.h"

#include    "ScoreDocument.h"

#include    <msclr/marshal_cppstd.h>
using       namespace   msclr::interop;


namespace  Score4Wrapper  {
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
    : m_ptrObj { new Score4Core::Common::ScoreDocument() },
      m_ptrBuf { new WrapCountedScoreList() },
      m_trgDate(0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ScoreDocument::~ScoreDocument()
{
    this->!ScoreDocument();
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ScoreDocument::!ScoreDocument()
{
    if ( this->m_ptrObj ) {
        delete  this->m_ptrObj;
        this->m_ptrObj  = nullptr;
    }
    if ( this->m_ptrBuf ) {
        delete  this->m_ptrBuf;
        this->m_ptrBuf  = nullptr;
    }
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

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    ドキュメントの内容をクリアする。
//

ErrCode
ScoreDocument::clearDocument()
{
    return ( static_cast<ErrCode>(this->m_ptrObj->clearDocument()) );
}

//----------------------------------------------------------------
//    指定したリーグに属するチームを、成績順にソートする。
//

TeamIndex
ScoreDocument::computeRankOrder(
        LeagueIndex         idxLeague,
        array<TeamIndex>^   bufIndex)
{
    std::vector<TeamIndex>  bufNatv;
    const   TeamIndex   retVal  = this->m_ptrObj->computeRankOrder(
            *(this->m_ptrBuf), idxLeague, bufNatv);
    copyVectorToManage(bufNatv, bufIndex);

    return ( retVal );
}

//----------------------------------------------------------------
//    試合結果を集計する。
//

ErrCode
ScoreDocument::countScores(
        DateSerial          trgLastDate,
        CountedScoreList^   bufCounted)
{
    Score4Core::Common::ErrCode  retVal;

    retVal  = this->m_ptrObj->countScores(trgLastDate, *(this->m_ptrBuf));
    const  LeagueIndex  numLeagues  = getNumLeagues();
    for ( LeagueIndex i = 0; i < numLeagues; ++ i ) {
        this->m_ptrObj->computeCurrentRank(i, *(this->m_ptrBuf));
    }

    this->m_trgDate = trgLastDate;
    return ( static_cast<ErrCode>(retVal) );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    ネイティブのインスタンスを取得する。
//

Score4Core::Common::ScoreDocument  &
ScoreDocument::toNativeInstance()
{
    return ( *(this->m_ptrObj) );
}

//----------------------------------------------------------------
//    ネイティブのインスタンスを取得する。
//

Score4Core::Common::ScoreDocument  *
ScoreDocument::toNativePointer()
{
    return ( (this->m_ptrObj) );
}

//----------------------------------------------------------------
//    登録されているリーグ数を取得する。
//

LeagueIndex
ScoreDocument::getNumLeagues()
{
    return ( this->m_ptrObj->getNumLeagues() );
}

//----------------------------------------------------------------
//    記録されているゲームレコード数を取得する。
//

RecordIndex
ScoreDocument::getNumRecords()
{
    return ( this->m_ptrObj->getNumRecords() );
}

//----------------------------------------------------------------
//    登録されているチーム数を取得する。
//

TeamIndex
ScoreDocument::getNumTeams()
{
    return ( this->m_ptrObj->getNumTeams() );
}

//----------------------------------------------------------------
//    最適化済みフラグを取得する。
//

Boolean
ScoreDocument::getOptimizedFlag()
{
    return ( static_cast<Boolean>(this->m_ptrObj->getOptimizedFlag()) );
}

//========================================================================
//
//    Properties.
//


LeagueInfo^
ScoreDocument::leagueInfo::get(
        int  idxLeague)
{
    const  WrapTarget::LeagueInfo  &
        leagueInfo  = this->m_ptrObj->getLeagueInfo(idxLeague);

    LeagueInfo^     retVal  = gcnew LeagueInfo;

    retVal->leagueName  = marshal_as<System::String^>(leagueInfo.leagueName);
    retVal->numPlayOff  = leagueInfo.numPlayOff;

    return ( retVal );
}

void
ScoreDocument::leagueInfo::set(
        int  idxLeague,  LeagueInfo^  leagueInfo)
{
    WrapTarget::LeagueInfo  natvVal;

    System::String^     leagueName  = leagueInfo->leagueName;

    natvVal.leagueName  = marshal_as<std::string>(leagueName);
    natvVal.numPlayOff  = leagueInfo->numPlayOff;

    this->m_ptrObj->setLeagueInfo(idxLeague, natvVal);
}

TeamInfo^
ScoreDocument::teamInfo::get(
        int  idxTeam)
{
    const  WrapTarget::TeamInfo  &
        teamInfo    = this->m_ptrObj->getTeamInfo(idxTeam);

    TeamInfo^   retVal  = gcnew TeamInfo;

    retVal->leagueID    = teamInfo.leagueID;
    retVal->teamName    = marshal_as<System::String^>(teamInfo.teamName);

    return ( retVal );
}

void
ScoreDocument::teamInfo::set(
        int  idxTeam,  TeamInfo^  teamInfo)
{
    WrapTarget::TeamInfo    natvVal;

    System::String^     teamName    = teamInfo->teamName;

    natvVal.leagueID    = teamInfo->leagueID;
    natvVal.teamName    = marshal_as<std::string>(teamName);

    this->m_ptrObj->setTeamInfo(idxTeam, natvVal);
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
}   //  End of namespace  Score4Wrapper
