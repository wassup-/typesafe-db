#ifndef _SELECT_QUERY_HPP
#define _SELECT_QUERY_HPP

#include "back_inserter.hpp"
#include "is_query.hpp"
#include "query_combiner.hpp"
#include "record.hpp"
#include "type_extractor.hpp"
#include "query_builder.hpp"

#include <algorithm>
#include <vector>

namespace fp {
    template<typename...> struct type_seq;
    template<int...> struct int_seq;
    template<typename, int...> struct select_query;
    
    template<typename TDescriptor, int... Is> struct is_query<select_query<TDescriptor, Is...> > {
        enum { value = true };
    };

    namespace impl {
        template<typename TRecord> struct query_impl;
        template<typename TType> struct get_values_impl;

        template<typename... Ts> struct get_values_impl<type_seq<Ts...> > {
            template<int I, typename Rec>
            static typename nth_type_of<I, Ts...>::type get(Rec const & r) {
                return fp::get<I > (r);
            }
        };

        template<typename TDescriptor, int... Fs> struct query_impl<record<TDescriptor, Fs...> > {
            template<int... Cs> struct result_of {
                typedef record<TDescriptor, Cs...> type;
            };

            template<int... Cs>
            static typename result_of <Cs...>::type select(record <TDescriptor, Fs...> const & r) noexcept {
                return typename result_of<Cs...>::type(impl::get_values_impl<typename TDescriptor::types>::template get<Cs>(r)...);
            }
        };
    }

    template<typename TDescriptor, int... Cs> struct select_query {
    public:
        typedef TDescriptor descriptor_type;
        typedef typename impl::query_impl<typename TDescriptor::record::type>::template result_of < Cs...>::type result_type;
    public:
        template<int... Fs>
        result_type apply(record<TDescriptor, Fs...> const & r) const {
            return impl::query_impl<record<TDescriptor, Fs...> >::template select < Cs...>(r);
        }

        template<int... Fs>
        std::vector<result_type> apply(std::vector<record<TDescriptor, Fs...> > const & r) const {
            std::vector<result_type> ret;
            for (auto const & cur : r) {
                ret.push_back(impl::query_impl<record<TDescriptor, Fs...> >::template select < Cs...>(cur));
            }
            return ret;
        }

        std::string to_string() const {
            query_builder qb;
            return qb.template build_select_query <TDescriptor, Cs...>();
        }
    };

    template<typename TDescriptor, int... Cs, int I>
    inline auto operator+(select_query<TDescriptor, Cs...> const & q, field<TDescriptor, I>) -> decltype(combine(q, select_query<TDescriptor, I>())) {
        return combine(q, select_query<TDescriptor, I>());
    }

    template<typename TDescriptor, int... Cl, int... Cr>
    inline auto operator&(select_query<TDescriptor, Cl...> const & l, select_query<TDescriptor, Cr...> const & r) -> decltype(combine(l, r)) {
        return combine(l, r);
    }

    template<typename TDescriptor, int... Cl, int... Cr>
    inline auto operator|(select_query<TDescriptor, Cl...> const & l, select_query<TDescriptor, Cr...> const & r) -> decltype(combine_unique(l, r)) {
        return combine_unique(l, r);
    }

    template<typename TDescriptor, int... Cs, int... Fs>
    inline auto select(record<TDescriptor, Fs...> const & rec, select_query<TDescriptor, Cs...> const & qry) -> decltype(qry.apply(rec)) {
        return qry.apply(rec);
    }

    template<typename TDescriptor, int... Cs, int... Fs>
    inline auto select(std::vector<record<TDescriptor, Fs...> > const & recs, select_query<TDescriptor, Cs...> const & qry) -> decltype(qry.apply(recs)) {
        return qry.apply(recs);
    }
}

#endif