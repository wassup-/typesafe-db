#ifndef _SELECT_QUERY_IMPL_HPP
#define _SELECT_QUERY_IMPL_HPP

#include "../nth_type_of.hpp"

namespace fp {
    template<typename...> struct type_seq;

    namespace impl {
        template<typename TRecord> struct select_query_impl;
        template<typename TType> struct get_values_impl;

        template<typename... Ts> struct get_values_impl<type_seq<Ts...> > {

            template<int I, typename Rec>
                    static auto get(Rec const & r) -> decltype(fp::get<I > (r)) {
                return fp::get<I > (r);
            }
        };

        template<typename TDescriptor, int... Fs> struct select_query_impl<record<TDescriptor, Fs...> > {

            template<int... Cs> struct result_of {
                typedef record<TDescriptor, Cs...> type;
            };

            template<int... Cs>
            static typename result_of < Cs...>::type select(record<TDescriptor, Fs...> const & r) noexcept {
                return typename result_of < Cs...>::type(get_values_impl<typename TDescriptor::types>::template get<Cs > (r)...);
            }

            static std::string build_select_query() {
                static std::string const field_identifiers[] = { to_string(field<TDescriptor, Fs>())... };
                std::stringstream ss;
                ss << "SELECT ";
                if (sizeof...(Fs) > 0) {
                    ss << field_identifiers[0];
                    for (unsigned int i = 1; i < sizeof...(Fs); ++i) {
                        ss << ", " << field_identifiers[i];
                    }
                }
                ss << " FROM " << TDescriptor::table::name;
                return ss.str();
            }
        };
    }
}

#endif