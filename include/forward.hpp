#ifndef FORWARD_HPP_
#define FORWARD_HPP_

#include <type_traits>

namespace fix {

	template<typename T>
	constexpr inline T&& forward(typename std::remove_reference<T>::type& t)
	{
		return static_cast<T&&>(t);
	}

	template<typename T>
	constexpr inline T&& forward(typename std::remove_reference<T>::type&& t)
	{
		static_assert(!std::is_lvalue_reference<T>::value, "template argument"
				" substituting T in an lvalue reference type");
		return static_cast<T&&>(t);
	}
}

#endif