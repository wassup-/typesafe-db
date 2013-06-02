/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _NTH_VALUE_OF_HPP
#define _NTH_VALUE_OF_HPP

namespace fp {
    template<int, int...>
    struct nth_value_of;
   
    template<int...>
    struct first_value_of;
    
    template<int...>
    struct last_value_of;

    template<int I, int H, int... T>
    struct nth_value_of<I, H, T...> : nth_value_of < (I - 1), T...> {
    };

    template<int H, int... T>
    struct nth_value_of < 0, H, T...> {

        enum {
            value = H
        };
    };

    template<int H, int... T>
    struct first_value_of<H, T...> {

        enum {
            value = H
        };
    };

    template<int H, int... T>
    struct last_value_of<H, T...> : last_value_of < T...> {
    };

    template<int H>
    struct last_value_of<H> {

        enum {
            value = H
        };
    };
}

#endif