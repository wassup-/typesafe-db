/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef COLUMN_HPP_
#define COLUMN_HPP_

#include "field.hpp"
#include "primary_key.hpp"

namespace fp {

	template<typename T>
    using DescriptorOf = typename T::descriptor_type;

    template<typename T>
    using TableOf = typename T::table_type;

    template<typename T>
    using FieldOf = typename T::field_type;

	template<typename /* Descriptor */, const char* /* Name */, typename /* Field */>
    struct column;

    template<typename>
    struct is_column : mpl::false_ { };
    template<typename Descriptor, const char* Name, typename Field>
    struct is_column<column<Descriptor, Name, Field>> : is_field<Field> { };

    namespace detail {

        template<typename Column, typename Descriptor>
        constexpr static bool is_primary_key_of(std::true_type /* HasPrimaryKey */) noexcept {
            return std::is_same<typename Descriptor::primary_key::type, Column>::value;
        }

        template<typename Column, typename Descriptor>
        constexpr static bool is_primary_key_of(std::false_type /* HasPrimaryKey */) noexcept {
            return false;
        }

        template<typename Column, typename Descriptor>
        constexpr static bool is_unique_key_of(std::true_type /* HasUniqueKeys */) noexcept {
            return Descriptor::unique_keys::template contains<Column>::value;
        }

        template<typename Column, typename Descriptor>
        constexpr static bool is_unique_key_of(std::false_type /* HasUniqueKeys */) noexcept {
            return false;
        }

        template<typename Column, typename Descriptor>
        constexpr static bool is_index_key_of(std::true_type /* HasIndexKeys */) noexcept {
            return Descriptor::index_keys::template contains<Column>::value;
        }

        template<typename Column, typename Descriptor>
        constexpr static bool is_index_key_of(std::false_type /* HasIndexKeys */) noexcept {
            return false;
        }
    }

    template<typename Descriptor, const char* Name, typename Field>
    struct column {
    public:
        using this_type = column;
        using descriptor_type = Descriptor;
        using table_type = decltype(Descriptor::table);
        using field_type = field<Field>;
        using value_type = typename field_traits<Field>::value_type;

    public:
        constexpr static decltype(Descriptor::table) table() {
            return Descriptor::table;
        }

        constexpr static const char* name() noexcept {
            return Name;
        }

        constexpr static bool is_primary_key() noexcept {
           return detail::is_primary_key_of<this_type, Descriptor>(HasPrimaryKey<Descriptor>{});
        }

        constexpr static bool is_unique_key() noexcept {
           return (detail::is_unique_key_of<this_type, Descriptor>(HasUniqueKeys<Descriptor>{}) || is_primary_key());
        }

        constexpr static bool is_index_key() noexcept {
           return (detail::is_index_key_of<this_type, Descriptor>(HasIndexKeys<Descriptor>{}) || is_unique_key() || is_primary_key());
        }

    public:
        friend std::string to_string(const column& f) {
            using std::to_string;
            return stringutils::concatenate(to_string(f.table()), ".", f.name());
        }

    };

    template<typename Descriptor, const char* Name, typename Field>
    constexpr inline bool operator==(const column<Descriptor, Name, Field>&, const column<Descriptor, Name, Field>&)
    { return true; }

    template<typename Descriptor, const char* Name, typename Field>
    constexpr inline bool operator!=(const column<Descriptor, Name, Field>&, const column<Descriptor, Name, Field>&)
    { return false; }

    template<
        typename LDescriptor, const char* LName, typename LField,
        typename RDescriptor, const char* RName, typename RField
    >
    constexpr inline bool operator==(const column<LDescriptor, LName, LField>&, const column<RDescriptor, RName, RField>&)
    { return false; }

    template<
        typename LDescriptor, const char* LName, typename LField,
        typename RDescriptor, const char* RName, typename RField
    >
    constexpr inline bool operator!=(const column<LDescriptor, LName, LField>&, const column<RDescriptor, RName, RField>&)
    { return true; }
}

#endif
