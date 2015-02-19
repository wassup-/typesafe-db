namespace geo
{
namespace _strings
{
constexpr static char const cities[] = "cities";
constexpr static char const cities_id[] = "id";
constexpr static char const cities_name[] = "name";
constexpr static char const cities_latitude[] = "latitude";
constexpr static char const cities_longitude[] = "longitude";
constexpr static char const cities_province[] = "province";
constexpr static char const countries[] = "countries";
constexpr static char const countries_id[] = "id";
constexpr static char const countries_name[] = "name";
constexpr static char const countries_latitude[] = "latitude";
constexpr static char const countries_longitude[] = "longitude";
constexpr static char const provinces[] = "provinces";
constexpr static char const provinces_id[] = "id";
constexpr static char const provinces_name[] = "name";
constexpr static char const provinces_latitude[] = "latitude";
constexpr static char const provinces_longitude[] = "longitude";
constexpr static char const provinces_country[] = "country";
}
struct cities
{
constexpr static fp::table<cities, _strings::cities> table = { };
constexpr static fp::column<cities, _strings::cities_id, fp::field<int>> id = { };
constexpr static fp::column<cities, _strings::cities_name, fp::field<std::string>> name = { };
constexpr static fp::column<cities, _strings::cities_latitude, fp::field<double>> latitude = { };
constexpr static fp::column<cities, _strings::cities_longitude, fp::field<double>> longitude = { };
constexpr static fp::column<cities, _strings::cities_province, fp::field<int>> province = { };
using primary_key = mpl::identity<fp::Unqualified<decltype(id)>>;
using unique_key = mpl::identity<>;
using index_key = mpl::identity<fp::Unqualified<decltype(province)>>;
};
struct countries
{
constexpr static fp::table<countries, _strings::countries> table = { };
constexpr static fp::column<countries, _strings::countries_id, fp::field<int>> id = { };
constexpr static fp::column<countries, _strings::countries_name, fp::field<std::string>> name = { };
constexpr static fp::column<countries, _strings::countries_latitude, fp::field<double>> latitude = { };
constexpr static fp::column<countries, _strings::countries_longitude, fp::field<double>> longitude = { };
using primary_key = mpl::identity<fp::Unqualified<decltype(id)>>;
using unique_key = mpl::identity<>;
using index_key = mpl::identity<>;
};
struct provinces
{
constexpr static fp::table<provinces, _strings::provinces> table = { };
constexpr static fp::column<provinces, _strings::provinces_id, fp::field<int>> id = { };
constexpr static fp::column<provinces, _strings::provinces_name, fp::field<std::string>> name = { };
constexpr static fp::column<provinces, _strings::provinces_latitude, fp::field<double>> latitude = { };
constexpr static fp::column<provinces, _strings::provinces_longitude, fp::field<double>> longitude = { };
constexpr static fp::column<provinces, _strings::provinces_country, fp::field<int>> country = { };
using primary_key = mpl::identity<fp::Unqualified<decltype(id)>>;
using unique_key = mpl::identity<>;
using index_key = mpl::identity<fp::Unqualified<decltype(country)>>;
};
}
