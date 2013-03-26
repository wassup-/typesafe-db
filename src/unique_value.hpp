/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UNIQUE_VALUE_HPP
#define _UNIQUE_VALUE_HPP

#include <cstddef>              // for int

namespace fp {
    template<typename, int> struct field;
    template<typename> struct unique_value;

    template<typename TDescriptor, int Idx> struct unique_value<field<TDescriptor, Idx> > {
        using field<TDescriptor, Idx>::index;
        using field<TDescriptor, Idx>::type;
        using field<TDescriptor, Idx>::name;
    };
}

#endif