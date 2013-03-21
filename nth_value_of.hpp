#ifndef _NTH_VALUE_OF_HPP
#define _NTH_VALUE_OF_HPP

namespace fp {
	template<int, int...> struct nth_value_of;

	template<int I, int H, int... T> struct nth_value_of<I, H, T...> {
		enum { value = nth_value_of<I - 1, T...>::value };
	};

	template<int H, int... T> struct nth_value_of<0, H, T...> {
		enum { value = H };
	};

	template<int... I> struct first_value_of {
		enum { value = nth_value_of<0, I...>::value };
	};

	template<int... I> struct last_value_of {
		enum { value = nth_value_of<sizeof...(I) - 1, I...>::value };
	};
}

#endif