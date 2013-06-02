#ifndef _SMALLEST_VALUE_IMPL_HPP
#define _SMALLEST_VALUE_IMPL_HPP

namespace fp {
    namespace impl {
        template<int, int...>
        struct smallest_value_impl;

        template<int S, int H, int... T>
        struct smallest_value_impl<S, H, T...> : smallest_value_impl<(S <= H) ? S : H, T...> {
        };

        template<int H>
        struct smallest_value_impl<H> {

            enum {
                value = H
            };
        };
    }
}

#endif