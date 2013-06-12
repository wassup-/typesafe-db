#ifndef _INSERTION_SORT_IMPL_HPP
#define _INSERTION_SORT_IMPL_HPP

namespace fp {
    template<int...>
    struct int_seq;

    template<typename, typename, typename>
    struct insertion_sort;

    namespace impl {
        template<bool, typename, typename, typename>
        struct insertion_sort_impl;

        template<int... S, int... L, int... R>
        struct insertion_sort_impl<true, int_seq<S...>, int_seq<L...>, int_seq<R...>> {

            enum {
                left = first_value_of<L...>::value
            };

            using left_type = typename skip_values<1, L...>::type;
            using right_type = int_seq<R...>;

            using type = typename insertion_sort<int_seq<S..., left>, left_type, right_type>::type;
        };

        template<int... S, int... L, int... R>
        struct insertion_sort_impl<false, int_seq<S...>, int_seq<L...>, int_seq<R...>> {

            enum {
                right = first_value_of<R...>::value
            };

            using left_type = int_seq<L...>;
            using right_type = typename skip_values<1, R...>::type;

            using type = typename insertion_sort<int_seq<S..., right>, left_type, right_type>::type;
        };
    }
}

#endif