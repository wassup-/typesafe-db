/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_RESULT_ITERATOR_HPP
#define _MYSQL_RESULT_ITERATOR_HPP

#include <utility>      // for std::swap

namespace fp {

    namespace mysql {

        namespace impl {

            template<typename> struct result_iterator_impl;
        }

        struct basic_result;

        template<typename T>
        struct result_iterator {
        public:
            typedef result_iterator<T> this_type;
            typedef typename std::iterator_traits<T> traits_type;

            typedef typename traits_type::value_type value_type;
            typedef typename traits_type::reference reference;
            typedef typename traits_type::pointer pointer;
            typedef typename traits_type::difference_type difference_type;
            typedef typename traits_type::iterator_category iterator_category;
        protected:
            impl::result_iterator_impl<T> * _impl;
        public:

            result_iterator(basic_result & res) : _impl(0) {
            }

            result_iterator(result_iterator const & it) : _impl(0) {

            }

            result_iterator(result_iterator && it) : _impl(0) {
                swap(*this, it);
            }

            ~result_iterator() {
                //delete _impl;
            }

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