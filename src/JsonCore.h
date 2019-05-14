#pragma once

#include "json.h"

namespace json {
    template<typename JT>
    class JsonCore {
    private:
        using _JsonValue= JsonValue<JT>;
    public:
        const JsonCategory category;
        const _JsonValue value;
    private:
        JsonCore(JsonCategory &&, _JsonValue &&);

        ~JsonCore();

    public:
        static JsonCore *construct(JsonCategory &&, _JsonValue &&);

        static void destruct(JsonCore *const &);
    };
}
