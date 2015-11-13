//
// Created by kalo on 2015/11/1.
//

#include "Factory.h"

namespace aa {
    template<typename JT>
    void _Json::JCoreFactory<JT>::passThrough(StrIter &iNow, const StrIter &iEnd) const {
        StrIter iBegin;
        do {
            iBegin = iNow;
            passSpace(iNow, iEnd);
            passLineComment(iNow, iEnd);
            passBlockComment(iNow, iEnd);
        } while (iNow > iBegin);
    }

    template<typename JT>
    void _Json::JCoreFactory<JT>::passSpace(StrIter &iNow, const StrIter &iEnd) const {
        for (; iNow != iEnd && std::isspace(*iNow); iNow++);
    }

    template<typename JT>
    void _Json::JCoreFactory<JT>::passLineComment(StrIter &iNow, const StrIter &iEnd) const {
        if (CS::strNCmp(
                &*iNow,
                &*CS::lnCmtHd.begin(),
                CS::lnCmtHd.size()
        ))
            return;
        for (iNow += CS::lnCmtHd.size(); iNow != iEnd && *iNow != CS::lineBreak; iNow++);
        if (iNow != iEnd) iNow++;
    }

    template<typename JT>
    void _Json::JCoreFactory<JT>::passBlockComment(StrIter &iNow, const StrIter &iEnd) const {
        if (CS::strNCmp(
                &*iNow,
                &*CS::bkCmtHd.begin(),
                CS::bkCmtHd.size()
        ))
            return;
        for (iNow += CS::bkCmtHd.size(); iNow != iEnd && CS::strNCmp(
                &*iNow,
                &*CS::bkCmtTl.begin(),
                CS::bkCmtTl.size()
        ); iNow++);
        if (iNow != iEnd) iNow += CS::bkCmtTl.size();
    }

    template<typename JT>
    bool _Json::JCoreFactory<JT>::isString(StrIter &iNow, const StrIter &iEnd, String &s) const {
        s = String();
        if (*iNow != CS::strBound) return false;
        for (iNow++; iNow != iEnd; iNow++) {
            switch (*iNow) {
                case CS::escapeSym:
                    if (iEnd - iNow <= 2) return false;
                    iNow++;
                    s += Trivial::escape(*iNow);
                    break;
                case CS::strBound:
                    iNow++;
                    return true;
                default:
                    s += *iNow;
            }
        }
        return false;
    }

    template<typename JT>
    typename _Json::JCoreFactory<JT>::JsonCore *
    _Json::JCoreFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
        const StrIter iBegin = iNow;
        try {
            passThrough(iNow, iEnd);
            if (iNow == iEnd) throw NULL;
            JsonCore *pjc;
            while (true) {
                if (pjc = JCNullFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = JCBooleanFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = JCNumberFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = JCStringFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = JCArrayFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = JCObjectFactory::pi()->byParsing(iNow, iEnd)) break;
                throw NULL;
            }
            if (iNow != iEnd) passThrough(iNow, iEnd);
            return pjc;
        } catch (...) {
            iNow = iBegin;
            return NULL;
        }
    }

    template<typename JT>
    typename _Json::JsonCore<JT> *
    _Json::JCNullFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
        if (CS::strNCmp(
                &*iNow,
                &*CS::nullSym.begin(),
                CS::nullSym.size()
        ))
            return NULL;
        iNow += CS::nullSym.size();
        return JsonCore::construct(JC_NULL, JsonValue{.pNull=NULL});
    }

    template<typename JT>
    typename _Json::JsonCore<JT> *
    _Json::JCNullFactory<JT>::byEntity() const {
        return JsonCore::construct(JC_NULL, JsonValue{.pNull=NULL});
    }

    template<typename JT>
    typename _Json::JsonCore<JT> *
    _Json::JCBooleanFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
        if (!CS::strNCmp(
                &*iNow,
                &*CS::boolTrue.begin(),
                CS::boolTrue.size()
        )) {
            iNow += CS::boolTrue.size();
            return JsonCore::construct(JC_BOOLEAN, JsonValue{.pBoolean=new bool(true)});
        }
        if (!CS::strNCmp(
                &*iNow,
                &*CS::boolFalse.begin(),
                CS::boolFalse.size()
        )) {
            iNow += CS::boolFalse.size();
            return JsonCore::construct(JC_BOOLEAN, JsonValue{.pBoolean=new bool(false)});
        }
        return NULL;
    }

    template<typename JT>
    template<typename T>
    typename _Json::JsonCore<JT> *
    _Json::JCBooleanFactory<JT>::byEntity(T &&t) const {
        return JsonCore::construct(JC_BOOLEAN, JsonValue{.pBoolean=new bool(std::forward<T>(t))});
    }

    template<typename JT>
    typename _Json::JsonCore<JT> *
    _Json::JCNumberFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
        Char *pcEnd;
        Number n = CNS::strToNum(&*iNow, &pcEnd);
        if (pcEnd == &*iNow) return NULL;
        iNow += pcEnd - &*iNow;
        return JsonCore::construct(JC_NUMBER, JsonValue{.pNumber=new Number(std::move(n))});
    }

    template<typename JT>
    template<typename T>
    typename _Json::JsonCore<JT> *
    _Json::JCNumberFactory<JT>::byEntity(T &&t) const {
        return JsonCore::construct(JC_NUMBER, JsonValue{.pNumber=new Number(std::forward<T>(t))});
    }

    template<typename JT>
    typename _Json::JsonCore<JT> *
    _Json::JCStringFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
        const StrIter iBegin = iNow;
        String s;
        if (!JCoreFactory::isString(iNow, iEnd, s)) {
            iNow = iBegin;
            return NULL;
        }
        return JsonCore::construct(JC_STRING, JsonValue{.pString=new String(std::move(s))});
    }

    template<typename JT>
    template<typename T>
    typename _Json::JsonCore<JT> *
    _Json::JCStringFactory<JT>::byEntity(T &&t) const {
        return JsonCore::construct(JC_STRING, JsonValue{.pString=new String(std::forward<T>(t))});
    }

    template<typename JT>
    typename _Json::JsonCore<JT> *
    _Json::JCArrayFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
        const StrIter iBegin = iNow;
        try {
            if (*iNow != CS::arrLeft) throw NULL;
            iNow++;
            if (iNow == iEnd) throw NULL;
            std::list<JT> l;
            while (true) {
                JsonCore *pjc = JCoreFactory::byParsing(iNow, iEnd);
                if (pjc) {
                    l.push_back(JT(pjc));
                    if (iNow == iEnd) throw NULL;
                    if (*iNow == CS::sepSym) {
                        iNow++;
                        if (iNow == iEnd) throw NULL;
                    } else if (*iNow != CS::arrRight) throw NULL;
                    else break;
                } else {
                    JCoreFactory::passThrough(iNow, iEnd);
                    if (iNow == iEnd || *iNow != CS::arrRight) throw NULL;
                    break;
                }
            }
            iNow++;
            return JsonCore::construct(JC_ARRAY, JsonValue{.pArray=new Array(AS::buildByList(std::move(l)))});
        } catch (...) {
            iNow = iBegin;
            return NULL;
        }

    }

    template<typename JT>
    template<typename T>
    typename _Json::JsonCore<JT> *
    _Json::JCArrayFactory<JT>::byEntity(T &&t) const {
        return JsonCore::construct(JC_ARRAY, JsonValue{.pArray=new Array(std::forward<T>(t))});
    }

    template<typename JT>
    typename _Json::JsonCore<JT> *
    _Json::JCObjectFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
        const StrIter iBegin = iNow;
        try {
            if (*iNow != CS::objLeft) throw NULL;
            iNow++;
            if (iNow == iEnd) throw NULL;
            Object o;
            while (true) {
                JCoreFactory::passThrough(iNow, iEnd);
                if (iNow == iEnd) throw NULL;
                String key;
                if (JCoreFactory::isString(iNow, iEnd, key)) {
                    if (iNow == iEnd) throw NULL;
                    JCoreFactory::passThrough(iNow, iEnd);
                    if (iNow == iEnd) throw NULL;
                    if (*iNow != CS::referSym) throw NULL;
                    iNow++;
                    if (iNow == iEnd) throw NULL;
                    JsonCore *pjc = JCoreFactory::byParsing(iNow, iEnd);
                    if (!pjc) throw NULL;
                    o.insert(std::pair<String, JT>(std::move(key), JT(pjc)));
                    if (iNow == iEnd) throw NULL;
                    if (*iNow == CS::sepSym) {
                        iNow++;
                        if (iNow == iEnd) throw NULL;
                    } else if (*iNow != CS::objRight) throw NULL;
                    else break;
                } else {
                    JCoreFactory::passThrough(iNow, iEnd);
                    if (iNow == iEnd || *iNow != CS::objRight) throw NULL;
                    break;
                }
            }
            iNow++;
            return JsonCore::construct(JC_OBJECT, JsonValue{.pObject=new Object(move(o))});
        } catch (...) {
            iNow = iBegin;
            return NULL;
        }
    }

    template<typename JT>
    template<typename T>
    typename _Json::JsonCore<JT> *
    _Json::JCObjectFactory<JT>::byEntity(T &&t) const {
        return JsonCore::construct(JC_OBJECT, JsonValue{.pObject=new Object(std::forward<T>(t))});
    }
}