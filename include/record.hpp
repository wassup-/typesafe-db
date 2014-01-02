/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _RECORD_HPP
#define _RECORD_HPP

#include "config.hpp"
#include "field.hpp"            // for fp::field
#include "type_traits.hpp"      // for fp::EnableIf, fp::DisableIf

#include <tuple>        // for std::tuple, std::get


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
        
        template<typename... TOther>
        struct rebind {
            using type = record<TOther...>;
        };
        
        template<std::size_t Idx>
        struct nth_type {
            using type = NthTypeOf<Idx, Invoke<TFields>...>;
        };
    protected:
        std::tuple<Invoke<TFields>...> _values;
    public:

        CONSTEXPR record() = default;

        record(const record&) = default;

        record(record&& rec) = default;

        CONSTEXPR record(Invoke<TFields>... fs)
        : _values(std::move(fs)...) {
        }

        record& operator=(const record&) = default;
        record& operator=(record&&) = default;

        friend void swap(record& l, record& r) noexcept {
            using std::swap;
            swap(l._values, r._values);
        }

        CONSTEXPR static std::size_t size() {
            return sizeof...(TFields);
        }

        template<std::size_t Idx>
        friend Invoke<nth_type<index_of<Idx, TFields::index...>::value>>& get(record& rec) {
            return std::get<index_of<Idx, TFields::index...>::value>(rec._values);
        }

        template<std::size_t Idx>
        friend const Invoke<nth_type<index_of<Idx, TFields::index...>::value>>& get(const record& rec) {
            return std::get<index_of<Idx, TFields::index...>::value>(rec._values);
        }

        template<typename TField, EnableIf<is_field<TField>> = _>
        friend Invoke<TField>& get(record& rec) {
            return get<TField::index>(rec);
        }

        template<typename TField, EnableIf<is_field<TField>> = _>
        friend const Invoke<TField>& get(const record& rec) {
            return get<TField::index>(rec);
        }
    };
}

#endif