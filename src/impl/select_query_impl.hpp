#ifndef _SELECT_QUERY_IMPL_HPP
#define _SELECT_QUERY_IMPL_HPP

#include "../unique_types.hpp"

#include <sstream>      // for std::ostringstream
#include <string>       // for std::string, std::to_string

namespace fp {

    namespace impl {
        template<typename...>
        struct select_query_impl;
        
        template<typename...>
        struct table_names;

        template<typename... TDescriptors>
        struct table_names {
            static unsigned int const size = sizeof...(TDescriptors);
            static std::string const names[];
        };
        
        template<typename... TDescriptors>
        static std::string (*get_table_names())[sizeof...(TDescriptors)] {
            static std::string names[] = { to_string(typename TDescriptors::table::type())... };
            return names;
        }

        template<typename... TDescriptors>
        std::string const table_names<TDescriptors...>::names[] = { to_string(typename TDescriptors::table::type())... };

        template<typename... TFields>
        struct select_query_impl {

            static std::string build_select_query() {
                using std::to_string;
                typedef typename Invoke<unique_types<DescriptorOf<TFields>...>>::template as<table_names>::type tables;
                static std::string const field_identifiers[] = { to_string(TFields())... };
                std::ostringstream ss;
                ss << "SELECT ";
                ss << field_identifiers[0];
                for (unsigned int i = 1; i < (sizeof (field_identifiers) / sizeof (std::string)); ++i) {
                    ss << ", " << field_identifiers[i];
                }
                ss << " FROM ";
                ss << tables::names[0];
                for (unsigned int i = 1; i < tables::size; ++i) {
                    ss << ", " << tables::names[i];
                }
                return ss.str();
            }
        };
    }
}

#endif