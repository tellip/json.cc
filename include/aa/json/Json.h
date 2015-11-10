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

    public:
        typedef NT number_type;
        typedef CT char_type;
        typedef typename Special<CT>::_::String string_type;
        typedef AC<json> array_type;
        typedef OC<string_type, json> object_type;

        friend string_type aa::stringify<NT, CT, AC, OC>(const json<NT, CT, AC, OC> &, const short &, const short &);

    private:
        typedef JsonCore <json> JsonCore;
        typedef JCoreFactory <json> JCoreFactory;
        typedef JCNullFactory <json> JCNullFactory;
        typedef JCBooleanFactory <json> JCBooleanFactory;
        typedef JCNumberFactory <json> JCNumberFactory;
        typedef JCStringFactory <json> JCStringFactory;
        typedef JCArrayFactory <json> JCArrayFactory;
        typedef JCObjectFactory <json> JCObjectFactory;

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

        bool &boolean() const;

        number_type &number() const;

        string_type &string() const;

        array_type &array() const;

        object_type &object() const;

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

        //Special: deal with situation that type 'number_type' is 'int'.
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
