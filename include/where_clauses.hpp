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

namespace fp
{

namespace where_clauses
{

template<typename> struct where_eq;
template<typename> struct where_neq;
template<typename> struct where_lt;
template<typename> struct where_gt;
template<typename> struct where_lte;
template<typename> struct where_gte;
template<typename> struct where_contains;
template<typename, typename> struct where_or;
template<typename, typename> struct where_and;

} // namespace where_clauses

namespace impl
{

template<typename>
struct is_where_clause : meta::bool_<false> { };

template<typename TColumn>
struct is_where_clause<where_clauses::where_eq<TColumn> > : meta::bool_<true> { };
template<typename TColumn>
struct is_where_clause<where_clauses::where_neq<TColumn> > : meta::bool_<true> { };
template<typename TColumn>
struct is_where_clause<where_clauses::where_lt<TColumn> > : meta::bool_<true> { };
template<typename TColumn>
struct is_where_clause<where_clauses::where_gt<TColumn> > : meta::bool_<true> { };
template<typename TColumn>
struct is_where_clause<where_clauses::where_lte<TColumn> > : meta::bool_<true> { };
template<typename TColumn>
struct is_where_clause<where_clauses::where_gte<TColumn> > : meta::bool_<true> { };
template<typename TColumn>
struct is_where_clause<where_clauses::where_contains<TColumn> > : meta::bool_<true> { };
template<typename TLeft, typename TRight>
struct is_where_clause<where_clauses::where_or<TLeft, TRight> > : meta::bool_<true> { };
template<typename TLeft, typename TRight>
struct is_where_clause<where_clauses::where_and<TLeft, TRight> > : meta::bool_<true> { };

} // namespace impl

namespace where_clauses
{

#define DECLARE_BASIC_CLAUSE(name, local_op, remote_op) \
  template<typename TColumn> \
  struct where_ ## name \
  { \
  public: \
    using this_type = where_ ## name; \
    using descriptor_type = DescriptorOf<TColumn>; \
    using value_type = typename TColumn::value_type; \
 \
  protected: \
    TColumn column_; \
    typename TColumn::value_type value_; \
 \
  public: \
    where_ ## name(TColumn col, value_type v) \
    : column_(col) \
    , value_(std::move(v)) \
    { } \
 \
    friend void swap(this_type& l, this_type& r) \
    { \
      using std::swap; \
      swap(l.column_, r.column_); \
      swap(l.value_, r.value_); \
    } \
 \
    template<typename TRecord> \
    bool operator()(const TRecord& r) const \
    { \
      return (get<TColumn>(r) local_op value_); \
    } \
 \
    template<typename Formatter> \
    friend std::string to_string(const this_type& self, Formatter& formatter) \
    { \
      return stringutils::concatenate("(", formatter.to_string(self.column_), " " #remote_op " ", formatter.to_string(self.value_), ")"); \
    } \
  }

DECLARE_BASIC_CLAUSE(eq, ==, =);
DECLARE_BASIC_CLAUSE(neq, !=, !=);
DECLARE_BASIC_CLAUSE(lt, <, <);
DECLARE_BASIC_CLAUSE(gt, >, >);
DECLARE_BASIC_CLAUSE(lte, <=, <=);
DECLARE_BASIC_CLAUSE(gte, >=, >=);

template<typename TColumn>
struct where_contains
{
public:
  using descriptor_type = DescriptorOf<TColumn>;

protected:
  TColumn column_;
  typename TColumn::value_type value_;

public:
  where_contains(TColumn col, typename TColumn::value_type v)
  : column_(col)
  , value_(std::move(v))
  { }

  friend void swap(where_contains& l, where_contains& r)
  {
    using std::swap;
    swap(l.column_, r.column_);
    swap(l.value_, r.value_);
  }

  template<typename TRecord>
  bool operator()(const TRecord& r) const
  {
    return (TColumn::type::npos != get<TColumn>(r).find(value_));
  }

  template<typename Formatter>
  friend std::string to_string(const where_contains& self, Formatter& formatter)
  {
    return stringutils::concatenate("(", formatter.to_string(self.column_), " LIKE \"%", formatter.to_string(self.value_), "%\")");
  }
};

template<typename L, typename R>
struct where_or
{
public:
  using this_type = where_or<L, R>;

protected:
  L left_;
  R right_;

public:
  where_or(L lhs, R rhs)
  : left_(std::move(lhs))
  , right_(std::move(rhs))
  { }

  friend void swap(where_or& l, where_or& r)
  {
    using std::swap;
    swap(l.left_, r.left_);
    swap(l.right_, r.right_);
  }

  template<typename TRecord>
  bool operator()(const TRecord& r) const
  {
    return (left_(r) || right_(r));
  }

  template<typename Formatter>
  friend std::string to_string(const where_or& self, Formatter& formatter)
  {
    return stringutils::concatenate("(", formatter.to_string(self.left_), " OR ", formatter.to_string(self.right_), ")");
  }
};

template<typename L, typename R>
struct where_and
{
public:
  using this_type = where_and<L, R>;

protected:
  L left_;
  R right_;

public:
  where_and(L lhs, R rhs)
  : left_(std::move(lhs))
  , right_(std::move(rhs))
  { }

  friend void swap(where_and& l, where_and& r)
  {
    using std::swap;
    swap(l.left_, r.left_);
    swap(l.right_, r.right_);
  }

  template<typename TRecord>
  bool operator()(const TRecord& r) const
  {
    return (left_(r) && right_(r));
  }

  template<typename Formatter>
  friend std::string to_string(const where_and& self, Formatter& formatter)
  {
    return stringutils::concatenate("(", formatter.to_string(self.left_), " AND ", formatter.to_string(self.right_), ")");
  }
};

} // namespace where_clauses

template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn> > >
inline where_clauses::where_eq<TColumn> eq(TColumn c, typename TColumn::value_type v)
{ return { c, v }; }

template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn> > >
inline where_clauses::where_neq<TColumn> neq(TColumn c, typename TColumn::value_type v)
{ return { c, v }; }

template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn> > >
inline where_clauses::where_lt<TColumn> lt(TColumn c, typename TColumn::value_type v)
{ return { c, v }; }

template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn> > >
inline where_clauses::where_gt<TColumn> gt(TColumn c, typename TColumn::value_type v)
{ return { c, v }; }

template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn> > >
inline where_clauses::where_lte<TColumn> lte(TColumn c, typename TColumn::value_type v)
{ return { c, v }; }

template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn> > >
inline where_clauses::where_gte<TColumn> gte(TColumn c, typename TColumn::value_type v)
{ return { c, v }; }

template<typename TColumn, typename = mpl::enable_if_t<is_column<TColumn> > >
inline where_clauses::where_contains<TColumn> contains(TColumn c, typename TColumn::value_type v)
{ return { c, v }; }

#define AUTO_RETURNS(x) -> decltype(x) { return x; }

template<typename TColumn>
inline auto operator==(TColumn c, typename TColumn::value_type v)
AUTO_RETURNS(eq(c, v))

template<typename TColumn>
inline auto operator!=(TColumn c, typename TColumn::value_type v)
AUTO_RETURNS(neq(c, v))

template<typename TColumn>
inline auto operator<(TColumn c, typename TColumn::value_type v)
AUTO_RETURNS(lt(c, v))

template<typename TColumn>
inline auto operator>(TColumn c, typename TColumn::value_type v)
AUTO_RETURNS(gt(c, v))

template<typename TColumn>
inline auto operator<=(TColumn c, typename TColumn::value_type v)
AUTO_RETURNS(lte(c, v))

template<typename TColumn>
inline auto operator>=(TColumn c, typename TColumn::value_type v)
AUTO_RETURNS(gte(c, v))

template<typename TColumn>
inline auto operator%(TColumn c, typename TColumn::value_type v)
AUTO_RETURNS(contains(c, v))

#undef AUTO_RETURNS

} // namespace fp

#endif
