﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
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
**      An Interface of ScoreDocument class.
**
**      @file       ScoreDocument.h
**/

#pragma     once

#include    "Score4Core/Document/ScoreDocument.h"

#include    "Score4Types.h"
#include    "ScoreInterface.h"

namespace  Score4Wrapper  {
namespace  Document  {

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

    typedef     Common::CountedScores       CountedScores;

    typedef     Common::GameCountTable      GameCountTable;

public:

    /**   リーグ情報。  **/
    typedef     Common::LeagueInfo          LeagueInfo;

    /**   チーム情報。  **/
    typedef     Common::TeamInfo            TeamInfo;

    /**   ゲーム結果のレコード。    **/
    typedef     Common::GameResult          GameResult;

    typedef     Common::WinningRateList     WinningRateList;
    typedef     Common::WinningRateTable    WinningRateTable;

    typedef     Common::NumOfDigitsList     NumOfDigitsList;
    typedef     Common::NumOfDigitsTable    NumOfDigitsTable;

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
public:

    //----------------------------------------------------------------
    /**   ゲームレコードを追加登録する。
    **
    **  @param [in] gameRecord    追加するレコードの内容。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    appendGameRecord(
            GameResult^     gameRecord);

    //----------------------------------------------------------------
    /**   全てのレコードを検査して最終日付を設定する。
    **
    **  @return     チェックした最後の日付を返す。
    **/
    System::DateTime^
    checkLastDate();

    //----------------------------------------------------------------
    /**   ドキュメントの内容をクリアする。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    clearDocument();

    //----------------------------------------------------------------
    /**   指定したリーグに属するチームを、成績順にソートする。
    **
    **  @param [in] csData      集計済みデータ。
    **  @param [in] idxLeague   リーグ。
    **  @param[out] bufIndex    チーム番号の配列を返す。
    **  @return     そのリーグに属するチーム数を返す。
    **/
    TeamIndex
    computeRankOrder(
            LeagueIndex         idxLeague,
        [System::Runtime::InteropServices::Out]
            array<TeamIndex>^   bufIndex);

    //----------------------------------------------------------------
    /**   指定したデータのコピーを作成する。
    **
    **  @param [in] src   コピー元インスタンス。
    **/
    ScoreDocument^
    copyFrom(
            ScoreDocument^  src);

    //----------------------------------------------------------------
    /**   試合結果を集計する。
    **
    **    指定した日付（その日付を含む）までの結果を集計する。
    **
    **  @param [in] trgLastDate   集計対象の最終日。
    **  @param[out] bufCounted    結果を格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    countScores(
        [System::Runtime::InteropServices::Out]
            System::DateTime^   trgLastDate);

    //----------------------------------------------------------------
    /**   指定した条件の対戦カードを検索する。
    **
    **  @param [in] gameDate      試合日。
    **  @param [in] homeTeam      ホームチームの番号。
    **  @param [in] visitorTeam   ビジタチームの番号。
    **  @param[out] bufRecord     結果を格納する変数。
    **      見つかったレコードのインデックスを格納する。
    **  @return     見つかったレコードの件数を返す。
    **/
    RecordIndex
    findGameRecords(
            System::DateTime^           gameDate,
            const   TeamIndex           homeTeam,
            const   TeamIndex           visitorTeam,
        [System::Runtime::InteropServices::Out]
            Common::RecordIndexList^%   bufRecord);

    //----------------------------------------------------------------
    /**   勝率テーブルを作成する。
    **
    **  @param [in] leagueIndex   桁数テーブルを作成するリーグ。
    **  @param[out] rateTable     勝率テーブルを格納する変数。
    **  @return     残り試合数の最大値を返す。
    **      最も多くの試合を残しているチームの、その残り試合数。
    **/
    GamesCount
    makeWinningRateTable(
            const  LeagueIndex  leagueIndex,
        [System::Runtime::InteropServices::Out]
            WinningRateTable^%  rateTable);

    //----------------------------------------------------------------
    /**   ゲームレコードを最適化する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    optimizeGameRecords();

    //----------------------------------------------------------------
    /**   最終日付を更新する。
    **
    **  @param [in] flgRecordOnly   設定する内容。
    **      - True :  レコード日付のみ設定。
    **      - False : レコード日付と試合日付の両方を設定。
    **  @param [in] lastDate        設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    updateLastDate(
            System::Boolean     flgRecordOnly,
            System::DateTime^   lastDate);

//========================================================================
//
//    Public Member Functions (Static).
//
public:

    //----------------------------------------------------------------
    /**   指定したデータのコピーを作成する。
    **
    **  @param [in] src   コピー元インスタンス。
    **  @return     新しいインスタンス。
    **/
    static  ScoreDocument^
    createCopy(
            ScoreDocument^  src);

    //----------------------------------------------------------------
    /**   表示桁数リストを作成する。
    **
    **  @param [in] rateList      勝率リスト。
    **  @param[out] digitsList    桁数リストを格納する変数。
    **          勝率リストの対応する要素を表示するのに
    **          最低限必要な桁数を格納する。
    **  @return     桁数リスト内の最大値を返す。
    **/
    static  NumOfDigits
    makeDigitsList(
            WinningRateList^    rateList,
        [System::Runtime::InteropServices::Out]
            NumOfDigitsList^%   digitsList);

    //----------------------------------------------------------------
    /**   表示桁数テーブルを作成する。
    **
    **  @param [in] rateTable     勝率テーブル。
    **  @param[out] digitsTable   桁数テーブルを格納する変数。
    **          勝率テーブルの対応するセルを表示するのに
    **          最低限必要な桁数を格納する。
    **  @return     桁数テーブル内の最大値を返す。
    **/
    static  NumOfDigits
    makeDigitsTable(
            WinningRateTable^   rateTable,
        [System::Runtime::InteropServices::Out]
            NumOfDigitsTable^%  digitsTable);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   ゲームレコードを取得する。
    **
    **/
    GameResult^
    getGameRecord(
            const  RecordIndex  idxRecord);

    //----------------------------------------------------------------
    /**   ゲームレコードを設定する。
    **
    **  @param [in] idxRecrod     上書きするレコード番号。
    **  @param [in] gameRecord    上書きするレコード内容。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setGameRecord(
            const  RecordIndex  idxRecord,
            GameResult^         gameRecord);

    //----------------------------------------------------------------
    /**   ネイティブのインスタンスを取得する。
    **
    **  @return     アンマネージド型の参照。
    **/
    Score4Core::Document::ScoreDocument  &
    toNativeInstance();

    //----------------------------------------------------------------
    /**   ネイティブのインスタンスを取得する。
    **
    **  @return     アンマネージド型の参照。
    **/
    Score4Core::Document::ScoreDocument  *
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
    System::Boolean
    getOptimizedFlag();

//========================================================================
//
//    Properties.
//
public:

    property    System::DateTime^   lastActiveDate
    {
        System::DateTime^   get();
        void  set(System::DateTime^  dtVal);
    }

    property    System::DateTime^   lastImportDate
    {
        System::DateTime^  get();
        void  set(System::DateTime^  dtVal);
    }

    property    System::DateTime^   lastRecordDate
    {
        System::DateTime^  get();
        void  set(System::DateTime^  dtVal);
    }

    property    LeagueInfo^     leagueInfo[int]
    {
        LeagueInfo^  get(int  idxLeague);
        void  set(int  idxLeague,  LeagueInfo^  leagueInfo);
    }

    property    CountedScores^  scoreInfo[int]
    {
        CountedScores^  get(int  idxTeam)  {
            return ( this->m_csiBuf[idxTeam] );
        }
    }

    property    DateSerial  targetLastDate
    {
        DateSerial  get()  {
            return ( this->m_trgDate );
        }
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

    typedef     Score4Core::Document::ScoreDocument     WrapTarget;

    typedef     std::vector<Score4Core::Common::CountedScores>
    WrapCountedScoreList;

    WrapTarget  *                   m_ptrObj;

    WrapCountedScoreList  *         m_ptrBuf;

    DateSerial                      m_trgDate;

    cli::array<CountedScores^>^     m_csiBuf;
};

}   //  End of namespace  Document
}   //  End of namespace  Score4Wrapper
