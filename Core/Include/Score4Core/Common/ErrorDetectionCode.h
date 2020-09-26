//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  The Score4 Core Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2020, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU General Public License (GPL) version 3,                 **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Interface of ErrorDetectionCode class.
**
**      @file       Common/ErrorDetectionCode.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_ERROR_DETECTION_CODE_H )
#    define   SCORE4CORE_COMMON_INCLUDED_ERROR_DETECTION_CODE_H

#include    "Score4Types.h"

#include    <iosfwd>
#include    <string>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //
class   ScoreDocument;

//========================================================================
//
//    ErrorDetectionCode  class.
//

class  ErrorDetectionCode
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   誤り検出符号のデータ型。  **/
    typedef     unsigned  int       EDCode;

    enum  {
        /**   誤り検出符号のバイト数。  **/
        CRC32_CODE_LENGTH   =  4
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
    ErrorDetectionCode();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ErrorDetectionCode();

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
    /**   誤り検出符号を計算して検査する。
    **
    **  @param [in] inBuf    バッファのアドレス。
    **  @param [in] cbBuf    バッファのバイト数。
    **  @return     計算した値を返す。
    **/
    EDCode
    checkCRC32(
            const   LpcReadBuf  inBuf,
            const   FileLength  cbBuf)  const;

    //----------------------------------------------------------------
    /**   生成多項式を指定する。
    **
    **  @param [in] crcPoly   生成多項式。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setupGenPoly(
            const   EDCode  crcPoly);

    //----------------------------------------------------------------
    /**   誤り検出符号を計算して書き込む。
    **
    **  @param [in,out] outBuf   バッファのアドレス。
    **  @param [in]     cbBuf    バッファのバイト数。
    **  @return     計算した値を返す。
    **/
    EDCode
    writeCRC32(
            LpWriteBuf  const   outBuf,
            const   FileLength  cbBuf)  const;

//========================================================================
//
//    Accessors.
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

    enum  {
        /**   計算用テーブルのサイズ。  **/
        CRC32_TABLE_SIZE    =  256
    };

    static  CONSTEXPR_VAR   EDCode  CRC32_MASK  =  0x80000000;

    /**
    **    計算用テーブルの型。
    **
    **    特定サイズの配列。
    **/
    typedef     EDCode      CRC32Table[CRC32_TABLE_SIZE];

private:

    //----------------------------------------------------------------
    /**   誤り検出符号を計算する。
    **
    **  @param [in] inBuf     バッファのアドレス。
    **  @param [in] cbBuf     バッファのバイト数。
    **  @param [in] edcInit   初期値。
    **  @return     計算した値を返す。
    **/
    static  EDCode
    computeCRC32(
            const   LpcByte     inBuf,
            const   FileLength  cbBuf,
            const   EDCode      crcInit,
            const   EDCode      crcPoly,
            const   CRC32Table  tblCRC);

//========================================================================
//
//    Member Variables.
//
private:

    /**   生成多項式。  **/
    EDCode          m_crcPoly;

    /**   計算に使うテーブル。  **/
    //EDCode      m_tblCRC32[256];
    CRC32Table      m_tblCRC32;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ErrorDetectionCodeTest;
};

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
