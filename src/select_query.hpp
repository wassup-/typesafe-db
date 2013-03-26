/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SELECT_QUERY_HPP
#define _SELECT_QUERY_HPP

#include "impl/select_query_impl.hpp"

#include "is_query.hpp"
#include "query_combiner.hpp"
#include "record.hpp"

#include <cstddef>      // for int
#include <string>       // for std::string, std::to_string
#include <vector>       // for std::vector

namespace fp {
    template<typename, int...> struct select_query;

    template<typename TDescriptor, int... Is> struct is_query<select_query<TDescriptor, Is...> > {

        enum {
            value = true
        };
    };

    template<typename TDescriptor, int... Cs> struct select_query {
    public:
        typedef TDescriptor descriptor_type;
        typedef typename impl::select_query_impl<typename TDescriptor::record::type>::template result_of < Cs...>::type result_type;
    public:

        friend void swap(select_query & l, select_query & r) {
            using std::swap;
        }

        template<int... Fs >
        friend result_type select(record<TDescriptor, Fs...> const & rec, select_query const & q) {
            return impl::select_query_impl < record<TDescriptor, Fs...> >::template select < Cs...>(rec);
        }

        template<int... Fs >
        friend std::vector<result_type> select(std::vector < record<TDescriptor, Fs...> > const & recs, select_query const & q) {
            std::vector<result_type> ret;
            for (record<TDescriptor, Fs...> const & cur : recs) {
                ret.push_back(impl::select_query_impl < record<TDescriptor, Fs...> >::template select < Cs...>(cur));
            }
            return ret;
        }

        friend std::string to_string(select_query const & q) {
            return impl::select_query_impl<result_type>::build_select_query();
        }
    };

    template<typename TDescriptor, int... Cs, int I>
    inline auto operator+(select_query<TDescriptor, Cs...> const & q, field<TDescriptor, I>) -> decltype(combine(q, select_query<TDescriptor, I>())) {
        return combine(q, select_query<TDescriptor, I > ());
    }

    template<typename TDescriptor, int... Cl, int... Cr>
    inline auto operator&(select_query<TDescriptor, Cl...> const & l, select_query<TDescriptor, Cr...> const & r) -> decltype(combine(l, r)) {
        return combine(l, r);
    }

    template<typename TDescriptor, int... Cl, int... Cr>
    inline auto operator|(select_query<TDescriptor, Cl...> const & l, select_query<TDescriptor, Cr...> const & r) -> decltype(combine_unique(l, r)) {
        return combine_unique(l, r);
    }
}

#endif