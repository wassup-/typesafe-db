/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _IMPLEMENTATION_HPP
#define _IMPLEMENTATION_HPP

#include <algorithm>
#include <type_traits>

namespace fp{
	template<typename T> struct implementation_traits {
		typedef T * pointer;
	};

	template<typename T> struct implementation_traits<T &> {
		typedef T * pointer;
	};

	template<typename T> struct implementation {
	public:
		typedef typename implementation_traits<T>::pointer pointer;

		template<typename N> struct rebind {
			typedef implementation<N> type;
		};
	protected:
		pointer m_impl;

		static pointer clone_or_null(pointer ptr) {
			return (ptr) ? ptr->clone() : 0;
		}
	public:
		explicit implementation(pointer impl) 		: m_impl(impl) { }
		implementation(implementation const & impl)	: m_impl(clone_or_null(impl.m_impl)) { }
		~implementation()							{ delete m_impl; }

		implementation * clone() const 				{ return new implementation(*this); }
		void swap(implementation & impl) 			{ std::swap(m_impl, impl.m_impl); }

		pointer operator->() const 					{ return m_impl; }

		implementation & operator=(pointer impl) 				{ implementation(impl).swap(*this); }
		implementation & operator=(implementation const & impl) { implementation(impl.m_impl).swap(*this); }

		bool operator==(implementation const & impl) const 		{ return (m_impl == impl.m_impl); }
		bool operator!=(implementation const & impl) const 		{ return (m_impl != impl.m_impl); }

		operator bool() const 				{ return m_impl; }
		explicit operator pointer() const 	{ return m_impl; }
	};
}

#endif