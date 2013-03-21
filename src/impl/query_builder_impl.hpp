#ifndef _QUERY_BUILDER_IMPL_HPP
#define _QUERY_BUILDER_IMPL_HPP

#include <sstream>

namespace fp {
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
}

#endif