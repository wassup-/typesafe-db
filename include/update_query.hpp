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
    struct is_update_query<update_query<TUpdate...>> : All<impl::is_update_modifier<TUpdate>...> { };

    template<typename... TUpdate>
    struct is_query<update_query<TUpdate...>> : is_update_query<update_query<TUpdate...>> { };

    template<typename... TUpdate>
    struct update_query {
    public:
        template<typename TRecord>
        struct result_of : identity<std::size_t> { };

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
            EnableIf<
                is_record<TRecord>
            > = _
        >
        friend TRecord& update(TRecord& rec, const update_query& q) {
            impl::update_applier<TUpdate...> eval = call_constructor<impl::update_applier<TUpdate...>>(q.updates_);
            eval(rec);
            return rec;
        }

        template<
            typename TContainer,
            typename TRecord = typename TContainer::value_type,
            EnableIf<
                is_record<TRecord>
            > = _
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
  
    template<typename TColumn>
    constexpr inline impl::update_modifiers::modifier<TColumn, impl::update_modifiers::value_getter<TColumn>> set(TColumn c, typename TColumn::value_type v) {
        using getter_type = impl::update_modifiers::value_getter<TColumn>;
        return impl::update_modifiers::modifier<TColumn, getter_type>{ c, getter_type{ c, v} };
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_column<TLeft>, is_column<TRight>> = _>
    constexpr inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_getter<TRight>> set(TLeft l, TRight r) {
        using getter_type = impl::update_modifiers::field_getter<TRight>;
        return impl::update_modifiers::modifier<TLeft, getter_type>{ l, getter_type{ l, r } };
    }
    
    template<typename TColumn>
    constexpr inline impl::update_modifiers::modifier<TColumn, impl::update_modifiers::value_add<TColumn>> add(TColumn c, typename TColumn::value_type v) {
        using getter_type = impl::update_modifiers::value_add<TColumn>;
        return impl::update_modifiers::modifier<TColumn, getter_type>{ c, getter_type{ c, v} };
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_column<TLeft>, is_column<TRight>> = _>
    constexpr inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_add<TLeft, TRight>> add(TLeft l, TRight r) {
        using getter_type = impl::update_modifiers::field_add<TLeft, TRight>;
        return impl::update_modifiers::modifier<TLeft, getter_type>{ l, getter_type{ l, r } };
    }
    
    template<typename TColumn>
    constexpr inline impl::update_modifiers::modifier<TColumn, impl::update_modifiers::value_sub<TColumn>> sub(TColumn c, typename TColumn::value_type v) {
        using getter_type = impl::update_modifiers::value_sub<TColumn>;
        return impl::update_modifiers::modifier<TColumn, getter_type>{ c, getter_type{ c, v} };
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_column<TLeft>, is_column<TRight>> = _>
    constexpr inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_sub<TLeft, TRight>> sub(TLeft l, TRight r) {
        using getter_type = impl::update_modifiers::field_sub<TLeft, TRight>;
        return impl::update_modifiers::modifier<TLeft, getter_type>{ l, getter_type{ l, r } };
    }
    
    template<typename TColumn>
    constexpr inline impl::update_modifiers::modifier<TColumn, impl::update_modifiers::value_mul<TColumn>> mul(TColumn c, typename TColumn::value_type v) {
        using getter_type = impl::update_modifiers::value_mul<TColumn>;
        return impl::update_modifiers::modifier<TColumn, getter_type>{ c, getter_type{ c, v} };
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_column<TLeft>, is_column<TRight>> = _>
    constexpr inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_mul<TLeft, TRight>> mul(TLeft l, TRight r) {
        using getter_type = impl::update_modifiers::field_mul<TLeft, TRight>;
        return impl::update_modifiers::modifier<TLeft, getter_type>{ l, getter_type{ l, r } };
    }
    
    template<typename TColumn>
    constexpr inline impl::update_modifiers::modifier<TColumn, impl::update_modifiers::value_div<TColumn>> div(TColumn c, typename TColumn::value_type v) {
        using getter_type = impl::update_modifiers::value_div<TColumn>;
        return impl::update_modifiers::modifier<TColumn, getter_type>{ c, getter_type{ c, v} };
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_column<TLeft>, is_column<TRight>> = _>
    constexpr inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_div<TLeft, TRight>> div(TLeft l, TRight r) {
        using getter_type = impl::update_modifiers::field_div<TLeft, TRight>;
        return impl::update_modifiers::modifier<TLeft, getter_type>{ l, getter_type{ l, r } };
    }
}

#endif