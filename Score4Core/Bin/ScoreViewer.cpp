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

#include    <iostream>

using   namespace   SCORE4_CORE_NAMESPACE;

int  main(int argc, char * argv[])
{
    if ( argc <= 1 ) {
        return ( 1 );
    }

    Common::DocumentFile    docFile;
    Common::ErrCode         retErr;
    retErr  = docFile.readFromBinaryFile(argv[1]);
    if ( retErr != Common::ERR_SUCCESS )
    {
        return ( retErr );
    }

    return ( 0 );
}
