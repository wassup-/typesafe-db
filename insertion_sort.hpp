#ifndef _INSERTION_SORT_HPP
#define _INSERTION_SORT_HPP

#include "nth_value_of.hpp"
#include "skip_values.hpp"

namespace fp {
	template<int...> struct int_seq;
	template<typename, typename, typename> struct insertion_sort;

	namespace impl {
		template<bool, typename, typename, typename> struct insertion_sort_impl;

		template<int... S, int... L, int... R> struct insertion_sort_impl<true, int_seq<S...>, int_seq<L...>, int_seq<R...> > {
			enum { left = first_value_of<L...>::value };

			typedef typename skip_values<1, L...>::type left_type;
			typedef int_seq<R...> right_type;

			typedef typename insertion_sort<int_seq<S..., left>, left_type, right_type>::type type;
		};

		template<int... S, int... L, int... R> struct insertion_sort_impl<false, int_seq<S...>, int_seq<L...>, int_seq<R...> > {
			enum { right = first_value_of<R...>::value };

			typedef int_seq<L...> left_type;
			typedef typename skip_values<1, R...>::type right_type;

			typedef typename insertion_sort<int_seq<S..., right>, left_type, right_type>::type type;
		};
	}

	template<int... S, int... L, int... R> struct insertion_sort<int_seq<S...>, int_seq<L...>, int_seq<R...> > {
		enum { left = first_value_of<L...>::value };
		enum { right = first_value_of<R...>::value };

		typedef typename impl::insertion_sort_impl<(left < right), int_seq<S...>, int_seq<L...>, int_seq<R...> >::type type;
	};
	template<int... S, int... L> struct insertion_sort<int_seq<S...>, int_seq<L...>, int_seq<> > {
		typedef typename insertion_sort<int_seq<S..., L...>, int_seq<>, int_seq<> >::type type;
	};
	template<int... S, int... R> struct insertion_sort<int_seq<S...>, int_seq<>, int_seq<R...> > {
		typedef typename insertion_sort<int_seq<S..., R...>, int_seq<>, int_seq<> >::type type;
	};
	template<int... S> struct insertion_sort<int_seq<S...>, int_seq<>, int_seq<> > {
		typedef int_seq<S...> type;
	};
}

#endif