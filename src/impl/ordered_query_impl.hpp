#ifndef _ORDERED_QUERY_IMPL_HPP
#define _ORDERED_QUERY_IMPL_HPP

#include "../type_traits.hpp"

#include <functional>   // for std::binary_function

namespace fp {
    namespace impl {

        struct ordered_query_impl {
            static char const * const ORDERINGS[];

            template<typename TRecord, typename TField, EnableIf<is_record<TRecord>> = _>
            struct ascending_sorter : std::binary_function<TRecord const &, TRecord const &, bool> {

                bool operator()(TRecord const & l, TRecord const & r) const {
                    return (get<TField>(l) <= get<TField>(r));
                }
            };

            template<typename TRecord, typename TField, EnableIf<is_record<TRecord>> = _>
            struct descending_sorter : std::binary_function<TRecord const &, TRecord const &, bool> {

                bool operator()(TRecord const & l, TRecord const & r) const {
                    return (get<TField>(l) >= get<TField>(r));
                }
            };
        };
        
        char const * const ordered_query_impl::ORDERINGS[] = {"ASC", "DESC"};
    }
}

#endif