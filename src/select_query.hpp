/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SELECT_QUERY_HPP
#define _SELECT_QUERY_HPP

#include "impl/select_query_impl.hpp"

#include "is_query.hpp"
#include "query_combiner.hpp"
#include "record.hpp"
#include "query_builder.hpp"

#include <vector>

namespace fp {
    template<typename, int...> struct select_query;
    
    template<typename TDescriptor, int... Is> struct is_query<select_query<TDescriptor, Is...> > {
        enum { value = true };
    };

    template<typename TDescriptor, int... Cs> struct select_query {
    public:
        typedef TDescriptor descriptor_type;
        typedef typename impl::query_impl<typename TDescriptor::record::type>::template result_of < Cs...>::type result_type;
    public:
        template<int... Fs>
        result_type apply(record<TDescriptor, Fs...> const & r) const {
            return impl::query_impl<record<TDescriptor, Fs...> >::template select < Cs...>(r);
        }

        template<int... Fs>
        std::vector<result_type> apply(std::vector<record<TDescriptor, Fs...> > const & r) const {
            std::vector<result_type> ret;
            for(auto const & cur : r) {
                ret.push_back(impl::query_impl<record<TDescriptor, Fs...> >::template select < Cs...>(cur));
            }
            return ret;
        }

        std::string to_string() const {
            query_builder qb;
            return qb.template build_select_query <TDescriptor, Cs...>();
        }
    };

    template<typename TDescriptor, int... Cs, int I>
    inline auto operator+(select_query<TDescriptor, Cs...> const & q, field<TDescriptor, I>) -> decltype(combine(q, select_query<TDescriptor, I>())) {
        return combine(q, select_query<TDescriptor, I>());
    }

    template<typename TDescriptor, int... Cl, int... Cr>
    inline auto operator&(select_query<TDescriptor, Cl...> const & l, select_query<TDescriptor, Cr...> const & r) -> decltype(combine(l, r)) {
        return combine(l, r);
    }

    template<typename TDescriptor, int... Cl, int... Cr>
    inline auto operator|(select_query<TDescriptor, Cl...> const & l, select_query<TDescriptor, Cr...> const & r) -> decltype(combine_unique(l, r)) {
        return combine_unique(l, r);
    }

    template<typename TDescriptor, int... Cs, int... Fs>
    inline auto select(record<TDescriptor, Fs...> const & rec, select_query<TDescriptor, Cs...> const & qry) -> decltype(qry.apply(rec)) {
        return qry.apply(rec);
    }

    template<typename TDescriptor, int... Cs, int... Fs>
    inline auto select(std::vector<record<TDescriptor, Fs...> > const & recs, select_query<TDescriptor, Cs...> const & qry) -> decltype(qry.apply(recs)) {
        return qry.apply(recs);
    }
}

#endif