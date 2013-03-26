/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _FIELD_HPP
#define _FIELD_HPP

#include <cstddef>              // for int
#include <string>

namespace fp {
    template<typename, int> struct field;

    template<typename> struct is_field {

        enum {
            value = false
        };
    };

    template<typename TDescriptor, int Idx> struct is_field<field<TDescriptor, Idx> > {

        enum {
            value = true
        };
    };

    template<typename TDescriptor, int Idx> struct field {

        enum {
            index = Idx
        };
        typedef typename TDescriptor::template field<Idx>::type type;
        
        friend std::string to_string(field) {
            return TDescriptor::template field<Idx>::name;
        }
    };
    
    template<int, typename...> struct combined_field;
    template<int Idx, typename TDescriptor, int... Indices> struct combined_field<Idx, field<TDescriptor, Indices>...> {
        friend std::string to_string(combined_field) {
            static std::string const names[] = { to_string(field<TDescriptor, Indices>())... };
            std::string ret = names[0];
            for(unsigned int i = 1; i < sizeof...(Indices); ++i) {
                ret += ", " + names[i];
            }
            return std::string("(") + ret + ") AS " + TDescriptor::template field<Idx>::name;
        }
    };
}

#endif