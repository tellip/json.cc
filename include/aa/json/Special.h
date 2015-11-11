//
// Created by kalo on 2015/11/7.
//

#pragma once

#include "hub.h"

namespace aa {
    struct _Json::Special {
    STATIC(Special)
    };

    //no default
    template<typename>
    struct _Json::CharSpecial : public Special {
    STATIC(CharSpecial)
    };

    template<>
    struct _Json::CharSpecial<char> : public Special {
    STATIC(CharSpecial)

    public:
        using String= std::string;
        using Oss= std::ostringstream;

        //Json config
        static const char objLeft, objRight, arrLeft, arrRight, sepSym, strBound, referSym, escapeSym, lineBreak, blankSpace;
        static const String boolTrue, boolFalse, nullSym, lnCmtHd, bkCmtHd, bkCmtTl;
        //, ldScnfFmt, dbScnfFmt;
        static const std::map<const char, const char> escapeMap, unescaMap;

        static int (*const &StrNCmp)(const char *, const char *, size_t);

        static long double (*const &StrToLd)(const char *, char **);

//            static int (*const &StrScanf)(const char *, const char *, ...);
    };

    template<>
    struct _Json::CharSpecial<wchar_t> : public Special {
    STATIC(CharSpecial)

    public:
        using String= std::wstring;
        using Oss= std::wostringstream;

        //Json config
        static const wchar_t objLeft, objRight, arrLeft, arrRight, sepSym, strBound, referSym, escapeSym, lineBreak, blankSpace;
        static const String boolTrue, boolFalse, nullSym, lnCmtHd, bkCmtHd, bkCmtTl;
        //, ldScnfFmt, dbScnfFmt;
        static const std::map<const wchar_t, const wchar_t> escapeMap, unescaMap;

        static int (*const &StrNCmp)(const wchar_t *, const wchar_t *, size_t);

        static long double (*const &StrToLd)(const wchar_t *, wchar_t **);

//            static int (*const &StrScanf)(const wchar_t *, const wchar_t *, ...);
    };

    //default
    template<typename AT, typename JT>
    struct _Json::ArraySpecial : public Special {
    STATIC(ArraySpecial)

    public:
        static AT buildByList(std::list<JT> &&);
    };

    template<typename JT>
    struct _Json::ArraySpecial<std::forward_list<JT>, JT> : public Special {
    STATIC(ArraySpecial)

    public:
        static std::forward_list<JT> buildByList(std::list<JT> &&);
    };

    template<typename JT>
    struct _Json::ArraySpecial<std::list<JT>, JT> : public Special {
    STATIC(ArraySpecial)

    public:
        static std::list<JT> buildByList(std::list<JT> &&);
    };

    template<typename JT>
    struct _Json::ArraySpecial<std::vector<JT>, JT> : public Special {
    STATIC(ArraySpecial)

    public:
        static std::vector<JT> buildByList(std::list<JT> &&);
    };

    template<typename JT>
    struct _Json::ArraySpecial<std::set<JT>, JT> : public Special {
    STATIC(ArraySpecial)

    public:
        static std::set<JT> buildByList(std::list<JT> &&);
    };

    template<typename JT>
    struct _Json::ArraySpecial<std::multiset<JT>, JT> : public Special {
    STATIC(ArraySpecial)

    public:
        static std::multiset<JT> buildByList(std::list<JT> &&);
    };
}

