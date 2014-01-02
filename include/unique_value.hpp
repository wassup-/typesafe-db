/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UNIQUE_VALUE_HPP
#define _UNIQUE_VALUE_HPP

namespace fp {
    
    template<typename, int, typename>
    struct field;
    
    template<typename>
    struct unique_value;

    template<typename TDescriptor, int Idx, typename TType>
    struct unique_value<field<TDescriptor, Idx, TType>> {
        using field<TDescriptor, Idx, TType>::index;
        using field<TDescriptor, Idx, TType>::type;
        using field<TDescriptor, Idx, TType>::name;
    };
}

#endif