//
// Created by karthusluo on 2015/7/4.
//

#pragma once

#include "common.h"

#define CONSTRUCTOR_DEFAULT_IMPL(C)\
    C::C(){}
#define DESTRUCTOR_DEFAULT_IMPL(C)\
    C::~C(){}
#define CD_DEFAULT_IMPL(C)\
    C::C(){}\
    C::~C(){}

#define CONSTRUCTOR_DEFAULT_IMPL_SCOPE(C, SCOPE)\
    SCOPE::C::C(){}
#define DESTRUCTOR_DEFAULT_IMPL_SCOPE(C, SCOPE)\
    SCOPE::C::~C(){}
#define CD_DEFAULT_IMPL_SCOPE(C, SCOPE)\
    SCOPE::C::C(){}\
    SCOPE::C::~C(){}

#define CONSTRUCTOR_DEFAULT_IMPL_TEMPLATE(C, TMPDEF, TMPSPE)\
    template TMPDEF\
    C TMPSPE::C(){}
#define DESTRUCTOR_DEFAULT_IMPL_TEMPLATE(C, TMPDEF, TMPSPE)\
    template TMPDEF\
    C TMPSPE::~C(){}
#define CD_DEFAULT_IMPL_TEMPLATE(C, TMPDEF, TMPSPE)\
    template TMPDEF\
    C TMPSPE::C(){}\
    template TMPDEF\
    C TMPSPE::~C(){}

#define CONSTRUCTOR_DEFAULT_IMPL_SCOPE_TEMPLATE(C, SCOPE, TMPDEF, TMPSPE)\
    template TMPDEF\
    SCOPE::C TMPSPE::C(){}
#define DESTRUCTOR_DEFAULT_IMPL_SCOPE_TEMPLATE(C, SCOPE, TMPDEF, TMPSPE)\
    template TMPDEF\
    SCOPE::C TMPSPE::~C(){}
#define CD_DEFAULT_IMPL_SCOPE_TEMPLATE(C, SCOPE, TMPDEF, TMPSPE)\
    template TMPDEF\
    SCOPE::C TMPSPE::C(){}\
    template TMPDEF\
    SCOPE::C TMPSPE::~C(){}

#define STATIC(C) \
    private:\
        virtual ~C()=0;

#define ABSTRACT(CLASS) \
    public:\
        virtual ~CLASS()=0;\
    private:

#define SINGLETON(C)\
    private:\
        static std::shared_ptr<C> _pi;\
    public:\
        static C *pi();\
    protected:\
        C();\
        virtual ~C();\
    protected:\
        static void destruct(C *const &);\
    private:
#define SINGLETON_IMPL(C)\
    std::shared_ptr<C> C::_pi;\
    C *C::pi(){\
        if(!C::_pi) C::_pi.reset(new C,C::destruct);\
        return C::_pi.get();\
    }\
    void C::destruct(C *const &pc){\
        delete pc;\
    }
#define SINGLETON_IMPL_SCOPE(C, SCOPE)\
    std::shared_ptr<SCOPE::C> SCOPE::C::_pi;\
    SCOPE::C *SCOPE::C::pi(){\
        if(!C::_pi) C::_pi.reset(new C,C::destruct);\
        return C::_pi.get();\
    }\
    void SCOPE::C::destruct(C *const &pc){\
        delete pc;\
    }
#define SINGLETON_IMPL_TEMPLATE(C, TMPDEF, TMPSPE)\
    template TMPDEF\
    std::shared_ptr<C TMPSPE> C TMPSPE::_pi;\
    template TMPDEF\
    C TMPSPE *C TMPSPE::pi(){\
        if(!C::_pi) C::_pi.reset(new C,C::destruct);\
        return C::_pi.get();\
    }\
    template TMPDEF\
    void C TMPSPE::destruct(C *const &pc){\
        delete pc;\
    }
#define SINGLETON_IMPL_SCOPE_TEMPLATE(C, SCOPE, TMPDEF, TMPSPE)\
    template TMPDEF\
    std::shared_ptr<SCOPE::C TMPSPE> SCOPE::C TMPSPE::_pi;\
    template TMPDEF\
    SCOPE::C TMPSPE *SCOPE::C TMPSPE::pi(){\
        if(!C::_pi) C::_pi.reset(new C,C::destruct);\
        return C::_pi.get();\
    }\
    template TMPDEF\
    void SCOPE::C TMPSPE::destruct(C *const &pc){\
        delete pc;\
    }

