#ifndef _LIMIT_QUERY_HPP
#define _LIMIT_QUERY_HPP

#include "is_query.hpp"

namespace fp {
	template<typename> struct limit_query;
	
	template<typename TQuery> struct is_query<limit_query<TQuery> > {
		enum { value = true };
	};

    template<typename TQuery> struct limit_query {
    public:
        typedef typename TQuery::descriptor_type TDescriptor;
        typedef typename TQuery::result_type result_type;
    protected:
        TQuery const m_query;
        int m_limit;
    public:
        limit_query(TQuery const & q, int l) : m_query(q), m_limit(l) { }

        template<int... Fs>
        bool evaluate(record<TDescriptor, Fs...> const & rec) const {
            return fp::evaluate(rec, m_query);
        }

        template<int... Fs>
        result_type select(record<TDescriptor, Fs...> const & rec) const {
            return fp::select(rec, m_query);
        }

        template<int... Fs>
        std::vector<result_type> apply(std::vector<record<TDescriptor, Fs...> > const & recs) const {
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
            return m_query.to_string() + " LIMIT " + lexical_cast<std::string>(m_limit);
        }
    };

    template<typename TQuery> typename std::enable_if<is_query<TQuery>::value, limit_query<TQuery> >::type limit(TQuery const & q, int l) {
        return limit_query<TQuery > (q, l);
    }

    template<typename TQuery, typename TDescriptor, int... Fs>
    bool evaluate(record<TDescriptor, Fs...> const & r, limit_query<TQuery> const & q) {
        return q.evaluate(r);
    }

    template<typename TQuery, typename TDescriptor, int... Fs>
    typename TQuery::result_type select(record<TDescriptor, Fs...> const & r, limit_query<TQuery> const & q) {
        return q.select(r);
    }
}

#endif