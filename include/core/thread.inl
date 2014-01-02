template<typename Fn>
thread::thread(Fn fn) : _impl(nullptr), _fn(new impl::functor<Fn>(fn))
{ }

template<typename Fn, typename... Arg>
thread::thread(Fn fn, Arg&&... arg) : _impl(nullptr), _fn(new impl::functor_with_args<Fn, Arg...>(fn, std::forward<Arg>(arg)...))
{ }

template<typename C>
thread::thread(void(C::*fn)(), C * obj) : _impl(nullptr), _fn(new impl::member_functor<C>(fn, obj))
{ }

template<typename C, typename... Arg>
thread::thread(void(C::*fn)(Arg...), C * obj, Arg... arg) : _impl(nullptr), _fn(new impl::member_functor_with_args<C, Arg...>(fn, obj, arg...))
{ }