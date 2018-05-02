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
    return ( ErrCode::ERR_FAILURE );
}


}   //  End of namespace  Common
}   //  End of namespace  Score4Wrapper
