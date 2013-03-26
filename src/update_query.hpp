/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UPDATE_QUERY_HPP
#define _UPDATE_QUERY_HPP

#include "impl/update_query_impl.hpp"

#include "apply_tuple.hpp"
#include "is_query.hpp"
#include "tuple_cat.hpp"

#include <algorithm>            // for std::swap
#include <cstddef>              // for int
#include <string>               // for std::string
#include <type_traits>          // for std::enable_if
#include <vector>               // for std::vector

namespace fp {
    template<typename, typename...> struct update_query;

    template<typename TDescriptor, typename... TModifiers> struct is_query<update_query<TDescriptor, TModifiers...> > {

        enum {
            value = true
        };
    };
    
    template<typename TDescriptor> struct update_query<TDescriptor> {
        typedef TDescriptor descriptor_type;
        typedef unsigned long long result_type;
        
        template<typename TModifier>
        friend update_query<TDescriptor, TModifier> operator+(update_query<TDescriptor> const & q, TModifier c) {
            return update_query<TDescriptor, TModifier>(c);
        }
    };

    template<typename TDescriptor, typename... TModifiers> struct update_query {
        typedef TDescriptor descriptor_type;
        typedef unsigned long long result_type;
    protected:
        std::tuple < TModifiers...> m_modifiers;
    public:
        update_query() : m_modifiers() {
        }

        update_query(TModifiers... modifiers) : m_modifiers(modifiers...) {
        }

        update_query(update_query const & wc) : m_modifiers(wc.m_modifiers) {
        }

        update_query(update_query && wc) : m_modifiers() {
            swap(*this, wc);
        }

        friend void swap(update_query & l, update_query & r) {
            using std::swap;
            swap(l.m_modifiers, r.m_modifiers);
        }

        template<int... Fs>
        friend result_type update(record<TDescriptor, Fs...> & rec, update_query const & q) {
            impl::update_applier<TModifiers...> eval = call_constructor<impl::update_applier<TModifiers...> >(q.m_modifiers);
            eval(rec);
            return 1;
        }

        template<int... Fs >
        friend result_type update(std::vector < record<TDescriptor, Fs...> > & recs, update_query const & q) {
            result_type ret = 0;
            for (record<TDescriptor, Fs...> & cur : recs) {
                ret += update(cur, q);
            }
            return ret;
        }

        friend std::string to_string(update_query const & q) {
            auto wrapper = wrap_fn(&impl::update_query_impl::build_update_query<TDescriptor, TModifiers...>);
            return call_function(wrapper, q.m_modifiers);
        }
        
        template<typename TModifier>
        friend typename std::enable_if<impl::is_update_modifier<TModifier>::value, update_query<TDescriptor, TModifiers..., TModifier> >::type operator+(update_query<TDescriptor, TModifiers...> const & q, TModifier c) {
            return call_constructor<update_query<TDescriptor, TModifiers..., TModifier> >(std::tuple_cat(q.m_modifiers, std::tuple<TModifier>(c)));
        }
    };
    
    template<typename TDescriptor, int I, typename TValue>
    inline impl::update_modifiers::modifier<TDescriptor, I, impl::update_modifiers::value_getter<TDescriptor, TValue> > operator^(field<TDescriptor, I>, TValue && v) {
        typedef impl::update_modifiers::value_getter<TDescriptor, TValue> getter_type;
        return impl::update_modifiers::modifier<TDescriptor, I, getter_type>(getter_type(std::forward<TValue>(v)));
    }
    
    template<typename TDescriptor, int I, int F>
    inline impl::update_modifiers::modifier<TDescriptor, I, impl::update_modifiers::field_getter<TDescriptor, F> > operator^(field<TDescriptor, I>, field<TDescriptor, F>) {
        typedef impl::update_modifiers::field_getter<TDescriptor, F> getter_type;
        return impl::update_modifiers::modifier<TDescriptor, I, getter_type>(getter_type());
    }
}

#endif