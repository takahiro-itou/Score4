//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  The Score4 Core Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      インポートツールプログラム。
**
**      @file       Bin/ImportTool.cpp
**/

#include    "Score4Core/Common/Score4CoreSettings.h"

#include    "Score4Core/Common/DocumentFile.h"
#include    "Score4Core/Common/ScoreDocument.h"
#include    "Score4Core/Common/ScoreInterface.h"

#include    <iostream>

using   namespace   SCORE4_CORE_NAMESPACE;

void  writeCountedScores(
        const   Common::CountedScores & cs,
        std::ostream                  & outStr)
{
    outStr  <<  "Wons  : "  <<  (cs.numWons[Common::FILTER_ALL_GAMES])
            <<  " (H: "     <<  (cs.numWons[Common::FILTER_HOME_GAMES])
            <<  ", A: "     <<  (cs.numWons[Common::FILTER_AWAY_GAMES])
            <<  ")\n"
            <<  "Losts : "  <<  (cs.numLost[Common::FILTER_ALL_GAMES])
            <<  " (H: "     <<  (cs.numLost[Common::FILTER_HOME_GAMES])
            <<  ", A: "     <<  (cs.numLost[Common::FILTER_AWAY_GAMES])
            <<  ")\n"
            <<  "Draws : "  <<  (cs.numDraw[Common::FILTER_ALL_GAMES])
            <<  " (H: "     <<  (cs.numDraw[Common::FILTER_HOME_GAMES])
            <<  ", A: "     <<  (cs.numDraw[Common::FILTER_AWAY_GAMES])
            <<  ")\n"
            <<  "Ranks : "  <<  (cs.currentRank);
    outStr  <<  std::endl;
}


int  main(int argc, char * argv[])
{
    if ( argc <= 1 ) {
        return ( 1 );
    }

    Common::DocumentFile    docFile;
    Common::ScoreDocument   objDoc;
    Common::ErrCode         retErr;

    retErr  = docFile.readFromTextStream(std::cin, &objDoc);
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    retErr  = docFile.saveToTextStream(objDoc, std::cout);
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    std::vector<Common::CountedScores>  cs;
    retErr  = objDoc.countScores(-1, cs);

    const  Common::LeagueIndex  numLeagues  = objDoc.getNumLeagues();
    for ( Common::LeagueIndex i = 0; i < numLeagues; ++ i ) {
        objDoc.computeCurrentRank(i, cs);
    }
    for ( Common::LeagueIndex i = 0; i < numLeagues; ++ i ) {
        std::vector<Common::TeamIndex>  rank;
        Common::TeamIndex   numTeam = objDoc.computeRankOrder(cs, i, rank);
        std::cerr   <<  "League : "
                    <<  objDoc.getLeagueInfo(i).leagueName
                    <<  std::endl;
        for ( Common::TeamIndex j = 0; j < numTeam; ++ j ) {
            const   Common::TeamIndex   idxTrg  = rank[j];
            std::cerr   <<  "Team[" <<  idxTrg  <<  "] "
                        <<  objDoc.getTeamInfo(idxTrg).teamName
                        <<  std::endl;
            writeCountedScores(cs[idxTrg], std::cerr);
        }
    }

    retErr  = docFile.saveToBinaryFile(objDoc, "dummyout.bin");
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( 0 );
}
