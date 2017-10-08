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
**      ビューワープログラム。
**
**      @file       Bin/ScoreView.cpp
**/

#include    "Score4Core/Common/Score4CoreSettings.h"

#include    "Score4Core/Common/DocumentFile.h"
#include    "Score4Core/Common/ScoreDocument.h"

#include    <iostream>

using   namespace   SCORE4_CORE_NAMESPACE;

int  main(int argc, char * argv[])
{
    if ( argc <= 1 ) {
        return ( 1 );
    }

    Common::DocumentFile    docFile;
    Common::ScoreDocument   objDoc;
    Common::ErrCode         retErr;
    retErr  = docFile.readFromBinaryFile(argv[1], &objDoc);
    if ( retErr != Common::ERR_SUCCESS )
    {
        return ( retErr );
    }

    const  Common::LeagueIndex  numLeagues  =  objDoc.getNumLeagues();
    const  Common::TeamIndex    numTeams    =  objDoc.getNumTeams();

    std::ostream  & outLog  =  std::cout;

    outLog  <<  "League Informations:"
            <<  "\nNumber of Leagues  = "   <<  (numLeagues);
    for ( Common::LeagueIndex k = 0; k < numLeagues; ++ k ) {
        const   Common::ScoreDocument::LeagueInfo   &
            leagueInfo  =  objDoc.getLeagueInfo(k);

        outLog  <<  "\nLeague ["    <<  k
                <<  "] Name    = "  <<  leagueInfo.leagueName
                <<  "\nLeague ["    <<  k
                <<  "] Playoff = "  <<  leagueInfo.numPlayOff;
    }
    outLog  <<  std::endl;

    outLog  <<  "Team Informations:"
            <<  "\nNumber of Teams    = "   <<  (numTeams);
    outLog.flush();

    for ( Common::TeamIndex i = 0; i < numTeams; ++ i ) {
        const   Common::ScoreDocument::TeamInfo  &
            teamInfo    =  objDoc.getTeamInfo(i);

        outLog  <<  "\nTeam ["      <<  i
                <<  "] Name    = "  <<  teamInfo.teamName
                <<  "\nTeam ["      <<  i
                <<  "] LeagueID = " <<  teamInfo.leagueID
                <<  "\t"
                <<  objDoc.getLeagueInfo(teamInfo.leagueID).leagueName;
    }

    outLog  <<  std::endl;

    return ( 0 );
}
