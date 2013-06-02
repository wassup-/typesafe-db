/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _ORDERED_QUERY_HPP
#define _ORDERED_QUERY_HPP

#include "impl/ordered_query_impl.hpp"

#include "is_query.hpp"
#include "record.hpp"
#include "type_traits.hpp"      // for EnableIf

#include <algorithm>            // for std::swap, std::sort
#include <string>               // for std::string, std::to_string
#include <utility>              // for std::forward

namespace fp {
    template<typename, typename>
    struct ordered_query;

    template<typename TQuery, typename TField>
    struct is_query<ordered_query<TQuery, TField> > : All<is_query<TQuery>, is_field<TField>> { };

    template<typename TQuery, typename TField>
    struct is_ordered_query<ordered_query<TQuery, TField> > : Bool<true> { };

    enum ordering_e {
        ascending = 0,
        descending = 1
    };

    template<typename TQuery, typename TField>
    struct ordered_query {
    public:
        template<typename TRecord>
        struct result_of {
            using type = Invoke<typename TQuery::template result_of<TRecord>>;
        };
    protected:
        TQuery _query;
        ordering_e _order;
    public:

        ordered_query() : _query() {
        }

        ordered_query(TQuery q, ordering_e o) : _query(std::move(q)), _order(o) {
        }

        ordered_query(ordered_query const &) = default;

        ordered_query(ordered_query && q) noexcept : _query(), _order(ascending) {
            swap(*this, q);
        }

        friend void swap(ordered_query & l, ordered_query & r) noexcept {
            using std::swap;
            swap(l._query, r._query);
            swap(l._order, r._order);
        }

        friend std::string to_string(ordered_query const & q) {
            using std::to_string;
            std::string ordering;
            if (Not<is_ordered_query<TQuery>>::value) {
                ordering = " ORDER BY " + to_string(TField()) + " " + impl::ordered_query_impl::ORDERINGS[q._order];
            } else {
                ordering = ", " + to_string(TField()) + " " + impl::ordered_query_impl::ORDERINGS[q._order];
            }
            return to_string(q._query) + ordering;
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend std::vector<Invoke<result_of<TRecord>>> query(std::vector<TRecord> const & recs, ordered_query const & q) {
            std::vector<Invoke<result_of<TRecord>>> ret = query(recs, q._query);
            switch(q._order){
                case ascending:
                    std::sort(ret.begin(), ret.end(), impl::ordered_query_impl::ascending_sorter<Invoke<result_of<TRecord>>, TField > ());
                    break;
                case descending:
                    std::sort(ret.begin(), ret.end(), impl::ordered_query_impl::descending_sorter<Invoke<result_of<TRecord>>, TField > ());
                    break;
            }
            return ret;
        }
    };

    /**
     * Applies absolute ordering to the result query
     * @param q query to apply absolute ordering to
     * @param f field on which to apply absolute ordering
     * @return ordered_query<TQuery, TField>
     */
    template<typename TQuery, typename TField, EnableIf<is_query<TQuery>, is_field<TField>> = _>
    inline ordered_query<TQuery, TField> order(TQuery q, TField, ordering_e o = ascending) {
        return ordered_query<TQuery, TField>(std::move(q), o);
    }
}

#endif