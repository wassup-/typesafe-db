/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UPDATE_QUERY_IMPL_HPP
#define _UPDATE_QUERY_IMPL_HPP

#include "../column.hpp"
#include "../stringutil.hpp"

#include <string>       // for std::string, std::to_string

namespace fp
{

namespace impl
{

template<typename...>
struct update_query_impl;

namespace update_modifiers
{

template<typename, typename>
struct modifier;

}

template<typename>
struct is_update_modifier
: std::false_type { };

template<typename TColumn, typename TGetter>
struct is_update_modifier<update_modifiers::modifier<TColumn, TGetter>>
: is_column<TColumn> { };

template<typename... TUpdate>
struct update_query_impl
{
  template<typename TDescriptor, typename Formatter>
  static std::string build_update_query(const TUpdate&... modifiers, Formatter& formatter)
  {
    return stringutils::concatenate(
      "UPDATE ",
      formatter.to_string(TDescriptor{}),
      " SET ",
      stringutils::implode(", ", formatter.to_string(modifiers)...)
    );
  }
};

template<typename...>
struct update_applier;

template<typename H, typename... T>
struct update_applier<H, T...>
{
protected:
  H head_;
  update_applier<T...> tail_;

public:
  update_applier(H h, T... t)
  : head_(h)
  , tail_(t...)
  { }

  template<typename TMapping, typename TRecord>
  void operator()(const TMapping& mapping, TRecord& rec) const
  {
    head_(mapping, rec);
    tail_(mapping, rec);
  }
};

template<typename H>
struct update_applier<H>
{
protected:
  H head_;

public:
  update_applier(H h)
  : head_(h)
  { }

  template<typename TMapping, typename TRecord>
  void operator()(const TMapping& mapping, TRecord& rec) const
  {
    head_(mapping, rec);
  }
};

namespace update_modifiers
{

  template<typename TColumn>
  struct column_getter
  {
  public:
    using descriptor_type = DescriptorOf<TColumn>;
    using value_type = typename TColumn::value_type;

  public:
    column_getter(TColumn col)
    : column_(col)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, column_);
    }

    template<typename Formatter>
    friend std::string to_string(const column_getter& self, Formatter& formatter)
    {
      return formatter.to_string(self.column_);
    }

  private:
    TColumn column_;
  };

  template<typename TLeft, typename TRight>
  struct column_add
  {
  public:
    using descriptor_type = DescriptorOf<TRight>;
    using value_type = typename TRight::value_type;

  public:
    constexpr column_add(TLeft l, TRight r)
    : left_(l)
    , right_(r)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, left_) + get(mapping, rec, right_);
    }

    template<typename Formatter>
    friend std::string to_string(const column_add& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.left_), " + ", formatter.to_string(self.right_));
    }

  private:
    TLeft left_;
    TRight right_;
  };

  template<typename TLeft, typename TRight>
  struct column_sub
  {
  public:
    using descriptor_type = DescriptorOf<TRight>;
    using value_type = typename TRight::value_type;

  public:
    constexpr column_sub(TLeft l, TRight r)
    : left_(l)
    , right_(r)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, left_) - get(mapping, rec, right_);
    }

    template<typename Formatter>
    friend std::string to_string(const column_sub& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.left_), " - ", formatter.to_string(self.right_));
    }

  private:
    TLeft left_;
    TRight right_;
  };

  template<typename TLeft, typename TRight>
  struct column_mul
  {
  public:
    using descriptor_type = DescriptorOf<TRight>;
    using value_type = typename TRight::value_type;

  public:
    constexpr column_mul(TLeft l, TRight r)
    : left_(l)
    , right_(r)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, left_) * get(mapping, rec, right_);
    }

    template<typename Formatter>
    friend std::string to_string(const column_mul& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.left_), " * ", formatter.to_string(self.right_));
    }

  private:
    TLeft left_;
    TRight right_;
  };

  template<typename TLeft, typename TRight>
  struct column_div
  {
  public:
    using descriptor_type = DescriptorOf<TRight>;
    using value_type = typename TRight::value_type;

  public:
    constexpr column_div(TLeft l, TRight r)
    : left_(l)
    , right_(r)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, left_) / get(mapping, rec, right_);
    }

    template<typename Formatter>
    friend std::string to_string(const column_div& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.left_), " / ", formatter.to_string(self.right_));
    }

  private:
    TLeft left_;
    TRight right_;
  };

  template<typename TColumn>
  struct value_getter
  {
  public:
    using descriptor_type = DescriptorOf<TColumn>;
    using value_type = typename TColumn::value_type;

  protected:
    TColumn column_;
    value_type value_;

  public:
    constexpr value_getter(TColumn c, value_type v)
    : column_(c)
    , value_(v)
    { }

    template<typename TMapping, typename TRecord>
    constexpr const value_type& operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return value_;
    }

    template<typename Formatter>
    friend std::string to_string(const value_getter& self, Formatter& formatter)
    {
      return formatter.to_string(self.value_);
    }
  };

  template<typename TColumn>
  struct value_add
  {
  public:
    using descriptor_type = DescriptorOf<TColumn>;
    using value_type = typename TColumn::value_type;

  public:
    constexpr value_add(TColumn c, value_type v)
    : column_(c)
    , value_(v)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, column_) + value_;
    }

    template<typename Formatter>
    friend std::string to_string(const value_add& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.column_), " + ", formatter.to_string(self.value_));
    }

  private:
    TColumn column_;
    value_type value_;
  };

  template<typename TColumn>
  struct value_sub
  {
  public:
    using descriptor_type = DescriptorOf<TColumn>;
    using value_type = typename TColumn::value_type;

  public:
    constexpr value_sub(TColumn c, value_type v)
    : column_(c)
    , value_(v)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, column_) - value_;
    }

    template<typename Formatter>
    friend std::string to_string(const value_sub& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.column_), " - ", formatter.to_string(self.value_));
    }

  private:
    TColumn column_;
    value_type value_;
  };

  template<typename TColumn>
  struct value_mul
  {
  public:
    using descriptor_type = DescriptorOf<TColumn>;
    using value_type = typename TColumn::value_type;

  public:
    constexpr value_mul(TColumn c, value_type v)
    : column_(c)
    , value_(v)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, column_) * value_;
    }

    template<typename Formatter>
    friend std::string to_string(const value_mul& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.column_), " * ", formatter.to_string(self.value_));
    }

  private:
    TColumn column_;
    value_type value_;
  };

  template<typename TColumn>
  struct value_div
  {
  public:
    using descriptor_type = DescriptorOf<TColumn>;
    using value_type = typename TColumn::value_type;

  public:
    constexpr value_div(TColumn c, value_type v)
    : column_(c)
    , value_(v)
    { }

    template<typename TMapping, typename TRecord>
    constexpr value_type operator()(const TMapping& mapping, const TRecord& rec) const
    {
      return get(mapping, rec, column_) / value_;
    }

    template<typename Formatter>
    friend std::string to_string(const value_div& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.column_), " / ", formatter.to_string(self.value_));
    }

  private:
    TColumn column_;
    value_type value_;
  };

  template<typename TColumn, typename TModifier>
  struct modifier
  {
  public:
    using descriptor_type = DescriptorOf<TColumn>;
    using value_type = typename TColumn::value_type;

  protected:
    TColumn column_;
    TModifier self_;

  public:
    constexpr modifier(TColumn c, TModifier m)
    : column_(c)
    , self_(m)
    { }

    template<typename TMapping, typename TRecord>
    void operator()(const TMapping& mapping, TRecord& rec) const
    {
      set(mapping, rec, column_, self_(mapping, rec));
    }

    template<typename Formatter>
    friend std::string to_string(const modifier& self, Formatter& formatter)
    {
      return stringutils::concatenate(formatter.to_string(self.column_), " = (", formatter.to_string(self.self_), ")");
    }
  };
}

}

}

#endif
