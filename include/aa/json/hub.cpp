//
// Created by kalo on 2015/11/1.
//

#include "hub.h"

template<
        typename NT,
        typename ST,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
void swap(aa::Json<NT, ST, AC, OC> &j1, aa::Json<NT, ST, AC, OC> &j2) {
    j1.swap(j2);
};

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator<(const aa::Json<NT, CT, AC, OC> &j1, const aa::Json<NT, CT, AC, OC> &j2) {
    aa::_json::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return jct1 < jct2;
    switch (jct1) {
        case aa::_json::JC_NULL:
            return false;
        case aa::_json::JC_BOOLEAN:
            return j1.b() < j2.b();
        case aa::_json::JC_NUMBER:
            return j1.n() < j2.n();
        case aa::_json::JC_STRING:
            return j1.s() < j2.s();
        case aa::_json::JC_ARRAY:
            return j1.a() < j2.a();
        case aa::_json::JC_OBJECT:
            return j1.o() < j2.o();
    }
}

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator>(const aa::Json<NT, CT, AC, OC> &j1, const aa::Json<NT, CT, AC, OC> &j2) {
    aa::_json::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return jct1 > jct2;
    switch (jct1) {
        case aa::_json::JC_NULL:
            return false;
        case aa::_json::JC_BOOLEAN:
            return j1.b() > j2.b();
        case aa::_json::JC_NUMBER:
            return j1.n() > j2.n();
        case aa::_json::JC_STRING:
            return j1.s() > j2.s();
        case aa::_json::JC_ARRAY:
            return j1.a() > j2.a();
        case aa::_json::JC_OBJECT:
            return j1.o() > j2.o();
    }
}

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator==(const aa::Json<NT, CT, AC, OC> &j1, const aa::Json<NT, CT, AC, OC> &j2) {
    aa::_json::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return false;
    switch (jct1) {
        case aa::_json::JC_NULL:
            return true;
        case aa::_json::JC_BOOLEAN:
            return j1.b() == j2.b();
        case aa::_json::JC_NUMBER:
            return j1.n() == j2.n();
        case aa::_json::JC_STRING:
            return j1.s() == j2.s();
        case aa::_json::JC_ARRAY:
            return j1.a() == j2.a();
        case aa::_json::JC_OBJECT:
            return j1.o() == j2.o();
    }
}
