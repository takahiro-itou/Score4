//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Interface of ScoreDocument class.
**
**      @file       ScoreDocument.h
**/

#pragma     once

#include    "Score4Core/Common/ScoreDocument.h"

#include    "Score4Types.h"


namespace  Score4Wrapper  {
namespace  Common  {

public ref  class   LeagueInfo
{
public:
    System::String^     leagueName;
    TeamIndex           numPlayOff;
};

public ref  class   TeamInfo
{
public:
    LeagueIndex         leagueID;
    System::String^     teamName;

    array<GamesCount>^  gameCounts;
};

public ref  class   GameResult
{
public:
    RecordFlag      eGameFlags;
    DateSerial      recordDate;
    TeamIndex       visitorTeam;
    TeamIndex       homeTeam;
    ScoreValue      visitorScore;
    ScoreValue      homeScore;
};

//========================================================================
//
//    ScoreDocument  class.
//

public ref  class  ScoreDocument
{

//========================================================================
//
//    Internal Type Definitions.
//
private:

public:


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
    ~ScoreDocument();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    !ScoreDocument();

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

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   ネイティブのインスタンスを取得する。
    **
    **  @return     アンマネージド型の参照。
    **/
    Score4Core::Common::ScoreDocument  &
    toNativeInstance();

    //----------------------------------------------------------------
    /**   ネイティブのインスタンスを取得する。
    **
    **  @return     アンマネージド型の参照。
    **/
    Score4Core::Common::ScoreDocument  *
    toNativePointer();

    //----------------------------------------------------------------
    /**   登録されているリーグ数を取得する。
    **
    **  @return     リーグの数を返す。
    **/
    LeagueIndex
    getNumLeagues();

    //----------------------------------------------------------------
    /**   記録されているゲームレコード数を取得する。
    **
    **  @return     ゲームレコードの数を返す。
    **/
    RecordIndex
    getNumRecords();

    //----------------------------------------------------------------
    /**   登録されているチーム数を取得する。
    **
    **  @return     チームの数を返す。
    **/
    TeamIndex
    getNumTeams();

    //----------------------------------------------------------------
    /**   最適化済みフラグを取得する。
    **
    **  @return     フラグの状態を返す。
    **/
    Boolean
    getOptimizedFlag();

//========================================================================
//
//    Properties.
//
public:

    property    DateSerial  lastActiveDate
    {
        DateSerial  get()  {
            return ( this->m_ptrObj->getLastActiveDate() );
        }
        void  set(DateSerial dsVal)  {
            this->m_ptrObj->setLastActiveDate(dsVal);
        }
    }

    property    DateSerial  lastImportDate
    {
        DateSerial  get()  {
            return ( this->m_ptrObj->getLastImportDate() );
        }
        void  set(DateSerial dsVal)  {
            this->m_ptrObj->setLastImportDate(dsVal);
        }
    }

    property    DateSerial  lastRecordDate
    {
        DateSerial  get()  {
            return ( this->m_ptrObj->getLastRecordDate() );
        }
        void  set(DateSerial  dsVal)  {
            this->m_ptrObj->setLastRecordDate(dsVal);
        }
    }

    property    LeagueInfo^     leagueInfo[int]
    {
        LeagueInfo^  get(int  idxLeague);
        void  set(int  idxLeague,  LeagueInfo^  leagueInfo);
    }

    property    TeamInfo^   teamInfo[int]
    {
        TeamInfo^  get(int  idxTeam);
        void  set(int  idxTeam,  TeamInfo^  teamInfo);
    }


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

    typedef     Score4Core::Common::ScoreDocument       WrapTarget;

    WrapTarget  *       m_ptrObj;

};

}   //  End of namespace  Common
}   //  End of namespace  Score4Wrapper
