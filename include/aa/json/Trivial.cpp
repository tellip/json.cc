//
// Created by kalo on 2015/11/1.
//

#include "Trivial.h"

namespace aa {
    namespace _json {
        const unsigned short Trivial::numPrec = 17;

        int Trivial::precFromBinaToDeci(const int &iBinaPrec) {
            unsigned long long iCache = pow(2, iBinaPrec) - 1;
            int iDeciPrec = 0;
            while (iCache) {
                iDeciPrec++;
                iCache /= 10;
            }
            return iDeciPrec;
        }

        template<typename CT>
        typename Trivial::String<CT>
        Trivial::bl2str(const bool &b) {
            return b ? CS<CT>::boolTrue : CS<CT>::boolFalse;
        }

        template<typename CT, typename NT>
        typename Trivial::String<CT>
        Trivial::nmb2str(const NT &d) {
            typename CS<CT>::Oss os;
            os << std::setprecision(NumberSpecial<NT>::deciPrec) << d;
            return os.str();
        }

        template<typename CT>
        CT Trivial::escape(const CT &c) {
            try {
                return CS<CT>::escapeMap.at(c);
            } catch (...) {
                return c;
            }
        }

        template<typename CT>
        typename Trivial::String<CT>
        Trivial::unesca(const CT &c) {
            try {
                return String<CT>() + CS<CT>::escapeSym + CS<CT>::unescaMap.at(c);
            } catch (...) {
                return String<CT>() + c;
            }
        }

        template<typename CT>
        typename Trivial::String<CT>
        Trivial::unesca(const String <CT> &s) {
            String <CT> s1;
            for (typename String<CT>::const_iterator i = s.begin(); i != s.end(); i++) {
                s1 += unesca<CT>(*i);
            }
            return s1;
        }

        template<typename CT>
        typename Trivial::String<CT>
        Trivial::unesca(const CT *const &s) {
            String <CT> s1;
            for (const CT *p = s; *p; p++) {
                s1 += unesca<CT>(*p);
            }
            return s1;
        }

        template<typename CT, typename AT>
        typename Trivial::String<CT>
        Trivial::arr2str(const AT &a, const short &indent, const short &depth) {
            String <CT> ws;
            ws += CS<CT>::arrLeft;
            if (!a.empty()) {
                typename AT::const_iterator i = a.begin();
                if (indent >= 0) {
                    ws += CS<CT>::lineBreak;
                    for (short si = 0; si < depth + 1; si++) ws.append(indent, CS<CT>::blankSpace);
                }
                ws += stringify(*i, indent, depth + 1);
                for (i++; i != a.end(); i++) {
                    ws += CS<CT>::sepSym;
                    if (indent >= 0) {
                        ws += CS<CT>::lineBreak;
                        for (short si = 0; si < depth + 1; si++) ws.append(indent, CS<CT>::blankSpace);
                    }
                    ws += aa::stringify(*i, indent, depth + 1);
                }
            }
            if (indent >= 0 && !a.empty()) {
                ws += CS<CT>::lineBreak;
                for (short si = 0; si < depth; si++) ws.append(indent, CS<CT>::blankSpace);
            }
            ws += CS<CT>::arrRight;
            return ws;
        }

        template<typename CT, typename OT>
        typename Trivial::String<CT>
        Trivial::obj2str(const OT &o, const short &indent, const short &depth) {
            String <CT> ws;
            ws += CS<CT>::objLeft;
            if (!o.empty()) {
                typename OT::const_iterator i = o.begin();
                if (indent >= 0) {
                    ws += CS<CT>::lineBreak;
                    for (short si = 0; si < depth + 1; si++) ws.append(indent, CS<CT>::blankSpace);
                }
                ws += CS<CT>::strBound + unesca<CT>(i->first) + CS<CT>::strBound + CS<CT>::referSym;
                if (indent >= 0) ws += CS<CT>::blankSpace;
                ws += stringify(i->second, indent, depth + 1);
                for (i++; i != o.end(); i++) {
                    ws += CS<CT>::sepSym;
                    if (indent >= 0) {
                        ws += CS<CT>::lineBreak;
                        for (short si = 0; si < depth + 1; si++) ws.append(indent, CS<CT>::blankSpace);
                    }
                    ws += CS<CT>::strBound + unesca<CT>((String <CT> &) i->first) + CS<CT>::strBound + CS<CT>::referSym;
                    if (indent >= 0) ws += CS<CT>::blankSpace;
                    ws += aa::stringify(i->second, indent, depth + 1);
                }
            }
            if (indent >= 0 && !o.empty()) {
                ws += CS<CT>::lineBreak;
                for (short si = 0; si < depth; si++) ws.append(indent, CS<CT>::blankSpace);
            }
            ws += CS<CT>::objRight;
            return ws;
        }

        template<typename CT, typename NT, typename AT, typename OT, typename JCT>
        typename Trivial::String<CT>
        Trivial::pjc2str(JCT *const &pjc, const short &indent, const short &depth) {
            switch (pjc->category) {
                case JC_NULL:
                    return CS<CT>::nullSym;
                case JC_BOOLEAN:
                    return bl2str<CT>(*pjc->value.pBoolean);
                case JC_NUMBER:
                    return nmb2str<CT, NT>(*pjc->value.pNumber);
                case JC_STRING:
                    return CS<CT>::strBound + unesca<CT>(*pjc->value.pString) + CS<CT>::strBound;
                case JC_ARRAY:
                    return arr2str<CT, AT>(*pjc->value.pArray, indent, depth);
                case JC_OBJECT:
                    return obj2str<CT, OT>(*pjc->value.pObject, indent, depth);
            }
        }
    }
}