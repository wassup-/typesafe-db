#ifndef COLUMN_HPP_
#define COLUMN_HPP_

#include "field.hpp"

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
    struct is_column : Bool<false> { };
    template<typename Descriptor, const char* Name, typename Field>
    struct is_column<column<Descriptor, Name, Field>> : is_field<Field> { };

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
