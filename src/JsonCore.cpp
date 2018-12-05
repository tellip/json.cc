//
// Created by kalo on 2015/11/1.
//

#include "JsonCore.h"

namespace json {
    template<typename JT>
    JsonCore<JT>::JsonCore(JsonCategory &&jc, _JsonValue &&jv) :
            category(std::move(jc)),
            value(std::move(jv)) {
    }

    template<typename JT>
    JsonCore<JT>::~JsonCore() {
        switch (category) {
            case JC_BOOLEAN:
                delete value.pBoolean;
                break;
            case JC_NUMBER:
                delete value.pNumber;
                break;
            case JC_STRING:
                delete value.pString;
                break;
            case JC_ARRAY:
                delete value.pArray;
                break;
            case JC_OBJECT:
                delete value.pObject;
                break;
        }
    }

    template<typename JT>
    JsonCore <JT> *JsonCore<JT>::construct(JsonCategory &&jc, _JsonValue &&jv) {
        return new JsonCore(std::move(jc), std::move(jv));
    };

    template<typename JT>
    void JsonCore<JT>::destruct(JsonCore *const &pjc) {
        delete pjc;
    };
}
