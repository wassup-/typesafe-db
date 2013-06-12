#ifndef _WHERE_QUERY_IMPL_HPP
#define _WHERE_QUERY_IMPL_HPP

#include <iostream>     // for std::ostream
#include <sstream>      // for std::ostringstream
#include <string>       // for std::string, std::to_string
#include <utility>      // for std::forward

namespace fp {
    namespace impl {
        template<typename...>
        struct clause_evaluator;
        
        template<typename...>
        struct get_where_clauses;
        
        struct where_query_impl;

        template<typename H, typename... T>
        struct clause_evaluator<H, T...> {
        protected:
            H _head;
            clause_evaluator<T...> _tail;
        public:

            clause_evaluator(H h, T && ... t)
            : _head(h), _tail(std::forward<T > (t)...) {
            }

            template<typename... Fs>
            bool operator()(record<Fs...> const & r) const {
                return (_head(r) && _tail(r));
            }
        };

        template<typename H>
        struct clause_evaluator<H> {
        protected:
            H _head;
        public:

            clause_evaluator(H h)
            : _head(h) {
            }

            template<typename... Fs>
            bool operator()(record<Fs...> const & r) const {
                return _head(r);
            }
        };

        template<typename H, typename... T>
        struct get_where_clauses<H, T...> {
        protected:
            H head;
            get_where_clauses<T...> tail;
        public:

            get_where_clauses(H h, T... t)
            : head(h), tail(t...) {
            }

            void get(std::ostream & ss) {
                ss << to_string(head) << " AND ";
                tail.get(ss);
            }
        };

        template<typename H>
        struct get_where_clauses<H> {
        protected:
            H head;
        public:

            get_where_clauses(H h)
            : head(h) {
            }

            void get(std::ostream & ss) {
                ss << to_string(head);
            }
        };

        struct where_query_impl {
            
            template<typename... Fs, typename... TWhere>
            static bool evaluate(record<Fs...> const & r, TWhere &&... c) {
                clause_evaluator<TWhere...> evaluator(std::forward<TWhere>(c)...);
                return evaluator(r);
            }
            
            template<typename... Ts >
            static std::string build_where_query(Ts... ts) {
                std::ostringstream ss;
                ss << "WHERE ";
                impl::get_where_clauses<Ts...> wc(ts...);
                wc.get(ss);
                return ss.str();
            }
        };
    }
}

#endif