#ifndef _APPLY_TUPLE_HPP
#define _APPLY_TUPLE_HPP

#include <tuple>

namespace fp {
	template<int C, int N> struct tuple_applier {
		struct constructor {
			template<typename TType, typename... TTuple, typename... TArg>
			static TType apply(std::tuple<TTuple...> const & t, TArg &&... arg) {
				return tuple_applier<C + 1, N>::constructor::template apply<TType>(t, std::forward<TArg>(arg)..., std::get<C>(t));
			}
		};

		struct function {
			template<typename Fn, typename... TTuple, typename... TArg>
			static typename Fn::return_type apply(Fn fn, std::tuple<TTuple...> const & t, TArg &&... arg) {
				return tuple_applier<C + 1, N>::function::apply(fn, t, std::forward<TArg>(arg)..., std::get<C>(t));
			}
		};
	};
	template<int N> struct tuple_applier<N, N> {
		struct constructor {
			template<typename TType, typename... TTuple, typename... TArg>
			static TType apply(std::tuple<TTuple...> const & t, TArg &&... arg) {
				return TType(std::forward<TArg>(arg)...);
			}
		};

		struct function {
			template<typename Fn, typename... TTuple, typename... TArg>
			static typename Fn::return_type apply(Fn fn, std::tuple<TTuple...> const & t, TArg &&... arg) {
				return fn(std::forward<TArg>(arg)...);
			}
		};
	};

	template<int N> struct apply_tuple {
		struct constructor {
			template<typename TType, typename... TTuple, typename... TArg>
			static TType apply(std::tuple<TTuple...> const & t, TArg &&... arg) {
				return tuple_applier<0, N>::constructor::template apply<TType>(t, std::forward<TArg>(arg)...);
			}
		};

		struct function {
			template<typename Fn, typename... TTuple, typename... TArg>
			static typename Fn::return_type apply(Fn fn, std::tuple<TTuple...> const & t, TArg &&... arg) {
				return tuple_applier<0, N>::function::apply(fn, t, std::forward<TArg>(arg)...);
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