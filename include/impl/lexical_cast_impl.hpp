/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LEXICAL_CAST_IMPL_HPP
#define _LEXICAL_CAST_IMPL_HPP

#include "../stringutil.hpp"

#include <sstream>      // for std::stringstream
#include <string>

namespace fp { namespace impl {

    template<typename Char, std::size_t N>
    mpl::enable_if_t<stringutils::is_char_type<Char>, std::basic_string<Char>> to_string(const Char(&s)[N]) {
        return { &s[0], N };
    }

    template<typename Char>
    mpl::enable_if_t<stringutils::is_char_type<Char>, std::basic_string<Char>> to_string(const Char* s) {
        return { s };
    }

    template<typename, typename>
    struct lexical_cast_impl;

    template<typename In, typename Out>
    struct lexical_cast_impl {

        static Out cast(const In& v) {
            Out ret;
            std::stringstream ss;
            ss << v;
            ss >> ret;
            return ret;
        }
    };

    template<typename T>
    struct lexical_cast_impl<T, T> {

        static const T& cast(const T& v) {
            return v;
        }
    };

    template<>
    struct lexical_cast_impl<std::string, const char*> {

        static const char* cast(const std::string& v) {
            return v.c_str();
        }
    };

    template<typename In>
    struct lexical_cast_impl<In, std::string> {

        static std::string cast(const In& v) {
            using std::to_string;
            return to_string(v);
        }
    };
} }

#endif