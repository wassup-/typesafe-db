/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _FIELD_HPP
#define _FIELD_HPP

namespace fp {

    template<typename TDescriptor, int I> struct field {
        enum { index = I };
        typedef typename TDescriptor::template field<I>::type type;
        static char const * name;
    };
    template<typename TDescriptor, int I> char const * field<TDescriptor, I>::name = TDescriptor::template field<I>::name;
    
    template<typename TDescriptor, int I>
    char const * get_field_identifier() {
        return field<TDescriptor, I>::name;
    }
    template<typename TDescriptor, int I>
    char const * get_field_identifier(field<TDescriptor, I>) {
        return field<TDescriptor, I>::name;
    }
}

#endif