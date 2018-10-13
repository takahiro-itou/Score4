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
**      An Interface of TextParser class.
**
**      @file       Common/TextParser.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_TEXT_PARSER_H )
#    define   SCORE4CORE_COMMON_INCLUDED_TEXT_PARSER_H

#include    "Score4Types.h"

#include    <string>
#include    <vector>


SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    TextParser  class.
//

class  TextParser
{

//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     std::vector<char>           TextBuffer;

    typedef     std::vector<const char *>   TokenArray;

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
public:

    //----------------------------------------------------------------
    /**   文字列を指定した文字で分割する。
    **
    **  @param [in] inText    入力テキスト。
    **  @param [in] sepChar   区切り文字。
    **  @param[out] bufText   テキストバッファ。
    **  @return     トークンの配列。
    **/
    TokenArray
    splitText(
            const  std::string  &inText,
            const  char  *      sepChrs,
            TextBuffer   *      bufText);

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

//========================================================================
//
//    Member Variables.
//
private:

    TextBuffer      m_bufText;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   TextParserTest;
};

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
