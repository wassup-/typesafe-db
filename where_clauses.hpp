#ifndef _WHERE_CLAUSES_HPP
#define _WHERE_CLAUSES_HPP

#include "int_sequence.hpp"
#include "lexical_cast.hpp"
#include "nth_type_of.hpp"
#include "record.hpp"
#include "type_sequence.hpp"

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

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return static_cast<T const *>(this)->operator()(r);
            }

            template<typename TDescriptor> std::string to_string() const {
                return static_cast<T const *>(this)->to_string<TDescriptor>();
            }

            template<typename C> where_or<T, C> operator|(C c) const {
                return where_or<T, C>(*static_cast<T const *>(this), c);
            }

            template<typename C> where_and<T, C> operator&(C c) const {
                return where_and<T, C>(*static_cast<T const *>(this), c);
            }
        };

        template<int I, typename T> struct where_eq : where_condition<where_eq<I, T> > {
        public:
            enum { index = I };
        protected:
            T const value;
        public:
            where_eq(T v) : value(v) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (fp::get<I > (r) == value);
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << TDescriptor::template field<I>::name << " = " << lexical_cast<std::string>(value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_neq : where_condition<where_neq<I, T> > {
        public:
            enum { index = I };
        protected:
            T const value;
        public:
            where_neq(T v) : value(v) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (fp::get<I>(r) != value);
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << TDescriptor::template field<I>::name << " != " << lexical_cast<std::string>(value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_lt : where_condition<where_lt<I, T> > {
        public:
            enum { index = I };
        protected:
            T const value;
        public:
            where_lt(T v) : value(v) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (fp::get<I>(r) < value);
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << TDescriptor::template field<I>::name << " < " << lexical_cast<std::string>(value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_gt : where_condition<where_gt<I, T> > {
        public:
            enum { index = I };
        protected:
            T const value;
        public:
            where_gt(T v) : value(v) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (fp::get<I>(r) > value);
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << TDescriptor::template field<I>::name << " > " << lexical_cast<std::string>(value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_lte : where_condition<where_lte<I, T> > {
        public:
            enum { index = I };
        protected:
            T const value;
        public:
            where_lte(T v) : value(v) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (fp::get<I>(r) <= value);
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << TDescriptor::template field<I>::name << " <= " << lexical_cast<std::string>(value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_gte : where_condition<where_gte<I, T> > {
        public:
            enum { index = I };
        protected:
            T const value;
        public:
            where_gte(T v) : value(v) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (fp::get<I>(r) >= value);
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << TDescriptor::template field<I>::name << " >= " << lexical_cast<std::string>(value) << ')';
                return ss.str();
            }
        };

        template<int I, typename T> struct where_contains : where_condition<where_contains<I, T> > {
        public:
            enum { index = I };
        protected:
            T const value;
        public:
            where_contains(T v) : value(v) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (T::npos != fp::get<I>(r).find(value));
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << TDescriptor::template field<I>::name << " LIKE \"%" << lexical_cast<std::string>(value) << "%\")";
                return ss.str();
            }
        };

        template<typename L, typename R> struct where_or : where_condition<where_or<L, R> > {
        protected:
            L m_left;
            R m_right;
        public:
            where_or(L l, R r) : m_left(l), m_right(r) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (m_left(r) || m_right(r));
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << m_left.to_string<TDescriptor > () << " OR " << m_right.to_string<TDescriptor>() << ')';
                return ss.str();
            }
        };

        template<typename L, typename R> struct where_and : where_condition<where_and<L, R> > {
        protected:
            L m_left;
            R m_right;
        public:
            where_and(L l, R r) : m_left(l), m_right(r) { }

            template<typename TRecord> bool operator()(TRecord const & r) const {
                return (m_left(r) && m_right(r));
            }

            template<typename TDescriptor> std::string to_string() const {
                std::stringstream ss;
                ss << '(' << m_left.to_string<TDescriptor > () << " AND " << m_right.to_string<TDescriptor>() << ')';
                return ss.str();
            }
        };
    }

    template<typename TDescriptor, int I, typename T>
    inline where_clauses::where_eq<I, T> operator==(field<TDescriptor, I>, T v) {
        return where_clauses::where_eq<I, T>(v);
    }

    template<typename TDescriptor, int I, typename T>
    inline where_clauses::where_neq<I, T> operator!=(field<TDescriptor, I>, T v) {
        return where_clauses::where_neq<I, T>(v);
    }

    template<typename TDescriptor, int I, typename T>
    inline where_clauses::where_lt<I, T> operator<(field<TDescriptor, I>, T v) {
        return where_clauses::where_lt<I, T>(v);
    }

    template<typename TDescriptor, int I, typename T>
    inline where_clauses::where_gt<I, T> operator>(field<TDescriptor, I>, T v) {
        return where_clauses::where_gt<I, T>(v);
    }

    template<typename TDescriptor, int I, typename T>
    inline where_clauses::where_lte<I, T> operator<=(field<TDescriptor, I>, T v) {
        return where_clauses::where_lte<I, T>(v);
    }

    template<typename TDescriptor, int I, typename T>
    inline where_clauses::where_gte<I, T> operator>=(field<TDescriptor, I>, T v) {
        return where_clauses::where_gte<I, T>(v);
    }

    template<typename TDescriptor, int I, typename T>
    inline where_clauses::where_contains<I, T> operator%(field<TDescriptor, I>, T v) {
        return where_clauses::where_contains<I, T>(v);
    }
}

#endif