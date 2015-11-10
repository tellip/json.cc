//
// Created by kalo on 2015/11/1.
//

#include "Factory.h"

namespace aa {
    namespace _json {
        template<typename JT>
        void Private::JCoreFactory<JT>::passThrough(StrIter &iNow, const StrIter &iEnd) const {
            StrIter iBegin;
            do {
                iBegin = iNow;
                passSpace(iNow, iEnd);
                passLineComment(iNow, iEnd);
                passBlockComment(iNow, iEnd);
            } while (iNow > iBegin);
        }

        template<typename JT>
        void Private::JCoreFactory<JT>::passSpace(StrIter &iNow, const StrIter &iEnd) const {
            for (; iNow != iEnd && std::isspace(*iNow); iNow++);
        }

        template<typename JT>
        void Private::JCoreFactory<JT>::passLineComment(StrIter &iNow, const StrIter &iEnd) const {
            if (CS::StrNCmp(
                    &*iNow,
                    &*CS::lnCmtHd.begin(),
                    CS::lnCmtHd.size()
            ))
                return;
            for (iNow += CS::lnCmtHd.size(); iNow != iEnd && *iNow != CS::lineBreak; iNow++);
            if (iNow != iEnd) iNow++;
        }

        template<typename JT>
        void Private::JCoreFactory<JT>::passBlockComment(StrIter &iNow, const StrIter &iEnd) const {
            if (CS::StrNCmp(
                    &*iNow,
                    &*CS::bkCmtHd.begin(),
                    CS::bkCmtHd.size()
            ))
                return;
            for (iNow += CS::bkCmtHd.size(); iNow != iEnd && CS::StrNCmp(
                    &*iNow,
                    &*CS::bkCmtTl.begin(),
                    CS::bkCmtTl.size()
            ); iNow++);
            if (iNow != iEnd) iNow += CS::bkCmtTl.size();
        }

        template<typename JT>
        bool Private::JCoreFactory<JT>::is_string(StrIter &iNow, const StrIter &iEnd, String &s) const {
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
        typename Private::JCoreFactory<JT>::JsonCore *
        Private::JCoreFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
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
        typename Private::JsonCore<JT> *
        Private::JCNullFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
            if (CS::StrNCmp(
                    &*iNow,
                    &*CS::nullSym.begin(),
                    CS::nullSym.size()
            ))
                return NULL;
            iNow += CS::nullSym.size();
            return JsonCore::construct(JC_NULL, JsonValue{.pNull=NULL});
        }

        template<typename JT>
        typename Private::JsonCore<JT> *
        Private::JCNullFactory<JT>::byEntity() const {
            return JsonCore::construct(JC_NULL, JsonValue{.pNull=NULL});
        }

        template<typename JT>
        typename Private::JsonCore<JT> *
        Private::JCBooleanFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
            if (!CS::StrNCmp(
                    &*iNow,
                    &*CS::boolTrue.begin(),
                    CS::boolTrue.size()
            )) {
                iNow += CS::boolTrue.size();
                return JsonCore::construct(JC_BOOLEAN, JsonValue{.pBoolean=new bool(true)});
            }
            if (!CS::StrNCmp(
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
        typename Private::JsonCore<JT> *
        Private::JCBooleanFactory<JT>::byEntity(T &&t) const {
            return JsonCore::construct(JC_BOOLEAN, JsonValue{.pBoolean=new bool(std::forward<T>(t))});
        }

        template<typename JT>
        typename Private::JsonCore<JT> *
        Private::JCNumberFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
            long double ldBig;
//            if (random(2)) {
            Char *pcEnd;
            ldBig = CS::StrToLd(&*iNow, &pcEnd);
////                if (*pcEnd) return NULL; //wrong: don't have to be end
            if (pcEnd == &*iNow) return NULL;
            iNow += pcEnd - &*iNow;
//            } else {
//                int iPrec;
//                CS::StrScanf(&*iNow, &*CS::ldScnfFmt.begin(), &ldBig, &iPrec);
////                if (iPrec != iEnd - iNow) return NULL; //wrong: don't have to be end
//                if(!iPrec) return NULL;
//                iNow += iPrec;
//            }
            return JsonCore::construct(JC_NUMBER, JsonValue{.pNumber=new Number(std::move(ldBig))});
        }

        template<typename JT>
        template<typename T>
        typename Private::JsonCore<JT> *
        Private::JCNumberFactory<JT>::byEntity(T &&t) const {
            return JsonCore::construct(JC_NUMBER, JsonValue{.pNumber=new Number(std::forward<T>(t))});
        }

        template<typename JT>
        typename Private::JsonCore<JT> *
        Private::JCStringFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
            const StrIter iBegin = iNow;
            String s;
            if (!JCoreFactory::is_string(iNow, iEnd, s)) {
                iNow = iBegin;
                return NULL;
            }
            return JsonCore::construct(JC_STRING, JsonValue{.pString=new String(std::move(s))});
        }

        template<typename JT>
        template<typename T>
        typename Private::JsonCore<JT> *
        Private::JCStringFactory<JT>::byEntity(T &&t) const {
            return JsonCore::construct(JC_STRING, JsonValue{.pString=new String(std::forward<T>(t))});
        }

        template<typename JT>
        typename Private::JsonCore<JT> *
        Private::JCArrayFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
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
                Array a(l.size());
                typename std::list<JT>::iterator il;
                typename Array::iterator ia;
                for (il = l.begin(), ia = a.begin(); il != l.end(); il++, ia++) {
                    ia->swap(*il);
                }
                return JsonCore::construct(JC_ARRAY, JsonValue{.pArray=new Array(move(a))});
            } catch (...) {
                iNow = iBegin;
                return NULL;
            }

        }

        template<typename JT>
        template<typename T>
        typename Private::JsonCore<JT> *
        Private::JCArrayFactory<JT>::byEntity(T &&t) const {
            return JsonCore::construct(JC_ARRAY, JsonValue{.pArray=new Array(std::forward<T>(t))});
        }

        template<typename JT>
        typename Private::JsonCore<JT> *
        Private::JCObjectFactory<JT>::byParsing(StrIter &iNow, const StrIter &iEnd) const {
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
                    if (JCoreFactory::is_string(iNow, iEnd, key)) {
                        if (iNow == iEnd) throw NULL;
                        JCoreFactory::passThrough(iNow, iEnd);
                        if (iNow == iEnd) throw NULL;
                        if (*iNow != CS::referSym) throw NULL;
                        iNow++;
                        if (iNow == iEnd) throw NULL;
                        JsonCore *pjc = JCoreFactory::byParsing(iNow, iEnd);
                        if (!pjc) throw NULL;
                        o.insert(std::pair<String,JT>(std::move(key), JT(pjc)));
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
        typename Private::JsonCore<JT> *
        Private::JCObjectFactory<JT>::byEntity(T &&t) const {
            return JsonCore::construct(JC_OBJECT, JsonValue{.pObject=new Object(std::forward<T>(t))});
        }
    }
}