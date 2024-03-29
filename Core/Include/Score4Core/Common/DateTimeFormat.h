﻿//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
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
**      An Interface of DateTimeFormat class.
**
**      @file       Common/DateTimeFormat.h
**/

#if !defined( SCORE4CORE_COMMON_INCLUDED_DATE_TIME_FORMAT_H )
#    define   SCORE4CORE_COMMON_INCLUDED_DATE_TIME_FORMAT_H

#include    "Score4Types.h"

#include    <iosfwd>
#include    <string>

SCORE4_CORE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    DateTimeFormat  class.
//

class  DateTimeFormat
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**
    **    日時構造体。
    **/
    struct  TDateTime
    {
        int     year;
        int     month;
        int     day;

        double  rems;
        int     hour;
        int     minute;
        int     second;
        double  remsec;
    };

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    DateTimeFormat();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~DateTimeFormat();

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
    /**   シリアル値から日時構造体に変換する。
    **
    **  @param [in] dtSerial    シリアル値。
    **  @param[out] ptrBuf      日時構造体。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    getDateTimeFromSerial(
            const   DateSerial  dtSerial,
            TDateTime  *        ptrBuf);

    //----------------------------------------------------------------
    /**   指定した日付をシリアル値に変換する。
    **
    **  @param [in] year
    **  @param [in] month
    **  @param [in] day
    **  @return     指定した日付の午前零時に対するシリアル値。
    **/
    static  DateSerial
    getSerialFromDate(
            const  int  year,
            const  int  month,
            const  int  day);

    //----------------------------------------------------------------
    /**   指定した日付をシリアル値に変換する。
    **
    **  @param [in] year
    **  @param [in] month
    **  @param [in] day
    **  @param [in] rems
    **  @return     指定した日付の午前零時に対するシリアル値。
    **/
    static  DateSerial
    getSerialFromDate(
            const   int         year,
            const   int         month,
            const   int         day,
            const   int         hour,
            const   int         minute,
            const   int         second,
            const   DateSerial  remsec = 0.0);

    //----------------------------------------------------------------
    /**   指定した日付をシリアル値に変換する。
    **
    **  @param [in] year
    **  @param [in] month
    **  @param [in] day
    **  @param [in] rems
    **  @return     指定した日付の午前零時に対するシリアル値。
    **/
    static  DateSerial
    getSerialFromDate(
            const   int         year,
            const   int         month,
            const   int         day,
            const   DateSerial  rems);

    //----------------------------------------------------------------
    /**   ダンプした文字列からシリアル値を復元する。
    **
    **  @param [in] hexDump   ダンプした 16 進文字列。
    **  @return     シリアル値。
    **/
    static  DateSerial
    getSerialFromString(
            const  std::string  &hexDump);

    //----------------------------------------------------------------
    /**   指定したシリアル値を文字列に変換する。
    **
    **  @param [in] dtSerial    シリアル値。
    **  @return     シリアル値を 16 進ダンプした文字列。
    **/
    static  std::string
    toString(
            const   DateSerial  dtSerial);

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

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   DateTimeFormatTest;
};

}   //  End of namespace  Common
SCORE4_CORE_NAMESPACE_END

#endif
