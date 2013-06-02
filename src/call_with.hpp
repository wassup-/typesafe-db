#ifndef CALL_WITH_HPP_
#define CALL_WITH_HPP_

#include "indices.hpp"          // for fp::indices, fp::build_indices
#include "result_of.hpp"        // for fp::result_of
#include "type_traits.hpp"      // for Unqualified

#include <array>                // for std::array
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

        template<typename F, typename T, int... Is>
        auto call_with(F && f, T && tup, indices<Is...>, tuplelike_tag) -> Invoke<result_of<Unqualified<F>>> {
            return (std::forward<F>(f))(std::get<Is>(std::forward<T>(tup))...);
        }

        template<typename F, typename A, int... Is>
        auto call_with(F && f, A && arr, indices<Is...>, arraylike_tag) -> Invoke<result_of<Unqualified<F>>> {
            return (std::forward<F>(f))(std::forward<A>(arr)[Is]...);
        }
    }

    template<typename F, typename Cont>
    inline auto call_with(F && f, Cont && cont) -> Invoke<result_of<Unqualified<F >>> {
        using unqualified = Unqualified<Cont>;
        using tag = typename detail::call_with_traits<unqualified>::tag;
        return detail::call_with(std::forward<F>(f), std::forward<Cont>(cont), build_indices<detail::call_with_traits<unqualified>::size>(), tag());
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
            C * _obj;
        public:

            member_fn_caller(Fn f, C * obj)
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
    inline auto call_function(F && f, Cont && cont) -> Invoke<result_of<Unqualified<F>>> {
        return call_with(std::forward<F>(f), std::forward<Cont>(cont));
    }
    
    template<typename F, typename C, typename Cont>
    inline auto call_function(F && f, C * obj, Cont && cont) -> Invoke<result_of<Unqualified<F>>> {
        return call_with(detail::member_fn_caller<Unqualified<F>>(std::forward<F>(f), obj), std::forward<Cont>(cont));
    }
}

#endif
