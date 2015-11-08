//
// Created by kalo on 2015/11/1.
//

#include "public.h"

namespace klib {
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
        return json::Private::Trivial<Json<NT, CT, AC, OC>>::pjc2str(j._pCore.get(), indent, depth);
    }
}