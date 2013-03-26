#ifndef _LEXICAL_CAST_IMPL_HPP
#define _LEXICAL_CAST_IMPL_HPP

#include <sstream>

namespace fp {
    namespace impl {
        template<typename, typename> struct lexical_cast_impl;

        template<typename In, typename Out> struct lexical_cast_impl {
            // this one returns a value since we shouldn't return (const) references to local variables

            static Out cast(In const & v) {
                Out ret;
                std::stringstream ss;
                ss << v;
                ss >> ret;
                return ret;
            }
        };

        template<typename T> struct lexical_cast_impl<T, T> {
            // this one returns a const reference to avoid unneeded copy-constructor invocations

            static T const & cast(T const & v) {
                return v;
            }
        };

        template<> struct lexical_cast_impl<std::string, char const *> {

            static char const * cast(std::string const & v) {
                return v.c_str();
            }
        };

        template<> struct lexical_cast_impl<char const *, std::string> {

            static std::string cast(char const * v) {
                return std::string(v);
            }
        };

        // we don't want people to use C-style strings no more

        template<typename In> struct lexical_cast_impl<In, char const *> {
        };

        template<typename In> struct lexical_cast_impl<In, char *> {
        };
    }
}

#endif