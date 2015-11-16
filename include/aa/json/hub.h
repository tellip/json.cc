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
#include <cmath>

#include "../class.h"
#include "../common.h"

namespace aa {
    namespace _json {
        struct Special;

        template<typename>
        struct NumberSpecial;

        template<typename>
        struct CharSpecial;

        template<typename, typename>
        struct CharNumberSpecial;

        template<typename, typename>
        struct ArraySpecial;

        enum JsonCategory {
            JC_NULL,
            JC_BOOLEAN,
            JC_NUMBER,
            JC_STRING,
            JC_ARRAY,
            JC_OBJECT
        };

        template<typename>
        union JsonValue;

        template<typename>
        class JsonCore;

        class Factory;

        template<typename>
        class JCoreFactory;

        template<typename>
        class JCNullFactory;

        template<typename>
        class JCBooleanFactory;

        template<typename>
        class JCNumberFactory;

        template<typename>
        class JCStringFactory;

        template<typename>
        class JCArrayFactory;

        template<typename>
        class JCObjectFactory;

        class Trivial;
    }

    template<
            typename=double,
            typename=char,
            template<typename...> class=std::deque,
            template<typename, typename...> class=std::map
    >
    class Json;

    template<
            typename NT=double,
            typename CT=char,
            template<typename...> class AC=std::deque,
            template<typename, typename...> class OC=std::map
    >
    using json=Json<NT, CT, AC, OC>;

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    void swap(Json<NT, CT, AC, OC> &, Json<NT, CT, AC, OC> &);

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator<(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool operator==(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    typename _json::CharSpecial<CT>::String stringify(const Json<NT, CT, AC, OC> &, const short &indent = -1, const short &depth = 0);
}

#include "Special.h"
#include "Trivial.h"
#include "JsonValue.h"
#include "JsonCore.h"
#include "Factory.h"
#include "Json.h"

#include "Special.cpp"
#include "Trivial.cpp"
#include "JsonCore.cpp"
#include "Factory.cpp"
#include "Json.cpp"
#include "hub.cpp"