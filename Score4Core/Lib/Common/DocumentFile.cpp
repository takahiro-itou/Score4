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

#include    "Score4Core/Common/DateTimeFormat.h"
#include    "Score4Core/Common/ErrorDetectionCode.h"
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

namespace  {

CONSTEXPR_VAR   const   char  *
s_tblRecordFlagName[] = {
    "EMPTY",
    "SCHEDULE",
    "CANCEL",
    "RESULT"
};

/**
**    レコードのサイズ。
**/
CONSTEXPR_VAR   FileLength  RECORD_SIZE     =  28;

}   //  End of (Unnamed) namespace.

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
//    バイナリ形式で保存するのに必要な容量を計算する。
//

FileLength
DocumentFile::computeImageSize(
        const  ScoreDocument  & objDoc)
{
    CONSTEXPR_VAR   FileLength  FILE_HEADER_SIZE    =  sizeof(FileHeader);
    CONSTEXPR_VAR   FileLength  EXTRA_HEADER_SIZE   =  sizeof(ExtraHeader);

    const  LeagueIndex  numLeagues  =  objDoc.getNumLeagues();
    const  TeamIndex    numTeams    =  objDoc.getNumTeams();
    const  RecordIndex  numRecords  =  objDoc.getNumRecords();

    const  FileLength   sizeLeague  =  numLeagues * 128;

    const  FileLength   cbTeamGame  =  sizeof(HeaderItem) * numTeams * 2;
    const  FileLength   cbTeamInfo  =  cbTeamGame + 72;
    const  FileLength   cbTeamReqs  =  (cbTeamInfo + 127) & ~127;
    const  FileLength   sizeTeams   =  cbTeamReqs * numTeams;

    const  FileLength   cbSettings  =  192 + sizeLeague + sizeTeams;
    const  FileLength   cbRecords   =  numRecords * RECORD_SIZE;

    FileLength  cbTotal = 0;
    cbTotal += (FILE_HEADER_SIZE + EXTRA_HEADER_SIZE);
    cbTotal += cbSettings;
    cbTotal += cbRecords + 72;
    cbTotal += ErrorDetectionCode::CRC32_CODE_LENGTH;

    return ( cbTotal );
}

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

    ErrorDetectionCode  edc;
    edc.setupGenPoly(FILE_CRC32_GENPOLY);
    const  ErrorDetectionCode::EDCode
        valCRC  =  edc.checkCRC32(inBuf, cbBuf);
    std::cerr   <<  "FILE CRC = "
                <<  std::hex    <<  valCRC
                <<  std::endl;

    ptrDoc->clearDocument();
    ptrDoc->setLastImportDate(extHead.lastImport);

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
    ErrCode         retErr;
    FileHeader      fileHeader;
    ExtraHeader     extHeader;

    fileHeader.fSignature   = 0x4C435357;
    fileHeader.fVersion     = 0x00010000;
    fileHeader.headerID     = 0x00000000;
    fileHeader.headerGame   = 0x4C425342;
    fileHeader.headerSize   = sizeof(FileHeader);
    fileHeader.offsRecord   = sizeof(FileHeader) + sizeof(ExtraHeader);
    fileHeader.reserved06   = 0;
    fileHeader.reserved07   = 0;
    fileHeader.offsExtHead  = sizeof(FileHeader);
    fileHeader.sizeExtHead  = sizeof(ExtraHeader);
    fileHeader.reserved10   = 0;
    fileHeader.reserved11   = 0;
    fileHeader.reserved12   = 0;
    fileHeader.reserved13   = 0;
    fileHeader.reserved14   = 0;
    fileHeader.reserved15   = 0;

    extHeader.lastImport    = objDoc.getLastImportDate();
    ::memset(extHeader.hiReserved, 0, sizeof(extHeader.hiReserved));

    retErr  = writeFileHeader(fileHeader, extHeader, cbBuf, outBuf);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    LpByte  const   ptrBuf  =  static_cast<LpByte>(outBuf);
    FileLength      cbWrite =  0;

    retErr  = writeSettingBlock(
                    objDoc,
                    ptrBuf + fileHeader.offsRecord,
                    cbBuf  - fileHeader.offsRecord,
                    &cbWrite);
    if ( retErr != ERR_SUCCESS ) {
        return ( ERR_SUCCESS );
    }

    retErr  = writeRecordBlock(
                    objDoc,
                    ptrBuf + (fileHeader.offsRecord + cbWrite),
                    cbBuf  - (fileHeader.offsRecord + cbWrite),
                    &cbWrite);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    データをバイナリファイルに書き込む。
//

ErrCode
DocumentFile::saveToBinaryFile(
        const  ScoreDocument  & objDoc,
        const  std::string    & fileName)
{
    const   FileLength  cbOuts  = computeImageSize(objDoc);
    std::vector<BtByte> outBuf(cbOuts, 0);

    const  ErrCode
        retErr  = saveToBinaryBuffer(objDoc, &(outBuf[0]), cbOuts);

    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    FILE *  fp  = fopen(fileName.c_str(), "wb");
    if ( fp == NULL ) {
        return ( ERR_FILE_OPEN_ERROR );
    }
    if ( fwrite(&(outBuf[0]), 1, cbOuts, fp) != cbOuts ) {
        return ( ERR_FILE_IO_ERROR );
    }
    fclose(fp);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    データをテキストストリームに書き込む.
//

ErrCode
DocumentFile::saveToTextStream(
        const  ScoreDocument  & objDoc,
        std::ostream          & outStr)
{
    const  LeagueIndex  numLeagues  =  objDoc.getNumLeagues();
    const  TeamIndex    numTeams    =  objDoc.getNumTeams();
    const  RecordIndex  numRecords  =  objDoc.getNumRecords();

    outStr  <<  "# Settings";
    for ( LeagueIndex k = 0; k < numLeagues; ++ k ) {
        const   ScoreDocument::LeagueInfo   &
            leagueInfo  =  objDoc.getLeagueInfo(k);

        outStr  <<  "\nLeague,"   <<  k     <<  ','
                <<  leagueInfo.leagueName   <<  ','
                <<  leagueInfo.numPlayOff;
    }

    for ( TeamIndex i = 0; i < numTeams; ++ i ) {
        const   ScoreDocument::TeamInfo
            & teamInfo  =  objDoc.getTeamInfo(i);

        outStr  <<  "\nTeam,"   <<  i   <<  ','
                <<  teamInfo.leagueID   <<  ','
                <<  teamInfo.teamName;
        for ( Common::TeamIndex j = 0; j < numTeams; ++ j ) {
            outStr  <<  ','
                    <<  objDoc.getGameCount(i, j, Common::FILTER_HOME_GAMES);
        }
    }
    outStr  <<  std::endl;

    outStr  <<  "# Records,"    <<  numRecords
            <<  "\nDate,HomeTeam,Score,VisitorTeam,Status,";
    DateTimeFormat::TDateTime   dtVal;
    for ( RecordIndex r = 0; r < numRecords; ++ r ) {
        const   ScoreDocument::GameResult
            &grRec  = objDoc.getGameRecord(r);
        DateTimeFormat::getDateTimeFromSerial(grRec.recordDate,  &dtVal);
        outStr  <<  '\n'
                <<  (dtVal.year)    <<  '/'
                <<  (dtVal.month)   <<  '/'
                <<  (dtVal.day)     <<  ','
                <<  objDoc.getTeamInfo(grRec.homeTeam).teamName     <<  ','
                <<  (grRec.homeScore)       <<  " - "
                <<  (grRec.visitorScore)    <<  ','
                <<  objDoc.getTeamInfo(grRec.visitorTeam).teamName  <<  ','
                <<  s_tblRecordFlagName[grRec.eGameFlags];
    }
    outStr  <<  std::endl;

    return ( ERR_SUCCESS );
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
    CONSTEXPR_VAR   FileLength
            FILE_HEADER_SIZE  =  sizeof(FileHeader);
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

    DateSerial  lastActiveDate,  lastRecordDate;
    ::memcpy(&lastActiveDate,  ptrCur, sizeof(lastActiveDate));
    ptrCur  +=  sizeof(lastActiveDate);
    ::memcpy(&lastRecordDate,  ptrCur, sizeof(lastRecordDate));
    ptrCur  +=  sizeof(lastRecordDate);

    HeaderItem  fOptimized  =  BOOL_FALSE;
    ::memcpy(&fOptimized,  ptrCur, sizeof(fOptimized));
    ptrCur  +=  sizeof(fOptimized);

    ptrDoc->setLastActiveDate(lastActiveDate);
    ptrDoc->setLastRecordDate(lastRecordDate);

    ptrCur  +=  (sizeof(HeaderItem) * 12);

    ScoreDocument::GameResult   gameRecord;

    for ( GamesCount t = 0; t < numRecords; ++ t ) {
        const  unsigned  int  *  const  ptrU32
            =  pointer_cast<const  unsigned  int  *>(ptrCur);
        gameRecord.eGameFlags   = static_cast<RecordFlag>(ptrU32[0]);
        ::memcpy(&(gameRecord.recordDate), ptrU32 + 1, sizeof(DateSerial));
        gameRecord.visitorTeam  = ptrU32[3];
        gameRecord.homeTeam     = ptrU32[4];
        gameRecord.visitorScore = ptrU32[5];
        gameRecord.homeScore    = ptrU32[6];
        ptrDoc->appendGameRecord(gameRecord);
        ptrCur  +=  RECORD_SIZE;
    }

    (* cbRead)  =  static_cast<FileLength>(ptrCur - ptrBuf);
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

    const   FileLength  cbTeamGame
        =  sizeof(HeaderItem) * gameInfo.size();
    const   FileLength  cbTeamReqs
        =  sizeof(tmpTeamName) + cbTeamGame + sizeof(HeaderItem) * 2;
    if ( cbTeamReqs != cbTeamInfo ) {
        // std::cerr   <<  "# ERROR : Size Mismatch. "
        //             <<  "Expected = "   <<  cbTeamReqs
        //             <<  ", Record = "   <<  cbTeamInfo
        //             <<  std::endl;
        return ( ERR_FAILURE );
    }

    ptrDoc->resizeTeamInfos(numTeams);
    ptrDoc->initializeGameCountTable();
    for ( TeamIndex i = 0; i < numTeams; ++ i ) {
        ::memcpy(tmpTeamName,  ptrCur, sizeof(tmpTeamName));
        ptrCur  +=  sizeof(tmpTeamName);

        ::memcpy(tmpTeamInfo,  ptrCur, sizeof(tmpTeamInfo));
        ptrCur  +=  sizeof(tmpTeamInfo);

        ptrDoc->setTeamInfo(i, std::string(tmpTeamName), tmpTeamInfo[1]);

        ::memcpy(&(gameInfo[0]),  ptrCur,  cbTeamGame);
        ptrCur  +=  cbTeamGame;
        ptrCur  +=  cbTeamRsvd;
        for ( int j = 0; j < numTeams; ++ j ) {
            ptrDoc->setGameCount(i, j, gameInfo.at(j * 2 + 0) );
        }
    }

    (* cbRead)  =  static_cast<FileLength>(ptrCur - ptrBuf);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ファイルヘッダを書き込む。
//

ErrCode
DocumentFile::writeFileHeader(
        const   FileHeader    & fileHead,
        const   ExtraHeader   & extHead,
        const   FileLength      cbBuf,
        LpWriteBuf      const   outBuf)
{
    CONSTEXPR_VAR   FileLength
            FILE_HEADER_SIZE    =  sizeof(FileHeader);
    if ( cbBuf < FILE_HEADER_SIZE ) {
        return ( ERR_FAILURE );
    }

    const   LpByte  ptrBuf  =  static_cast<LpByte>(outBuf);

    ::memcpy(ptrBuf,  &fileHead, sizeof(FileHeader));
    const   HeaderItem  offsExtHead = fileHead.offsExtHead;
    const   HeaderItem  sizeExtHead = fileHead.sizeExtHead;
    if ( (sizeExtHead > 0) && (offsExtHead > 0) ) {
        if ( cbBuf < (offsExtHead + sizeExtHead) ) {
            return ( ERR_FAILURE );
        }
        ::memcpy(ptrBuf + offsExtHead, &extHead, sizeExtHead);
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    レコードブロックを書き込む。
//

ErrCode
DocumentFile::writeRecordBlock(
        const  ScoreDocument  & objDoc,
        LpWriteBuf      const   outBuf,
        const  FileLength       cbBuf,
        FileLength  *   const   cbWrite)
{
    LpByte  const   ptrBuf  =  static_cast<LpByte>(outBuf);
    LpByte          ptrCur  =  ptrBuf;

    const   GamesCount  numRecords  =  objDoc.getNumRecords();
    ::memcpy(ptrCur,  &numRecords, sizeof(numRecords));
    ptrCur  +=  sizeof(numRecords);

    const   DateSerial  lastActiveDate  =  objDoc.getLastActiveDate();
    const   DateSerial  lastRecordDate  =  objDoc.getLastRecordDate();
    const   HeaderItem  fOptimized      =  objDoc.getOptimizedFlag();

    ::memcpy(ptrCur,  &lastActiveDate,  sizeof(lastActiveDate));
    ptrCur  +=  sizeof(lastActiveDate);
    ::memcpy(ptrCur,  &lastRecordDate,  sizeof(lastRecordDate));
    ptrCur  +=  sizeof(lastRecordDate);

    ::memcpy(ptrCur,  &fOptimized, sizeof(fOptimized));
    ptrCur  +=  sizeof(fOptimized);

    ::memset(ptrCur,  0xFF,  sizeof(HeaderItem) * 12);
    ptrCur  +=  (sizeof(HeaderItem) * 12);

    for ( GamesCount t = 0; t < numRecords; ++ t ) {
        const   ScoreDocument::GameResult  &
            gameRecord  =  objDoc.getGameRecord(t);
        unsigned  int  *  const
                ptrU32  =  pointer_cast<unsigned  int  *>(ptrCur);
        ptrU32[ 0]  =  gameRecord.eGameFlags;
        ::memcpy(ptrU32 + 1, &(gameRecord.recordDate), sizeof(DateSerial));
        ptrU32[ 3]  =  gameRecord.visitorTeam;
        ptrU32[ 4]  =  gameRecord.homeTeam;
        ptrU32[ 5]  =  gameRecord.visitorScore;
        ptrU32[ 6]  =  gameRecord.homeScore;

        ptrCur  +=  RECORD_SIZE;
    }

    (*cbWrite)  =  static_cast<FileLength>(ptrCur - ptrBuf);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    設定ブロックを書き込む。
//

ErrCode
DocumentFile::writeSettingBlock(
        const  ScoreDocument  & objDoc,
        LpWriteBuf      const   outBuf,
        const  FileLength       cbBuf,
        FileLength  *   const   cbWrite)
{
    LpByte  const   ptrBuf  =  static_cast<LpByte>(outBuf);
    LpByte          ptrCur  =  ptrBuf;

    const  LeagueIndex  numLeagues  =  objDoc.getNumLeagues();
    const  TeamIndex    numTeams    =  objDoc.getNumTeams();
    std::vector<HeaderItem>     gameInfo(numTeams * 2);
    char        tmpTeamName[64];
    HeaderItem  tmpTeamInfo[2];

    const   FileLength  cbTeamGame
        =  sizeof(HeaderItem) * gameInfo.size();
    const   FileLength  cbTeamInfo
        =  sizeof(tmpTeamName) + cbTeamGame + sizeof(HeaderItem) * 2;
    const   FileLength  cbTeamReqs  =  (cbTeamInfo + 127) & ~127;
    const   FileLength  cbTeamRsvd  =  (cbTeamReqs - cbTeamInfo);

    HeaderItem  blockInfo[8];
    BtByte      dataTitle[152];

    ::memset(blockInfo, 0, sizeof(blockInfo));
    ::memset(dataTitle, 0, sizeof(dataTitle));

    blockInfo[0]    =  cbTeamInfo;
    blockInfo[1]    =  cbTeamRsvd;
    ::memcpy(ptrCur, blockInfo, sizeof(blockInfo));
    ptrCur  +=  sizeof(blockInfo);

    ::memcpy(ptrCur, dataTitle, sizeof(dataTitle));
    ptrCur  +=  sizeof(dataTitle);

    ::memcpy(ptrCur,  &numLeagues,  sizeof(numLeagues));
    ptrCur  +=  sizeof(numLeagues);
    ::memcpy(ptrCur,  &numTeams,    sizeof(numTeams)  );
    ptrCur  +=  sizeof(numTeams);

    //  リーグ情報を書き込む。  //
    for ( LeagueIndex k = 0; k < numLeagues; ++ k ) {
        const   ScoreDocument::LeagueInfo  &
            leagueInfo  =  objDoc.getLeagueInfo(k);
        char        tmpName[96];
        HeaderItem  tmpInfo[8];
        ::memset(tmpName, 0, sizeof(tmpName));
        ::memset(tmpInfo, 0, sizeof(tmpInfo));

        ::strcpy(tmpName, leagueInfo.leagueName.c_str());
        ::memcpy(ptrCur,  tmpName, sizeof(tmpName));
        ptrCur  +=  sizeof(tmpName);

        tmpInfo[0]  =  leagueInfo.numPlayOff;
        ::memcpy(ptrCur,  tmpInfo, sizeof(tmpInfo));
        ptrCur  +=  sizeof(tmpInfo);
    }

    //  チーム情報を書き込む。  //
    for ( TeamIndex i = 0; i < numTeams; ++ i ) {
        ::memset(tmpTeamName, 0, sizeof(tmpTeamName));
        ::memset(tmpTeamInfo, 0, sizeof(tmpTeamInfo));

        const   ScoreDocument::TeamInfo
            & teamInfo  =  objDoc.getTeamInfo(i);

        ::strcpy(tmpTeamName, teamInfo.teamName.c_str());
        ::memcpy(ptrCur, tmpTeamName, sizeof(tmpTeamName));
        ptrCur  +=  sizeof(tmpTeamName);

        tmpTeamInfo[0]  =  cbTeamReqs;
        tmpTeamInfo[1]  =  teamInfo.leagueID;
        ::memcpy(ptrCur, tmpTeamInfo, sizeof(tmpTeamInfo));
        ptrCur  +=  sizeof(tmpTeamInfo);

        for ( int j = 0; j < numTeams; ++ j ) {
            gameInfo.at(j * 2 + 0)  =  objDoc.getGameCount(i, j);
            gameInfo.at(j * 2 + 1)  =  objDoc.getGameCount(j, i);
        }
        ::memcpy(ptrCur, &(gameInfo[0]), cbTeamGame);
        ptrCur  +=  cbTeamGame;

        ::memset(ptrCur, 0, cbTeamRsvd);
        ptrCur  +=  cbTeamRsvd;
    }

    (*cbWrite)  =  static_cast<FileLength>(ptrCur - ptrBuf);
    return ( ERR_SUCCESS );
}

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
