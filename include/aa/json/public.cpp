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
    void swap(json<NT, ST, AC, OC> &j1, json<NT, ST, AC, OC> &j2) {
        j1.swap(j2);
    };

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    typename json<NT, CT, AC, OC>::string_type stringify(const json<NT, CT, AC, OC> &j, const short &indent, const short &depth) {
        return _json::Private::Trivial<json<NT, CT, AC, OC>>::pjc2str(j._pCore.get(), indent, depth);
    }
}