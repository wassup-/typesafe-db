#ifndef CALL_WITH_HPP_
#define CALL_WITH_HPP_

#include "type_traits.hpp"      // for fp::ResultOf, fp::Unqualified

#include <array>                // for std::array, std::get
#include <cstddef>              // for std::size_t
#include <tuple>                // for std::tuple, std::get
#include <utility>              // for std::forward

namespace fp {
    namespace detail {

        struct tuplelike_tag { };
        struct arraylike_tag { };

        template<typename>
        struct call_with_traits;

        template<typename... Ts>
        struct call_with_traits<std::tuple<Ts...>> {
            using tag = tuplelike_tag;

            enum { size = sizeof...(Ts) };
        };

        template<typename T, std::size_t Sz>
        struct call_with_traits<std::array<T, Sz>> {
            using tag = arraylike_tag;

            enum { size = Sz };
        };

        template<typename T, std::size_t Sz>
        struct call_with_traits<T[Sz]> {
            using tag = arraylike_tag;

            enum { size = Sz };
        };
        
        template<std::size_t N, std::size_t... Is>
        struct build_indices_impl : build_indices_impl<(N - 1), (N - 1), Is...>
        { };

        template<std::size_t... Is>
        struct build_indices_impl<0, Is...> : val_seq<std::size_t, Is...>
        { };
        
        template<std::size_t N>
        struct build_indices : build_indices_impl<N>
        { };
        
        template<std::size_t I, typename T, std::size_t Sz>
        constexpr T & get(T(&arr)[Sz]) {
            static_assert(I < Sz, "Index out of bounds");
            return arr[I];
        }
        
        template<std::size_t I, typename T, std::size_t Sz>
        constexpr T const & get(T const(&arr)[Sz]) {
            static_assert(I < Sz, "Index out of bounds");
            return arr[I];
        }
        
        template<typename F, typename T, std::size_t... Is>
        auto call_with(F && f, T && tup, val_seq<std::size_t, Is...>, tuplelike_tag) -> ResultOf<Unqualified<F>> {
            return (std::forward<F>(f))(std::get<Is>(std::forward<T>(tup))...);
        }

        template<typename F, typename A, std::size_t... Is>
        auto call_with(F && f, A && arr, val_seq<std::size_t, Is...>, arraylike_tag) -> ResultOf<Unqualified<F>> {
            using std::get;     // enable ADL
            return (std::forward<F>(f))(get<Is>(std::forward<A>(arr))...);
        }
    }

    template<typename F, typename Cont>
    inline auto call_with(F && f, Cont && cont) -> ResultOf<Unqualified<F>> {
        using traits = detail::call_with_traits<Unqualified<Cont>>;
        using tag = typename traits::tag;
        using indices = detail::build_indices<traits::size>;
        return detail::call_with(std::forward<F>(f), std::forward<Cont>(cont), indices(), tag());
    }

    namespace detail {

        template<typename T>
        struct object_creator {

            template<typename... Ts >
            T operator()(Ts && ... ts) {
                return T { std::forward<Ts>(ts)... };
            }
        };

        template<typename>
        struct member_fn_caller;

        template<typename Ret, typename C, typename... Arg>
        struct member_fn_caller<Ret(C::*)(Arg...)> {
            using Fn = Ret(C::*)(Arg...);
        protected:
            Fn _fn;
            C * const _obj;
        public:

            member_fn_caller(Fn f, C * obj)
            : _fn(f), _obj(obj) {
            }

            template<typename... Ts >
            Ret operator()(Ts && ... ts) {
                return (_obj->*_fn)(std::forward<Ts>(ts)...);
            }
        };
        
        template<typename Ret, typename C, typename... Arg>
        struct member_fn_caller<Ret(C::*)(Arg...) const> {
            using Fn = Ret(C::*)(Arg...) const;
        protected:
            Fn _fn;
            C const * const _obj;
        public:

            member_fn_caller(Fn f, C const * obj)
            : _fn(f), _obj(obj) {
            }

            template<typename... Ts >
            Ret operator()(Ts && ... ts) {
                return (_obj->*_fn)(std::forward<Ts>(ts)...);
            }
        };
    }
    
    template<typename T, typename Cont>
    inline T call_constructor(Cont && cont) {
        return call_with(detail::object_creator<T>(), std::forward<Cont>(cont));
    }

    template<typename F, typename Cont>
    inline auto call_function(F && f, Cont && cont) -> ResultOf<Unqualified<F>> {
        return call_with(std::forward<F>(f), std::forward<Cont>(cont));
    }
    
    template<typename F, typename C, typename Cont>
    inline auto call_function(F && f, C * obj, Cont && cont) -> ResultOf<Unqualified<F>> {
        return call_with(detail::member_fn_caller<Unqualified<F>>(std::forward<F>(f), obj), std::forward<Cont>(cont));
    }
}

#endif
