/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SELECT_QUERY_IMPL_HPP
#define _SELECT_QUERY_IMPL_HPP

#include "../config.hpp"
#include "../record.hpp"
#include "../stringutil.hpp"
#include "../unique_types.hpp"

#include <string>       // for std::string, std::to_string

namespace fp {

    namespace impl {
        
        template<typename... /* Columns */>
        struct select_query_impl;
        
        template<typename... /* Descriptors */>
        struct table_names;

        template<typename... TDescriptors>
        struct table_names {
            constexpr static std::size_t size = sizeof...(TDescriptors);
            constexpr static const char* names[size] = { TDescriptors::table.name()... };
        };
        
        template<typename... TDescriptors>
        constexpr const char* table_names<TDescriptors...>::names[table_names<TDescriptors...>::size];

        template<typename... TColumns>
        struct select_query_impl {

            static std::string build_select_query(const TColumns&... f) {
                using std::to_string;
                using tables = typename Invoke<unique_types<DescriptorOf<TColumns>...>>::template as<table_names>::type;
                return stringutils::concatenate(
                    "SELECT ",
                    stringutils::implode(", ", to_string(f)...),
                    " FROM ",
                    stringutils::implode(", ", tables::names)
                );
            }
        };
    }
}

#endif