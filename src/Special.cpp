//
// Created by kalo on 2015/11/7.
//

#include "Special.h"

namespace jsoncpp {
    //number special
    int NumberSpecial<short>::deciPrec = Trivial::precFromBinaToDeci(sizeof(short) * 8 - 1);
    int NumberSpecial<unsigned short>::deciPrec = Trivial::precFromBinaToDeci(sizeof(short) * 8);
    int NumberSpecial<int>::deciPrec = Trivial::precFromBinaToDeci(sizeof(int) * 8 - 1);
    int NumberSpecial<unsigned int>::deciPrec = Trivial::precFromBinaToDeci(sizeof(int) * 8);
    int NumberSpecial<long>::deciPrec = Trivial::precFromBinaToDeci(sizeof(long) * 8 - 1);
    int NumberSpecial<unsigned long>::deciPrec = Trivial::precFromBinaToDeci(sizeof(long) * 8);
    int NumberSpecial<long long>::deciPrec = Trivial::precFromBinaToDeci(sizeof(long long) * 8 - 1);
    int NumberSpecial<unsigned long long>::deciPrec = Trivial::precFromBinaToDeci(sizeof(long long) * 8);
    int NumberSpecial<float>::deciPrec = Trivial::precFromBinaToDeci(sizeof(float) * 8);
    int NumberSpecial<double>::deciPrec = Trivial::precFromBinaToDeci(sizeof(double) * 8);
    int NumberSpecial<long double>::deciPrec = Trivial::precFromBinaToDeci(sizeof(long double) * 8);

    //char special
    const char
            CharSpecial<char>::objLeft = '{',
            CharSpecial<char>::objRight = '}',
            CharSpecial<char>::arrLeft = '[',
            CharSpecial<char>::arrRight = ']',
            CharSpecial<char>::sepSym = ',',
            CharSpecial<char>::strBound = '"',
            CharSpecial<char>::referSym = ':',
            CharSpecial<char>::escapeSym = '\\',
            CharSpecial<char>::lineBreak = '\n',
            CharSpecial<char>::blankSpace = ' ';
    const std::string
            CharSpecial<char>::boolTrue = "true",
            CharSpecial<char>::boolFalse = "false",
            CharSpecial<char>::nullSym = "null",
            CharSpecial<char>::lnCmtHd = "//",
            CharSpecial<char>::bkCmtHd = "/*",
            CharSpecial<char>::bkCmtTl = "*/";
    const std::map<const char, const char>
            CharSpecial<char>::escapeMap = {
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
            CharSpecial<char>::unescaMap = {
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

    int (*const &CharSpecial<char>::strNCmp)(const char *, const char *, size_t) = strncmp;

    const wchar_t
            CharSpecial<wchar_t>::objLeft = L'{',
            CharSpecial<wchar_t>::objRight = L'}',
            CharSpecial<wchar_t>::arrLeft = L'[',
            CharSpecial<wchar_t>::arrRight = L']',
            CharSpecial<wchar_t>::sepSym = L',',
            CharSpecial<wchar_t>::strBound = L'"',
            CharSpecial<wchar_t>::referSym = L':',
            CharSpecial<wchar_t>::escapeSym = L'\\',
            CharSpecial<wchar_t>::lineBreak = L'\n',
            CharSpecial<wchar_t>::blankSpace = L' ';
    const std::wstring
            CharSpecial<wchar_t>::boolTrue = L"true",
            CharSpecial<wchar_t>::boolFalse = L"false",
            CharSpecial<wchar_t>::nullSym = L"null",
            CharSpecial<wchar_t>::lnCmtHd = L"//",
            CharSpecial<wchar_t>::bkCmtHd = L"/*",
            CharSpecial<wchar_t>::bkCmtTl = L"*/";
    const std::map<const wchar_t, const wchar_t>
            CharSpecial<wchar_t>::escapeMap = {
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
            CharSpecial<wchar_t>::unescaMap = {
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

    int (*const &CharSpecial<wchar_t>::strNCmp)(const wchar_t *, const wchar_t *, size_t) = wcsncmp;

    //char number special
    //char
    long CharNumberSpecial<char, long>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtol(ps, pcEnd, 10);
    }

    int CharNumberSpecial<char, int>::strToNum(const char *const &ps, char **const &pcEnd) {
        return int(CharNumberSpecial<char, long>::strToNum(ps, pcEnd));
    }

    short CharNumberSpecial<char, short>::strToNum(const char *const &ps, char **const &pcEnd) {
        return short(CharNumberSpecial<char, long>::strToNum(ps, pcEnd));
    }

    unsigned long CharNumberSpecial<char, unsigned long>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtoul(ps, pcEnd, 10);
    }

    unsigned int CharNumberSpecial<char, unsigned int>::strToNum(const char *const &ps, char **const &pcEnd) {
        return (unsigned int) CharNumberSpecial<char, unsigned long>::strToNum(ps, pcEnd);
    }

    unsigned short CharNumberSpecial<char, unsigned short>::strToNum(const char *const &ps, char **const &pcEnd) {
        return (unsigned short) CharNumberSpecial<char, unsigned long>::strToNum(ps, pcEnd);
    }

    long long CharNumberSpecial<char, long long>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtoll(ps, pcEnd, 10);
    }

    unsigned long long CharNumberSpecial<char, unsigned long long>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtoull(ps, pcEnd, 10);
    }

    float CharNumberSpecial<char, float>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtof(ps, pcEnd);
    }

    double CharNumberSpecial<char, double>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtod(ps, pcEnd);
    }

    long double CharNumberSpecial<char, long double>::strToNum(const char *const &ps, char **const &pcEnd) {
        return strtold(ps, pcEnd);
    }

    //wchar_t
    long CharNumberSpecial<wchar_t, long>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstol(ps, pcEnd, 10);
    }

    int CharNumberSpecial<wchar_t, int>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return int(CharNumberSpecial<wchar_t, long>::strToNum(ps, pcEnd));
    }

    short CharNumberSpecial<wchar_t, short>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return short(CharNumberSpecial<wchar_t, long>::strToNum(ps, pcEnd));
    }

    unsigned long CharNumberSpecial<wchar_t, unsigned long>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstoul(ps, pcEnd, 10);
    }

    unsigned int CharNumberSpecial<wchar_t, unsigned int>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return (unsigned int) CharNumberSpecial<wchar_t, unsigned long>::strToNum(ps, pcEnd);
    }

    unsigned short CharNumberSpecial<wchar_t, unsigned short>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return (unsigned short) CharNumberSpecial<wchar_t, unsigned long>::strToNum(ps, pcEnd);
    }

    long long CharNumberSpecial<wchar_t, long long>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstoll(ps, pcEnd, 10);
    }

    unsigned long long CharNumberSpecial<wchar_t, unsigned long long>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstoull(ps, pcEnd, 10);
    }

    float CharNumberSpecial<wchar_t, float>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstof(ps, pcEnd);
    }

    double CharNumberSpecial<wchar_t, double>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstod(ps, pcEnd);
    }

    long double CharNumberSpecial<wchar_t, long double>::strToNum(const wchar_t *const &ps, wchar_t **const &pcEnd) {
        return wcstold(ps, pcEnd);
    }

    //array special
    template<typename AT, typename JT>
    AT
    ArraySpecial<AT, JT>::buildByList(std::list<JT> &&l) {
        AT a;
        for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) a.push_back(std::move(*i));
        return a;
    }

    template<typename JT>
    std::forward_list<JT>
    ArraySpecial<std::forward_list<JT>, JT>::buildByList(std::list<JT> &&l) {
        std::forward_list<JT> fl;
        typename std::list<JT>::iterator i;
        for (i = l.end(), i--; i != l.begin(); i--) fl.push_front(std::move(*i));
        fl.push_front(std::move(*i));
        return fl;
    }

    template<typename JT>
    std::list<JT>
    ArraySpecial<std::list<JT>, JT>::buildByList(std::list<JT> &&l) {
        return std::move(l);
    }

    template<typename JT>
    std::vector<JT>
    ArraySpecial<std::vector<JT>, JT>::buildByList(std::list<JT> &&l) {
        std::vector<JT> v(l.size());
        typename std::vector<JT>::iterator i1 = v.begin();
        for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++, i1++) i1->swap(*i);
        return v;
    }

    template<typename JT>
    std::set<JT>
    ArraySpecial<std::set<JT>, JT>::buildByList(std::list<JT> &&l) {
        std::set<JT> st;
        for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) st.insert(std::move(*i));
        return st;
    }

    template<typename JT>
    std::multiset<JT>
    ArraySpecial<std::multiset<JT>, JT>::buildByList(std::list<JT> &&l) {
        std::multiset<JT> st;
        for (typename std::list<JT>::iterator i = l.begin(); i != l.end(); i++) st.insert(std::move(*i));
        return st;
    }

}
