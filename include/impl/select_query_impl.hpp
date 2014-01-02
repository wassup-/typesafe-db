/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SELECT_QUERY_IMPL_HPP
#define _SELECT_QUERY_IMPL_HPP

#include "../config.hpp"
#include "../field.hpp"
#include "../stringutil.hpp"
#include "../unique_types.hpp"

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
        std::string const table_names<TDescriptors...>::names[] = { to_string(typename TDescriptors::table::type())... };

        template<typename... TFields>
        struct select_query_impl {

            static std::string build_select_query() {
                using std::to_string;
                using tables = typename Invoke<unique_types<DescriptorOf<TFields>...>>::template as<table_names>::type;
                return stringutils::concatenate(
                    "SELECT ",
                    stringutils::implode(", ", to_string(TFields())...),
                    " FROM ",
                    stringutils::implode(", ", tables::names)
                );
            }
        };
    }
}

#endif