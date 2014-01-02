/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _INSERT_QUERY_HPP
#define _INSERT_QUERY_HPP

#include "impl/insert_query_impl.hpp"

#include "field.hpp"
#include "is_query.hpp"
#include "query_combiner.hpp"
#include "record.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate
#include "type_traits.hpp"

#include <string>               // for std::string, std::to_string
#include <vector>               // for std::vector

namespace fp {
    
    template<typename, typename...>
    struct insert_query;

    template<typename TDescriptor, typename... TFields>
    struct is_query<insert_query<TDescriptor, TFields...> > : All<is_field<TFields>...> { };

    template<typename TDescriptor, typename... TFields>
    struct is_insert_query<insert_query<TDescriptor, TFields...> > : Bool<true> { };

    template<typename TDescriptor, typename... TFields>
    struct insert_query {
    public:
        
        template<typename TRecord>
        struct result_of {
            using type = Invoke<TRecord::rebind<TFields...>>;
        };
    public:

        friend void swap(insert_query& l, insert_query& r) noexcept {
            using std::swap;
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> insert(std::vector<TRecord>& recs, const insert_query& q) {
            std::vector<Invoke<result_of<TRecord>>> ret;
            for(const TRecord& cur : recs) {
                ret.push_back(select(cur, q));
            }
            return ret;
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> query(std::vector<TRecord>& recs, const insert_query& q) {
            return insert(recs, q);
        }

        friend std::string to_string(const select_query& q) {
            return impl::insert_query_impl<TFields...>::build_insert_query();
        }
    };
}

#endif