/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_CLAUSES_HPP
#define _WHERE_CLAUSES_HPP

#include "field.hpp"
#include "lexical_cast.hpp"

#include <cstddef>              // for int
#include <algorithm>            // for std::swap
#include <string>               // for std::string
#include <sstream>              // for std::stringstream

namespace fp {

    namespace where_clauses {
        template<typename, int, typename> struct where_eq;
        template<typename, int, typename> struct where_neq;
        template<typename, int, typename> struct where_lt;
        template<typename, int, typename> struct where_gt;
        template<typename, int, typename> struct where_lte;
        template<typename, int, typename> struct where_gte;
        template<typename, int, typename> struct where_contains;
        template<typename, typename> struct where_or;
        template<typename, typename> struct where_and;

        template<typename T> struct where_condition {

            template<typename C >
            where_or<T, C> operator|(C c) const {
                return where_or<T, C > (static_cast<T const &> (*this), c);
            }

            template<typename C >
            where_and<T, C> operator&(C c) const {
                return where_and<T, C > (static_cast<T const &> (*this), c);
            }
        };

        template<typename TDescriptor, int I, typename T> struct where_eq : where_condition<where_eq<TDescriptor, I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T value;
        public:
            where_eq() : value() {
            }

            explicit where_eq(T v) : value(v) {
            }
            
            where_eq(where_eq const & weq) : value(weq.value) {
            }
            
            where_eq(where_eq && weq) : value() {
                swap(*this, weq);
            }
            
            friend void swap(where_eq & l, where_eq & r) {
                std::swap(l.value, r.value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) == value);
            }

            friend std::string to_string(where_eq const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(field<TDescriptor, I >()) << " = " << to_string(c.value) << ')';
                return ss.str();
            }
        };

        template<typename TDescriptor, int I, typename T> struct where_neq : where_condition<where_neq<TDescriptor, I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T value;
        public:
            where_neq() : value() {
            }

            explicit where_neq(T v) : value(v) {
            }
            
            where_neq(where_neq const & wneq) : value(wneq.value) {
            }
            
            where_neq(where_neq && wneq) : value() {
                swap(*this, wneq);
            }
            
            friend void swap(where_neq & l, where_neq & r) {
                std::swap(l.value, r.value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) != value);
            }

            friend std::string to_string(where_neq const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(field<TDescriptor, I >()) << " != " << to_string(c.value) << ')';
                return ss.str();
            }
        };

        template<typename TDescriptor, int I, typename T> struct where_lt : where_condition<where_lt<TDescriptor, I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T value;
        public:
            where_lt() : value() {
            }

            explicit where_lt(T v) : value(v) {
            }
            
            where_lt(where_lt const & wlt) : value(wlt.value) {
            }
            
            where_lt(where_lt && wlt) : value() {
                swap(*this, wlt);
            }
            
            friend void swap(where_lt & l, where_lt & r) {
                std::swap(l.value, r.value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) < value);
            }

            friend std::string to_string(where_lt const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(field<TDescriptor, I >()) << " < " << to_string(c.value) << ')';
                return ss.str();
            }
        };

        template<typename TDescriptor, int I, typename T> struct where_gt : where_condition<where_gt<TDescriptor, I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T value;
        public:
            where_gt() : value() {
            }

            explicit where_gt(T v) : value(v) {
            }
            
            where_gt(where_gt const & wgt) : value(wgt.value) {
            }
            
            where_gt(where_gt && wgt) : value() {
                swap(*this, wgt);
            }
            
            friend void swap(where_gt & l, where_gt & r) {
                std::swap(l.value, r.value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) > value);
            }

            friend std::string to_string(where_gt const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(field<TDescriptor, I >()) << " > " << to_string(c.value) << ')';
                return ss.str();
            }
        };

        template<typename TDescriptor, int I, typename T> struct where_lte : where_condition<where_lte<TDescriptor, I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T value;
        public:
            where_lte() : value() {
            }

            explicit where_lte(T v) : value(v) {
            }
            
            where_lte(where_lte const & wlte) : value(wlte.value) {
            }
            
            where_lte(where_lte && wlte) : value() {
                swap(*this, wlte);
            }
            
            friend void swap(where_lte & l, where_lte & r) {
                std::swap(l.value, r.value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) <= value);
            }

            friend std::string to_string(where_lte const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(field<TDescriptor, I >()) << " <= " << to_string(c.value) << ')';
                return ss.str();
            }
        };

        template<typename TDescriptor, int I, typename T> struct where_gte : where_condition<where_gte<TDescriptor, I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T value;
        public:
            where_gte() : value() {
            }

            explicit where_gte(T v) : value(v) {
            }
            
            where_gte(where_gte const & wgte) : value(wgte.value) {
            }
            
            where_gte(where_gte && wgte) : value() {
                swap(*this, wgte);
            }
            
            friend void swap(where_gte & l, where_gte & r) {
                std::swap(l.value, r.value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) >= value);
            }

            friend std::string to_string(where_gte const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(field<TDescriptor, I >()) << " >= " << to_string(c.value) << ')';
                return ss.str();
            }
        };

        template<typename TDescriptor, int I, typename T> struct where_contains : where_condition<where_contains<TDescriptor, I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T value;
        public:
            where_contains() : value() {
            }
            
            explicit where_contains(T v) : value(v) {
            }
            
            where_contains(where_contains const & wc) : value(wc.value) {
            }
            
            where_contains(where_contains && wc) : value() {
                swap(*this, wc);
            }
            
            friend void swap(where_contains & l, where_contains & r) {
                std::swap(l.value, r.value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (T::npos != fp::get<I > (r).find(value));
            }

            friend std::string to_string(where_contains const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(field<TDescriptor, I >()) << " LIKE \"%" << c.value << "%\")";
                return ss.str();
            }
        };

        template<typename L, typename R> struct where_or : where_condition<where_or<L, R> > {
        protected:
            L m_left;
            R m_right;
        public:

            where_or(L l, R r) : m_left(l), m_right(r) {
            }
            
            where_or(where_or const & wor) : m_left(wor.m_left), m_right(wor.m_right) {
            }
            
            where_or(where_or && wor) : m_left(), m_right() {
                swap(*this, wor);
            }
            
            friend void swap(where_or & l, where_or & r) {
                std::swap(l.m_left, r.m_left);
                std::swap(l.m_right, r.m_right);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (m_left(r) || m_right(r));
            }

            friend std::string to_string(where_or const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(c.m_left) << " OR " << to_string(c.m_right) << ')';
                return ss.str();
            }
        };

        template<typename L, typename R> struct where_and : where_condition<where_and<L, R> > {
        protected:
            L m_left;
            R m_right;
        public:

            where_and(L l, R r) : m_left(l), m_right(r) {
            }
            
            where_and(where_and const & wand) : m_left(wand.m_left), m_right(wand.m_right) {
            }
            
            where_and(where_and && wand) : m_left(), m_right() {
                swap(*this, wand);
            }
            
            friend void swap(where_and & l, where_and & r) {
                std::swap(l.m_left, r.m_left);
                std::swap(l.m_right, r.m_right);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (m_left(r) && m_right(r));
            }

            friend std::string to_string(where_and const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(c.m_left) << " AND " << to_string(c.m_right) << ')';
                return ss.str();
            }
        };
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_eq<TDescriptor, I, typename field<TDescriptor, I>::type> eq(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_eq<TDescriptor, I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_neq<TDescriptor, I, typename field<TDescriptor, I>::type> neq(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_neq<TDescriptor, I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_lt<TDescriptor, I, typename field<TDescriptor, I>::type> lt(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_lt<TDescriptor, I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_gt<TDescriptor, I, typename field<TDescriptor, I>::type> gt(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_gt<TDescriptor, I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_lte<TDescriptor, I, typename field<TDescriptor, I>::type> lte(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_lte<TDescriptor, I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_gte<TDescriptor, I, typename field<TDescriptor, I>::type> gte(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_gte<TDescriptor, I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_contains<TDescriptor, I, typename field<TDescriptor, I>::type> contains(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_contains<TDescriptor, I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline auto operator==(field<TDescriptor, I> f, typename field<TDescriptor, I>::type v) -> decltype(fp::eq(f, v)) {
        return fp::eq(f, v);
    }

    template<typename TDescriptor, int I>
    inline auto operator!=(field<TDescriptor, I> f, typename field<TDescriptor, I>::type v) -> decltype(fp::neq(f, v)) {
        return fp::neq(f, v);
    }

    template<typename TDescriptor, int I>
    inline auto operator<(field<TDescriptor, I> f, typename field<TDescriptor, I>::type v) -> decltype(fp::lt(f, v)) {
        return fp::lt(f, v);
    }

    template<typename TDescriptor, int I>
    inline auto operator>(field<TDescriptor, I> f, typename field<TDescriptor, I>::type v) -> decltype(fp::gt(f, v)) {
        return fp::gt(f, v);
    }

    template<typename TDescriptor, int I>
    inline auto operator<=(field<TDescriptor, I> f, typename field<TDescriptor, I>::type v) -> decltype(fp::lte(f, v)) {
        return fp::lte(f, v);
    }

    template<typename TDescriptor, int I>
    inline auto operator>=(field<TDescriptor, I> f, typename field<TDescriptor, I>::type v) -> decltype(fp::gte(f, v)) {
        return fp::gte(f, v);
    }

    template<typename TDescriptor, int I>
    inline auto operator%(field<TDescriptor, I> f, typename field<TDescriptor, I>::type v) -> decltype(fp::contains(f, v)) {
        return fp::contains(f, v);
    }
}

#endif