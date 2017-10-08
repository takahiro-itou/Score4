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
**      An Implementation of DocumentFile class.
**
**      @file       Common/DocumentFile.cpp
**/

#include    "Score4Core/Common/DocumentFile.h"

#include    "Score4Core/Common/ScoreDocument.h"

#include    <fcntl.h>
#include    <memory.h>
#include    <stdio.h>
#include    <sys/stat.h>
#include    <unistd.h>
#include    <vector>

#include    <iostream>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    DocumentFile  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

DocumentFile::DocumentFile()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

DocumentFile::~DocumentFile()
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
//    データをバイナリバッファから読み込む。
//

ErrCode
DocumentFile::readFromBinaryBuffer(
        const   LpcReadBuf  inBuf,
        const   FileLength  cbBuf,
        ScoreDocument  *    ptrDoc)
{
    ErrCode         retErr;
    FileHeader      fileHead;
    ExtraHeader     extHead;

    retErr  = readFileHeader(inBuf, cbBuf, &fileHead, &extHead);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    std::ostream  & outLog  =  std::cerr;
    outLog  <<  std::hex
            <<    "FileHead.Sigunature = "  <<  fileHead.fSignature
            <<  "\nFileHead.Version    = "  <<  fileHead.fVersion
            <<  "\nFileHead.HeaderID   = "  <<  fileHead.headerID
            <<  "\nFileHead.HeaderGame = "  <<  fileHead.headerGame
            <<  "\nFileHead.HeaderSize = "  <<  fileHead.headerSize
            <<  "\nFileHead.OffsRecord = "  <<  fileHead.offsRecord
            <<  "\nFileHead.OffsExHead = "  <<  fileHead.offsExtHead
            <<  "\nFileHead.SizeExHead = "  <<  fileHead.sizeExtHead
            <<  "\nExtHead.LastImport  = "  <<  extHead.lastImport
            <<  std::endl;

    ptrDoc->clearDocument();

    const  LpcByte  ptrBuf  =  static_cast<LpcByte>(inBuf);

    FileLength  cbRead  = 0;
    retErr  = readSettingBlock(
                    ptrBuf + fileHead.offsRecord,
                    cbBuf  - fileHead.offsRecord,
                    ptrDoc,  &cbRead);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    retErr  = readRecordBlock(
                    ptrBuf + fileHead.offsRecord + cbRead,
                    cbBuf  - fileHead.offsRecord - cbRead,
                    ptrDoc,  &cbRead);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    データをバイナリファイルから読み込む。
//

ErrCode
DocumentFile::readFromBinaryFile(
        const  std::string  &fileName,
        ScoreDocument  *    ptrDoc)
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

    const  ErrCode
        retErr  = readFromBinaryBuffer(&(buf[0]), cbFile, ptrDoc);

    return ( retErr );
}

//----------------------------------------------------------------
//    データをテキストストリームから読み込む。
//

ErrCode
DocumentFile::readFromTextStream(
        std::istream     &  inStr,
        ScoreDocument  *    ptrDoc)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをバイナリバッファに書き込む。
//

ErrCode
DocumentFile::saveToBinaryBuffer(
        const  ScoreDocument  & objDoc,
        LpWriteBuf  const       outBuf,
        const   FileLength      cbBuf)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをバイナリファイルに書き込む。
//

ErrCode
DocumentFile::saveToBinaryFile(
        const  ScoreDocument  & objDoc,
        const  std::string    & fileName)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをテキストストリームに書き込む.
//

ErrCode
DocumentFile::saveToTextStream(
        const  ScoreDocument  & objDoc,
        std::ostream          & outStr)
{
    return ( ERR_FAILURE );
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
//    ファイルヘッダを読み込む。
//

ErrCode
DocumentFile::readFileHeader(
        const   LpcReadBuf      inBuf,
        const   FileLength      cbBuf,
        FileHeader   *  const   fileHead,
        ExtraHeader  *  const   extHead)
{
    CONSTEXPR_VAR   size_t  FILE_HEADER_SIZE    =  sizeof(FileHeader);
    if ( cbBuf < FILE_HEADER_SIZE ) {
        return ( ERR_FAILURE );
    }

    const  LpcByte  ptrBuf  =  static_cast<LpcByte>(inBuf);

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

//----------------------------------------------------------------
//    レコードブロックを読み込む。
//

ErrCode
DocumentFile::readRecordBlock(
        const   LpcReadBuf  inBuf,
        const   FileLength  cbBuf,
        ScoreDocument  *    ptrDoc,
        FileLength  *       cbRead)
{
    const  LpcByte  ptrBuf  =  static_cast<LpcByte>(inBuf);
    LpcByte         ptrCur  =  ptrBuf;

    GamesCount  numRecords  = 0;
    ::memcpy(&numRecords,  ptrCur, sizeof(numRecords));
    ptrCur  +=  sizeof(numRecords);

    DateSerial  lastGameDate,  lastRecordDate;
    ::memcpy(&lastGameDate,    ptrCur, sizeof(lastGameDate)  );
    ptrCur  +=  sizeof(lastGameDate);
    ::memcpy(&lastRecordDate,  ptrCur, sizeof(lastRecordDate));
    ptrCur  +=  sizeof(lastRecordDate);

    HeaderItem  fOptimized  =  BOOL_FALSE;
    ::memcpy(&fOptimized,  ptrCur, sizeof(fOptimized));
    ptrCur  +=  sizeof(fOptimized);

    ptrCur  +=  (sizeof(HeaderItem) * 12);

    ScoreDocument::GameResult   gameRecord;

    std::ostream  & outLog  =  std::cerr;
    outLog  <<    "Number of Records = "    <<  numRecords
            <<  "\nSize of Record    = "    <<  sizeof(gameRecord)
            <<  "\nLastGameDate      = "    <<  lastGameDate
            <<  "\nLastRecordDate    = "    <<  lastRecordDate
            <<  std::endl;

    const   FileLength  RECORD_SIZE     =  28;
    for ( GamesCount t = 0; t < numRecords; ++ t ) {
        //::memcpy(&gameRecord,  ptrCur, sizeof(gameRecord));
        const  unsigned  int  *  const  ptrU32
            =  pointer_cast<const  unsigned  int  *>(ptrCur);
        gameRecord.eGameFlags   = static_cast<RecordFlag>(ptrU32[0]);
        ::memcpy(&(gameRecord.recordDate), ptrU32 + 1, sizeof(DateSerial));
        gameRecord.visitorTeam  = ptrU32[3];
        gameRecord.homeTeam     = ptrU32[4];
        gameRecord.visitorScore = ptrU32[5];
        gameRecord.homeScore    = ptrU32[6];
        ptrCur  +=  RECORD_SIZE;
    }

    (* cbRead)  =  static_cast<FileLength>(ptrCur - ptrBuf);

    outLog  <<  "The Read Size = "  <<  (* cbRead)
            <<  " Bytes."   <<  std::endl;


    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    設定ブロックを読み込む。
//

ErrCode
DocumentFile::readSettingBlock(
        const   LpcReadBuf  inBuf,
        const   FileLength  cbBuf,
        ScoreDocument  *    ptrDoc,
        FileLength  *       cbRead)
{
    const  LpcByte  ptrBuf  =  static_cast<LpcByte>(inBuf);
    LpcByte         ptrCur  =  ptrBuf;

    HeaderItem  blockInfo[8];
    ::memcpy(blockInfo,  ptrCur, sizeof(blockInfo));
    ptrCur  +=  sizeof(blockInfo);

    BtByte  dataTitle[152];
    ::memcpy(dataTitle,  ptrCur, sizeof(dataTitle));
    ptrCur  +=  sizeof(dataTitle);

    LeagueIndex     numLeagues;
    TeamIndex       numTeams;
    ::memcpy(&numLeagues,  ptrCur, sizeof(numLeagues));
    ptrCur  +=  sizeof(numLeagues);
    ::memcpy(&numTeams,    ptrCur, sizeof(numTeams)  );
    ptrCur  +=  sizeof(numTeams);

    std::ostream  & outLog  =  std::cerr;
    outLog  <<  std::dec    <<  "Setting.BlockInfo:"
            <<  "\nSetting.BlockInfo[0] = "     <<  blockInfo[0]
            <<  "\nSetting.BlockInfo[1] = "     <<  blockInfo[1]
            <<  "\nSetting.BlockInfo[2] = "     <<  blockInfo[2]
            <<  "\nSetting.BlockInfo[3] = "     <<  blockInfo[3]
            <<  "\nSetting.BlockInfo[4] = "     <<  blockInfo[4]
            <<  "\nSetting.BlockInfo[5] = "     <<  blockInfo[5]
            <<  "\nSetting.BlockInfo[6] = "     <<  blockInfo[6]
            <<  "\nSetting.BlockInfo[7] = "     <<  blockInfo[7]
            <<  "\nSetting.NumLeagues   = "     <<  numLeagues
            <<  "\nSetting.NumTeams     = "     <<  numTeams
            <<  std::endl;

    ScoreDocument::LeagueInfo   leagueInfo;
    for ( LeagueIndex k = 0; k < numLeagues; ++ k ) {
        char        tmpName[96];
        HeaderItem  tmpInfo[ 8];
        ::memcpy(tmpName,  ptrCur, sizeof(tmpName));
        ptrCur  +=  sizeof(tmpName);

        ::memcpy(tmpInfo,  ptrCur, sizeof(tmpInfo));
        ptrCur  +=  sizeof(tmpInfo);

        leagueInfo.leagueName   = std::string(tmpName);
        leagueInfo.numPlayOff   = tmpInfo[0];
        ptrDoc->appendLeagueInfo(leagueInfo);
    }

    const   FileLength  cbTeamInfo  =  blockInfo[0];
    const   FileLength  cbTeamRsvd  =  blockInfo[1];

    std::vector<HeaderItem>     gameInfo(numTeams * 2);
    char        tmpTeamName[64];
    HeaderItem  tmpTeamInfo[2];

    const   FileLength  cbTeamGame  =  sizeof(HeaderItem) * gameInfo.size();
    const   FileLength  cbTeamReqs
        =  sizeof(tmpTeamName) + cbTeamGame + sizeof(HeaderItem) * 2;
    if ( cbTeamReqs != cbTeamInfo ) {
        outLog  <<  "# ERROR : Size Mismatch. "
                <<  "Expected = "   <<  cbTeamReqs
                <<  ", Record = "   <<  cbTeamInfo
                <<  std::endl;
        return ( ERR_FAILURE );
    }

    for ( TeamIndex i = 0; i < numTeams; ++ i ) {
        ::memcpy(tmpTeamName,  ptrCur, sizeof(tmpTeamName));
        ptrCur  +=  sizeof(tmpTeamName);

        ::memcpy(tmpTeamInfo,  ptrCur, sizeof(tmpTeamInfo));
        ptrCur  +=  sizeof(tmpTeamInfo);

        ptrDoc->appendTeamInfo(tmpTeamInfo[1], std::string(tmpTeamName));

        ::memcpy(&(gameInfo[0]),  ptrCur,  cbTeamGame);
        ptrCur  +=  cbTeamGame;
        ptrCur  +=  cbTeamRsvd;
    }

    (* cbRead)  =  static_cast<FileLength>(ptrCur - ptrBuf);
    outLog  <<  "The Read Size = "  <<  (* cbRead)
            <<  " Bytes."   <<  std::endl;

    return ( ERR_SUCCESS );
}

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
