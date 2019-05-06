#include "hub.h"

#include "Special.cc"
#include "Trivial.cc"
#include "JsonCore.cc"
#include "Factory.cc"
#include "Json.cc"

#include "class.cc"
#include "common.cc"

template<
        typename NT,
        typename ST,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
void swap(json::Json<NT, ST, AC, OC> &j1, json::Json<NT, ST, AC, OC> &j2) {
    j1.swap(j2);
};

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator<(const json::Json<NT, CT, AC, OC> &j1, const json::Json<NT, CT, AC, OC> &j2) {
    json::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return jct1 < jct2;
    switch (jct1) {
        case json::JC_NULL:
            return false;
        case json::JC_BOOLEAN:
            return j1.b() < j2.b();
        case json::JC_NUMBER:
            return j1.n() < j2.n();
        case json::JC_STRING:
            return j1.s() < j2.s();
        case json::JC_ARRAY:
            return j1.a() < j2.a();
        case json::JC_OBJECT:
            return j1.o() < j2.o();
    }
}

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator>(const json::Json<NT, CT, AC, OC> &j1, const json::Json<NT, CT, AC, OC> &j2) {
    json::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return jct1 > jct2;
    switch (jct1) {
        case json::JC_NULL:
            return false;
        case json::JC_BOOLEAN:
            return j1.b() > j2.b();
        case json::JC_NUMBER:
            return j1.n() > j2.n();
        case json::JC_STRING:
            return j1.s() > j2.s();
        case json::JC_ARRAY:
            return j1.a() > j2.a();
        case json::JC_OBJECT:
            return j1.o() > j2.o();
    }
}

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator==(const json::Json<NT, CT, AC, OC> &j1, const json::Json<NT, CT, AC, OC> &j2) {
    json::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return false;
    switch (jct1) {
        case json::JC_NULL:
            return true;
        case json::JC_BOOLEAN:
            return j1.b() == j2.b();
        case json::JC_NUMBER:
            return j1.n() == j2.n();
        case json::JC_STRING:
            return j1.s() == j2.s();
        case json::JC_ARRAY:
            return j1.a() == j2.a();
        case json::JC_OBJECT:
            return j1.o() == j2.o();
    }
}