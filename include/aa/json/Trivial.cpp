//
// Created by kalo on 2015/11/1.
//

#include "Trivial.h"

namespace aa {
    namespace _json {
        template<typename JT>
        const unsigned short Private::Trivial<JT>::numPrec = 17;

        template<typename JT>
        typename Private::Trivial<JT>::String
        Private::Trivial<JT>::bl2str(const bool &b) {
            return b ? CS::boolTrue : CS::boolFalse;
        }

        template<typename JT>
        typename Private::Trivial<JT>::String
        Private::Trivial<JT>::nmb2str(const Number &d) {
            typename CS::Oss os;
            os << std::setprecision(numPrec) << d;
            return os.str();
        }

        template<typename JT>
        typename Private::Trivial<JT>::Char
        Private::Trivial<JT>::escape(const Char &c) {
            try {
                return CS::escapeMap.at(c);
            } catch (...) {
                return c;
            }
        }

        template<typename JT>
        typename Private::Trivial<JT>::String
        Private::Trivial<JT>::unesca(const Char &c) {
            try {
                return String() + CS::escapeSym + CS::unescaMap.at(c);
            } catch (...) {
                return String() + c;
            }
        }

        template<typename JT>
        typename Private::Trivial<JT>::String
        Private::Trivial<JT>::unesca(const String &s) {
            String s1;
            for (typename String::const_iterator i = s.begin(); i != s.end(); i++) {
                s1 += unesca(*i);
            }
            return s1;
        }

        template<typename JT>
        typename Private::Trivial<JT>::String
        Private::Trivial<JT>::unesca(const Char *const &s) {
            String s1;
            for (const Char *p = s; *p; p++) {
                s1 += unesca(*p);
            }
            return s1;
        }

        template<typename JT>
        typename Private::Trivial<JT>::String
        Private::Trivial<JT>::arr2str(const Array &a, const short &indent, const short &depth) {
            String ws;
            ws += CS::arrLeft;
            if (a.begin() != a.end()) {
                typename Array::const_iterator i = a.begin();
                if (indent >= 0) {
                    ws += CS::lineBreak;
                    for (short si = 0; si < depth + 1; si++) ws.append(indent, CS::blankSpace);
                }
                ws += stringify(*i, indent, depth + 1);
                for (i++; i != a.end(); i++) {
                    ws += CS::sepSym;
                    if (indent >= 0) {
                        ws += CS::lineBreak;
                        for (short si = 0; si < depth + 1; si++) ws.append(indent, CS::blankSpace);
                    }
                    ws += aa::stringify(*i, indent, depth + 1);
                }
            }
            if (indent >= 0 && a.begin() != a.end()) {
                ws += CS::lineBreak;
                for (short si = 0; si < depth; si++) ws.append(indent, CS::blankSpace);
            }
            ws += CS::arrRight;
            return ws;
        }

        template<typename JT>
        typename Private::Trivial<JT>::String
        Private::Trivial<JT>::obj2str(const Object &o, const short &indent, const short &depth) {
            String ws;
            ws += CS::objLeft;
            if (o.size()) {
                typename Object::const_iterator i = o.begin();
                if (indent >= 0) {
                    ws += CS::lineBreak;
                    for (short si = 0; si < depth + 1; si++) ws.append(indent, CS::blankSpace);
                }
                ws += CS::strBound + unesca(i->first) + CS::strBound + CS::referSym;
                if (indent >= 0) ws += CS::blankSpace;
                ws += stringify(i->second, indent, depth + 1);
                for (i++; i != o.end(); i++) {
                    ws += CS::sepSym;
                    if (indent >= 0) {
                        ws += CS::lineBreak;
                        for (short si = 0; si < depth + 1; si++) ws.append(indent, CS::blankSpace);
                    }
                    ws += CS::strBound + unesca((String &) i->first) + CS::strBound + CS::referSym;
                    if (indent >= 0) ws += CS::blankSpace;
                    ws += aa::stringify(i->second, indent, depth + 1);
                }
            }
            if (indent >= 0 && o.size()) {
                ws += CS::lineBreak;
                for (short si = 0; si < depth; si++) ws.append(indent, CS::blankSpace);
            }
            ws += CS::objRight;
            return ws;
        }

        template<typename JT>
        typename Private::Trivial<JT>::String
        Private::Trivial<JT>::pjc2str(JsonCore *const &pjc, const short &indent, const short &depth) {
            switch (pjc->category) {
                case JC_NULL:
                    return CS::nullSym;
                case JC_BOOLEAN:
                    return bl2str(*pjc->value.pBoolean);
                case JC_NUMBER:
                    return nmb2str(*pjc->value.pNumber);
                case JC_STRING:
                    return CS::strBound + unesca(*pjc->value.pString) + CS::strBound;
                case JC_ARRAY:
                    return arr2str(*pjc->value.pArray, indent, depth);
                case JC_OBJECT:
                    return obj2str(*pjc->value.pObject, indent, depth);
            }
        }
    }
}