/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _APPLY_TUPLE_HPP
#define _APPLY_TUPLE_HPP

#include "result_of.hpp"
#include "impl/apply_tuple_impl.hpp"

#include <cstddef>      // for int
#include <utility>      // for std::forward
#include <tuple>        // for std::tuple, std::tuple_size

namespace fp {

    template<int N> struct apply_tuple {

        struct constructor {

            template<typename TType, typename... TTuple, typename... TArg>
            static TType apply(std::tuple < TTuple...> const & t, TArg && ... arg) {
                return impl::apply_tuple_impl < 0, N>::constructor::template apply<TType > (t, std::forward<TArg > (arg)...);
            }
        };

        struct function {

            template<typename Fn, typename... TTuple, typename... TArg>
            static typename result_of<Fn>::type apply(Fn fn, std::tuple < TTuple...> const & t, TArg && ... arg) {
                return impl::apply_tuple_impl < 0, N>::function::apply(fn, t, std::forward<TArg > (arg)...);
            }
        };
    };

    template<typename> struct fn_wrapper;

    template<typename TRet, typename... TArg> struct fn_wrapper<TRet(*)(TArg...)> {
    public:
        typedef TRet type;
    protected:
        TRet(*m_fn)(TArg...);
    public:

        fn_wrapper(TRet(*fn)(TArg...)) : m_fn(fn) {
        }

        template<typename... Arg >
        TRet operator()(Arg && ... arg) const {
            return (*m_fn)(std::forward<Arg > (arg)...);
        }
    };

    template<typename TClass, typename TRet, typename... TArg> struct fn_wrapper<TRet(TClass::*)(TArg...)> {
    public:
        typedef TRet type;
    protected:
        TClass * m_obj;
        TRet(TClass::*m_fn)(TArg...);
    public:

        fn_wrapper(TClass & obj, TRet(TClass::*fn)(TArg...)) : m_obj(&obj), m_fn(fn) {
        }

        template<typename... Arg >
        TRet operator()(Arg && ... arg) const {
            return (m_obj->*m_fn)(std::forward<Arg > (arg)...);
        }
    };

    template<typename TClass, typename TRet, typename... TArg> struct fn_wrapper<TRet(TClass::*)(TArg...) const> {
    public:
        typedef TRet type;
    protected:
        TClass const * m_obj;
        TRet(TClass::*m_fn)(TArg...) const;
    public:

        fn_wrapper(TClass const & obj, TRet(TClass::*fn)(TArg...) const) : m_obj(&obj), m_fn(fn) {
        }

        template<typename... Arg >
        TRet operator()(Arg... arg) const {
            return (m_obj->*m_fn)(std::forward<Arg > (arg)...);
        }
    };
    
    template<typename C, typename Ret, typename... Arg> fn_wrapper<Ret(C::*)(Arg...)> wrap_fn(C & obj, Ret(C::*fn)(Arg...)) {
        return fn_wrapper<Ret(C::*)(Arg...)>(obj, fn);
    }
    
    template<typename Fn> fn_wrapper<Fn> wrap_fn(Fn fn) {
        return fn_wrapper<Fn>(fn);
    }

    template<typename Fn, typename... TTuple, typename... TArg>
    inline auto call_function(Fn fn, std::tuple<TTuple...> const & tup, TArg && ... arg) -> typename result_of<Fn>::type {
        return apply_tuple < std::tuple_size < std::tuple < TTuple...> >::value>::function::apply(fn, tup, std::forward<TArg > (arg)...);
    }

    template<typename C, typename... TTuple, typename... TArg>
    inline C call_constructor(std::tuple<TTuple...> const & tup, TArg && ... arg) {
        return apply_tuple < std::tuple_size < std::tuple < TTuple...> >::value>::constructor::template apply<C > (tup, std::forward<TArg > (arg)...);
    }
}

#endif