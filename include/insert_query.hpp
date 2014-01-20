/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _INSERT_QUERY_HPP
#define _INSERT_QUERY_HPP

#include "field.hpp"
#include "is_query.hpp"
#include "record.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate
#include "type_traits.hpp"

#include <stdexcept>
#include <string>               // for std::string, std::to_string

namespace fp {
    
    template<typename...>
    struct insert_query;

    template<typename... TColumns>
    struct is_query<insert_query<TColumns...> > : mpl::all_<is_column<TColumns>...> { };

    template<typename... TColumns>
    struct is_insert_query<insert_query<TColumns...> > : mpl::true_ { };

    template<typename... TColumns>
    struct insert_query {
    public:
        
        template<typename TRecord>
        struct result_of : mpl::identity<Invoke<typename TRecord::template rebind<TColumns...>>> { };
    public:

        friend void swap(insert_query& l, insert_query& r) noexcept {
            using std::swap;
        }

        template<
            typename TContainer,
            typename TRecord = typename TContainer::value_type,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend typename TContainer::template rebind<Invoke<result_of<TRecord>>>::type insert(TContainer& recs, const insert_query& q) {
            using TReturnContainer = typename TContainer::template rebind<Invoke<result_of<TRecord>>>::type;
            TReturnContainer ret;
            ret.reserve(recs.size());
            for(const TRecord& cur : recs) {
                ret.push_back({ fp::get(cur, TColumns())... });
            }
            return ret;
        }

        template<
            typename TContainer,
            typename TRecord = typename TContainer::value_type,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend typename TContainer::template rebind<Invoke<result_of<TRecord>>>::type query(TContainer& recs, const insert_query& q) {
            return insert(recs, q);
        }

        friend std::string to_string(const insert_query& q) {
            //return impl::insert_query_impl<TColumns...>::build_insert_query();
            throw std::runtime_error("Not implemented yet");
        }
    };

    template<
        typename... TColumns,
        typename = mpl::enable_if_t<mpl::all_<is_column<TColumns>...>>
    >
    insert_query<TColumns...> insert(TColumns... c) {
        return { c... };
    }
}

#endif