#ifndef _SORTED_VALUES_IMPL_HPP
#define _SORTED_VALUES_IMPL_HPP

#include "../erase_value.hpp"
#include "../smallest_value.hpp"

namespace fp {
	template<int...> struct int_seq;

	namespace impl {
		template<bool, typename, typename, typename> struct sorted_values_helper;
		template<typename, typename, typename> struct sorted_values_impl;

		template<int... S, int... L, int... R> struct sorted_values_helper<true, int_seq<S...>, int_seq<L...>, int_seq<R...> > {
			enum {
				smallest = fp::smallest_value<L...>::value,
				index = fp::index_of<smallest, L...>::value
			};

			typedef typename sorted_values_impl<int_seq<S..., smallest>, typename erase_value<index, L...>::type, int_seq<R...> >::type type;
		};
		template<int... S, int... L, int... R> struct sorted_values_helper<false, int_seq<S...>, int_seq<L...>, int_seq<R...> > {
			enum {
				smallest = fp::smallest_value<R...>::value,
				index = fp::index_of<smallest, R...>::value
			};

			typedef typename sorted_values_impl<int_seq<S..., smallest>, int_seq<L...>, typename erase_value<index, R...>::type>::type type;
		};

		template<int... S, int... L, int... R> struct sorted_values_impl<int_seq<S...>, int_seq<L...>, int_seq<R...> > {
			enum {
				smallest_left = fp::smallest_value<L...>::value,
				smallest_right = fp::smallest_value<R...>::value,
				left_smallest = (smallest_left < smallest_right)
			};

			typedef typename sorted_values_helper<(smallest_left <= smallest_right), int_seq<S...>, int_seq<L...>, int_seq<R...> >::type type;
		};

		template<int... S, int... L> struct sorted_values_impl<int_seq<S...>, int_seq<L...>, int_seq<> > {
			enum {
				smallest = fp::smallest_value<L...>::value,
				index = fp::index_of<smallest, L...>::value
			};

			typedef typename sorted_values_impl<int_seq<S..., smallest>, typename erase_value<index, L...>::type, int_seq<> >::type type;
		};
		template<int... S, int... R> struct sorted_values_impl<int_seq<S...>, int_seq<>, int_seq<R...> > {
			enum {
				smallest = fp::smallest_value<R...>::value,
				index = fp::index_of<smallest, R...>::value
			};

			typedef typename sorted_values_impl<int_seq<S..., smallest>, int_seq<>, typename erase_value<index, R...>::type>::type type;
		};
		template<int... S> struct sorted_values_impl<int_seq<S...>, int_seq<>, int_seq<> > {
			typedef int_seq<S...> type;
		};
	}
}

#endif