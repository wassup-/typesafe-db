#ifndef _WHERE_QUERY_IMPL_HPP
#define _WHERE_QUERY_IMPL_HPP

#include <sstream>      // for std::stringstream
#include <utility>      // for std::forward

namespace fp {
    namespace impl {
        template<typename Fn> Fn get_type_of(Fn);

        template<typename, typename...> struct clause_evaluator;
        template<typename, typename...> struct get_where_clauses;
        struct where_query_impl;

        template<typename TDescriptor, typename H, typename... T> struct clause_evaluator<TDescriptor, H, T...> {
        protected:
            H m_head;
            clause_evaluator <TDescriptor, T...> m_tail;
        public:

            clause_evaluator(H h, T && ... t) : m_head(h), m_tail(std::forward<T > (t)...) {
            }

            template<int... Is>
            bool operator()(record<TDescriptor, Is...> const & r) const {
                return (m_head(r) && m_tail(r));
            }
        };

        template<typename TDescriptor, typename H> struct clause_evaluator<TDescriptor, H> {
        protected:
            H m_head;
        public:

            clause_evaluator(H h) : m_head(h) {
            }

            template<int... Is>
            bool operator()(record<TDescriptor, Is...> const & r) const {
                return m_head(r);
            }
        };

        template<typename TDescriptor, typename H, typename... T> struct get_where_clauses<TDescriptor, H, T...> {
        protected:
            H head;
            get_where_clauses<TDescriptor, T...> tail;
        public:

            get_where_clauses(H h, T... t) : head(h), tail(t...) {
            }

            void get(std::stringstream & ss) {
                ss << to_string(head) << " AND ";
                tail.get(ss);
            }
        };

        template<typename TDescriptor, typename H> struct get_where_clauses<TDescriptor, H> {
        protected:
            H head;
        public:

            get_where_clauses(H h) : head(h) {
            }

            void get(std::stringstream & ss) {
                ss << to_string(head);
            }
        };

        struct where_query_impl {
            template<typename TDescriptor, int... Is, typename... TClauses>
            static bool evaluate(record<TDescriptor, Is...> const & r, TClauses... c) {
                clause_evaluator<TDescriptor, TClauses...> evaluator(std::forward<TClauses>(c)...);
                return evaluator(r);
            }
            
            template<typename TDescriptor, typename... Ts >
            static std::string build_where_query(Ts const &... ts) {
                std::stringstream ss;
                ss << "WHERE ";
                impl::get_where_clauses<TDescriptor, Ts...> wc(ts...);
                wc.get(ss);
                return ss.str();
            }
        };
    }
}

#endif