#ifndef _QUERY_BUILDER_HPP
#define _QUERY_BUILDER_HPP

#include <sstream>

namespace fp {

    template<typename TDescriptor, int I> inline char const * get_field_identifier() {
        return TDescriptor::template field<I>::name;
    }

    namespace impl {
        template<typename, typename...> struct get_where_clauses;
        template<typename TDescriptor, typename H, typename... T> struct get_where_clauses<TDescriptor, H, T...> {
        protected:
            H head;
            get_where_clauses<TDescriptor, T...> tail;
        public:
            get_where_clauses(H h, T... t) : head(h), tail(t...) { }

            void get(std::stringstream & ss) {
                ss << head.template to_string<TDescriptor>() << " AND ";
                tail.get(ss);
            }
        };

        template<typename TDescriptor, typename H> struct get_where_clauses<TDescriptor, H> {
        protected:
            H head;
        public:
            get_where_clauses(H h) : head(h) { }

            void get(std::stringstream & ss) {
                ss << head.template to_string<TDescriptor>();
            }
        };
    }

    template<typename TDescriptor, int... Is> inline char const ** get_field_identifiers() {
        static char const * ret[sizeof...(Is)]= { get_field_identifier<TDescriptor, Is>()... };
        return ret;
    }

    struct query_builder {
        template<typename TDescriptor, int... Cs >
        std::string build_select_query() const {
            char const ** field_identifiers = get_field_identifiers<TDescriptor, Cs...>();
            std::stringstream ss;
            ss << "SELECT ";
            if (sizeof...(Cs) > 0) {
                ss << field_identifiers[0];
                for (unsigned int i = 1; i < sizeof...(Cs); ++i) {
                    ss << ", " << field_identifiers[i];
                }
            }
            ss << " FROM " << TDescriptor::table::name;
            return ss.str();
        }

        template<typename TDescriptor, typename... Ts >
        std::string build_where_query(Ts const &... ts) const {
            std::stringstream ss;
            ss << "WHERE ";
            impl::get_where_clauses<TDescriptor, Ts...> wc(ts...);
            wc.get(ss);
            return ss.str();
        }
    };
}

#endif