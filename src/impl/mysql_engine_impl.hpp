#ifndef _MYSQL_ENGINE_IMPL_HPP
#define _MYSQL_ENGINE_IMPL_HPP

#include "../mysql_basic_row.hpp"
#include "../record.hpp"

#include <utility>

namespace fp {
	template<int...> struct int_seq;
	template<typename...> struct type_seq;

	namespace impl {
		template<typename> struct make_record;
        template<int, typename, typename> struct make_record_impl;

        template<int I, typename TRecord, typename H, typename... T> struct make_record_impl<I, TRecord, type_seq<H, T...> > {
            template<typename... TArg>
            static TRecord make(mysql::basic_row const & r, TArg && ... arg) {
                return make_record_impl<I + 1, TRecord, type_seq<T...> >::make(r, std::forward<TArg>(arg)..., r.get<I, H>());
            }
        };

        template<int I, typename TRecord, typename H> struct make_record_impl<I, TRecord, type_seq<H> > {
            template<typename... TArg>
            static TRecord make(mysql::basic_row const & r, TArg && ... arg) {
                return TRecord(std::forward<TArg>(arg)..., r.get<I, H>());
            }
        };

        template<typename TDescriptor, int... Is> struct make_record<record<TDescriptor, Is...> > {
            typedef record<TDescriptor, Is...> TRecord;

            static TRecord make(mysql::basic_row const & r) {
                return make_record_impl<0, TRecord, typename TRecord::types>::make(r);
            }
        };
    }
}

#endif