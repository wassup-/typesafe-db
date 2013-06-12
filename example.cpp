#include "include/record.hpp"               // for fp::get
#include "include/field.hpp"                // for fp::field
#include "include/mysql/basic_engine.hpp"   // for fp::mysql::basic_engine

#include "include/table.hpp"                // for fp::table
#include "include/primary_key.hpp"          // for fp::primary_key
#include "include/ordered_query.hpp"        // for fp::order
#include "include/select_query.hpp"         // for fp::select
#include "include/type_traits.hpp"          // for fp::Invoke
#include "include/where_query.hpp"          // for fp::where
#include "include/limit_query.hpp"          // for fp::limit, fp::where
#include "include/update_query.hpp"         // for fp::update
#include "include/where_select_query.hpp"   // for fp::query, fp::where, fp::select
#include "include/where_update_query.hpp"
#include "include/is_contained_value.hpp"

#include <iostream>                     // for std::cout
#include <string>                       // for std::string
#include <vector>                       // for std::vector

namespace geo {
    namespace db {
        namespace impl {

            CONSTEXPR static char const * city_table = "geo_city";
            CONSTEXPR static char const * province_table = "geo_province";
            CONSTEXPR static char const * country_table = "geo_country";

            CONSTEXPR static char const * city_fields[] = {
                "id",
                "alpha",
                "name",
                "code",
                "longitude",
                "latitude",
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
            using id = fp::field<city, 0, int>;
            using alpha = fp::field<city, 1, std::string>;
            using name = fp::field<city, 2, std::string>;
            using code = fp::field<city, 3, std::string>;
            using longitude = fp::field<city, 4, double>;
            using latitude = fp::field<city, 5, double>;

            struct table {
                using primary_key = fp::primary_key<city::id>;
                using type = fp::table<city::id, city::alpha, city::name, city::code, city::longitude, city::latitude>;

                CONSTEXPR static char const * name = impl::city_table;
            };

            struct record {
                using type = fp::Invoke<typename city::table::type::record>;
            };

            template<int I>
                    struct field {
                CONSTEXPR static char const * name = impl::city_fields[I];
            };
        };

        struct province {
            using id = fp::field<province, 0, int>;
            using name = fp::field<province, 1, std::string>;
            using longitude = fp::field<province, 2, double>;
            using latitude = fp::field<province, 3, double>;

            struct table {
                using primary_key = fp::primary_key<province::id>;
                using type = fp::table<province::id, province::name, province::longitude, province::latitude>;

                CONSTEXPR static char const * name = impl::province_table;
            };

            struct record {
                using type = fp::Invoke<typename province::table::type::record>;
            };

            template<int I>
                    struct field {
                CONSTEXPR static char const * name = impl::province_fields[I];
            };
        };

        struct country {
            using id = fp::field<country, 0, int>;
            using name = fp::field<country, 1, std::string>;
            using longitude = fp::field<country, 2, double>;
            using latitude = fp::field<country, 3, double>;

            struct table {
                //using primary_key = fp::primary_key<country::id>;
                using type = fp::table<country::id, country::name, country::longitude, country::latitude>;

                CONSTEXPR static char const * name = impl::country_table;
            };

            struct record {
                using type = fp::Invoke<typename country::table::type::record>;
            };

            template<int I>
                    struct field {
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
    
    std::cout << "city has PK: " << fp::has_primary_key<geo::db::city::table>::value << std::endl;
    std::cout << "province has PK: " << fp::has_primary_key<geo::db::province::table>::value << std::endl;
    std::cout << "country has PK: " << fp::has_primary_key<geo::db::country::table>::value << std::endl;
    
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