/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_QUERY_HPP
#define _WHERE_QUERY_HPP

#include "impl/where_query_impl.hpp"

#include "call_with.hpp"
#include "erase.hpp"
#include "is_query.hpp"
#include "not_implemented_exception.hpp"
#include "record.hpp"
#include "type_traits.hpp"      // for fp::EnableIf
#include "where_clauses.hpp"

#include <algorithm>            // for std::swap
#include <functional>           // for std::bind
#include <string>               // for std::string, std::to_string

namespace fp {

    template<typename... /* Where */>
    struct where_query;

    template<typename... TWhere>
    struct is_where_query<where_query<TWhere...>> : mpl::all_<impl::is_where_clause<TWhere>...> { };

    template<typename... TWhere>
    struct is_query<where_query<TWhere...>> : is_where_query<where_query<TWhere...>> { };

    template<typename... TWhere>
    struct where_query
    {
    public:
        using descriptor_type = FirstTypeOf<DescriptorOf<TWhere>...>;

    public:
        constexpr where_query(TWhere... clauses)
        : clauses_(clauses...)
        { }

        friend void swap(where_query& l, where_query& r) noexcept {
            using std::swap;
            swap(l.clauses_, r.clauses_);
        }

        template<typename TRecord>
        bool evaluate(const TRecord& rec) const {
            bool(*eval_fn)(const TRecord&, const TWhere&...) = &impl::where_query_impl::evaluate;
            return call_function(eval_fn, clauses_, rec);
        }

        template<
            typename TRecord,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend bool evaluate(const TRecord& rec, const where_query& q) {
            return q.evaluate(rec);
        }

        template<
            typename TContainer,
            typename TRecord = typename TContainer::value_type,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend TContainer evaluate(TContainer cont, const where_query& q) {
            erase_if(cont, std::bind(&where_query::evaluate, std::cref(q), std::placeholders::_1, std::cref(q)));//[&](const TRecord& cur) { return evaluate(cur, q); });
            return cont;
        }

        template<
            typename TContainer,
            typename TRecord = typename TContainer::value_type,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend TContainer query(const TContainer& rec, const where_query& q) {
            //return evaluate(rec, q);
            throw not_implemented_exception("Not implemented yet");
        }

        friend std::string to_string(const where_query& q) {
            std::string(*build_fn)(TWhere...) = &impl::where_query_impl::build_where_query<TWhere...>;
            return call_function(build_fn, q.clauses_);
        }
    private:
        std::tuple<TWhere...> clauses_;
    };

    template<typename... TCondition>
    constexpr inline where_query<TCondition...> where(TCondition... c) {
        return { c... };
    }
}

#endif
