#ifndef _LEXICAL_CAST_IMPL_HPP
#define _LEXICAL_CAST_IMPL_HPP

#include <sstream>      // for std::stringstream

namespace fp {
    namespace impl {
        template<typename, typename>
        struct lexical_cast_impl;

        template<typename In, typename Out>
        struct lexical_cast_impl {

            static Out cast(In const & v) {
                Out ret;
                std::stringstream ss;
                ss << v;
                ss >> ret;
                return ret;
            }
        };

        template<typename T>
        struct lexical_cast_impl<T, T> {

            static T const & cast(T const & v) {
                return v;
            }
        };

        template<>
        struct lexical_cast_impl<std::string, char const *> {

            static char const * cast(std::string const & v) {
                return v.c_str();
            }
        };

        template<>
        struct lexical_cast_impl<char const *, std::string> {

            static std::string cast(char const * v) {
                return std::string(v);
            }
        };

        template<typename In>
        struct lexical_cast_impl<In, char const *>;

        template<typename In>
        struct lexical_cast_impl<In, char *>;
    }
}

#endif