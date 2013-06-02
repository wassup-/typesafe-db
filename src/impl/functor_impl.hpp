#ifndef FUNCTOR_IMPL_HPP
#define FUNCTOR_IMPL_HPP

#include "../call_with.hpp"       // for fp::call_function

#include <tuple>                        // for std::tuple

namespace fp {
    namespace impl {

        struct func_impl {

            virtual ~func_impl() {
            }

            virtual void run() = 0;

            virtual func_impl * clone() const = 0;
        };

        template<typename Fn> struct functor : func_impl {
        protected:
            Fn m_fn;
        public:

            functor(Fn fn) : m_fn(fn) {
            }

            void run() {
                (*m_fn)();
            }

            functor * clone() const {
                return new functor(*this);
            }
        };

        template<typename Fn, typename... Arg> struct functor_with_args : func_impl {
        protected:
            Fn m_fn;
            std::tuple < Arg...> m_arg;
        public:

            functor_with_args(Fn fn, Arg... arg) : m_fn(fn), m_arg(arg...) {
            }

            void run() {
                call_function(m_fn, m_arg);
            }

            functor_with_args * clone() const {
                return new functor_with_args(*this);
            }
        };

        template<typename C> struct member_functor : func_impl {
        protected:
            void(C::*m_fn)();
            C * m_obj;
        public:

            member_functor(void(C::*fn)(), C * obj) : m_fn(fn), m_obj(obj) {
            }

            void run() {
                (m_obj->*m_fn)();
            }

            member_functor * clone() const {
                return new member_functor(*this);
            }
        };

        template<typename C, typename... Arg> struct member_functor_with_args : func_impl {
        protected:
            void(C::*m_fn)(Arg...);
            C * m_obj;
            std::tuple < Arg...> m_arg;
        public:

            member_functor_with_args(void(C::*fn)(Arg...), C * obj, Arg... arg) : m_fn(fn), m_obj(obj), m_arg(arg...) {
            }

            void run() {
                call_function(m_fn, m_obj, m_arg);
            }

            member_functor_with_args * clone() const {
                return new member_functor_with_args(*this);
            }
        };
    }
}

#endif