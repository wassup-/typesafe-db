#ifndef UTIL_HPP_
#define UTIL_HPP_

namespace fp {

	template<typename _InputIter, typename _OutputIter, typename _Predicate, typename _Tranform>
	inline _OutputIter transform_if(_InputIter __first, _InputIter __last, _OutputIter __result, _Predicate __pred, _Tranform __trans) {
		for (; __first != __last; ++__first) {
			if (__pred(*__first))
			{
				*__result = __trans(*__first);
				++__result;
			}
		}
		return __result;
	}
}

#endif