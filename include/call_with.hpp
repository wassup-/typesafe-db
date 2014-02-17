/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef CALL_WITH_HPP_
#define CALL_WITH_HPP_

#include "ce_tuple.hpp"
#include "forward.hpp"
#include "type_traits.hpp"      // for fp::ResultOf, fp::Unqualified

#include <array>                // for std::array, std::get
#include <cstddef>              // for std::size_t
#include <tuple>                // for std::tuple, std::get
#include <utility>              // for fix::forward

namespace fp {
    namespace detail {

        struct tuplelike_tag { };
        struct arraylike_tag { };

        template<typename>
        struct call_with_traits;

        template<typename... Ts>
        struct call_with_traits<std::tuple<Ts...>> {
            using tag = tuplelike_tag;
            constexpr static std::size_t size = sizeof...(Ts);
        };

        template<typename... Ts>
        struct call_with_traits<ce_tuple<Ts...>> {
            using tag = tuplelike_tag;
            constexpr static std::size_t size = sizeof...(Ts);
        };

        template<typename T, std::size_t Sz>
        struct call_with_traits<std::array<T, Sz>> {
            using tag = arraylike_tag;
            constexpr static std::size_t size = Sz;
        };

        template<typename T, std::size_t Sz>
        struct call_with_traits<T[Sz]> {
            using tag = arraylike_tag;
            constexpr static std::size_t size = Sz;
        };

        template<std::size_t N, std::size_t... Is>
        struct build_indices_impl : build_indices_impl<(N - 1), (N - 1), Is...>
        { };

        template<std::size_t... Is>
        struct build_indices_impl<0, Is...> : mpl::indices_<Is...>
        { };

        template<std::size_t N>
        struct build_indices : build_indices_impl<N>
        { };

        template<std::size_t I, typename T, std::size_t Sz>
        constexpr T& get(T(&arr)[Sz]) {
            static_assert((I < Sz), "Index out of bounds");
            return arr[I];
        }

        template<std::size_t I, typename T, std::size_t Sz>
        constexpr const T& get(const T(&arr)[Sz]) {
            static_assert((I < Sz), "Index out of bounds");
            return arr[I];
        }

        template<typename F, typename T, std::size_t... Is>
        auto call_with(F&& f, T&& tup, mpl::indices_<Is...>, tuplelike_tag) -> ResultOf<Unqualified<F>> {
            using std::get;     // enable ADL
            return (fix::forward<F>(f))(get<Is>(fix::forward<T>(tup))...);
        }

        template<typename F, typename A, std::size_t... Is>
        auto call_with(F&& f, A&& arr, mpl::indices_<Is...>, arraylike_tag) -> ResultOf<Unqualified<F>> {
            using std::get;     // enable ADL
            return (fix::forward<F>(f))(get<Is>(fix::forward<A>(arr))...);
        }
    }

    template<typename F, typename Cont>
    inline auto call_with(F&& f, Cont&& cont) -> ResultOf<Unqualified<F>> {
        using traits = detail::call_with_traits<Unqualified<Cont>>;
        using tag = typename traits::tag;
        using indices = detail::build_indices<traits::size>;
        return detail::call_with(fix::forward<F>(f), fix::forward<Cont>(cont), indices(), tag());
    }

    namespace detail {

        template<typename T>
        struct object_creator {
        public:

            template<typename... Ts>
            T operator()(Ts&&... ts) const {
                return T(fix::forward<Ts>(ts)...);
            }
        };

        template<typename>
        struct member_fn_caller;

        template<typename Ret, typename C, typename... Arg>
        struct member_fn_caller<Ret(C::*)(Arg...)> {
        public:
            using Fn = Ret(C::*)(Arg...);
        public:

            member_fn_caller(Fn f, C* obj)
            : _fn(f), _obj(obj)
            { }

            template<typename... Ts>
            Ret operator()(Ts&&... ts) const {
                return (_obj->*_fn)(fix::forward<Ts>(ts)...);
            }
        protected:
            Fn _fn;
            C* const _obj;
        };

        template<typename Ret, typename C, typename... Arg>
        struct member_fn_caller<Ret(C::*)(Arg...) const> {
        public:
            using Fn = Ret(C::*)(Arg...) const;
        public:

            member_fn_caller(Fn f, const C* obj)
            : _fn(f), _obj(obj)
            { }

            template<typename... Ts>
            Ret operator()(Ts&&... ts) const {
                return (_obj->*_fn)(fix::forward<Ts>(ts)...);
            }
        protected:
            Fn _fn;
            const C* const _obj;
        };
    }

    template<typename T, typename Cont>
    inline T call_constructor(Cont&& cont) {
        return call_with(detail::object_creator<T>(), fix::forward<Cont>(cont));
    }

    template<typename F, typename Cont>
    inline auto call_function(F&& f, Cont&& cont) -> ResultOf<Unqualified<F>> {
        return call_with(fix::forward<F>(f), fix::forward<Cont>(cont));
    }

    template<typename F, typename C, typename Cont>
    inline auto call_function(F&& f, C * obj, Cont&& cont) -> ResultOf<Unqualified<F>> {
        return call_with(detail::member_fn_caller<Unqualified<F>>(fix::forward<F>(f), obj), fix::forward<Cont>(cont));
    }
}

#endif
