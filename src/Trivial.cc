#include "Trivial.h"

namespace json {
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
            s1 += unesca < CT > (*i);
        }
        return s1;
    }

    template<typename CT>
    typename Trivial::String<CT>
    Trivial::unesca(const CT *const &s) {
        String <CT> s1;
        for (const CT *p = s; *p; p++) {
            s1 += unesca < CT > (*p);
        }
        return s1;
    }

    template<typename JT>
    typename JT::String Trivial::arr2str(const typename JT::Array &a, const short &indent, const short &depth) {
        using Array=typename JT::Array;
        using CS=CS<typename JT::Char>;

        typename JT::String ws;
        ws += CS::arrLeft;
        if (!a.empty()) {
            typename Array::const_iterator i = a.begin();
            if (indent >= 0) {
                ws += CS::lineBreak;
                for (short si = 0; si < depth + 1; si++) ws.append(indent, CS::blankSpace);
            }
            ws += JT::stringify(*i, indent, depth + 1);
            for (i++; i != a.end(); i++) {
                ws += CS::sepSym;
                if (indent >= 0) {
                    ws += CS::lineBreak;
                    for (short si = 0; si < depth + 1; si++) ws.append(indent, CS::blankSpace);
                }
                ws += JT::stringify(*i, indent, depth + 1);
            }
        }
        if (indent >= 0 && !a.empty()) {
            ws += CS::lineBreak;
            for (short si = 0; si < depth; si++) ws.append(indent, CS::blankSpace);
        }
        ws += CS::arrRight;
        return ws;
    }

    template<typename JT>
    typename JT::String Trivial::obj2str(const typename JT::Object &o, const short &indent, const short &depth) {
        using Char=typename JT::Char;
        using Object=typename JT::Object;
        using CS=CS<Char>;

        typename JT::String ws;
        ws += CS::objLeft;
        if (!o.empty()) {
            typename Object::const_iterator i = o.begin();
            if (indent >= 0) {
                ws += CS::lineBreak;
                for (short si = 0; si < depth + 1; si++) ws.append(indent, CS::blankSpace);
            }
            ws += CS::strBound + unesca<Char>(i->first) + CS::strBound + CS::referSym;
            if (indent >= 0) ws += CS::blankSpace;
            ws += JT::stringify(i->second, indent, depth + 1);
            for (i++; i != o.end(); i++) {
                ws += CS::sepSym;
                if (indent >= 0) {
                    ws += CS::lineBreak;
                    for (short si = 0; si < depth + 1; si++) ws.append(indent, CS::blankSpace);
                }
                ws += CS::strBound + unesca<Char>(i->first) + CS::strBound + CS::referSym;
                if (indent >= 0) ws += CS::blankSpace;
                ws += JT::stringify(i->second, indent, depth + 1);
            }
        }
        if (indent >= 0 && !o.empty()) {
            ws += CS::lineBreak;
            for (short si = 0; si < depth; si++) ws.append(indent, CS::blankSpace);
        }
        ws += CS::objRight;
        return ws;
    }

    template<typename JT>
    typename JT::String Trivial::pjc2str(JsonCore <JT> *const &pjc, const short &indent, const short &depth) {
        using Char=typename JT::Char;
        using String=typename JT::String;
        static const std::unordered_map<JsonCategory, std::function<String()>> SWITCH = {
                {JC_NULL,    [&]() { return CS<Char>::nullSym; }},
                {JC_BOOLEAN, [&]() { return bl2str<Char>(*pjc->value.pBoolean); }},
                {JC_NUMBER,  [&]() { return nmb2str<Char, typename JT::Number>(*pjc->value.pNumber); }},
                {JC_STRING,  [&]() { return CS<Char>::strBound + unesca<Char>(*pjc->value.pString) + CS<Char>::strBound; }},
                {JC_ARRAY,   [&]() { return arr2str<JT>(*pjc->value.pArray, indent, depth); }},
                {JC_OBJECT,  [&]() { return obj2str<JT>(*pjc->value.pObject, indent, depth); }}
        };
        return SWITCH.at(pjc->category)();
    }
}