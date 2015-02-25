/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef CE_TUPLE_HPP_
#define CE_TUPLE_HPP_

#include "type_traits.hpp"

namespace fp {

	template<typename...>
	class ce_tuple;

	template<>
	class ce_tuple<>
	{
	public:
		template<std::size_t>
		void get() const = delete;
	};

	template<typename H>
	class ce_tuple<H>
	{
	public:
		using this_type = ce_tuple;

	public:
		constexpr ce_tuple() = default;
		constexpr ce_tuple(H h)
		: _head(h)
		{ }

		template<std::size_t I>
		AddLvalueReference<Invoke<std::enable_if<(I == 0), RemoveReference<H>>>> get() noexcept
		{ return _head; }

		template<std::size_t I>
		AddLvalueReference<AddConst<Invoke<std::enable_if<(I == 0), RemoveReference<H>>>>> get() const noexcept
		{ return _head; }

		constexpr std::size_t size() const
		{ return 1; }

	private:
		H _head;
	};

	template<typename H, typename... T>
	class ce_tuple<H, T...>
	{
	public:
		using this_type = ce_tuple;

	public:
		constexpr ce_tuple() = default;
		constexpr ce_tuple(H h, T... t)
		: _head(h)
		, _tail(t...)
		{ }

		template<std::size_t I>
		AddLvalueReference<Invoke<std::enable_if<(I == 0), RemoveReference<H>>>> get() noexcept
		{ return _head; }

		template<std::size_t I>
		AddLvalueReference<AddConst<Invoke<std::enable_if<(I == 0), RemoveReference<H>>>>> get() const noexcept
		{ return _head; }

		template<std::size_t I>
		AddLvalueReference<Invoke<std::enable_if<(I > 0), fp::NthTypeOf<I, fp::RemoveReference<H>, fp::RemoveReference<T>...>>>> get()
		{ return _tail.template get<(I - 1)>(); }

		template<std::size_t I>
		AddLvalueReference<AddConst<Invoke<std::enable_if<(I > 0), fp::NthTypeOf<I, fp::RemoveReference<H>, fp::RemoveReference<T>...>>>>> get() const
		{ return _tail.template get<(I - 1)>(); }

		constexpr std::size_t size() const
		{ return 1 + _tail.size(); }

	private:
		H _head;
		ce_tuple<T...> _tail;
	};

	template<typename... T>
	constexpr ce_tuple<T&...> tie(T&... x)
	{ return { x... }; }

	template<std::size_t I, typename... T>
	constexpr fp::NthTypeOf<I, T...>& get(ce_tuple<T...>& tup)
	{ return tup.template get<I>(); }

	template<std::size_t I, typename... T>
	constexpr const fp::NthTypeOf<I, T...>& get(const ce_tuple<T...>& tup)
	{ return tup.template get<I>(); }

	template<typename... Ts>
	using tuple_size = std::integral_constant<std::size_t, sizeof...(Ts)>;
}

#endif
