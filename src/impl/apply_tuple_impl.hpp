#ifndef _APPLY_TUPLE_IMPL_HPP
#define _APPLY_TUPLE_IMPL_HPP

#include <tuple>

namespace fp {
	namespace impl {
		template<int C, int N> struct apply_tuple_impl {
			struct constructor {
				template<typename TType, typename... TTuple, typename... TArg>
				static TType apply(std::tuple<TTuple...> const & t, TArg &&... arg) {
					return apply_tuple_impl<C + 1, N>::constructor::template apply<TType>(t, std::forward<TArg>(arg)..., std::get<C>(t));
				}
			};

			struct function {
				template<typename Fn, typename... TTuple, typename... TArg>
				static typename Fn::return_type apply(Fn fn, std::tuple<TTuple...> const & t, TArg &&... arg) {
					return apply_tuple_impl<C + 1, N>::function::apply(fn, t, std::forward<TArg>(arg)..., std::get<C>(t));
				}
			};
		};
		
		template<int N> struct apply_tuple_impl<N, N> {
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
	}
}

#endif