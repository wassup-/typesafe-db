/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _PRIMARY_KEY_HPP
#define _PRIMARY_KEY_HPP

namespace fp {
    template<typename, int, typename>
    struct field;
    
    namespace impl {
        template<typename> struct primary_key;
        
        template<typename TDescriptor, int Idx, typename TType>
        struct primary_key<field<TDescriptor, Idx, TType> > {
            using field<TDescriptor, Idx, TType>::index;
            using field<TDescriptor, Idx, TType>::type;
        };
    }
    
    template<typename T>
    struct primary_key : impl::primary_key<T> { };
}

#endif