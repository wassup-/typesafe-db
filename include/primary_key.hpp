/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef PRIMARY_KEY_HPP_
#define PRIMARY_KEY_HPP_

namespace fp
{

struct unique_tag { };
struct primary_tag { };
struct index_tag { };
struct foreign_tag { };

template<typename Column, typename Tag>
struct key
{
public:
	constexpr key(const char* const name) noexcept
	: name_(name)
	{ }

private:
	const char* const name_;
};

template<typename LocalKey, typename RemoteKey>
struct keyref
{
public:
	constexpr keyref(const char* const name) noexcept
	: name_(name)
	{ }

private:
	const char* const name_;
};

namespace detail
{

template<typename Key>
constexpr static bool is_primary_key(const Key& key)
{ return false; }

template<typename Column>
constexpr static bool is_primary_key(const key<Column, primary_tag>& key)
{ return true; }

template<typename Key>
constexpr static bool is_unique_key(const Key& key)
{ return is_primary_key(key); }

template<typename Column>
constexpr static bool is_unique_key(const key<Column, unique_tag>& key)
{ return true; }

template<typename Key>
constexpr static bool is_index_key(const Key& key)
{ return is_unique_key(key); }

template<typename Column>
constexpr static bool is_index_key(const key<Column, index_tag>& key)
{ return true; }

template<typename Key>
constexpr static bool is_foreign_key(const Key& key)
{ return false; }

template<typename Column>
constexpr static bool is_foreign_key(const key<Column, foreign_tag>& key)
{ return true; }

} // namespace detail

template<typename Key>
constexpr static bool is_primary_key(const Key& key)
{ return detail::is_primary_key(key); }

template<typename Key>
constexpr static bool is_unique_key(const Key& key)
{ return detail::is_unique_key(key); }

template<typename Key>
constexpr static bool is_index_key(const Key& key)
{ return detail::is_index_key(key); }

template<typename Key>
constexpr static bool is_foreign_key(const Key& key)
{ return detail::is_foreign_key(key); }

} // namespace fp

#endif
