/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_CLAUSES_HPP
#define _WHERE_CLAUSES_HPP

#include "field.hpp"
#include "lexical_cast.hpp"

#include <algorithm>            // for std::swap
#include <string>               // for std::string, std::to_string
#include <sstream>              // for std::stringstream
#include <type_traits>          // for std::true_type, std::false_type

namespace fp {
    
     namespace where_clauses {
        template<typename> struct where_eq;
        template<typename> struct where_neq;
        template<typename> struct where_lt;
        template<typename> struct where_gt;
        template<typename> struct where_lte;
        template<typename> struct where_gte;
        template<typename> struct where_contains;
        template<typename, typename> struct where_or;
        template<typename, typename> struct where_and;
        
    }
    
    namespace impl {
        template<typename>
        struct is_where_clause : std::false_type { };

        template<typename TField>
        struct is_where_clause<where_clauses::where_eq<TField> > : std::true_type { };
        template<typename TField>
        struct is_where_clause<where_clauses::where_neq<TField> > : std::true_type { };
        template<typename TField>
        struct is_where_clause<where_clauses::where_lt<TField> > : std::true_type { };
        template<typename TField>
        struct is_where_clause<where_clauses::where_gt<TField> > : std::true_type { };
        template<typename TField>
        struct is_where_clause<where_clauses::where_lte<TField> > : std::true_type { };
        template<typename TField>
        struct is_where_clause<where_clauses::where_gte<TField> > : std::true_type { };
        template<typename TField>
        struct is_where_clause<where_clauses::where_contains<TField> > : std::true_type { };
        template<typename TLeft, typename TRight>
        struct is_where_clause<where_clauses::where_or<TLeft, TRight> > : std::true_type { };
        template<typename TLeft, typename TRight>
        struct is_where_clause<where_clauses::where_and<TLeft, TRight> > : std::true_type { };
    }
    
    namespace where_clauses {

        template<typename TField>
        struct where_eq {
        public:
            using descriptor_type = DescriptorOf<TField>;
        protected:
            Invoke<TField> _value;
        public:
            where_eq()
            : _value() {
            }

            explicit where_eq(Invoke<TField> v)
            : _value(std::move(v)) {
            }
            
            where_eq(where_eq const &) = default;
            
            where_eq(where_eq && c)
            : _value() {
                swap(*this, c);
            }
            
            friend void swap(where_eq & l, where_eq & r) {
                using std::swap;
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (get<TField>(r) == _value);
            }

            friend std::string to_string(where_eq const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(TField()) << " = " << to_string(c._value) << ')';
                return ss.str();
            }
        };

        template<typename TField>
        struct where_neq {
        public:
            using descriptor_type = DescriptorOf<TField>;
        protected:
            Invoke<TField> _value;
        public:
            where_neq()
            : _value() {
            }

            explicit where_neq(Invoke<TField> v)
            : _value(std::move(v)) {
            }
            
            where_neq(where_neq const &) = default;
            
            where_neq(where_neq && c)
            : _value() {
                swap(*this, c);
            }
            
            friend void swap(where_neq & l, where_neq & r) {
                using std::swap;
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (get<TField>(r) != _value);
            }

            friend std::string to_string(where_neq const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(TField()) << " != " << to_string(c._value) << ')';
                return ss.str();
            }
        };

        template<typename TField>
        struct where_lt {
        public:
            using descriptor_type = DescriptorOf<TField>;
        protected:
            Invoke<TField> _value;
        public:
            where_lt()
            : _value() {
            }

            explicit where_lt(Invoke<TField> v)
            : _value(std::move(v)) {
            }
            
            where_lt(where_lt const &) = default;
            
            where_lt(where_lt && c)
            : _value() {
                swap(*this, c);
            }
            
            friend void swap(where_lt & l, where_lt & r) {
                using std::swap;
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (get<TField>(r) < _value);
            }

            friend std::string to_string(where_lt const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(TField()) << " < " << to_string(c._value) << ')';
                return ss.str();
            }
        };

        template<typename TField>
        struct where_gt {
        public:
            using descriptor_type = DescriptorOf<TField>;
        protected:
            Invoke<TField> _value;
        public:
            where_gt()
            : _value() {
            }

            explicit where_gt(Invoke<TField> v)
            : _value(std::move(v)) {
            }
            
            where_gt(where_gt const &) = default;
            
            where_gt(where_gt && c)
            : _value() {
                swap(*this, c);
            }
            
            friend void swap(where_gt & l, where_gt & r) {
                using std::swap;
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (get<TField>(r) > _value);
            }

            friend std::string to_string(where_gt const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(TField()) << " > " << to_string(c._value) << ')';
                return ss.str();
            }
        };

        template<typename TField>
        struct where_lte {
        public:
            using descriptor_type = DescriptorOf<TField>;
        protected:
            Invoke<TField> _value;
        public:
            where_lte()
            : _value() {
            }

            explicit where_lte(Invoke<TField> v)
            : _value(std::move(v)) {
            }
            
            where_lte(where_lte const &) = default;
            
            where_lte(where_lte && c)
            : _value() {
                swap(*this, c);
            }
            
            friend void swap(where_lte & l, where_lte & r) {
                using std::swap;
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (get<TField>(r) <= _value);
            }

            friend std::string to_string(where_lte const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(TField()) << " <= " << to_string(c._value) << ')';
                return ss.str();
            }
        };

        template<typename TField>
        struct where_gte {
        public:
            using descriptor_type = DescriptorOf<TField>;
        protected:
            Invoke<TField> _value;
        public:
            where_gte()
            : _value() {
            }

            explicit where_gte(Invoke<TField> v)
            : _value(std::move(v)) {
            }
            
            where_gte(where_gte const &) = default;
            
            where_gte(where_gte && c)
            : _value() {
                swap(*this, c);
            }
            
            friend void swap(where_gte & l, where_gte & r) {
                using std::swap;
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (get<TField>(r) >= _value);
            }

            friend std::string to_string(where_gte const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(TField()) << " >= " << to_string(c._value) << ')';
                return ss.str();
            }
        };

        template<typename TField>
        struct where_contains {
        public:
            using descriptor_type = DescriptorOf<TField>;
        protected:
            Invoke<TField> _value;
        public:
            where_contains()
            : _value() {
            }
            
            explicit where_contains(Invoke<TField> v)
            : _value(std::move(v)) {
            }
            
            where_contains(where_contains const &) = default;
            
            where_contains(where_contains && c)
            : _value() {
                swap(*this, c);
            }
            
            friend void swap(where_contains & l, where_contains & r) {
                using std::swap;
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (TField::type::npos != get<TField>(r).find(_value));
            }

            friend std::string to_string(where_contains const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(TField()) << " LIKE \"%" << c._value << "%\")";
                return ss.str();
            }
        };

        template<typename L, typename R>
        struct where_or {
        public:
            typedef where_or<L, R> this_type;
        protected:
            L _left;
            R _right;
        public:

            where_or(L l, R r)
            : _left(std::move(l)), _right(std::move(r)) {
            }
            
            where_or(where_or const &) = default;
            
            where_or(where_or && c)
            : _left(), _right() {
                swap(*this, c);
            }
            
            friend void swap(where_or & l, where_or & r) {
                using std::swap;
                swap(l._left, r._left);
                swap(l._right, r._right);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (_left(r) || _right(r));
            }

            friend std::string to_string(where_or const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(c._left) << " OR " << to_string(c._right) << ')';
                return ss.str();
            }
        };

        template<typename L, typename R>
        struct where_and {
        public:
            typedef where_and<L, R> this_type;
        protected:
            L _left;
            R _right;
        public:

            where_and(L l, R r)
            : _left(std::move(l)), _right(std::move(r)) {
            }
            
            where_and(where_and const &) = default;
            
            where_and(where_and && c)
            : _left(), _right() {
                swap(*this, c);
            }
            
            friend void swap(where_and & l, where_and & r) {
                using std::swap;
                swap(l._left, r._left);
                swap(l._right, r._right);
            }

            template<typename TRecord>
            bool operator()(TRecord const & r) const {
                return (_left(r) && _right(r));
            }

            friend std::string to_string(where_and const & c) {
                using std::to_string;
                std::stringstream ss;
                ss << '(' << to_string(c._left) << " AND " << to_string(c._right) << ')';
                return ss.str();
            }
        };
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline where_clauses::where_eq<TField> eq(TField, Invoke<TField> v) {
        return where_clauses::where_eq<TField> (v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline where_clauses::where_neq<TField> neq(TField, Invoke<TField> v) {
        return where_clauses::where_neq<TField> (v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline where_clauses::where_lt<TField> lt(TField, Invoke<TField> v) {
        return where_clauses::where_lt<TField> (v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline where_clauses::where_gt<TField> gt(TField, Invoke<TField> v) {
        return where_clauses::where_gt<TField> (v);
    }
    
    template<typename TField, EnableIf<is_field<TField>> = _>
    inline where_clauses::where_lte<TField> lte(TField, Invoke<TField> v) {
        return where_clauses::where_lte<TField> (v);
    }
    
    template<typename TField, EnableIf<is_field<TField>> = _>
    inline where_clauses::where_gte<TField> gte(TField, Invoke<TField> v) {
        return where_clauses::where_gte<TField> (v);
    }
    
    template<typename TField, EnableIf<is_field<TField>> = _>
    inline where_clauses::where_contains<TField> contains(TField, Invoke<TField> v) {
        return where_clauses::where_contains<TField> (v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline auto operator==(TField f, Invoke<TField> v) -> decltype(fp::eq(f, v)) {
        return fp::eq(f, v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline auto operator!=(TField f, Invoke<TField> v) -> decltype(fp::neq(f, v)) {
        return fp::neq(f, v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline auto operator<(TField f, Invoke<TField> v) -> decltype(fp::lt(f, v)) {
        return fp::lt(f, v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline auto operator>(TField f, Invoke<TField> v) -> decltype(fp::gt(f, v)) {
        return fp::gt(f, v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline auto operator<=(TField f, Invoke<TField> v) -> decltype(fp::lte(f, v)) {
        return fp::lte(f, v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline auto operator>=(TField f, Invoke<TField> v) -> decltype(fp::gte(f, v)) {
        return fp::gte(f, v);
    }

    template<typename TField, EnableIf<is_field<TField>> = _>
    inline auto operator%(TField f, Invoke<TField> v) -> decltype(fp::contains(f, v)) {
        return fp::contains(f, v);
    }
}

#endif