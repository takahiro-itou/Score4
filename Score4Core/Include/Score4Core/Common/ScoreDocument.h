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
    /**   データをバイナリバッファから読み込む。
    **
    **  @param [in] inBuf   バッファのアドレス。
    **  @param [in] cbBuf   バッファのバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    readFromBinaryBuffer(
            const   LpcReadBuf  inBuf,
            const   FileLength  cbBuf);

    //----------------------------------------------------------------
    /**   データをバイナリファイルから読み込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    readFromBinaryFile(
            const  std::string  &fileName);

    //----------------------------------------------------------------
    /**   データをテキストストリームから読み込む。
    **
    **  @param [in,out] inStr   入力ストリーム。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    readFromTextStream(
            std::istream  & inStr);

    //----------------------------------------------------------------
    /**   データをバイナリバッファに書き込む。
    **
    **  @param[out] outBuf    バッファのアドレス。
    **  @param [in] cbBuf     バッファのバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    saveToBinaryBuffer(
            LpWriteBuf  const   outBuf,
            const   FileLength  cbBuf);

    //----------------------------------------------------------------
    /**   データをバイナリファイルに書き込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    saveToBinaryFile(
            const  std::string  &fileName);
    //----------------------------------------------------------------
    /**   データをテキストストリームに書き込む.
    **
    **  @param[out] outStr    出力ストリーム。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    saveToTextStream(
            std::ostream  & outStr);

//========================================================================
//
//    Public Member Functions.
//

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
