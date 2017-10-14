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
**      An Implementation of ErrorDetectionCode class.
**
**      @file       Common/ErrorDetectionCode.cpp
**/

#include    "Score4Core/Common/ErrorDetectionCode.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ErrorDetectionCode  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ErrorDetectionCode::ErrorDetectionCode()
    : m_crcPoly(0x04C11DB7),
      m_tblCRC32()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ErrorDetectionCode::~ErrorDetectionCode()
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

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    誤り検出符号を計算して検査する。
//

ErrorDetectionCode::EDCode
ErrorDetectionCode::checkCRC32(
        const   LpcReadBuf  inBuf,
        const   FileLength  cbBuf)  const
{
    const  LpcByte  ptrBuf  =  static_cast<LpcByte>(inBuf);
    const  EDCode
        retVal  =  computeCRC32(ptrBuf, cbBuf, 0,
                                this->m_crcPoly,
                                this->m_tblCRC32);
    return ( retVal );
}

//----------------------------------------------------------------
//    生成多項式を指定する。
//

ErrCode
ErrorDetectionCode::setupGenPoly(
        const   EDCode  crcPoly)
{

    //  指定された生成多項式でテーブルを作成する。  //
    for ( EDCode i = 0; i < CRC32_TABLE_SIZE; ++ i ) {
        EDCode  tmpCRC  = 0;
        for ( int k = 0; k < 8; ++ k ) {
            tmpCRC  = (tmpCRC << 1)
                    ^ ((tmpCRC & CRC32_MASK) ? crcPoly : 0);
        }
        this->m_tblCRC32[i] = tmpCRC;
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    誤り検出符号を計算して書き込む。
//

ErrorDetectionCode::EDCode
ErrorDetectionCode::writeCRC32(
        LpWriteBuf  const   outBuf,
        const   FileLength  cbBuf)  const
{
    LpByte  ptrBuf  =  static_cast<LpByte>(outBuf);

    const   EDCode
        retVal  =  computeCRC32(ptrBuf, cbBuf, 0,
                                this->m_crcPoly,
                                this->m_tblCRC32);
    LpByte  ptrCur  =  ptrBuf + cbBuf - CRC32_CODE_LENGTH;

    ptrCur[ 0]  =  (retVal >> 24) & 255;
    ptrCur[ 1]  =  (retVal >> 16) & 255;
    ptrCur[ 2]  =  (retVal >>  8) & 255;
    ptrCur[ 3]  =  (retVal      ) & 255;

    return ( retVal );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    誤り検出符号を計算する。
//

ErrorDetectionCode::EDCode
ErrorDetectionCode::computeCRC32(
        const   LpcByte     inBuf,
        const   FileLength  cbBuf,
        const   EDCode      crcInit,
        const   EDCode      crcPoly,
        const   CRC32Table  tblCRC)
{
    EDCode  valCRC  =  crcInit;

    for ( FileLength i = 0; i < cbBuf; ++ i ) {
        EDCode  valBuf  =  static_cast<EDCode>(inBuf[i]);
        for ( int k = 0; k < 8; ++ k ) {
            const   EDCode
                tmpFlp  =  ( (valCRC & CRC32_MASK) ? crcPoly : 0 );
            valCRC  =  (valCRC << 1) ^ tmpFlp;
        }
        valBuf  <<=  1;
        if ( (valBuf & 0x100) ) {
            valCRC  ^=  1;
        }
    }

    return ( valCRC );
}

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
