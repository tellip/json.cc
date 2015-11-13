//
// Created by kalo on 2015/11/7.
//

#include "Special.h"

namespace aa {
    //number special

    int _Json::NumberSpecial<short>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(short) * 8 - 1);
    int _Json::NumberSpecial<unsigned short>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(short) * 8);
    int _Json::NumberSpecial<int>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(int) * 8 - 1);
    int _Json::NumberSpecial<unsigned int>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(int) * 8);
    int _Json::NumberSpecial<long>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(long) * 8 - 1);
    int _Json::NumberSpecial<unsigned long>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(long) * 8);
    int _Json::NumberSpecial<long long>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(long long) * 8 - 1);
    int _Json::NumberSpecial<unsigned long long>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(long long) * 8);
    int _Json::NumberSpecial<float>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(float) * 8);
    int _Json::NumberSpecial<double>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(double) * 8);
    int _Json::NumberSpecial<long double>::deciPrec = _Json::Trivial::precFromBinaToDeci(sizeof(long double) * 8);

    //char special
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

    int (*const &_Json::CharSpecial<char>::strNCmp)(const char *, const char *, size_t) = strncmp;

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

    int (*const &_Json::CharSpecial<wchar_t>::strNCmp)(const wchar_t *, const wchar_t *, size_t) = wcsncmp;

    //char number special
    //char
    long _Json::CharNumberSpecial<char, long>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtol(ps, pcEnd, 10);
    }

    int _Json::CharNumberSpecial<char, int>::strToNum(const char *const &ps, char **const &pcEnd) {
        return int(CharNumberSpecial<char, long>::strToNum(ps, pcEnd));
    }

    short _Json::CharNumberSpecial<char, short>::strToNum(const char *const &ps, char **const &pcEnd) {
        return short(CharNumberSpecial<char, long>::strToNum(ps, pcEnd));
    }

    unsigned long _Json::CharNumberSpecial<char, unsigned long>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtoul(ps, pcEnd, 10);
    }

    unsigned int _Json::CharNumberSpecial<char, unsigned int>::strToNum(const char *const &ps, char **const &pcEnd) {
        return (unsigned int) CharNumberSpecial<char, unsigned
        long>::strToNum(ps, pcEnd);
    }

    unsigned short _Json::CharNumberSpecial<char, unsigned short>::strToNum(const char *const &ps, char **const &pcEnd) {
        return (unsigned short) CharNumberSpecial<char, unsigned
        long>::strToNum(ps, pcEnd);
    }

    long long _Json::CharNumberSpecial<char, long long>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtoll(ps, pcEnd, 10);
    }

    unsigned long long _Json::CharNumberSpecial<char, unsigned long long>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtoull(ps, pcEnd, 10);
    }

    float _Json::CharNumberSpecial<char, float>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtof(ps, pcEnd);
    }

    double _Json::CharNumberSpecial<char, double>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtod(ps, pcEnd);
    }

    long double _Json::CharNumberSpecial<char, long double>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtold(ps, pcEnd);
    }

    //wchar_t
    long _Json::CharNumberSpecial<wchar_t, long>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstol(ps, pcEnd, 10);
    }

    int _Json::CharNumberSpecial<wchar_t, int>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return int(CharNumberSpecial<wchar_t, long>::strToNum(ps, pcEnd));
    }

    short _Json::CharNumberSpecial<wchar_t, short>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return short(CharNumberSpecial<wchar_t, long>::strToNum(ps, pcEnd));
    }

    unsigned long _Json::CharNumberSpecial<wchar_t, unsigned long>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstoul(ps, pcEnd, 10);
    }

    unsigned int _Json::CharNumberSpecial<wchar_t, unsigned int>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return (unsigned int) CharNumberSpecial<wchar_t, unsigned
        long>::strToNum(ps, pcEnd);
    }

    unsigned short _Json::CharNumberSpecial<wchar_t, unsigned short>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return (unsigned short) CharNumberSpecial<wchar_t, unsigned
        long>::strToNum(ps, pcEnd);
    }

    long long _Json::CharNumberSpecial<wchar_t, long long>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstoll(ps, pcEnd, 10);
    }

    unsigned long long _Json::CharNumberSpecial<wchar_t, unsigned long long>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstoull(ps, pcEnd, 10);
    }

    float _Json::CharNumberSpecial<wchar_t, float>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstof(ps, pcEnd);
    }

    double _Json::CharNumberSpecial<wchar_t, double>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstod(ps, pcEnd);
    }

    long double _Json::CharNumberSpecial<wchar_t, long double>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstold(ps, pcEnd);
    }

    //array special
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