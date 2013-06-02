/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UPDATE_QUERY_HPP
#define _UPDATE_QUERY_HPP

#include "impl/update_query_impl.hpp"

#include "call_with.hpp"
#include "is_query.hpp"
#include "tuple_cat.hpp"
#include "type_traits.hpp"      // for fp::enable_if, fp::enable_if_c

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string
#include <vector>               // for std::vector

namespace fp {
    template<typename...>
    struct update_query;

    template<typename... TUpdate>
    struct is_query<update_query<TUpdate...> > : All<All<impl::is_update_modifier<TUpdate>...>, is_same<DescriptorOf<TUpdate>...>> { };
    
    template<typename... TUpdate>
    struct is_update_query<update_query<TUpdate...> > : Bool<true> { };
    
    template<typename... TUpdate>
    struct update_query {
        
        template<typename TRecord>
        struct result_of {
            using type = unsigned long long;
        };
    protected:
        std::tuple<TUpdate...> _updates;
    public:
        update_query()
        : _updates() {
        }

        update_query(TUpdate... updates)
        : _updates(std::move(updates)...) {
        }

        update_query(update_query const & qry)
        : _updates(qry._updates) {
        }

        update_query(update_query && qry) noexcept
        : _updates() {
            swap(*this, qry);
        }

        friend void swap(update_query & l, update_query & r) noexcept {
            using std::swap;
            swap(l._updates, r._updates);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<TRecord>> update(TRecord & rec, update_query const & q) {
            impl::update_applier<TUpdate...> eval = call_constructor<impl::update_applier<TUpdate...>>(q._updates);
            eval(rec);
            return 1;
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<TRecord>> update(std::vector<TRecord> & recs, update_query const & q) {
            Invoke<result_of<TRecord>> ret = 0;
            for (TRecord & cur : recs) {
                ret += update(cur, q);
            }
            return ret;
        }

        friend std::string to_string(update_query const & q) {
            std::string(*build_fn)(TUpdate...) = &impl::update_query_impl::build_update_query<TUpdate...>;
            return call_function(build_fn, q._updates);
        }
        
        template<typename T, EnableIf<impl::is_update_modifier<T>> = _>
        friend update_query<TUpdate..., T> operator+(update_query const & q, T c) {
            return call_constructor<update_query<TUpdate..., T>>(std::tuple_cat(q._updates, std::tuple<T>(c)));
        }
    };
    
    template<typename... TUpdate>
    update_query<TUpdate...> update(TUpdate... u) {
        return update_query<TUpdate...>(std::move(u)...);
    }
    
    template<typename TField>
    inline impl::update_modifiers::modifier<TField, impl::update_modifiers::value_getter<TField>> operator^(TField, typename TField::type v) {
        using getter_type = impl::update_modifiers::value_getter<TField>;
        return impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_getter<TRight>> operator^(TLeft, TRight) {
        using getter_type = impl::update_modifiers::field_getter<TRight>;
        return impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_getter<TField>> set(TField, typename TField::type v) {
        using getter_type = fp::impl::update_modifiers::value_getter<TField>;
        return fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_getter<TRight>> set(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_getter<TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_add<TField>> add(TField f, typename TField::type v) {
        using getter_type = fp::impl::update_modifiers::value_add<TField>;
        fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_add<TLeft, TRight>> add(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_add<TLeft, TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_sub<TField>> sub(TField f, typename TField::type v) {
        using getter_type = fp::impl::update_modifiers::value_sub<TField>;
        fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_sub<TLeft, TRight>> sub(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_sub<TLeft, TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_mul<TField>> mul(TField f, typename TField::type v) {
        using getter_type = fp::impl::update_modifiers::value_mul<TField>;
        fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_mul<TLeft, TRight>> mul(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_mul<TLeft, TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_div<TField>> div(TField f, typename TField::type v) {
        using getter_type = fp::impl::update_modifiers::value_div<TField>;
        fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_div<TLeft, TRight>> div(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_div<TLeft, TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
}

#endif