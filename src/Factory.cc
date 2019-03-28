#include "Factory.h"

namespace json {
    template<typename JT>
    void JCoreFactory<JT>::passThrough(_StrIter &iNow, const _StrIter &iEnd) const {
        _StrIter iBegin;
        do {
            iBegin = iNow;
            passSpace(iNow, iEnd);
            passLineComment(iNow, iEnd);
            passBlockComment(iNow, iEnd);
        } while (iNow > iBegin);
    }

    template<typename JT>
    void JCoreFactory<JT>::passSpace(_StrIter &iNow, const _StrIter &iEnd) const {
        for (; iNow != iEnd && std::isspace(*iNow); iNow++);
    }

    template<typename JT>
    void JCoreFactory<JT>::passLineComment(_StrIter &iNow, const _StrIter &iEnd) const {
        if (_CS::strNCmp(
                &*iNow,
                &*_CS::lnCmtHd.begin(),
                _CS::lnCmtHd.size()
        ))
            return;
        for (iNow += _CS::lnCmtHd.size(); iNow != iEnd && *iNow != _CS::lineBreak; iNow++);
        if (iNow != iEnd) iNow++;
    }

    template<typename JT>
    void JCoreFactory<JT>::passBlockComment(_StrIter &iNow, const _StrIter &iEnd) const {
        if (_CS::strNCmp(
                &*iNow,
                &*_CS::bkCmtHd.begin(),
                _CS::bkCmtHd.size()
        ))
            return;
        for (iNow += _CS::bkCmtHd.size(); iNow != iEnd && _CS::strNCmp(
                &*iNow,
                &*_CS::bkCmtTl.begin(),
                _CS::bkCmtTl.size()
        ); iNow++);
        if (iNow != iEnd) iNow += _CS::bkCmtTl.size();
    }

    template<typename JT>
    bool JCoreFactory<JT>::isString(_StrIter &iNow, const _StrIter &iEnd, _String &s) const {
        s = _String();
        if (*iNow != _CS::strBound) return false;
        for (iNow++; iNow != iEnd; iNow++) {
            switch (*iNow) {
                case _CS::escapeSym:
                    if (iEnd - iNow <= 2) return false;
                    iNow++;
                    s += Trivial::escape(*iNow);
                    break;
                case _CS::strBound:
                    iNow++;
                    return true;
                default:
                    s += *iNow;
            }
        }
        return false;
    }

    template<typename JT>
    JsonCore <JT> *JCoreFactory<JT>::byParsing(_StrIter &iNow, const _StrIter &iEnd) const {
        const _StrIter iBegin = iNow;
        try {
            passThrough(iNow, iEnd);
            if (iNow == iEnd) throw nullptr;
            _JsonCore *pjc;
            while (true) {
                if (pjc = _JCNullFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = _JCBooleanFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = _JCNumberFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = _JCStringFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = _JCArrayFactory::pi()->byParsing(iNow, iEnd)) break;
                if (pjc = _JCObjectFactory::pi()->byParsing(iNow, iEnd)) break;
                throw nullptr;
            }
            if (iNow != iEnd) passThrough(iNow, iEnd);
            return pjc;
        } catch (...) {
            iNow = iBegin;
            return nullptr;
        }
    }

    template<typename JT>
    JsonCore <JT> *JCNullFactory<JT>::byParsing(_StrIter &iNow, const _StrIter &iEnd) const {
        if (_CS::strNCmp(
                &*iNow,
                &*_CS::nullSym.begin(),
                _CS::nullSym.size()
        ))
            return nullptr;
        iNow += _CS::nullSym.size();
        return _JsonCore::construct(JC_NULL, _JsonValue{.pNull=new nullptr_t(nullptr)});
    }

    template<typename JT>
    JsonCore <JT> *JCNullFactory<JT>::byEntity() const {
        return _JsonCore::construct(JC_NULL, _JsonValue{.pNull=new nullptr_t(nullptr)});
    }

    template<typename JT>
    JsonCore <JT> *JCBooleanFactory<JT>::byParsing(_StrIter &iNow, const _StrIter &iEnd) const {
        if (!_CS::strNCmp(
                &*iNow,
                &*_CS::boolTrue.begin(),
                _CS::boolTrue.size()
        )) {
            iNow += _CS::boolTrue.size();
            return _JsonCore::construct(JC_BOOLEAN, _JsonValue{.pBoolean=new bool(true)});
        }
        if (!_CS::strNCmp(
                &*iNow,
                &*_CS::boolFalse.begin(),
                _CS::boolFalse.size()
        )) {
            iNow += _CS::boolFalse.size();
            return _JsonCore::construct(JC_BOOLEAN, _JsonValue{.pBoolean=new bool(false)});
        }
        return nullptr;
    }

    template<typename JT>
    template<typename T>
    JsonCore <JT> *JCBooleanFactory<JT>::byEntity(T &&t) const {
        return _JsonCore::construct(JC_BOOLEAN, _JsonValue{.pBoolean=new bool(std::forward<T>(t))});
    }

    template<typename JT>
    JsonCore <JT> *JCNumberFactory<JT>::byParsing(_StrIter &iNow, const _StrIter &iEnd) const {
        _Char *pcEnd;
        _Number n = _CNS::strToNum(&*iNow, &pcEnd);
        if (pcEnd == &*iNow) return nullptr;
        iNow += pcEnd - &*iNow;
        return _JsonCore::construct(JC_NUMBER, _JsonValue{.pNumber=new _Number(std::move(n))});
    }

    template<typename JT>
    template<typename T>
    JsonCore <JT> *JCNumberFactory<JT>::byEntity(T &&t) const {
        return _JsonCore::construct(JC_NUMBER, _JsonValue{.pNumber=new _Number(std::forward<T>(t))});
    }

    template<typename JT>
    JsonCore <JT> *JCStringFactory<JT>::byParsing(_StrIter &iNow, const _StrIter &iEnd) const {
        const _StrIter iBegin = iNow;
        _String s;
        if (!isString(iNow, iEnd, s)) {
            iNow = iBegin;
            return nullptr;
        }
        return _JsonCore::construct(JC_STRING, _JsonValue{.pString=new _String(std::move(s))});
    }

    template<typename JT>
    template<typename T>
    JsonCore <JT> *JCStringFactory<JT>::byEntity(T &&t) const {
        return _JsonCore::construct(JC_STRING, _JsonValue{.pString=new _String(std::forward<T>(t))});
    }

    template<typename JT>
    JsonCore <JT> *JCArrayFactory<JT>::byParsing(_StrIter &iNow, const _StrIter &iEnd) const {
        const _StrIter iBegin = iNow;
        try {
            if (*iNow != _CS::arrLeft) throw nullptr;
            iNow++;
            if (iNow == iEnd) throw nullptr;
            std::list<JT> l;
            while (true) {
                _JsonCore *pjc = _Base::byParsing(iNow, iEnd);
                if (pjc) {
                    l.push_back(JT(std::move(pjc)));
                    if (iNow == iEnd) throw nullptr;
                    if (*iNow == _CS::sepSym) {
                        iNow++;
                        if (iNow == iEnd) throw nullptr;
                    } else if (*iNow != _CS::arrRight) throw nullptr;
                    else break;
                } else {
                    passThrough(iNow, iEnd);
                    if (iNow == iEnd || *iNow != _CS::arrRight) throw nullptr;
                    break;
                }
            }
            iNow++;
            return _JsonCore::construct(JC_ARRAY, _JsonValue{.pArray=new _Array(_AS::buildByList(std::move(l)))});
        } catch (...) {
            iNow = iBegin;
            return nullptr;
        }

    }

    template<typename JT>
    template<typename T>
    JsonCore <JT> *JCArrayFactory<JT>::byEntity(T &&t) const {
        return _JsonCore::construct(JC_ARRAY, _JsonValue{.pArray=new _Array(std::forward<T>(t))});
    }

    template<typename JT>
    JsonCore <JT> *JCObjectFactory<JT>::byParsing(_StrIter &iNow, const _StrIter &iEnd) const {
        const _StrIter iBegin = iNow;
        try {
            if (*iNow != _CS::objLeft) throw nullptr;
            iNow++;
            if (iNow == iEnd) throw nullptr;
            _Object o;
            while (true) {
                passThrough(iNow, iEnd);
                if (iNow == iEnd) throw nullptr;
                _String key;
                if (isString(iNow, iEnd, key)) {
                    if (iNow == iEnd) throw nullptr;
                    passThrough(iNow, iEnd);
                    if (iNow == iEnd) throw nullptr;
                    if (*iNow != _CS::referSym) throw nullptr;
                    iNow++;
                    if (iNow == iEnd) throw nullptr;
                    _JsonCore *pjc = _Base::byParsing(iNow, iEnd);
                    if (!pjc) throw nullptr;
                    o.insert(std::pair<_String, JT>(std::move(key), JT(std::move(pjc))));
                    if (iNow == iEnd) throw nullptr;
                    if (*iNow == _CS::sepSym) {
                        iNow++;
                        if (iNow == iEnd) throw nullptr;
                    } else if (*iNow != _CS::objRight) throw nullptr;
                    else break;
                } else {
                    passThrough(iNow, iEnd);
                    if (iNow == iEnd || *iNow != _CS::objRight) throw nullptr;
                    break;
                }
            }
            iNow++;
            return _JsonCore::construct(JC_OBJECT, _JsonValue{.pObject=new _Object(move(o))});
        } catch (...) {
            iNow = iBegin;
            return nullptr;
        }
    }

    template<typename JT>
    template<typename T>
    JsonCore <JT> *JCObjectFactory<JT>::byEntity(T &&t) const {
        return _JsonCore::construct(JC_OBJECT, _JsonValue{.pObject=new _Object(std::forward<T>(t))});
    }
}