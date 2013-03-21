#ifndef _BIND_UNWRAP_H
#define _BIND_UNWRAP_H

namespace fp {
	template<typename R, typename F> struct unwrapped_fn;

	template<typename R, typename F> struct unwrapped_fn {
	public:
		typedef R return_type;
		typedef F function_type;
	protected:
		F * m_fn;
	public:
		unwrapped_fn(F * fn) : m_fn(fn) { }

		template<typename... A>
		R operator()(A... a) const {
			return m_fn(a...);
		}
	};

	template<typename R, typename C, typename F> struct unwrapped_fn<R, R(C::*)()

	template<typename R, typename... A>
	unwrapped_fn<R, R(*)(A...)> unwrap(R(*fn)(A...)) {
		return fn;
	};
}

#endif