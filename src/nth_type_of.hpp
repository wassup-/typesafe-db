/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _NTH_TYPE_OF_H
#define _NTH_TYPE_OF_H

namespace fp {
    template<typename...>
    struct type_seq;
    
    template<int, typename...>
    struct nth_type_of;
    
    template<typename...>
    struct first_type_of;
    
    template<typename...>
    struct last_type_of;
    
    template<int, typename>
    struct nth_type_of_seq;

    template<int I, typename H, typename... T>
    struct nth_type_of<I, H, T...> : nth_type_of < (I - 1), T...> {
    };

    template<typename H, typename... T>
    struct nth_type_of < 0, H, T...> {
        typedef H type;
    };

    template<int I, typename... Ts>
    struct nth_type_of_seq<I, type_seq<Ts...> > : nth_type_of<I, Ts...> {
    };

    template<typename H, typename... T>
    struct first_type_of<H, T...> {
        typedef H type;
    };

    template<typename H, typename... T>
    struct last_type_of<H, T...> : last_type_of < T...> {
    };

    template<typename H>
    struct last_type_of<H> {
        typedef H type;
    };
}

#endif