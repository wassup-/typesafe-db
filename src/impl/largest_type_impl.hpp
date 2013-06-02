#ifndef _LARGEST_TYPE_IMPL_HPP
#define _LARGEST_TYPE_IMPL_HPP

namespace fp {
    namespace impl {
        template<typename...>
        struct largest_type_impl;

        namespace {

            template<int L, int R>
            struct _max {

                enum {
                    value = (L < R) ? R : L
                };
            };

            template<int L, int R>
            struct _min {

                enum {
                    value = (L < R) ? L : R
                };
            };
        }

        template<typename H, typename... T>
        struct largest_type_impl<H, T...> {

            enum {
                value = _max<sizeof(H), largest_type_impl<T...>::size>::value
            };
        };

        template<typename T>
        struct largest_type_impl<T> {

            enum {
                value = sizeof(T)
            };
        };
    }
}

#endif