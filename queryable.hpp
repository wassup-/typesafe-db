/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

template<typename> struct queryable_base { };
template<typename> struct queryable;

template<typename> struct container_rebind;

template<template<typename> class C, typename T> struct container_rebind<C<T>> {
	template<typename N> struct rebind {
		typedef C<N> type;
	};
};

template<template<typename, typename> class C, typename T, typename A> struct container_rebind<C<T, A> > {
	template<typename N> struct rebind {
		typedef C<N, typename A::template rebind<N>::type > type;
	};
};

template<template<typename, typename> class C, typename T, typename A> struct queryable<C<T, A> > : queryable_base<T>{
public:
	typedef C<T, A> container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::reference reference;
	typedef typename container_type::const_reference const_reference;
	typedef typename container_type::pointer pointer;
	typedef typename container_type::const_pointer const_pointer;
	typedef typename container_type::size_type size_type;

	typedef queryable<container_type> this_type;
protected:
	typedef typename container_type::iterator iterator;
	typedef typename container_type::const_iterator const_iterator;

	container_type & m_original;
public:
	queryable(container_type & cont) : m_original(cont) { }

	template<typename N> queryable<typename container_rebind<container_type>::template rebind<N>::type> select(int) {
		queryable<typename container_rebind<container_type>::template rebind<N>::type> ret;
		return ret;
	}
};