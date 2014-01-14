/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ASSERT_HPP_
#define ASSERT_HPP_

#include "config.hpp"

#include <iostream>     // for std::cerr

#if defined(assert)
#undef assert
#endif

#if defined(FP_DEBUG)
#define FP_ASSERT(x, msg)       do { if(!(x)) { ::fp::assert((#x), (msg), (__FILE__), (__LINE__), (__PRETTY_FUNCTION__)); } } while(0)
#else
#define FP_ASSERT(x, msg)
#endif

namespace fp {

    enum class assert_method_e {
        halt_, continue_,
    };

    static assert_method_e assert_method = assert_method_e::halt_;

    static void assert(const char* cond, const char* msg, const char* file, int line, const char* fn) {
        std::cerr << file << ":" << line << " in " << fn << " :\n\tAssert " << cond << " failed: " << msg << std::endl;
        if (assert_method_e::halt_ == assert_method) {
            exit(0);
        }
    }
}

#endif