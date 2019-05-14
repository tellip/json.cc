#pragma once

#include "json.h"

namespace json {
    template<typename JT>
    union JsonValue {
        nullptr_t *pNull;
        bool *pBoolean;
        typename JT::Number *pNumber;
        typename JT::String *pString;
        typename JT::Array *pArray;
        typename JT::Object *pObject;
    };
}
