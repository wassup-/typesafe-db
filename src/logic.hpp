/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LOGIC_HPP
#define _LOGIC_HPP

namespace fp {
    template<bool> struct _not;
    template<bool...> struct _and;
    template<bool...> struct _or;

    template<bool...> struct _any;
    template<bool...> struct _all;
    template<bool...> struct _none;

    template<bool V> struct _not {

        enum {
            value = (!V)
        };
    };

    template<bool H, bool... T> struct _and<H, T...> {

        enum {
            value = (H && _and < T...>::value)
        };
    };

    template<bool... T> struct _and < false, T...> {

        enum {
            value = false
        };
    };

    template<> struct _and < true > {

        enum {
            value = true
        };
    };

    template<> struct _and < false > {

        enum {
            value = false
        };
    };

    template<bool H, bool... T> struct _or<H, T...> {

        enum {
            value = (H || _or < T...>::value)
        };
    };

    template<bool... T> struct _or < true, T...> {

        enum {
            value = true
        };
    };

    template<> struct _or < true > {

        enum {
            value = true
        };
    };

    template<> struct _or < false > {

        enum {
            value = false
        };
    };

    template<bool H, bool... T> struct _any<H, T...> {

        enum {
            value = _or<H, T...>::value
        };
    };

    template<bool H, bool... T> struct _all<H, T...> {

        enum {
            value = _and<H, T...>::value
        };
    };

    template<bool H, bool... T> struct _none<H, T...> {

        enum {
            value = (!H && _none < T...>::value)
        };
    };

    template<bool... T> struct _none < true, T...> {

        enum {
            value = false
        };
    };

    template<> struct _none < true > {

        enum {
            value = false
        };
    };

    template<> struct _none < false > {

        enum {
            value = true
        };
    };
}

#endif