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
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    retErr  = docFile.saveToTextStream(objDoc, std::cout);
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    retErr  = docFile.saveToBinaryFile(objDoc, "dummy.bin");
    if ( retErr != Common::ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( 0 );
}
