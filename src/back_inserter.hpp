/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _BACK_INSERTER_HPP
#define _BACK_INSERTER_HPP

#include <utility>

namespace std {
	template<typename, typename> struct vector;
}

namespace fp {
	template<typename> struct front_inserter;
	template<typename> struct back_inserter;

	template<typename TType, typename TAlloc> struct front_inserter<std::vector<TType, TAlloc> > {
	public:
		template<typename T> struct rebind {
			typedef front_inserter<T> type;
		};
	protected:
		std::vector<TType, TAlloc> & m_cont;		
	public:
		front_inserter(std::vector<TType, TAlloc> & vec) : m_cont(vec) { }

		template<typename T>
		void operator()(T && t) {
			m_cont.push_front(std::forward<T>(t));
		}
	};

	template<typename TType, typename TAlloc> struct back_inserter<std::vector<TType, TAlloc> > {
	public:
		template<typename T> struct rebind {
			typedef back_inserter<T> type;
		};
	protected:
		std::vector<TType, TAlloc> & m_cont;
	public:
		back_inserter(std::vector<TType, TAlloc> & vec) : m_cont(vec) { }

		template<typename T>
		void operator()(T && t) {
			m_cont.push_back(std::forward<T>(t));
		}
	};
}

#endif