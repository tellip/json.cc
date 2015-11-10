//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "Private.h"

namespace aa {
    namespace _json {
        template<typename JT>
        union Private::JsonValue {
            void *pNull;
            bool *pBoolean;
            typename JT::number_type *pNumber;
            typename JT::string_type *pString;
            typename JT::array_type *pArray;
            typename JT::object_type *pObject;
        };
    }
}
