/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _NULLABLE_H
#define _NULLABLE_H

#include "exceptions.hpp"

namespace fp {
    template<typename> struct nullable;

    namespace impl {

        template<typename TException>
        void assert_or_throw(bool c) throw (TException) {
            if (!c) {
                throw TException();
            }
        }
    }

    template<typename T> struct nullable {
    public:
        typedef T value_type;
        typedef T & reference;
        typedef T const & const_reference;
        typedef T * pointer;
        typedef T const * const_pointer;
        typedef nullable<T> this_type;
    protected:
        pointer m_ptr;

        void reset(T const & v) {
            delete m_ptr;
            m_ptr = new T(v);
        }

        void reset(T const * p) {
            delete m_ptr;
            if (p) {
                m_ptr = new T(*p);
            } else {
                m_ptr = 0;
            }
        }
    public:

        nullable() : m_ptr(0) {
        }

        explicit nullable(T const & v) : m_ptr(0) {
            reset(v);
        }

        nullable(nullable const & n) : m_ptr(0) {
            reset(n.m_ptr);
        }

        template<typename O>
        nullable(nullable<O> const & n) : m_ptr(0) {
            reset(n.m_ptr);
        }

        ~nullable() {
            delete m_ptr;
        }

        reference get() {
            impl::assert_or_throw<null_exception > (0 != m_ptr);
            return *m_ptr;
        }

        const_reference get() const {
            impl::assert_or_throw<null_exception > (0 != m_ptr);
            return *m_ptr;
        }

        pointer ptr() {
            return m_ptr;
        }

        const_pointer ptr() const {
            return m_ptr;
        }

        bool operator!() const {
            return (0 == m_ptr);
        }

        nullable & operator=(T const & v) {
            reset(v);
            return *this;
        }

        nullable & operator=(nullable const & n) {
            if (&n != this) {
                reset(n.m_ptr);
            }
            return *this;
        }

        template<typename O>
        nullable & operator=(nullable<O> const & n) {
            if (&n != this) {
                reset(n.m_ptr);
            }
            return *this;
        }

        void clear() {
            delete m_ptr;
            m_ptr = 0;
        }

        bool is_set() const {
            return (0 != m_ptr);
        }
    };
}

#endif