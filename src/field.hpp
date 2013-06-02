/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _FIELD_HPP
#define _FIELD_HPP

#include "type_traits.hpp"      // for fp::result_of, fp::indexed

#include <string>               // for std::string, std::to_string
#include <tuple>                // for std::tuple
#include <type_traits>          // for std::true_type, std::false_type

namespace fp {
    template<typename, int, typename>
    struct field;
    
    template<int, typename...>
    struct combined_field;
    
    template<typename>
    struct is_field;
    
    template<typename>
    struct field_traits;
    
    template<typename T>
    using DescriptorOf = typename T::descriptor_type;
    
    template<typename T>
    using TableOf = typename T::table_type;

    template<typename>
    struct is_field : Bool<false> { };
    
    template<typename TDescriptor, int Index, typename TType>
    struct is_field<field<TDescriptor, Index, TType>> : Bool<true> {
    };
    
    template<int Index, typename... TFields>
    struct is_field<combined_field<Index, TFields...>> : All<is_field<TFields>...> {
    };

    template<typename>
    struct field_traits;

    template<typename TDescriptor, int Index, typename TType>
    struct field_traits<field<TDescriptor, Index, TType> > {
        using descriptor_type = TDescriptor;
        using table_type = typename TDescriptor::table::type;
        using type = TType;
        
        CONSTEXPR static int index = Index;
        CONSTEXPR static char const * name = TDescriptor::template field<Index>::name;
    };

    template<typename TDescriptor, int Index, int... Indices, typename... TTypes>
    struct field_traits<combined_field<Index, field<TDescriptor, Indices, TTypes>...> > {
        using descriptor_type = DescriptorOf<combined_field<Index, field<TDescriptor, Indices, TTypes>...>>;
        using table_type = typename descriptor_type::table::type;
        using type = Invoke<combined_field<Index, field<TDescriptor, Indices, TTypes>...>>;
        
        CONSTEXPR static int index = combined_field<Index, field<TDescriptor, Indices, TTypes>...>::index;
        CONSTEXPR static char const * name = combined_field<Index, field<TDescriptor, Indices, TTypes>...>::name;
    };

    template<typename TDescriptor, int Index, typename TType>
    struct field {
        using descriptor_type = DescriptorOf<field_traits<field<TDescriptor, Index, TType>>>;
        using type = typename field_traits<field<TDescriptor, Index, TType>>::type;

        CONSTEXPR static int index = field_traits<field<TDescriptor, Index, TType>>::index;
        CONSTEXPR static char const * name = field_traits<field<TDescriptor, Index, TType>>::name;

        friend std::string to_string(field) {
            return to_string(typename descriptor_type::table::type()) + std::string(".") + std::string(name);
        }
    };

    template<int Index, typename... TFields>
    struct combined_field {
        using descriptor_type = FirstTypeOf<DescriptorOf<TFields>...>;
        using type = std::tuple<Invoke<TFields>...>;

        CONSTEXPR static int index = field_traits<combined_field<Index, TFields...>>::index;
        CONSTEXPR static char const * name = field_traits<combined_field<Index, TFields...>>::name;

        friend std::string to_string(combined_field) {
            using std::to_string;
            static std::string const names[] = {to_string(TFields())...};
            std::string ret = names[0];
            for (unsigned int i = 1; i < sizeof...(TFields); ++i) {
                ret += ", " + names[i];
            }
            return std::string("(") + ret + ") AS " + name;
        }
    };

    template<typename TDescriptor, int Index, typename TType>
    struct result_of<field<TDescriptor, Index, TType> > {
        using type = TType;
    };

    template<int Idx, typename TDescriptor, int... Indices, typename... TTypes>
    struct result_of<combined_field<Idx, field<TDescriptor, Indices, TTypes>...> > {
        using type = std::tuple<TTypes...>;
    };

    template<int Idx, typename TDescriptor, int... Indices, typename... TTypes>
    struct is_field<combined_field<Idx, field<TDescriptor, Indices, TTypes>...> > : Bool<true> { };

    template<typename... TFields>
    struct are_related_fields : All<is_field<TFields>..., is_same<DescriptorOf<TFields>...>> { };

    template<int Index, typename... TFields, EnableIf<is_field<TFields>...> = _>
    inline combined_field<Index, TFields...> combine(TFields...) {
        return combined_field<Index, TFields...>();
    }
}

#endif