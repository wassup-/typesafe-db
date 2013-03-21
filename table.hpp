#ifndef _TABLE_HPP
#define _TABLE_HPP

#include "int_sequence.hpp"

namespace fp {
	template<typename...> struct type_seq;
	template<typename, int...> struct record;

	namespace {
		template<typename, typename> struct make_record;
		template<typename TDescriptor, int... Is> struct make_record<TDescriptor, int_seq<Is...> > {
			typedef fp::record<TDescriptor, Is...> type;
		};
	}

    template<typename... Ts> struct table {
        typedef type_seq<Ts...> types;

        template<typename TDescriptor> struct record {
            typedef typename make_record<TDescriptor, typename range_builder<0, sizeof...(Ts)>::type>::type type;
        };
    };
}

#endif