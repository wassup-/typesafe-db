#ifndef _QUERY_BUILDER_HPP
#define _QUERY_BUILDER_HPP

#include <sstream>

namespace fp {

    template<typename TTable, int I> inline char const * get_field_identifier() {
        return TTable::template field<I>::name;
    }

    namespace impl {
        template<typename TTable, int...> struct get_field_identifiers_impl;
        template<typename TTable, int H, int... T> struct get_field_identifiers_impl<TTable, H, T...> {
            static void get(char const ** buff) {
                *buff = get_field_identifier<TTable, H>();
                get_field_identifiers_impl<TTable, T...>::get(buff + 1);
            }
        };
        template<typename TTable, int H> struct get_field_identifiers_impl<TTable, H> {
            static void get(char const ** buff) {
                *buff = get_field_identifier<TTable, H>();
            }
        };

        template<typename, typename...> struct get_where_clauses;
        template<typename TTable, typename H, typename... T> struct get_where_clauses<TTable, H, T...> {
        protected:
            H head;
            get_where_clauses<TTable, T...> tail;
        public:
            get_where_clauses(H h, T... t) : head(h), tail(t...) { }

            void get(std::stringstream & ss) {
                ss << head.template to_string<TTable>() << " AND ";
                tail.get(ss);
            }
        };

        template<typename TTable, typename H> struct get_where_clauses<TTable, H> {
        protected:
            H head;
        public:
            get_where_clauses(H h) : head(h) { }

            void get(std::stringstream & ss) {
                ss << head.template to_string<TTable>();
            }
        };
    }

    template<typename TTable, int... Is> inline char const ** get_field_identifiers() {
        static char const * ret[sizeof...(Is)];
        impl::get_field_identifiers_impl<TTable, Is...>::get(ret);
        return ret;
    }

    struct query_builder {
        template<typename TTable, int... Cs >
        std::string build_select_query() const {
            char const ** field_identifiers = get_field_identifiers<TTable, Cs...>();
            std::stringstream ss;
            ss << "SELECT ";
            if (sizeof...(Cs) > 0) {
                ss << field_identifiers[0];
                for (unsigned int i = 1; i < sizeof...(Cs); ++i) {
                    ss << ", " << field_identifiers[i];
                }
            }
            ss << " FROM " << TTable::table::name;
            return ss.str();
        }

        template<typename TTable, typename... Ts >
        std::string build_where_query(Ts const &... ts) const {
            std::stringstream ss;
            ss << "WHERE ";
            impl::get_where_clauses<TTable, Ts...> wc(ts...);
            wc.get(ss);
            return ss.str();
        }
    };
}

#endif