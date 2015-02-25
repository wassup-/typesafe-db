/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _FIELD_HPP
#define _FIELD_HPP

#include "type_traits.hpp"      // for fp::Bool

namespace fp
{

template<typename /* Type */>
struct field;

template<typename, typename>
struct lazy_field;

template<typename>
struct is_field
: meta::bool_<false>
{ };

template<typename Type>
struct is_field<field<Type> >
: meta::bool_<true>
{ };

template<typename Foreign, typename Ref>
struct is_field<lazy_field<Foreign, Ref> >
: meta::bool_<true>
{ };

template<typename Type>
struct field
{
  using this_type = field;
  using value_type = typename std::decay<Type>::type;
};

template<typename Foreign, typename Ref>
struct lazy_field
{
  using this_type = lazy_field;
  using value_type = typename Ref::descriptor_type;
};

template<typename>
struct field_traits;

template<typename Type>
struct field_traits<field<Type> >
{
  using value_type = typename field<Type>::value_type;
};

template<typename Foreign, typename Ref>
struct field_traits<lazy_field<Foreign, Ref> >
{
  using value_type = typename lazy_field<Foreign, Ref>::value_type;
};

}

#endif
