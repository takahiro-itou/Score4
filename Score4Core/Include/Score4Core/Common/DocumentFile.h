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
**      An Interface of DocumentFile class.
**
**      @file       Common/DocumentFile.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_DOCUMENT_FILE_H )
#    define   SCORE4CORE_COMMON_INCLUDED_DOCUMENT_FILE_H

#include    "Score4Types.h"

#include    <iosfwd>
#include    <string>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    DocumentFile  class.
//

class  DocumentFile
{

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

private:

    //----------------------------------------------------------------
    /**   ファイルヘッダを読み込む。
    **
    **  @param [in] inBuf
    **  @param [in] inBuf   バッファのアドレス。
    **  @param [in] cbBuf   バッファのバイト数。
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

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif