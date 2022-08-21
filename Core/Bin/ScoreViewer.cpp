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
**      ビューワープログラム。
**
**      @file       Bin/ScoreView.cpp
**/

#include    "Score4Core/Common/Score4CoreSettings.h"

#include    "Score4Core/Common/ScoreInterface.h"

#include    "Score4Core/Document/DocumentFile.h"
#include    "Score4Core/Document/ScoreDocument.h"

#include    <iostream>

using   namespace   SCORE4_CORE_NAMESPACE;

void  writeCountedScores(
        const   Common::CountedScores & cs,
        std::ostream                  & outStr)
{
    outStr  <<  "Wons  : "  <<  (cs.numWons[FILTER_ALL_GAMES])
            <<  " (H: "     <<  (cs.numWons[FILTER_HOME_GAMES])
            <<  ", A: "     <<  (cs.numWons[FILTER_AWAY_GAMES])
            <<  ")\n"
            <<  "Losts : "  <<  (cs.numLost[FILTER_ALL_GAMES])
            <<  " (H: "     <<  (cs.numLost[FILTER_HOME_GAMES])
            <<  ", A: "     <<  (cs.numLost[FILTER_AWAY_GAMES])
            <<  ")\n"
            <<  "Draws : "  <<  (cs.numDraw[FILTER_ALL_GAMES])
            <<  " (H: "     <<  (cs.numDraw[FILTER_HOME_GAMES])
            <<  ", A: "     <<  (cs.numDraw[FILTER_AWAY_GAMES])
            <<  ")\n"
            <<  "Ranks : "  <<  (cs.currentRank);
    outStr  <<  std::endl;
}

void  writeGameCountTable(
        const  Document::ScoreDocument  & scoreData,
        std::ostream                    & outStr)
{
    const   TeamIndex  numTeam  = scoreData.getNumTeams();
    for ( int i = 0; i < numTeam; ++ i ) {
        const   Document::ScoreDocument::TeamInfo   &
            teamInfo    = scoreData.getTeamInfo(i);
        outStr  <<  "Team[" <<  i   <<  "] "
                <<  teamInfo.teamName   <<  "\t:";
        for ( int j = 0; j < numTeam; ++ j ) {
            outStr  <<  teamInfo.gameCounts.at(j)[FILTER_ALL_GAMES]
                    <<  ", ";
        }
        outStr  <<  std::endl;
    }
}

void  writeRestGameTable(
        const   TeamIndex               numTeam,
        const   Common::CountedScores   & cs,
        std::ostream                    & outStr)
{
    for ( int j = 0; j < numTeam; ++ j ) {
        outStr  <<  (cs.restGames.at(j)[FILTER_ALL_GAMES])
                <<  " (H: " <<  (cs.restGames[j][FILTER_HOME_GAMES])
                <<  ", A: " <<  (cs.restGames[j][FILTER_AWAY_GAMES])
                <<  "), ";
    }
    outStr  <<  std::endl;
}

int  main(int argc, char * argv[])
{
    if ( argc <= 1 ) {
        return ( 1 );
    }

    Document::DocumentFile  docFile;
    Document::ScoreDocument objDoc;
    ErrCode                 retErr;
    retErr  = docFile.readFromBinaryFile(argv[1], &objDoc);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    retErr  = docFile.saveToTextStream(objDoc, std::cout);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    std::vector<Common::CountedScores>  cs;
    try {
        retErr  = objDoc.countScores(-1, cs);
    } catch ( std::exception & e ) {
        std::cerr   <<  e.what()    <<  std::endl;
        return ( ERR_FAILURE );
    }

    const  LeagueIndex  numLeagues  = objDoc.getNumLeagues();
    for ( LeagueIndex i = 0; i < numLeagues; ++ i ) {
        objDoc.computeCurrentRank(i, cs);
    }
    for ( LeagueIndex i = 0; i < numLeagues; ++ i ) {
        std::vector<TeamIndex>  rank;
        TeamIndex   numTeam = objDoc.computeRankOrder(cs, i, rank);
        std::cerr   <<  "League : "
                    <<  objDoc.getLeagueInfo(i).leagueName
                    <<  std::endl;
        for ( TeamIndex j = 0; j < numTeam; ++ j ) {
            const   TeamIndex   idxTrg  = rank[j];
            std::cerr   <<  "Team[" <<  idxTrg  <<  "] "
                        <<  objDoc.getTeamInfo(idxTrg).teamName
                        <<  std::endl;
            writeCountedScores(cs[idxTrg], std::cerr);
            writeRestGameTable(
                    objDoc.getNumTeams(), cs[idxTrg], std::cerr);
        }
    }

    writeGameCountTable(objDoc, std::cerr);

    retErr  = docFile.saveToBinaryFile(objDoc, "dummy.bin");
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( 0 );
}
