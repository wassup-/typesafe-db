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

    template<typename... TFields>
    struct select_query {
    public:
        
        template<typename TRecord>
        struct result_of {
            using type = Invoke<typename TRecord::template rebind<TFields...>>;
        };
    public:

        friend void swap(select_query& l, select_query& r) noexcept {
            using std::swap;
        }

        template<typename TRecord, EnableIf<is_record<Unqualified<TRecord>>> = _>
        friend Invoke<result_of<Unqualified<TRecord>>> select(TRecord&& rec, const select_query& q) {
            return { std::get<TFields>(std::forward<TRecord>(rec))... };
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> select(const std::vector<TRecord>& recs, const select_query& q) {
            std::vector<Invoke<result_of<TRecord>>> ret;
            for (const TRecord& cur : recs) {
                ret.push_back(select(cur, q));
            }
            return ret;
        }
        
        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> query(const std::vector<TRecord>& recs, const select_query& q) {
            return select(recs, q);
        }

        friend std::string to_string(const select_query& q) {
             return impl::select_query_impl<TFields...>::build_select_query();
        }
    };
    
    template<typename... TFields, EnableIf<is_field<Unqualified<TFields>>...> = _>
    CONSTEXPR inline select_query<Unqualified<TFields>...> select(TFields&&...) {
        return { };
    }

    template<typename LeftSelect, typename RightSelect, EnableIf<is_select_query<LeftSelect>, is_select_query<RightSelect>> = _>
    CONSTEXPR inline auto operator&(LeftSelect&& l, RightSelect&& r) -> decltype(combine(std::forward<LeftSelect>(l), std::forward<RightSelect>(r))) {
        return combine(std::forward<LeftSelect>(l), std::forward<RightSelect>(r));
    }

    template<typename LeftSelect, typename RightSelect, EnableIf<is_select_query<LeftSelect>, is_select_query<RightSelect>> = _>
    CONSTEXPR inline auto operator|(LeftSelect&& l, RightSelect&& r) -> decltype(combine_unique(std::forward<LeftSelect>(l), std::forward<RightSelect>(r))) {
        return combine_unique(std::forward<LeftSelect>(l), std::forward<RightSelect>(r));
    }
}

#endif