/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef FUNCTOR_IMPL_HPP
#define FUNCTOR_IMPL_HPP

#include "../call_with.hpp"       // for fp::call_function

#include <tuple>                        // for std::tuple

namespace fp { namespace impl {

    template<typename Fn>
    struct functor {
    protected:
        Fn m_fn;
    public:

        functor(Fn fn)
        : m_fn(fn)
        { }

        void run() const {
            (*m_fn)();
        }

        friend void run(const functor& fn) {
            fn.run();
        }
    };

    template<typename Fn, typename... Arg>
    struct functor_with_args {
    protected:
        Fn m_fn;
        std::tuple<Arg...> m_arg;
    public:

        functor_with_args(Fn fn, Arg... arg)
        : m_fn(fn), m_arg(arg...)
        { }

        void run() const {
            call_function(m_fn, m_arg);
        }

        friend void run(const functor_with_args& fn) {
            fn.run();
        }
    };

    template<typename C>
    struct member_functor {
    protected:
        void(C::*m_fn)();
        C* m_obj;
    public:

        member_functor(void(C::*fn)(), C* obj)
        : m_fn(fn), m_obj(obj)
        { }

        void run() const {
            (m_obj->*m_fn)();
        }

        friend void run(const member_functor& fn) {
            fn.run();
        }
    };

    template<typename C, typename... Arg>
    struct member_functor_with_args {
    protected:
        void(C::*m_fn)(Arg...);
        C* m_obj;
        std::tuple<Arg...> m_arg;
    public:

        member_functor_with_args(void(C::*fn)(Arg...), C* obj, Arg... arg)
        : m_fn(fn), m_obj(obj), m_arg(arg...)
        { }

        void run() const {
            call_function(m_fn, m_obj, m_arg);
        }

        friend void run(const member_functor_with_args& fn) {
            fn.run();
        }
    };
} }

#endif