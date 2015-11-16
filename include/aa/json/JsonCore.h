//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace aa {
    namespace _json {
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
}
