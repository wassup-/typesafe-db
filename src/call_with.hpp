#ifndef CALL_WITH_TUPLE_HPP_
#define CALL_WITH_TUPLE_HPP_

#include "indices.hpp"
#include "result_of.hpp"        // for fp::result_of
#include "type_traits.hpp"      // for RemoveReference

#include <array>                // for std::array
#include <tuple>                // for std::tuple, std::get
#include <utility>              // for std::forward

namespace fp {
    namespace detail {

        template<typename F, typename... Ts, int... Is>
        auto call_with_tuple(F && f, std::tuple<Ts...> const & t, indices<Is...>) -> Invoke<result_of<Unqualified<F>>> {
            return (std::forward<F>(f))(std::get<Is>(t)...);
        }
        
        template<typename F, typename T, std::size_t Sz, int... Is>
        auto call_with_array(F && f, std::array<T, Sz> const & a, indices<Is...>) -> Invoke<result_of<Unqualified<F>>> {
            return (std::forward<F>(f))(a[Is]...);
        }
    }

    template<typename F, typename... Ts>
    inline auto call_with_tuple(F && f, std::tuple<Ts...> const & t) -> Invoke<result_of<Unqualified<F>>> {
        return detail::call_with_tuple(std::forward<F>(f), t, build_indices<sizeof...(Ts)>());
    }
    
    template<typename F, typename T, std::size_t Sz>
    inline auto call_with_array(F && f, std::array<T, Sz> const & a) -> Invoke<result_of<Unqualified<F>>> {
        return detail::call_with_array(std::forward<F>(f), a, build_indices<Sz>());
    }

    namespace detail {

        template<typename T>
        struct object_creator {

            template<typename... Ts >
            T operator()(Ts &&... ts) {
                return T(std::forward<Ts>(ts)...);
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

            template<typename... Ts>
            Ret operator()(Ts &&... ts) {
                return (_obj->*_fn)(std::forward<Ts>(ts)...);
            }
        };
    }

    template<typename C, typename... Ts>
    inline C call_constructor(std::tuple<Ts...> const & t) {
        return call_with_tuple(detail::object_creator<C>(), t);
    }
    
    template<typename C, typename T, std::size_t Sz>
    inline C call_constructor(std::array<T, Sz> const & a) {
        return call_with_array(detail::object_creator<C>(), a);
    }

    template<typename F, typename... Ts>
    inline auto call_function(F && f, std::tuple<Ts...> const & t) -> Invoke<result_of<Unqualified<F>>> {
        return call_with_tuple(std::forward<F>(f), t);
    }
    
    template<typename F, typename T, std::size_t Sz>
    inline auto call_function(F && f, std::array<T, Sz> const & a) -> Invoke<result_of<Unqualified<F>>> {
        return call_with_array(std::forward<F>(f), a);
    }

    template<typename F, typename C, typename... Ts>
    inline auto call_function(F && f, C * obj, std::tuple<Ts...> const & t) -> Invoke<result_of<Unqualified<F>>> {
        return call_with_tuple(detail::member_fn_caller<F>(std::forward<F>(f), obj), t);
    }
    
    template<typename F, typename C, typename T, std::size_t Sz>
    inline auto call_function(F && f, C * obj, std::array<T, Sz> const & a) -> Invoke<result_of<Unqualified<F>>> {
        return call_with_array(detail::member_fn_caller<F>(std::forward<F>(f), obj), a);
    }
}

#endif
