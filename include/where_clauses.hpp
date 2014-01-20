/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _WHERE_CLAUSES_HPP
#define _WHERE_CLAUSES_HPP

#include "field.hpp"
#include "lexical_cast.hpp"
#include "stringutil.hpp"       // for stringutils::concatenate
#include "type_traits.hpp"      // for fp::Bool

#include <string>               // for std::string, std::to_string
#include <sstream>              // for std::ostringstream
#include <utility>              // for std::move, std::swap

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
        struct is_where_clause : mpl::false_ { };

        template<typename TColumn>
        struct is_where_clause<where_clauses::where_eq<TColumn> > : mpl::true_ { };
        template<typename TColumn>
        struct is_where_clause<where_clauses::where_neq<TColumn> > : mpl::true_ { };
        template<typename TColumn>
        struct is_where_clause<where_clauses::where_lt<TColumn> > : mpl::true_ { };
        template<typename TColumn>
        struct is_where_clause<where_clauses::where_gt<TColumn> > : mpl::true_ { };
        template<typename TColumn>
        struct is_where_clause<where_clauses::where_lte<TColumn> > : mpl::true_ { };
        template<typename TColumn>
        struct is_where_clause<where_clauses::where_gte<TColumn> > : mpl::true_ { };
        template<typename TColumn>
        struct is_where_clause<where_clauses::where_contains<TColumn> > : mpl::true_ { };
        template<typename TLeft, typename TRight>
        struct is_where_clause<where_clauses::where_or<TLeft, TRight> > : mpl::true_ { };
        template<typename TLeft, typename TRight>
        struct is_where_clause<where_clauses::where_and<TLeft, TRight> > : mpl::true_ { };
    }
    
    namespace where_clauses {

        template<typename TColumn>
        struct where_eq {
        public:
            using descriptor_type = DescriptorOf<TColumn>;
        protected:
            TColumn _column;
            typename TColumn::value_type _value;
        public:
            explicit where_eq(TColumn col, typename TColumn::value_type v)
            : _column(col), _value(std::move(v))
            { }
            
            friend void swap(where_eq& l, where_eq& r) {
                using std::swap;
                swap(l._column, r._column);
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (get<TColumn>(r) == _value);
            }

            friend std::string to_string(const where_eq& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._column), " = ", to_string(c._value), ")");
            }
        };

        template<typename TColumn>
        struct where_neq {
        public:
            using descriptor_type = DescriptorOf<TColumn>;
        protected:
            TColumn _column;
            typename TColumn::value_type _value;
        public:
            explicit where_neq(TColumn col, typename TColumn::value_type v)
            : _column(col), _value(std::move(v))
            { }
            
            friend void swap(where_neq& l, where_neq& r) {
                using std::swap;
                swap(l._column, r._column);
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (get<TColumn>(r) != _value);
            }

            friend std::string to_string(const where_neq& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._column), " != ", to_string(c._value), ")");
            }
        };

        template<typename TColumn>
        struct where_lt {
        public:
            using descriptor_type = DescriptorOf<TColumn>;
        protected:
            TColumn _column;
            typename TColumn::value_type _value;
        public:
            explicit where_lt(TColumn col, typename TColumn::value_type v)
            : _column(col), _value(std::move(v))
            { }
            
            friend void swap(where_lt& l, where_lt& r) {
                using std::swap;
                swap(l._column, r._column);
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (get<TColumn>(r) < _value);
            }

            friend std::string to_string(const where_lt& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._column), " < ", to_string(c._value), ")");
            }
        };

        template<typename TColumn>
        struct where_gt {
        public:
            using descriptor_type = DescriptorOf<TColumn>;
        protected:
            TColumn _column;
            typename TColumn::value_type _value;
        public:
            explicit where_gt(TColumn col, typename TColumn::value_type v)
            : _column(col), _value(std::move(v))
            { }
            
            friend void swap(where_gt& l, where_gt& r) {
                using std::swap;
                swap(l._column, r._column);
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (get<TColumn>(r) > _value);
            }

            friend std::string to_string(const where_gt& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._column), " > ", to_string(c._value), ")");
            }
        };

        template<typename TColumn>
        struct where_lte {
        public:
            using descriptor_type = DescriptorOf<TColumn>;
        protected:
            TColumn _column;
            typename TColumn::value_type _value;
        public:
            explicit where_lte(TColumn col, typename TColumn::value_type v)
            : _column(col), _value(std::move(v))
            { }
            
            friend void swap(where_lte& l, where_lte& r) {
                using std::swap;
                swap(l._column, r._column);
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (get<TColumn>(r) <= _value);
            }

            friend std::string to_string(const where_lte& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._column), " <= ", to_string(c._value), ")");
            }
        };

        template<typename TColumn>
        struct where_gte {
        public:
            using descriptor_type = DescriptorOf<TColumn>;
        protected:
            TColumn _column;
            typename TColumn::value_type _value;
        public:
            explicit where_gte(TColumn col, typename TColumn::value_type v)
            : _column(col), _value(std::move(v))
            { }
            
            friend void swap(where_gte& l, where_gte& r) {
                using std::swap;
                swap(l._column, r._column);
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (get<TColumn>(r) >= _value);
            }

            friend std::string to_string(const where_gte& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._column), " >= ", to_string(c._value), ")");
            }
        };

        template<typename TColumn>
        struct where_contains {
        public:
            using descriptor_type = DescriptorOf<TColumn>;
        protected:
            TColumn _column;
            typename TColumn::value_type _value;
        public:
            explicit where_contains(TColumn col, typename TColumn::value_type v)
            : _column(col), _value(std::move(v))
            { }
            
            friend void swap(where_contains& l, where_contains& r) {
                using std::swap;
                swap(l._column, r._column);
                swap(l._value, r._value);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (TColumn::type::npos != get<TColumn>(r).find(_value));
            }

            friend std::string to_string(const where_contains& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._column), " LIKE \"%", c._value, "%\")");
            }
        };

        template<typename L, typename R>
        struct where_or {
        public:
            using this_type = where_or<L, R>;
        protected:
            L _left;
            R _right;
        public:

            where_or(L l, R r)
            : _left(std::move(l)), _right(std::move(r))
            { }
            
            where_or(const where_or&) = default;
            
            where_or(where_or&& c)
            : _left(), _right()
            { swap(*this, c); }
            
            friend void swap(where_or& l, where_or& r) {
                using std::swap;
                swap(l._left, r._left);
                swap(l._right, r._right);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (_left(r) || _right(r));
            }

            friend std::string to_string(const where_or& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._left), " OR ", to_string(c._right), ")");
            }
        };

        template<typename L, typename R>
        struct where_and {
        public:
            using this_type = where_and<L, R>;
        protected:
            L _left;
            R _right;
        public:

            where_and(L l, R r)
            : _left(std::move(l)), _right(std::move(r))
            { }
            
            where_and(const where_and&) = default;
            
            where_and(where_and&& c)
            : _left(), _right()
            { swap(*this, c); }
            
            friend void swap(where_and& l, where_and& r) {
                using std::swap;
                swap(l._left, r._left);
                swap(l._right, r._right);
            }

            template<typename TRecord>
            bool operator()(const TRecord& r) const {
                return (_left(r) && _right(r));
            }

            friend std::string to_string(const where_and& c) {
                using std::to_string;
                return stringutils::concatenate("(", to_string(c._left), " AND ", to_string(c._right), ")");
            }
        };
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline where_clauses::where_eq<TColumn> eq(TColumn c, typename TColumn::value_type v) {
        return where_clauses::where_eq<TColumn>(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline where_clauses::where_neq<TColumn> neq(TColumn c, typename TColumn::value_type v) {
        return where_clauses::where_neq<TColumn>(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline where_clauses::where_lt<TColumn> lt(TColumn c, typename TColumn::value_type v) {
        return where_clauses::where_lt<TColumn>(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline where_clauses::where_gt<TColumn> gt(TColumn c, typename TColumn::value_type v) {
        return where_clauses::where_gt<TColumn>(c, v);
    }
    
    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline where_clauses::where_lte<TColumn> lte(TColumn c, typename TColumn::value_type v) {
        return where_clauses::where_lte<TColumn>(c, v);
    }
    
    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline where_clauses::where_gte<TColumn> gte(TColumn c, typename TColumn::value_type v) {
        return where_clauses::where_gte<TColumn>(c, v);
    }
    
    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline where_clauses::where_contains<TColumn> contains(TColumn c, typename TColumn::value_type v) {
        return where_clauses::where_contains<TColumn>(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline auto operator==(TColumn c, typename TColumn::value_type v) -> decltype(fp::eq(c, v)) {
        return fp::eq(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline auto operator!=(TColumn c, typename TColumn::value_type v) -> decltype(fp::neq(c, v)) {
        return fp::neq(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline auto operator<(TColumn c, typename TColumn::value_type v) -> decltype(fp::lt(c, v)) {
        return fp::lt(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline auto operator>(TColumn c, typename TColumn::value_type v) -> decltype(fp::gt(c, v)) {
        return fp::gt(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline auto operator<=(TColumn c, typename TColumn::value_type v) -> decltype(fp::lte(c, v)) {
        return fp::lte(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline auto operator>=(TColumn c, typename TColumn::value_type v) -> decltype(fp::gte(c, v)) {
        return fp::gte(c, v);
    }

    template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn>>>
    inline auto operator%(TColumn c, typename TColumn::value_type v) -> decltype(fp::contains(c, v)) {
        return fp::contains(c, v);
    }
}

#endif