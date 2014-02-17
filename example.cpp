#include "include/mysql/basic_engine.hpp"   // for fp::mysql::basic_engine

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
#include <string>                       // for std::string, std::to_string

#include "database_geo.hpp"             // for geo::db

constexpr static const char GEO_DB[] = "shared";
constexpr static const char GEO_USER[] = "shared_read";
constexpr static const char GEO_PASSWD[] = "shared_read";


constexpr auto sq1 = fp::select(
    geo::db::city::alpha,
    geo::db::city::latitude,
    geo::db::city::longitude
);
auto wq1 = fp::where(
    fp::contains(geo::db::city::name, "ken")
);
auto uq1 = fp::update(
    fp::set(geo::db::city::latitude, 1),
    fp::mul(geo::db::city::longitude, geo::db::city::longitude)
);
auto wuq1 = uq1 + wq1;

int main(int argc, char ** argv) {
    using std::get;
    using std::to_string;

    const char * db_host = nullptr;
    if(argc > 1) {
        db_host = argv[1];
    }

    fp::mysql::basic_engine engine(db_host, GEO_USER, GEO_PASSWD, GEO_DB);

    auto qry = fp::limit(fp::order(sq1 + wq1, geo::db::city::alpha, fp::ascending), 10);
    auto res = fp::query(engine, qry);

    std::cout << "[Query]" << std::endl << to_string(qry) << std::endl;
    std::cout << "[Results]" << std::endl << res.size() << std::endl;
    std::cout << "----------" << std::endl;
    for (const auto& cur : res) {
        std::cout << "Alpha: " << get(cur, geo::db::city::alpha) << std::endl;
        std::cout << "Longitude: " << get(cur, geo::db::city::longitude) << std::endl;
        std::cout << "Latitude: " << get(cur, geo::db::city::latitude) << std::endl;
        std::cout << std::endl;
    }
    std::cout << "----------" << std::endl;

    return 0;
}