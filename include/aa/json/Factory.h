//
// Created by kalo on 2015/11/1.
//

#pragma once

#include "Private.h"

namespace aa {
    namespace _json {
        class Private::Factory : public Private {
        ABSTRACT(Factory)
        };
        DESTRUCTOR_DEFAULT_IMPL_SCOPE(Factory, Private)

        template<typename JT>
        class Private::JCoreFactory : public Factory {
        SINGLETON(JCoreFactory)
        private:
            typedef typename JT::string_type::const_iterator StrIter;
            typedef typename Special<typename JT::char_type>::_ CS;
            typedef typename JT::string_type String;
            typedef JsonCore <JT> JsonCore;
            typedef JsonValue <JT> JsonValue;
            typedef Trivial<JT> Trivial;
            typedef JCNullFactory <JT> JCNullFactory;
            typedef JCBooleanFactory <JT> JCBooleanFactory;
            typedef JCNumberFactory <JT> JCNumberFactory;
            typedef JCStringFactory <JT> JCStringFactory;
            typedef JCArrayFactory <JT> JCArrayFactory;
            typedef JCObjectFactory <JT> JCObjectFactory;
        protected:
            void passThrough(StrIter &, const StrIter &) const;

            void passSpace(StrIter &, const StrIter &) const;

            void passLineComment(StrIter &, const StrIter &) const;

            void passBlockComment(StrIter &, const StrIter &) const;

            bool is_string(StrIter &, const StrIter &, String &) const;

        public:
            virtual JsonCore *byParsing(StrIter &, const StrIter &) const;
        };

        SINGLETON_IMPL_SCOPE_TEMPLATE(JCoreFactory, Private, <typename JT>, <JT>)

        CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCoreFactory, Private, <typename JT>, <JT>)

        template<typename JT>
        class Private::JCNullFactory : public JCoreFactory<JT> {
        SINGLETON(JCNullFactory)
        private:
            typedef typename Special<typename JT::char_type>::_ CS;
            typedef typename JT::string_type::const_iterator StrIter;
            typedef Private::JsonCore<JT> JsonCore;
            typedef Private::JsonValue<JT> JsonValue;
        public:
            JsonCore *byParsing(StrIter &, const StrIter &) const;

            JsonCore *byEntity() const;
        };

        SINGLETON_IMPL_SCOPE_TEMPLATE(JCNullFactory, Private, <typename JT>, <JT>)

        CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCNullFactory, Private, <typename JT>, <JT>)

        template<typename JT>
        class Private::JCBooleanFactory : public JCoreFactory<JT> {
        SINGLETON(JCBooleanFactory)
        private:
            typedef typename Special<typename JT::char_type>::_ CS;
            typedef typename JT::string_type::const_iterator StrIter;
            typedef Private::JsonCore<JT> JsonCore;
            typedef Private::JsonValue<JT> JsonValue;
        public:
            JsonCore *byParsing(StrIter &, const StrIter &) const;

            template<typename T>
            JsonCore *byEntity(T &&) const;
        };

        SINGLETON_IMPL_SCOPE_TEMPLATE(JCBooleanFactory, Private, <typename JT>, <JT>)

        CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCBooleanFactory, Private, <typename JT>, <JT>)

        template<typename JT>
        class Private::JCNumberFactory : public JCoreFactory<JT> {
        SINGLETON(JCNumberFactory)
        private:
            typedef typename JT::char_type Char;
            typedef typename Special<Char>::_ CS;
            typedef typename JT::string_type::const_iterator StrIter;
            typedef Private::JsonCore<JT> JsonCore;
            typedef Private::JsonValue<JT> JsonValue;
            typedef typename JT::number_type Number;
        public:
            JsonCore *byParsing(StrIter &, const StrIter &) const;

            template<typename T>
            JsonCore *byEntity(T &&) const;
        };

        SINGLETON_IMPL_SCOPE_TEMPLATE(JCNumberFactory, Private, <typename JT>, <JT>)

        CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCNumberFactory, Private, <typename JT>, <JT>)

        template<typename JT>
        class Private::JCStringFactory : public JCoreFactory<JT> {
        SINGLETON(JCStringFactory)
        private:
            typedef Private::JCoreFactory<JT> JCoreFactory;
            typedef typename Special<typename JT::char_type>::_ CS;
            typedef typename JT::string_type::const_iterator StrIter;
            typedef Private::JsonCore<JT> JsonCore;
            typedef Private::JsonValue<JT> JsonValue;
            typedef typename JT::string_type String;
        public:
            JsonCore *byParsing(StrIter &, const StrIter &) const;

            template<typename T>
            JsonCore *byEntity(T &&) const;
        };

        SINGLETON_IMPL_SCOPE_TEMPLATE(JCStringFactory, Private, <typename JT>, <JT>)

        CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCStringFactory, Private, <typename JT>, <JT>)

        template<typename JT>
        class Private::JCArrayFactory : public JCoreFactory<JT> {
        SINGLETON(JCArrayFactory)
        private:
            typedef Private::JCoreFactory<JT> JCoreFactory;
            typedef typename Special<typename JT::char_type>::_ CS;
            typedef typename JT::string_type::const_iterator StrIter;
            typedef Private::JsonCore<JT> JsonCore;
            typedef Private::JsonValue<JT> JsonValue;
            typedef typename JT::array_type Array;
        public:
            JsonCore *byParsing(StrIter &, const StrIter &) const;

            template<typename T>
            JsonCore *byEntity(T &&) const;
        };

        SINGLETON_IMPL_SCOPE_TEMPLATE(JCArrayFactory, Private, <typename JT>, <JT>)

        CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCArrayFactory, Private, <typename JT>, <JT>)

        template<typename JT>
        class Private::JCObjectFactory : public JCoreFactory<JT> {
        SINGLETON(JCObjectFactory)
        private:
            typedef Private::JCoreFactory<JT> JCoreFactory;
            typedef typename Special<typename JT::char_type>::_ CS;
            typedef typename JT::string_type::const_iterator StrIter;
            typedef Private::JsonCore<JT> JsonCore;
            typedef Private::JsonValue<JT> JsonValue;
            typedef typename JT::object_type Object;
            typedef typename JT::string_type String;
        public:
            JsonCore *byParsing(StrIter &, const StrIter &) const;

            template<typename T>
            JsonCore *byEntity(T &&) const;
        };

        SINGLETON_IMPL_SCOPE_TEMPLATE(JCObjectFactory, Private, <typename JT>, <JT>)

        CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCObjectFactory, Private, <typename JT>, <JT>)
    }
}


