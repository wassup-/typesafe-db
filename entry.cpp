#include "type_sequence.hpp"
#include "int_sequence.hpp"
#include "nth_type_of.hpp"
#include "nth_value_of.hpp"
#include "lexical_cast.hpp"
#include "datasource.hpp"
#include "record.hpp"
#include "logic.hpp"
#include "mysql_engine.hpp"

#include "table.hpp"
#include "primary_key.hpp"
#include "select_query.hpp"
#include "where_query.hpp"
#include "where_select_query.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace geo {
    namespace db {

        struct city {

            struct table {
                typedef fp::table<int, std::string, std::string, std::string, double, double> type;
                typedef fp::type_seq<int, std::string, std::string, std::string, double, double> fields;
                static char const * const name;
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

            typedef fp::field < city, 0 > id;
            typedef fp::field < city, 1 > alpha;
            typedef fp::field < city, 2 > name;
            typedef fp::field < city, 3 > code;
            typedef fp::field < city, 4 > longitude;
            typedef fp::field < city, 5 > latitude;

            typedef fp::primary_key<id> primary_key;
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

            struct table {
                typedef fp::table<int, std::string, double, double> type;
                typedef fp::type_seq<int, std::string, double, double> fields;
                static char const * const name;
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

            typedef fp::field < province, 0 > id;
            typedef fp::field < province, 1 > name;
            typedef fp::field < province, 2 > longitude;
            typedef fp::field < province, 3 > latitude;

            typedef fp::primary_key<id> primary_key;
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

            struct table {
                typedef fp::table<int, std::string, double, double> type;
                typedef fp::type_seq<int, std::string, double, double> fields;
                static char const * const name;
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

            typedef fp::field < country, 0 > id;
            typedef fp::field < country, 1 > name;
            typedef fp::field < country, 2 > longitude;
            typedef fp::field < country, 3 > latitude;

            typedef fp::primary_key<id> primary_key;
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

namespace fp {

    template<typename TQuery> struct limited_query {
    public:
        typedef typename TQuery::table_type table_type;
        typedef typename TQuery::record_type record_type;
        typedef typename TQuery::result_type result_type;
    protected:
        TQuery const m_query;
        int m_limit;
    public:

        limited_query(TQuery const & q, int l) : m_query(q), m_limit(l) {
        }

        bool evaluate(record_type const & rec) const {
            return fp::evaluate(rec, m_query);
        }

        result_type select(record_type const & rec) const {
            return fp::select(rec, m_query);
        }

        std::vector<result_type> apply(std::vector<record_type> const & recs) const {
            std::vector<result_type> ret(m_limit);
            for (auto const & cur : recs) {
                if (fp::evaluate(cur, m_query)) {
                    ret.push_back(fp::select(cur, m_query));
                    if (ret.size() == m_limit) {
                        break;
                    }
                }
            }
            return ret;
        }

        std::string to_string() const {
            return m_query.to_string() + " LIMIT " + lexical_cast<std::string > (m_limit);
        }
    };

    template<typename TQuery> limited_query<TQuery> limit(TQuery const & q, int l) {
        return limited_query<TQuery > (q, l);
    }

    template<typename TQuery>
    bool evaluate(typename TQuery::record_type const & r, limited_query<TQuery> const & q) {
        return q.evaluate(r);
    }

    template<typename TQuery>
    typename TQuery::result_type select(typename TQuery::record_type const & r, limited_query<TQuery> const & q) {
        return q.select(r);
    }
}

#define GEO_USER "test"
#define GEO_PASSWD "testpw"
#define GEO_DB "shared"

int main(int argc, char ** argv) {
    fp::mysql_engine engine(0, GEO_USER, GEO_PASSWD, GEO_DB);
    
    auto sq1 = (fp::select_query<geo::db::city > () + geo::db::city::alpha() + geo::db::city::longitude() + geo::db::city::latitude());
    auto wq1 = (fp::where_query<geo::db::city > () + ((geo::db::city::name() % std::string("ken"))));

    auto res = fp::query(engine, fp::limit(sq1 + wq1, 10));
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