//
// Created by kalo on 2015/11/7.
//

#include "Special.h"

namespace aa {
    namespace json {
        const char
                Private::Special<char>::_::objLeft = '{',
                Private::Special<char>::_::objRight = '}',
                Private::Special<char>::_::arrLeft = '[',
                Private::Special<char>::_::arrRight = ']',
                Private::Special<char>::_::sepSym = ',',
                Private::Special<char>::_::strBound = '"',
                Private::Special<char>::_::referSym = ':',
                Private::Special<char>::_::escapeSym = '\\',
                Private::Special<char>::_::lineBreak = '\n',
                Private::Special<char>::_::blankSpace = ' ';
        const std::string
                Private::Special<char>::_::boolTrue = "true",
                Private::Special<char>::_::boolFalse = "false",
                Private::Special<char>::_::nullSym = "null",
                Private::Special<char>::_::lnCmtHd = "//",
                Private::Special<char>::_::bkCmtHd = "/*",
                Private::Special<char>::_::bkCmtTl = "*/";//,
//                Private::Special<char>::_::ldScnfFmt = "%LF%n",
//                Private::Special<char>::_::dbScnfFmt = "%lf%n";
        const std::map<const char, const char>
                Private::Special<char>::_::escapeMap = {
                {'a',  '\a'},
                {'b',  '\b'},
                {'f',  '\f'},
                {'n',  '\n'},
                {'r',  '\r'},
                {'t',  '\t'},
                {'v',  '\v'},
                {'\\', '\\'},
                {'\'', '\''},
                {'\"', '\"'},
                {'0',  '\0'}
        },
                Private::Special<char>::_::unescaMap = {
                {'\a', 'a'},
                {'\b', 'b'},
                {'\f', 'f'},
                {'\n', 'n'},
                {'\r', 'r'},
                {'\t', 't'},
                {'\v', 'v'},
                {'\\', '\\'},
                {'\'', '\''},
                {'\"', '\"'},
                {'\0', '0'}
        };

        int (*const &Private::Special<char>::_::StrNCmp)(const char *, const char *, size_t) = strncmp;

        long double (*const &Private::Special<char>::_::StrToLd)(const char *, char **) = strtold;

//        int (*const &Private::Special<char>::_::StrScanf)(const char *, const char *, ...) = sscanf;

        const wchar_t
                Private::Special<wchar_t>::_::objLeft = L'{',
                Private::Special<wchar_t>::_::objRight = L'}',
                Private::Special<wchar_t>::_::arrLeft = L'[',
                Private::Special<wchar_t>::_::arrRight = L']',
                Private::Special<wchar_t>::_::sepSym = L',',
                Private::Special<wchar_t>::_::strBound = L'"',
                Private::Special<wchar_t>::_::referSym = L':',
                Private::Special<wchar_t>::_::escapeSym = L'\\',
                Private::Special<wchar_t>::_::lineBreak = L'\n',
                Private::Special<wchar_t>::_::blankSpace = L' ';
        const std::wstring
                Private::Special<wchar_t>::_::boolTrue = L"true",
                Private::Special<wchar_t>::_::boolFalse = L"false",
                Private::Special<wchar_t>::_::nullSym = L"null",
                Private::Special<wchar_t>::_::lnCmtHd = L"//",
                Private::Special<wchar_t>::_::bkCmtHd = L"/*",
                Private::Special<wchar_t>::_::bkCmtTl = L"*/";//,
//                Private::Special<wchar_t>::_::ldScnfFmt = L"%LF%n",
//                Private::Special<wchar_t>::_::dbScnfFmt = L"%lf%n";
        const std::map<const wchar_t, const wchar_t>
                Private::Special<wchar_t>::_::escapeMap = {
                {L'a',  L'\a'},
                {L'b',  L'\b'},
                {L'f',  L'\f'},
                {L'n',  L'\n'},
                {L'r',  L'\r'},
                {L't',  L'\t'},
                {L'v',  L'\v'},
                {L'\\', L'\\'},
                {L'\'', L'\''},
                {L'\"', L'\"'},
                {L'0',  L'\0'}
        },
                Private::Special<wchar_t>::_::unescaMap = {
                {L'\a', L'a'},
                {L'\b', L'b'},
                {L'\f', L'f'},
                {L'\n', L'n'},
                {L'\r', L'r'},
                {L'\t', L't'},
                {L'\v', L'v'},
                {L'\\', L'\\'},
                {L'\'', L'\''},
                {L'\"', L'\"'},
                {L'\0', L'0'}
        };

        int (*const &Private::Special<wchar_t>::_::StrNCmp)(const wchar_t *, const wchar_t *, size_t) = wcsncmp;

        long double (*const &Private::Special<wchar_t>::_::StrToLd)(const wchar_t *, wchar_t **) = wcstold;

//        int (*const &Private::Special<wchar_t>::_::StrScanf)(const wchar_t *, const wchar_t *, ...) = swscanf;
    }
}