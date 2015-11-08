//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "public.h"

namespace klib {
    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    class Json : public json::Private {
        friend class Private;

    private:
        typedef typename Special<CT>::_ CharSpecial;
    public:
        typedef NT Number;
        typedef CT Char;
        typedef typename CharSpecial::String String;
    private:
        typedef String Key;
    public:
        typedef AC<Json> Array;
        typedef OC<const Key, Json> Object;
        typedef std::pair<const Key, Json> KeyValue;

        friend String klib::stringify<NT, CT, AC, OC>(const Json<NT, CT, AC, OC> &, const short &, const short &);

    private:
        typedef JsonCore <Json> JsonCore;
        typedef JCoreFactory <Json> JCoreFactory;
        typedef JCNullFactory <Json> JCNullFactory;
        typedef JCBooleanFactory <Json> JCBooleanFactory;
        typedef JCNumberFactory <Json> JCNumberFactory;
        typedef JCStringFactory <Json> JCStringFactory;
        typedef JCArrayFactory <Json> JCArrayFactory;
        typedef JCObjectFactory <Json> JCObjectFactory;

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
        bool isNull() const;

        bool isBoolean() const;

        bool isNumber() const;

        bool isString() const;

        bool isArray() const;

        bool isObject() const;

        bool &boolean() const;

        Number &number() const;

        String &string() const;

        Array &array() const;

        Object &object() const;

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

        //Special: deal with situation that type 'Number' is 'int'.
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

        Json(JsonCore *);
    };
}
