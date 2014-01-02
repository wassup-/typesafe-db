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
        std::tuple<TUpdate...> updates_;
    public:
        update_query() = default;

        update_query(TUpdate... updates)
        : updates_(std::move(updates)...)
        { }

        update_query(const update_query& qry) = default;

        update_query(update_query&& qry) noexcept
        : updates_()
        { swap(*this, qry); }

        friend void swap(update_query& l, update_query& r) noexcept {
            using std::swap;
            swap(l.updates_, r.updates_);
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<Unqualified<TRecord>>> update(TRecord&& rec, const update_query& q) {
            impl::update_applier<TUpdate...> eval = call_constructor<impl::update_applier<TUpdate...>>(q.updates_);
            eval(std::forward<TRecord>(rec));
            return 1;
        }

        template<typename TRecord, EnableIf<is_record<TRecord>> = _>
        friend Invoke<result_of<TRecord>> update(std::vector<TRecord>& recs, const update_query& q) {
            Invoke<result_of<TRecord>> ret = 0;
            for (TRecord& cur : recs) {
                ret += update(cur, q);
            }
            return ret;
        }

        friend std::string to_string(const update_query& q) {
            std::string(*build_fn)(TUpdate...) = &impl::update_query_impl::build_update_query<TUpdate...>;
            return call_function(build_fn, q.updates_);
        }
        
        template<typename T, EnableIf<impl::is_update_modifier<T>> = _>
        friend update_query<TUpdate..., T> operator+(const update_query& q, T c) {
            return call_constructor<update_query<TUpdate..., T>>(std::tuple_cat(q.updates_, std::tuple<T>(c)));
        }
    };
    
    template<typename... TUpdate>
    CONSTEXPR inline update_query<Unqualified<TUpdate>...> update(TUpdate&&... u) {
        return { std::forward<TUpdate>(u)... };
    }
    
    template<typename TField>
    inline impl::update_modifiers::modifier<TField, impl::update_modifiers::value_getter<TField>> operator^(TField, Invoke<TField> v) {
        using getter_type = impl::update_modifiers::value_getter<TField>;
        return impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_getter<TRight>> operator^(TLeft, TRight) {
        using getter_type = impl::update_modifiers::field_getter<TRight>;
        return impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_getter<TField>> set(TField, Invoke<TField> v) {
        using getter_type = fp::impl::update_modifiers::value_getter<TField>;
        return fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_getter<TRight>> set(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_getter<TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_add<TField>> add(TField f, Invoke<TField> v) {
        using getter_type = fp::impl::update_modifiers::value_add<TField>;
        fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_add<TLeft, TRight>> add(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_add<TLeft, TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_sub<TField>> sub(TField f, Invoke<TField> v) {
        using getter_type = fp::impl::update_modifiers::value_sub<TField>;
        fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_sub<TLeft, TRight>> sub(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_sub<TLeft, TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_mul<TField>> mul(TField f, Invoke<TField> v) {
        using getter_type = fp::impl::update_modifiers::value_mul<TField>;
        fp::impl::update_modifiers::modifier<TField, getter_type>(getter_type(v));
    }
    
    template<typename TLeft, typename TRight, EnableIf<is_field<TLeft>, is_field<TRight>> = _>
    inline impl::update_modifiers::modifier<TLeft, impl::update_modifiers::field_mul<TLeft, TRight>> mul(TLeft, TRight) {
        using getter_type = fp::impl::update_modifiers::field_mul<TLeft, TRight>;
        return fp::impl::update_modifiers::modifier<TLeft, getter_type>(getter_type());
    }
    
    template<typename TField>
    inline fp::impl::update_modifiers::modifier<TField, fp::impl::update_modifiers::value_div<TField>> div(TField f, Invoke<TField> v) {
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