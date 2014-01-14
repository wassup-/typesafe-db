/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef STRING_UTIL_HPP_
#define STRING_UTIL_HPP_

#include "assert.hpp"		// for FP_ASSERT
#include "forward.hpp"		// for fix::forward
#include "type_traits.hpp"	// fp::EnableIf, fp::Unqualified

#include <algorithm>	// for std::accumulate, std::distance, std::transform
#include <cctype>		// for std::tolower, std::toupper
#include <cstring>		// for std::strlen

#define FP_IGNORE(x) (void)x

// forward declaration so we don't need to include <string>
namespace std {

	template<typename CharT, typename Traits, typename Alloc>
	class basic_string;
}

namespace stringutils {

	template<typename>
	struct is_char_type : std::false_type { };
	template<typename T>
	struct is_char_type<const T> : is_char_type<T> { };
	template<>
	struct is_char_type<char> : std::true_type { };
	template<>
	struct is_char_type<wchar_t> : std::true_type { };
	template<>
	struct is_char_type<char16_t> : std::true_type { };
	template<>
	struct is_char_type<char32_t> : std::true_type { };

	template<typename>
	struct is_std_string : std::false_type { };
	template<typename T>
	struct is_std_string<const T> : is_std_string<T> { };
	template<typename CharT, typename Traits, typename Alloc>
	struct is_std_string<std::basic_string<CharT, Traits, Alloc>> : std::true_type { };

	template<typename T>
	struct is_string_like : std::conditional<
								is_std_string<T>::value,
								std::true_type,
								is_char_type<
									decltype(std::declval<T&>()[0])
								>
							>::type { };


	namespace detail {

		template<
			typename Char,
			std::size_t N,
			fp::EnableIf<is_char_type<Char>> = fp::_
		>
		constexpr inline std::size_t string_size(Char(&)[N])
		{ return N - 1; }

		template<
			typename Ptr,
			fp::EnableIf<
				fp::All<
					std::is_pointer<Ptr>,
					is_char_type<fp::RemovePointer<Ptr>>
				>
			> = fp::_
		>
		constexpr inline std::size_t string_size(Ptr s)
		{ return s ? std::strlen(s) : 0; }

		template<
			typename String,
			fp::EnableIf<is_std_string<fp::Unqualified<String>>> = fp::_
		>
		constexpr inline std::size_t string_size(String&& s)
		{ return fix::forward<String>(s).size(); }

		template<
			typename H,
			typename... T
		>
		constexpr inline std::size_t string_size(H&& h, T&&... t)	{
			return string_size(fix::forward<H>(h)) + string_size(fix::forward<T>(t)...);
		}

		template<
			typename Dst,
			typename Src
		>
		inline void concatenate(Dst& dst, Src&& src)
		{ dst += fix::forward<Src>(src); }

		template<
			typename Dst,
			typename H,
			typename... T
		>
		inline void concatenate(Dst& dst, H&& h, T&&... t) {
			concatenate(dst, fix::forward<H>(h));
			concatenate(dst, fix::forward<T>(t)...);
		}

		struct size_accumulator {

			template<typename T>
			constexpr std::size_t operator()(std::size_t size, const T& string) const {
				return size + string_size(string);
			}
		};
	}

	template<typename... String>
	static std::string concatenate(String&&... string) {
		std::string result { };
		result.reserve(detail::string_size(fix::forward<String>(string)...));
		detail::concatenate(result, fix::forward<String>(string)...);
		FP_ASSERT(result.capacity() == result.size(), "Bad reserve(): capacity != size");
		return result;
	}

	template<
		typename H,
		typename... T
	>
	static std::string implode(std::string glue, H&& h, T&&... t) {
		std::string result { };
		result.reserve(detail::string_size(fix::forward<H>(h), fix::forward<T>(t)...) + (detail::string_size(glue) * sizeof...(T)));
		detail::concatenate(result, fix::forward<H>(h));
		int ctx[] = { 0, (detail::concatenate(result, glue, fix::forward<T>(t)), void(), 0)... };
		FP_IGNORE(ctx);
		FP_ASSERT(result.capacity() == result.size(), "Bad reserve(): capacity != size");
		return result;
	}

	template<typename ForwardIter>
	static std::string implode(std::string glue, ForwardIter first, ForwardIter last) {
		std::string result { };
		if(first == last) { return result; }
		const std::size_t dist = std::distance(first, last);
		const std::size_t len = std::accumulate(first, last, 0, detail::size_accumulator());
		result.reserve(len + (detail::string_size(glue) * (dist - 1)));
		detail::concatenate(result, *first);
		for(++first; first != last; ++first) {
			detail::concatenate(result, glue, *first);
		}
		FP_ASSERT(result.capacity() == result.size(), "Bad reserve(): capacity != size");
		return result;
	}

	template<
		typename String,
		std::size_t N,
		fp::DisableIf<is_char_type<String>> = fp::_
	>
	inline std::string implode(std::string glue, const String(&strings)[N]) {
		if(N == 1) { return strings[0]; }
		return implode(glue, &strings[0], &strings[N]);
	}

	template<
		typename String,
		fp::EnableIf<is_std_string<String>> = fp::_
	>
	inline String tolower(String s) {
		using std::begin; using std::end;
		std::transform(begin(s), end(s), begin(s), [](typename String::value_type c) { using std::tolower; return tolower(c); });
		return s;
	}

	template<
		typename String,
		fp::EnableIf<is_std_string<String>> = fp::_
	>
	inline String toupper(String s) {
		using std::begin; using std::end;
		std::transform(begin(s), end(s), begin(s), [](typename String::value_type c) { using std::toupper; return toupper(c); });
		return s;
	}
}

#endif
