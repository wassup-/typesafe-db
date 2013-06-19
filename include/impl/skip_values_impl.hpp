#ifndef _SKIP_VALUES_IMPL_HPP
#define _SKIP_VALUES_IMPL_HPP

namespace fp {
    template<int...>
    struct int_seq;

    namespace impl {
        template<int, bool, int...>
        struct skip_values_helper;
        
        template<int, int...>
        struct skip_values_impl;

        template<int C, int H, int... T>
        struct skip_values_impl<C, H, T...> : skip_values_impl<(C - 1), T...> {
        };

        template<int H, int... T>
        struct skip_values_impl<0, H, T...> {
            using type = int_seq<H, T...>;
        };

        template<> struct skip_values_impl < 0 > {
            using type = int_seq<>;
        };

        template<int C, bool S, int... I> struct skip_values_helper : skip_values_impl<C, I...> {
        };

        template<int C, int... I> struct skip_values_helper<C, true, I...> {
            using type = int_seq<>;
        };
    }
}

#endif