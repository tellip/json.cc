//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace aa {
    namespace _json {
        class Trivial {
        STATIC(Trivial)

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

            template<typename CT, typename AT>
            static String<CT> arr2str(const AT &, const short &indent = -1, const short &depth = 0);

            template<typename CT, typename OT>
            static String<CT> obj2str(const OT &, const short &indent = -1, const short &depth = 0);

            template<typename CT, typename NT, typename AT, typename OT, typename JCT>
            static String<CT> pjc2str(JCT *const &, const short &indent = -1, const short &depth = 0);
        };
    }
}
