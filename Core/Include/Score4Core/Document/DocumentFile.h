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
**      An Interface of DocumentFile class.
**
**      @file       Document/DocumentFile.h
**/

#if !defined( SCORE4CORE_DOCUMENT_INCLUDED_DOCUMENT_FILE_H )
#    define   SCORE4CORE_DOCUMENT_INCLUDED_DOCUMENT_FILE_H

#include    "Score4Core/Common/Score4Types.h"
#include    "Score4Core/Common/ScoreInterface.h"

#include    <iosfwd>
#include    <string>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Document  {

//  クラスの前方宣言。  //
class   ScoreDocument;

//========================================================================
//
//    DocumentFile  class.
//

class  DocumentFile
{

//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     Common::GameCountList       GameCountList;

public:

    //  各ブロックのサイズを計算した結果。  //
    struct  BlockSizeInfo
    {
        FileLength  bsFileHead;     /**<  ファイルヘッダ領域。  **/
        FileLength  bsExtHead;      /**<  拡張ヘッダ領域。      **/
        FileLength  bsLeagure;      /**<  全リーグ分のサイズ。  **/
        FileLength  bsTeamInfo;     /**<  全チーム分のサイズ。  **/
        FileLength  bsSettings;     /**<  設定領域のサイズ。    **/
        FileLength  bsRecords;      /**<  レコード部のサイズ。  **/
        FileLength  bsFileSize;     /**<  ファイル全体の長さ。  **/

        FileLength  cbLeague;       /**<  壱リーグ分のサイズ。  **/
        FileLength  cbTeamGame;     /**<  試合数テーブル領域。  **/
        FileLength  cbTeamInfo;     /**<  チーム情報のサイズ。  **/
        FileLength  cbTeamRsvd;     /**<  チーム情報予約領域。  **/
        FileLength  cbTeamReqs;     /**<  壱チーム分のサイズ。  **/
        FileLength  cbRecsHead;     /**<  レコード部先頭領域。  **/
        FileLength  cbRecsBody;     /**<  レコード部本体領域。  **/
    };

    /**   エラー情報。  **/
    struct  ErrorInfo
    {
        std::string     message;
        std::string     what;
    };

    /**
    **    発生したエラーを保存しておくバッファ。
    **/
    typedef     std::vector<ErrorInfo>      ErrorArray;

    /**   ゲーム結果のレコード。    **/
    typedef     Common::GameResult          GameResult;

    typedef     std::vector<GameResult>     GameResultList;

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
    DocumentFile();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~DocumentFile();

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
    /**   バイナリ形式で保存するのに必要な容量を計算する。
    **
    **  @param [in] objDoc    ドキュメント。
    **  @param[out] bsInfo    各ブロックのサイズ。
    **  @return     シリアライズに必要なバイト数。
    **/
    static  FileLength
    computeImageSize(
            const  ScoreDocument  & objDoc,
            BlockSizeInfo  *        bsInfo);

    //----------------------------------------------------------------
    /**   レコードをテキストストリームからインポートする。
    **
    **  @param [in,out] inStr     入力ストリーム。
    **  @param [in,out] ptrDoc    内容を格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    importRecordFromTextStream(
            std::istream     &  inStr,
            ScoreDocument  *    ptrDoc);

    //----------------------------------------------------------------
    /**   データをバイナリバッファから読み込む。
    **
    **  @param [in] inBuf    バッファのアドレス。
    **  @param [in] cbBuf    バッファのバイト数。
    **  @param[out] ptrDoc   ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    readFromBinaryBuffer(
            const   LpcReadBuf  inBuf,
            const   FileLength  cbBuf,
            ScoreDocument  *    ptrDoc);

    //----------------------------------------------------------------
    /**   データをバイナリファイルから読み込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @param[out] ptrDoc      ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    readFromBinaryFile(
            const  std::string  &fileName,
            ScoreDocument  *    ptrDoc);

    //----------------------------------------------------------------
    /**   データをテキストファイルから読み込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @param[out] ptrDoc      ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    readFromTextFile(
            const  std::string  &fileName,
            ScoreDocument  *    ptrDoc);

    //----------------------------------------------------------------
    /**   データをテキストストリームから読み込む。
    **
    **  @param [in,out] inStr     入力ストリーム。
    **  @param    [out] ptrDoc    ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    readFromTextStream(
            std::istream     &  inStr,
            ScoreDocument  *    ptrDoc);

    //----------------------------------------------------------------
    /**   レコード部をテキストストリームから読み込む。
    **
    **  @param [in]     objDoc    ドキュメント。
    **  @param [in,out] inStr     入力ストリーム。
    **  @param    [out] outRec    内容を格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    readRecordFromTextStream(
            const  ScoreDocument  & objDoc,
            std::istream          & inStr,
            GameResultList        & outRec);

    //----------------------------------------------------------------
    /**   データをバイナリバッファに書き込む。
    **
    **  @param [in] objDoc    ドキュメント。
    **  @param [in] bsInfo    各ブロックのサイズ情報。
    **  @param[out] outBuf    バッファのアドレス。
    **  @param [in] cbBuf     バッファのバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    saveToBinaryBuffer(
            const  ScoreDocument  & objDoc,
            const  BlockSizeInfo  * bsInfo,
            LpWriteBuf  const       outBuf,
            const   FileLength      cbBuf);

    //----------------------------------------------------------------
    /**   データをバイナリファイルに書き込む。
    **
    **  @param [in] objDoc      ドキュメント。
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    saveToBinaryFile(
            const  ScoreDocument  & objDoc,
            const  std::string    & fileName);

    //----------------------------------------------------------------
    /**   データをテキストファイルに書き込む。
    **
    **  @param [in] objDoc      ドキュメント。
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    saveToTextFile(
            const  ScoreDocument  & objDoc,
            const  std::string    & fileName);

    //----------------------------------------------------------------
    /**   データをテキストストリームに書き込む.
    **
    **  @param [in] objDoc    ドキュメント。
    **  @param[out] outStr    出力ストリーム。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    saveToTextStream(
            const  ScoreDocument  & objDoc,
            std::ostream          & outStr);

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//
protected:

    //----------------------------------------------------------------
    /**   発生したエラーの情報を登録する。
    **
    **  @param [in] errInfo
    **  @return     void.
    **/
    void
    appendErrorInfo(
            const  ErrorInfo  & errInfo);

    //----------------------------------------------------------------
    /**   発生したエラーの情報を登録する。
    **
    **  @param [in] errInfo
    **  @return     void.
    **/
    void
    appendErrorInfo(
            const  std::string  &message,
            const  std::string  &what);

    //----------------------------------------------------------------
    /**   発生した警告を登録する。
    **
    **  @param [in] message
    **  @param [in] what
    **  @return     void.
    **/
    void
    appendWarningLog(
            const  std::string  &message,
            const  std::string  &what);

//========================================================================
//
//    For Internal Use Only.
//
private:

    typedef     unsigned  int       HeaderItem;

    struct  FileHeader
    {
        HeaderItem      fSignature;
        HeaderItem      fVersion;
        HeaderItem      headerID;
        HeaderItem      headerGame;
        HeaderItem      headerSize;
        HeaderItem      offsRecord;
        HeaderItem      reserved06;
        HeaderItem      reserved07;
        HeaderItem      offsExtHead;
        HeaderItem      sizeExtHead;
        HeaderItem      reserved10;
        HeaderItem      reserved11;
        HeaderItem      reserved12;
        HeaderItem      reserved13;
        HeaderItem      reserved14;
        HeaderItem      reserved15;
    };

    struct  ExtraHeader
    {
        DateSerial      lastImport;
        HeaderItem      hiReserved[14];
    };

    enum  {
        /**
        **    誤り検出（CRC-32）の計算に使う生成多項式。
        **/
        FILE_CRC32_GENPOLY  =  0x04C11DB7
    };

private:

    //----------------------------------------------------------------
    /**   ファイルヘッダを読み込む。
    **
    **  @param [in] inBuf       バッファのアドレス。
    **  @param [in] cbBuf       バッファのバイト数。
    **  @param[out] fileHead    標準ヘッダを格納する変数。
    **  @param[out] extHead     拡張ヘッダを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    readFileHeader(
            const   LpcReadBuf      inBuf,
            const   FileLength      cbBuf,
            FileHeader   *  const   fileHead,
            ExtraHeader  *  const   extHead);

    //----------------------------------------------------------------
    /**   レコードブロックを読み込む。
    **
    **  @param [in] inBuf     バッファのアドレス。
    **  @param [in] cbBuf     バッファのバイト数。
    **  @param[out] ptrDoc    ドキュメントを格納する変数。
    **  @param[out] cbRead    読み込んだバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    readRecordBlock(
            const   LpcReadBuf  inBuf,
            const   FileLength  cbBuf,
            ScoreDocument  *    ptrDoc,
            FileLength  *       cbRead);

    //----------------------------------------------------------------
    /**   設定ブロックを読み込む。
    **
    **  @param [in] inBuf     バッファのアドレス。
    **  @param [in] cbBuf     バッファのバイト数。
    **  @param[out] ptrDoc    ドキュメントを格納する変数。
    **  @param[out] cbRead    読み込んだバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    readSettingBlock(
            const   LpcReadBuf  inBuf,
            const   FileLength  cbBuf,
            ScoreDocument  *    ptrDoc,
            FileLength  *       cbRead);

    //----------------------------------------------------------------
    /**   ファイルヘッダを書き込む。
    **
    **  @param [in] fileHead    標準ヘッダを格納する変数。
    **  @param [in] extHead     拡張ヘッダを格納する変数。
    **  @param [in] cbBuf       バッファのバイト数。
    **  @param[out] outBuf      バッファのアドレス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    writeFileHeader(
            const   FileHeader    & fileHead,
            const   ExtraHeader   & extHead,
            const   FileLength      cbBuf,
            LpWriteBuf      const   outBuf);

    //----------------------------------------------------------------
    /**   レコードブロックを書き込む。
    **
    **  @param [in] objDoc    ドキュメント。
    **  @param[out] outBuf    バッファのアドレス。
    **  @param [in] cbBuf     バッファのバイト数。
    **  @param[out] cbWrtie   書き込んだバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    writeRecordBlock(
            const  ScoreDocument  & objDoc,
            LpWriteBuf      const   outBuf,
            const  FileLength       cbBuf,
            FileLength  *   const   cbWrite);


    //----------------------------------------------------------------
    /**   設定ブロックを書き込む。
    **
    **  @param [in] objDoc    ドキュメント。
    **  @param[out] outBuf    バッファのアドレス。
    **  @param [in] cbBuf     バッファのバイト数。
    **  @param [in] fStart    書き込み開始位置。
    **      ブロック内にレコードの位置を保存する。
    **      その値を計算するためだけに使う。
    **  @param[out] cbWrtie   書き込んだバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    writeSettingBlock(
            const  ScoreDocument  & objDoc,
            const  BlockSizeInfo  & bsInfo,
            LpWriteBuf      const   outBuf,
            const  FileLength       cbBuf,
            const  FileLength       fStart,
            FileLength  *   const   cbWrite);

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
    friend  class   DocumentFileTest;
};

}   //  End of namespace  Document
SCORE4_CORE_NAMESPACE_END

#endif
