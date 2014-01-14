/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _ORDERED_QUERY_IMPL_HPP
#define _ORDERED_QUERY_IMPL_HPP

#include "../record.hpp"
#include "../type_traits.hpp"

#include <functional>   // for std::binary_function

namespace fp { namespace impl { namespace ordered_query {
    
    constexpr static const char* ORDERINGS[] = { "ASC", "DESC" };

    template<typename TRecord, typename TField, EnableIf<is_record<TRecord>> = _>
    struct ascending_sorter : std::binary_function<const TRecord&, const TRecord&, bool> {

        bool operator()(const TRecord& l, const TRecord& r) const {
            return (get<TField>(l) <= get<TField>(r));
        }
    };

    template<typename TRecord, typename TField, EnableIf<is_record<TRecord>> = _>
    struct descending_sorter : std::binary_function<const TRecord&, const TRecord&, bool> {

        bool operator()(const TRecord& l, const TRecord& r) const {
            return (get<TField>(l) >= get<TField>(r));
        }
    };
    
} } }

#endif