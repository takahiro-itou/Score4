//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  The Score4 Core Library.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of TextParser class.
**
**      @file       Common/TextParser.cpp
**/

#include    "Score4Core/Common/TextParser.h"

#include    <string.h>


SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    TextParser  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

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
//    文字列を指定した文字で分割する。
//

ErrCode
TextParser::splitText(
        const  std::string  &inText,
        const  char  *      sepChrs,
        TextBuffer          &bufText,
        TokenArray          &vTokens)
{
    const   size_t  szText  = inText.size();
    bufText.clear();
    bufText.resize(szText + 1);
    char  *  const  ptrBuf  = &(bufText[0]);

    ::memcpy(ptrBuf, inText.c_str(), szText);
    ptrBuf[szText]  = '\0';

    char  *         pSaved  = nullptr;
    const  char  *  pToken  = nullptr;

#if defined( _WIN32 )
    pToken  = strtok_s(ptrBuf, sepChrs, &pSaved);
#else
    pToken  = strtok_r(ptrBuf, sepChrs, &pSaved);
#endif

    while ( pToken != nullptr ) {
        vTokens.push_back(pToken);
#if defined( _WIN32 )
        pToken  = strtok_s(ptrBuf, sepChrs, &pSaved);
#else
        pToken  = strtok_r(ptrBuf, sepChrs, &pSaved);
#endif
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END
