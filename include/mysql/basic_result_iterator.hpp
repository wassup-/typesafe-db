/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _MYSQL_RESULT_ITERATOR_HPP
#define _MYSQL_RESULT_ITERATOR_HPP

#include <iterator>
#include <utility>      // for std::swap

namespace fp { namespace mysql {

    template<typename Provider, typename T>
    struct result_iterator : std::iterator<std::input_iterator_tag, typename std::remove_pointer<T>::type> {
    public:
        using this_type = result_iterator;
        using traits_type = typename std::iterator_traits<T>;

        using value_type = typename traits_type::value_type;
        using reference = typename traits_type::reference;
        using pointer = typename traits_type::pointer;
        using difference_type = typename traits_type::difference_type;
        using iterator_category = typename traits_type::iterator_category;
    protected:
        Provider* self_;
        std::size_t index_;
    public:

        result_iterator(Provider& self, std::size_t index)
        : self_(&self)
        , index_(index)
        { }

        friend void swap(result_iterator& l, result_iterator& r) {
            using std::swap;
            swap(l.self_, r.self_);
            swap(l.index_, r.index_);
        }

        result_iterator& operator++() {
            ++index_;
            return *this;
        }

        result_iterator operator++(int) {
            result_iterator ret{ self_, index_ };
            ++index_;
            return ret;
        }

        value_type operator*() {
            return self_->fetch_row();
        }

        friend bool operator!=(const result_iterator& l, const result_iterator& r) {
            return (l.index_ != r.index_);
        }

        friend difference_type operator-(const result_iterator& l, const result_iterator& r) {
            return (l.index_ - r.index_);
        }
    };
} }

#endif