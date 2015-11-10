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
            using StrIter= typename JT::string_type::const_iterator;
            using CS= CharSpecial<typename JT::char_type>;
            using String= typename JT::string_type;
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
            using CS= CharSpecial<typename JT::char_type>;
            using StrIter= typename JT::string_type::const_iterator;
            using JsonCore= Private::JsonCore<JT>;
            using JsonValue= Private::JsonValue<JT>;
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
            using CS= CharSpecial<typename JT::char_type>;
            using StrIter= typename JT::string_type::const_iterator;
            using JsonCore= Private::JsonCore<JT>;
            using JsonValue= Private::JsonValue<JT>;
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
            using Char= typename JT::char_type;
            using CS= CharSpecial<Char>;
            using StrIter= typename JT::string_type::const_iterator;
            using JsonCore= Private::JsonCore<JT>;
            using JsonValue= Private::JsonValue<JT>;
            using Number= typename JT::number_type;
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
            using JCoreFactory= Private::JCoreFactory<JT>;
            using CS= CharSpecial<typename JT::char_type>;
            using StrIter= typename JT::string_type::const_iterator;
            using JsonCore= Private::JsonCore<JT>;
            using JsonValue= Private::JsonValue<JT>;
            using String= typename JT::string_type;
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
            using JCoreFactory= Private::JCoreFactory<JT>;
            using CS= CharSpecial<typename JT::char_type>;
            using AS= ArraySpecial<typename JT::array_type, JT>;
            using StrIter= typename JT::string_type::const_iterator;
            using JsonCore= Private::JsonCore<JT>;
            using JsonValue= Private::JsonValue<JT>;
            using Array= typename JT::array_type;
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
            using JCoreFactory= Private::JCoreFactory<JT>;
            using CS= CharSpecial<typename JT::char_type>;
            using StrIter= typename JT::string_type::const_iterator;
            using JsonCore= Private::JsonCore<JT>;
            using JsonValue= Private::JsonValue<JT>;
            using Object= typename JT::object_type;
            using String= typename JT::string_type;
        public:
            JsonCore *byParsing(StrIter &, const StrIter &) const;

            template<typename T>
            JsonCore *byEntity(T &&) const;
        };

        SINGLETON_IMPL_SCOPE_TEMPLATE(JCObjectFactory, Private, <typename JT>, <JT>)

        CD_DEFAULT_IMPL_SCOPE_TEMPLATE(JCObjectFactory, Private, <typename JT>, <JT>)
    }
}


