#ifndef _WHERE_QUERY_IMPL_HPP
#define _WHERE_QUERY_IMPL_HPP

#include <utility>

namespace fp {
	namespace impl {
        template<typename Fn> Fn get_type_of(Fn);

        template<typename, typename...> struct clause_evaluator;
        template<typename TRecord, typename H, typename... T> struct clause_evaluator<TRecord, H, T...> {
        protected:
            H m_head;
            clause_evaluator <TRecord, T...> m_tail;
        public:
            clause_evaluator(H h, T && ... t) : m_head(h), m_tail(std::forward<T> (t)...) { }

            bool operator()(TRecord const & r) const {
                return (m_head(r) && m_tail(r));
            }
        };
        template<typename TRecord, typename H> struct clause_evaluator<TRecord, H> {
        protected:
            H m_head;
        public:
            clause_evaluator(H h) : m_head(h) { }

            bool operator()(TRecord const & r) const {
                return m_head(r);
            }
        };
    }
}

#endif