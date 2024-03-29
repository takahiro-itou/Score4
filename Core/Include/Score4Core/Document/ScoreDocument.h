﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
**      An Interface of ScoreDocument class.
**
**      @file       Document/ScoreDocument.h
**/

#if !defined( SCORE4CORE_DOCUMENT_INCLUDED_SCORE_DOCUMENT_H )
#    define   SCORE4CORE_DOCUMENT_INCLUDED_SCORE_DOCUMENT_H

#include    "Score4Core/Common/Score4Types.h"
#include    "Score4Core/Common/ScoreInterface.h"

#include    <iosfwd>
#include    <string>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Document  {

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
private:

    typedef     Common::WinsForBeatList         WinsForBeatList;

    typedef     Common::CountedScores           CountedScores;
    typedef     std::vector<CountedScores>      CountedScoreList;

    typedef     Common::GameCountTable          GameCountTable;

public:

    /**   リーグ情報。  **/
    typedef     Common::LeagueInfo              LeagueInfo;

    /**   チーム情報。  **/
    typedef     Common::TeamInfo                TeamInfo;

    /**   ゲーム結果のレコード。    **/
    typedef     Common::GameResult              GameResult;

    /**   レコード番号の配列。      **/
    typedef     std::vector<RecordIndex>        RecordIndexList;

    typedef     std::vector<WinningRate>        WinningRateList;
    typedef     std::vector<WinningRateList>    WinningRateTable;

    typedef     std::vector<NumOfDigits>        NumOfDigitsList;
    typedef     std::vector<NumOfDigitsList>    NumOfDigitsTable;

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
    /**   インスタンスを初期化する
    **  （コピーコンストラクタ）。
    **
    **  @param [in] src   コピー元インスタンス。
    **/
    ScoreDocument(
            const   ScoreDocument  &src);

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
    /**   ゲームレコードを追加登録する。
    **
    **  @param [in] gameRecord    追加するレコードの内容。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    appendGameRecord(
            const   GameResult  &gameRecord);

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
    /**   チーム情報を追加登録する。
    **
    **  @param [in] teamName    チーム名。
    **  @param [in] leagueID    所属するリーグ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    appendTeamInfo(
            const  std::string  &teamName,
            const  LeagueIndex  leagueID);

    //----------------------------------------------------------------
    /**   各チームのプレーオフ進出マジックを計算する。
    **
    **  @param [in,out] bufCounted
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    calculateMagicNumbers(
            CountedScoreList    &bufCounted)  const;

    //----------------------------------------------------------------
    /**   全てのレコードを検査して最終日付を設定する。
    **
    **  @return     チェックした最後の日付を返す。
    **/
    virtual  DateSerial
    checkLastDate();

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

    //----------------------------------------------------------------
    /**   集計済みの成績表から順位を計算する。
    **
    **  @param [in]     idxLeague   リーグ。
    **  @param [in,out] csBuf       集計済みデータ。
    **  @return     指定したリーグに属するチーム数を返す。
    **/
    virtual  TeamIndex
    computeCurrentRank(
            const  LeagueIndex  idxLeague,
            CountedScoreList    &csData)  const;

    //----------------------------------------------------------------
    /**   指定したリーグに属するチームを、成績順にソートする。
    **
    **  @param [in] csData      集計済みデータ。
    **  @param [in] idxLeague   リーグ。
    **  @param[out] bufIndex    チーム番号の配列を返す。
    **  @return     そのリーグに属するチーム数を返す。
    **/
    virtual  TeamIndex
    computeRankOrder(
            const  CountedScoreList &csData,
            const  LeagueIndex      idxLeague,
            std::vector<TeamIndex>  &bufIndex)  const;

    //----------------------------------------------------------------
    /**   確定順位を計算して書き込む。
    **
    **  集計済みデータから、可能性のある順位の範囲を決定する。
    **
    **  @param [in,out] bufCounted
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    computeRankRange(
            CountedScoreList    &bufCounted)  const;

    //----------------------------------------------------------------
    /**   指定したデータのコピーを作成する。
    **
    **  @param [in] src   コピー元インスタンス。
    **/
    virtual  ScoreDocument  &
    copyFrom(
            const   ScoreDocument  &src);

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
    virtual  ErrCode
    countScores(
            const   DateSerial  trgLastDate,
            CountedScoreList    &bufCounted)  const;

    //----------------------------------------------------------------
    /**   指定した日付の特定の対戦カードを検索する。
    **
    **  @param [in] gameDate      試合日。
    **  @param [in] homeTeam      ホームチームの番号。
    **  @param [in] visitorTeam   ビジタチームの番号。
    **  @param [in] multiGame     ダブルヘッダーなどで、
    **      同一条件のゲームが複数ある場合、
    **      ゼロから始まるインデックスで特定する。
    **  @return     見つかったレコードのインデックスを返す。
    **              見つからない場合は負の整数を返す。
    **/
    virtual  RecordIndex
    findGameRecord(
            const  DateSerial   gameDate,
            const  TeamIndex    homeTeam,
            const  TeamIndex    visitorTeam,
            const  RecordIndex  multiGame)  const;

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
    virtual  RecordIndex
    findGameRecords(
            const  DateSerial   gameDate,
            const  TeamIndex    homeTeam,
            const  TeamIndex    visitorTeam,
            RecordIndexList   & bufRecord)  const;

    //----------------------------------------------------------------
    /**   チーム情報を検索する。
    **
    **  @param [in] teamName    チーム名。
    **  @return     チーム番号を返す。
    **/
    virtual  TeamIndex
    findTeamInfo(
            const  std::string  &teamName)  const;

    //----------------------------------------------------------------
    /**   対戦試合数用の領域を確保し初期化する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    initializeGameCountTable();

    //----------------------------------------------------------------
    /**   勝率テーブルを作成する。
    **
    **  @param [in] csData        集計済みデータ。
    **  @param [in] leagueIndex   桁数テーブルを作成するリーグ。
    **  @param[out] rateTable     勝率テーブルを格納する変数。
    **  @return     残り試合数の最大値を返す。
    **      最も多くの試合を残しているチームの、その残り試合数。
    **/
    virtual  GamesCount
    makeWinningRateTable(
            const  CountedScoreList &csData,
            const  LeagueIndex      leagueIndex,
            WinningRateTable        &rateTable)  const;

    //----------------------------------------------------------------
    /**   ゲームレコードを最適化する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    optimizeGameRecords();

    //----------------------------------------------------------------
    /**   チーム情報用の領域を確保する。
    **
    **  @param [in] numTeam   チーム数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    resizeTeamInfos(
            const   TeamIndex   numTeam);

    //----------------------------------------------------------------
    /**   最終日付を更新する。
    **
    **  @param [in] flgRecordOnly   設定する内容。
    **      - True :  レコード日付のみ設定。
    **      - False : レコード日付と試合日付の両方を設定。
    **  @param [in] dsVal           設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    updateLastDate(
            const   Boolean     flgRecordOnly,
            const   DateSerial  dsVal);

    //----------------------------------------------------------------
    /**   試合結果のレコードを比較する。
    **
    **  @param [in] recordIndex     比較するレコードのインデックス。
    **  @param [in] eGameFlags      フラグ。
    **  @param [in] gameDate        試合が行われた日。
    **  @param [in] visitorTeam     ビジタチームの番号。
    **  @param [in] homeTeam        ホームチームの番号。
    **  @param [in] visitorScore    ビジタチームの得点。
    **  @param [in] homeScore       ホームチームの得点。
    **/
    virtual  Boolean
    verifyRecord(
            const  RecordIndex  recordIndex,
            const  RecordFlag   eGameFlags,
            const  DateSerial   gameDate,
            const  TeamIndex    visitorTeam,
            const  TeamIndex    homeTeam,
            const  ScoreValue   visitorScore,
            const  ScoreValue   homeScore)  const;

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   指定した相手を確実に上回るのに必要な勝数を計算する。
    **
    **/
    static  GamesCount
    calculateGamesForWin(
            const   WinningRateTable  & rateTable,
            const   TeamIndex           teamIndex,
            const   TeamIndex           enemyIndex,
            const   GamesCount          teamRest,
            const   GamesCount          enemyRest,
            const   Boolean             allowEqual);

    //----------------------------------------------------------------
    /**   表示桁数リストを作成する。
    **
    **  @param [in] rateList      勝率リスト。
    **          ただし要素はソートおよび重複除去済みとする。
    **  @param[out] digitsList    桁数リストを格納する変数。
    **          勝率リストの対応する要素を表示するのに
    **          最低限必要な桁数を格納する。
    **  @return     桁数リスト内の最大値を返す。
    **/
    static  NumOfDigits
    makeDigitsFromUnique(
            const  WinningRateList  &rateList,
            NumOfDigitsList         &digitsList);

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
            const  WinningRateList  &rateList,
            NumOfDigitsList         &digitsList);

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
            const  WinningRateTable &rateTable,
            NumOfDigitsTable        &digitsTable);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   対戦カード毎の試合数を取得する。
    **
    **  @param [in] srcTeam     チーム番号。
    **  @param [in] trgTeam     チーム番号。
    **  @param [in] flagGame    フィルタ。
    **  @return     試合数を返す。
    **/
    GamesCount
    getGameCount(
            const   TeamIndex   srcTeam,
            const   TeamIndex   trgTeam,
            const   GameFilter  flagGame)  const;

    //----------------------------------------------------------------
    /**   対戦カード毎の試合数を取得する。
    **
    **  @param [in] homeTeam      ホームチームの番号。
    **  @param [in] visitorTeam   ビジタチームの番号。
    **  @return     試合数を返す。
    **/
    GamesCount
    getGameCount(
            const   TeamIndex   homeTeam,
            const   TeamIndex   visitorTeam)  const;

    //----------------------------------------------------------------
    /**   対戦カード毎の試合数を設定する。
    **
    **  @param [in] homeTeam      ホームチームの番号。
    **  @param [in] visitorTeam   ビジタチームの番号。
    **  @param [in] gameCount     設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setGameCount(
            const   TeamIndex   homeTeam,
            const   TeamIndex   visitorTeam,
            const   GamesCount  gameCount);

    //----------------------------------------------------------------
    /**   ゲームレコードを取得する。
    **
    **  @param [in] idxRecord   レコード番号。
    **  @return     ゲームレコードの内容を返す。
    **/
    const   GameResult  &
    getGameRecord(
            const  RecordIndex  idxRecord)  const;

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
            const  GameResult   &gameRecord);

    //----------------------------------------------------------------
    /**   最終試合日付を取得する。
    **
    **  @return     試合が実際に行われたデータの最終日付。
    **/
    DateSerial
    getLastActiveDate()  const;

    //----------------------------------------------------------------
    /**   最終試合日付を設定する。
    **
    **  @param [in] dsVal   設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setLastActiveDate(
            const   DateSerial  dsVal);

    //----------------------------------------------------------------
    /**   最終インポート日時を取得する。
    **
    **  @return     最終インポート日時。
    **/
    DateSerial
    getLastImportDate()  const;

    //----------------------------------------------------------------
    /**   最終インポート日時を設定する。
    **
    **  @param [in] dsVal   設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setLastImportDate(
            const   DateSerial  dsVal);

    //----------------------------------------------------------------
    /**   最終レコード日付を取得する。
    **
    **  @return     レコードだけのデータも含めた最終日付。
    **/
    DateSerial
    getLastRecordDate()  const;

    //----------------------------------------------------------------
    /**   最終レコード日付を設定する。
    **
    **  @param [in] dsVal   設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setLastRecordDate(
            const   DateSerial  dsVal);

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
    /**   記録されているゲームレコード数を取得する。
    **
    **  @return     ゲームレコードの数を返す。
    **/
    RecordIndex
    getNumRecords()  const;

    //----------------------------------------------------------------
    /**   登録されているチーム数を取得する。
    **
    **  @return     チームの数を返す。
    **/
    TeamIndex
    getNumTeams()  const;

    //----------------------------------------------------------------
    /**   最適化済みフラグを取得する。
    **
    **  @return     フラグの状態を返す。
    **/
    Boolean
    getOptimizedFlag()  const;

    //----------------------------------------------------------------
    /**   最適化済みフラグを設定する。
    **
    **  @param [in] fVal    設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setOptimizedFlag(
            const  Boolean  fVal);

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

    //----------------------------------------------------------------
    /**   登録されているチームの情報を更新する。
    **
    **  @param [in] idxTeam     チーム番号。
    **  @param [in] teamName    チーム名。
    **  @param [in] leagueID    所属するリーグ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setTeamInfo(
            const  TeamIndex    idxTeam,
            const  std::string  &teamName,
            const  LeagueIndex  leagueID);

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//
private:

    //----------------------------------------------------------------
    /**   可能性のある最終勝率の範囲を計算する。
    **
    **  @param [in] csData    集計済みデータ。
    **  @param[out] miOut     結果を書き込む変数。
    **/
    static  ErrCode
    computeWinningRateRange(
            const  CountedScores  & csData,
            Common::MagicInfo     & miOut);

    //----------------------------------------------------------------
    /**   集計結果を格納する配列をクリアする。
    **
    **  @param[out] bufCounted    結果を格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    clearCountedScoresList(
            CountedScoreList  & bufCounted)  const;

    //----------------------------------------------------------------
    /**   対チーム毎の集計結果から、合計を計算する。
    **
    **  @param [in]     idxLeague   所属するリーグ。
    **  @param [in,out] trgCS       結果を読み書きする変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    countTotalScores(
            const  LeagueIndex  idxLeague,
            CountedScores     & trgCS)  const;

    //----------------------------------------------------------------
    /**   表示桁数リストから指定した要素を検索する。
    **
    **  @param [in] rateList      勝率リスト。
    **  @param [in] digitsList    桁数リスト。
    **  @param [in] wrValue       検索する値。
    **  @return     検索した値に対応する桁数。
    **/
    static  NumOfDigits
    findDigitsList(
            const  WinningRateList  &rateList,
            const  NumOfDigitsList  &digitsList,
            const  WinningRate      wrValue);

    //----------------------------------------------------------------
    /**   敵チームを上回るのに必要な勝利数を計算する。
    **
    **  @param [in] rateTable     事前に作成した勝率テーブル。
    **  @param [in] srcTeam       チーム番号。
    **  @param [in] trgTeam       チーム番号。
    **  @param [in] srcRest       残り試合数。
    **  @param [in] trgRest       残り試合数。
    **  @param [in] directRest    直接対決の残り試合数。
    **  @return     必要な勝利数を記録した構造体。
    **/
    const   Common::NumWinsForBeat
    makeWinsForBeatInfo(
            const   WinningRateTable  & rateTable,
            const   TeamIndex           srcTeam,
            const   TeamIndex           trgTeam,
            const   GamesCount          srcRest,
            const   GamesCount          trgRest,
            const   GamesCount          directRest)  const;

    //----------------------------------------------------------------
    /**   各チームに対する必要勝利数テーブルを作成する。
    **
    **/
    ErrCode
    makeWinsForBeatTable(
            const   WinningRateTable  & rateTable,
            const   TeamIndex           srcTeam,
            CountedScoreList          & bufCounted)  const;

    //----------------------------------------------------------------
    /**   対戦カード毎の試合数を設定する。
    **
    **  @param [in] srcTeam     チーム番号。
    **  @param [in] trgTeam     チーム番号。
    **  @param [in] flagGame    フィルタ。
    **  @param [in] gameCount   設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setGameCount(
            const   TeamIndex   srcTeam,
            const   TeamIndex   trgTeam,
            const   GameFilter  flagGame,
            const   GamesCount  gameCount);

    //----------------------------------------------------------------
    /**   チームごとのマジック関連の情報を書き込む。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    writeTeamMagicNumbers(
            const  TeamIndex        idxTeam,
            const  WinsForBeatList  &wbData,
            Common::MagicInfo       &miOut)  const;

//========================================================================
//
//    Member Variables.
//
private:

    typedef     std::vector<LeagueInfo>     LeagueInfoList;
    typedef     std::vector<TeamInfo>       TeamInfoList;
    typedef     std::vector<GameResult>     GameResultList;

private:

    /**   リーグ情報。      **/
    LeagueInfoList      m_leagueInfos;

    /**   チーム情報。      **/
    TeamInfoList        m_teamInfos;

    /**   ゲームレコード。  **/
    GameResultList      m_gameResults;

    /**   最適化フラグ。    **/
    Boolean             m_fOptimized;

    /**
    **    最終試合日付。
    **
    **    試合が実際に行われたデータの最終日付。
    **/
    DateSerial          m_lastActiveDate;

    /**
    **    最終レコード日付。
    **
    **    レコードだけのデータも含めた最終日付。
    **/
    DateSerial          m_lastRecordDate;

    /**
    **    最終インポート日時。
    **/
    DateSerial          m_lastImportDate;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ScoreDocumentTest;
};

}   //  End of namespace  Document
SCORE4_CORE_NAMESPACE_END

#endif
