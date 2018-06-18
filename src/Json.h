//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace jsoncpp {
    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    class Json {
        friend class jsoncpp::JCArrayFactory<Json>;

        friend class jsoncpp::JCObjectFactory<Json>;

        friend bool operator<
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

        friend bool operator>
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

        friend bool operator==
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

    public:
        using Number= NT;
        using Char= CT;
        using String= typename jsoncpp::CharSpecial<CT>::String;
        using Array= AC<Json>;
        using Object= OC<String, Json>;

        using boolean=bool;
        using number=Number;
        using string=String;
        using array=Array;
        using object=Object;

    private:
        using _JsonCore= jsoncpp::JsonCore<Json>;
        using _JCoreFactory= jsoncpp::JCoreFactory<Json>;
        using _JCNullFactory= jsoncpp::JCNullFactory<Json>;
        using _JCBooleanFactory= jsoncpp::JCBooleanFactory<Json>;
        using _JCNumberFactory= jsoncpp::JCNumberFactory<Json>;
        using _JCStringFactory= jsoncpp::JCStringFactory<Json>;
        using _JCArrayFactory= jsoncpp::JCArrayFactory<Json>;
        using _JCObjectFactory= jsoncpp::JCObjectFactory<Json>;

    private:
        static std::shared_ptr<bool> _pDefaultBoolean;
        static std::shared_ptr<Number> _pDefaultNumber;
        static std::shared_ptr<String> _pDefaultString;
        static std::shared_ptr<Array> _pDefaultArray;
        static std::shared_ptr<Object> _pDefaultObject;

    public:
        static Json parse(const String &);

        static String stringify(const Json &, const short &indent = -1, const short &depth = 0);

    private:
        std::shared_ptr<_JsonCore> _pCore;

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
        Json(_JsonCore *&&);
    };
}
