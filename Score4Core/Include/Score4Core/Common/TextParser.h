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
public:

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
    **  @param[out] vTokens   分割結果を追記する変数。
    **      必要なら呼び出す前に内容をクリアする。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    splitText(
            const  std::string  &inText,
            const  char  *      sepChrs,
            TextBuffer          &bufText,
            TokenArray          &vTokens);

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
