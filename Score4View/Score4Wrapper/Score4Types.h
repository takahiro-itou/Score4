//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Score4 Wrapper  Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      Type Definitions.
**
**      @file       Score4Types.h
**/

#pragma     once

#include    "Score4Core/Common/Score4Types.h"


namespace  Score4Wrapper  {
namespace  Common  {

public enum  class  ErrCode
{
    ERR_SUCCESS             = Score4Core::Common::ERR_SUCCESS,
    ERR_FAILURE             = Score4Core::Common::ERR_FAILURE,
    ERR_FILE_OPEN_ERROR     = Score4Core::Common::ERR_FILE_OPEN_ERROR,
    ERR_FILE_IO_ERROR       = Score4Core::Common::ERR_FILE_IO_ERROR,
    ERR_INDEX_OUT_OF_RANGE  = Score4Core::Common::ERR_INDEX_OUT_OF_RANGE
};

typedef     Score4Core::Common::Boolean         Boolean;

typedef     Score4Core::Common::RecordFlag      RecordFlag;
typedef     Score4Core::Common::GameFilter      GameFilter;

typedef     Score4Core::Common::DateSerial      DateSerial;
typedef     Score4Core::Common::TeamIndex       TeamIndex;
typedef     Score4Core::Common::LeagueIndex     LeagueIndex;
typedef     Score4Core::Common::GamesCount      GamesCount;
typedef     Score4Core::Common::RecordIndex     RecordIndex;
typedef     Score4Core::Common::ScoreValue      ScoreValue;
typedef     Score4Core::Common::FileLength      FileLength;

}   //  End of namespace  Common
}   //  End of namespace  Score4Wrapper
