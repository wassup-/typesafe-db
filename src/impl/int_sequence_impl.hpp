#ifndef _INT_SEQUENCE_IMPL_HPP
#define _INT_SEQUENCE_IMPL_HPP

namespace fp {
    template<int...> struct int_seq;
    namespace impl {
        template<int...>
        struct int_seq_to_array;
        
        template<int, int, int, int...>
        struct build_range_incr;
        
        template<int, int, int, int...>
        struct build_range_decr;
        
        template<int, int...>
        struct is_contained_int_impl;
        
        template<int, int, int...>
        struct index_of_impl;

        template<int H, int... T>
        struct int_seq_to_array<H, T...> {

            static void to_array(int * arr) {
                arr[0] = H;
                int_seq_to_array<T...>::to_array(arr + 1);
            }
        };

        template<int H>
        struct int_seq_to_array<H> {

            static void to_array(int * arr) {
                arr[0] = H;
            }
        };

        template<int Min, int Max, int Cur, int... R>
        struct build_range_incr : build_range_incr<Min, Max, (Cur + 1), Cur, R...> {
        };

        template<int Min, int Max, int... R>
        struct build_range_incr<Min, Max, Min, R...> : int_seq<Min, R...> {
            typedef int_seq<Min, R...> type;
        };

        template<int Min, int Max, int Cur, int... R>
        struct build_range_decr : build_range_decr<Min, Max, (Cur - 1), Cur, R...> {
        };

        template<int Min, int Max, int... R>
        struct build_range_decr<Min, Max, Min, R...> : int_seq<Min, R...> {
            typedef int_seq<Min, R...> type;
        };

        template<bool /* = false */, int Min, int Max>
        struct range_builder_impl : build_range_incr<Min, Max, Max> {
        };

        template<int Min, int Max>
        struct range_builder_impl<true, Min, Max> : build_range_decr<Min, Max, Max> {
        };

        template<int V, int H, int... T>
        struct is_contained_int_impl<V, H, T...> : is_contained_int_impl<V, T...> {
        };

        template<int V, int... T>
        struct is_contained_int_impl<V, V, T...> {

            enum {
                value = true
            };
        };

        template<int V, int H>
        struct is_contained_int_impl<V, H> {

            enum {
                value = false
            };
        };

        template<int V>
        struct is_contained_int_impl<V, V> {

            enum {
                value = true
            };
        };

        template<int I, int V, int H, int... T>
        struct index_of_impl<I, V, H, T...> : index_of_impl<(I + 1), V, T...> {
        };

        template<int I, int V, int... T>
        struct index_of_impl<I, V, V, T...> {

            enum {
                value = I
            };
        };

        template<int, int, int...>
        struct occurences_of_impl {

            enum {
                value = 0
            };
        };

        template<int C, int V, int H, int... T>
        struct occurences_of_impl<C, V, H, T...> : occurences_of_impl<C, V, T...> {
        };

        template<int C, int V, int... T>
        struct occurences_of_impl<C, V, V, T...> {

            enum {
                value = occurences_of_impl<C, V, T...>::value + 1
            };
        };
    }
}

#endif