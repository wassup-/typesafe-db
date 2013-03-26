#ifndef _IS_CONTAINED_VALUE_IMPL_HPP
#define _IS_CONTAINED_VALUE_IMPL_HPP

namespace fp {
    namespace impl {
        template<int, int...> struct is_contained_value_impl;

        template<int I, int H, int... T> struct is_contained_value_impl<I, H, T...> : is_contained_value_impl<I, T...> {
        };

        template<int I, int... T> struct is_contained_value_impl<I, I, T...> {

            enum {
                value = true
            };
        };

        template<int I, int H> struct is_contained_value_impl<I, H> {

            enum {
                value = false
            };
        };

        template<int I> struct is_contained_value_impl<I, I> {

            enum {
                value = true
            };
        };
    }
}

#endif