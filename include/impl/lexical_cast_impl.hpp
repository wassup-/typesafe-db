/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _LEXICAL_CAST_IMPL_HPP
#define _LEXICAL_CAST_IMPL_HPP

#include <sstream>      // for std::stringstream

namespace fp {
    namespace impl {
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

            static T const & cast(const T& v) {
                return v;
            }
        };

        template<>
        struct lexical_cast_impl<std::string, const char*> {

            static const char* cast(const std::string& v) {
                return v.c_str();
            }
        };

        template<>
        struct lexical_cast_impl<const char*, std::string> {

            static std::string cast(const char* v) {
                return std::string(v);
            }
        };

        template<typename In>
        struct lexical_cast_impl<In, const char*>;

        template<typename In>
        struct lexical_cast_impl<In, char *>;
    }
}

#endif