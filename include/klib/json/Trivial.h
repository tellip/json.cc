//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "Private.h"

namespace klib {
    namespace json {
        template<typename JT>
        class Private::Trivial : public Private {
        STATIC(Trivial)

        private:
            typedef typename JT::Number Number;
            typedef typename JT::Char Char;
            typedef typename JT::String String;
            typedef typename JT::Array Array;
            typedef typename JT::Object Object;
            typedef JsonCore <JT> JsonCore;
            typedef typename Special<Char>::_ CS;
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
}
