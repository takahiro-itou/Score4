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
//    データをバイナリバッファから読み込む。
//

ErrCode
ScoreDocument::readFromBinaryBuffer(
        const   LpcReadBuf  inBuf,
        const   FileLength  cbBuf)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをバイナリファイルから読み込む。
//

ErrCode
ScoreDocument::readFromBinaryFile(
        const  std::string  &fileName)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをテキストストリームから読み込む。
//

ErrCode
ScoreDocument::readFromTextStream(
        std::istream  & inStr)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをバイナリバッファに書き込む。
//

ErrCode
ScoreDocument::saveToBinaryBuffer(
        LpWriteBuf  const   outBuf,
        const   FileLength  cbBuf)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをバイナリファイルに書き込む。
//

ErrCode
ScoreDocument::saveToBinaryFile(
        const  std::string  &fileName)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをテキストストリームに書き込む.
//

ErrCode
ScoreDocument::saveToTextStream(
        std::ostream  & outStr)
{
    return ( ERR_FAILURE );
}

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

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
