/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _RECORD_HPP
#define _RECORD_HPP

#include "field.hpp"
#include "int_sequence.hpp"
#include "nth_type_of.hpp"
#include "type_sequence.hpp"

#include <cstddef>      // for int
#include <string>       // for std::string
#include <tuple>        // for std::tuple, std::tuple_cat, std::get

namespace fp {
    template<typename, int...> struct record;
    
    template<typename> struct is_record {
        
        enum {
            value = false
        };
    };
    
    template<typename TDescriptor, int... Fields> struct is_record<record<TDescriptor, Fields...> > {
        
        enum {
            value = true
        };
    };
    
    template<typename TDescriptor, int... Fields> struct record {
    public:
        typedef type_seq<typename TDescriptor::template field<Fields>::type...> types;
        static int const SIZE = sizeof...(Fields);
    protected:
        std::tuple<typename TDescriptor::template field<Fields>::type...> m_values;
    public:

        record() : m_values() {
        }

        record(typename TDescriptor::template field<Fields>::type && ... ts) : m_values(std::forward<typename TDescriptor::template field<Fields>::type > (ts)...) {
        }

        record(record const & rec) : m_values(rec.m_values) {
        }

        int size() const {
            return SIZE;
        }

        template<int I>
        typename TDescriptor::template field<I>::type & get() {
            return std::get < index_of<I, Fields...>::value > (m_values);
        }

        template<int I>
        typename TDescriptor::template field<I>::type const & get() const {
            return std::get < index_of<I, Fields...>::value > (m_values);
        }
    };

    template<int I, typename TDescriptor, int... Fs>
    inline auto get(record<TDescriptor, Fs...> & r) -> decltype(r.template get<I>()) {
        return r.template get<I > ();
    }

    template<int I, typename TDescriptor, int... Fs>
    inline auto get(record<TDescriptor, Fs...> const & r) -> decltype(r.template get<I>()) {
        return r.template get<I > ();
    }

    template<typename F, typename TDescriptor, int... Fs>
    inline auto get(record<TDescriptor, Fs...> & r) -> decltype(r.template get<F::index>()) {
        return r.template get<F::index > ();
    }

    template<typename F, typename TDescriptor, int... Fs>
    inline auto get(record<TDescriptor, Fs...> const & r) -> decltype(r.template get<F::index>()) {
        return r.template get<F::index > ();
    }

    template<typename TDescriptor, int I, int... Fs>
    inline auto get(record<TDescriptor, Fs...> & r, field<TDescriptor, I>) -> decltype(r.template get<I>()) {
        return r.template get<I > ();
    }

    template<typename TDescriptor, int I, int... Fs>
    inline auto get(record<TDescriptor, Fs...> const & r, field<TDescriptor, I>) -> decltype(r.template get<I>()) {
        return r.template get<I > ();
    }
}

#endif