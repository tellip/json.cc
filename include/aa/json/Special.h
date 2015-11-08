//
// Created by kalo on 2015/11/7.
//

#pragma once

#include "Private.h"

namespace aa {
    namespace json {
        template<typename...>
        struct Private::Special {
        STATIC(Special)

        public:
            struct _;
        };

        template<>
        struct Private::Special<char>::_ {
        STATIC(_)

        public:
            typedef std::string String;
            typedef std::ostringstream Oss;

            //Json config
            static const char objLeft, objRight, arrLeft, arrRight, sepSym, strBound, referSym, escapeSym, lineBreak, blankSpace;
            static const String boolTrue, boolFalse, nullSym, lnCmtHd, bkCmtHd, bkCmtTl;//, ldScnfFmt, dbScnfFmt;
            static const std::map<const char, const char> escapeMap, unescaMap;

            static int (*const &StrNCmp)(const char *, const char *, size_t);

            static long double (*const &StrToLd)(const char *, char **);

//            static int (*const &StrScanf)(const char *, const char *, ...);
        };

        template<>
        struct Private::Special<wchar_t>::_ {
        STATIC(_)

        public:
            typedef std::wstring String;
            typedef std::wostringstream Oss;

            //Json config
            static const wchar_t objLeft, objRight, arrLeft, arrRight, sepSym, strBound, referSym, escapeSym, lineBreak, blankSpace;
            static const String boolTrue, boolFalse, nullSym, lnCmtHd, bkCmtHd, bkCmtTl;//, ldScnfFmt, dbScnfFmt;
            static const std::map<const wchar_t, const wchar_t> escapeMap, unescaMap;

            static int (*const &StrNCmp)(const wchar_t *, const wchar_t *, size_t);

            static long double (*const &StrToLd)(const wchar_t *, wchar_t **);

//            static int (*const &StrScanf)(const wchar_t *, const wchar_t *, ...);
        };
    }
}
