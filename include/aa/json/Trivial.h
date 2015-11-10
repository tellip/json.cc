//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "Private.h"

namespace aa {
    namespace _json {
        template<typename JT>
        class Private::Trivial : public Private {
        STATIC(Trivial)

        private:
            typedef typename JT::number_type Number;
            typedef typename JT::char_type Char;
            typedef typename JT::string_type String;
            typedef typename JT::array_type Array;
            typedef typename JT::object_type Object;
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
