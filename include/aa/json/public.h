//
// Created by kalo on 2015/11/1.
//

#pragma once

//string
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>
//array
#include <forward_list>
#include <list>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
//map
#include <map>
#include <unordered_map>
//others
#include <utility>
#include <memory>
#include <type_traits>

#include "../class.h"
#include "../common.h"

namespace aa {
    namespace _json {
        class Private;
    }

    template<
            typename=double,
            typename=char,
            template<typename...> class=std::deque,
            template<typename, typename...> class=std::map
    >
    class json;

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    void swap(json<NT, CT, AC, OC> &, json<NT, CT, AC, OC> &);

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    typename json<NT, CT, AC, OC>::string_type stringify(const json<NT, CT, AC, OC> &, const short &indent = -1, const short &depth = 0);

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator<(const json<NT, CT, AC, OC> &, const json<NT, CT, AC, OC> &);

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator>(const json<NT, CT, AC, OC> &, const json<NT, CT, AC, OC> &);

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator==(const json<NT, CT, AC, OC> &, const json<NT, CT, AC, OC> &);
}

#include "Private.h"
#include "Special.h"
#include "Trivial.h"
#include "JsonValue.h"
#include "JsonCore.h"
#include "Factory.h"
#include "json.h"

#include "Special.cpp"
#include "Trivial.cpp"
#include "JsonCore.cpp"
#include "Factory.cpp"
#include "json.cpp"
#include "public.cpp"