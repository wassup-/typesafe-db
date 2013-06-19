/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _FIELD_HPP
#define _FIELD_HPP

#include "type_traits.hpp"      // for fp::Bool, fp::result_of, fp::indexed

#include <sstream>              // for std::ostringstream
#include <string>               // for std::string, std::to_string
#include <tuple>                // for std::tuple

namespace fp {
    template<typename, int, typename>
    struct field;

    template<int, typename...>
    struct combined_field;
    
    // This sole purpose of this declaration is to enable ADL
    template<typename> void to_string() = delete;

    namespace detail {

        template<typename>
        struct is_field : Bool<false> { };
        
        template<typename>
        struct unpack_field;
        
        template<typename TDescriptor, int Idx, typename TValue>
        struct unpack_field<field<TDescriptor, Idx, TValue>> {
            static std::string const tables[];
            static std::string const fields[];
        };
        
        template<typename TDescriptor, int Idx, typename TValue>
        std::string const unpack_field<field<TDescriptor, Idx, TValue>>::tables[] = { to_string(Invoke<typename TDescriptor::table>()) };
        
        template<typename TDescriptor, int Idx, typename TValue>
        std::string const unpack_field<field<TDescriptor, Idx, TValue>>::fields[] = { to_string(TDescriptor::template field<Idx>::name) };
        
        template<int Idx, typename... TField>
        struct unpack_field<combined_field<Idx, TField...>> {
            static std::string const tables[];
            static std::string const fields[];
        };
        
        template<int Idx, typename... TField>
        std::string const unpack_field<combined_field<Idx, TField...>>::tables[] = { };
        
        template<int Idx, typename... TField>
        std::string const unpack_field<combined_field<Idx, TField...>>::fields[] = { };
    }
    
    template<typename T>
    struct unpack_field : detail::unpack_field<T> { };

    template<typename T>
    struct is_field : detail::is_field<T> { };

    template<typename>
    struct field_traits;

    template<typename T>
    using DescriptorOf = typename T::descriptor_type;

    template<typename T>
    using TableOf = typename T::table_type;

    namespace detail {
        
        template<typename TDescriptor, int Index, typename TType>
        struct is_field<field<TDescriptor, Index, TType>> : Bool<true> { };

        template<int Index, typename... TFields>
        struct is_field<combined_field<Index, TFields...>> : All<is_field<TFields>...> { };
    }

    template<typename TDescriptor, int Index, typename TType>
    struct field_traits<field<TDescriptor, Index, TType> > {
        
        using descriptor_type = TDescriptor;
        using table_type = Invoke<typename TDescriptor::table>;
        using type = TType;

        CONSTEXPR static int index = Index;
        CONSTEXPR static char const * name = TDescriptor::template field<Index>::name;
    };

    template<typename TDescriptor, int Index, int... Indices, typename... TTypes>
    struct field_traits<combined_field<Index, field<TDescriptor, Indices, TTypes>...>> {
        
        using descriptor_type = FirstTypeOf<DescriptorOf<field<TDescriptor, Indices, TTypes>>...>;
        using table_type = typename TDescriptor::table::type;
        using type = std::tuple<TTypes...>;

        CONSTEXPR static int index = combined_field<Index, field<TDescriptor, Indices, TTypes>...>::index;
        CONSTEXPR static char const * name = combined_field<Index, field<TDescriptor, Indices, TTypes>...>::name;
    };

    template<typename TDescriptor, int Index, typename TType>
    struct field {
        
        using descriptor_type = typename field_traits<field<TDescriptor, Index, TType>>::descriptor_type;
        using type = typename field_traits<field<TDescriptor, Index, TType>>::type;

        CONSTEXPR static int index = field_traits<field<TDescriptor, Index, TType >>::index;
        CONSTEXPR static char const * name = field_traits<field<TDescriptor, Index, TType>>::name;

        friend std::string to_string(field) {
            return to_string(Invoke<typename TDescriptor::table>()) + std::string(".") + std::string(name);
        }
    };

    template<int Index, typename... TFields>
    struct combined_field {
        
        using descriptor_type = typename field_traits<combined_field<Index, TFields...>>::descriptor_type;
        using type = typename field_traits<combined_field<Index, TFields...>>::type;

        CONSTEXPR static int index = field_traits<combined_field<Index, TFields... >>::index;
        CONSTEXPR static char const * name = field_traits<combined_field<Index, TFields... >>::name;

        friend std::string to_string(combined_field) {
            using std::to_string;
            static std::string const names[] = { to_string(TFields())... };
            std::ostringstream ss;
            ss << '(';
            ss << names[0];
            for (std::size_t i = 1; i < sizeof...(TFields); ++i) {
                ss << ", " << names[i];
            }
            ss << ") AS " << name;
            return ss.str();
        }
    };

    namespace detail {
        
        template<int Idx, typename TDescriptor, int... Indices, typename... TTypes>
        struct is_field<combined_field<Idx, field<TDescriptor, Indices, TTypes>...>> : Bool<true> { };
    }

    template<typename... TFields>
    struct are_related_fields : All<is_field<TFields>..., is_same<DescriptorOf<TFields>...>> { };

    template<int Index, typename... TFields, EnableIf<is_field<TFields>...> = _>
    inline combined_field<Index, TFields...> combine(TFields...){
        return combined_field<Index, TFields...>();
    }
}

#endif