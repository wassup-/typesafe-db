/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_RESULT_ITERATOR_HPP
#define _MYSQL_RESULT_ITERATOR_HPP

#include <utility>      // for std::swap

namespace fp {

    namespace mysql {

        namespace impl {

            template<typename>
            struct result_iterator_impl;
        }

        struct basic_result;

        template<typename T>
        struct result_iterator {
        public:
            using this_type = result_iterator<T>;
            using traits_type = typename std::iterator_traits<T>;

            using value_type = typename traits_type::value_type;
            using reference = typename traits_type::reference;
            using pointer = typename traits_type::pointer;
            using difference_type = typename traits_type::difference_type;
            using iterator_category = typename traits_type::iterator_category;
        protected:
            impl::result_iterator_impl<T> * _impl;
        public:

            result_iterator(basic_result & res)
            : _impl(0)
            { }

            result_iterator(result_iterator const & it)
            : _impl(0)
            { }

            result_iterator(result_iterator && it)
            : _impl(0)
            { swap(*this, it); }

            ~result_iterator()
            { }

            friend void swap(result_iterator & l, result_iterator & r) {
                using std::swap;
                swap(l._impl, r._impl);
            }

            result_iterator & operator++() {
                return *this;
            }

            result_iterator operator++(int) {
                result_iterator ret(*this);
                return ret;
            }

            pointer operator->() const {
                return 0;
            }

            reference operator*() const {
                return *(operator->());
            }
        };
    }
}

#endif