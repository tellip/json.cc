//
// Created by kalo on 2015/11/1.
//

#include "public.h"

namespace aa {
    template<
            typename NT,
            typename ST,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    void swap(Json<NT, ST, AC, OC> &j1, Json<NT, ST, AC, OC> &j2) {
        j1.swap(j2);
    };

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    typename Json<NT, CT, AC, OC>::String stringify(const Json<NT, CT, AC, OC> &j, const short &indent, const short &depth) {
        return _json::Private::Trivial<Json<NT, CT, AC, OC>>::pjc2str(j._pCore.get(), indent, depth);
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator<(const Json<NT, CT, AC, OC> &j1, const Json<NT, CT, AC, OC> &j2) {
        _json::Private::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
        if (jct1 != jct2) return jct1 < jct2;
        switch (jct1) {
            case _json::Private::JC_NULL:
                return false;
            case _json::Private::JC_BOOLEAN:
                return j1.b() < j2.b();
            case _json::Private::JC_NUMBER:
                return j1.n() < j2.n();
            case _json::Private::JC_STRING:
                return j1.s() < j2.s();
            case _json::Private::JC_ARRAY:
                return j1.a() < j2.a();
            case _json::Private::JC_OBJECT:
                return j1.o() < j2.o();
        }
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator>(const Json<NT, CT, AC, OC> &j1, const Json<NT, CT, AC, OC> &j2) {
        _json::Private::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
        if (jct1 != jct2) return jct1 > jct2;
        switch (jct1) {
            case _json::Private::JC_NULL:
                return false;
            case _json::Private::JC_BOOLEAN:
                return j1.b() > j2.b();
            case _json::Private::JC_NUMBER:
                return j1.n() > j2.n();
            case _json::Private::JC_STRING:
                return j1.s() > j2.s();
            case _json::Private::JC_ARRAY:
                return j1.a() > j2.a();
            case _json::Private::JC_OBJECT:
                return j1.o() > j2.o();
        }
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator==(const Json<NT, CT, AC, OC> &j1, const Json<NT, CT, AC, OC> &j2) {
        _json::Private::JsonCategory jct1 = j1._pCore->category, jct2 = j2._pCore->category;
        if (jct1 != jct2) return false;
        switch (jct1) {
            case _json::Private::JC_NULL:
                return true;
            case _json::Private::JC_BOOLEAN:
                return j1.b() == j2.b();
            case _json::Private::JC_NUMBER:
                return j1.n() == j2.n();
            case _json::Private::JC_STRING:
                return j1.s() == j2.s();
            case _json::Private::JC_ARRAY:
                return j1.a() == j2.a();
            case _json::Private::JC_OBJECT:
                return j1.o() == j2.o();
        }
    }
}