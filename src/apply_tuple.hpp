/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _APPLY_TUPLE_HPP
#define _APPLY_TUPLE_HPP

#include "impl/apply_tuple_impl.hpp"

#include <tuple>

namespace fp {
	template<int N> struct apply_tuple {
		struct constructor {
			template<typename TType, typename... TTuple, typename... TArg>
			static TType apply(std::tuple<TTuple...> const & t, TArg &&... arg) {
				return impl::apply_tuple_impl<0, N>::constructor::template apply<TType>(t, std::forward<TArg>(arg)...);
			}
		};

		struct function {
			template<typename Fn, typename... TTuple, typename... TArg>
			static typename Fn::return_type apply(Fn fn, std::tuple<TTuple...> const & t, TArg &&... arg) {
				return impl::apply_tuple_impl<0, N>::function::apply(fn, t, std::forward<TArg>(arg)...);
			}
		};
	};

	template<typename> struct wrap_call;
	template<typename TRet, typename... TArg> struct wrap_call<TRet(*)(TArg...)> {
	public:
		typedef TRet return_type;
	protected:
		TRet(*m_fn)(TArg...);
	public:
		wrap_call(TRet(*fn)(TArg...)) : m_fn(fn) { }

		template<typename... Arg> TRet operator()(Arg &&... arg) const {
			return (*m_fn)(std::forward<Arg>(arg)...);
		}
	};
	template<typename TClass, typename TRet, typename... TArg> struct wrap_call<TRet(TClass::*)(TArg...)> {
	public:
		typedef TRet return_type;
	protected:
		TClass * m_obj;
		TRet(TClass::*m_fn)(TArg...);
	public:
		wrap_call(TClass & obj, TRet(TClass::*fn)(TArg...)) : m_obj(&obj), m_fn(fn) { }

		template<typename... Arg> TRet operator()(Arg &&... arg) const {
			return (m_obj->*m_fn)(std::forward<Arg>(arg)...);
		}
	};

	template<typename TClass, typename TRet, typename... TArg> struct wrap_call<TRet(TClass::*)(TArg...) const> {
	public:
		typedef TRet return_type;
	protected:
		TClass const * m_obj;
		TRet(TClass::*m_fn)(TArg...) const;
	public:
		wrap_call(TClass const & obj, TRet(TClass::*fn)(TArg...) const) : m_obj(&obj), m_fn(fn) { }

		TRet operator()(TArg &&... arg) const {
			return (m_obj->*m_fn)(std::forward<TArg>(arg)...);
		}
	};

	template<typename Fn, typename... TTuple, typename... TArg>
	inline auto call_function(Fn fn, std::tuple<TTuple...> const & tup, TArg &&... arg) -> decltype(apply_tuple<std::tuple_size<std::tuple<TTuple...> >::value>::function::apply(fn, tup, std::forward<TArg>(arg)...)) {
		return apply_tuple<std::tuple_size<std::tuple<TTuple...> >::value>::function::apply(fn, tup, std::forward<TArg>(arg)...);
	}

	template<typename C, typename... TTuple, typename... TArg>
	inline C call_constructor(std::tuple<TTuple...> const & tup, TArg &&... arg) {
		return apply_tuple<std::tuple_size<std::tuple<TTuple...> >::value>::constructor::template apply<C>(tup, std::forward<TArg>(arg)...);
	}
}

#endif