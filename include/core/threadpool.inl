template<typename Fn>
void threadpool::push(Fn fn) {
    {
        lock_guard<mutex_t> lg(_mutex);
        _tasks.push_back(new impl::functor<Fn > (fn));
    }
    _semaphore.post();
}

template<typename C>
void threadpool::push(void(C::*fn)(), C * obj) {
    {
        lock_guard<mutex_t> lg(_mutex);
        _tasks.push_back(new impl::member_functor<C > (fn, obj));
    }
    _semaphore.post();
}

template<typename Fn, typename... Arg>
void threadpool::push(Fn fn, Arg&& ... arg) {
    {
        lock_guard<mutex_t> lg(_mutex);
        _tasks.push_back(new impl::functor_with_args<Fn, typename std::remove_reference<Arg>::type...>(fn, std::forward<Arg > (arg)...));
    }
    _semaphore.post();
}

template<typename C, typename... Arg>
void threadpool::push(void(C::*fn)(Arg...), C * obj, Arg... arg) {
    {
        lock_guard<mutex_t> lg(_mutex);
        _tasks.push_back(new impl::functor_with_args<C, typename std::remove_reference<Arg>::type...>(fn, obj, arg...));
    }
    _semaphore.post();
}