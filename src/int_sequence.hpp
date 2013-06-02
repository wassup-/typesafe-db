/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _INT_SEQ_H
#define _INT_SEQ_H

#include "impl/int_sequence_impl.hpp"

namespace fp {
    template<int...>
    struct int_seq;
    
    template<int, int>
    struct range_builder;
    
    template<int...>
    struct skip_value;
    
    template<int... Is> struct int_seq {

        enum {
            size = sizeof...(Is)
        };

        template<template<int...> class C>
        struct as {
            using type = C<Is...>;
        };
    };

    template<int V, int... Vs>
    struct occurences_of : impl::occurences_of_impl < 0, V, Vs...> {
    };

    template<int V, int... Vs>
    struct index_of : impl::index_of_impl < 0, V, Vs...> {
    };

    template<int Min, int Max>
    struct range_builder : impl::range_builder_impl < (Min <= Max), Min, Max> {
    };

    template<int H, int... T>
    struct skip_value<H, T...> {
        using type = int_seq<T...>;
    };

    template<int Min, int Max>
    inline typename range_builder<Min, Max>::type make_range() {
        return typename range_builder<Min, Max>::type();
    }
};

#endif