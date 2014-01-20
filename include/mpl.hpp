/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef MPL_HPP_
#define MPL_HPP_

#include <type_traits>

namespace mpl {

	template<typename...>
	struct type_sequence { };

	template<typename T, T...>
	struct integer_sequence { };

	template<typename T, T V>
	using const_ = std::integral_constant<T, V>;

	template<bool V, typename...>
	using bool_ = const_<bool, V>;

	using true_ = bool_<true>;
	using false_ = bool_<false>;

	template<int I>
	using int_ = const_<int, I>;

	template<std::size_t Idx>
	using index_ = const_<std::size_t, Idx>;

	template<typename T>
	struct identity { using type = T; };
	template<typename T>
	using identity_t = typename T::type;

	namespace detail {
		template<typename, typename>
		struct is_same : identity<false_> { };
		template<typename T>
		struct is_same<T, T> : identity<true_> { };
	}

	template<typename T, typename U>
	using is_same = identity_t<detail::is_same<T, U>>;

	template<bool, typename Then, typename Else>
	struct if_ : identity<Then> { };
	template<typename Then, typename Else>
	struct if_<false, Then, Else> : identity<Else> { };

	template<typename If, typename Then, typename Else>
	using eval_if = identity_t<if_<If::value, Then, Else>>;

	namespace detail {

		template<typename H, typename... T>
		struct any_of : eval_if<H, true_, any_of<T...>> { };
		template<typename H>
		struct any_of<H> : eval_if<H, true_, false_> { };

		template<typename H, typename... T>
		struct all_of : eval_if<H, all_of<T...>, false_> { };
		template<typename H>
		struct all_of<H> : eval_if<H, true_, false_> { };

		template<typename H, typename... T>
		struct none_of : eval_if<H, false_, none_of<T...>> { };
		template<typename H>
		struct none_of<H> : eval_if<H, false_, true_> { };
	}

	template<typename T>
	using not_ = identity_t<detail::none_of<T>>;

	template<typename... T>
	using any_ = identity_t<detail::any_of<T...>>;
	template<typename... T>
	using all_ = identity_t<detail::all_of<T...>>;
	template<typename... T>
	using none_ = identity_t<detail::none_of<T...>>;

	template<typename If, typename T = void>
	using enable_if = std::enable_if<If::value, T>;
	template<typename If, typename T = void>
	using enable_if_t = identity_t<enable_if<If, T>>;

	template<typename If, typename T = void>
	using disable_if = std::enable_if<not_<If>::value, T>;
	template<typename If, typename T = void>
	using disable_if_t = identity_t<disable_if<If, T>>;

	template<typename If, typename Then, typename Else>
	using conditional = eval_if<If, Then, Else>;
	template<typename If, typename Then, typename Else>
	using conditional_t = identity_t<conditional<If, Then, Else>>;

	namespace detail {

		template<typename Head, typename... Tail>
        struct min : Head { };
        template<typename T, typename U, typename... Tail>
        struct min<T, U, Tail...> : min<conditional<bool_<(T::value < U::value)>, T, U>, Tail...> { };

        template<typename Head, typename... Tail>
        struct max : Head { };
        template<typename T, typename U, typename... Tail>
        struct max<T, U, Tail...> : max<conditional<bool_<(T::value > U::value)>, T, U>, Tail...> { };
	}

	template<typename... T>
	using min_ = identity_t<detail::min<T...>>;
	template<typename... T>
	using max_ = identity_t<detail::max<T...>>;

	namespace detail {

        template<typename... T>
        struct count : mpl::int_<0> { };
        template<typename Head, typename... Tail>
        struct count<Head, Tail...> : mpl::int_<(!!Head::value) + count<Tail...>::value> { };
    }
    
    template<typename... T>
    using count_ = identity_t<detail::count<T...>>;
}

#endif
