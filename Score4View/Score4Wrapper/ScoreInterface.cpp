//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
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
**      @file       ScoreInterface.cpp
**/

#include    "StdAfx.h"

#include    "ScoreInterface.h"
#include    "Score4Types.h"

namespace  Score4Wrapper  {
namespace  Common  {

//----------------------------------------------------------------
//    アンマネージ型をマネージ型に変換する。
//

ErrCode
copyToManageType(
        const  Score4Core::Common::CountedScores  & csSrc,
        Score4Wrapper::Common::CountedScores      ^ csTrg)
{
    csTrg->numWons      = copyToManageArray(csSrc.numWons);
    csTrg->numLost      = copyToManageArray(csSrc.numLost);
    csTrg->numDraw      = copyToManageArray(csSrc.numDraw);
    csTrg->numGames     = copyToManageArray(csSrc.numGames);
    csTrg->vsWons       = copyToManageTable(csSrc.vsWons);
    csTrg->vsLost       = copyToManageTable(csSrc.vsLost);
    csTrg->vsDraw       = copyToManageTable(csSrc.vsDraw);
    csTrg->restGames    = copyToManageTable(csSrc.restGames);

    csTrg->numLeagueRestGames
            = copyToManageArray(csSrc.numLeagueRestGames);
    csTrg->numInterRestGames
            = copyToManageArray(csSrc.numInterRestGames);
    csTrg->numTotalRestGames
            = copyToManageArray(csSrc.numTotalRestGames);

    csTrg->currentRank  = csSrc.currentRank;

    csTrg->totalGotScores
            = copyToManageArray(csSrc.totalGotScores);
    csTrg->totalLostScores
            = copyToManageArray(csSrc.totalLostScores);
    csTrg->vsGotScores  = copyToManageTable(csSrc.vsGotScores);
    csTrg->vsLostScores = copyToManageTable(csSrc.vsLostScores);

    return ( ErrCode::ERR_SUCCESS );
}


}   //  End of namespace  Common
}   //  End of namespace  Score4Wrapper
