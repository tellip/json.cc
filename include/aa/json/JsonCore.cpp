//
// Created by kalo on 2015/11/1.
//

#include "JsonCore.h"

namespace aa {
    namespace _json {
        template<typename JT>
        Private::JsonCore<JT>::JsonCore(JsonCategory &&jc, JsonValue &&jv) :
                category(std::move(jc)),
                value(std::move(jv)) {
//            static int t = 0;
//            std::cout << "c\t" << ++t << std::endl;
        }

        template<typename JT>
        Private::JsonCore<JT>::~JsonCore() {
//            static int t = 0;
//            std::cout << "d\t" << ++t << std::endl;
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
        Private::JsonCore<JT> *Private::JsonCore<JT>::construct(JsonCategory &&jc, JsonValue &&jv) {
            return new JsonCore(std::move(jc), std::move(jv));
        };

        template<typename JT>
        void Private::JsonCore<JT>::destruct(JsonCore *const &pjc) {
            delete pjc;
        };
    }
}
