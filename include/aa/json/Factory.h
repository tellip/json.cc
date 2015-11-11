//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "hub.h"

namespace aa {
    class _Json::Factory : public _Json {
    ABSTRACT(Factory)
    };
    DESTRUCTOR_DEFAULT_IMPL_SCOPE(Factory, _Json)

    template<typename JT>
    class _Json::JCoreFactory : public Factory {
    SINGLETON(JCoreFactory)
    private:
        using StrIter= typename JT::String::const_iterator;
        using CS= CharSpecial<typename JT::Char>;
        using String= typename JT::String;
        using JsonCore= JsonCore<JT>;
        using JsonValue= JsonValue<JT>;
        using Trivial= Trivial<JT>;
        using JCNullFactory= JCNullFactory<JT>;
        using JCBooleanFactory= JCBooleanFactory<JT>;
        using JCNumberFactory= JCNumberFactory<JT>;
        using JCStringFactory= JCStringFactory<JT>;
        using JCArrayFactory= JCArrayFactory<JT>;
        using JCObjectFactory= JCObjectFactory<JT>;
    protected:
        void passThrough(StrIter &, const StrIter &) const;

        void passSpace(StrIter &, const StrIter &) const;

        void passLineComment(StrIter &, const StrIter &) const;

        void passBlockComment(StrIter &, const StrIter &) const;

        bool isString(StrIter &, const StrIter &, String &) const;

    public:
        virtual JsonCore *byParsing(StrIter &, const StrIter &) const;
    };

    SINGLETON_IMPL_SCOPE_TEMPLATE(JCoreFactory, _Json, <typename JT>, <JT>)

    CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCoreFactory, _Json, <typename JT>, <JT>)

    template<typename JT>
    class _Json::JCNullFactory : public JCoreFactory<JT> {
    SINGLETON(JCNullFactory)
    private:
        using CS= CharSpecial<typename JT::Char>;
        using StrIter= typename JT::String::const_iterator;
        using JsonCore= _Json::JsonCore<JT>;
        using JsonValue= _Json::JsonValue<JT>;
    public:
        JsonCore *byParsing(StrIter &, const StrIter &) const;

        JsonCore *byEntity() const;
    };

    SINGLETON_IMPL_SCOPE_TEMPLATE(JCNullFactory, _Json, <typename JT>, <JT>)

    CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCNullFactory, _Json, <typename JT>, <JT>)

    template<typename JT>
    class _Json::JCBooleanFactory : public JCoreFactory<JT> {
    SINGLETON(JCBooleanFactory)
    private:
        using CS= CharSpecial<typename JT::Char>;
        using StrIter= typename JT::String::const_iterator;
        using JsonCore= _Json::JsonCore<JT>;
        using JsonValue= _Json::JsonValue<JT>;
    public:
        JsonCore *byParsing(StrIter &, const StrIter &) const;

        template<typename T>
        JsonCore *byEntity(T &&) const;
    };

    SINGLETON_IMPL_SCOPE_TEMPLATE(JCBooleanFactory, _Json, <typename JT>, <JT>)

    CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCBooleanFactory, _Json, <typename JT>, <JT>)

    template<typename JT>
    class _Json::JCNumberFactory : public JCoreFactory<JT> {
    SINGLETON(JCNumberFactory)
    private:
        using Char= typename JT::Char;
        using CS= CharSpecial<Char>;
        using StrIter= typename JT::String::const_iterator;
        using JsonCore= _Json::JsonCore<JT>;
        using JsonValue= _Json::JsonValue<JT>;
        using Number= typename JT::Number;
    public:
        JsonCore *byParsing(StrIter &, const StrIter &) const;

        template<typename T>
        JsonCore *byEntity(T &&) const;
    };

    SINGLETON_IMPL_SCOPE_TEMPLATE(JCNumberFactory, _Json, <typename JT>, <JT>)

    CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCNumberFactory, _Json, <typename JT>, <JT>)

    template<typename JT>
    class _Json::JCStringFactory : public JCoreFactory<JT> {
    SINGLETON(JCStringFactory)
    private:
        using JCoreFactory= _Json::JCoreFactory<JT>;
        using CS= CharSpecial<typename JT::Char>;
        using StrIter= typename JT::String::const_iterator;
        using JsonCore= _Json::JsonCore<JT>;
        using JsonValue= _Json::JsonValue<JT>;
        using String= typename JT::String;
    public:
        JsonCore *byParsing(StrIter &, const StrIter &) const;

        template<typename T>
        JsonCore *byEntity(T &&) const;
    };

    SINGLETON_IMPL_SCOPE_TEMPLATE(JCStringFactory, _Json, <typename JT>, <JT>)

    CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCStringFactory, _Json, <typename JT>, <JT>)

    template<typename JT>
    class _Json::JCArrayFactory : public JCoreFactory<JT> {
    SINGLETON(JCArrayFactory)
    private:
        using JCoreFactory= _Json::JCoreFactory<JT>;
        using CS= CharSpecial<typename JT::Char>;
        using AS= ArraySpecial<typename JT::Array, JT>;
        using StrIter= typename JT::String::const_iterator;
        using JsonCore= _Json::JsonCore<JT>;
        using JsonValue= _Json::JsonValue<JT>;
        using Array= typename JT::Array;
    public:
        JsonCore *byParsing(StrIter &, const StrIter &) const;

        template<typename T>
        JsonCore *byEntity(T &&) const;
    };

    SINGLETON_IMPL_SCOPE_TEMPLATE(JCArrayFactory, _Json, <typename JT>, <JT>)

    CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCArrayFactory, _Json, <typename JT>, <JT>)

    template<typename JT>
    class _Json::JCObjectFactory : public JCoreFactory<JT> {
    SINGLETON(JCObjectFactory)
    private:
        using JCoreFactory= _Json::JCoreFactory<JT>;
        using CS= CharSpecial<typename JT::Char>;
        using StrIter= typename JT::String::const_iterator;
        using JsonCore= _Json::JsonCore<JT>;
        using JsonValue= _Json::JsonValue<JT>;
        using Object= typename JT::Object;
        using String= typename JT::String;
    public:
        JsonCore *byParsing(StrIter &, const StrIter &) const;

        template<typename T>
        JsonCore *byEntity(T &&) const;
    };

    SINGLETON_IMPL_SCOPE_TEMPLATE(JCObjectFactory, _Json, <typename JT>, <JT>)

    CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCObjectFactory, _Json, <typename JT>, <JT>)
}



