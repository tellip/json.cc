/**
 * format
 * (\w+)\n\s*(\w+)\) -> $1 $2)
 * (\w+)\n\s*(\w+)\s(\w+)\) -> $1 $2 $3)
 * (\w+)\n\s*(\w+)\n\s*(\w+)\) -> $1 $2 $3)
 */

#pragma once

#include "hub.h"

namespace json {
    struct Special {
    JSON_STATIC(Special)
    };

    //no default
    template<typename>
    struct NumberSpecial : public Special {
    JSON_STATIC(NumberSpecial)

    private:

    };

#define JSON_NUMBER_SPECIAL(NT)\
    template<>\
    struct NumberSpecial<NT> : public Special {\
    JSON_STATIC(NumberSpecial)\
    public:\
        static int deciPrec;\
    };

    JSON_NUMBER_SPECIAL(short)

    JSON_NUMBER_SPECIAL(unsigned short)

    JSON_NUMBER_SPECIAL(int)

    JSON_NUMBER_SPECIAL(unsigned int)

    JSON_NUMBER_SPECIAL(long)

    JSON_NUMBER_SPECIAL(unsigned long)

    JSON_NUMBER_SPECIAL(long long)

    JSON_NUMBER_SPECIAL(unsigned long long)

    JSON_NUMBER_SPECIAL(float)

    JSON_NUMBER_SPECIAL(double)

    JSON_NUMBER_SPECIAL(long double)

#undef JSON_NUMBER_SPECIAL

    //no default
    template<typename>
    struct CharSpecial : public Special {
    JSON_STATIC(CharSpecial)
    };

#define JSON_CHAR_SPECIAL(CT, ST, OSST)\
    template<>\
    struct CharSpecial<CT> : public Special {\
    JSON_STATIC(CharSpecial)\
    public:\
        using String= ST;\
        using Oss= OSST;\
        static const CT objLeft, objRight, arrLeft, arrRight, sepSym, strBound, referSym, escapeSym, lineBreak, blankSpace;\
        static const String boolTrue, boolFalse, nullSym, lnCmtHd, bkCmtHd, bkCmtTl;\
        static const std::map<const CT, const CT> escapeMap, unescaMap;\
        static int (*const &strNCmp)(const CT *, const CT *, size_t);\
    };

    JSON_CHAR_SPECIAL(char, std::string, std::ostringstream)

    JSON_CHAR_SPECIAL(wchar_t, std::wstring, std::wostringstream)

#undef JSON_CHAR_SPECIAL

    //no deafult
    template<typename, typename>
    struct CharNumberSpecial : public Special {
    JSON_STATIC(CharNumberSpecial)
    };

#define JSON_CHAR_NUMBER_SPECIAL(CT, NT)\
    template<>\
    struct CharNumberSpecial<CT, NT> : public Special {\
    JSON_STATIC(CharNumberSpecial)\
    public:\
        static NT strToNum(const CT *const &, CT **const &);\
    };

    JSON_CHAR_NUMBER_SPECIAL(char, long)

    JSON_CHAR_NUMBER_SPECIAL(char, int)

    JSON_CHAR_NUMBER_SPECIAL(char, short)

    JSON_CHAR_NUMBER_SPECIAL(char, unsigned long)

    JSON_CHAR_NUMBER_SPECIAL(char, unsigned int)

    JSON_CHAR_NUMBER_SPECIAL(char, unsigned short)

    JSON_CHAR_NUMBER_SPECIAL(char, long long)

    JSON_CHAR_NUMBER_SPECIAL(char, unsigned long long)

    JSON_CHAR_NUMBER_SPECIAL(char, float)

    JSON_CHAR_NUMBER_SPECIAL(char, double)

    JSON_CHAR_NUMBER_SPECIAL(char, long double)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, long)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, int)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, short)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, unsigned long)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, unsigned int)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, unsigned short)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, long long)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, unsigned long long)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, float)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, double)

    JSON_CHAR_NUMBER_SPECIAL(wchar_t, long double)

#undef JSON_CHAR_NUMBER_SPECIAL

    //default
    template<typename AT, typename JT>
    struct ArraySpecial : public Special {
    JSON_STATIC(ArraySpecial)

    public:
        static AT buildByList(std::list<JT> &&);
    };

#define JSON_ARRAY_SPECIAL(AC)\
    template<typename JT>\
    struct ArraySpecial<AC<JT>, JT> : public Special {\
    JSON_STATIC(ArraySpecial)\
    public:\
        static AC<JT> buildByList(std::list<JT> &&);\
    };

    JSON_ARRAY_SPECIAL(std::forward_list)

    JSON_ARRAY_SPECIAL(std::list)

    JSON_ARRAY_SPECIAL(std::vector)

    JSON_ARRAY_SPECIAL(std::set)

    JSON_ARRAY_SPECIAL(std::multiset)

#undef JSON_ARRAY_SPECIAL

}
