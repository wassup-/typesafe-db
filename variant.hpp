#ifndef _VARIANT_HPP
#define _VARIANT_HPP

#include "is_contained_type.hpp"
#include "largest_type.hpp"
#include "nth_type_of.hpp"
#include "type_sequence.hpp"

#include <type_traits>

namespace fp {
	template<typename... Ts> struct variant {
	public:
		typedef fp::type_seq<Ts...> types;
		typedef variant<Ts...> this_type;
		static int const size = fp::largest_type<Ts...>::size;
	protected:
		unsigned char m_buffer[size];
	public:
		variant() { }
		variant(variant const &) { }

		template<int I>
		typename fp::nth_type_of<I, Ts...>::type operator[](fp::arg<I>) {
			typedef typename fp::nth_type_of<I, Ts...>::type return_type;
			static int const offset = (size - sizeof(return_type));
			return *(reinterpret_cast<return_type *>(m_buffer + offset));
		};

		template<typename T>
		typename std::enable_if<fp::is_contained_type<T, Ts...>::value, T>::type get() {
			static int const offset = (size - sizeof(T));
			return *(reinterpret_cast<T *>(m_buffer + offset));
		}
		template<typename T>
		typename std::enable_if<fp::is_contained_type<T, Ts...>::value, void>::type set(T v) {
			static int const offset = (size - sizeof(T));
			*reinterpret_cast<T *>(m_buffer + offset) = v;
		}
	};
}

#endif