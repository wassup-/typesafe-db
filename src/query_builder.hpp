/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _QUERY_BUILDER_HPP
#define _QUERY_BUILDER_HPP

#include "impl/query_builder_impl.hpp"

#include <sstream>

namespace fp {
    template<typename TDescriptor, int... Is> inline char const ** get_field_identifiers() {
        static char const * ret[sizeof...(Is)]= { get_field_identifier<TDescriptor, Is>()... };
        return ret;
    }

    struct query_builder {
        template<typename TDescriptor, int... Cs >
        std::string build_select_query() const {
            char const ** field_identifiers = get_field_identifiers<TDescriptor, Cs...>();
            std::stringstream ss;
            ss << "SELECT ";
            if (sizeof...(Cs) > 0) {
                ss << field_identifiers[0];
                for (unsigned int i = 1; i < sizeof...(Cs); ++i) {
                    ss << ", " << field_identifiers[i];
                }
            }
            ss << " FROM " << TDescriptor::table::name;
            return ss.str();
        }

        template<typename TDescriptor, typename... Ts >
        std::string build_where_query(Ts const &... ts) const {
            std::stringstream ss;
            ss << "WHERE ";
            impl::get_where_clauses<TDescriptor, Ts...> wc(ts...);
            wc.get(ss);
            return ss.str();
        }
    };
}

#endif