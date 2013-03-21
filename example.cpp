#include "src/type_sequence.hpp"
#include "src/int_sequence.hpp"
#include "src/record.hpp"
#include "src/mysql_engine.hpp"

#include "src/table.hpp"
#include "src/primary_key.hpp"
#include "src/select_query.hpp"
#include "src/where_query.hpp"
#include "src/limit_query.hpp"
#include "src/where_select_query.hpp"

#include <iostream>
#include <string>
#include <vector>

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
                typedef fp::type_seq<int, std::string, std::string, std::string, double, double> fields;
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
        };
        template<int I> char const * const city::field<I>::name = city::fields::names[I];

        struct province {
            typedef fp::field < province, 0 > id;
            typedef fp::field < province, 1 > name;
            typedef fp::field < province, 2 > longitude;
            typedef fp::field < province, 3 > latitude;
            
            struct table {
                typedef fp::table<int, std::string, double, double> type;
                typedef fp::type_seq<int, std::string, double, double> fields;
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
                typedef fp::type_seq<int, std::string, double, double> fields;
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

#define GEO_USER "test"
#define GEO_PASSWD "testpw"
#define GEO_DB "shared"

int main(int argc, char ** argv) {
    fp::mysql_engine engine(0, GEO_USER, GEO_PASSWD, GEO_DB);
    
    auto sq1 = (fp::select_query<geo::db::city > () + geo::db::city::alpha() + geo::db::city::longitude() + geo::db::city::latitude());
    auto wq1 = (fp::where_query<geo::db::city > () + ((geo::db::city::name() % std::string("ken"))));

    auto res = fp::query(engine, sq1 + wq1);
    std::cout << "Executed query: " << engine.last_query() << std::endl;
    std::cout << "Results: " << res.size() << std::endl;
    std::cout << "----------" << std::endl;
    for (auto & cur : res) {
        std::cout << "Alpha: " << fp::get<geo::db::city::alpha > (cur) << std::endl;
        std::cout << "Longitude: " << fp::get<geo::db::city::longitude > (cur) << std::endl;
        std::cout << "Latitude: " << fp::get<geo::db::city::latitude > (cur) << std::endl;
        std::cout << std::endl;
    }
    std::cout << "----------" << std::endl;

    return 0;
}