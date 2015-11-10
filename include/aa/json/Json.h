//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "public.h"

namespace aa {
    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    class json : public _json::Private {
        friend class Private;

        friend bool operator<
                <NT, CT, AC, OC>(const json<NT, CT, AC, OC> &, const json<NT, CT, AC, OC> &);

        friend bool operator>
                <NT, CT, AC, OC>(const json<NT, CT, AC, OC> &, const json<NT, CT, AC, OC> &);

        friend bool operator==
                <NT, CT, AC, OC>(const json<NT, CT, AC, OC> &, const json<NT, CT, AC, OC> &);

    public:
        using number_type= NT;
        using char_type= CT;
        using string_type= typename CharSpecial<CT>::String;
        using array_type= AC<json>;
        using object_type= OC<string_type, json>;

        friend string_type aa::stringify<NT, CT, AC, OC>(const json &, const short &, const short &);

    private:
        using JsonCore= JsonCore<json>;
        using JCoreFactory= JCoreFactory<json>;
        using JCNullFactory= JCNullFactory<json>;
        using JCBooleanFactory= JCBooleanFactory<json>;
        using JCNumberFactory= JCNumberFactory<json>;
        using JCStringFactory= JCStringFactory<json>;
        using JCArrayFactory= JCArrayFactory<json>;
        using JCObjectFactory= JCObjectFactory<json>;

    private:
        static std::shared_ptr<bool> _pDefaultBoolean;
        static std::shared_ptr<number_type> _pDefaultNumber;
        static std::shared_ptr<string_type> _pDefaultString;
        static std::shared_ptr<array_type> _pDefaultArray;
        static std::shared_ptr<object_type> _pDefaultObject;

    public:
        static json parse(const string_type &);

    private:
        std::shared_ptr<JsonCore> _pCore;

    public:
        bool is_null() const;

        bool is_boolean() const;

        bool is_number() const;

        bool is_string() const;

        bool is_array() const;

        bool is_object() const;

        bool &b() const;

        number_type &n() const;

        string_type &s() const;

        array_type &a() const;

        object_type &o() const;

    public:
        json();

        json(json &&);

        json(const json &);

        json &operator=(json &&);

        json &operator=(const json &);

    public:
        template<typename T>
        json(T &&);

        template<typename T>
        json &operator=(T &&);

        void swap(json &);

        ~json();

        //CharSpecial: deal with situation that type 'number_type' is 'int'.
        json(int &&);

        json(const int &);

        json &operator=(int &&);

        json &operator=(const int &);
        ///

    private:
        void _move(json &&);

        void _copy(const json &);

        template<typename T>
        void _auto(T &&, bool *const &p = NULL);

        template<typename T>
        void _auto(T &&, number_type *const &p = NULL);

        template<typename T>
        void _auto(T &&, string_type *const &p = NULL);

        template<typename T>
        void _auto(T &&, const char_type **const &p = NULL);

        template<typename T>
        void _auto(T &&, array_type *const &p = NULL);

        template<typename T>
        void _auto(T &&, object_type *const &p = NULL);

        void _auto(json &&, json *const &p = NULL);

        void _auto(const json &, json *const &p = NULL);

        json(JsonCore *);
    };
}
