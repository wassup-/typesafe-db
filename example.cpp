#include "src/record.hpp"               // for fp::get
#include "src/field.hpp"                // for fp::field
#include "src/mysql/basic_engine.hpp"   // for fp::mysql::basic_engine

#include "src/table.hpp"                // for fp::table
#include "src/primary_key.hpp"          // for fp::primary_key
#include "src/ordered_query.hpp"        // for fp::order
#include "src/select_query.hpp"         // for fp::select
#include "src/where_query.hpp"          // for fp::where
#include "src/limit_query.hpp"          // for fp::limit, fp::where
#include "src/update_query.hpp"         // for fp::update
#include "src/where_select_query.hpp"   // for fp::query, fp::where, fp::select
#include "src/where_update_query.hpp"   // for fp::query, fp::where, fp::update

#include <iostream>                     // for std::cout
#include <string>                       // for std::string
#include <vector>                       // for std::vector

namespace geo {
    namespace db {
        namespace impl {

            CONSTEXPR static char const * city_fields[] = {
                "id",
                "alpha",
                "name",
                "code",
                "longitude",
                "latitude",
                "fullname",
            };

            CONSTEXPR static char const * province_fields[] = {
                "id",
                "name",
                "longitude",
                "latitude",
            };

            CONSTEXPR static char const * country_fields[] = {
                "id",
                "name",
                "longitude",
                "latitude",
            };
        }

        struct city {
            typedef fp::field<city, 0, int> id;
            typedef fp::field<city, 1, std::string> alpha;
            typedef fp::field<city, 2, std::string> name;
            typedef fp::field<city, 3, std::string> code;
            typedef fp::field<city, 4, double> longitude;
            typedef fp::field<city, 5, double> latitude;

            struct table {
                using type = fp::table<city::id, city::alpha, city::name, city::code, city::longitude, city::latitude>;
                CONSTEXPR static char const * name = "geo_city";

                using primary_key = fp::primary_key<city::id>;
            };

            struct record {
                using type = typename city::table::type::record::type;
            };

            template<int I> struct field {
                CONSTEXPR static char const * name = impl::city_fields[I];
            };
        };

        struct province {
            typedef fp::field<province, 0, int> id;
            typedef fp::field<province, 1, std::string> name;
            typedef fp::field<province, 2, double> longitude;
            typedef fp::field<province, 3, double> latitude;

            struct table {
                using type = fp::table<province::id, province::name, province::longitude, province::latitude>;
                CONSTEXPR static char const * name = "geo_province";

                using primary_key = fp::primary_key<province::id>;
            };

            struct record {
                using type = typename province::table::type::record;
            };

            template<int I> struct field {
                CONSTEXPR static char const * name = impl::province_fields[I];
            };
        };

        struct country {
            typedef fp::field<country, 0, int> id;
            typedef fp::field<country, 1, std::string> name;
            typedef fp::field<country, 2, double> longitude;
            typedef fp::field<country, 3, double> latitude;

            struct table {
                using type = fp::table<country::id, country::name, country::longitude, country::latitude>;
                CONSTEXPR static char const * name = "geo_country";

                using primary_key = fp::primary_key<country::id>;
            };

            struct record {
                using type = typename country::table::type::record;
            };

            template<int I> struct field {
                CONSTEXPR static char const * name = impl::country_fields[I];
            };
        };
    }
}

CONSTEXPR static char const * GEO_USER = "test";
CONSTEXPR static char const * GEO_PASSWD = "testpw";
CONSTEXPR static char const * GEO_DB = "shared";

auto sq1 = fp::select(geo::db::city::alpha(), geo::db::city::latitude(), geo::db::city::longitude());
auto wq1 = fp::where(fp::contains(geo::db::city::name(), "ken"));
auto uq1 = fp::update(fp::set(geo::db::city::latitude(), 1), fp::mul(geo::db::city::longitude(), geo::db::city::longitude()));
auto wuq1 = uq1 + wq1;

int main(int argc, char ** argv) {
    using fp::get;
    using fp::to_string;

    fp::mysql::basic_engine engine(0, GEO_USER, GEO_PASSWD, GEO_DB);

    auto qry = fp::limit(fp::order(sq1 + wq1, geo::db::city::alpha(), fp::ascending), 10);
    auto res = fp::query(engine, qry);
    std::cout << "[Query]" << std::endl << to_string(qry) << std::endl;
    std::cout << "[Results]" << std::endl << res.size() << std::endl;
    std::cout << "----------" << std::endl;
    for (auto && cur : res) {
        std::cout << "Alpha: " << get<geo::db::city::alpha > (cur) << std::endl;
        std::cout << "Longitude: " << get<geo::db::city::longitude > (cur) << std::endl;
        std::cout << "Latitude: " << get<geo::db::city::latitude > (cur) << std::endl;
        std::cout << std::endl;
    }
    std::cout << "----------" << std::endl;

    return 0;
}