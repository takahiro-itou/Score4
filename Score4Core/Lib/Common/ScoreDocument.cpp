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

#include    <fcntl.h>
#include    <memory.h>
#include    <stdio.h>
#include    <sys/stat.h>
#include    <unistd.h>
#include    <vector>

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
    ErrCode         retErr;
    FileHeader      fileHead;
    ExtraHeader     extHead;

    retErr  = readFileHeader(inBuf, cbBuf, &fileHead, &extHead);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをバイナリファイルから読み込む。
//

ErrCode
ScoreDocument::readFromBinaryFile(
        const  std::string  &fileName)
{
    int     fd  =  -1;

    fd  = open(fileName.c_str(), O_RDONLY);
    if ( fd == -1 ) {
        return ( ERR_FILE_OPEN_ERROR );
    }

    struct  stat    stBuf;

    if ( fstat(fd, &stBuf) == -1 ) {
        close(fd);
        return ( ERR_FILE_IO_ERROR );
    }

    const   FileLength  cbFile  = stBuf.st_size;
    std::vector<unsigned char>  buf(cbFile);
    if ( read(fd, &(buf[0]), cbFile) != static_cast<ssize_t>(cbFile) )
    {
        close(fd);
        return ( ERR_FILE_IO_ERROR );
    }
    close(fd);

    const  ErrCode  retErr  = readFromBinaryBuffer(&(buf[0]), cbFile);

    return ( retErr );
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

//----------------------------------------------------------------
//    ファイルヘッダを読み込む。
//

ErrCode
ScoreDocument::readFileHeader(
        const   LpcReadBuf      inBuf,
        const   FileLength      cbBuf,
        FileHeader   *  const   fileHead,
        ExtraHeader  *  const   extHead)
{
    CONSTEXPR_VAR   size_t  FILE_HEADER_SIZE    =  sizeof(FileHeader);
    if ( cbBuf < FILE_HEADER_SIZE ) {
        return ( ERR_FAILURE );
    }

    const   unsigned  char  *
        ptrBuf  =  static_cast<const unsigned char *>(inBuf);

    ::memcpy(fileHead, ptrBuf, sizeof(FileHeader));
    const   HeaderItem  offsExtHead = fileHead->offsExtHead;
    const   HeaderItem  sizeExtHead = fileHead->sizeExtHead;
    if ( (sizeExtHead > 0) && (offsExtHead > 0) ) {
        ::memset(extHead, 0, sizeof(ExtraHeader));
        if ( cbBuf < (offsExtHead + sizeExtHead) ) {
            return ( ERR_FAILURE );
        }
        ::memcpy(extHead, ptrBuf + offsExtHead, sizeExtHead);
    }

    return ( ERR_SUCCESS );
}

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
