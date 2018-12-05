//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace json {
    class Trivial {
    JSON_STATIC(Trivial)

    private:
        template<typename CT>
        using CS=CharSpecial<CT>;
        template<typename CT>
        using String=typename CS<CT>::String;
        static const unsigned short numPrec;
    public:
        static int precFromBinaToDeci(const int &);

        template<typename CT>
        static String<CT> bl2str(const bool &);

        template<typename CT, typename NT>
        static String<CT> nmb2str(const NT &);

        template<typename CT>
        static CT escape(const CT &);

        template<typename CT>
        static String<CT> unesca(const CT &);

        template<typename CT>
        static String<CT> unesca(const String<CT> &);

        template<typename CT>
        static String<CT> unesca(const CT *const &);

        template<typename JT>
        static typename JT::String arr2str(const typename JT::Array &, const short &indent = -1, const short &depth = 0);

        template<typename JT>
        static typename JT::String obj2str(const typename JT::Object &, const short &indent = -1, const short &depth = 0);

        template<typename JT>
        static typename JT::String pjc2str(JsonCore <JT> *const &, const short &indent = -1, const short &depth = 0);
    };
}
