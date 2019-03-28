#pragma once

#include "hub.h"

namespace json {
    template<typename JT>
    union JsonValue {
        void *pNull;
        bool *pBoolean;
        typename JT::Number *pNumber;
        typename JT::String *pString;
        typename JT::Array *pArray;
        typename JT::Object *pObject;
    };
}
