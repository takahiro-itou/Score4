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
**      An Implementation of DateTimeFormat class.
**
**      @file       Common/DateTimeFormat.cpp
**/

#include    "Score4Core/Common/DateTimeFormat.h"

#include    <cstdlib>
#include    <iomanip>
#include    <sstream>
#include    <stdint.h>

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
    int  wYear  = static_cast<int>(dtSerial / 365.24) + 1900;
    int  wMonth = 0;
    DateSerial  wdsRem  = 0;
    for ( ; ; ++ wYear )
    {
        const   DateSerial  dsValue = getSerialFromDate(wYear, 1, 1);
        if ( dsValue > dtSerial ) {
            --  wYear;
            wdsRem  =  dtSerial - getSerialFromDate(wYear, 1, 1);
            break;
        }
    }

    int     isLeap  = 0;
    if ( ! (wYear & 3) ) {
        if ( (wYear % 100) == 0 ) {
            isLeap  =  ( ((wYear % 400) == 0) ? 1 : 0 );
        } else {
            isLeap  =  1;
        }
    }
    for ( wMonth = 1; wMonth <= 12; ++ wMonth ) {
        const  int  nxDays  =
            DAYS_OF_MONTH[wMonth]  + (wMonth == 2 ? isLeap : 0);
        if ( wdsRem < nxDays ) {
            break;
        }
        wdsRem  -=  nxDays;
    }

    if ( wMonth >= 13 ) {
        ptrBuf->year    = wYear  +  1;
        ptrBuf->month   = wMonth - 12;
    } else {
        ptrBuf->year    = wYear;
        ptrBuf->month   = wMonth;
    }
    ptrBuf->day     = static_cast<int>(wdsRem + 1);

    DateSerial  dtTime  = dtSerial - static_cast<int>(dtSerial);
    ptrBuf->remsec  = dtTime;

    dtTime  *= 24;
    ptrBuf->hour    = static_cast<int>(dtTime);
    dtTime  -= (ptrBuf->hour);

    dtTime  *= 60;
    ptrBuf->minute  = static_cast<int>(dtTime);
    dtTime  -= (ptrBuf->minute);

    dtTime  *= 60;
    ptrBuf->second  = static_cast<int>(dtTime);
    dtTime  -= (ptrBuf->second);

    return ( ERR_SUCCESS );
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

//----------------------------------------------------------------
//    指定した日付をシリアル値に変換する。
//

DateSerial
DateTimeFormat::getSerialFromDate(
            const   int         year,
            const   int         month,
            const   int         day,
            const   int         hour,
            const   int         minute,
            const   int         second,
            const   DateSerial  remsec)
{
    DateSerial  dsRems  = (hour * 60 + minute) * 60 + second + remsec;
    return ( getSerialFromDate(year, month, day) + dsRems / 86400 );
}

//----------------------------------------------------------------
//    指定した日付をシリアル値に変換する。
//

DateSerial
DateTimeFormat::getSerialFromDate(
        const   int         year,
        const   int         month,
        const   int         day,
        const   DateSerial  rems)
{
    return ( getSerialFromDate(year, month, day) + rems );
}

//----------------------------------------------------------------
//    ダンプした文字列からシリアル値を復元する。
//

DateSerial
DateTimeFormat::getSerialFromString(
        const  std::string  &hexDump)
{
    size_t          idx = 0;
    const uint64_t  val = std::stoull(hexDump, &idx, 16);

    return ( *(pointer_cast<const DateSerial *>(&val)) );
}

//----------------------------------------------------------------
//    指定したシリアル値を文字列に変換する。
//

std::string
DateTimeFormat::toString(
        const   DateSerial  dtSerial)
{
    const uint64_t  val = *(pointer_cast<const uint64_t *>(&dtSerial));
    std::stringstream   ss;

    ss  <<  std::uppercase  <<  std::hex
        <<  std::setw(16)   <<  std::setfill('0')
        <<  val;
    return  ( ss.str() );
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
