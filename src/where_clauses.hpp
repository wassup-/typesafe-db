/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_CLAUSES_HPP
#define _WHERE_CLAUSES_HPP

#include "lexical_cast.hpp"

#include <string>
#include <sstream>

namespace fp {
    template<typename, int> struct field;

    namespace where_clauses {
        template<int, typename> struct where_eq;
        template<int, typename> struct where_neq;
        template<int, typename> struct where_lt;
        template<int, typename> struct where_gt;
        template<int, typename> struct where_lte;
        template<int, typename> struct where_gte;
        template<int, typename> struct where_contains;
        template<typename, typename> struct where_or;
        template<typename, typename> struct where_and;

        template<typename T> struct where_condition {

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return static_cast<T const *> (this)->operator()(r);
            }

            template<typename TDescriptor >
            std::string to_string() const {
                return static_cast<T const *> (this)->to_string<TDescriptor > ();
            }

            template<typename C >
            where_or<T, C> operator|(C c) const {
                return where_or<T, C > (*static_cast<T const *> (this), c);
            }

            template<typename C >
            where_and<T, C> operator&(C c) const {
                return where_and<T, C > (*static_cast<T const *> (this), c);
            }
        };

        template<int I, typename T> struct where_eq : where_condition<where_eq<I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T const value;
        public:

            where_eq(T v) : value(v) {
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) == value);
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << fp::get_field_identifier<TDescriptor, I > () << " = " << lexical_cast<std::string > (value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_neq : where_condition<where_neq<I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T const value;
        public:

            where_neq(T v) : value(v) {
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) != value);
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << fp::get_field_identifier<TDescriptor, I > () << " != " << lexical_cast<std::string > (value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_lt : where_condition<where_lt<I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T const value;
        public:

            where_lt(T v) : value(v) {
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) < value);
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << fp::get_field_identifier<TDescriptor, I > () << " < " << lexical_cast<std::string > (value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_gt : where_condition<where_gt<I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T const value;
        public:

            where_gt(T v) : value(v) {
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) > value);
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << fp::get_field_identifier<TDescriptor, I > () << " > " << lexical_cast<std::string > (value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_lte : where_condition<where_lte<I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T const value;
        public:

            where_lte(T v) : value(v) {
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) <= value);
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << fp::get_field_identifier<TDescriptor, I > () << " <= " << lexical_cast<std::string > (value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_gte : where_condition<where_gte<I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T const value;
        public:

            where_gte(T v) : value(v) {
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) >= value);
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << fp::get_field_identifier<TDescriptor, I > () << " >= " << lexical_cast<std::string > (value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_contains : where_condition<where_contains<I, T> > {
        public:

            enum {
                index = I
            };
        protected:
            T const value;
        public:

            where_contains(T v) : value(v) {
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (T::npos != fp::get<I > (r).find(value));
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << fp::get_field_identifier<TDescriptor, I > () << " LIKE \"%" << lexical_cast<std::string > (value) << "%\")";
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

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (m_left(r) || m_right(r));
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << m_left.to_string<TDescriptor > () << " OR " << m_right.to_string<TDescriptor > () << ')';
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

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (m_left(r) && m_right(r));
            }

            template<typename TDescriptor >
            std::string to_string() const {
                std::stringstream ss;
                ss << '(' << m_left.to_string<TDescriptor > () << " AND " << m_right.to_string<TDescriptor > () << ')';
                return ss.str();
            }
        };
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_eq<I, typename field<TDescriptor, I>::type> eq(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_eq<I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_neq<I, typename field<TDescriptor, I>::type> neq(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_neq<I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_lt<I, typename field<TDescriptor, I>::type> lt(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_lt<I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_gt<I, typename field<TDescriptor, I>::type> gt(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_gt<I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_lte<I, typename field<TDescriptor, I>::type> lte(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_lte<I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_gte<I, typename field<TDescriptor, I>::type> gte(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_gte<I, typename field<TDescriptor, I>::type > (v);
    }

    template<typename TDescriptor, int I>
    inline where_clauses::where_contains<I, typename field<TDescriptor, I>::type> contains(field<TDescriptor, I>, typename field<TDescriptor, I>::type v) {
        return where_clauses::where_contains<I, typename field<TDescriptor, I>::type > (v);
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