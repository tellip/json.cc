//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace aa {
    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    class Json : public _Json {
        friend class _Json;

        friend bool operator<
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

        friend bool operator>
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

        friend bool operator==
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

        friend typename CharSpecial<CT>::String stringify<NT, CT, AC, OC>(const Json &, const short &, const short &);

    public:
        using Number= NT;
        using Char= CT;
        using String= typename CharSpecial<CT>::String;
        using Array= AC<Json>;
        using Object= OC<String, Json>;

        using number_type=Number;
        using char_type=Char;
        using string_type=String;
        using array_type=Array;
        using object_type=Object;

    private:
        using JsonCore= JsonCore<Json>;
        using JCoreFactory= JCoreFactory<Json>;
        using JCNullFactory= JCNullFactory<Json>;
        using JCBooleanFactory= JCBooleanFactory<Json>;
        using JCNumberFactory= JCNumberFactory<Json>;
        using JCStringFactory= JCStringFactory<Json>;
        using JCArrayFactory= JCArrayFactory<Json>;
        using JCObjectFactory= JCObjectFactory<Json>;

    private:
        static std::shared_ptr<bool> _pDefaultBoolean;
        static std::shared_ptr<Number> _pDefaultNumber;
        static std::shared_ptr<String> _pDefaultString;
        static std::shared_ptr<Array> _pDefaultArray;
        static std::shared_ptr<Object> _pDefaultObject;

    public:
        static Json parse(const String &);

    private:
        std::shared_ptr<JsonCore> _pCore;

    public:
        //checker
        bool isNull() const;

        bool isBoolean() const;

        bool isNumber() const;

        bool isString() const;

        bool isArray() const;

        bool isObject() const;

        bool is_null() const;

        bool is_boolean() const;

        bool is_number() const;

        bool is_string() const;

        bool is_array() const;

        bool is_object() const;

        //entity referer
        bool &b() const;

        Number &n() const;

        String &s() const;

        Array &a() const;

        Object &o() const;

    public:
        Json();

        Json(Json &&);

        Json(const Json &);

        Json &operator=(Json &&);

        Json &operator=(const Json &);

    public:
        template<typename T>
        Json(T &&);

        template<typename T>
        Json &operator=(T &&);

        void swap(Json &);

        ~Json();

        //CharSpecial: deal with situation that type 'Number' is 'int'.
        Json(int &&);

        Json(const int &);

        Json &operator=(int &&);

        Json &operator=(const int &);
        ///

    private:
        void _move(Json &&);

        void _copy(const Json &);

        template<typename T>
        void _auto(T &&, bool *const &p = NULL);

        template<typename T>
        void _auto(T &&, Number *const &p = NULL);

        template<typename T>
        void _auto(T &&, String *const &p = NULL);

        template<typename T>
        void _auto(T &&, const Char **const &p = NULL);

        template<typename T>
        void _auto(T &&, Array *const &p = NULL);

        template<typename T>
        void _auto(T &&, Object *const &p = NULL);

        void _auto(Json &&, Json *const &p = NULL);

        void _auto(const Json &, Json *const &p = NULL);

    private:
        Json(JsonCore *&&);
    };
}
