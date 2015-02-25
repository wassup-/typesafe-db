#include "include/meta.hpp"
#include "include/column.hpp"
#include "include/field.hpp"
#include "include/table.hpp"
#include <type_traits>

namespace geo
{

namespace _strings
{

	constexpr static char const cities[] = "cities";
	constexpr static char const countries[] = "countries";
	constexpr static char const provinces[] = "provinces";
	constexpr static char const cities_id[] = "id";
	constexpr static char const cities_name[] = "name";
	constexpr static char const cities_latitude[] = "latitude";
	constexpr static char const cities_longitude[] = "longitude";
	constexpr static char const cities_province[] = "province";
	constexpr static char const countries_id[] = "id";
	constexpr static char const countries_name[] = "name";
	constexpr static char const countries_latitude[] = "latitude";
	constexpr static char const countries_longitude[] = "longitude";
	constexpr static char const provinces_id[] = "id";
	constexpr static char const provinces_name[] = "name";
	constexpr static char const provinces_latitude[] = "latitude";
	constexpr static char const provinces_longitude[] = "longitude";
	constexpr static char const provinces_country[] = "country";

}

struct cities : fp::table<cities>
{
	constexpr static const char* _name() noexcept { return _strings::cities; }

	constexpr static fp::column<cities, _strings::cities_id, fp::field<int>> id = { };
	constexpr static fp::column<cities, _strings::cities_name, fp::field<std::string>> name = { };
	constexpr static fp::column<cities, _strings::cities_latitude, fp::field<double>> latitude = { };
	constexpr static fp::column<cities, _strings::cities_longitude, fp::field<double>> longitude = { };
	constexpr static fp::column<cities, _strings::cities_province, fp::field<int>> province = { };

	using columns = meta::transform<meta::list<decltype(id), decltype(name), decltype(latitude), decltype(longitude), decltype(province)>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;

	using primary_keys = meta::transform<meta::list<decltype(id)>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
	using unique_keys  = meta::transform<meta::list<>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
	using index_keys   = meta::transform<meta::list<decltype(province)>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
};

struct countries : fp::table<countries>
{
	constexpr static const char* _name() noexcept { return _strings::countries; }

	constexpr static fp::column<countries, _strings::countries_id, fp::field<int>> id = { };
	constexpr static fp::column<countries, _strings::countries_name, fp::field<std::string>> name = { };
	constexpr static fp::column<countries, _strings::countries_latitude, fp::field<double>> latitude = { };
	constexpr static fp::column<countries, _strings::countries_longitude, fp::field<double>> longitude = { };

	using columns = meta::transform<meta::list<decltype(id), decltype(name), decltype(latitude), decltype(longitude)>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;

	using primary_keys = meta::transform<meta::list<decltype(id)>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
	using unique_keys  = meta::transform<meta::list<>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
	using index_keys   = meta::transform<meta::list<>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
};

struct provinces : fp::table<provinces>
{
	constexpr static const char* _name() noexcept { return _strings::provinces; }

	constexpr static fp::column<provinces, _strings::provinces_id, fp::field<int>> id = { };
	constexpr static fp::column<provinces, _strings::provinces_name, fp::field<std::string>> name = { };
	constexpr static fp::column<provinces, _strings::provinces_latitude, fp::field<double>> latitude = { };
	constexpr static fp::column<provinces, _strings::provinces_longitude, fp::field<double>> longitude = { };
	constexpr static fp::column<provinces, _strings::provinces_country, fp::field<int>> country = { };

	using columns = meta::transform<meta::list<decltype(id), decltype(name), decltype(latitude), decltype(longitude), decltype(country)>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;

	using primary_keys = meta::transform<meta::list<decltype(id)>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
	using unique_keys  = meta::transform<meta::list<>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
	using index_keys   = meta::transform<meta::list<decltype(country)>, meta::compose<meta::quote<std::remove_cv>, meta::quote<std::remove_reference>>>;
};

}

