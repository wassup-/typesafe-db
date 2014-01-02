/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef UTIL_HPP_
#define UTIL_HPP_

namespace fp {

	template<typename ForwardInputIter, typename ForwardOutputIter, typename Predicate, typename Tranform>
	inline ForwardOutputIter transform_if(ForwardInputIter first, ForwardInputIter last, ForwardOutputIter result, Predicate pred, Tranform trans) {
		for (; first != last; ++first) {
			if(pred(*first))
			{
				*result = trans(*first);
				++result;
			}
		}
		return result;
	}
}

#endif