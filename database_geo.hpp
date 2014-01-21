#ifndef DB_GEO_HPP_
#define DB_GEO_HPP_

#include "include/column.hpp"
#include "include/field.hpp"
#include "include/primary_key.hpp"
#include "include/table.hpp"

namespace geo { namespace db {

    namespace strings {
        constexpr static char const city[] = "geo_city";
        constexpr static char const province[] = "geo_province";
        constexpr static char const country[] = "geo_country";

        constexpr static char const id[] = "id";
        constexpr static char const alpha[] = "alpha";
        constexpr static char const name[] = "name";
        constexpr static char const code[] = "code";
        constexpr static char const longitude[] = "longitude";
        constexpr static char const latitude[] = "latitude";
    }

    struct city {

        constexpr static fp::table<city, strings::city> table = { };

        constexpr static fp::column<city, strings::id, fp::field<int>> id = { };
        constexpr static fp::column<city, strings::alpha, fp::field<char[255]>> alpha = { };
        constexpr static fp::column<city, strings::name, fp::field<std::string>> name = { };
        constexpr static fp::column<city, strings::code, fp::field<std::string>> code = { };
        constexpr static fp::column<city, strings::longitude, fp::field<double>> longitude = { };
        constexpr static fp::column<city, strings::latitude, fp::field<double>> latitude = { };

        using primary_key = mpl::identity<fp::Unqualified<decltype(id)>>;
        using unique_keys = mpl::type_sequence<fp::Unqualified<decltype(name)>>;
        using index_keys = mpl::type_sequence<fp::Unqualified<decltype(code)>>;
    };

    constexpr fp::table<city, strings::city> city::table;

    constexpr fp::column<city, strings::id, fp::field<int>> city::id;
    constexpr fp::column<city, strings::alpha, fp::field<char[255]>> city::alpha;
    constexpr fp::column<city, strings::name, fp::field<std::string>> city::name;
    constexpr fp::column<city, strings::code, fp::field<std::string>> city::code;
    constexpr fp::column<city, strings::longitude, fp::field<double>> city::longitude;
    constexpr fp::column<city, strings::latitude, fp::field<double>> city::latitude;

    struct province {

        constexpr static fp::table<province, strings::province> table = { };

        constexpr static fp::column<province, strings::id, fp::field<int>> id = { };
        constexpr static fp::column<province, strings::name, fp::field<std::string>> name = { };
        constexpr static fp::column<province, strings::longitude, fp::field<double>> longitude = { };
        constexpr static fp::column<province, strings::latitude, fp::field<double>> latitude = { };
    };

    constexpr fp::table<province, strings::province> province::table;

    constexpr fp::column<province, strings::id, fp::field<int>> province::id;
    constexpr fp::column<province, strings::name, fp::field<std::string>> province::name;
    constexpr fp::column<province, strings::longitude, fp::field<double>> province::longitude;
    constexpr fp::column<province, strings::latitude, fp::field<double>> province::latitude;

    struct country {

        constexpr static fp::table<country, strings::country> table = { };

        constexpr static fp::column<country, strings::id, fp::field<int>> id = { };
        constexpr static fp::column<country, strings::name, fp::field<std::string>> name = { };
        constexpr static fp::column<country, strings::longitude, fp::field<double>> longitude = { };
        constexpr static fp::column<country, strings::latitude, fp::field<double>> latitude = { };
    };

    constexpr fp::table<country, strings::country> country::table;

    constexpr fp::column<country, strings::id, fp::field<int>> country::id;
    constexpr fp::column<country, strings::name, fp::field<std::string>> country::name;
    constexpr fp::column<country, strings::longitude, fp::field<double>> country::longitude;
    constexpr fp::column<country, strings::latitude, fp::field<double>> country::latitude;
} }

#endif // DB_GEO_HPP_
