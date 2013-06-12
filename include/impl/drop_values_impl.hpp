#ifndef _DROP_VALUES_IMPL_HPP
#define _DROP_VALUES_IMPL_HPP

#include "../nth_value_of.hpp"

namespace fp {
    template<int...>
    struct int_seq;

    namespace impl {
        template<int, bool, typename, typename>
        struct drop_values_impl;

        template<int C, bool S, int... L, int... R>
        struct drop_values_impl<C, S, int_seq<L...>, int_seq<R...>> : drop_values_impl<C, (C == (sizeof...(R) - 1)), int_seq<L..., fp::first_value_of<R...>::value>, typename fp::skip_value<R...>::type> {
        };

        template<int C, int... L, int... R>
        struct drop_values_impl<C, true, int_seq<L...>, int_seq<R...>> {
            using type = int_seq<L...>;
        };
    }
}

#endif