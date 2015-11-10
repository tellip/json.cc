//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "Private.h"

namespace aa {
    namespace _json {
        template<typename JT>
        class Private::JsonCore : public Private {
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
}
