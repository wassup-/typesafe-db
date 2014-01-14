/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

template<typename Fn>
thread::thread(Fn fn)
: _impl(nullptr), _self(Runnable(impl::functor<Fn>(fn)))
{ }

template<typename C>
thread::thread(void(C::*fn)(), C* obj)
: _impl(nullptr), _self(Runnable(impl::member_functor<C>(fn, obj)))
{ }

template<typename Fn, typename... Arg>
thread::thread(Fn fn, Arg&&... arg)
: _impl(nullptr), _self(Runnable(impl::functor_with_args<Fn, Arg...>(fn, fix::forward<Arg>(arg)...)))
{ }

template<typename C, typename... Arg>
thread::thread(void(C::*fn)(Arg...), C* obj, Arg... arg)
: _impl(nullptr), _self(Runnable(impl::member_functor_with_args<C, Arg...>(fn, obj, arg...)))
{ }