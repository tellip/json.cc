//
// Created by kalo on 2015/11/7.
//

#include "Special.h"

namespace aa {
    const char
            _Json::CharSpecial<char>::objLeft = '{',
            _Json::CharSpecial<char>::objRight = '}',
            _Json::CharSpecial<char>::arrLeft = '[',
            _Json::CharSpecial<char>::arrRight = ']',
            _Json::CharSpecial<char>::sepSym = ',',
            _Json::CharSpecial<char>::strBound = '"',
            _Json::CharSpecial<char>::referSym = ':',
            _Json::CharSpecial<char>::escapeSym = '\\',
            _Json::CharSpecial<char>::lineBreak = '\n',
            _Json::CharSpecial<char>::blankSpace = ' ';
    const std::string
            _Json::CharSpecial<char>::boolTrue = "true",
            _Json::CharSpecial<char>::boolFalse = "false",
            _Json::CharSpecial<char>::nullSym = "null",
            _Json::CharSpecial<char>::lnCmtHd = "//",
            _Json::CharSpecial<char>::bkCmtHd = "/*",
            _Json::CharSpecial<char>::bkCmtTl = "*/";
    //,
//                _Json::CharSpecial<char>::ldScnfFmt = "%LF%n",
//                _Json::CharSpecial<char>::dbScnfFmt = "%lf%n";
    const std::map<const char, const char>
            _Json::CharSpecial<char>::escapeMap = {
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
            _Json::CharSpecial<char>::unescaMap = {
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

    int (*const &_Json::CharSpecial<char>::StrNCmp)(const char *, const char *, size_t) = strncmp;

    long double (*const &_Json::CharSpecial<char>::StrToLd)(const char *, char **) = strtold;

//        int (*const &_Json::CharSpecial<char>::StrScanf)(const char *, const char *, ...) = sscanf;

    const wchar_t
            _Json::CharSpecial<wchar_t>::objLeft = L'{',
            _Json::CharSpecial<wchar_t>::objRight = L'}',
            _Json::CharSpecial<wchar_t>::arrLeft = L'[',
            _Json::CharSpecial<wchar_t>::arrRight = L']',
            _Json::CharSpecial<wchar_t>::sepSym = L',',
            _Json::CharSpecial<wchar_t>::strBound = L'"',
            _Json::CharSpecial<wchar_t>::referSym = L':',
            _Json::CharSpecial<wchar_t>::escapeSym = L'\\',
            _Json::CharSpecial<wchar_t>::lineBreak = L'\n',
            _Json::CharSpecial<wchar_t>::blankSpace = L' ';
    const std::wstring
            _Json::CharSpecial<wchar_t>::boolTrue = L"true",
            _Json::CharSpecial<wchar_t>::boolFalse = L"false",
            _Json::CharSpecial<wchar_t>::nullSym = L"null",
            _Json::CharSpecial<wchar_t>::lnCmtHd = L"//",
            _Json::CharSpecial<wchar_t>::bkCmtHd = L"/*",
            _Json::CharSpecial<wchar_t>::bkCmtTl = L"*/";
    //,
//                _Json::CharSpecial<wchar_t>::ldScnfFmt = L"%LF%n",
//                _Json::CharSpecial<wchar_t>::dbScnfFmt = L"%lf%n";
    const std::map<const wchar_t, const wchar_t>
            _Json::CharSpecial<wchar_t>::escapeMap = {
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
            _Json::CharSpecial<wchar_t>::unescaMap = {
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

    int (*const &_Json::CharSpecial<wchar_t>::StrNCmp)(const wchar_t *, const wchar_t *, size_t) = wcsncmp;

    long double (*const &_Json::CharSpecial<wchar_t>::StrToLd)(const wchar_t *, wchar_t **) = wcstold;

//        int (*const &_Json::CharSpecial<wchar_t>::StrScanf)(const wchar_t *, const wchar_t *, ...) = swscanf;

    template<typename AT, typename JT>
    AT
    _Json::ArraySpecial<AT, JT>::buildByList(std::list<JT> &&l) {
        AT a;
        for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) a.push_back(std::move(*i));
        return a;
    }

    template<typename JT>
    std::forward_list<JT>
    _Json::ArraySpecial<std::forward_list<JT>, JT>::buildByList(std::list<JT> &&l) {
        std::forward_list<JT> fl;
        typename std::list<JT>::iterator i;
        for (i = l.end(), i--; i != l.begin(); i--) fl.push_front(std::move(*i));
        fl.push_front(std::move(*i));
        return fl;
    }

    template<typename JT>
    std::list<JT>
    _Json::ArraySpecial<std::list<JT>, JT>::buildByList(std::list<JT> &&l) {
        return std::move(l);
    }

    template<typename JT>
    std::vector<JT>
    _Json::ArraySpecial<std::vector<JT>, JT>::buildByList(std::list<JT> &&l) {
        std::vector<JT> v(l.size());
        typename std::vector<JT>::iterator i1 = v.begin();
        for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++, i1++) i1->swap(*i);
        return v;
    }

    template<typename JT>
    std::set<JT>
    _Json::ArraySpecial<std::set<JT>, JT>::buildByList(std::list<JT> &&l) {
        std::set<JT> st;
        for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) st.insert(std::move(*i));
        return st;
    }

    template<typename JT>
    std::multiset<JT>
    _Json::ArraySpecial<std::multiset<JT>, JT>::buildByList(std::list<JT> &&l) {
        std::multiset<JT> st;
        for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) st.insert(std::move(*i));
        return st;
    }
}