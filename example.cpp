#include "src/record.hpp"               // for fp::get
#include "src/field.hpp"                // for fp::field
#include "src/mysql_engine.hpp"         // for fp::mysql_engine

#include "src/table.hpp"                // for fp::table
#include "src/primary_key.hpp"          // for fp::primary_key
#include "src/select_query.hpp"         // for fp::select
#include "src/where_query.hpp"          // for fp::evaluate
#include "src/limit_query.hpp"          // for fp::limit, fp::evaluate
#include "src/update_query.hpp"         // for fp::update
#include "src/where_select_query.hpp"   // for fp::query, fp::evaluate, fp::select
#include "src/where_update_query.hpp"
#include "src/largest_type.hpp"
#include "src/impl/drop_values_impl.hpp"   // for fp::query, fp::evaluate, fp::update

#include <iostream>                     // for std::cout
#include <string>                       // for std::string
#include <vector>                       // for std::vector

namespace geo {
    namespace db {

        struct city {
            typedef fp::field < city, 0 > id;
            typedef fp::field < city, 1 > alpha;
            typedef fp::field < city, 2 > name;
            typedef fp::field < city, 3 > code;
            typedef fp::field < city, 4 > longitude;
            typedef fp::field < city, 5 > latitude;

            struct table {
                typedef fp::table<int, std::string, std::string, std::string, double, double> type;
                typedef typename type::types fields;
                static char const * const name;

                typedef fp::primary_key<id> primary_key;
            };

            struct record {
                typedef typename table::type::record<city>::type type;
            };

            struct fields {
                static char const * const names[];
            };

            template<int I> struct field {
                typedef typename fp::nth_type_of_seq<I, typename table::fields>::type type;
                static char const * const name;
            };
        };
        char const * const city::table::name = "geo_city";
        char const * const city::fields::names[] = {
            "id",
            "alpha",
            "name",
            "code",
            "longitude",
            "latitude",
            "fullname",
        };
        template<int I> char const * const city::field<I>::name = city::fields::names[I];

        struct province {
            typedef fp::field < province, 0 > id;
            typedef fp::field < province, 1 > name;
            typedef fp::field < province, 2 > longitude;
            typedef fp::field < province, 3 > latitude;

            struct table {
                typedef fp::table<int, std::string, double, double> type;
                typedef typename type::types fields;
                static char const * const name;

                typedef fp::primary_key<id> primary_key;
            };

            struct record {
                typedef typename table::type::record<province> type;
            };

            struct fields {
                static char const * const names[];
            };

            template<int I> struct field {
                typedef typename fp::nth_type_of_seq<I, typename table::fields>::type type;
                static char const * const name;
            };
        };
        char const * const province::table::name = "geo_province";
        char const * const province::fields::names[] = {
            "id",
            "name",
            "longitude",
            "latitude",
        };
        template<int I> char const * const province::field<I>::name = province::fields::names[I];

        struct country {
            typedef fp::field < country, 0 > id;
            typedef fp::field < country, 1 > name;
            typedef fp::field < country, 2 > longitude;
            typedef fp::field < country, 3 > latitude;

            struct table {
                typedef fp::table<int, std::string, double, double> type;
                typedef typename type::types fields;
                static char const * const name;

                typedef fp::primary_key<id> primary_key;
            };

            struct record {
                typedef typename table::type::record<country> type;
            };

            struct fields {
                static char const * const names[];
            };

            template<int I> struct field {
                typedef typename fp::nth_type_of_seq<I, typename table::fields>::type type;
                static char const * const name;
            };
        };
        char const * const country::table::name = "geo_country";
        char const * const country::fields::names[] = {
            "id",
            "name",
            "longitude",
            "latitude",
        };
        template<int I> char const * const country::field<I>::name = country::fields::names[I];
    }
}

#define GEO_USER        "test"
#define GEO_PASSWD      "testpw"
#define GEO_DB          "shared"

auto sq1 = (fp::select_query<geo::db::city > () + geo::db::city::alpha() + geo::db::city::longitude() + geo::db::city::latitude());
auto wq1 = (fp::where_query<geo::db::city > () + (geo::db::city::name() % std::string("ken")));
auto uq1 = (fp::update_query<geo::db::city > () + (geo::db::city::latitude() ^ 0) + (geo::db::city::latitude() ^ geo::db::city::longitude()));

int main(int argc, char ** argv) {
    fp::mysql_engine engine(0, GEO_USER, GEO_PASSWD, GEO_DB);
    
    auto lim = fp::limit(sq1 + wq1, 10);
    auto res = fp::query(engine, lim);
    
    std::cout << "Executed query: " << engine.last_query() << std::endl;
    std::cout << "Results: " << res.size() << std::endl;
    std::cout << "----------" << std::endl;
    for (auto const & cur : res) {
        std::cout << "Alpha: " << fp::get<geo::db::city::alpha > (cur) << std::endl;
        std::cout << "Longitude: " << fp::get<geo::db::city::longitude > (cur) << std::endl;
        std::cout << "Latitude: " << fp::get<geo::db::city::latitude > (cur) << std::endl;
        std::cout << std::endl;
    }
    std::cout << "----------" << std::endl;
    return 0;
}