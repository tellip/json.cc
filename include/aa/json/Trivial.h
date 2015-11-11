//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace aa {
    template<typename JT>
    class _Json::Trivial : public _Json {
    STATIC(Trivial)

    private:
        using Number= typename JT::Number;
        using Char= typename JT::Char;
        using String= typename JT::String;
        using Array= typename JT::Array;
        using Object= typename JT::Object;
        using JsonCore= JsonCore<JT>;
        using CS= CharSpecial<Char>;
        static const unsigned short numPrec;
    public:
        static String bl2str(const bool &);

        static String nmb2str(const Number &);

        static Char escape(const Char &);

        static String unesca(const Char &);

        static String unesca(const String &);

        static String unesca(const Char *const &);

        static String arr2str(const Array &, const short &indent = -1, const short &depth = 0);

        static String obj2str(const Object &, const short &indent = -1, const short &depth = 0);

        static String pjc2str(JsonCore *const &, const short &indent = -1, const short &depth = 0);
    };
}
