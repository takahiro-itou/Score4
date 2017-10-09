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
**      An Implementation of DateTimeFormat class.
**
**      @file       Common/DateTimeFormat.cpp
**/

#include    "Score4Core/Common/DateTimeFormat.h"

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

CONSTEXPR_VAR   const   int
DAYS_OF_MONTH[15] = {
    0,
    31, 28, 31, 30,  31, 30, 31, 31,
    30, 31, 30, 31,  31, 28
};

CONSTEXPR_VAR   const   int
SUM_DAYS_OF_MONTH[15] = {
    0,
    0,    31,  59,  90,  120, 151, 181, 212,
    243, 273, 304, 334,  365, 396,
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    DateTimeFormat  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

DateTimeFormat::DateTimeFormat()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

DateTimeFormat::~DateTimeFormat()
{
}

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
//    シリアル値から日時構造体に変換する。
//

ErrCode
DateTimeFormat::getDateTimeFromSerial(
        const   DateSerial  dtSerial,
        TDateTime  *        ptrBuf)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    指定した日付をシリアル値に変換する。
//

DateSerial
DateTimeFormat::getSerialFromDate(
        const  int  year,
        const  int  month,
        const  int  day)
{
    //  閏年の計算を簡単にするため、壱月と弐月は、  //
    //  前年の十三月と十四月として計算する。        //
    const  int  wYear   = (month <= 2 ? year  -  1 : year);
    const  int  wMonth  = (month <= 2 ? month + 12 : month);

    //  西暦零年から、その年までの、閏年の回数を計算する。  //
    const  int  numLeap = (wYear / 4) - (wYear / 100) + (wYear / 400);

    //  その年の元日が、基準日から何日経過しているか計算。  //
    //  基準となる 1900 年より前には、460 回の閏年がある。  //
    CONSTEXPR_VAR  int  BASE_DATE_SERIAL_VALUE  =  365 - 1;
    const  int  dsYear  = ((wYear - 1899) * 365) + (numLeap - 460)
                                - BASE_DATE_SERIAL_VALUE;
    return ( dsYear + SUM_DAYS_OF_MONTH[wMonth] + day );
}

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
