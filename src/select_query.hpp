/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SELECT_QUERY_HPP
#define _SELECT_QUERY_HPP

#include "impl/select_query_impl.hpp"

#include "field.hpp"
#include "is_query.hpp"
#include "query_combiner.hpp"
#include "record.hpp"

#include <string>       // for std::string, std::to_string
#include <vector>       // for std::vector

namespace fp {
    template<typename...>
    struct select_query;

    template<typename... TFields>
    struct is_query<select_query<TFields...> > : All<is_field<TFields>..., is_same<DescriptorOf<TFields>...>> { };
    
    template<typename... TFields>
    struct is_select_query<select_query<TFields...> > : Bool<true> { };

    template<typename... TFields> struct select_query {
    public:
        template<typename TRecord>
        struct result_of {
            using type = Invoke<typename TRecord::template rebind<TFields...>>;
        };
    public:

        friend void swap(select_query & l, select_query & r) noexcept {
            using std::swap;
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<TRecord>> select(TRecord const & rec, select_query const & q) {
            return typename result_of<TRecord>::type(get<TFields>(rec)...);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> select(std::vector<TRecord> const & recs, select_query const & q) {
            std::vector<typename result_of<TRecord>::type> ret;
            for (TRecord const & cur : recs) {
                ret.push_back(select(cur, q));
            }
            return ret;
        }
        
        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> query(std::vector<TRecord> const & recs, select_query const & q) {
            return select(recs, q);
        }

        friend std::string to_string(select_query const & q) {
             return impl::select_query_impl<TFields...>::build_select_query();
        }
    };
    
    template<typename... TFields, EnableIf<is_field<TFields>...> = _>
    inline select_query<TFields...> select(TFields...) {
        return select_query<TFields...>();
    }

    template<typename... LFields, typename... RFields, EnableIf<is_field<LFields>..., is_field<RFields>...> = _>
    inline auto operator&(select_query<LFields...> const & l, select_query<RFields...> const & r) -> decltype(combine(l, r)) {
        return combine(l, r);
    }

    template<typename... LFields, typename... RFields, EnableIf<is_field<LFields>..., is_field<RFields>...> = _>
    inline auto operator|(select_query<LFields...> const & l, select_query<RFields...> const & r) -> decltype(combine_unique(l, r)) {
        return combine_unique(l, r);
    }
}

#endif