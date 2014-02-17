/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _RECORD_HPP
#define _RECORD_HPP

#include "config.hpp"
#include "column.hpp"           // for fp::column
#include "type_traits.hpp"      // for fp::EnableIf, fp::DisableIf

#include <stdexcept>

namespace fp {

    template<typename... /* Columns */>
    struct record;

    template<typename>
    struct is_record : mpl::false_ { };
    template<typename... TColumns>
    struct is_record<record<TColumns...> > : mpl::all_<is_column<TColumns>...> { };

    template<typename... Columns>
    struct record {
    public:
        using this_type = record;

        template<typename... TOther>
        struct rebind : mpl::identity<record<TOther...>> { };

        template<std::size_t Idx>
        struct nth_type : mpl::identity<NthTypeOf<Idx, Columns...>> { };

    public:
        record(typename Columns::value_type... x)
        : values_(x...)
        { }

        constexpr static std::size_t size() {
            return sizeof...(Columns);
        }

        template<std::size_t Idx>
        typename Invoke<nth_type<Idx>>::value_type& get() {
            return std::get<Idx>(values_);
        }

        template<std::size_t Idx>
        const typename Invoke<nth_type<Idx>>::value_type& get() const {
            return std::get<Idx>(values_);
        }

    public:
        friend void swap(record& l, record& r) noexcept {
            using std::swap;
            swap(l.values_, r.values_);
        }

        template<std::size_t Idx>
        friend typename Invoke<nth_type<Idx>>::value_type& get(record& r) {
            return r.template get<Idx>();
        }

        template<std::size_t Idx>
        friend const typename Invoke<nth_type<Idx>>::value_type& get(const record& r) {
            return r.template get<Idx>();
        }

    private:
        std::tuple<typename Columns::value_type...> values_;
    };

    template<typename... Column>
    constexpr inline record<Column...> make_record(typename Column::value_type... value) {
        return { value... };
    }

    namespace detail {

        template<typename Ret, typename Record, std::size_t Idx>
        inline Ret get(const Record& rec, mpl::index_<Idx>) {
            return rec.template get<Idx>();
        }

        template<typename Value, typename Record, std::size_t Idx>
        inline void set(Record& rec, const Value& x, mpl::index_<Idx>) {
            rec.template get<Idx>() = x;
        }
    }

    template<
        typename... Columns,
        typename Column,
        typename Value = typename Column::value_type,
        typename = mpl::enable_if_t<is_column<Column>>
    >
    inline const Value& get(const record<Columns...>& r, const Column& col) {
        return detail::get<const Value&>(r, mpl::index_of_t<Column, Columns...>{});
    }

    template<
        typename... Columns,
        typename... Column,
        typename = mpl::enable_if_t<mpl::bool_<(sizeof...(Column) > 1)>>
    >
    inline std::tuple<const typename Column::value_type&...> get(const record<Columns...>& r, const Column&... col) {
        return std::tie(get(r, col)...);
    }

    template<
        typename... Columns,
        typename Column,
        typename Value = typename Column::value_type,
        typename = mpl::enable_if_t<is_column<Column>>
    >
    inline void set(record<Columns...>& r, const Column& col, const Value& x) {
        return detail::set(r, x, mpl::index_of_t<Column, Columns...>{});
    }
}

#endif