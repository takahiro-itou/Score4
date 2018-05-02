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
            <<  ")\n";
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
    retErr  = docFile.readFromBinaryFile(argv[1], &objDoc);
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    retErr  = docFile.saveToTextStream(objDoc, std::cout);
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    std::vector<Common::CountedScores>  cs;
    retErr  = objDoc.countScores(-1, cs);
    std::cerr   <<  (cs.size())
                <<  " Teams Found"  <<  std::endl;
    for ( size_t i = 0; i < cs.size(); ++ i ) {
        std::cerr   <<  "Team[" <<  i   <<  "] "
                    <<  objDoc.getTeamInfo(i).teamName;
        writeCountedScores(cs[i], std::cerr);
    }

    retErr  = docFile.saveToBinaryFile(objDoc, "dummy.bin");
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( 0 );
}
