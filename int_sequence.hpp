#ifndef _INT_SEQ_H
#define _INT_SEQ_H

namespace fp {
	template<int...> struct int_seq;
	template<int, int> struct range_builder;

	namespace impl {
		template<int...> struct int_seq_to_array;
		template<int H, int... T> struct int_seq_to_array<H, T...> {
			static void to_array(int * arr) {
				arr[0] = H;
				int_seq_to_array<T...>::to_array(arr + 1);
			}
		};
		template<int H> struct int_seq_to_array<H> {
			static void to_array(int * arr) {
				arr[0] = H;
			}
		};
	}

	template<int... Is> struct int_seq {
		enum { size = sizeof...(Is) };

		static void to_array(int * arr) {
			impl::int_seq_to_array<Is...>::to_array(arr);
		}

		template<template<int...> class C> struct as {
			typedef C<Is...> type;
		};
	};

	namespace impl {
		template<int, int, int, int...> struct build_range_incr;
		template<int, int, int, int...> struct build_range_decr;
		template<int, int...> struct is_contained_int_impl;
		template<int, int, int...> struct index_of_impl;

		template<int Min, int Max, int Cur, int... R> struct build_range_incr : build_range_incr<Min, Max, Cur + 1, Cur, R...> { };
		template<int Min, int Max, int... R> struct build_range_incr<Min, Max, Min, R...> : int_seq<Min, R...> { typedef int_seq<Min, R...> type; };

		template<int Min, int Max, int Cur, int... R> struct build_range_decr : build_range_decr<Min, Max, Cur - 1, Cur, R...> { };
		template<int Min, int Max, int... R> struct build_range_decr<Min, Max, Min, R...> : int_seq<Min, R...> { typedef int_seq<Min, R...> type; };

	
		template<bool /* = false */, int Min, int Max> struct range_builder_impl {
			typedef typename build_range_incr<Min, Max, Max>::type type;	
		};
		template<int Min, int Max> struct range_builder_impl<true, Min, Max> {
			typedef typename build_range_decr<Min, Max, Max>::type type;	
		};

		template<int V, int H, int... T> struct is_contained_int_impl<V, H, T...> {
			enum { value = is_contained_int_impl<V, T...>::value };
		};
		template<int V, int... T> struct is_contained_int_impl<V, V, T...> {
			enum { value = true };
		};
		template<int V, int H> struct is_contained_int_impl<V, H> {
			enum { value = false };
		};
		template<int V> struct is_contained_int_impl<V, V> {
			enum { value = true };
		};

		template<int I, int V, int H, int... T> struct index_of_impl<I, V, H, T...> {
			enum { value = index_of_impl<I + 1, V, T...>::value };
		};
		template<int I, int V, int... T> struct index_of_impl<I, V, V, T...> {
			enum { value = I };
		};

		template<int, int, int...> struct occurences_of_impl {
			enum { value = 0 };
		};
		template<int C, int V, int H, int... T> struct occurences_of_impl<C, V, H, T...> {
			enum { value = occurences_of_impl<C, V, T...>::value };
		};
		template<int C, int V, int... T> struct occurences_of_impl<C, V, V, T...> {
			enum { value = occurences_of_impl<C, V, T...>::value + 1 };
		};
	}

	template<int V, int... Vs> struct occurences_of {
		enum { value = impl::occurences_of_impl<0, V, Vs...>::value };
	};

	template<int V, int... Vs> struct index_of {
		enum { value = impl::index_of_impl<0, V, Vs...>::value };
	};

	template<int Min, int Max> struct range_builder {
		typedef typename impl::range_builder_impl<Min <= Max, Min, Max>::type type;	
	};

	template<int Min, int Max> typename range_builder<Min, Max>::type make_range() {
		return typename range_builder<Min, Max>::type();
	}

	template<int V, int... Vs> struct is_contained_int {
		enum { value = impl::is_contained_int_impl<V, Vs...>::value };
	};
};

#endif