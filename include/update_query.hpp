/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UPDATE_QUERY_HPP
#define _UPDATE_QUERY_HPP

#include "impl/update_query_impl.hpp"

#include "call_with.hpp"
#include "is_query.hpp"
#include "record.hpp"
#include "type_traits.hpp"      // for fp::enable_if, fp::enable_if_c

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string
#include <tuple>                // for std::tuple, std::tie

namespace fp {
    
    template<typename...>
    struct update_query;

    template<typename... TUpdate>
    struct is_update_query<update_query<TUpdate...>> : mpl::all_<impl::is_update_modifier<TUpdate>...> { };

    template<typename... TUpdate>
    struct is_query<update_query<TUpdate...>> : is_update_query<update_query<TUpdate...>> { };

    template<typename... TUpdate>
    struct update_query {
    public:
        template<typename TRecord>
        struct result_of : mpl::identity<std::size_t> { };

    public:
        constexpr update_query(TUpdate... updates)
        : updates_(updates...)
        { }

    public:
        friend void swap(update_query& l, update_query& r) noexcept {
            using std::swap;
            swap(l.updates_, r.updates_);
        }

        template<
            typename TRecord,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend TRecord& update(TRecord& rec, const update_query& q) {
            impl::update_applier<TUpdate...> eval = call_constructor<impl::update_applier<TUpdate...>>(q.updates_);
            eval(rec);
            return rec;
        }

        template<
            typename TContainer,
            typename TRecord = typename TContainer::value_type,
            typename = mpl::enable_if_t<is_record<TRecord>>
        >
        friend TContainer update(TContainer cont, const update_query& q) {
            for(TRecord& cur : cont) {
                update(cur, q);
            }
            return cont;
        }

        friend std::string to_string(const update_query& q) {
            std::string(*build_fn)(TUpdate...) = &impl::update_query_impl::build_update_query<TUpdate...>;
            return call_function(build_fn, q.updates_);
        }

    private:
        std::tuple<TUpdate...> updates_;
    };
    
    template<typename... TUpdate>
    constexpr inline update_query<Unqualified<TUpdate>...> update(TUpdate... u) {
        return { u... };
    }

    template<
        typename TLeft,
        typename TRight,
        typename = mpl::enable_if_t<is_column<TLeft>>
    >
    constexpr inline impl::update_modifiers::modifier<
                        TLeft,
                        mpl::conditional_t<
                            is_column<TRight>,
                            mpl::identity<impl::update_modifiers::column_getter<TRight>>,
                            mpl::identity<impl::update_modifiers::value_getter<TLeft>>
                        >
    > set(TLeft l, TRight r) {
        using getter_type = mpl::conditional_t<
                                is_column<TRight>,
                                mpl::identity<impl::update_modifiers::column_getter<TRight>>,
                                mpl::identity<impl::update_modifiers::value_getter<TLeft>>
                            >;
        return impl::update_modifiers::modifier<TLeft, getter_type>{ l, getter_type(l, r) };
    }

#define DECLARE_BIN_OP_UPDATE(name, suffix) \
    template< \
        typename TLeft, \
        typename TRight, \
        typename = mpl::enable_if_t<is_column<TLeft>> \
    > \
    constexpr inline impl::update_modifiers::modifier< \
                        TLeft, \
                        mpl::conditional_t< \
                            is_column<TRight>, \
                            mpl::identity<impl::update_modifiers::column ## suffix <TLeft, TRight>>, \
                            mpl::identity<impl::update_modifiers::value ## suffix <TLeft>> \
                        > \
    > name (TLeft l, TRight r) { \
        using getter_type = mpl::conditional_t< \
                                is_column<TRight>, \
                                mpl::identity<impl::update_modifiers::column ## suffix <TLeft, TRight>>, \
                                mpl::identity<impl::update_modifiers::value ## suffix <TLeft>> \
                            >; \
        return impl::update_modifiers::modifier<TLeft, getter_type>{ l, getter_type(l, r) }; \
    }
    
    DECLARE_BIN_OP_UPDATE(add, _add)
    DECLARE_BIN_OP_UPDATE(sub, _sub)
    DECLARE_BIN_OP_UPDATE(mul, _mul)
    DECLARE_BIN_OP_UPDATE(div, _div)

#undef DECLARE_BIN_OP_UPDATE
}

#endif