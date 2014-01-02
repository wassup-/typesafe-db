/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ERASE_HPP
#define ERASE_HPP

#include "container_traits.hpp"

#include <algorithm>	// for std::remove, std::remove_if

namespace fp {
    namespace impl {

        template<typename TContainer, typename TValue>
        typename TContainer::iterator erase_impl(TContainer& cont, const TValue& val, vectorlike_tag) {
            return cont.erase(std::remove(cont.begin(), cont.end(), val), cont.end());
        }

        template<typename TContainer, typename TValue>
        typename TContainer::iterator erase_impl(TContainer& cont, const TValue& val, listlike_tag) {
            return cont.remove(val);
        }

        template<typename TContainer, typename TValue>
        typename TContainer::iterator erase_impl(TContainer& cont, const TValue& val, associative_tag) {
            return cont.erase(val);
        }

        template<typename TContainer, typename TPred>
        typename TContainer::iterator erase_if_impl(TContainer& cont, TPred pred, vectorlike_tag) {
            return cont.erase(std::remove_if(cont.begin(), cont.end(), pred), cont.end());
        }

        template<typename TContainer, typename TPred>
        typename TContainer::iterator erase_if_impl(TContainer& cont, TPred pred, listlike_tag) {
            return cont.remove_if(pred);
        }

        template<typename TContainer, typename TPred>
        typename TContainer::iterator erase_if_impl(TContainer& cont, TPred pred, associative_tag) {
            auto ret = cont.end();
            for (auto it = cont.begin(); it != cont.end(); /* */) {
                if (pred(*it)) {
                    ret = cont.erase(it++);
                } else {
                    ++it;
                }
            }
            return ret;
        }
    }

    template<typename TContainer, typename TValue>
    typename TContainer::iterator erase(TContainer& cont, const TValue& val) {
        typedef typename container_traits<TContainer>::category tag;
        return impl::erase_impl(cont, val, tag());
    }

    template<typename TContainer, typename TPred>
    typename TContainer::iterator erase_if(TContainer& cont, TPred pred) {
        typedef typename container_traits<TContainer>::category tag;
        return impl::erase_if_impl(cont, pred, tag());
    }
}

#endif