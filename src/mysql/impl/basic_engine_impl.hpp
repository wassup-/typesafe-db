#ifndef _MYSQL_ENGINE_IMPL_HPP
#define _MYSQL_ENGINE_IMPL_HPP

#include "../basic_row.hpp"

#include <utility>      // for std::forward

namespace fp {
    template<typename...>
    struct type_seq;
    
    namespace mysql {
        namespace impl {
            
            template<typename>
            struct make_record;
            
            template<int, typename>
            struct make_record_impl;

            template<int I, typename TRecord>
            struct make_record_impl {

                template<typename... TArg>
                static TRecord make(mysql::basic_row const & r, TArg && ... arg) {
                    return make_record_impl<(I - 1), TRecord>::make(r, get<(I - 1), typename TRecord::template nth_type<(I - 1)>::type>(r), std::forward<TArg>(arg)...);
                }
            };

            template<typename TRecord>
            struct make_record_impl<0, TRecord> {

                template<typename... TArg>
                static TRecord make(mysql::basic_row const & r, TArg && ... arg) {
                    return TRecord(std::forward<TArg> (arg)...);
                }
            };

            template<typename TRecord>
            struct make_record {

                static TRecord make(mysql::basic_row const & r) {
                    return make_record_impl<TRecord::size(), TRecord>::make(r);
                }
            };
        }
    }
}

#endif