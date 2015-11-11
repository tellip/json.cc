//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace aa {
    template<typename JT>
    class _Json::JsonCore : public _Json {
    private:
        using JsonValue= JsonValue<JT>;
    public:
        const JsonCategory category;
        const JsonValue value;
    private:
        JsonCore(JsonCategory &&, JsonValue &&);

        ~JsonCore();

    public:
        static JsonCore *construct(JsonCategory &&, JsonValue &&);

        static void destruct(JsonCore *const &);
    };
}
