//
// Created by kalo on 2015/11/1.
//

#include "json.h"

namespace aa {
    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    std::shared_ptr<bool> json<NT, CT, AC, OC>::_pDefaultBoolean;

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    std::shared_ptr<typename json<NT, CT, AC, OC>::number_type> json<NT, CT, AC, OC>::_pDefaultNumber;

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    std::shared_ptr<typename json<NT, CT, AC, OC>::string_type> json<NT, CT, AC, OC>::_pDefaultString;

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    std::shared_ptr<typename json<NT, CT, AC, OC>::array_type> json<NT, CT, AC, OC>::_pDefaultArray;

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    std::shared_ptr<typename json<NT, CT, AC, OC>::object_type> json<NT, CT, AC, OC>::_pDefaultObject;

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC> json<NT, CT, AC, OC>::parse(const string_type &s) {
        typename string_type::const_iterator iNow = s.begin();
        JsonCore *pjc = JCoreFactory::pi()->byParsing(iNow, s.end());
        if (!pjc) return json();
        if (iNow != s.end()) {
            JsonCore::destruct(pjc);
            return json();
        }
        return json(pjc);
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool json<NT, CT, AC, OC>::is_null() const {
        return _pCore->category == JC_NULL;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool json<NT, CT, AC, OC>::is_boolean() const {
        return _pCore->category == JC_BOOLEAN;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool json<NT, CT, AC, OC>::is_number() const {
        return _pCore->category == JC_NUMBER;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool json<NT, CT, AC, OC>::is_string() const {
        return _pCore->category == JC_STRING;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool json<NT, CT, AC, OC>::is_array() const {
        return _pCore->category == JC_ARRAY;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool json<NT, CT, AC, OC>::is_object() const {
        return _pCore->category == JC_OBJECT;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    bool &json<NT, CT, AC, OC>::boolean() const {
        if (_pCore->category == JC_BOOLEAN) return *_pCore->value.pBoolean;
        _pDefaultBoolean.reset(new bool);
        return *_pDefaultBoolean;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    typename json<NT, CT, AC, OC>::number_type &json<NT, CT, AC, OC>::number() const {
        if (_pCore->category == JC_NUMBER) return *_pCore->value.pNumber;
        _pDefaultNumber.reset(new number_type);
        return *_pDefaultNumber;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    typename json<NT, CT, AC, OC>::string_type &json<NT, CT, AC, OC>::string() const {
        if (_pCore->category == JC_STRING) return *_pCore->value.pString;
        _pDefaultString.reset(new string_type);
        return *_pDefaultString;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    typename json<NT, CT, AC, OC>::array_type &json<NT, CT, AC, OC>::array() const {
        if (_pCore->category == JC_ARRAY) return *_pCore->value.pArray;
        _pDefaultArray.reset(new array_type);
        return *_pDefaultArray;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    typename json<NT, CT, AC, OC>::object_type &json<NT, CT, AC, OC>::object() const {
        if (_pCore->category == JC_OBJECT) return *_pCore->value.pObject;
        _pDefaultObject.reset(new object_type);
        return *_pDefaultObject;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC>::json() : _pCore(
            JCNullFactory::pi()->byEntity(),
            JsonCore::destruct
    ) {
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC>::json(json &&j) {
        _move(std::move(j));
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC>::json(const json &j) {
        _copy(j);
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC> &json<NT, CT, AC, OC>::operator=(json &&j) {
        _move(std::move(j));
        return *this;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC> &json<NT, CT, AC, OC>::operator=(const json &j) {
        _copy(j);
        return *this;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    template<typename T>
    json<NT, CT, AC, OC>::json(T &&t) {
        _auto(std::forward<T>(t), (typename std::decay<T>::type *const &) NULL);
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    template<typename T>
    json<NT, CT, AC, OC> &json<NT, CT, AC, OC>::operator=(T &&t) {
        _auto(std::forward<T>(t), (typename std::decay<T>::type *const &) NULL);
        return *this;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    void json<NT, CT, AC, OC>::swap(json &j) {
        _pCore.swap(j._pCore);
    };

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC>::~json() {
        _pCore.reset();
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC>::json(int &&i) {
        _auto(std::move(i), (number_type *const &) NULL);
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC>::json(const int &i) {
        _auto(i, (number_type *const &) NULL);
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC> &json<NT, CT, AC, OC>::operator=(int &&i) {
        _auto(i, (number_type *const &) NULL);
        return *this;
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC> &json<NT, CT, AC, OC>::operator=(const int &i) {
        _auto(i, (number_type *const &) NULL);
        return *this;
    }


    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    void json<NT, CT, AC, OC>::_move(json &&j) {
        if (_pCore != j._pCore) {
            _pCore.reset(
                    JCNullFactory::pi()->byEntity(),
                    JsonCore::destruct
            );
            _pCore.swap(j._pCore);
//            std::cout << "move" << std::endl;
        } else {
//            std::cout << "self move" << std::endl;
        }
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    void json<NT, CT, AC, OC>::_copy(const json &j) {
        if (_pCore != j._pCore) {
            JsonCore *pjc;
            switch (j._pCore->category) {
                case JC_BOOLEAN:
                    pjc = JCBooleanFactory::pi()->byEntity(*j._pCore->value.pBoolean);
                    break;
                case JC_NUMBER:
                    pjc = JCNumberFactory::pi()->byEntity(*j._pCore->value.pNumber);
                    break;
                case JC_STRING:
                    pjc = JCStringFactory::pi()->byEntity(*j._pCore->value.pString);
                    break;
                case JC_ARRAY:
                    pjc = JCArrayFactory::pi()->byEntity(*j._pCore->value.pArray);
                    break;
                case JC_OBJECT:
                    pjc = JCObjectFactory::pi()->byEntity(*j._pCore->value.pObject);
                    break;
                default:
                    pjc = JCNullFactory::pi()->byEntity();
            }
            _pCore.reset(pjc, JsonCore::destruct);
//            std::cout << "copy" << std::endl;
        } else {
//            std::cout << "self copy" << std::endl;
        }
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    template<typename T>
    void json<NT, CT, AC, OC>::_auto(T &&t, bool *const &) {
        _pCore.reset(
                JCBooleanFactory::pi()->byEntity(std::forward<T>(t)),
                JsonCore::destruct
        );
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    template<typename T>
    void json<NT, CT, AC, OC>::_auto(T &&t, number_type *const &) {
        _pCore.reset(
                JCNumberFactory::pi()->byEntity(std::forward<T>(t)),
                JsonCore::destruct
        );
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    template<typename T>
    void json<NT, CT, AC, OC>::_auto(T &&t, string_type *const &) {
        _pCore.reset(
                JCStringFactory::pi()->byEntity(std::forward<T>(t)),
                JsonCore::destruct
        );
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    template<typename T>
    void json<NT, CT, AC, OC>::_auto(T &&t, const char_type **const &) {
        _pCore.reset(
                JCStringFactory::pi()->byEntity(string_type(std::forward<T>(t))),
                JsonCore::destruct
        );
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    template<typename T>
    void json<NT, CT, AC, OC>::_auto(T &&t, array_type *const &) {
        _pCore.reset(
                JCArrayFactory::pi()->byEntity(std::forward<T>(t)),
                JsonCore::destruct
        );
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    template<typename T>
    void json<NT, CT, AC, OC>::_auto(T &&t, object_type *const &) {
        _pCore.reset(
                JCObjectFactory::pi()->byEntity(std::forward<T>(t)),
                JsonCore::destruct
        );
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    void json<NT, CT, AC, OC>::_auto(json &&j, json *const &) {
        _move(std::move(j));
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    void json<NT, CT, AC, OC>::_auto(const json &j, json *const &) {
        _copy(j);
    }

    template<
            typename NT,
            typename CT,
            template<typename...> class AC,
            template<typename, typename...> class OC
    >
    json<NT, CT, AC, OC>::json(JsonCore *pjc) : _pCore(pjc, JsonCore::destruct) { }
}