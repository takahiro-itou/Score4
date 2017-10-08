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
**      An Interface of ScoreDocument class.
**
**      @file       Common/ScoreDocument.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_SCORE_DOCUMENT_H )
#    define   SCORE4CORE_COMMON_INCLUDED_SCORE_DOCUMENT_H

#include    "Score4Types.h"

#include    <iosfwd>
#include    <string>
#include    <vector>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ScoreDocument  class.
//

class  ScoreDocument
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     std::vector<GamesCount>     GameCountTable;

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

    /**
    **   　チーム情報。
    **/
    struct  TeamInfo
    {
        LeagueIndex     leagueID;       /**<  所属リーグ。      **/
        std::string     teamName;       /**<  チーム名。        **/
        GameCountTable  gameCounts;     /**<  試合数のリスト。  **/
    };

    /**
    **    ゲーム結果のレコード。
    **/
    struct  GameResult
    {
        RecordFlag      eGameFlags;
        DateSerial      recordDate;
        TeamIndex       visitorTeam;
        ScoreValue      homeTeam;
        TeamIndex       visitorScore;
        ScoreValue      homeScore;
    };

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    ScoreDocument();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ScoreDocument();

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
public:

    //----------------------------------------------------------------
    /**   リーグ情報を追加登録する。
    **
    **  @param [in] leagueInfo    追加するリーグの情報。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    appendLeagueInfo(
            const   LeagueInfo  &leagueInfo);

    //----------------------------------------------------------------
    /**   チーム情報を追加登録する。
    **
    **  @param [in] teamInfo    追加するチームの情報。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    appendTeamInfo(
            const   TeamInfo    &teamInfo);

    //----------------------------------------------------------------
    /**   ドキュメントの内容をクリアする。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    clearDocument();

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   登録されているリーグの情報を取得する。
    **
    **  @param [in] idxLeague   リーグ番号。
    **  @return     リーグの情報を返す。
    **/
    const   LeagueInfo  &
    getLeagueInfo(
            const  LeagueIndex  idxLeague)  const;

    //----------------------------------------------------------------
    /**   登録されているリーグの情報を更新する。
    **
    **  @param [in] idxLeague     リーグ番号。
    **  @param [in] leagueInfo    リーグ情報。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setLeagueInfo(
            const  LeagueIndex  idxLeague,
            const  LeagueInfo   &leagueInfo);

    //----------------------------------------------------------------
    /**   登録されているリーグ数を取得する。
    **
    **  @return     リーグの数を返す。
    **/
    LeagueIndex
    getNumLeagues()  const;

    //----------------------------------------------------------------
    /**   登録されているチーム数を取得する。
    **
    **  @return     チームの数を返す。
    **/
    TeamIndex
    getNumTeams()  const;

    //----------------------------------------------------------------
    /**   登録されているチームの情報を取得する。
    **
    **  @param [in] idxTeam   チーム番号。
    **  @return     チームの情報を返す。
    **/
    const   TeamInfo  &
    getTeamInfo(
            const   TeamIndex   idxTeam)  const;

    //----------------------------------------------------------------
    /**   登録されているチームの情報を更新する。
    **
    **  @param [in] idxTeam     チーム番号。
    **  @param [in] teamInfo    チーム情報。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setTeamInfo(
            const   TeamIndex   idxTeam,
            const   TeamInfo    &teamInfo);

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    typedef     std::vector<LeagueInfo>     LeagueInfoList;
    typedef     std::vector<TeamInfo>       TeamInfoList;

private:

    /**   リーグ情報。  **/
    LeagueInfoList      m_leagueInfos;

    /**   チーム情報。  **/
    TeamInfoList        m_teamInfos;


//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ScoreDocumentTest;
};

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
