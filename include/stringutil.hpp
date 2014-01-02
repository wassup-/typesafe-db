/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef STRING_UTIL_HPP_
#define STRING_UTIL_HPP_

#include "assert.hpp"		// for FP_ASSERT
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
		{ return std::forward<String>(s).size(); }

		template<
			typename H,
			typename... T
		>
		constexpr inline std::size_t string_size(H&& h, T&&... t)	{
			return string_size(std::forward<H>(h)) + string_size(std::forward<T>(t)...);
		}

		template<
			typename Dst,
			typename Src
		>
		inline void concatenate(Dst& dst, Src&& src)
		{ dst += std::forward<Src>(src); }

		template<
			typename Dst,
			typename H,
			typename... T
		>
		inline void concatenate(Dst& dst, H&& h, T&&... t) {
			concatenate(dst, std::forward<H>(h));
			concatenate(dst, std::forward<T>(t)...);
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
		result.reserve(detail::string_size(std::forward<String>(string)...));
		detail::concatenate(result, std::forward<String>(string)...);
		FP_ASSERT(result.capacity() == result.size(), "Bad reserve(): capacity != size");
		return result;
	}

	template<
		typename H,
		typename... T
	>
	static std::string implode(std::string glue, H&& h, T&&... t) {
		std::string result { };
		result.reserve(detail::string_size(std::forward<H>(h), std::forward<T>(t)...) + (detail::string_size(glue) * sizeof...(T)));
		detail::concatenate(result, std::forward<H>(h));
		int ctx[] = {(detail::concatenate(result, glue, std::forward<T>(t)), void(), 0)...};
		FP_IGNORE(ctx);
		FP_ASSERT(result.capacity() == result.size(), "Bad reserve(): capacity != size");
		return result;
	}

	template<typename ForwardIter>
	static std::string implode(std::string glue, ForwardIter first, ForwardIter last) {
		std::string result { };
		std::size_t dist = std::distance(first, last);
		std::size_t len = std::accumulate(first, last, 0, detail::size_accumulator());
		result.reserve(len + (detail::string_size(glue) * (dist - 1)));
		for(; first != last; ++first) {
			detail::concatenate(result, *first);
		}
		FP_ASSERT(result.capacity() == result.size(), "Bad reserve(): capacity != size");
		return result;
	}

	template<
		typename String,
		std::size_t N
	>
	inline std::string implode(std::string glue, String(&strings)[N]) {
		return implode(glue, &strings[0], &strings[N]);
	}

	template<
		typename String,
		fp::EnableIf<is_std_string<String>> = fp::_
	>
	String tolower(String s) {
		using std::begin; using std::end;
		std::transform(begin(s), end(s), begin(s), [](typename String::value_type c) { using std::tolower; return tolower(c); });
		return s;
	}

	template<
		typename String,
		fp::EnableIf<is_std_string<String>> = fp::_
	>
	String toupper(String s) {
		using std::begin; using std::end;
		std::transform(begin(s), end(s), begin(s), [](typename String::value_type c) { using std::toupper; return toupper(c); });
		return s;
	}
}

#endif
