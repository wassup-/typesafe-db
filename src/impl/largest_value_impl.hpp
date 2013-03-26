#ifndef _LARGEST_VALUE_IMPL_HPP
#define _LARGEST_VALUE_IMPL_HPP

namespace fp {
    namespace impl {
        template<int, int...> struct largest_value_impl;

        template<int S, int H, int... T> struct largest_value_impl<S, H, T...> : largest_value_impl < ((S >= H) ? S : H), T...> {
        };

        template<int S> struct largest_value_impl<S> {

            enum {
                value = S
            };
        };
    }
}

#endif