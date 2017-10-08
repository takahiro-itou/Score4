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
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    ドキュメントの内容をクリアする。
//

ErrCode
ScoreDocument::clearDocument()
{
    return ( ERR_FAILURE );
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

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
