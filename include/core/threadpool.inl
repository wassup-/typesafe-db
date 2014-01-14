/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

template<typename Fn>
void threadpool::push(Fn fn) {
    {
        lock_guard<mutex_t> lg(_mutex);
        _tasks.push_back(impl::functor<Fn>(fn));
    }
    _semaphore.post();
}

template<typename C>
void threadpool::push(void(C::*fn)(), C * obj) {
    {
        lock_guard<mutex_t> lg(_mutex);
        _tasks.push_back(impl::member_functor<C>(fn, obj));
    }
    _semaphore.post();
}

template<typename Fn, typename... Arg>
void threadpool::push(Fn fn, Arg&& ... arg) {
    {
        lock_guard<mutex_t> lg(_mutex);
        _tasks.push_back(impl::functor_with_args<Fn, typename std::remove_reference<Arg>::type...>(fn, fix::forward<Arg>(arg)...));
    }
    _semaphore.post();
}

template<typename C, typename... Arg>
void threadpool::push(void(C::*fn)(Arg...), C * obj, Arg... arg) {
    {
        lock_guard<mutex_t> lg(_mutex);
        _tasks.push_back(impl::functor_with_args<C, typename std::remove_reference<Arg>::type...>(fn, obj, arg...));
    }
    _semaphore.post();
}