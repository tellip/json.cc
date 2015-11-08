//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "Private.h"

namespace aa {
    namespace json {
        template<typename JT>
        union Private::JsonValue {
            void *pNull;
            bool *pBoolean;
            typename JT::Number *pNumber;
            typename JT::String *pString;
            typename JT::Array *pArray;
            typename JT::Object *pObject;
        };
    }
}
