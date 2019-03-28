#pragma once

#include "hub.h"

namespace json {
    class Factory {
    JSON_ABSTRACT(Factory)
    };
    JSON_DESTRUCTOR_DEFAULT_IMPL(Factory)

    template<typename JT>
    class JCoreFactory : public Factory {
    JSON_SINGLETON(JCoreFactory)
    private:
        using _StrIter= typename JT::String::const_iterator;
        using _CS= CharSpecial<typename JT::Char>;
        using _String= typename JT::String;
        using _JsonCore= JsonCore<JT>;
        using _JCNullFactory= JCNullFactory<JT>;
        using _JCBooleanFactory= JCBooleanFactory<JT>;
        using _JCNumberFactory= JCNumberFactory<JT>;
        using _JCStringFactory= JCStringFactory<JT>;
        using _JCArrayFactory= JCArrayFactory<JT>;
        using _JCObjectFactory= JCObjectFactory<JT>;
    protected:
        void passThrough(_StrIter &, const _StrIter &) const;

        void passSpace(_StrIter &, const _StrIter &) const;

        void passLineComment(_StrIter &, const _StrIter &) const;

        void passBlockComment(_StrIter &, const _StrIter &) const;

        bool isString(_StrIter &, const _StrIter &, _String &) const;

    public:
        virtual _JsonCore *byParsing(_StrIter &, const _StrIter &) const;
    };

    JSON_SINGLETON_IMPL_TEMPLATE(JCoreFactory, <typename JT>, <JT>)

    JSON_CD_DEFAULT_IMPL_TEMPLATE(JCoreFactory, <typename JT>, <JT>)

    template<typename JT>
    class JCNullFactory : public JCoreFactory<JT> {
    JSON_SINGLETON(JCNullFactory)
    private:
        using _CS= CharSpecial<typename JT::Char>;
        using _StrIter= typename JT::String::const_iterator;
        using _JsonCore= JsonCore<JT>;
        using _JsonValue= JsonValue<JT>;
    public:
        _JsonCore *byParsing(_StrIter &, const _StrIter &) const;

        _JsonCore *byEntity() const;
    };

    JSON_SINGLETON_IMPL_TEMPLATE(JCNullFactory, <typename JT>, <JT>)

    JSON_CD_DEFAULT_IMPL_TEMPLATE(JCNullFactory, <typename JT>, <JT>)

    template<typename JT>
    class JCBooleanFactory : public JCoreFactory<JT> {
    JSON_SINGLETON(JCBooleanFactory)
    private:
        using _CS= CharSpecial<typename JT::Char>;
        using _StrIter= typename JT::String::const_iterator;
        using _JsonCore= JsonCore<JT>;
        using _JsonValue= JsonValue<JT>;
    public:
        _JsonCore *byParsing(_StrIter &, const _StrIter &) const;

        template<typename T>
        _JsonCore *byEntity(T &&) const;
    };

    JSON_SINGLETON_IMPL_TEMPLATE(JCBooleanFactory, <typename JT>, <JT>)

    JSON_CD_DEFAULT_IMPL_TEMPLATE(JCBooleanFactory, <typename JT>, <JT>)

    template<typename JT>
    class JCNumberFactory : public JCoreFactory<JT> {
    JSON_SINGLETON(JCNumberFactory)
    private:
        using _Char= typename JT::Char;
        using _Number= typename JT::Number;
        using _CS= CharSpecial<_Char>;
        using _CNS=CharNumberSpecial<_Char, _Number>;
        using _StrIter= typename JT::String::const_iterator;
        using _JsonCore= JsonCore<JT>;
        using _JsonValue= JsonValue<JT>;

    public:
        _JsonCore *byParsing(_StrIter &, const _StrIter &) const;

        template<typename T>
        _JsonCore *byEntity(T &&) const;
    };

    JSON_SINGLETON_IMPL_TEMPLATE(JCNumberFactory, <typename JT>, <JT>)

    JSON_CD_DEFAULT_IMPL_TEMPLATE(JCNumberFactory, <typename JT>, <JT>)

    template<typename JT>
    class JCStringFactory : public JCoreFactory<JT> {
    JSON_SINGLETON(JCStringFactory)
    private:
        using _CS= CharSpecial<typename JT::Char>;
        using _StrIter= typename JT::String::const_iterator;
        using _JsonCore= JsonCore<JT>;
        using _JsonValue= JsonValue<JT>;
        using _String= typename JT::String;

        using JCoreFactory<JT>::isString;
    public:
        _JsonCore *byParsing(_StrIter &, const _StrIter &) const;

        template<typename T>
        _JsonCore *byEntity(T &&) const;
    };

    JSON_SINGLETON_IMPL_TEMPLATE(JCStringFactory, <typename JT>, <JT>)

    JSON_CD_DEFAULT_IMPL_TEMPLATE(JCStringFactory, <typename JT>, <JT>)

    template<typename JT>
    class JCArrayFactory : public JCoreFactory<JT> {
    JSON_SINGLETON(JCArrayFactory)
    private:
        using _Base=JCoreFactory<JT>;
        using _CS= CharSpecial<typename JT::Char>;
        using _AS= ArraySpecial<typename JT::Array, JT>;
        using _StrIter= typename JT::String::const_iterator;
        using _JsonCore= JsonCore<JT>;
        using _JsonValue= JsonValue<JT>;
        using _Array= typename JT::Array;

        using _Base::passThrough;
    public:
        _JsonCore *byParsing(_StrIter &, const _StrIter &) const;

        template<typename T>
        _JsonCore *byEntity(T &&) const;
    };

    JSON_SINGLETON_IMPL_TEMPLATE(JCArrayFactory, <typename JT>, <JT>)

    JSON_CD_DEFAULT_IMPL_TEMPLATE(JCArrayFactory, <typename JT>, <JT>)

    template<typename JT>
    class JCObjectFactory : public JCoreFactory<JT> {
    JSON_SINGLETON(JCObjectFactory)
    private:
        using _Base=JCoreFactory<JT>;
        using _CS= CharSpecial<typename JT::Char>;
        using _StrIter= typename JT::String::const_iterator;
        using _JsonCore= JsonCore<JT>;
        using _JsonValue= JsonValue<JT>;
        using _Object= typename JT::Object;
        using _String= typename JT::String;

        using _Base::passThrough;
        using _Base::isString;
    public:
        _JsonCore *byParsing(_StrIter &, const _StrIter &) const;

        template<typename T>
        _JsonCore *byEntity(T &&) const;
    };

    JSON_SINGLETON_IMPL_TEMPLATE(JCObjectFactory, <typename JT>, <JT>)

    JSON_CD_DEFAULT_IMPL_TEMPLATE(JCObjectFactory, <typename JT>, <JT>)
}



