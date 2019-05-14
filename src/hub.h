#pragma once

#include <functional>
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
#include <initializer_list>
#include <utility>
#include <memory>
#include <type_traits>
#include <cmath>

namespace json {
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

    template<
            typename=double,
            typename=char,
            template<typename...> class=std::list,
            template<typename, typename...> class=std::unordered_map
    >
    class Json;

//    template<
//            typename NT=double,
//            typename CT=char,
//            template<typename...> class AC=std::list,
//            template<typename, typename...> class OC=std::unordered_map
//    >
//    using json=Json<NT, CT, AC, OC>;
}

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
void swap(json::Json<NT, CT, AC, OC> &, json::Json<NT, CT, AC, OC> &);

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator<(const json::Json<NT, CT, AC, OC> &, const json::Json<NT, CT, AC, OC> &);

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator>(const json::Json<NT, CT, AC, OC> &, const json::Json<NT, CT, AC, OC> &);

template<
        typename NT,
        typename CT,
        template<typename...> class AC,
        template<typename, typename...> class OC
>
bool operator==(const json::Json<NT, CT, AC, OC> &, const json::Json<NT, CT, AC, OC> &);

#include "class.h"
#include "common.h"

#include "Special.h"
#include "Trivial.h"
#include "JsonValue.h"
#include "JsonCore.h"
#include "Factory.h"
#include "Json.h"