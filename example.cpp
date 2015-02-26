#include "include/mysql/basic_engine.hpp"   // for fp::mysql::basic_engine

#include "include/ordered_query.hpp"        // for fp::order
#include "include/select_query.hpp"         // for fp::select
#include "include/type_traits.hpp"          // for fp::Invoke
#include "include/where_query.hpp"          // for fp::where
#include "include/limit_query.hpp"          // for fp::limit, fp::where
#include "include/update_query.hpp"         // for fp::update
#include "include/where_select_query.hpp"   // for fp::query, fp::where, fp::select
#include "include/where_update_query.hpp"   // for fp::query, fp::update, fp::where

#include <iostream>                         // for std::cout
#include <string>                           // for std::string, std::to_string

#include "geo.hpp"                          // for geo

constexpr auto sq1 = fp::select(
  geo::cities::name,
  geo::cities::latitude,
  geo::cities::longitude
);
auto wq1 = fp::where(
  fp::contains(geo::cities::name, "ken")
);
auto uq1 = fp::update(
  fp::set(geo::cities::latitude, 1),
  fp::mul(geo::cities::longitude, geo::cities::longitude)
);
auto wuq1 = uq1 + wq1;

template<typename T>
void pretty_print(T)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main(int argc, char ** argv) {
  using std::get;
  using std::to_string;

  const char *db_host = "localhost";
  const char *db_user = "root";
  const char *db_pass = nullptr;
  const char *db_dbase = nullptr;

  switch(argc)
  {
    case 5: {
      db_pass = argv[4];
      // fall-through
    }
    case 4: {
      db_user = argv[3];
      // fall-through
    }
    case 3: {
      db_dbase = argv[2];
      // fall-through
    }
    case 2: {
      db_host = argv[1];
      // fall-through
    }
    default: {
      break;
    }
  }

  fp::mysql::basic_engine engine(db_host, db_user, db_pass, db_dbase);
  fp::mysql::basic_formatter formatter { };

  auto qry = fp::limit(fp::order(sq1 + wq1, geo::cities::name, fp::ascending), 10);
  auto res = fp::query(engine, qry);

  std::cout << "[Query]" << std::endl << to_string(qry, formatter) << std::endl;
  std::cout << "[Results]" << std::endl << res.size() << std::endl;
  std::cout << "----------" << std::endl;
  for (const auto& cur : res) {
    std::cout << "Alpha: " << get(cur, geo::cities::name) << std::endl;
    std::cout << "Longitude: " << get(cur, geo::cities::longitude) << std::endl;
    std::cout << "Latitude: " << get(cur, geo::cities::latitude) << std::endl;
    std::cout << std::endl;
  }
  std::cout << "----------" << std::endl;

  return 0;
}
