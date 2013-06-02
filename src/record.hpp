/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _RECORD_HPP
#define _RECORD_HPP

#include "config.hpp"
#include "field.hpp"            // for fp::field
#include "int_sequence.hpp"     // for fp::index_of
#include "type_sequence.hpp"    // for fp::type_seq
#include "type_traits.hpp"      // for fp::enable_if, fp::enable_if_c

#include <string>       // for std::string
#include <tuple>        // for std::tuple, std::tuple_cat, std::get


namespace fp {
    template<typename...>
    struct record;
    
    // This sole purpose of this declaration is to enable ADL
    template<typename> void get() = delete;

    template<typename>
    struct is_record : Bool<false> { };
    
    template<typename... TFields>
    struct is_record<record<TFields...> > : All<is_field<TFields>...> { };
    
    template<>
    struct record<> {
        template<typename... TOther>
        struct rebind {
            using type = record<TOther...>;
        };
    };

    template<typename... TFields>
    struct record {
    public:
        static int const SIZE = sizeof...(TFields);
        
        template<typename... TOther>
        struct rebind {
            using type = record<TOther...>;
        };
        
        template<int Idx>
        struct nth_type {
            using type = NthTypeOf<Idx, Invoke<TFields>...>;
        };
    protected:
        std::tuple<Invoke<TFields>...> _values;
    public:

        record()
        : _values() {
        }

        record(Invoke<TFields>... fs)
        : _values(std::move(fs)...) {
        }

        record(record const & rec)
        : _values(rec._values) {
        }

        record(record && rec) noexcept
        : _values() {
            swap(*this, rec);
        }

        friend void swap(record & l, record & r) {
            using std::swap;
            swap(l._values, r._values);
        }

        int size() const {
            return SIZE;
        }

        template<int I>
        friend NthTypeOf<index_of<I, TFields::index...>::value, Invoke<TFields> &...> get(record & rec) {
            return std::get<index_of<I, TFields::index...>::value>(rec._values);
        }

        template<int I>
        friend NthTypeOf<index_of<I, TFields::index...>::value, Invoke<TFields> const &...> get(record const & rec) {
            return std::get<index_of<I, TFields::index...>::value>(rec._values);
        }

        template<typename TField, EnableIf<is_field<TField>> = _>
        friend Invoke<TField> & get(record & rec) {
            return get<TField::index>(rec);
        }

        template<typename TField, EnableIf<is_field<TField>> = _>
        friend Invoke<TField> const & get(record const & rec) {
            return get<TField::index>(rec);
        }
    };
}

#endif