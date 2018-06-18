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
void swap(jsoncpp::Json<NT, ST, AC, OC> &j1, jsoncpp::Json<NT, ST, AC, OC> &j2) {
    j1.swap(j2);
};

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator<(const jsoncpp::Json<NT, CT, AC, OC> &j1, const jsoncpp::Json<NT, CT, AC, OC> &j2) {
    jsoncpp::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return jct1 < jct2;
    switch (jct1) {
        case jsoncpp::JC_NULL:
            return false;
        case jsoncpp::JC_BOOLEAN:
            return j1.b() < j2.b();
        case jsoncpp::JC_NUMBER:
            return j1.n() < j2.n();
        case jsoncpp::JC_STRING:
            return j1.s() < j2.s();
        case jsoncpp::JC_ARRAY:
            return j1.a() < j2.a();
        case jsoncpp::JC_OBJECT:
            return j1.o() < j2.o();
    }
}

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator>(const jsoncpp::Json<NT, CT, AC, OC> &j1, const jsoncpp::Json<NT, CT, AC, OC> &j2) {
    jsoncpp::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return jct1 > jct2;
    switch (jct1) {
        case jsoncpp::JC_NULL:
            return false;
        case jsoncpp::JC_BOOLEAN:
            return j1.b() > j2.b();
        case jsoncpp::JC_NUMBER:
            return j1.n() > j2.n();
        case jsoncpp::JC_STRING:
            return j1.s() > j2.s();
        case jsoncpp::JC_ARRAY:
            return j1.a() > j2.a();
        case jsoncpp::JC_OBJECT:
            return j1.o() > j2.o();
    }
}

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator==(const jsoncpp::Json<NT, CT, AC, OC> &j1, const jsoncpp::Json<NT, CT, AC, OC> &j2) {
    jsoncpp::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
    if (jct1 != jct2) return false;
    switch (jct1) {
        case jsoncpp::JC_NULL:
            return true;
        case jsoncpp::JC_BOOLEAN:
            return j1.b() == j2.b();
        case jsoncpp::JC_NUMBER:
            return j1.n() == j2.n();
        case jsoncpp::JC_STRING:
            return j1.s() == j2.s();
        case jsoncpp::JC_ARRAY:
            return j1.a() == j2.a();
        case jsoncpp::JC_OBJECT:
            return j1.o() == j2.o();
    }
}
