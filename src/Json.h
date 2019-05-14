#pragma once

#include "hub.h"

namespace json {
    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    class Json {
        friend class json::JCArrayFactory<Json>;

        friend class json::JCObjectFactory<Json>;

        friend bool operator<
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

        friend bool operator>
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

        friend bool operator==
                <NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const Json<NT, CT, AC, OC> &);

    public:
        using Null=nullptr_t;
        using Boolean=bool;
        using Number= NT;
        using Char= CT;
        using String= typename json::CharSpecial<CT>::String;
        using Array= AC<Json>;
        using Object= OC<String, Json>;

        using null=Null;
        using boolean=Boolean;
        using number=Number;
        using string=String;
        using array=Array;
        using object=Object;

    private:
        using _JsonCore= json::JsonCore<Json>;
        using _JCoreFactory= json::JCoreFactory<Json>;
        using _JCNullFactory= json::JCNullFactory<Json>;
        using _JCBooleanFactory= json::JCBooleanFactory<Json>;
        using _JCNumberFactory= json::JCNumberFactory<Json>;
        using _JCStringFactory= json::JCStringFactory<Json>;
        using _JCArrayFactory= json::JCArrayFactory<Json>;
        using _JCObjectFactory= json::JCObjectFactory<Json>;

    private:
        static std::shared_ptr<nullptr_t> _pDefaultNull;
        static std::shared_ptr<bool> _pDefaultBoolean;
        static std::shared_ptr<Number> _pDefaultNumber;
        static std::shared_ptr<String> _pDefaultString;
        static std::shared_ptr<Array> _pDefaultArray;
        static std::shared_ptr<Object> _pDefaultObject;

    public:
        static Json parse(const String &);

        static String stringify(const Json &, const Json & = Null());

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
        nullptr_t &asNull() const;

        bool &asBoolean() const;

        Number &asNumber() const;

        String &asString() const;

        Array &asArray() const;

        Object &asObject() const;

        nullptr_t &as_null() const;

        bool &as_boolean() const;

        Number &as_number() const;

        String &as_string() const;

        Array &as_array() const;

        Object &as_object() const;

    public:
        Json();

        explicit Json(Json &&);

        explicit Json(const Json &);

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

        //initializer_list
        Json(std::initializer_list<Json> &&);

        Json(const std::initializer_list<Json> &);

    private:
        void _move(Json &&);

        void _copy(const Json &);

        template<typename T>
        void _auto(T &&, bool *const &p = nullptr);

        template<typename T>
        void _auto(T &&, Number *const &p = nullptr);

        template<typename T>
        void _auto(T &&, String *const &p = nullptr);

        template<typename T>
        void _auto(T &&, const Char **const &p = nullptr);

        template<typename T>
        void _auto(T &&, Array *const &p = nullptr);

        template<typename T>
        void _auto(T &&, Object *const &p = nullptr);

        void _auto(Json &&, Json *const &p = nullptr);

        void _auto(const Json &, Json *const &p = nullptr);

    private:
        Json(_JsonCore *&&);

    public:
        struct Indent {
            struct _Indent {
                virtual bool positive() const = 0;
            };

            struct _INegative : _Indent {
                inline bool positive() const final { return false; }
            };

            struct _IPositive : _Indent {
                const std::size_t value;

                explicit _IPositive(const std::size_t &value) : value(value) {}

                inline bool positive() const final { return true; }

                virtual bool complex() const = 0;
            };

            struct _IPNaive : _IPositive {
                explicit _IPNaive(const std::size_t &value) : _IPositive(value) {}

                bool complex() const final { return false; }
            };

            struct _IPComplex : _IPositive {
                explicit _IPComplex(const std::size_t &value) : _IPositive(value) {}

                bool complex() const final { return true; }

                enum IPCType {
                    Negative, Naive, Array, Object
                };

                virtual IPCType complexType() const = 0;
            };

            struct _IPCNegative : _IPComplex {
                _IPCNegative(const std::size_t &value) : _IPComplex(value) {}

                inline typename _IPComplex::IPCType complexType() const final { return _IPComplex::IPCType::Negative; }
            };

            struct _IPCNaive : _IPComplex {
                const std::size_t sub_value;

                _IPCNaive(const std::size_t &value, const std::size_t &sub_value) : _IPComplex(value), sub_value(sub_value) {}

                inline typename _IPComplex::IPCType complexType() const final { return _IPComplex::IPCType::Naive; }
            };

            struct _IPCArray : _IPComplex {
                const std::list<Indent> array;
                const Indent rest;

                _IPCArray(const std::size_t &value, std::list<Indent> array, Indent rest) :
                        _IPComplex(value),
                        array(std::move(array)),
                        rest(std::move(rest)) {}

                inline typename _IPComplex::IPCType complexType() const final { return _IPComplex::IPCType::Array; }
            };

            struct _IPCObject : _IPComplex {
                const std::unordered_map<String, Indent> object;
                const Indent rest;

                _IPCObject(const std::size_t &value, std::unordered_map<String, Indent> object, Indent rest) :
                        _IPComplex(value),
                        object(std::move(object)),
                        rest(std::move(rest)) {}

                inline typename _IPComplex::IPCType complexType() const final { return _IPComplex::IPCType::Object; }
            };

            const std::shared_ptr<_Indent> value;

            Indent(const nullptr_t &) : value(std::make_shared<_INegative>()) {}

            Indent(const std::size_t &value) : value(std::make_shared<_IPNaive>(value)) {}

            Indent(const std::size_t &value, const Null &) : value(std::make_shared<_IPCNegative>(value)) {}

            Indent(const std::size_t &value, const std::size_t &sub_value) : value(std::make_shared<_IPCNaive>(value, sub_value)) {}

            Indent(const std::size_t &value, std::list<Indent> array, Indent rest = nullptr) : value(std::make_shared<_IPCArray>(value, std::move(array), std::move(rest))) {}

            Indent(const std::size_t &value, std::unordered_map<String, Indent> object, Indent rest = nullptr) : value(std::make_shared<_IPCObject>(value, std::move(object), std::move(rest))) {}
        };
    };
}
