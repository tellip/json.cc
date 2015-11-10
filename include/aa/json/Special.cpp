//
// Created by kalo on 2015/11/7.
//

#include "Special.h"

namespace aa {
    namespace _json {
        const char
                Private::CharSpecial<char>::objLeft = '{',
                Private::CharSpecial<char>::objRight = '}',
                Private::CharSpecial<char>::arrLeft = '[',
                Private::CharSpecial<char>::arrRight = ']',
                Private::CharSpecial<char>::sepSym = ',',
                Private::CharSpecial<char>::strBound = '"',
                Private::CharSpecial<char>::referSym = ':',
                Private::CharSpecial<char>::escapeSym = '\\',
                Private::CharSpecial<char>::lineBreak = '\n',
                Private::CharSpecial<char>::blankSpace = ' ';
        const std::string
                Private::CharSpecial<char>::boolTrue = "true",
                Private::CharSpecial<char>::boolFalse = "false",
                Private::CharSpecial<char>::nullSym = "null",
                Private::CharSpecial<char>::lnCmtHd = "//",
                Private::CharSpecial<char>::bkCmtHd = "/*",
                Private::CharSpecial<char>::bkCmtTl = "*/";
        //,
//                Private::CharSpecial<char>::ldScnfFmt = "%LF%n",
//                Private::CharSpecial<char>::dbScnfFmt = "%lf%n";
        const std::map<const char, const char>
                Private::CharSpecial<char>::escapeMap = {
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
                Private::CharSpecial<char>::unescaMap = {
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

        int (*const &Private::CharSpecial<char>::StrNCmp)(const char *, const char *, size_t) = strncmp;

        long double (*const &Private::CharSpecial<char>::StrToLd)(const char *, char **) = strtold;

//        int (*const &Private::CharSpecial<char>::StrScanf)(const char *, const char *, ...) = sscanf;

        const wchar_t
                Private::CharSpecial<wchar_t>::objLeft = L'{',
                Private::CharSpecial<wchar_t>::objRight = L'}',
                Private::CharSpecial<wchar_t>::arrLeft = L'[',
                Private::CharSpecial<wchar_t>::arrRight = L']',
                Private::CharSpecial<wchar_t>::sepSym = L',',
                Private::CharSpecial<wchar_t>::strBound = L'"',
                Private::CharSpecial<wchar_t>::referSym = L':',
                Private::CharSpecial<wchar_t>::escapeSym = L'\\',
                Private::CharSpecial<wchar_t>::lineBreak = L'\n',
                Private::CharSpecial<wchar_t>::blankSpace = L' ';
        const std::wstring
                Private::CharSpecial<wchar_t>::boolTrue = L"true",
                Private::CharSpecial<wchar_t>::boolFalse = L"false",
                Private::CharSpecial<wchar_t>::nullSym = L"null",
                Private::CharSpecial<wchar_t>::lnCmtHd = L"//",
                Private::CharSpecial<wchar_t>::bkCmtHd = L"/*",
                Private::CharSpecial<wchar_t>::bkCmtTl = L"*/";
        //,
//                Private::CharSpecial<wchar_t>::ldScnfFmt = L"%LF%n",
//                Private::CharSpecial<wchar_t>::dbScnfFmt = L"%lf%n";
        const std::map<const wchar_t, const wchar_t>
                Private::CharSpecial<wchar_t>::escapeMap = {
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
                Private::CharSpecial<wchar_t>::unescaMap = {
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

        int (*const &Private::CharSpecial<wchar_t>::StrNCmp)(const wchar_t *, const wchar_t *, size_t) = wcsncmp;

        long double (*const &Private::CharSpecial<wchar_t>::StrToLd)(const wchar_t *, wchar_t **) = wcstold;

//        int (*const &Private::CharSpecial<wchar_t>::StrScanf)(const wchar_t *, const wchar_t *, ...) = swscanf;

        template<typename AT, typename JT>
        AT
        Private::ArraySpecial<AT, JT>::buildByList(std::list<JT> &&l) {
            AT a;
            for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) a.push_back(std::move(*i));
            return a;
        }

        template<typename JT>
        std::forward_list<JT>
        Private::ArraySpecial<std::forward_list<JT>, JT>::buildByList(std::list<JT> &&l) {
            std::forward_list<JT> fl;
            typename std::list<JT>::iterator i;
            for (i = l.end(), i--; i != l.begin(); i--) fl.push_front(std::move(*i));
            fl.push_front(std::move(*i));
            return fl;
        }

        template<typename JT>
        std::list<JT>
        Private::ArraySpecial<std::list<JT>, JT>::buildByList(std::list<JT> &&l) {
            return std::move(l);
        }

        template<typename JT>
        std::vector<JT>
        Private::ArraySpecial<std::vector<JT>, JT>::buildByList(std::list<JT> &&l) {
            std::vector<JT> v(l.size());
            typename std::vector<JT>::iterator i1 = v.begin();
            for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++, i1++) i1->swap(*i);
            return v;
        }

        template<typename JT>
        std::set<JT>
        Private::ArraySpecial<std::set<JT>, JT>::buildByList(std::list<JT> &&l) {
            std::set<JT> st;
            for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) st.insert(std::move(*i));
            return st;
        }

        template<typename JT>
        std::multiset<JT>
        Private::ArraySpecial<std::multiset<JT>, JT>::buildByList(std::list<JT> &&l) {
            std::multiset<JT> st;
            for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) st.insert(std::move(*i));
            return st;
        }
    }
}