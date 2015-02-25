/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_SELECT_QUERY_HPP
#define _WHERE_SELECT_QUERY_HPP

#include "forward.hpp"
#include "is_query.hpp"
#include "select_query.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate
#include "where_query.hpp"

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string

namespace fp {

    template<typename /* TSelect */, typename /* TWhere */>
    struct where_select_query;

    template<typename TSelect, typename TWhere>
    struct is_select_query<where_select_query<TSelect, TWhere> >
    : is_select_query<TSelect>
    { };

    template<typename TSelect, typename TWhere>
    struct is_where_query<where_select_query<TSelect, TWhere> >
    : is_where_query<TWhere>
    { };

    template<typename TSelect, typename TWhere>
    struct is_query<where_select_query<TSelect, TWhere> >
    : mpl::all_<is_select_query<TSelect>, is_where_query<TWhere> >
    { };

    template<typename TSelect, typename TWhere>
    struct where_select_query
    {
    public:
        template<typename TRecord>
        using result_of = typename TSelect::template result_of<TRecord>;

    protected:
        TSelect _select;
        TWhere _where;

    public:
        constexpr where_select_query(TSelect s, TWhere w)
        : _select(s)
        , _where(w)
        { }

        friend void swap(where_select_query& l, where_select_query& r) noexcept
        {
            using std::swap;
            swap(l._select, r._select);
            swap(l._where, r._where);
        }

        template<
            typename TRecord,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend bool evaluate(const TRecord& rec, const where_select_query& self)
        {
            return evaluate(rec, self._where);
        }

        template<
            typename TRecord,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend result_of<Unqualified<TRecord> > select(const TRecord& rec, const where_select_query& self)
        {
            return select(rec, self._select);
        }

        template<
            typename TContainer,
            typename TRecord = typename TContainer::value_type,
            typename = mpl::enable_if_t<is_record<TRecord> >
        >
        friend typename TContainer::template rebind<result_of<TRecord> >::type query(const TContainer& recs, const where_select_query& self)
        {
            using TReturnContainer = typename TContainer::template rebind<result_of<TRecord> >::type;

            TReturnContainer ret;
            for(const TRecord& cur : recs) {
                if (evaluate(cur, self._where)) {
                    ret.push_back(select(cur, self._select));
                }
            }
            return ret;
        }

        template<typename Formatter>
        friend std::string to_string(const where_select_query& self, Formatter& formatter)
        {
            return stringutils::concatenate(formatter.to_string(self._select), " ", formatter.to_string(self._where));
        }
    };

    template<
        typename TSelect,
        typename TWhere,
        typename = mpl::enable_if_t<mpl::all_<is_select_query<TSelect>, is_where_query<TWhere> > >
    >
    constexpr inline where_select_query<TSelect, TWhere> operator+(TSelect s, TWhere w)
    {
        return { s, w };
    }
}

#endif
