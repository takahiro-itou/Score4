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
**      An Implementation of DocumentFile class.
**
**      @file       Document/DocumentFile.cpp
**/

#include    "Score4Core/Document/DocumentFile.h"

#include    "Score4Core/Document/ScoreDocument.h"

#include    "Score4Core/Common/DateTimeFormat.h"
#include    "Score4Core/Common/ErrorDetectionCode.h"
#include    "Score4Core/Common/TextParser.h"

#include    <fcntl.h>
#include    <memory.h>
#include    <stdexcept>
#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/stat.h>

#if defined( _MSC_VER )
#    include    <io.h>
#else
#    include    <unistd.h>
#endif

#include    <vector>

#include    <iostream>


#define     HELPER_UNUSED_VARIABLE(var)     (void)(var)

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Document  {

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

//----------------------------------------------------------------
/**   安全な文字列コピー関数。
**
**  @tparam N   コピー先の配列のサイズ。
**  @param[out] dest    コピー先の文字配列 (の参照) 。
**  @param [in] src     コピー元の文字列。
**  @return     コピー先の先頭アドレスを返す。
**/

template <size_t N>
inline  char *
my_safe_strcpy(char (&dest)[N], const char *src)
{

#if !defined( SCORE4_USE_PRE_CONFIGURED_MSVC )
    ::strncpy(dest, src, N);
#else
    errno_t ret = ::strcpy_s(dest, src);
#endif
    dest[N - 1] = '\0';
    return ( dest );
}

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
        const  ScoreDocument  & objDoc,
        BlockSizeInfo  *        bsInfo)
{
    CONSTEXPR_VAR   FileLength  FILE_HEADER_SIZE    =  sizeof(FileHeader);
    CONSTEXPR_VAR   FileLength  EXTRA_HEADER_SIZE   =  sizeof(ExtraHeader);

    const  LeagueIndex  numLeagues  =  objDoc.getNumLeagues();
    const  TeamIndex    numTeams    =  objDoc.getNumTeams();
    const  RecordIndex  numRecords  =  objDoc.getNumRecords();

    const  FileLength   cbTeamGame  =  sizeof(HeaderItem) * numTeams * 2;
    const  FileLength   cbTeamInfo  =  cbTeamGame + 72;
    const  FileLength   cbTeamReqs  =  (cbTeamInfo + 127) & ~127;

    bsInfo->cbLeague    =  128;
    bsInfo->cbTeamGame  =  cbTeamGame;
    bsInfo->cbTeamInfo  =  cbTeamInfo;
    bsInfo->cbTeamRsvd  =  (cbTeamReqs - cbTeamInfo);
    bsInfo->cbTeamReqs  =  cbTeamReqs;
    bsInfo->cbRecsHead  =  72;
    bsInfo->cbRecsBody  =  (RECORD_SIZE * numRecords);

    const  FileLength   sizeLeague  =  (bsInfo->cbLeague) * numLeagues;
    const  FileLength   sizeTeams   =  (bsInfo->cbTeamReqs) * numTeams;

    bsInfo->bsLeagure   =  sizeLeague;
    bsInfo->bsTeamInfo  =  sizeTeams ;

    FileLength  cbTotal = 0;

    cbTotal +=  bsInfo->bsFileHead  =  FILE_HEADER_SIZE;
    cbTotal +=  bsInfo->bsExtHead   =  EXTRA_HEADER_SIZE;
    cbTotal +=  bsInfo->bsSettings  =  192 + (sizeLeague) + (sizeTeams);
    cbTotal +=  bsInfo->bsRecords
            =   (bsInfo->cbRecsHead) + (bsInfo->cbRecsBody);
    cbTotal +=  Common::ErrorDetectionCode::CRC32_CODE_LENGTH;
    bsInfo->bsFileSize  =  cbTotal;

    return ( cbTotal );
}

//----------------------------------------------------------------
//    レコードをテキストストリームからインポートする。
//

ErrCode
DocumentFile::importRecordFromTextStream(
        std::istream     &  inStr,
        ScoreDocument  *    ptrDoc)
{
    ErrCode         retErr;
    GameResultList  gameResults;

    gameResults.clear();
    retErr  = readRecordFromTextStream(* ptrDoc, inStr, gameResults);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    const   GameResultList::const_iterator  itrEnd  = gameResults.end();
    for ( GameResultList::const_iterator
            itr = gameResults.begin(); itr != itrEnd; ++ itr )
    {
        ptrDoc->appendGameRecord(*itr);
    }

    return ( retErr );
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
    typedef     Common::ErrorDetectionCode      ErrorDetectionCode;

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
    HELPER_UNUSED_VARIABLE(valCRC);
    // std::cerr   <<  "FILE CRC = "
    //             <<  std::hex    <<  valCRC
    //             <<  std::endl;

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
#if defined( _MSC_VER )
    FILE *  fp  = fopen(fileName.c_str(), "rb");
    if ( fp == NULL ) {
        return ( ERR_FILE_OPEN_ERROR );
    }

    ::fseek(fp, 0, SEEK_END);
    const   FileLength  cbFile  = ::ftell(fp);
    ::fseek(fp, 0, SEEK_SET);

    std::vector<unsigned char>  buf(cbFile);
    if ( fread(&(buf[0]), 1, cbFile, fp) != cbFile )
    {
        ::fclose(fp);
        return ( ERR_FILE_IO_ERROR );
    }
    ::fclose(fp);

    const  ErrCode
        retErr  = readFromBinaryBuffer(&(buf[0]), cbFile, ptrDoc);
#else
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
#endif
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
    typedef     Common::DateTimeFormat          DateTimeFormat;
    typedef     Common::TextParser              TextParser;
    typedef     std::vector<GameCountList>      GameCountBuffer;

    std::string             strLine;
    TextParser::TextBuffer  bufText;
    TextParser::TokenArray  vTokens;
    GameCountBuffer         bufCnts;
    ErrCode                 retErr;
    DateSerial              serDate;

    bufCnts.clear();
    vTokens.reserve(32);

    for (;;) {
        if ( !inStr ) {
            break;
        }
        std::getline(inStr, strLine);

        if ( strLine.empty() ) {
            //  空行スキップ。  //
            continue;
        }

        vTokens.clear();
        TextParser::splitText(strLine, ",", bufText, vTokens);

        if ( strLine == std::string("# Settings") )  {
            continue;
        }
        if ( strcmp(vTokens[0], "# Records") == 0 ) {
            break;
        }

        if ( strcmp(vTokens[0], "# LastImportDate") == 0 ) {
            serDate = DateTimeFormat::getSerialFromString(vTokens[1]);
            ptrDoc->setLastImportDate(serDate);
            continue;
        }
        if ( strcmp(vTokens[0], "# LastActiveDate") == 0 ) {
            serDate = DateTimeFormat::getSerialFromString(vTokens[1]);
            ptrDoc->setLastActiveDate(serDate);
            continue;
        }
        if ( strcmp(vTokens[0], "# LastRecordDate") == 0 ) {
            serDate = DateTimeFormat::getSerialFromString(vTokens[1]);
            ptrDoc->setLastRecordDate(serDate);
            continue;
        }
        if ( strcmp(vTokens[0], "# OptimizedFlag" ) == 0 ) {
            ptrDoc->setOptimizedFlag(
                    atoi(vTokens[1]) != 0 ? BOOL_TRUE : BOOL_FALSE
            );
            continue;
        }

        if ( vTokens[0] == std::string("League") ) {
            ScoreDocument::LeagueInfo   leagueInfo;
            leagueInfo.leagueName   = std::string(vTokens[2]);
            leagueInfo.numPlayOff   = atoi(vTokens[3]);
            ptrDoc->appendLeagueInfo(leagueInfo);
        } else if ( vTokens[0] == std::string("Team") ) {
            ScoreDocument::TeamInfo     teamInfo;
            TeamIndex   teamID  = atoi(vTokens[1]);
            teamInfo.leagueID   = atoi(vTokens[2]);
            teamInfo.teamName   = std::string(vTokens[3]);
            if ( static_cast<TeamIndex>(bufCnts.size()) <= teamID ) {
                bufCnts.resize(teamID + 1);
            }
            GameCountList & gcInfo  = bufCnts[teamID];
            const   size_t  numCol  = vTokens.size() - 4;
            gcInfo.resize(numCol);
            for ( size_t idx = 0; idx < numCol; ++ idx ) {
                gcInfo[idx] = atoi(vTokens[idx + 4]);
            }
            ptrDoc->appendTeamInfo(teamInfo);
        } else {
            throw  std::runtime_error("Invalid Format.");
        }
    }

    const  TeamIndex   numTeams = ptrDoc->getNumTeams();
    ptrDoc->initializeGameCountTable();
    for ( TeamIndex i = 0; i < numTeams; ++ i ) {
        for ( TeamIndex j = 0; j < numTeams; ++ j ) {
            ptrDoc->setGameCount(i, j, bufCnts[i][j]);
        }
    }

    GameResultList  gameResults;
    gameResults.clear();
    retErr  = readRecordFromTextStream(* ptrDoc, inStr, gameResults);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    const   GameResultList::const_iterator  itrEnd  = gameResults.end();
    for ( GameResultList::const_iterator
            itr = gameResults.begin(); itr != itrEnd; ++ itr )
    {
        ptrDoc->appendGameRecord(*itr);
    }

    return ( retErr );
}

//----------------------------------------------------------------
//    レコード部をテキストストリームから読み込む。
//

ErrCode
DocumentFile::readRecordFromTextStream(
        const  ScoreDocument  & objDoc,
        std::istream          & inStr,
        GameResultList        & outRec)
{
    typedef     Common::TextParser      TextParser;

    std::string             strLine;
    TextParser::TextBuffer  bufText;
    TextParser::TokenArray  vTokens;
    ErrCode                 retErr;

    vTokens.reserve(16);

    ScoreDocument::GameResult   gameRecord;

    for (;;) {
        if ( !inStr ) {
            break;
        }
        std::getline(inStr, strLine);

        if ( strLine.empty() ) {
            //  空行スキップ。  //
            continue;
        }

        vTokens.clear();
        TextParser::splitText(strLine, ",-", bufText, vTokens);

        if ( strcmp(vTokens[0], "# Records") == 0 ) {
            //  無視する。  //
            continue;
        }

        if ( strcmp(vTokens[0], "Date") == 0 ) {
            //  ヘッダ行。  //
            continue;
        }

        if ( (strcmp(vTokens[5], "SCHEDULE") == 0)
                || (vTokens[5][0] == '\0') )
        {
            gameRecord.eGameFlags   = GAME_SCHEDULE;
        } else if ( (strcmp(vTokens[5], "CANCEL") == 0)
                || (strcmp(vTokens[5], "中止") == 0) )
        {
            gameRecord.eGameFlags   = GAME_CANCEL;
        } else if ( (strcmp(vTokens[5], "RESULT") == 0)
                || (strcmp(vTokens[5], "結果") == 0) )
        {
            gameRecord.eGameFlags   = GAME_RESULT;
        }

        int     dtYear  = 0;
        int     dtMonth = 0;
        int     dtDay   = 0;
        retErr  = TextParser::parseDateString(
                        std::string(vTokens[0]),
                        &dtYear, &dtMonth, &dtDay);
        if ( retErr != ERR_SUCCESS ) {
            return ( retErr );
        }

        gameRecord.recordDate   = Common::DateTimeFormat::getSerialFromDate(
                dtYear, dtMonth, dtDay);

        gameRecord.visitorTeam  = objDoc.findTeamInfo(vTokens[4]);
        gameRecord.homeTeam     = objDoc.findTeamInfo(vTokens[1]);
        gameRecord.visitorScore = atoi(vTokens[3]);
        gameRecord.homeScore    = atoi(vTokens[2]);

        outRec.push_back(gameRecord);
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    データをバイナリバッファに書き込む。
//

ErrCode
DocumentFile::saveToBinaryBuffer(
        const  ScoreDocument  & objDoc,
        const  BlockSizeInfo  * bsInfo,
        LpWriteBuf  const       outBuf,
        const   FileLength      cbBuf)
{
    typedef     Common::ErrorDetectionCode      ErrorDetectionCode;

    BlockSizeInfo   tmpBsInfo;
    ErrCode         retErr;
    FileHeader      fileHeader;
    ExtraHeader     extHeader;

    if ( bsInfo == nullptr ) {
        computeImageSize(objDoc,  &tmpBsInfo);
        bsInfo  =  &tmpBsInfo;
    }

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
                    * bsInfo,
                    ptrBuf + fileHeader.offsRecord,
                    cbBuf  - fileHeader.offsRecord,
                    fileHeader.offsRecord,
                    &cbWrite);
    if ( retErr != ERR_SUCCESS ) {
        return ( ERR_SUCCESS );
    }

    const   FileLength  cbRecs
        =  cbBuf - (fileHeader.offsRecord + cbWrite)
        -  ErrorDetectionCode::CRC32_CODE_LENGTH;
    retErr  = writeRecordBlock(
                    objDoc,
                    ptrBuf + (fileHeader.offsRecord + cbWrite),
                    cbRecs,
                    &cbWrite);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }
    if ( cbWrite != cbRecs ) {
        return ( ERR_INDEX_OUT_OF_RANGE );
    }

    //  誤り検出符号。  //
    ErrorDetectionCode  edc;
    edc.setupGenPoly(FILE_CRC32_GENPOLY);
    edc.writeCRC32(outBuf,  cbBuf);

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
    BlockSizeInfo       bsInfo;
    const   FileLength  cbOuts  = computeImageSize(objDoc,  &bsInfo);
    std::vector<BtByte> outBuf(cbOuts, 0);

    const  ErrCode
        retErr  = saveToBinaryBuffer(
                        objDoc, &bsInfo, &(outBuf[0]), cbOuts);

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
    typedef     Common::DateTimeFormat      DateTimeFormat;

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
        for ( TeamIndex j = 0; j < numTeams; ++ j ) {
            outStr  <<  ','
                    <<  objDoc.getGameCount(i, j, FILTER_HOME_GAMES);
        }
    }
    outStr  <<  std::endl;

    outStr  <<  "# LastImportDate,"
            <<  DateTimeFormat::toString(objDoc.getLastImportDate())
            <<  ","
            <<  objDoc.getLastImportDate()  <<  "\n"

            <<  "# LastActiveDate,"
            <<  DateTimeFormat::toString(objDoc.getLastActiveDate())
            <<  ","
            <<  objDoc.getLastActiveDate()  <<  "\n"

            <<  "# LastRecordDate,"
            <<  DateTimeFormat::toString(objDoc.getLastRecordDate())
            <<  ","
            <<  objDoc.getLastRecordDate()  <<  "\n"

            <<  "# OptimizedFlag,"
            <<  objDoc.getOptimizedFlag ()  <<  std::endl;

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

    ptrDoc->setOptimizedFlag (fOptimized ? BOOL_TRUE : BOOL_FALSE);
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
        const  BlockSizeInfo  & bsInfo,
        LpWriteBuf      const   outBuf,
        const  FileLength       cbBuf,
        const  FileLength       fStart,
        FileLength  *   const   cbWrite)
{
    LpByte  const   ptrBuf  =  static_cast<LpByte>(outBuf);
    LpByte          ptrCur  =  ptrBuf;

    const  LeagueIndex  numLeagues  =  objDoc.getNumLeagues();
    const  TeamIndex    numTeams    =  objDoc.getNumTeams();
    std::vector<HeaderItem>     gameInfo(numTeams * 2);
    char        tmpTeamName[64];
    HeaderItem  tmpTeamInfo[2];

    // const   FileLength  cbTeamGame
    //     =  sizeof(HeaderItem) * gameInfo.size();
    // const   FileLength  cbTeamInfo
    //     =  sizeof(tmpTeamName) + cbTeamGame + sizeof(HeaderItem) * 2;
    // const   FileLength  cbTeamReqs  =  (cbTeamInfo + 127) & ~127;
    // const   FileLength  cbTeamRsvd  =  (cbTeamReqs - cbTeamInfo);

    HeaderItem  blkInfo [8];
    BtByte      docTitle[152];

    ::memset(blkInfo,  0, sizeof(blkInfo) );
    ::memset(docTitle, 0, sizeof(docTitle));

    blkInfo[0]  =  static_cast<HeaderItem>(bsInfo.cbTeamInfo);
    blkInfo[1]  =  static_cast<HeaderItem>(bsInfo.cbTeamRsvd);
    blkInfo[2]  =  static_cast<HeaderItem>(bsInfo.cbTeamReqs);
    blkInfo[3]  =  0;
    blkInfo[4]  =  static_cast<HeaderItem>(bsInfo.bsSettings);
    blkInfo[5]  =  static_cast<HeaderItem>(fStart + blkInfo[4]);
    ::memcpy(ptrCur, blkInfo, sizeof(blkInfo));
    ptrCur  +=  sizeof(blkInfo);

    ::memcpy(ptrCur, docTitle, sizeof(docTitle));
    ptrCur  +=  sizeof(docTitle);

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

        my_safe_strcpy(tmpName, leagueInfo.leagueName.c_str());
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

        my_safe_strcpy(tmpTeamName, teamInfo.teamName.c_str());
        ::memcpy(ptrCur, tmpTeamName, sizeof(tmpTeamName));
        ptrCur  +=  sizeof(tmpTeamName);

        tmpTeamInfo[0]  =  static_cast<HeaderItem>(bsInfo.cbTeamReqs);
        tmpTeamInfo[1]  =  teamInfo.leagueID;
        ::memcpy(ptrCur, tmpTeamInfo, sizeof(tmpTeamInfo));
        ptrCur  +=  sizeof(tmpTeamInfo);

        for ( int j = 0; j < numTeams; ++ j ) {
            gameInfo.at(j * 2 + 0)  =  objDoc.getGameCount(i, j);
            gameInfo.at(j * 2 + 1)  =  objDoc.getGameCount(j, i);
        }
        ::memcpy(ptrCur, &(gameInfo[0]), bsInfo.cbTeamGame);
        ptrCur  +=  (bsInfo.cbTeamGame);

        ::memset(ptrCur, 0, bsInfo.cbTeamRsvd);
        ptrCur  +=  (bsInfo.cbTeamRsvd);
    }

    (*cbWrite)  =  static_cast<FileLength>(ptrCur - ptrBuf);
    return ( ERR_SUCCESS );
}

}   //  End of namespace  Document
SCORE4_CORE_NAMESPACE_END
