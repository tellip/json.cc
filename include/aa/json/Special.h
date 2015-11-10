//
// Created by kalo on 2015/11/7.
//

#pragma once

#include "Private.h"

namespace aa {
    namespace _json {
        struct Private::Special {
        STATIC(Special)
        };

        //no default
        template<typename>
        struct Private::CharSpecial : public Special {
        STATIC(CharSpecial)
        };

        template<>
        struct Private::CharSpecial<char> : public Special {
        STATIC(CharSpecial)

        public:
            using String= std::string;
            using Oss= std::ostringstream;

            //json config
            static const char objLeft, objRight, arrLeft, arrRight, sepSym, strBound, referSym, escapeSym, lineBreak, blankSpace;
            static const String boolTrue, boolFalse, nullSym, lnCmtHd, bkCmtHd, bkCmtTl;
            //, ldScnfFmt, dbScnfFmt;
            static const std::map<const char, const char> escapeMap, unescaMap;

            static int (*const &StrNCmp)(const char *, const char *, size_t);

            static long double (*const &StrToLd)(const char *, char **);

//            static int (*const &StrScanf)(const char *, const char *, ...);
        };

        template<>
        struct Private::CharSpecial<wchar_t> : public Special {
        STATIC(CharSpecial)

        public:
            using String= std::wstring;
            using Oss= std::wostringstream;

            //json config
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
        struct Private::ArraySpecial : public Special {
        STATIC(ArraySpecial)

        public:
            static AT buildByList(std::list<JT> &&);
        };

        template<typename JT>
        struct Private::ArraySpecial<std::forward_list<JT>, JT> : public Special {
        STATIC(ArraySpecial)

        public:
            static std::forward_list<JT> buildByList(std::list<JT> &&);
        };

        template<typename JT>
        struct Private::ArraySpecial<std::list<JT>, JT> : public Special {
        STATIC(ArraySpecial)

        public:
            static std::list<JT> buildByList(std::list<JT> &&);
        };

        template<typename JT>
        struct Private::ArraySpecial<std::vector<JT>, JT> : public Special {
        STATIC(ArraySpecial)

        public:
            static std::vector<JT> buildByList(std::list<JT> &&);
        };

        template<typename JT>
        struct Private::ArraySpecial<std::set<JT>, JT> : public Special {
        STATIC(ArraySpecial)

        public:
            static std::set<JT> buildByList(std::list<JT> &&);
        };

        template<typename JT>
        struct Private::ArraySpecial<std::multiset<JT>, JT> : public Special {
        STATIC(ArraySpecial)

        public:
            static std::multiset<JT> buildByList(std::list<JT> &&);
        };
    }
}
