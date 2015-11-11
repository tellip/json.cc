//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace aa {
    template<typename JT>
    union _Json::JsonValue {
        void *pNull;
        bool *pBoolean;
        typename JT::Number *pNumber;
        typename JT::String *pString;
        typename JT::Array *pArray;
        typename JT::Object *pObject;
    };
}
