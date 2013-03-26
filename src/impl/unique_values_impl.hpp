#ifndef _UNIQUE_VALUES_IMPL_HPP
#define _UNIQUE_VALUES_IMPL_HPP

#include "../is_contained_value.hpp"

namespace fp {
    template<int...> struct int_seq;

    namespace impl {
        template<typename, typename> struct unique_values_impl;
        template<bool, typename, typename> struct unique_values_helper;

        template<int... TLeft, int H, int... T>
        struct unique_values_impl<int_seq<TLeft...>, int_seq<H, T...> > : unique_values_helper < is_contained_value<H, TLeft...>::value, int_seq < TLeft...>, int_seq<H, T...> > {
        };

        template<int... TLeft>
        struct unique_values_impl<int_seq<TLeft...>, int_seq<> > {
            typedef int_seq < TLeft...> type;
        };

        template<int... TLeft, int TRightHead, int... TRightTail>
        struct unique_values_helper < false, int_seq<TLeft...>, int_seq<TRightHead, TRightTail...> > : unique_values_impl < int_seq < TLeft..., TRightHead>, int_seq < TRightTail...> > {
        };

        template<int... TLeft, int TRightHead, int... TRightTail>
        struct unique_values_helper < true, int_seq<TLeft...>, int_seq<TRightHead, TRightTail...> > : unique_values_impl < int_seq < TLeft...>, int_seq < TRightTail...> > {
        };
    }
}

#endif